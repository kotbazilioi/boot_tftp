/**
  ******************************************************************************
  * @file    IAP_Main/Inc/flash_if.h 
  * @author  MCD Application Team
  * @brief   This file provides all the headers of the flash_if functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_IF_H
#define __FLASH_IF_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Base address of the Flash sectors */


////
////#define A_START_BOOT 0x08000000
////#define A_BOOT_FW 0x08000004
////#define A_CRC_APP 0x8004000
////#define A_CRC_DATA_BOOT 0x8004002
//////*******************************
////#define A_IP_ADRESS 0x8004004
////#define A_IP_MASK 0x8004008
////#define A_GET_ADRESS 0x800400c
////#define A_FW_VER 0x8004010
////#define A_FW_LEN 0x8004014
////#define A_BOOT_VER 0x8004018
////#define A_CRC_DATA 0x800401C
////#define A_DHCP 0x800401E
//////*******************************
////#define A_LOGIN 0x800401f //21
////#define A_PASSWORD 0x800402f //31
////#define A_DNS 0x800403f  //41
////#define A_WEB_PORT 0x8004043 //45
////#define A_SNMP 0x8004045 //47
////#define A_HTTP_IP 0x8004049
////#define A_ON_MESS 0x800404B
////#define A_OFF_MESS 0x800406B
////#define A_FLAG_EN_MAN 0x800408B
////#define A_FLAG_EN_WEB 0x800408C
////#define A_FLAG_EN_RASP 0x800408D
////#define A_FLAG_EN_WATCHMAN 0x800408E
////#define A_EMAIL_ERR 0x800408F
////#define A_D1_TIME 0x80040AF
////#define A_D2_TIME 0x80040B3
////#define A_D3_TIME 0x80040B7
////#define A_D4_TIME 0x80040BB
////#define A_D5_TIME 0x80040BF
////#define A_D6_TIME 0x80040C3
////#define A_D7_TIME 0x80040C7
////#define A_D8_TIME 0x80040CB
////#define A_D9_TIME 0x80040CF
////#define A_D10_TIME 0x80040D3
////#define A_RD1_TIME 0x80040D7
////#define A_RD2_TIME 0x80040DB
////#define A_RD3_TIME 0x80040DF
////#define A_IP_PING_TIME 0x80040E3
////#define A_TIME_SEND 0x80040E5
////#define A_TIME_READ 0x80040E7
////#define A_N_RERID 0x80040E9
////#define A_TIME_RESET 0x80040EB
////#define A_DELAY_PING 0x80040ED
////#define A_SOST_RESET 0x80040EF
////#define A_N_PING 0x80040F0
////#define A_IP_NTP1 0x80040F1
////#define A_IP_NTP2 0x80040F5
////#define A_PORT_NTP 0x80040F9
////#define A_NAME_SNMP 0x80040FB
////#define A_PORT_SNMP 0x800411B
////#define A_LOGIN_SNMP 0x800411D
////#define A_PASSWORD_SNMP 0x800412B
////#define A_RESV 0x800413B
////#define A_CRC_LOG 0x8004800
////#define A_LOG 0x8004804
////#define A_START_APP 0x8005000
////#define A_FW_APP 0x8005004
////#define A_HTTP_DUMP 0x8005000
////#define A_END_APP     ((uint32_t)0x08020000) 

