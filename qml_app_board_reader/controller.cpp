//#define VERBOSE
//#define MODULE "mmc_channel"

///* Includes ---------------------------------------------------------- */
//#include <sys/types.h>

//#include "common/util.h"
//#include "common/network_iface.h"
//#include <common/generic_iface.h>

//#include "suinsa/communications_iface_2.h"
//#include <service_cmd/core_channel.h>
///* ------------------------------------------------------------------------ */

///* Local Functions -------------------------------------------------------- */
//static void decoder( char *slot, t_socket_msg *msg );
///* ------------------------------------------------------------------------ */
///* Local data ------------------------------------------------------------- */
//static event_dem_t  event_dem;
///* ------------------------------------------------------------- Local data */


///* Boot/Shutdown interface ------------------------------------------------ */
//int mmc_channel_boot( void )
//{
//    LOG_TRACE( "[%s:%s]Initializing-----------------------", MODULE, __func__ );
//    slot_create("core", __MMC_CORE_id, __MMC_SERVICE_id, decoder);
//    LOG_TRACE( "[%s:%s]Initialized------------------------\n", MODULE, __func__ );
//    return( 1 );
//}

//static int connected = 0;

//int mmc_channel_configure( char *name )
//{
//    char *ip;

//    if( !name || !*name )
//        return -1;

//    if( (ip = slot_get_host_ip( name )) )
//    {
//        LOG_TRACE( "[%s:%s]ip=%s port=%d", MODULE, __func__, ip, __MMC_CORE_IP_PORT );
//        slot_connect("core", ip, __MMC_CORE_IP_PORT);
//        slot_activate("core");
//        while (!connected){}
//    }
//    else
//    {
//        ERROUT(( "[%s]Host NOT found", __func__));
//        return -1;
//    }

//    return 1;
//}
///* ------------------------------------------------ Boot/Shutdown interface */



///* Download interface ----------------------------------------------------- */

///* ----------------------------------------------------- Download interface */




///* Communications decoder --------------------------------------------------*/
//static void decoder( char *slot, t_socket_msg *msg )
//{

//    switch( msg->header.bit.msg_id )
//    {

//    case __CHANNEL_ECHO_ANS_id:
//    case __ENCAP_ACK_MSG_id:
//        break;

//    case __KILL_CONNECTION_id:
//        MSGLOG(( "[%s]KILL_CONNECTION", __func__ ));
//        break;

//    case __FULL_DUPLEX_COMPLETED_id:
//        MSGLOG(( "[%s]FULL_DUPLEX_COMPLETED", __func__ ));
//        connected = 1;
//        break;
//    default:
//        break;
//    }
//}
///* ------------------------------------------------- Communications decoder */

