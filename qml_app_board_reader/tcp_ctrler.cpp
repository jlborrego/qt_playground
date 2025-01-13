///*
//	Revisiones:

//	28.03.08.
//	Cambio en como se guardan los valores en las variables
//	que sean independientes a endian del host.

//	Se almacenaran siempre en el endian que tenga el host donde se esta corriendo
//	local_port
//	TSlot.peer_port
//	TSlot.peer_ip

//*/
////#define VERBOSE
//#ifdef HAVE_CONFIG_H
//#  include <config.h>
//#endif
//#include <sys/types.h>
//#include <sys/socket.h>

//#include <stdio.h>
//#include <unistd.h>

//#include <stdarg.h>
//#include <stdlib.h>

//#include <string.h>
//#include <fcntl.h>
//#include <errno.h>

//#include <netdb.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <time.h>
//#include <sys/time.h>
//#include <linux/socket.h>

//#include <signal.h>
//#include <bits/signum.h>

//#include <pthread.h>

//#include <common/util.h>
//#include <common/tcp_ctrler.h>
//#include <ipc/lib.h>

//#include <common/sys_notifier.h>


//#ifndef MIN
//#define MIN(x,y) ((x)<(y)?(x):(y))
//#define MAX(x,y) ((x)>(y)?(x):(y))
//#endif



///**
//	VARIABLES DE TRABAJO INTERNAS A ESTE MODULO
//***************************************************************************/
//// esta variable guarda el puerto usado por el host para recibir sockets
//// entrantes, su valor esta guardado SIEMPRE en el formato del HOST,
//// si el host es big endian, sera BIG sino sera LIT
//static  __u16 local_port;
//static  __u32 local_ip;

//static int com_running;
//static  __u32 local_flags;
//static  int local_skt = -1;



//typedef void ( *slot_callback )( char *slot,  t_socket_msg *msg );
//typedef void ( *_slot_callback )( char *slot, t_socket_msg *msg, void *arg );
//typedef struct
//{
//    char	name[16];
//    __u8	local_id;
//    __u8	peer_id;

//    __u16	peer_port;
//    __u32	peer_ip;

//    int skt_in, skt_out;
//    struct
//    {
//        __u16   active:1;
//        __u16   connected:1;
//        __u16   pinging:3;
//        __u16   autoconnect:1;
//    }
//    flags;
//    void *arg;
//    slot_callback	callback;
//    _slot_callback	_callback;
//    sys_notifier_t	notifier;
//}
//TSlot;

//#define	DIRECTION_QUERY		1
//#define	DIRECTION_REPLY		2

//typedef struct THandcheck
//{
//    struct
//    {
//        int	direction;
//        int	stamp;
//        int	msg_id;
//        int	msg_len;
//    }
//    header;
//    char	data[1024];
//}
//THandcheck;

//typedef struct TRetry
//{
//    struct TRetry *next;

//    struct
//    {
//        char      enabled:1;
//        char      no_stop:1;
//    }
//    flags;

//    char	      channel[32];
//    __u32	      next_xmit;
//    __u32	      delay;
//    __u16	      stamp;
//    __u16	      size;
//    THandcheck *msg;
//    short	      period;
//}
//TRetry;

///**
//	FORWARD DECLARATIONS
//***************************************************************************/
//static void *controller_process( void *dummy_arg );
//char *show_msg            ( char *lab, void *msg, int len);

//static void processEncapsulatedMessage( TSlot* , t_socket_msg* );
//static void processSendFileMessage( TSlot* , t_socket_msg* );
//static void process_new_conection(int skt, struct sockaddr_in* );
//static void process_slot_request(int skt, struct sockaddr_in*, t_socket_msg* );
//static void process_slot_accepted(int skt, struct sockaddr_in*, t_socket_msg* );

//static void *slot_process       ( void *);
//static void slot_run            ( TSlot* );
//static void slot_try_connect    ( TSlot* );
//static void slot_upload_msg     ( TSlot*, int msg_id, void *data, int len );
//static TSlot *slot_find_by_id   ( int id );
//static TSlot *slot_find_by_name ( char *name );
//static TSlot* slot_get_by_link  ( int link_id );

//static int make_nonblock  ( int socket, int nonblock);
//static int waitconnect    ( int sockfd, int timeout_msec );
//static int socketerror    ( int sockfd );

//static int tcp_connect    ( __u32 saddr, __u16 port, int timeout);
//static int tcp_read_msg   ( int skt, void *data, int timeout);
//static int tcp_write_msg  ( int skt, int link, int id, void *data, int len, int timeout);
//static int tcp_read_data  ( int skt, void *data, int len, int timeout);
//static int tcp_write_data ( int skt, void *data, int len, int timeout);

//static void   *retry_process(void *v);
//static TRetry *retry_find( char *channel, int msg_id );
//static TRetry *retry_alloc( int len );
//static TRetry *retry_realloc( TRetry*, int len );
//static void retry_unlock(void );
//static void retry_lock( void );
//static __u32 xmit_now( void );

//static void slot_gateway(sys_callback_t *cb, void *msg);


///*******************************************************************************
//transmision de archivos
//*******************************************************************************/
//typedef struct TFile
//{
//    struct TFile *next;
//    char	channel[32];
//    char	realname[128];
//    char	filename[128];
//    int	file_id;
//    FILE *fd;
//    int	pos;
//    int	size;
//    int	eof:1;
//    int	enabled:1;
//    int	fname:1;
//    int	retrieve:1;
//    int	sender;
//    void	*cb, *dt;
//}
//TFile;
//static TFile *file_find( char *channel, int msg_id, int sender );
//static int    fsize( FILE *fd );
//static void   file_lock( void );
//static void   file_unlock( void );

//typedef struct TChannelFile
//{
//    int  file_id;
//    int  pos;
//    int  size;
//    int  ack;
//    int  eof;
//    int  fname;
//    int  retrieve;
//    char buffer[256];
//}
//TChannelFile;
//typedef void ( *FileCallback )(char *channel, int file_id, char *fname, char *realname);

//#define kill_socket( socket_fd, timeout ) { shutdown( socket_fd, timeout ); close( socket_fd ); }


//static TSlot slots[ POOL_SIZE ];

//static pthread_mutex_t	retry_mutex = PTHREAD_MUTEX_INITIALIZER;
//static pthread_cond_t	retry_cond = PTHREAD_COND_INITIALIZER;
//static volatile  __u8		retry_pending;
//static  __u16		retry_stamp;
//static  __u32		retry_start;
//static  TRetry		*retry_pool;

//static pthread_mutex_t	file_mutex = PTHREAD_MUTEX_INITIALIZER;
//static TFile  *file_pool;
//static void slot_send_file_xmit( TFile* );
//static void slot_retrieve_file_xmit( TFile* );
//static int booted = 0;
///* ----------------------------- User API stuff ------------------------------ */



