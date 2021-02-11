#ifndef __ETHERNET_H
#define __ETHERNET_H

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< includes >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//#include "stm32_eth.h"
#include <stdio.h>

#include "bootloader.h"
#include <stdbool.h>
#include "stm32f1xx_hal.h"
//#include "uipopt.h"

//#include "uip.h"
#include "psock.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< defines >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< types >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

typedef struct uip_tcp_state {
  struct psock p;
  char inputbuffer[UIP_CONF_BUFFER_SIZE];
} uip_tcp_appstate_t;

typedef struct uip_udp_state{
	struct psock p;
  char inputbuffer[UIP_CONF_BUFFER_SIZE];
} uip_udp_appstate_t;

/** Main packet buffer struct */
struct pbuf {
  /** next pbuf in singly linked pbuf chain */
  struct pbuf *next;

  /** pointer to the actual data in the buffer */
  void *payload;

  /**
   * total length of this buffer and all next buffers in chain
   * belonging to the same packet.
   *
   * For non-queue packet chains this is the invariant:
   * p->tot_len == p->len + (p->next? p->next->tot_len: 0)
   */
  u16_t tot_len;

  /** length of this buffer */
  u16_t len;

  /** pbuf_type as u8_t instead of enum to save space */
  u8_t /*pbuf_type*/ type;

  /** misc flags */
  u8_t flags;

  /**
   * the reference count always equals the number of pointers
   * that refer to this pbuf. This can be pointers from an application,
   * the stack itself, or pbuf->next pointers from a chain.
   */
  u16_t ref;
};

typedef enum {
  /** Includes spare room for transport layer header, e.g. UDP header.
   * Use this if you intend to pass the pbuf to functions like udp_send().
   */
  PBUF_TRANSPORT,
  /** Includes spare room for IP header.
   * Use this if you intend to pass the pbuf to functions like raw_send().
   */
  PBUF_IP,
  /** Includes spare room for link layer header (ethernet header).
   * Use this if you intend to pass the pbuf to functions like ethernet_output().
   * @see PBUF_LINK_HLEN
   */
  PBUF_LINK,
  /** Includes spare room for additional encapsulation header before ethernet
   * headers (e.g. 802.11).
   * Use this if you intend to pass the pbuf to functions like netif->linkoutput().
   * @see PBUF_LINK_ENCAPSULATION_HLEN
   */
  PBUF_RAW_TX,
  /** Use this for input packets in a netif driver when calling netif->input()
   * in the most common case - ethernet-layer netif driver. */
  PBUF_RAW
} pbuf_layer;

struct sk_buff 
{
uint8_t * data;
uint16_t len_data;
} ;
typedef enum {
  /** pbuf data is stored in RAM, used for TX mostly, struct pbuf and its payload
      are allocated in one piece of contiguous memory (so the first payload byte
      can be calculated from struct pbuf).
      pbuf_alloc() allocates PBUF_RAM pbufs as unchained pbufs (although that might
      change in future versions).
      This should be used for all OUTGOING packets (TX).*/
  PBUF_RAM,
  /** pbuf data is stored in ROM, i.e. struct pbuf and its payload are located in
      totally different memory areas. Since it points to ROM, payload does not
      have to be copied when queued for transmission. */
  PBUF_ROM,
  /** pbuf comes from the pbuf pool. Much like PBUF_ROM but payload might change
      so it has to be duplicated when queued before transmitting, depending on
      who has a 'ref' to it. */
  PBUF_REF,
  /** pbuf payload refers to RAM. This one comes from a pool and should be used
      for RX. Payload can be chained (scatter-gather RX) but like PBUF_RAM, struct
      pbuf and its payload are allocated in one piece of contiguous memory (so
      the first payload byte can be calculated from struct pbuf).
      Don't use this for TX, if the pool becomes empty e.g. because of TCP queuing,
      you are unable to receive TCP acks! */
  PBUF_POOL
} pbuf_type;

extern DMA_HandleTypeDef hdma_ETHtomem_dma1_channel1;
extern ETH_HandleTypeDef hetho;
//extern RTC_HandleTypeDef hrtc;
extern struct uip_udp_conn *udp_conn;



void uip_appcall(void);
void uip_udp_appcall(void);
#ifndef UIP_APPCALL
#define UIP_APPCALL uip_appcall
#endif /* UIP_APPCALL */
#ifndef UIP_UDP_APPCALL
#define UIP_UDP_APPCALL uip_udp_appcall
#endif /* UIP_APPCALL */


#define IP_ADDRESS0  192
#define IP_ADDRESS1  168
#define IP_ADDRESS2  0
#define IP_ADDRESS3  10

#define NETMASK_ADDRESS0  255
#define NETMASK_ADDRESS1  255
#define NETMASK_ADDRESS2  255
#define NETMASK_ADDRESS3  0

#define GATEWAY_ADDRESS0  192
#define GATEWAY_ADDRESS1  168
#define GATEWAY_ADDRESS2  0
#define GATEWAY_ADDRESS3  1

//<<<<<<<<<<<<<<<<<<<<<<<<<<<< function prototypes >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void TFTP_conn (void);
void BOOT_EthernetInit(void);
void GPIO_Configuration(void);
void ETH_Configuration(void);

void uIP_PeriodicFunc(void);

void newdata(struct uip_tcp_state *s);
void udp_newdata(struct uip_udp_state *s);
void uip_udp_appcall(void);
void ETH_SendUDPResponse(void);
static uint8_t low_level_input(ETH_HandleTypeDef *Eth_hendle);

#endif
