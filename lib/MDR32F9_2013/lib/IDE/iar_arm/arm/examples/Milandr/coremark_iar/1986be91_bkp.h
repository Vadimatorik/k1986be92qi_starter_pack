#ifndef __1986BE91_BKP_H
#define __1986BE91_BKP_H

#include "cm3_macro.h"

typedef struct {
  unsigned LOW                                  : 3;
  unsigned SelectRI                             : 3;
  unsigned JTAGA                                : 1;
  unsigned JTAGB                                : 1;
  unsigned Trim                                 : 3;
  unsigned FPOR                                 : 1;
  unsigned __dummy0                             : 20;
} _bkp_reg_0e;

typedef volatile _bkp_reg_0e _io_bkp_reg_0e;

#define offs_BKP_REG_0E_LOW                     0
#define offs_BKP_REG_0E_SelectRI                3
#define offs_BKP_REG_0E_JTAGA                   6
#define offs_BKP_REG_0E_JTAGB                   7
#define offs_BKP_REG_0E_Trim                    8
#define offs_BKP_REG_0E_FPOR                    11

#define size_BKP_REG_0E_LOW                     3
#define size_BKP_REG_0E_SelectRI                3
#define size_BKP_REG_0E_JTAGA                   1
#define size_BKP_REG_0E_JTAGB                   1
#define size_BKP_REG_0E_Trim                    3
#define size_BKP_REG_0E_FPOR                    1

#define mask_BKP_REG_0E_LOW                     ((unsigned long)0x00000007)
#define mask_BKP_REG_0E_SelectRI                ((unsigned long)0x00000038)
#define mask_BKP_REG_0E_JTAGA                   ((unsigned long)0x00000040)
#define mask_BKP_REG_0E_JTAGB                   ((unsigned long)0x00000080)
#define mask_BKP_REG_0E_Trim                    ((unsigned long)0x00000700)
#define mask_BKP_REG_0E_FPOR                    ((unsigned long)0x00000800)


typedef struct {
  unsigned LSE_ON                               : 1;
  unsigned LSE_BYP                              : 1;
  unsigned RTC_SEL                              : 2;
  unsigned RTC_EN                               : 1;
  unsigned CAL                                  : 8;
  unsigned LSE_RDY                              : 1;
  unsigned __dummy0                             : 1;
  unsigned LSI_ON                               : 1;
  unsigned LSI_TRIM                             : 5;
  unsigned LSI_RDY                              : 1;
  unsigned HSI_ON                               : 1;
  unsigned HSI_RDY                              : 1;
  unsigned HSI_TRIM                             : 6;
  unsigned STANDBY                              : 1;
  unsigned RTC_RESET                            : 1;
} _bkp_reg_0f;

typedef volatile _bkp_reg_0f _io_bkp_reg_0f;

#define offs_BKP_REG_0F_LSE_ON                  0
#define offs_BKP_REG_0F_LSE_BYP                 1
#define offs_BKP_REG_0F_RTC_SEL                 2
#define offs_BKP_REG_0F_RTC_EN                  4
#define offs_BKP_REG_0F_CAL                     5
#define offs_BKP_REG_0F_LSE_RDY                 13
#define offs_BKP_REG_0F_LSI_ON                  15
#define offs_BKP_REG_0F_LSI_TRIM                16
#define offs_BKP_REG_0F_LSI_RDY                 21
#define offs_BKP_REG_0F_HSI_ON                  22
#define offs_BKP_REG_0F_HSI_RDY                 23
#define offs_BKP_REG_0F_HSI_TRIM                24
#define offs_BKP_REG_0F_STANDBY                 30
#define offs_BKP_REG_0F_RTC_RESET               31

#define size_BKP_REG_0F_LSE_ON                  1
#define size_BKP_REG_0F_LSE_BYP                 1
#define size_BKP_REG_0F_RTC_SEL                 2
#define size_BKP_REG_0F_RTC_EN                  1
#define size_BKP_REG_0F_CAL                     8
#define size_BKP_REG_0F_LSE_RDY                 1
#define size_BKP_REG_0F_LSI_ON                  1
#define size_BKP_REG_0F_LSI_TRIM                5
#define size_BKP_REG_0F_LSI_RDY                 1
#define size_BKP_REG_0F_HSI_ON                  1
#define size_BKP_REG_0F_HSI_RDY                 1
#define size_BKP_REG_0F_HSI_TRIM                6
#define size_BKP_REG_0F_STANDBY                 1
#define size_BKP_REG_0F_RTC_RESET               1