///* 1.- slot facility  ----------------------------------------------------- */
//int slot_init( char *ip, __u16 port, __u32 flags )
//{
//    if( booted ) return 1;
//    booted = 1;

//    memset( slots, 0, sizeof( slots ) );
//    retry_start = ( __u32 )time( NULL );

//    com_running = 1;
//    local_flags = flags;
//    local_port = BE16(port);	// local port siempre estara guardado como big endian

//    if (!ip || !*ip)
//    {
//        char localhost[64];

//        if( gethostname( localhost, sizeof( localhost ) ) < 0 )
//        {
//            ERROUT(("[%s:%d] Unable to load local hostname. Aborting...", __func__, __LINE__));
//            exit(0);
//        }

//        LOG_TRACE( "[%s]localhost[%s]", __func__, localhost );
//        ip= slot_get_host_ip( localhost );

//    }

//    if ( !ip || !*ip )
//    {
//        ERROUT(("[%s:%d] Unable to load local hostname. Aborting...", __func__, __LINE__));
//        exit(0);
//    }

//    local_ip= inet_addr(ip); // local ip siempre estara como bigendian
//    local_skt = -1;

//    if( dbg_create_thread(NULL, NULL, controller_process, NULL) != 0 )
//        return 0;
//    if (dbg_create_thread(NULL, NULL, retry_process, NULL ) != 0 )
//        return 0;

//    // el evento sigpipe tiene que estar desconectado
//    signal(SIGPIPE, SIG_IGN);

//    return 1;

//}

//void slot_shutdown( void )
//{
//    LOG_TRACE("Communication controller closing...");
//    com_running= 0;
//    kill_socket( local_skt, 2);

//}


//int _slot_create( char *name, int peer_id, int local_id, void *cb, void *arg )
//{
//    int i;
//    pthread_t  th;
//    TSlot   *slot = slot_find_by_name( name );

//    if( ! slot )
//    {
//        for( i = 0 ; i < POOL_SIZE; i++ )
//        {
//            if( slots[ i ].name[ 0 ] == 0 )
//            {
//                slot= & slots[ i ];
//                break;
//            }
//        }
//    }
//    if ( ! slot )
//        return 0;
//    memset( slot, 0, sizeof( *slot ) );
//    strcpy( slot->name, name );
//    slot->local_id = local_id;
//    slot->peer_id  = peer_id;
//    slot->arg      = ( void* )arg;
//    if( arg == NULL )
//    {
//        slot->callback  = ( slot_callback )cb;
//        slot->_callback = NULL;
//    }
//    else
//    {
//        slot->callback  = NULL;
//        slot->_callback = ( _slot_callback )cb;
//    }
//    sys_notifier_init( &slot->notifier );
//    if( pthread_create( & th, NULL, slot_process, slot ) != 0 )
//    {
//        WARN_TRACE("%s.%d %s: %s",
//                   __FUNCTION__ , __LINE__ , slot->name, strerror( errno ) );
//        return 0;
//    }
//    return 1;
//}


//int slot_create( char *name, int peer_id, int local_id, void *cb )
//{
//    return _slot_create( name, peer_id, local_id, cb, NULL );
//}


//int slot_connect( char *name, char *ip, __u16 port )
//{
//    TSlot   *slot = slot_find_by_name( name );

//    if( ! slot )
//        return 0;
//    if( ip && *ip )
//        slot->peer_ip= ntohl(inet_addr(ip)); // local host endian (inet_addr devuelve big)
//    else
//        slot->peer_ip = 0;

//    slot->peer_port= port; // local host endian
//    slot->flags.connected = 0;
//    slot->flags.autoconnect = 1;
//    return 1;

//}


//int slot_activate( char *name )
//{
//    TSlot   *slot = slot_find_by_name( name );

//    if ( !slot ) return 0;
//    slot->flags.active = 1;
//    return 1;

//}


//int slot_deactivate(char *name)
//{
//    TSlot   *slot = slot_find_by_name(name);

//    if (!slot) return 0;
//    slot->flags.active= 0;
//    return 1;

//}


//int slot_write_msg(char *name, int msg_id, void *data, int len )
//{
//    TSlot   *slot = slot_find_by_name( name );

//    if ( ! slot) return -1;
//    if ( ! slot->flags.active ) return -1;
//    if ( ! slot->flags.connected ) return -1;
//    //	LOG_TRACE( "\tid=%d", msg_id );
//    tcp_write_msg( slot->skt_out, slot->local_id, msg_id, data, len, 3000 );
//    return 1;

//}


//int slot_is_connected( char *name )
//{
//    TSlot   *slot = slot_find_by_name(name);

//    return( slot && slot->flags.active && slot->flags.connected );

//}

//char *slot_get_host_ip( char *name )
//{
//    static char ip[32];
//    struct hostent *host= gethostbyname (name);

//    if ( ! host )
//        return NULL;
//    strcpy( ip, inet_ntoa( * ( ( struct in_addr* )( host->h_addr_list[ 0 ] ) ) ) );
//    return( ip );

//}



///* 2.- Latch facility API -------------------------------------------------- */
//#include "suinsa/communications_iface.h"
//int slot_write_latch_msg( char *channel, int msg, void *data, int len,
//                         int period /* en segundos */)
//{
//    TRetry *retry;

//    /* paranoid section */
//    //	if ( len < 0 || len > 1024 )
//    //	{
//    //		  ERR_TRACE( "[%s:%d]Size out of limits [%d]", __func__, __LINE__, len );
//    //		  return 0;
//    //	}

//    if ( len && ! data )
//    {
//        ERR_TRACE( "[%s:%d]Invalid data", __func__, __LINE__ );
//        return 0;
//    }

//    retry = retry_find( channel, msg );
//    if ( ! retry )
//        retry = retry_alloc( len );
//    if ( ! retry )
//    {
//        retry_unlock( );
//        ERR_TRACE( "[%s:%d]", __func__, __LINE__ );
//        return 0;
//    }

//    // si existe, pero no tiene espacio suficiente, intentar aumentar
//    if ( len > retry->size )
//        retry = retry_realloc(retry, len);

//    if ( ! retry )
//    {
//        retry_unlock();
//        ERR_TRACE( "[%s:%d]", __func__, __LINE__ );
//        return 0;
//    }

//    if ( period < 1 )
//        period = 1;

//    strcpy( retry->channel, channel );
//    retry->period = period * 1000;
//    retry->flags.enabled= 1;

//    retry->msg->header.direction= DIRECTION_QUERY;
//    retry->msg->header.stamp= retry->stamp;
//    retry->msg->header.msg_id= msg;
//    retry->msg->header.msg_len= len;
//    if ( len && data )
//        memcpy(retry->msg->data, data, len);

