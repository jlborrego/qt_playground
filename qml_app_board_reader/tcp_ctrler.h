/***************************************************************************
 *   Copyright (C) 2007 by Suinsa Medical Systems S.A.   *
 *   artaza@suinsa.com   *
 *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 ***************************************************************************/

#ifndef __tcp_ctrler_h__
#define __tcp_ctrler_h__

#ifdef __cplusplus
extern  "C"
{
#endif

#define SWAP32(v) \
(((v&0xff)<<24)|((v&0xff00)<<8)|((v&0xff0000)>>8)|((v&0xff000000)>>24))
#define SWAP16(v) \
    (((v&0xff)<<8)|((v&0xff00)>>8))

#include <asm/byteorder.h>
#if defined(__LITTLE_ENDIAN_BITFIELD)
//#warning "Compiling on a little endian machine"

#define LE32(x)  (x)
#define BE32(x)  SWAP32(x)
#define LE16(x)  (x)
#define BE16(x)  SWAP16(x)

#elif defined (__BIG_ENDIAN_BITFIELD)
//#warning "Compiling on a big endian machine"

#define LE32(x)  SWAP32(x)
#define BE32(x)  (x)
#define LE16(x)  SWAP16(x)
#define BE16(x)  (x)

#else
#error	"Please fix <asm/byteorder.h>"
#endif

/**
        Cuantos slots podemos crear
    ****************************************************/
#define POOL_SIZE 4


#define __u32 unsigned int
#define __u16 unsigned short
#define __u8 unsigned char

#define SLOT_BIGENDIAN          0x0001
#define SLOT_READY              0x0002

#define SLOT_AUTO_CONNECT       0x0001

#define FILE_SENDER	  1
#define FILE_RECEIVER 0

    /*!
        Inicializa el controlador
        \param  ip Direcci�n IP a la que se enlazar� el controlador para
                    aceptar conexiones
        \param  port Puerto TCP a la que se enlazar� el controlador
                        para aceptar conexiones
        \param  flags Reservado, debe ser 0
        \return 1=ok, 0=error
    */
    int     slot_init(char *ip, __u16 port, __u32 flags);
void	slot_shutdown(void);

int     slot_get_local_ip(char *ip);

/*!
        Crea un canal de comunicaciones con una maquina remota
        \param  name Nombre que se le dar� al canal
        \param  peer_id Identificador de la maquina remota
        \param  local_id Nuestro identificador frente a la maquina remota
        \param  callback Funcion a la que se llamara cada vez que se reciba un mensaje
        \return 1=ok, 0=error
        \sa	slot_connect() slot_activate() slot_deactivate()
    */
int     slot_create(char *name, int peer_id, int local_id, void *callback);
int     _slot_create(char *name, int peer_id, int local_id, void *callback, void *arg );
/*!
        Activa un canal para su uso.
        \param  name Nombre del canal a activar.
        \return 1=ok, 0=error
        \sa	slot_create() slot_connect() slot_deactivate()

        Cuando se crea un canal con slot_create(), el mismo est� desactivado y no se
        podr� utilizar hasta que se active llamando a esta funci�n
    */
int     slot_activate(char *name);

/*!
        Permite desactivar un canal en runtime sin necesidad de destruirlo
        \param  name Nombre del canal a desactivar.
        \return 1=ok, 0=error
        \sa	slot_create() slot_connect() slot_activate()

        Cuando se crea un canal con slot_create(), el mismo est� desactivado y no se
        podr� utilizar hasta que se active llamando a esta funci�n
    */
int     slot_deactivate(char *name);

/*!
        Esta funcion marca el canal	como master.
        Un canal master que se encuentre activo estar� intentando conectarse
        con la maquina remota hasta que lo consiga o hasta que lo desactiven
        \param  name Nombre del canal a definir como master.
        \return 1=ok, 0=error
        \sa	slot_create() slot_activate() slot_deactivate()

        Cuando se crea un canal con slot_create(), el mismo est� desactivado y no se
        podr� utilizar hasta que se active llamando a esta funci�n
    */
int     slot_connect(char *name, char *ip, __u16 port);

int 	slot_write_msg(char *name, int msg_id, void *data, int len);
char 	*slot_get_host_ip(char *name);
int     slot_is_connected(char *name);


/****************************************************************************
        Interface para solicitar el envio de files desde el canal
        y para colocar un callback que se llame cuando se recibe
        un archivo desde el canal
        Esto es usado para hacer backup/restore
    ****************************************************************************/
int	slot_file_setup(char *channel, int file_id, int action, void *cb);
int	slot_retrieve_file(char *channel, int file_id, char *peer_name,
                       void *cb, void *dt);
int	slot_retrieve_stop(char *channel, int file_id);
int	slot_send_stop(char *channel, int file_id);
int	slot_send_file(char *channel, int file_id, char *file_name, char *target_name);


/*  periodic functions */
#define	LATCH_NO_STOP	1
#define LATCH_SEND	1
#define LATCH_STOP	2
typedef struct
{
    int		cmd;
    int		msg;
    int		rslt;
}
latch_activity_t;

void slot_latch_config(char *channel, int msg, int flags);
int	slot_write_latch_msg(char *channel, int msg, void *data, int len, int segs);
void slot_latch_stop( char *channel, int msg);

/* connection protocol */
typedef struct t_tcp_pluggin
{
    __u32  ip;
    __u32  port;
}
t_tcp_pluggin;
typedef t_tcp_pluggin tcp_plugin_t;
typedef tcp_plugin_t plugin_t;

typedef union t_socket_header{
#ifdef __BIG_ENDIAN_BITFIELD
    struct
    {
        __u16 endian    :1;
        __u16 so_packet :15;
        __u8  msg_id    :8;
        __u8  link_id   :8; /* lsb */
    } bit;
#else
    struct
    {
        __u8  link_id   :8; /* lsb */
        __u8  msg_id    :8;
        __u16 so_packet :15;
        __u16 endian	:1;
    }
    bit;
#endif
    __u32 all;
}t_socket_header;
typedef t_socket_header socket_header_t;

typedef struct t_socket_msg
{
    t_socket_header header;
    __u32 packet[ 1024 ]; 	// 4096 bytes de datos
    int so_packet;			// deprecated
}
t_socket_msg;
typedef t_socket_msg socket_msg_t;



enum {
    __CHANNEL_CONNECTION_id = 1,
    __FULL_DUPLEX_COMPLETED_id,
    __CHANNEL_ECHO_REQ_id,
    __CHANNEL_ECHO_ANS_id,

    __KILL_CONNECTION_id,
    __ENCAP_ACK_MSG_id,
    __SEND_FILE_id,

    // los primeros 16 mensajes pertenecen a la capa de conexion
    // cualquier mensaje de alto nivel debe empezar de 0x16 hacia atras
};


#define __END_TCPIP_PACKET_id 0xdeadbeef
#define __TCPIP_NO_ENDIAN_TOGGLE_id 0x4000

int slot_add_notifier(char *slot, void *fn, void *dt);
void slot_del_notifier(char *slot, void *fn, void *dt);



void retry_wakeup(void);


#ifdef __cplusplus

}
#endif

#endif

