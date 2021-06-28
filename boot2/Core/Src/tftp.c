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
#include "tftp.h"
#include "flash_if.h"
uint8_t ETH_TransmitBuffer[256];
extern uint16_t uip_slen;
 uint8_t tftp_nblock[2];
 uint16_t size_block=512;
 uint16_t srem_addr[1];
 uint16_t srport;
//
//==============================================================================
void udp_newdata(struct uip_udp_state *s)
{
	
	struct uip_udpip_hdr *hdr;
	uint8_t *pBuffer;
	uint32_t BytesLeft=bMIN(UIP_CONF_BUFFER_SIZE,uip_datalen());
	
        hdr = (struct uip_udpip_hdr *)&uip_buf[UIP_LLH_LEN];
        srem_addr[0]=uip_udp_conn->ripaddr[0];
        srem_addr[1]=uip_udp_conn->ripaddr[1];      
        srport = uip_udp_conn->rport;
        
        uip_ipaddr_copy(&uip_udp_conn->ripaddr, hdr->srcipaddr);
        uip_udp_conn->rport = hdr->srcport;
        
       
	memcpy(s->inputbuffer,uip_appdata,BytesLeft);
	pBuffer=(uint8_t*)&s->inputbuffer;
        if ((pBuffer[1]==3)||(pBuffer[1]==5))
        {
         tftp_nblock[0]=pBuffer[2];
         tftp_nblock[1]=pBuffer[3];
         if (tftp_nblock[0]==1)
         {
          tftp_nblock[0]=1;
         
         }
         size_block = ((uint16_t)(hdr->len[1]|(hdr->len[0]<<8)) -32);
        }
    
        opcode_out=TFTP_ASK + frame_in_to_flash(pBuffer,tftp_nblock,uip_len);
	ETH_SendUDPResponse();


}
//==============================================================================
//
//
//==============================================================================
void ETH_SendUDPResponse(void)
{
	uint8_t *pBuffer=ETH_TransmitBuffer;
	uint32_t Len;
        uint8_t out_data[512];
        out_data[0]=tftp_nblock[0];
        out_data[1]=tftp_nblock[1];
        flag_tftp=1;
        memcpy(ETH_TransmitBuffer,out_data,3);
        pBuffer=(uint8_t*)((uint32_t)ETH_TransmitBuffer+7);
	Len=(uint32_t)pBuffer-(uint32_t)ETH_TransmitBuffer;	
	memcpy(uip_appdata, ETH_TransmitBuffer, Len /*> UIP_BUFSIZE? UIP_BUFSIZE: Len*/);
	uip_slen = Len;

}