//    retry->stamp= ++retry_stamp;
//    retry->msg->header.stamp = retry->stamp;
//    retry->next_xmit = MAX( xmit_now(), retry->delay );
//    retry_pending++;
//    pthread_cond_signal( & retry_cond );
//    retry_unlock();

//    return 1;
//}


//void slot_latch_stop(char *channel, int msg)
//{
//    TRetry *retry = retry_find(channel, msg);

//    if (!retry)
//    {
//        retry_unlock();
//        return;
//    }

//    retry->flags.enabled= 0;
//    retry_unlock();
//    return;

//}


//void slot_latch_config(char *channel, int msg, int flags)
//{
//    TRetry *retry = retry_find( channel, msg );

//    if (!retry)
//        retry= retry_alloc(16);
//    if (!retry)
//    {
//        retry_unlock();
//        return;
//    }
//    strcpy(retry->channel, channel);
//    retry->msg->header.direction = DIRECTION_QUERY;
//    retry->msg->header.msg_id = msg;
//    retry->flags.no_stop = ( flags & LATCH_NO_STOP ) !=0 ;
//    retry_unlock();

//}


///* 3. File transfer facility ------------------------------------------- */
//int slot_file_setup(char *channel, int file_id, int action, void *cb)
//{
//    TFile *file= file_find( channel, file_id, action );

//    if (!file)
//    {
//        file_unlock();
//        return 0;
//    }

//    file->cb= cb;
//    file->dt= NULL;

//    file_unlock();
//    return 1;
//}


///* Retrieves from the "channel" slot the "file_id" index (see file setup)  */
//int slot_retrieve_file( char *channel, int file_id, char *peer_name,
//                       void *cb, void *dt )
//{
//    TFile *file= file_find( channel, file_id, FILE_RECEIVER );

//    if( ! file )
//    {
//        file_unlock();
//        return 0;
//    }

//    file->enabled= 0;
//    file->pos= 0;
//    file->eof= 0;
//    file->retrieve= 1;
//    file->dt= dt;
//    file->cb= cb;
//    file->fname= 1;
//    strcpy( file->filename, peer_name );
//    if ( file->fd )
//        fclose( file->fd );
//    file->fd = 0;
//    file->enabled= 1;
//    slot_latch_config( channel, __SEND_FILE_id, LATCH_NO_STOP );
//    slot_retrieve_file_xmit(file);
//    file_unlock();
//    return 1;

//}


//int slot_retrieve_stop( char *channel, int file_id )
//{
//    TFile *file= file_find( channel, file_id, FILE_RECEIVER );

//    if (!file)
//    {
//        file_unlock();
//        return 0;
//    }
//    file->enabled= 0;
//    file->retrieve= 0;
//    file->cb= NULL;
//    file->dt= NULL;
//    file_unlock();
//    return 1;

//}


//int  slot_send_file( char *channel, int file_id, char *file_name,
//                   char *target_name )
//{
//    TFile *file= file_find( channel, file_id, FILE_SENDER );

//    if ( ! file )
//    {
//        file_unlock( );
//        return 0;
//    }

//    file->pos      = 0;
//    file->enabled  = 0;
//    file->retrieve = 0;
//    file->fname = 0;
//    file->cb = NULL;
//    file->dt = NULL;
//    strcpy(file->filename, file_name);
//    if( file->fd )
//        fclose( file->fd );
//    file->fd = fopen(file->filename, "r");
//    if( ! file->fd )
//    {
//        file_unlock();
//        return 0;
//    }
//    if( target_name && *target_name )
//    {
//        strcpy(file->filename, target_name);
//        file->fname = 1;
//    }
//    file->size = fsize( file->fd );
//    file->enabled = 1;
//    slot_latch_config( channel, __SEND_FILE_id, LATCH_NO_STOP );
//    slot_send_file_xmit( file );
//    file_unlock();
//    return 1;

//}


//int slot_send_stop(char *channel, int file_id)
//{
//    TFile *file= file_find( channel, file_id, FILE_SENDER );

//    if( ! file )
//    {
//        file_unlock();
//        return 0;
//    }
//    file->enabled = 0;
//    file->retrieve = 0;
//    file->cb = NULL;
//    file->dt = NULL;
//    file_unlock( );
//    return 1;

//}



///* ------------------------------ Internal stuff ---------------------------- */
//static TSlot *slot_find_by_id(int id)
//{
//    int i;

//    for( i = 0 ; i < POOL_SIZE; i++ )
//        if( slots[ i ].peer_id == id )
//            return( slots + i );
//    return NULL;

//}


//static TSlot *slot_find_by_name(char *name)
//{
//    int i;

//    for( i = 0; i < POOL_SIZE; i++)
//        if ( strcmp( slots[ i ].name, name ) == 0 )
//            return & slots[ i ];
//    return NULL;

//}


//static void *controller_process(void *v)
//{
//    int reuse =1;
//    int child;
//    socklen_t cb_addr;
//    struct sockaddr_in addr;

//    LOG_TRACE("TCP connector thread:%30s", "Up And Running");
//    pthread_detach( pthread_self( ) );

//    while( com_running )
//    {
//        local_flags &= ~1;
//        sleep( 1 );
//        local_skt= socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
//        if ( local_skt < 0 )
//            continue;

//        addr.sin_family= AF_INET;
//        addr.sin_port= local_port; // localport ya es big endian
//        addr.sin_addr.s_addr= 0;

//        setsockopt(local_skt, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse, sizeof(reuse));
//        if (bind(local_skt, (struct sockaddr*)&addr, sizeof(addr)))
//        {
//            close(local_skt);
//            continue;
//        }

//        if( listen( local_skt, 4 ) )
//        {
//            kill_socket( local_skt, 2 );
//            continue;
//        }

//        local_flags |= 1;

//        LOG_TRACE("[%s] connector requested: now listening on %08x:%d", __func__, ntohl(addr.sin_addr.s_addr), ntohs(local_port));
//        while (com_running)
//        {
//            cb_addr = sizeof( addr );
//            child = accept( local_skt, ( struct sockaddr* )& addr, & cb_addr );
//            if ( child < 0 )
//            {
//                kill_socket( local_skt, 2 );
//                break;
//            }
//            LOG_TRACE("[%s] channel requested: %08x:%d", __func__, ntohl(addr.sin_addr.s_addr), ntohs(addr.sin_port));
//            process_new_conection(child, &addr);
//        }
//    }

//    LOG_TRACE("TCP connector thread: %30s", "exits");
//    return NULL;

//}



//void process_new_conection( int skt, struct sockaddr_in *addr )
//{
//    int			err;
//    t_socket_msg	msg;

//    DBUG_TRACE("TCP connector NEW CONNECTION requested from %08x", htonl(addr->sin_addr.s_addr));

