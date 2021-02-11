#ifndef _BYTESWAP_H
#define _BYTESWAP_H


#define bswap_16(x) (((x)>>8)|((x)<<8))&0xffff
//#define bswap_16(x)	(unsigned short)(__rev(x)>>16)

#define bswap_32(x) (bswap_16((x)&0xffff)<<16) | (bswap_16(((x)>>16)&0xffff))
//#define bswap_32(x) (unsigned int)(__rev(x))

//#define bswap_64(x) (((unsigned long long)bswap_32((x)&0xffffffffull))<<32) | (bswap_32((x)>>32))

#define htonl(x)		bswap_32(x)
#define htons(x)		bswap_16(x)
#define ntohl(x)		bswap_32(x)
#define ntohs(x)		bswap_16(x)

#endif
