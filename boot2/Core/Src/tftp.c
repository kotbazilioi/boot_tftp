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
//static const uint8_t tcp_startnewmessage[]="newmsg";                        // ?????? ?????? ?????? ?????????
uint8_t tftp_nblock[2];
 uint16_t size_block=512;
 uint16_t srem_addr[1];
 uint16_t srport;
//
//==============================================================================
void udp_newdata(struct uip_udp_state *s)
{
	
//	struct uip_udp_conn *udp_connection;
	struct uip_udpip_hdr *hdr;
	uint8_t *pBuffer;
	uint32_t BytesLeft=bMIN(UIP_CONF_BUFFER_SIZE,uip_datalen());
	
        hdr = (struct uip_udpip_hdr *)&uip_buf[UIP_LLH_LEN];
        srem_addr[0]=uip_udp_conn->ripaddr[0];
        srem_addr[1]=uip_udp_conn->ripaddr[1];      
        srport = uip_udp_conn->rport;
        
        uip_ipaddr_copy(&uip_udp_conn->ripaddr, hdr->srcipaddr);
        uip_udp_conn->rport = hdr->srcport;
        
//////	hdr = (struct uip_udpip_hdr *)&uip_buf[UIP_LLH_LEN];
//////	udp_connection= uip_udp_new(&hdr->srcipaddr, hdr->srcport);
//////	if(udp_connection==NULL)
//////		return;
        
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
      // __disable_irq();
       
        opcode_out=TFTP_ASK + frame_in_to_flash(pBuffer,tftp_nblock,uip_len);
    //    __enable_irq();
	//if(memcmp(pBuffer,tcp_startnewmessage,sizeof(tcp_startnewmessage))==0)
	//  {
	
		ETH_SendUDPResponse();
	//  }
	//uip_udp_remove(0);
      //  uip_udp_conns->lport=0;

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
        
       // opcode_out=TFTP_ASK;
        flag_tftp=1;
        memcpy(ETH_TransmitBuffer,out_data,3);
	//memcpy(ETH_TransmitBuffer,tcp_startnewmessage,sizeof(tcp_startnewmessage));
        
	//pBuffer=(uint8_t*)((uint32_t)ETH_TransmitBuffer+3);
        pBuffer=(uint8_t*)((uint32_t)ETH_TransmitBuffer+7);
	Len=(uint32_t)pBuffer-(uint32_t)ETH_TransmitBuffer;
	
	memcpy(uip_appdata, ETH_TransmitBuffer, Len /*> UIP_BUFSIZE? UIP_BUFSIZE: Len*/);
	uip_slen = Len;
      //  uip_process(UIP_UDP_SEND_CONN);
	//uip_slen =0;
}

////void processTFTP (TFTPDpkt * tp)
////{
////	register int nbtry;
////	TFTPDpkt tftpd_pkt;
////
////	if (!tftp_req)
////		return;
////
////	if (tftp_req->port == 0)
////		tftp_req->port = tp->udphdr.src_port;
////
////	if (tp->udphdr.iphdr.src_ip == tftp_req->server
////		&& tp->udphdr.src_port == tftp_req->port) {
////		if (tp->opcode == 3) {
////			if (tp->num == tftp_req->bloc || tp->num == tftp_req->bloc - 1) {
////				memset (&tftpd_pkt, 0, sizeof tftpd_pkt);
////				tftpd_pkt.opcode = 4;
////				tftpd_pkt.num = tp->num;
////				for (nbtry = 4; nbtry; --nbtry) {
////					if (sendUDP
////						((UDPpkt *) & tftpd_pkt, 4, tftp_req->server,
////						 TFTP_LOCAL_PORT, tp->udphdr.src_port) == 0)
////						break;
////					usleep (1000);
////				}
////				if (nbtry == 0)
////					printf ("TFTP: error sending ACK\n");
////				if (tp->num == tftp_req->bloc) {
////					register unsigned short len = tp->udphdr.length - 12;
////
////					if (len) {
////						memcpy ((void *) (tftp_req->addr + tftp_req->bcnt),
////								tp->data, len);
////						tftp_req->bcnt += len;
////					}
////					++tftp_req->bloc;
////					putchar ("-\\|/"[tftp_req->bloc % 4]);
////					putchar ('\b');
////					if (tp->udphdr.length < 524) {
////						tftp_req->sts = 1;
////						printf ("TFTP: downloaded %d bytes\n",
////								tftp_req->bcnt);
////					}
////				}
////			}
////		}
////		else if (tp->opcode == 5) {
////			printf ("TFTP error %d: %s\n", tp->num, tp->data);
////			tftp_req->sts = -tp->num;
////		}
////	}
////}
////
////int sendTFTPRequest (void)
////{
////	TFTPRpkt tftpr_pkt;
////	unsigned short len;
////
////	if (tftp_req) {
////		memset (&tftpr_pkt, 0, sizeof tftpr_pkt);
////		tftpr_pkt.opcode = 1;
////		strcpy (tftpr_pkt.data, tftp_req->file);
////		len = strlen (tftp_req->file) + 1;
////		strcpy (tftpr_pkt.data + len, "octet");
////		len += 8;				/* opcode size + octet\0 size */
////
////		return sendUDP ((UDPpkt *) & tftpr_pkt, len, tftp_req->server,
////						TFTP_LOCAL_PORT, TFTP_SRV_PORT);
////	}
////	return 1;
////}