//    if ( (err=tcp_read_msg( skt, & msg, 2000 )) <= 0 )
//    {
//        kill_socket( skt, 2 );
//        return;
//    }

//    DBUG_TRACE("TCP connector NEW CONNECTION request header (%d . %d)",
//               msg.header.bit.link_id, msg.header.bit.msg_id);

//    switch( msg.header.bit.msg_id )
//    {
//    default:
//        kill_socket( skt, 2 );
//        return;

//    case __CHANNEL_CONNECTION_id:
//        process_slot_request( skt, addr, & msg );
//        return;

//    case __FULL_DUPLEX_COMPLETED_id:
//        process_slot_accepted (skt, addr, & msg );
//        return;
//    }

//}


//static TSlot* slot_get_by_link( int link_id )
//{
//    TSlot* slot = NULL;

//    if( ( slot = slot_find_by_id( link_id ) ) == 0 )
//    {
//        DBUG_TRACE( "slot not found for network link %d", link_id );
//        return( ( TSlot* )NULL );
//    }

//    if( ! slot->flags.active )
//    {
//        DBUG_TRACE( "manager got request from %d but we are disabled", link_id );
//        return( ( TSlot* )NULL );
//    }
//    return( slot );

//}


//static void process_slot_request( int skt, struct sockaddr_in *addr,
//                                 t_socket_msg *msg )
//{
//    TSlot	*slot;
//    t_tcp_pluggin	plug;

//    if( ( slot = slot_get_by_link( msg->header.bit.link_id ) ) == NULL )
//    {
//        kill_socket(skt, 2);
//        return;
//    }

//    // everything looks ok, connect the output socket, and activate the channel
//    slot->flags.connected = 0;
//    memcpy( & plug, msg->packet +1, sizeof( plug ) );
//    slot->peer_ip = ntohl(addr->sin_addr.s_addr); // addr->sin_addr.s_addr es big
//    slot->peer_port = plug.port; // local host endian

//    slot->skt_out = tcp_connect(slot->peer_ip, slot->peer_port, 1000 );
//    if( slot->skt_out < 0 )
//    {
//        DBUG_TRACE("manager got request from %d but it don't allow connection",
//                   msg->header.bit.link_id );
//        kill_socket( skt, 2 );
//        return;
//    }

//    // peer accepts connection, send full duplex pluging
//    // no se llena la informacion
//    // porque el peer ya la conoce
//    plug.ip = 0;
//    plug.port = 0;
//    if( tcp_write_msg( slot->skt_out,
//                      slot->local_id, __FULL_DUPLEX_COMPLETED_id,
//                      & plug, sizeof( plug ), 3000 ) < 0 )
//    {
//        kill_socket( skt, 2 );
//        kill_socket( slot->skt_out, 2 );
//        return;
//    }

//    // we are now connected to the other part
//    slot->skt_in = skt;
//    slot->flags.connected = 1;
//    msg->header.bit.msg_id = __FULL_DUPLEX_COMPLETED_id;

//    if( slot->callback )  slot->callback ( slot->name, msg );
//    if( slot->_callback ) slot->_callback( slot->name, msg, slot->arg );
//    sys_notifier_call( &slot->notifier, slot_gateway, msg );
//    return;

//}


//static void process_slot_accepted( int skt, struct sockaddr_in *addr,
//                                  t_socket_msg *msg )
//{
//    TSlot	*slot;

//    if( ( slot = slot_get_by_link( msg->header.bit.link_id ) ) == NULL )
//    {
//        kill_socket( skt, 2);
//        return;
//    }
//    slot->skt_in = skt;
//    slot->flags.connected = 1;
//    if( slot->callback )  slot->callback ( slot->name, msg );
//    if( slot->_callback ) slot->_callback( slot->name, msg, slot->arg );
//    sys_notifier_call( &slot->notifier, slot_gateway, msg );

//}


//static void slot_upload_msg( TSlot *slot, int msg_id, void *data, int len )
//{
//    t_socket_msg	msg;

//    msg.header.bit.link_id= 0;
//    msg.header.bit.msg_id= msg_id;
//    msg.header.bit.so_packet= ( len +3 ) & ~3;
//    if ( data && ( len > 0 ) )
//        memcpy( msg.packet +1, data, len);
//    if( slot->callback )  slot->callback ( slot->name, & msg );
//    if( slot->_callback ) slot->_callback( slot->name, & msg, slot->arg );
//    sys_notifier_call( &slot->notifier, slot_gateway, &msg );

//}


//static void *slot_process( void *v )
//{
//    TSlot *slot = ( TSlot* )v;

//    LOG_TRACE("peer(%s) %30s ", slot->name, "Up and Running" );
//    pthread_detach( pthread_self() );
//    {
//        char s[128];
//        sprintf(s, "slot_process:%s", slot->name);
//    }

//    while( com_running )
//    {
//        sleep(1);
//        if (!slot->flags.active) continue;

//        if ( ! slot->flags.connected && slot->flags.autoconnect )
//            slot_try_connect(slot);

//        if ( slot->flags.connected )
//            slot_run(slot);
//    }
//    LOG_TRACE( "Communication peer (%s) thread leave", slot->name );
//    return NULL;

//}


//static void slot_close( TSlot *slot )
//{
//    slot->flags.connected= 0;
//    kill_socket( slot->skt_out, 2);
//    kill_socket( slot->skt_in, 2);
//}


//static void slot_run( TSlot *slot )
//{
//    int delay;
//    unsigned long  timestamp;

//    DBUG_TRACE( "%s.%s on going", __FUNCTION__, slot->name );

//    timestamp = time(NULL) + 5;

//    slot->flags.pinging= 0;
//    delay= 1000;

//    while( slot->flags.connected )
//    {
//        t_socket_msg	msg;

//        if( ! slot->flags.active )
//        {
//            LOG_TRACE("Communication closed: channel \"%s\" is deactivated",
//                      slot->name );
//            slot_close( slot );
//            msg.header.bit.msg_id= __KILL_CONNECTION_id;
//            if( slot->callback )  slot->callback ( slot->name, & msg );
//            if( slot->_callback ) slot->_callback( slot->name, & msg, slot->arg );
//            sys_notifier_call( &slot->notifier, slot_gateway, &msg );
//            return;
//        }

//        if( ( time(NULL) - timestamp ) >= 5 )
//        {
//            timestamp = time(NULL);
//            msg.header.bit.link_id = slot->local_id;
//            msg.header.bit.msg_id= __CHANNEL_ECHO_ANS_id;
//            if( slot->callback )  slot->callback ( slot->name, & msg );
//            if( slot->_callback ) slot->_callback( slot->name, & msg, slot->arg );
//            sys_notifier_call( &slot->notifier, slot_gateway, &msg );
//        }