#define A_START_BOOT 0x08000000
#define A_BOOT_FW 0x08000004
#define A_CRC_APP 0x8005000
#define A_CRC_DATA_BOOT 0x8005002
//*******************************
#define A_IP_ADRESS 0x8005004
#define A_IP_MASK 0x8005008
#define A_GET_ADRESS 0x800500c
#define A_FW_VER 0x8005010
#define A_FW_LEN 0x8005014
#define A_BOOT_VER 0x8005018
#define A_CRC_DATA 0x800501C
#define A_DHCP 0x800501E
//*******************************
#define A_LOGIN A_DHCP+2
#define A_PASSWORD A_LOGIN+16 
#define A_DNS A_PASSWORD+16
#define A_WEB_PORT A_DNS+4 
#define A_SNMP A_WEB_PORT+4 
#define A_HTTP_IP A_SNMP+4
#define A_ON_MESS A_HTTP_IP+2
#define A_OFF_MESS A_ON_MESS+32
#define A_FLAG_EN_MAN A_OFF_MESS+32
#define A_FLAG_EN_WEB A_FLAG_EN_MAN+1
#define A_FLAG_EN_RASP A_FLAG_EN_WEB+1
#define A_FLAG_EN_WATCHMAN A_FLAG_EN_RASP+1
#define A_EMAIL_ERR A_FLAG_EN_WATCHMAN+1
#define A_D_TIME A_EMAIL_ERR+32

#define A_RD1_TIME A_D_TIME+40

#define A_IP_PING A_RD1_TIME+12
#define A_TIME_SEND A_IP_PING+4
#define A_TIME_READ A_TIME_SEND+2
#define A_N_RERID A_TIME_READ+2
#define A_TIME_RESET A_N_RERID+2
#define A_DELAY_PING A_TIME_RESET+2
#define A_SOST_RESET A_DELAY_PING+2
#define A_N_PING A_SOST_RESET+1
#define A_IP_NTP1 A_N_PING+2
#define A_IP_NTP2 A_IP_NTP1+4
#define A_PORT_NTP A_IP_NTP2+4
#define A_NAME_SMTP A_PORT_NTP+2
#define A_PORT_SNMP A_NAME_SMTP+32
#define A_LOGIN_SMTP A_PORT_SNMP+2
#define A_PASSWORD_SMTP A_LOGIN_SMTP+16
#define A_GEOM_NAME A_PASSWORD_SMTP+16  
#define A_ID_MAC A_GEOM_NAME+86        
#define A_NAME_DEV A_ID_MAC+8
#define A_CALL_DATA A_NAME_DEV+86
#define A_IP_SNMP A_CALL_DATA+86
#define A_NTP_CIRCL A_IP_SNMP+4 
#define A_TYPE_OUT A_NTP_CIRCL+1
#define A_RESV V_TYPE_OUT+1
    
    
    
    
    
#define A_CRC_LOG 0x8005800
#define A_LOG A_CRC_LOG+2
#define A_START_APP 0x8007000
#define A_FW_APP 0x8007004
#define A_HTTP_DUMP 0x8007000
#define A_END_APP     ((uint32_t)0x08040000) 

#define BOOT_VER_FW 0X00010001

//typedef struct {

//} cons_type_def_t;
//cons_type_def_t data_const;



