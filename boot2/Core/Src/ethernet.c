//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< defines >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>		



//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< includes >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "ethernet.h"
#include "uip.h"
#include "uip_arp.h"
#include <string.h>
//#include "stm32_eth.h"
#include "stdbool.h"
#include "byteswap.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"
#define ETH_RMIIMODE 1
#include "tftp.h"
#include "flash_if.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< global variables >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// флаги таймера для uip
#define BOOTETH_LISTENTFTPPORT									0069
#define BOOTETH_LISTENUDPPORT									1001								// UDP порт сервера
#define BOOTETH_LISTENTCPPORT									1000								// TCP порт сервера
#define BOOTETH_RXBUFNB      									8 									//
#define BOOTETH_TXBUFNB      									8 									//
							// 
#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

//-------------------------------------------------------------------------------
// Ethernet буферы
ETH_DMADescTypeDef  DMARxDscrTab[BOOTETH_RXBUFNB], DMATxDscrTab[BOOTETH_TXBUFNB];
//#if defined ( __ICCARM__ ) /*!< IAR Compiler */
////  #pragma data_alignment=4
////#endif
////__ALIGN_BEGIN ETH_DMADescTypeDef  DMARxDscrTab[ETH_RXBUFNB] __ALIGN_END;/* Ethernet Rx MA Descriptor */
////
////#if defined ( __ICCARM__ ) /*!< IAR Compiler */
////  #pragma data_alignment=4
////#endif
////__ALIGN_BEGIN ETH_DMADescTypeDef  DMATxDscrTab[ETH_TXBUFNB] __ALIGN_END;/* Ethernet Tx DMA Descriptor */

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN uint8_t Rx_Buff[ETH_RXBUFNB][ETH_MAX_PACKET_SIZE] __ALIGN_END; /* Ethernet Receive Buffer */

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN uint8_t Tx_Buff[ETH_TXBUFNB][ETH_MAX_PACKET_SIZE] __ALIGN_END; /* Ethernet Transmit Buffer */


//uint8_t Rx_Buff[BOOTETH_RXBUFNB][ETH_MAX_PACKET_SIZE], Tx_Buff[BOOTETH_TXBUFNB][ETH_MAX_PACKET_SIZE]; 

////
////uint8_t data[1500];
struct uip_udp_conn *udp_conn;

struct pbuf  *pbuf_out;

///RTC_HandleTypeDef hrtc;
ETH_HandleTypeDef hetho;
DMA_HandleTypeDef hdma_ETHtomem_dma1_channel1;
//-------------------------------------------------------------------------------

//<<<<<<<<<<<<<<<<<<<<<<<<<<<< function prototypes >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void TransmitPacket(void);
void TFTP_conn (void)
{
	uip_ipaddr_t ipaddr;
	//struct uip_udp_conn *nudp_conn;
        
        uip_ipaddr(ipaddr, 0, 0, 0, 0);
	udp_conn = uip_udp_new(&ipaddr, 0); 
	if(udp_conn != NULL) 
	{
		uip_udp_bind(udp_conn,  HTONS(69));
	}
}
//==============================================================================
// 	@Описание: 	Настройка ETH
//	@Аргуметры:	нет	 
//	@Результат: нет
//==============================================================================
void BOOT_EthernetInit(void)
{
	uip_ipaddr_t ipaddr;
	struct uip_eth_addr mac;
	//struct uip_udp_conn *udp_conn;

	
	ETH_Configuration();
	
	uip_init();
	uip_arp_init();

	mac.addr[0] = hetho.Init.MACAddr[0];
        mac.addr[1] = hetho.Init.MACAddr[1];
        mac.addr[2] = hetho.Init.MACAddr[2];
        mac.addr[3] = hetho.Init.MACAddr[3];
        mac.addr[4] = hetho.Init.MACAddr[4];
        mac.addr[5] = hetho.Init.MACAddr[5];
        
        
        
	uip_setethaddr(mac);

	uip_ipaddr(ipaddr, FW_data.V_IP_CONFIG[0],  FW_data.V_IP_CONFIG[1],  FW_data.V_IP_CONFIG[2],  FW_data.V_IP_CONFIG[3]);
	uip_sethostaddr(ipaddr);
        
	uip_ipaddr(ipaddr, FW_data.V_IP_MASK[0], FW_data.V_IP_MASK[1], FW_data.V_IP_MASK[2], FW_data.V_IP_MASK[3]);
	uip_setnetmask(ipaddr);
        
	uip_ipaddr(ipaddr, FW_data.V_IP_GET[0], FW_data.V_IP_GET[1], FW_data.V_IP_GET[2], FW_data.V_IP_GET[3]);
        uip_setdraddr(ipaddr);
	
        TFTP_conn();
        
}
//==============================================================================
// 	@Описание: 	Настройка ETH
//	@Аргуметры:	нет	 
//	@Результат: нет
//==============================================================================
void ETH_Configuration(void)
{

  /* Initialize Tx Descriptors list: Chain Mode */
  HAL_ETH_DMATxDescListInit(&hetho,DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);
  /* Initialize Rx Descriptors list: Chain Mode  */
  HAL_ETH_DMARxDescListInit(&hetho,DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);

  /* Enable MAC and DMA transmission and reception */
 /// ETH_Start(); 
HAL_ETH_Start(&hetho);
}