//        if( tcp_read_msg( slot->skt_in, &msg, delay ) <= 0 )
//        {
//            delay= 1000;
//            tcp_write_msg( slot->skt_out, slot->local_id,
//                          __CHANNEL_ECHO_REQ_id, NULL, 0, 3000);
//            if ( ++slot->flags.pinging > 6 )
//            {
//                WARN_TRACE("communication lost: channel \"%s\"", slot->name );
//                slot_close(slot);
//                msg.header.bit.msg_id= __KILL_CONNECTION_id;
//                if( slot->callback )  slot->callback ( slot->name, & msg );
//                if( slot->_callback ) slot->_callback( slot->name, & msg, slot->arg );
//                sys_notifier_call( &slot->notifier, slot_gateway, &msg );
//                return;
//            }
//            continue;
//        }
//        slot->flags.pinging= 0;
//        delay= 5000;

//        // si es una respuesta del ping, continuamos
//        if( msg.header.bit.msg_id == __CHANNEL_ECHO_ANS_id )
//            continue;

//        // si es una peticion de ping, respondemos y continuamos
//        if (msg.header.bit.msg_id == __CHANNEL_ECHO_REQ_id )
//        {
//            tcp_write_msg( slot->skt_out,
//                          slot->local_id,
//                          __CHANNEL_ECHO_ANS_id, NULL, 0, 3000 );
//            continue;
//        }

//        if( msg.header.bit.msg_id == __ENCAP_ACK_MSG_id )
//        {
//            processEncapsulatedMessage( slot, & msg );
//            continue;
//        }


//        if( msg.header.bit.msg_id == __SEND_FILE_id )
//        {
//            processSendFileMessage(slot, &msg);
//            continue;
//        }

//        if( slot->callback )  slot->callback ( slot->name, & msg );
//        if( slot->_callback ) slot->_callback( slot->name, & msg, slot->arg );
//        sys_notifier_call( &slot->notifier, slot_gateway, &msg );
//    }

//}


///*
// * Return >= 0 on fine connect, -1 on timeout or error
// */
//static int tcp_connect(__u32 saddr, __u16 port, int timeout)
//{
//    int  rc, skt;
//    struct 	sockaddr_in	addr;

//    skt= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

//    if (skt<0) return -1;

//    make_nonblock(skt, 1);

//    addr.sin_family= AF_INET;
//    addr.sin_port= htons(port);
//    addr.sin_addr.s_addr= htonl(saddr);
//    rc = connect(skt, (struct sockaddr*) &addr, sizeof(addr));

//    // si se conecto, solo en raras ocasiones da tiempo en un socket
//    // nonblock que se conecte antes de retornar, pero puede ser
//    if (rc==0)
//    {
//        make_nonblock(skt, 0);
//        return skt;
//    }

//    // si no se conecto, que paso ?
//    switch ((rc=errno))
//    {
//    case 0:
//    case ECONNREFUSED: /* no one listening */
//    default:
//        /* unknown error, fallthrough ! */
//        break;

//    case EINPROGRESS:
//    case EAGAIN:
//    case EINTR:
//        /* asynchronous connect, wait for connect or timeout */
//        rc = waitconnect(skt, timeout);
//        break;
//    }

//    make_nonblock(skt, 0);

//    if (rc!=0)
//    {
//        shutdown(skt, 2);
//        close(skt);
//        return -1;
//    }

//    return skt;
//}


//static int make_nonblock(int socket,   int nonblock )
//{
//    int flags;

//    flags = fcntl(socket, F_GETFL, 0);
//    if (nonblock)
//        return fcntl(socket, F_SETFL, flags | O_NONBLOCK);
//    else
//        return fcntl(socket, F_SETFL, flags & (~O_NONBLOCK));
//}


///*
// * Return 0 on fine connect, -1 on error and 1 on timeout.
// */
//static int waitconnect( int sockfd, int timeout_msec )
//{
//    fd_set fd;
//    fd_set errfd;
//    struct timeval interval;
//    int rc;

//    interval.tv_sec = timeout_msec/1000;
//    interval.tv_usec = (timeout_msec % 1000) * 1000;

//    for (;;)
//    {

//        /* now select() until we get connect or timeout */
//        FD_ZERO( & fd);
//        FD_SET( sockfd, & fd);
//        FD_ZERO( & errfd);
//        FD_SET( sockfd, & errfd);
//        rc = select( sockfd +1, NULL, & fd, & errfd, & interval );
//        if ( rc < 1 ) return -1;

//        if(FD_ISSET(sockfd, &errfd))
//        {
//            /* error condition caught */
//            return 2;
//        }

//        if(FD_ISSET(sockfd, &fd))
//        {
//            int err = socketerror(sockfd);

//            if ((err==0) || (err==EISCONN))
//            {
//                /* we are connected, awesome! */
//                return 0;
//            }
//        }

//    }

//    /* we have a connect! */
//    return -2;
//}


//static int socketerror(int sockfd)
//{
//    int err = 0;
//    socklen_t errSize = sizeof(err);

//    if( -1 == getsockopt(sockfd, SOL_SOCKET, SO_ERROR,
//                         ( void * ) & err, & errSize ) )
//        err = errno;
//    return err;

//}

//static int  tcp_read_msg(int skt, void *data, int timeout)
//{
//    int i, size;
//    t_socket_msg	msg;
//    unsigned int	*tmp= ( unsigned int* )( & msg );

//    size = tcp_read_data( skt, ( char* ) & msg.header, sizeof(msg.header), timeout );
//    if ( size <= 0 )
//        return -2;

//    tmp[ 0 ]= ntohl( tmp[ 0 ] );
//    size= (msg.header.bit.so_packet+3) >> 2;
//    if (tcp_read_data(skt, (char*)&msg.packet[1], 4 * (size+1), timeout)<=0)
//        return -3;

//    if ( ! msg.header.bit.endian )
//    {
//        for( i=1; i<=size; i++ )
//            tmp[ i ]= ntohl( tmp[ i ] );
//    }
//    tmp[size+1]= htonl(tmp[size+1]);

//    msg.packet[ 0 ] = msg.packet[ 1 ];
//    memcpy( data, & msg, 4 * ( size+2 ) );
//    return 1;
//}


//static int tcp_write_msg(int skt, int link_id, int msg_id, void *data, int len, int timeout)
//{
//    int				i;
//    int				size;
//    t_socket_msg	msg;
//    unsigned int	*tmp= (unsigned int*)&msg;

//    if ((local_flags & 1)==0) return -1;