//////#define ADDR_FLASH_PAGE_8     ((uint32_t)0x08004000) /* Base @ of Page 8, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_9     ((uint32_t)0x08004800) /* Base @ of Page 9, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_10    ((uint32_t)0x08005000) /* Base @ of Page 10, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_11    ((uint32_t)0x08005800) /* Base @ of Page 11, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_12    ((uint32_t)0x08006000) /* Base @ of Page 12, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_13    ((uint32_t)0x08006800) /* Base @ of Page 13, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_14    ((uint32_t)0x08007000) /* Base @ of Page 14, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_15    ((uint32_t)0x08007800) /* Base @ of Page 15, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_16    ((uint32_t)0x08008000) /* Base @ of Page 16, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_17    ((uint32_t)0x08008800) /* Base @ of Page 17, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_18    ((uint32_t)0x08009000) /* Base @ of Page 18, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_19    ((uint32_t)0x08009800) /* Base @ of Page 19, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_20    ((uint32_t)0x0800A000) /* Base @ of Page 20, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_21    ((uint32_t)0x0800A800) /* Base @ of Page 21, 2 Kbytes  */
//////#define ADDR_FLASH_PAGE_22    ((uint32_t)0x0800B000) /* Base @ of Page 22, 2 Kbytes  */
//////#define ADDR_FLASH_PAGE_23    ((uint32_t)0x0800B800) /* Base @ of Page 23, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_24    ((uint32_t)0x0800C000) /* Base @ of Page 24, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_25    ((uint32_t)0x0800C800) /* Base @ of Page 25, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_26    ((uint32_t)0x0800D000) /* Base @ of Page 26, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_27    ((uint32_t)0x0800D800) /* Base @ of Page 27, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_28    ((uint32_t)0x0800E000) /* Base @ of Page 28, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_29    ((uint32_t)0x0800E800) /* Base @ of Page 29, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_30    ((uint32_t)0x0800F000) /* Base @ of Page 30, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_31    ((uint32_t)0x0800F800) /* Base @ of Page 31, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_32    ((uint32_t)0x08010000) /* Base @ of Page 32, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_33    ((uint32_t)0x08010800) /* Base @ of Page 33, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_34    ((uint32_t)0x08011000) /* Base @ of Page 34, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_35    ((uint32_t)0x08011800) /* Base @ of Page 35, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_36    ((uint32_t)0x08012000) /* Base @ of Page 36, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_37    ((uint32_t)0x08012800) /* Base @ of Page 37, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_38    ((uint32_t)0x08013000) /* Base @ of Page 38, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_39    ((uint32_t)0x08013800) /* Base @ of Page 39, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_40    ((uint32_t)0x08014000) /* Base @ of Page 40, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_41    ((uint32_t)0x08014800) /* Base @ of Page 41, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_42    ((uint32_t)0x08015000) /* Base @ of Page 42, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_43    ((uint32_t)0x08015800) /* Base @ of Page 43, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_44    ((uint32_t)0x08016000) /* Base @ of Page 44, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_45    ((uint32_t)0x08016800) /* Base @ of Page 45, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_46    ((uint32_t)0x08017000) /* Base @ of Page 46, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_47    ((uint32_t)0x08017800) /* Base @ of Page 47, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_48    ((uint32_t)0x08018000) /* Base @ of Page 48, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_49    ((uint32_t)0x08018800) /* Base @ of Page 49, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_50    ((uint32_t)0x08019000) /* Base @ of Page 50, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_51    ((uint32_t)0x08019800) /* Base @ of Page 51, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_52    ((uint32_t)0x0801A000) /* Base @ of Page 52, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_53    ((uint32_t)0x0801A800) /* Base @ of Page 53, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_54    ((uint32_t)0x0801B000) /* Base @ of Page 54, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_55    ((uint32_t)0x0801B800) /* Base @ of Page 55, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_56    ((uint32_t)0x0801C000) /* Base @ of Page 56, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_57    ((uint32_t)0x0801C800) /* Base @ of Page 57, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_58    ((uint32_t)0x0801D000) /* Base @ of Page 58, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_59    ((uint32_t)0x0801D800) /* Base @ of Page 59, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_60    ((uint32_t)0x0801E000) /* Base @ of Page 60, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_61    ((uint32_t)0x0801E800) /* Base @ of Page 61, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_62    ((uint32_t)0x0801F000) /* Base @ of Page 62, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_63    ((uint32_t)0x0801F800) /* Base @ of Page 63, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_64    ((uint32_t)0x08020000) /* Base @ of Page 64, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_65    ((uint32_t)0x08020800) /* Base @ of Page 65, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_66    ((uint32_t)0x08021000) /* Base @ of Page 66, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_67    ((uint32_t)0x08021800) /* Base @ of Page 67, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_68    ((uint32_t)0x08022000) /* Base @ of Page 68, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_69    ((uint32_t)0x08022800) /* Base @ of Page 69, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_70    ((uint32_t)0x08023000) /* Base @ of Page 70, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_71    ((uint32_t)0x08023800) /* Base @ of Page 71, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_72    ((uint32_t)0x08024000) /* Base @ of Page 72, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_73    ((uint32_t)0x08024800) /* Base @ of Page 73, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_74    ((uint32_t)0x08025000) /* Base @ of Page 74, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_75    ((uint32_t)0x08025800) /* Base @ of Page 75, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_76    ((uint32_t)0x08026000) /* Base @ of Page 76, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_77    ((uint32_t)0x08026800) /* Base @ of Page 77, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_78    ((uint32_t)0x08027000) /* Base @ of Page 78, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_79    ((uint32_t)0x08027800) /* Base @ of Page 79, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_80    ((uint32_t)0x08028000) /* Base @ of Page 80, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_81    ((uint32_t)0x08028800) /* Base @ of Page 81, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_82    ((uint32_t)0x08029000) /* Base @ of Page 82, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_83    ((uint32_t)0x08029800) /* Base @ of Page 83, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_84    ((uint32_t)0x0802A000) /* Base @ of Page 84, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_85    ((uint32_t)0x0802A800) /* Base @ of Page 85, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_86    ((uint32_t)0x0802B000) /* Base @ of Page 86, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_87    ((uint32_t)0x0802B800) /* Base @ of Page 87, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_88    ((uint32_t)0x0802C000) /* Base @ of Page 88, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_89    ((uint32_t)0x0802C800) /* Base @ of Page 89, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_90    ((uint32_t)0x0802D000) /* Base @ of Page 90, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_91    ((uint32_t)0x0802D800) /* Base @ of Page 91, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_92    ((uint32_t)0x0802E000) /* Base @ of Page 92, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_93    ((uint32_t)0x0802E800) /* Base @ of Page 93, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_94    ((uint32_t)0x0802F000) /* Base @ of Page 94, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_95    ((uint32_t)0x0802F800) /* Base @ of Page 95, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_96    ((uint32_t)0x08030000) /* Base @ of Page 96, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_97    ((uint32_t)0x08030800) /* Base @ of Page 97, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_98    ((uint32_t)0x08031000) /* Base @ of Page 98, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_99    ((uint32_t)0x08031800) /* Base @ of Page 99, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_100   ((uint32_t)0x08032000) /* Base @ of Page 100, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_101   ((uint32_t)0x08032800) /* Base @ of Page 101, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_102   ((uint32_t)0x08033000) /* Base @ of Page 102, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_103   ((uint32_t)0x08033800) /* Base @ of Page 103, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_104   ((uint32_t)0x08034000) /* Base @ of Page 104, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_105   ((uint32_t)0x08034800) /* Base @ of Page 105, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_106   ((uint32_t)0x08035000) /* Base @ of Page 106, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_107   ((uint32_t)0x08035800) /* Base @ of Page 107, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_108   ((uint32_t)0x08036000) /* Base @ of Page 108, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_109   ((uint32_t)0x08036800) /* Base @ of Page 109, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_110   ((uint32_t)0x08037000) /* Base @ of Page 110, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_111   ((uint32_t)0x08037800) /* Base @ of Page 111, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_112   ((uint32_t)0x08038000) /* Base @ of Page 112, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_113   ((uint32_t)0x08038800) /* Base @ of Page 113, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_114   ((uint32_t)0x08039000) /* Base @ of Page 114, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_115   ((uint32_t)0x08039800) /* Base @ of Page 115, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_116   ((uint32_t)0x0803A000) /* Base @ of Page 116, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_117   ((uint32_t)0x0803A800) /* Base @ of Page 117, 2 Kbytes  */
//////#define ADDR_FLASH_PAGE_118   ((uint32_t)0x0803B000) /* Base @ of Page 118, 2 Kbytes  */
//////#define ADDR_FLASH_PAGE_119   ((uint32_t)0x0803B800) /* Base @ of Page 119, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_120   ((uint32_t)0x0803C000) /* Base @ of Page 120, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_121   ((uint32_t)0x0803C800) /* Base @ of Page 121, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_122   ((uint32_t)0x0803D000) /* Base @ of Page 122, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_123   ((uint32_t)0x0803D800) /* Base @ of Page 123, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_124   ((uint32_t)0x0803E000) /* Base @ of Page 124, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_125   ((uint32_t)0x0803E800) /* Base @ of Page 125, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_126   ((uint32_t)0x0803F000) /* Base @ of Page 126, 2 Kbytes */
//////#define ADDR_FLASH_PAGE_127   ((uint32_t)0x0803F800) /* Base @ of Page 127, 2 Kbytes */

