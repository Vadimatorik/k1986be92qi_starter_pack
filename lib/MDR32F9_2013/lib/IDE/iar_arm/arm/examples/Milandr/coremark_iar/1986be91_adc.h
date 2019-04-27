#ifndef __1986BE91_ADC_H
#define __1986BE91_ADC_H

#include "cm3_macro.h"

typedef struct {
  unsigned Cfg_REG_ADON                         : 1;
  unsigned Cfg_REG_GO                           : 1;
  unsigned Cfg_REG_CLKS                         : 1;
  unsigned Cfg_REG_SAMPLE                       : 1;
  unsigned Cfg_REG_CHS                          : 5;
  unsigned Cfg_REG_CHCH                         : 1;
  unsigned Cfg_REG_RNGC                         : 1;
  unsigned Cfg_M_REF                            : 1;
  unsigned Cfg_REG_DIVCLK                       : 4;
  unsigned Cfg_Sync_Conver                      : 1;
  unsigned TS_EN                                : 1;
  unsigned TS_BUF_EN                            : 1;
  unsigned SEL_TS                               : 1;
  unsigned SEL_VREF                             : 1;
  unsigned TR                                   : 4;
  unsigned Delay_Go                             : 3;
  unsigned Delay_ADC                            : 4;
} _adc1_cfg;

typedef volatile _adc1_cfg _io_adc1_cfg;

#define offs_ADC1_CFG_Cfg_REG_ADON              0
#define offs_ADC1_CFG_Cfg_REG_GO                1
#define offs_ADC1_CFG_Cfg_REG_CLKS              2
#define offs_ADC1_CFG_Cfg_REG_SAMPLE            3
#define offs_ADC1_CFG_Cfg_REG_CHS               4
#define offs_ADC1_CFG_Cfg_REG_CHCH              9
#define offs_ADC1_CFG_Cfg_REG_RNGC              10
#define offs_ADC1_CFG_Cfg_M_REF                 11
#define offs_ADC1_CFG_Cfg_REG_DIVCLK            12
#define offs_ADC1_CFG_Cfg_Sync_Conver           16
#define offs_ADC1_CFG_TS_EN                     17
#define offs_ADC1_CFG_TS_BUF_EN                 18
#define offs_ADC1_CFG_SEL_TS                    19
#define offs_ADC1_CFG_SEL_VREF                  20
#define offs_ADC1_CFG_TR                        21
#define offs_ADC1_CFG_Delay_Go                  25
#define offs_ADC1_CFG_Delay_ADC                 28

#define size_ADC1_CFG_Cfg_REG_ADON              1
#define size_ADC1_CFG_Cfg_REG_GO                1
#define size_ADC1_CFG_Cfg_REG_CLKS              1
#define size_ADC1_CFG_Cfg_REG_SAMPLE            1
#define size_ADC1_CFG_Cfg_REG_CHS               5
#define size_ADC1_CFG_Cfg_REG_CHCH              1
#define size_ADC1_CFG_Cfg_REG_RNGC              1
#define size_ADC1_CFG_Cfg_M_REF                 1
#define size_ADC1_CFG_Cfg_REG_DIVCLK            4
#define size_ADC1_CFG_Cfg_Sync_Conver           1
#define size_ADC1_CFG_TS_EN                     1
#define size_ADC1_CFG_TS_BUF_EN                 1
#define size_ADC1_CFG_SEL_TS                    1
#define size_ADC1_CFG_SEL_VREF                  1
#define size_ADC1_CFG_TR                        4
#define size_ADC1_CFG_Delay_Go                  3
#define size_ADC1_CFG_Delay_ADC                 4

#define mask_ADC1_CFG_Cfg_REG_ADON              ((unsigned long)0x00000001)
#define mask_ADC1_CFG_Cfg_REG_GO                ((unsigned long)0x00000002)
#define mask_ADC1_CFG_Cfg_REG_CLKS              ((unsigned long)0x00000004)
#define mask_ADC1_CFG_Cfg_REG_SAMPLE            ((unsigned long)0x00000008)
#define mask_ADC1_CFG_Cfg_REG_CHS               ((unsigned long)0x000001F0)
#define mask_ADC1_CFG_Cfg_REG_CHCH              ((unsigned long)0x00000200)
#define mask_ADC1_CFG_Cfg_REG_RNGC              ((unsigned long)0x00000400)
#define mask_ADC1_CFG_Cfg_M_REF                 ((unsigned long)0x00000800)
#define mask_ADC1_CFG_Cfg_REG_DIVCLK            ((unsigned long)0x0000F000)
#define mask_ADC1_CFG_Cfg_Sync_Conver           ((unsigned long)0x00010000)
#define mask_ADC1_CFG_TS_EN                     ((unsigned long)0x00020000)
#define mask_ADC1_CFG_TS_BUF_EN                 ((unsigned long)0x00040000)
#define mask_ADC1_CFG_SEL_TS                    ((unsigned long)0x00080000)
#define mask_ADC1_CFG_SEL_VREF                  ((unsigned long)0x00100000)
#define mask_ADC1_CFG_TR                        ((unsigned long)0x01E00000)
#define mask_ADC1_CFG_Delay_Go                  ((unsigned long)0x0E000000)
#define mask_ADC1_CFG_Delay_ADC                 ((unsigned long)0xF0000000)