//    size= (len+3) >> 2;
//    msg.header.bit.endian = (msg_id & __TCPIP_NO_ENDIAN_TOGGLE_id) != 0;
//    msg.header.bit.link_id = link_id;
//    msg.header.bit.msg_id = msg_id;
//    msg.header.bit.so_packet = (len+3) & ~3;
//    if (data && (len>0)) memcpy(&msg.packet[0], data, len);
//    msg.packet[size]= __END_TCPIP_PACKET_id;
//    tmp[0]= htonl(tmp[0]);
//    if ( ! msg.header.bit.endian )
//    {
//        for (i=1;i<=size;i++)
//        {
//            tmp[i]= htonl(tmp[i]);
//        }
//    }
//    tmp[size+1]= htonl(tmp[size+1]);
//    return tcp_write_data(skt, &msg, 4 * (size+2), timeout);
//}


//static int tcp_write_data(int skt, void *data, int len, int timeout)
//{
//    struct timeval  tv;

//    tv.tv_sec= timeout / 1000;
//    tv.tv_usec= (timeout % 1000) * 1000;
//    if ( setsockopt( skt, SOL_SOCKET, SO_SNDTIMEO, & tv, sizeof( tv ) ) )
//    {
//        ERR_TRACE("manager fail to set write timeout");
//        return -1;
//    }
//    if ( send( skt, data, len, 0 ) != len )
//        return -1;
//    return 1;

//}


//static int tcp_read_data(int skt, void *data, int len, int timeout)
//{
//    int size;
//    struct timeval  tv;

//    memset(&tv, 0, sizeof(tv));
//    if ( timeout > 0 )
//    {
//        tv.tv_sec = timeout / 1000;
//        tv.tv_usec = ( timeout % 1000 ) * 1000;
//    }

//    if (setsockopt( skt, SOL_SOCKET, SO_RCVTIMEO, & tv, sizeof( tv ) ) )
//    {
//        ERR_TRACE("manager fail to set read timeout");
//        return -1;
//    }

//    while ( len > 0 )
//    {
//        size= recv( skt, data, len, 0 );
//        if ( size <=0 )
//            return -1;
//        len -= size;
//        data += size;
//    }
//    return 1;

//}


//static void slot_try_connect(TSlot *slot)
//{
//    int				i;
//    t_tcp_pluggin		plug;

//    DBUG_TRACE(" %s.%s", __FUNCTION__, slot->name );
//    slot->flags.connected= 0;
//    if ((local_flags & 1)==0) return;

//    if (slot->peer_ip==0)	  return;

//    slot->skt_out= tcp_connect(slot->peer_ip, slot->peer_port, 1000);
//    if ( slot->skt_out < 0 )
//    {
//        WARN_TRACE("%s.%d %s: TCP connect \"T I M E D O U T\"",
//                   __FUNCTION__ , __LINE__ , slot->name );
//        return;
//    }

//    // local_ip siempre esta guardado como big_endian
//    // en el mensaje de red que se envia, tiene que estar tambien en big_endian
//    // pero como la capa de red le cambia el endian a todo lo que se envia
//    // aqui le cambiamos el endian, para que luego vuelva a cambiarse
//    // lo mismo se cumple para el puerto
//    plug.ip= htonl(local_ip);
//    plug.port= ntohs(local_port);

//    if ( tcp_write_msg( slot->skt_out,
//                      slot->local_id,
//                      __CHANNEL_CONNECTION_id,
//                      & plug, sizeof(plug), 3000 ) < 0 )
//    {
//        WARN_TRACE("%s.%d %s: tcp_write connect \"T I M E D O U T\"",
//                   __FUNCTION__, __LINE__ ,slot->name );
//        shutdown(slot->skt_out, 2);
//        close(slot->skt_out);
//        return;
//    }

//    for ( i = 0; i < 3; i++)
//    {
//        sleep( 1 );
//        if ( slot->flags.connected )
//        {
//            LOG_TRACE("%s: peer \"C O N N E C T E D\"", slot->name );
//            return;
//        }
//    }

//    WARN_TRACE("%s.%d %s: peer not answer", __FUNCTION__ , __LINE__ , slot->name );
//    kill_socket( slot->skt_out, 2);
//    return;
//}



//char *show_msg(char *lab, void *msg, int len)
//{
//    int	 i;
//    static char deb[1024];
//    char *pdeb= deb;
//    unsigned char *tmp = (unsigned char *)msg;

//    pdeb= deb;
//    for (i=0;i<MIN(256, len);i++)
//    {
//        if ((i&3)==0) pdeb+= sprintf(pdeb, "\n");
//        pdeb+= sprintf(pdeb, "%02x", tmp[i]);
//    }
//    pdeb+= sprintf(pdeb, "\n");
//    return deb;
//}




///*******************************************************************************
//	esta parte de codigo esta destinada a realizar
//	la retransmision automatica de paquetes
//*******************************************************************************/

//static __u32 xmit_now(void)
//{
//    struct 	timeval tv;

//    gettimeofday( & tv, NULL );
//    return( ( tv.tv_sec - retry_start) * 1000 + tv.tv_usec / 1000 );

//}

//static void retry_lock(void)
//{
//    pthread_mutex_lock( & retry_mutex );
//}

//static void retry_unlock(void)
//{
//    pthread_mutex_unlock( & retry_mutex );
//}

///*****************************************************************
//	Helper functions (estas funciones no bloquean ni desbloquean
//	el pool, deberan ser llamadas con el pool bloqueado
//*****************************************************************/
//static void retry_add_to_pool( TRetry *retry )
//{
//    retry->next= retry_pool;
//    retry_pool= retry;
//}

//static void retry_remove_from_pool( TRetry *retry )
//{
//    TRetry *tmp;

//    if( ! retry || ! retry_pool )
//        return;

//    if ( retry == retry_pool)
//    {
//        retry_pool= retry_pool->next;
//        return;
//    }

//    for( tmp = retry_pool +0; tmp->next; tmp = tmp->next )
//    {
//        if( tmp->next == retry )
//        {
//            tmp->next= tmp->next->next;
//            return;
//        }
//    }
//    return;

//}


//static void retry_destroy(TRetry *retry)
//{
//    if (!retry) return;

//    retry_remove_from_pool(retry);
//    if (retry->msg) free(retry->msg);
//    free(retry);
//    return;
//}


//static TRetry *retry_alloc(int len)
//{
//    TRetry	*retry;

//    retry= malloc(sizeof(*retry));
//    if (!retry)
//    {
//        return NULL;
//    }
//    memset(retry, 0, sizeof(*retry));

//    retry->msg = malloc( sizeof( retry->msg->header ) + len );
//    if (!retry->msg)
//    {
//        free(retry);
//        return NULL;
//    }
//    memset(retry->msg, 0, sizeof(retry->msg->header) + len);

//    retry->size= len;
//    retry->msg->header.msg_len= len;
//    retry->next_xmit= xmit_now();
//    retry_add_to_pool(retry);
//    return retry;

//}


//static TRetry *retry_realloc(TRetry *retry, int len)
//{