/* Error code */
enum 
{
  FLASHIF_OK = 0,
  FLASHIF_ERASEKO,
  FLASHIF_WRITINGCTRL_ERROR,
  FLASHIF_WRITING_ERROR,
  FLASHIF_PROTECTION_ERRROR
};

/* protection type */  
enum{
  FLASHIF_PROTECTION_NONE         = 0,
  FLASHIF_PROTECTION_PCROPENABLED = 0x1,
  FLASHIF_PROTECTION_WRPENABLED   = 0x2,
  FLASHIF_PROTECTION_RDPENABLED   = 0x4,
};

/* protection update */
enum {
	FLASHIF_WRP_ENABLE,
	FLASHIF_WRP_DISABLE
};

/* Define the address from where user application will be loaded.
   Note: this area is reserved for the IAP code                  */
#define FLASH_PAGE_STEP         FLASH_PAGE_SIZE           /* Size of page : 2 Kbytes */
#define APPLICATION_ADDRESS     A_START_APP      /* Start user code address: ADDR_FLASH_PAGE_8 */

/* Notable Flash addresses */
#define USER_FLASH_BANK1_START_ADDRESS  0x08000000
#define USER_FLASH_BANK2_START_ADDRESS  0x08080000
#define USER_FLASH_BANK1_END_ADDRESS    FLASH_BANK1_END
#define USER_FLASH_BANK2_END_ADDRESS    FLASH_BANK2_END