void
uip_appcall(void)
{

  struct uip_tcp_state *s = &(uip_conn->appstate);
	//-----------------
	if(uip_connected()) 
	{
		uip_len = 0;
		return;
	}

	//-----------------
	if(uip_timedout()) 
	{
		uip_abort();
	}
	if(uip_conn->lport == (uint16_t)HTONS(BOOTETH_LISTENTCPPORT))
	{
		//-----------------
		if(uip_newdata()) 
                {
                  newdata(s);
                }
	}
	//-----------------
	if(uip_rexmit()) 
	{
		
	}
	
}
//==============================================================================
//
//
//==============================================================================
void newdata(struct uip_tcp_state *s)
{
	
}
//==============================================================================
//
//
//==============================================================================
void uip_udp_appcall(void)
{
  uint16_t port_d =0; 
//  uint16_t port_p =0; 
	struct uip_udp_state *s = &(uip_udp_conn->appstate);
         port_d=uip_udp_conn->lport;
         //port_p = (uint32_t)HTONS(BOOTETH_LISTENUDPPORT);
	if(port_d == (uint32_t)HTONS(BOOTETH_LISTENUDPPORT))
	{
	//-----------------
		if(uip_newdata()) {
                  udp_newdata(s);
                }
	//-----------------
	}
       
        if( port_d == (uint16_t)HTONS(0x0045))
	{
	//-----------------
		if(uip_newdata()) {
                  udp_newdata(s);
                }
          


//////        static struct uip_udpip_hdr *hdr;
//////        hdr = (struct uip_udpip_hdr *)&uip_buf[UIP_LLH_LEN];
//////        uip_ipaddr_copy(&uip_udp_conn->ripaddr, hdr->srcipaddr);
//////        uip_udp_conn->rport = hdr->srcport;
//////  
//////        inputLen =  sizeof(inMsg));
//////        memcpy((char *)&inMsg, (char *)uip_appdata, inputLen);
//////        
//////        process_msg(&inMsg, &inputLen, &outMsg, &outputLen);
//////        
//////        memcpy((char *)uip_appdata(), (char *)&outMsg, outputLen);
////        uip_slen = outputLen;
////  
////        uip_process(UIP_UDP_SEND_CONN);

	//-----------------
	}
}
//==============================================================================
//