//    free(retry->msg);
//    retry->msg= malloc(sizeof(retry->msg->header) + len);
//    if (!retry->msg)
//    {
//        retry_remove_from_pool(retry);
//        retry_destroy(retry);
//        return NULL;
//    }
//    memset(retry->msg, 0, sizeof(retry->msg->header) + len);
//    retry->size= len;
//    retry->msg->header.msg_len= len;
//    return retry;

//}

///*******************************************************************
//	Mucho cuidado al utilizar esta funcion porque
//	al salir deja el pool bloqueado
//*******************************************************************/
//static TRetry *retry_find(char *channel, int msg_id)
//{
//    TRetry	*retry;

//    retry_lock( );
//    for( retry = retry_pool +0; retry ; retry = retry->next )
//        if( ( msg_id == retry->msg->header.msg_id ) &&
//            ( strcmp( channel, retry->channel ) == 0 ) )
//            return retry;
//    return NULL;
//}





///* Latch layer procesing -------------------------------------------------- */
//static void processEncapsulatedMessage(TSlot *slot, t_socket_msg *data )
//{
//    THandcheck	*msg;

//    msg= (THandcheck *)&data->packet[1];

//    //	LOG_TRACE( "[%s]dir=%d id=%d", __func__, msg->header.direction, msg->header.msg_id );
//    if (msg->header.direction==DIRECTION_REPLY)
//    {
//        int	msg_id= msg->header.msg_id;
//        TRetry *retry= retry_find(slot->name, msg_id);

//        // parar el latch si el stamp del msg conicide
//        // con el ultimo enviado
//        if (retry && msg->header.stamp==retry->stamp)
//        {
//            if (retry->flags.no_stop == 0)
//            {
//                retry->flags.enabled= 0;
//            }
//        }

//        retry_unlock();

//        // notificar al layer superior que se ha parado un latch
//        // debido a un ack
//        {
//            latch_activity_t	latch;
//            latch.cmd= LATCH_STOP;
//            latch.msg= retry->msg->header.msg_id;
//            slot_upload_msg(slot, __ENCAP_ACK_MSG_id, &latch, sizeof(latch));
//        }
//        return;
//    }

//    if (msg->header.direction==DIRECTION_QUERY)
//    {
//        msg->header.direction= DIRECTION_REPLY;
//        slot_write_msg(slot->name, __ENCAP_ACK_MSG_id, msg, sizeof(msg->header));

//        data->header.bit.msg_id= msg->header.msg_id;
//        data->header.bit.so_packet= msg->header.msg_len;

//        if (data->header.bit.so_packet>0)
//        {
//            memcpy(&data->packet[1], msg->data, data->header.bit.so_packet);
//        }

//        if( slot->callback )  slot->callback ( slot->name, data );
//        if( slot->_callback ) slot->_callback( slot->name, data, slot->arg );
//        sys_notifier_call( &slot->notifier, slot_gateway, data );

//    }
//}

//void retry_wakeup(void)
//{
//    retry_lock();
//    pthread_cond_signal( & retry_cond );
//    retry_unlock();
//}

//static int retry_can_send(TRetry	*retry)
//{
//    latch_activity_t	*latch;
//    t_socket_msg		msg;
//    TSlot				*slot;

//    slot = slot_find_by_name( retry->channel );
//    if ( ! slot )
//    {
//        retry->flags.enabled= 0;
//        return 1;
//    }

//    latch = ( latch_activity_t* )( msg.packet +1 );

//    msg.header.bit.msg_id= __ENCAP_ACK_MSG_id;
//    latch->cmd= LATCH_SEND;
//    latch->msg= retry->msg->header.msg_id;
//    latch->rslt= 1;

//    if( slot->callback )  slot->callback ( slot->name, & msg );
//    if( slot->_callback ) slot->_callback( slot->name, & msg, slot->arg );
//    sys_notifier_call( &slot->notifier, slot_gateway, &msg );
//    return (int)(latch->rslt);
//}


//static void retry_transmit(TRetry	*retry)
//{
//    DBGOUT(("[%s] id=%d", __func__, retry->msg->header.msg_id));
//    //	LOG_TRACE("[%s] id=%d stop=%d", __func__, retry->msg->header.msg_id, retry->flags.no_stop );

//    // si el latch esta configurado para no resetearse,
//    // enviar el mensaje tal cual
//    // de lo contrario encapsularlo
//    if (retry->flags.no_stop)
//    {
//        slot_write_msg(retry->channel, retry->msg->header.msg_id,
//                       retry->msg->data, retry->msg->header.msg_len );
//    }
//    else
//    {
//        retry->stamp= ++retry_stamp;
//        retry->msg->header.stamp= retry->stamp;
//        slot_write_msg(retry->channel,
//                       __ENCAP_ACK_MSG_id,
//                       retry->msg,
//                       sizeof(retry->msg->header) +
//                           retry->msg->header.msg_len );
//    }
//}


///* Latch controller thread ------------------------------------------------- */
//static void *retry_process(void *v)
//{
//    __u32	xmit, next_xmit;
//    TRetry	*retry;

//    LOG_TRACE("Retransmision thread enter");
//    pthread_detach( pthread_self( ) );
//    xmit= xmit_now( );
//    next_xmit= xmit + 1000;

//    retry_lock();

//    while( com_running )
//    {
//        int					blocked,count;
//        TSlot				*slot;
//        t_socket_msg		msg;
//        latch_activity_t	*latch;

//        //		LOG_TRACE("[%s:%d]", __func__, __LINE__ );
//        xmit= xmit_now();
//        next_xmit= xmit + 1000;

//        count= blocked= 0;
//        for( retry = retry_pool; retry; retry = retry->next )
//        {
//            if( ! retry->flags.enabled )
//            {
//                continue;
//            }

//            if ( retry->next_xmit > ( xmit + 100 ) )
//            {
//                next_xmit= MIN(	next_xmit, retry->next_xmit );
//                continue;
//            }

//            retry_unlock();
//            if ( !retry_can_send(retry) )
//            {
//                blocked++;
//                retry_lock();
//                continue;
//            }

//            retry->next_xmit = xmit + retry->period;
//            retry->delay = 0;

//            //			LOG_TRACE("[%s:%d]", __func__, __LINE__ );
//            retry_transmit(retry);
//            count++;

//            retry_lock();
//        }

//        if ( !blocked || !count )
//        {
//            struct timespec ts;
//            //			LOG_TRACE("[%s:%d]", __func__, __LINE__ );
//            ts.tv_sec= retry_start + next_xmit / 1000;
//            ts.tv_nsec=  (next_xmit % 1000) * 1000000;
//            if( !retry_pending )
//                pthread_cond_timedwait(&retry_cond, &retry_mutex, &ts);
//            retry_pending=0;
//        }
//    }
//    retry_unlock();
//    LOG_TRACE("Retransmision thread leave");
//    return NULL;
//}