/* Define the user application size */
#define USER_FLASH_SIZE               ((uint32_t)0x00003000) /* Small default template application */

/* Define bitmap representing user flash area that could be write protected (check restricted to pages 8-39). */
#define FLASH_PAGE_TO_BE_PROTECTED (OB_WRP_PAGES8TO9 | OB_WRP_PAGES10TO11 | OB_WRP_PAGES12TO13 | OB_WRP_PAGES14TO15 | \
                                    OB_WRP_PAGES16TO17 | OB_WRP_PAGES18TO19 | OB_WRP_PAGES20TO21 | OB_WRP_PAGES22TO23 | \
                                    OB_WRP_PAGES24TO25 | OB_WRP_PAGES26TO27 | OB_WRP_PAGES28TO29 | OB_WRP_PAGES30TO31 | \
                                    OB_WRP_PAGES32TO33 | OB_WRP_PAGES34TO35 | OB_WRP_PAGES36TO37 | OB_WRP_PAGES38TO39  )  


/* Exported macro ------------------------------------------------------------*/
/* ABSoulute value */
#define ABS_RETURN(x,y)               (((x) < (y)) ? (y) : (x))

/* Get the number of sectors from where the user program will be loaded */
#define FLASH_SECTOR_NUMBER           ((uint32_t)(ABS_RETURN(APPLICATION_ADDRESS,FLASH_START_BANK1))>>12)

/* Compute the mask to test if the Flash memory, where the user program will be
  loaded, is write protected */
#define FLASH_PROTECTED_SECTORS       (~(uint32_t)((1 << FLASH_SECTOR_NUMBER) - 1))
/* Exported functions ------------------------------------------------------- */
void FLASH_If_Init(void);
uint32_t FLASH_If_Erase(uint32_t StartSector);
uint32_t FLASH_If_GetWriteProtectionStatus(void);
uint32_t FLASH_If_Write(uint32_t destination, uint32_t *p_source, uint32_t length);

