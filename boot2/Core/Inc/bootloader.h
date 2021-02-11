#ifndef __BOOTLOADER_H
#define __BOOTLOADER_H

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< includes >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//------------------------------------------------------------------------------
//<<<<<<<<<<<<<<<<<<<<<<<<<<<< Определение семейства >>>>>>>>>>>>>>>>>>>>>>>>>>>
// проверка на принадлежность чипа к семейству F10x
#if defined (STM32F10X_LD) || defined (STM32F10X_LD_VL) || defined (STM32F10X_MD) || defined (STM32F10X_MD_VL) \
	|| defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_XL) || defined (STM32F10X_CL) 
#define STM32F10X_SERIES
// проверка на принадлежность чипа к семейству F2xx
#elif	defined (STM32F2XX)
  #define STM32F2XX_SERIES
#endif

#ifdef STM32F10X_SERIES
#include "stm32f10x.h"
#elif defined(STM32F2XX_SERIES)
#include "stm32f2xx.h"
#endif
//------------------------------------------------------------------------------
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< defines >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#define bMAX(a,b)	(a)>(b)?(a):(b)
#define bMIN(a,b)	(a)>(b)?(b):(a)

#define BOOT_SYSTICKFREQ_HZ				10
#define BOOT_SYSTICKPERIOD_MS			1000/BOOT_SYSTICKFREQ_HZ	

#define DEVICE_F10XIDBASEADDR		0x1FFFF7E8
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< types >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<< function prototypes >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Wait_us(volatile uint32_t usec);
void Wait_ms(volatile uint32_t msec);


#endif