//==============================================================================
//
//
//==============================================================================
void uIP_PeriodicFunc(void) 
{
 uint32_t i;
 low_level_input(&hetho);
 if(uip_len != NULL)
  {
   if(BUF->type == (uint16_t)(uint16_t)HTONS(UIP_ETHTYPE_IP))
    {
     uip_arp_ipin();
     uip_input();
     if(uip_len > 0)
      {
        
       uip_arp_out();
       TransmitPacket();
      }
    }
   else if(BUF->type == (uint16_t)(uint16_t)HTONS(UIP_ETHTYPE_ARP));
    {
     uip_arp_arpin();
     if(uip_len > 0)
      {
        TransmitPacket();
      }
    }
  }
 else     if(fPassed500ms)
  {
   fPassed500ms=false;
   for(i = 0; i < UIP_CONNS; i++)
    {
      uip_periodic(i);
      if(uip_len > 0)
      {
       uip_arp_out();
       TransmitPacket();
      }
    }
#if UIP_UDP
 for(i = 0; i < UIP_UDP_CONNS; i++)
  {
   uip_udp_periodic(i);
   if(uip_len > 0)
   {
    uip_arp_out();
    TransmitPacket();
   }
  }
#endif /* UIP_UDP */
  if(fPassed10s)
   {	
    fPassed10s=false;
    uip_arp_timer();
   }
 }
}

void TransmitPacket(void)
{
 if (flag_tftp==1)
  
 {
   uip_buf[42]=0;
   uip_buf[43]=opcode_out; 
   uip_buf[44]=tftp_nblock[0]; 
   uip_buf[45]=tftp_nblock[1]; 
   flag_tftp=0;
    if (size_block<512)
          {
            tftp_nblock[0] = 0;
            tftp_nblock[1] = 0;
            size_block=512;
            opcode_out = 0;
          //  uip_udp_conns->lport =0;
////            uip_udp_conn->ripaddr[0]=srem_addr[0];
////            uip_udp_conn->ripaddr[1]=srem_addr[1];      
////            uip_udp_conn->rport=srport;
            uip_udp_remove(udp_conn);    
            TFTP_conn();
          }
   
 }

     hetho.TxDesc->Buffer1Addr = (uint32_t)uip_buf;
     HAL_ETH_TransmitFrame(&hetho,uip_len);
   
}
/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

//static uint8_t low_level_input(ETH_HandleTypeDef *Eth_hendle,uint16_t *len,uint8_t *buffer) {
static uint8_t low_level_input(ETH_HandleTypeDef *Eth_hendle) {
 //   struct sk_buff *skb;
   // int len;
 //   uint8_t *buffer;
    uint32_t i=0;
    __IO ETH_DMADescTypeDef *dmarxdesc;

   // skb = NULL;

    /* get received frame */
    if (HAL_ETH_GetReceivedFrame(Eth_hendle) != HAL_OK)
    {
     //// skb->len_data=NULL;
        return NULL;
    
    }
    

////    /* Obtain the size of the packet and put it into the "len" variable. */
////   *len = Eth_hendle->RxFrameInfos.length;
////    memcpy(buffer,(uint8_t*) Eth_hendle->RxFrameInfos.buffer,Eth_hendle->RxFrameInfos.length);//*len);
  
    memcpy(uip_buf,(uint8_t*) Eth_hendle->RxFrameInfos.buffer,Eth_hendle->RxFrameInfos.length);//*len);
   uip_len = Eth_hendle->RxFrameInfos.length;
      /* Release descriptors to DMA */
      dmarxdesc = Eth_hendle->RxFrameInfos.FSRxDesc;

      /* Set Own bit in Rx descriptors: gives the buffers back to DMA */
      for (i=0; i< Eth_hendle->RxFrameInfos.SegCount; i++)
      {
        dmarxdesc->Status |= ETH_DMARXDESC_OWN;
        dmarxdesc = (ETH_DMADescTypeDef *)(dmarxdesc->Buffer2NextDescAddr);
      }

      /* Clear Segment_Count */
      Eth_hendle->RxFrameInfos.SegCount =0;


      /* When Rx Buffer unavailable flag is set: clear it and resume reception */
      if ((Eth_hendle->Instance->DMASR & ETH_DMASR_RBUS) != (uint32_t)RESET)
      {
        /* Clear RBUS ETHERNET DMA flag */
          Eth_hendle->Instance->DMASR = ETH_DMASR_RBUS;
        /* Resume DMA reception */
          Eth_hendle->Instance->DMARPDR = 0;
      }
    return 1;
}