uint32_t FLASH_If_WriteProtectionConfig(uint32_t protectionstate);
extern uint8_t flag_app_start;
extern   uint32_t timer_to_app;
extern uint32_t timer_start_app;
extern uint32_t flag_start_wait;
extern uint8_t step_boot ;
extern uint32_t ct_led_timer;
//extern CRC_HandleTypeDef crc_hcrc;
typedef struct 
{
uint16_t nblock_in;
uint32_t nblock_inflash;
uint16_t nframe16;
uint32_t size_file;
uint16_t temp_block_flash;
uint16_t temp_block;
uint16_t index;
uint8_t data_to_block[2048];
}file_data_t;

typedef struct 
{
uint8_t dicr ;//0
uint8_t type_event;//1
uint8_t reple_hours;//2
uint8_t reple_minuts;//3
uint8_t reple_seconds;//4
uint8_t day;//5
uint8_t dweek;//6
uint8_t month;//7
uint16_t year;//9

}log_reple_t;

typedef struct 
{
 uint16_t CRC16;
 log_reple_t log_reple[200];
} logs_t;

typedef struct 
{
 uint8_t on_swich_m;
 uint8_t on_swich_h;
 uint8_t off_swich_m;
 uint8_t off_swich_h;
} day_swich_elem;
typedef struct 
{
 uint8_t day;
 uint8_t month;
 uint8_t year;
} data_swich_elem;
typedef struct 
{
 day_swich_elem time_data[6];
 uint8_t set_up_day;
} V_D_TIME_type;

typedef struct 
{
 data_swich_elem data[10];
 uint8_t restore_day[10];
} V_RD_DATA_type;