#define mask_BKP_REG_0F_LSE_ON                  ((unsigned long)0x00000001)
#define mask_BKP_REG_0F_LSE_BYP                 ((unsigned long)0x00000002)
#define mask_BKP_REG_0F_RTC_SEL                 ((unsigned long)0x0000000C)
#define mask_BKP_REG_0F_RTC_EN                  ((unsigned long)0x00000010)
#define mask_BKP_REG_0F_CAL                     ((unsigned long)0x00001FE0)
#define mask_BKP_REG_0F_LSE_RDY                 ((unsigned long)0x00002000)
#define mask_BKP_REG_0F_LSI_ON                  ((unsigned long)0x00008000)
#define mask_BKP_REG_0F_LSI_TRIM                ((unsigned long)0x001F0000)
#define mask_BKP_REG_0F_LSI_RDY                 ((unsigned long)0x00200000)
#define mask_BKP_REG_0F_HSI_ON                  ((unsigned long)0x00400000)
#define mask_BKP_REG_0F_HSI_RDY                 ((unsigned long)0x00800000)
#define mask_BKP_REG_0F_HSI_TRIM                ((unsigned long)0x3F000000)
#define mask_BKP_REG_0F_STANDBY                 ((unsigned long)0x40000000)
#define mask_BKP_REG_0F_RTC_RESET               ((unsigned long)0x80000000)


typedef struct {
  unsigned OWF                                  : 1;
  unsigned SECF                                 : 1;
  unsigned ALRF                                 : 1;
  unsigned OWF_IE                               : 1;
  unsigned SECF_IE                              : 1;
  unsigned ALRF_IE                              : 1;
  unsigned WEC                                  : 1;
  unsigned __dummy0                             : 25;
} _bkp_rtc_cs;

typedef volatile _bkp_rtc_cs _io_bkp_rtc_cs;

#define offs_BKP_RTC_CS_OWF                     0
#define offs_BKP_RTC_CS_SECF                    1
#define offs_BKP_RTC_CS_ALRF                    2
#define offs_BKP_RTC_CS_OWF_IE                  3
#define offs_BKP_RTC_CS_SECF_IE                 4
#define offs_BKP_RTC_CS_ALRF_IE                 5
#define offs_BKP_RTC_CS_WEC                     6

#define size_BKP_RTC_CS_OWF                     1
#define size_BKP_RTC_CS_SECF                    1
#define size_BKP_RTC_CS_ALRF                    1
#define size_BKP_RTC_CS_OWF_IE                  1
#define size_BKP_RTC_CS_SECF_IE                 1
#define size_BKP_RTC_CS_ALRF_IE                 1
#define size_BKP_RTC_CS_WEC                     1

#define mask_BKP_RTC_CS_OWF                     ((unsigned long)0x00000001)
#define mask_BKP_RTC_CS_SECF                    ((unsigned long)0x00000002)
#define mask_BKP_RTC_CS_ALRF                    ((unsigned long)0x00000004)
#define mask_BKP_RTC_CS_OWF_IE                  ((unsigned long)0x00000008)
#define mask_BKP_RTC_CS_SECF_IE                 ((unsigned long)0x00000010)
#define mask_BKP_RTC_CS_ALRF_IE                 ((unsigned long)0x00000020)
#define mask_BKP_RTC_CS_WEC                     ((unsigned long)0x00000040)


typedef struct {
	__io_reg REG_00;
	__io_reg __dummy0[13];
	__io_reg REG_0E;
	__io_reg REG_0F;
	__io_reg RTC_CNT;
	__io_reg RTC_DIV;
	__io_reg RTC_PRL;
	__io_reg RTC_ALRM;
	__io_reg RTC_CS;
} _bkp;

#endif /* __1986BE91_BKP_H */