typedef struct {
  unsigned Cfg_REG_ADON                         : 1;
  unsigned Cfg_REG_GO                           : 1;
  unsigned Cfg_REG_CLKS                         : 1;
  unsigned Cfg_REG_SAMPLE                       : 1;
  unsigned Cfg_REG_CHS                          : 5;
  unsigned Cfg_REG_CHCH                         : 1;
  unsigned Cfg_REG_RNGC                         : 1;
  unsigned Cfg_M_REF                            : 1;
  unsigned Cfg_REG_DIVCLK                       : 4;
  unsigned __dummy0                             : 1;
  unsigned ADC1_OP                              : 1;
  unsigned ADC2_OP                              : 1;
  unsigned __dummy1                             : 6;
  unsigned Delay_Go                             : 3;
  unsigned __dummy2                             : 4;
} _adc2_cfg;

typedef volatile _adc2_cfg _io_adc2_cfg;

#define offs_ADC2_CFG_Cfg_REG_ADON              0
#define offs_ADC2_CFG_Cfg_REG_GO                1
#define offs_ADC2_CFG_Cfg_REG_CLKS              2
#define offs_ADC2_CFG_Cfg_REG_SAMPLE            3
#define offs_ADC2_CFG_Cfg_REG_CHS               4
#define offs_ADC2_CFG_Cfg_REG_CHCH              9
#define offs_ADC2_CFG_Cfg_REG_RNGC              10
#define offs_ADC2_CFG_Cfg_M_REF                 11
#define offs_ADC2_CFG_Cfg_REG_DIVCLK            12
#define offs_ADC2_CFG_ADC1_OP                   17
#define offs_ADC2_CFG_ADC2_OP                   18
#define offs_ADC2_CFG_Delay_Go                  25

#define size_ADC2_CFG_Cfg_REG_ADON              1
#define size_ADC2_CFG_Cfg_REG_GO                1
#define size_ADC2_CFG_Cfg_REG_CLKS              1
#define size_ADC2_CFG_Cfg_REG_SAMPLE            1
#define size_ADC2_CFG_Cfg_REG_CHS               5
#define size_ADC2_CFG_Cfg_REG_CHCH              1
#define size_ADC2_CFG_Cfg_REG_RNGC              1
#define size_ADC2_CFG_Cfg_M_REF                 1
#define size_ADC2_CFG_Cfg_REG_DIVCLK            4
#define size_ADC2_CFG_ADC1_OP                   1
#define size_ADC2_CFG_ADC2_OP                   1
#define size_ADC2_CFG_Delay_Go                  3

#define mask_ADC2_CFG_Cfg_REG_ADON              ((unsigned long)0x00000001)
#define mask_ADC2_CFG_Cfg_REG_GO                ((unsigned long)0x00000002)
#define mask_ADC2_CFG_Cfg_REG_CLKS              ((unsigned long)0x00000004)
#define mask_ADC2_CFG_Cfg_REG_SAMPLE            ((unsigned long)0x00000008)
#define mask_ADC2_CFG_Cfg_REG_CHS               ((unsigned long)0x000001F0)
#define mask_ADC2_CFG_Cfg_REG_CHCH              ((unsigned long)0x00000200)
#define mask_ADC2_CFG_Cfg_REG_RNGC              ((unsigned long)0x00000400)
#define mask_ADC2_CFG_Cfg_M_REF                 ((unsigned long)0x00000800)
#define mask_ADC2_CFG_Cfg_REG_DIVCLK            ((unsigned long)0x0000F000)
#define mask_ADC2_CFG_ADC1_OP                   ((unsigned long)0x00020000)
#define mask_ADC2_CFG_ADC2_OP                   ((unsigned long)0x00040000)
#define mask_ADC2_CFG_Delay_Go                  ((unsigned long)0x0E000000)


typedef struct {
  unsigned RESULT                               : 12;
  unsigned __dummy0                             : 4;
  unsigned CHANNEL                              : 12;
  unsigned __dummy1                             : 4;
} _adc1_result;

typedef volatile _adc1_result _io_adc1_result;

#define offs_ADC1_RESULT                        0
#define offs_ADC1_RESULT_CHANNEL                16

#define size_ADC1_RESULT                        12
#define size_ADC1_RESULT_CHANNEL                12