typedef struct 
{ 
uint16_t  V_CRC_APP  ;
////#define A_CRC_APP 0x8004000
uint16_t  V_CRC_BOOT  ;
////#define A_CRC_DATA_BOOT 0x8004002
//////*******************************
uint8_t V_IP_CONFIG[4] ;
////#define A_IP_ADRESS 0x8004004
uint8_t V_IP_MASK[4] ;
////#define A_IP_MASK 0x8004008
uint8_t V_IP_GET[4] ;
////#define A_GET_ADRESS 0x800400c
uint8_t V_FW1_VER[4] ;
////#define A_FW_VER 0x8004010
uint32_t V_FW1_LEN ;
////#define A_FW_LEN 0x8004014
uint32_t V_BOOT_VER ;
////#define A_BOOT_VER 0x8004018


//*******************************
uint16_t V_CRC_DATA;
////#define A_CRC_DATA 0x800401C

uint8_t V_DHCP;
////#define A_DHCP 0x800401C
char V_LOGIN[16];
////#define A_LOGIN 0x8004021
char V_PASSWORD[16];
////#define A_PASSWORD 0x8004031
uint8_t V_IP_DNS[4] ;
////#define A_DNS 0x8004041
uint16_t V_WEB_PORT;
////#define A_WEB_PORT 0x8004045
uint16_t V_SNMP;
////#define A_SNMP 0x8004047
uint16_t V_HTTP_IP; 
////#define A_HTTP_IP 0x8004049
char V_ON_MESS[32];
////#define A_ON_MESS 0x800404B
char V_OFF_MESS[32];
////#define A_OFF_MESS 0x800406B
uint8_t V_FLAG_EN_MAN;
////#define A_FLAG_EN_MAN 0x800408B
uint8_t V_FLAG_EN_WEB;
////#define A_FLAG_EN_WEB 0x800408C
uint8_t V_FLAG_EN_RASP;
////#define A_FLAG_EN_RASP 0x800408D
uint8_t V_FLAG_EN_WATCHMAN;
////#define A_FLAG_EN_WATCHMAN 0x800408E
uint8_t V_EMAIL_ERR[32];
////#define A_EMAIL_ERR 0x800408F
V_D_TIME_type V_D_TIME[10]; //260

V_RD_DATA_type V_RD_DATA; //78

uint16_t V_IP_PING_TIME;
////#define A_IP_PING_TIME 0x80040E3
uint16_t V_TIME_SEND;
////#define A_TIME_SEND 0x80040E5
uint16_t V_TIME_READ;
////#define A_TIME_READ 0x80040E7
uint16_t V_N_RERID;
////#define A_N_RERID 0x80040E9
uint16_t V_TIME_RESET;
////#define A_TIME_RESET 0x80040EB
uint16_t V_DELAY_PING;
////#define A_DELAY_PING 0x80040ED
uint8_t V_SOST_RESET;
////#define A_SOST_RESET 0x80040EF
uint8_t V_N_PING;
////#define A_N_PING 0x80040F0
uint8_t V_IP_NTP1[4];
////#define A_IP_NTP1 0x80040F1
uint8_t V_IP_NTP2[4];
////#define A_IP_NTP2 0x80040F5
uint16_t V_PORT_NTP;
////#define A_PORT_NTP 0x80040F9
char V_NAME_SMTP[32];
////#define A_NAME_SNMP 0x80040FB
uint16_t V_PORT_SNMP;
////#define A_PORT_SNMP 0x800411B
char V_LOGIN_SMTP[32];
////#define A_LOGIN_SNMP 0x800411D
char V_PASSWORD_SMTP[32];
////#define A_PASSWORD_SNMP 0x800412B
char V_GEOM_NAME[86];
uint8_t V_ID_MAC[8];
char V_Name_dev[86];
char V_CALL_DATA[86];
uint8_t V_IP_SNMP[4];
signed char V_NTP_CIRCL;
uint8_t V_TYPE_OUT;


//new
uint8_t V_TYPE_LOGIC;
uint8_t V_EN_WATCHDOG;
uint8_t V_EN_WATCHDOG_CN_A;
uint8_t V_EN_WATCHDOG_CN_B;
uint8_t V_EN_WATCHDOG_CN_C;
uint8_t V_IP_WDT_ADDR_CN_A[4];
uint8_t V_IP_WDT_ADDR_CN_B[4];
uint8_t V_IP_WDT_ADDR_CN_C[4];
uint16_t V_CT_RES_ALLSTART;
uint16_t V_T_SEND_PING;
uint16_t V_TIME_RESEND_PING;
uint16_t V_MAX_REPID_PING;
uint16_t V_TIME_RESET_PULSE;
uint16_t V_PAUSE_RESET_TO_REPID;
uint16_t V_MAX_RESEND_PACET_RESET;
uint8_t V_SOST_ERR_RASP;
uint8_t V_IP_SYSL[4];
uint8_t V_FLAG_EN_EMAIL;
uint8_t V_FLAG_DEF_EMAIL;

uint16_t V_FLAG_EMAIL_PORT;
char V_EMAIL_ADDR[32];
char V_EMAIL_FROM[32];
char V_EMAIL_TO[32];
char V_EMAIL_CC1[32];
char V_EMAIL_CC2[32];
char V_EMAIL_CC3[32];


uint8_t V_resv[1167];

////#define A_RESV 0x800413B
logs_t V_logs_struct;
//uint16_t V_CRC_LOG;
////#define A_CRC_LOG 0x8004800
//char V_LOG[50][40]; 
////#define A_LOG 0x8004804
////#define A_START_APP 0x8005000
////#define A_FW_APP 0x8005004
////#define A_HTTP_DUMP 0x8005000
////#define A_END_APP     ((uint32_t)0x08020000) 
}FW_data_t;


extern file_data_t data_file;
extern FW_data_t FW_data;
extern uint16_t *idBase0;
extern uint16_t *idBase1;
extern uint32_t *idBase2 ;
extern uint32_t *idBase3 ;
#endif  /* __FLASH_IF_H */
typedef  void (*pFunction)(void);
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
uint8_t frame_in_to_flash(uint8_t* data, uint8_t* nframe, uint16_t len_frame);
void jamp_to_app (void);
void load_def_data (void);
uint8_t load_struct_flash_data (void);
uint8_t save_data_blok (uint8_t N_sector,uint32_t* struct_to);
void Save_CRC_APP (void);
uint8_t Comp_CRC_APP(void);