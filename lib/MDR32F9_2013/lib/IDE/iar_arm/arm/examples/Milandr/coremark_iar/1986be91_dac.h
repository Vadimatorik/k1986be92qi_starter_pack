#ifndef __1986BE91_DAC_H
#define __1986BE91_DAC_H

#include "cm3_macro.h"

typedef struct {
  unsigned Cfg_M_REF0                           : 1;
  unsigned Cfg_M_REF1                           : 1;
  unsigned Cfg_ON_DAC0                          : 1;
  unsigned Cfg_ON_DAC1                          : 1;
  unsigned Cfg_SYNC_A                           : 1;
  unsigned __dummy0                             : 27;
} _dac_cfg;

typedef volatile _dac_cfg _io_dac_cfg;

#define offs_DAC_CFG_Cfg_M_REF0                 0
#define offs_DAC_CFG_Cfg_M_REF1                 1
#define offs_DAC_CFG_Cfg_ON_DAC0                2
#define offs_DAC_CFG_Cfg_ON_DAC1                3
#define offs_DAC_CFG_Cfg_SYNC_A                 4

#define size_DAC_CFG_Cfg_M_REF0                 1
#define size_DAC_CFG_Cfg_M_REF1                 1
#define size_DAC_CFG_Cfg_ON_DAC0                1
#define size_DAC_CFG_Cfg_ON_DAC1                1
#define size_DAC_CFG_Cfg_SYNC_A                 1

#define mask_DAC_CFG_Cfg_M_REF0                 ((unsigned long)0x00000001)
#define mask_DAC_CFG_Cfg_M_REF1                 ((unsigned long)0x00000002)
#define mask_DAC_CFG_Cfg_ON_DAC0                ((unsigned long)0x00000004)
#define mask_DAC_CFG_Cfg_ON_DAC1                ((unsigned long)0x00000008)
#define mask_DAC_CFG_Cfg_SYNC_A                 ((unsigned long)0x00000010)


typedef struct {
  unsigned DAC0DATA                             : 12;
  unsigned __dummy0                             : 4;
  unsigned DAC1DATA                             : 12;
  unsigned __dummy1                             : 4;
} _dac1_data;

typedef volatile _dac1_data _io_dac1_data;

#define offs_DAC1_DATA_DAC0DATA                 0
#define offs_DAC1_DATA_DAC1DATA                 16

#define size_DAC1_DATA_DAC0DATA                 12
#define size_DAC1_DATA_DAC1DATA                 12

#define mask_DAC1_DATA_DAC0DATA                 ((unsigned long)0x00000FFF)
#define mask_DAC1_DATA_DAC1DATA                 ((unsigned long)0x0FFF0000)


typedef struct {
  unsigned DAC1DATA                             : 12;
  unsigned __dummy0                             : 4;
  unsigned DAC0DATA                             : 12;
  unsigned __dummy1                             : 4;
} _dac2_data;

typedef volatile _dac2_data _io_dac2_data;

#define offs_DAC2_DATA_DAC1DATA                 0
#define offs_DAC2_DATA_DAC0DATA                 16

#define size_DAC2_DATA_DAC1DATA                 12
#define size_DAC2_DATA_DAC0DATA                 12

#define mask_DAC2_DATA_DAC1DATA                 ((unsigned long)0x00000FFF)
#define mask_DAC2_DATA_DAC0DATA                 ((unsigned long)0x0FFF0000)


typedef struct {
	__io_reg CFG;
	__io_reg DAC1_DATA;
	__io_reg DAC2_DATA;
} _dac;

#endif /* __1986BE91_DAC_H */