#define mask_ADC1_RESULT                        ((unsigned long)0x00000FFF)
#define mask_ADC1_RESULT_CHANNEL                ((unsigned long)0x0FFF0000)


typedef struct {
  unsigned RESULT                               : 12;
  unsigned __dummy0                             : 4;
  unsigned CHANNEL                              : 12;
  unsigned __dummy1                             : 4;
} _adc2_result;

typedef volatile _adc2_result _io_adc2_result;

#define offs_ADC2_RESULT                        0
#define offs_ADC2_RESULT_CHANNEL                16

#define size_ADC2_RESULT                        12
#define size_ADC2_RESULT_CHANNEL                12

#define mask_ADC2_RESULT                        ((unsigned long)0x00000FFF)
#define mask_ADC2_RESULT_CHANNEL                ((unsigned long)0x0FFF0000)


typedef struct {
  unsigned Flg_REG_OVERWRITE                    : 1;
  unsigned Flg_REG_AWOIFEN                      : 1;
  unsigned Flg_REG_EOCIF                        : 1;
  unsigned AWOIF_IE                             : 1;
  unsigned ECOIF_IE                             : 1;
  unsigned __dummy0                             : 27;
} _adc1_status;

typedef volatile _adc1_status _io_adc1_status;

#define offs_ADC1_STATUS_Flg_REG_OVERWRITE      0
#define offs_ADC1_STATUS_Flg_REG_AWOIFEN        1
#define offs_ADC1_STATUS_Flg_REG_EOCIF          2
#define offs_ADC1_STATUS_AWOIF_IE               3
#define offs_ADC1_STATUS_ECOIF_IE               4

#define size_ADC1_STATUS_Flg_REG_OVERWRITE      1
#define size_ADC1_STATUS_Flg_REG_AWOIFEN        1
#define size_ADC1_STATUS_Flg_REG_EOCIF          1
#define size_ADC1_STATUS_AWOIF_IE               1
#define size_ADC1_STATUS_ECOIF_IE               1

#define mask_ADC1_STATUS_Flg_REG_OVERWRITE      ((unsigned long)0x00000001)
#define mask_ADC1_STATUS_Flg_REG_AWOIFEN        ((unsigned long)0x00000002)
#define mask_ADC1_STATUS_Flg_REG_EOCIF          ((unsigned long)0x00000004)
#define mask_ADC1_STATUS_AWOIF_IE               ((unsigned long)0x00000008)
#define mask_ADC1_STATUS_ECOIF_IE               ((unsigned long)0x00000010)


typedef struct {
  unsigned Flg_REG_OVERWRITE                    : 1;
  unsigned Flg_REG_AWOIFEN                      : 1;
  unsigned Flg_REG_EOCIF                        : 1;
  unsigned AWOIF_IE                             : 1;
  unsigned ECOIF_IE                             : 1;
  unsigned __dummy0                             : 27;
} _adc2_status;

typedef volatile _adc2_status _io_adc2_status;

#define offs_ADC2_STATUS_Flg_REG_OVERWRITE      0
#define offs_ADC2_STATUS_Flg_REG_AWOIFEN        1
#define offs_ADC2_STATUS_Flg_REG_EOCIF          2
#define offs_ADC2_STATUS_AWOIF_IE               3
#define offs_ADC2_STATUS_ECOIF_IE               4

#define size_ADC2_STATUS_Flg_REG_OVERWRITE      1
#define size_ADC2_STATUS_Flg_REG_AWOIFEN        1
#define size_ADC2_STATUS_Flg_REG_EOCIF          1
#define size_ADC2_STATUS_AWOIF_IE               1
#define size_ADC2_STATUS_ECOIF_IE               1

#define mask_ADC2_STATUS_Flg_REG_OVERWRITE      ((unsigned long)0x00000001)
#define mask_ADC2_STATUS_Flg_REG_AWOIFEN        ((unsigned long)0x00000002)
#define mask_ADC2_STATUS_Flg_REG_EOCIF          ((unsigned long)0x00000004)
#define mask_ADC2_STATUS_AWOIF_IE               ((unsigned long)0x00000008)
#define mask_ADC2_STATUS_ECOIF_IE               ((unsigned long)0x00000010)


typedef struct {
	__io_reg ADC1_CFG;
	__io_reg ADC2_CFG;
	__io_reg ADC1_H_LEVEL;
	__io_reg ADC2_H_LEVEL;
	__io_reg ADC1_L_LEVEL;
	__io_reg ADC2_L_LEVEL;
	__io_reg ADC1_RESULT;
	__io_reg ADC2_RESULT;
	__io_reg ADC1_STATUS;
	__io_reg ADC2_STATUS;
	__io_reg ADC1_CHSEL;
	__io_reg ADC2_CHSEL;
} _adc;

#endif /* __1986BE91_ADC_H */