///* File prototocol stuff ------------------------------------------------------- */
//static int fsize(FILE *fd)
//{
//    fseek(fd, 0, SEEK_END);
//    return ftell(fd);
//}


//static void file_lock(void)
//{
//    pthread_mutex_lock( & file_mutex );
//    return;
//}


//static void file_unlock(void)
//{

//    pthread_mutex_unlock( & file_mutex );
//    return;

//}


//static TFile *file_find(char *channel, int msg_id, int sender)
//{
//    TFile	*file;

//    file_lock( );
//    for(file=file_pool; file; file= file->next)
//    {
//        if ( (msg_id==file->file_id) && (sender==file->sender) && (strcmp(channel, file->channel)==0))
//        {
//            return file;
//        }
//    }

//    file= malloc(sizeof(*file));
//    if (file==NULL) return NULL;
//    memset(file, 0, sizeof(*file));
//    file->file_id= msg_id;
//    file->sender= sender;
//    strcpy(file->channel, channel);
//    file->next= file_pool;
//    file_pool= file;
//    return file;
//}



//static void slot_send_file_xmit(TFile *file)
//{
//    TChannelFile	data;

//    data.file_id= file->file_id;
//    data.pos= file->pos;
//    data.size= MIN(file->size-file->pos, 256);
//    data.eof= file->pos+data.size >= file->size;
//    data.ack= 0;
//    data.fname= 0;
//    data.retrieve= 0;
//    if (file->fname)
//    {
//        data.eof= 0;
//        data.fname= 1;
//        strcpy(data.buffer, file->filename);
//    }
//    else
//    {
//        fseek(file->fd, file->pos, SEEK_SET);
//        fread(data.buffer, data.size, 1, file->fd);
//    }
//    slot_write_latch_msg(file->channel, __SEND_FILE_id, &data, sizeof(data), 5);

//}


//static void slot_retrieve_file_xmit(TFile *file)
//{
//    TChannelFile	data;

//    memset( & data, 0, sizeof( data ));
//    data.file_id= file->file_id;
//    data.retrieve= 1;
//    data.size= 1;
//    strcpy(data.buffer, file->filename);
//    slot_write_latch_msg( file->channel, __SEND_FILE_id, & data, sizeof( data ), 5 );

//}


//static void processSendFileMessage(TSlot *slot, t_socket_msg	*data)
//{
//    TFile *file;
//    TChannelFile	*msg;
//    t_socket_msg	next;

//    msg = ( TChannelFile* )( & data->packet[ 1 ] );
//    if (msg->ack == 0)
//    {
//        // buscar el receptor
//        file= file_find( slot->name, msg->file_id, FILE_RECEIVER );

//        if (!file)
//        {
//            file_unlock();
//            return;
//        }

//        // alguien pide que le manden un archivo
//        if (msg->retrieve)
//        {
//            msg->ack= 1;
//            slot_write_msg(slot->name, __SEND_FILE_id, msg, sizeof(*msg) - sizeof(msg->buffer));

//            file_unlock();
//            slot_send_file(slot->name, msg->file_id, msg->buffer, "");
//            return;
//        }

//        if (msg->size<1)
//        {
//            file_unlock();
//            return;
//        }

//        // si este archivo fue pedido, borrar el flag
//        file->retrieve= 0;

//        if (file->fd == NULL)
//        {
//            static int	file_no = 0;

//            sprintf(file->filename, "/opt/log/F%08x.tmp", ++file_no);
//            if (msg->fname)
//                strcpy(file->realname, msg->buffer);
//            else
//                file->realname[0]= 0;

//            file->fd= fopen(file->filename, "w");
//            if (!file->fd)
//            {
//                file_unlock();
//                return;
//            }
//        }

//        file->size= fsize(file->fd);
//        if (msg->pos > file->size)
//        {
//            file_unlock();
//            return;
//        }

//        msg->ack= 1;
//        slot_write_msg(slot->name, __SEND_FILE_id, msg, sizeof(*msg) - sizeof(msg->buffer));

//        if (msg->fname)
//        {
//            file_unlock();
//            return;
//        }

//        fseek(file->fd, msg->pos, SEEK_SET);
//        fwrite(msg->buffer, msg->size, 1, file->fd);

//        if (msg->eof)
//        {
//            fclose(file->fd);
//            file->fd= NULL;

//            next= *data;
//            strcpy((char*) &next.packet[2], file->filename);

//            file->eof= 1;

//            if (file->cb)
//            {
//                ((FileCallback)(file->cb))(slot->name, file->file_id, file->filename, file->realname);
//                file_unlock();
//                return;
//            }

//            file_unlock();
//            if( slot->callback )  slot->callback ( slot->name, & next );
//            if( slot->_callback ) slot->_callback( slot->name, & next, slot->arg );
//            sys_notifier_call( &slot->notifier, slot_gateway, &next );

//            return;
//        }

//        file_unlock();
//        return;
//    }

//    slot_latch_stop(slot->name, __SEND_FILE_id);

//    // buscar el emisor
//    file= file_find(slot->name, msg->file_id, FILE_SENDER);

//    if (file && file->enabled && !file->retrieve)
//    {
//        if (msg->fname)
//        {
//            // ya se ha procesado el nombre
//            // pasar a transmitir el fichero
//            file->fname= 0;
//        }
//        else
//            if (msg->eof)
//            {
//                // ya se ha transmitido todo, cerrar
//                fclose(file->fd);
//                file->fd= NULL;
//                file->enabled= 0;
//                if (file->cb)
//                {
//                    ((FileCallback)(file->cb))(slot->name, file->file_id, file->filename, file->realname);
//                }
//            }
//            else
//            {
//                // pasar al proximo bloque
//                file->pos+= msg->size;
//            }
//    }

//    for (file= file_pool;file;file=file->next)
//        if (file->enabled && file->retrieve)
//        {
//            slot_retrieve_file_xmit(file);
//            break;
//        }
//        else
//            if (file->enabled && file->sender)
//            {
//                slot_send_file_xmit(file);
//                break;
//            }

//    file_unlock();

//}


//static void slot_gateway(sys_callback_t *cb, void *msg)
//{
//    TSlot *slot = (TSlot*) cb->priv;

//    ((void(*)(char*,void*,void*))(cb->fn))(slot->name,msg,cb->dt);
//}

//int slot_add_notifier(char *name, void *fn, void *dt)
//{
//    TSlot *slot= slot_find_by_name(name);
//    if (!slot) return -1;

//    return sys_notifier_add( &slot->notifier, slot, fn, dt );
//}

//void slot_del_notifier(char *name, void *fn, void *dt)
//{
//    TSlot *slot= slot_find_by_name(name);
//    if (!slot) return ;
//    sys_notifier_del( &slot->notifier, slot, fn, dt );
//}
