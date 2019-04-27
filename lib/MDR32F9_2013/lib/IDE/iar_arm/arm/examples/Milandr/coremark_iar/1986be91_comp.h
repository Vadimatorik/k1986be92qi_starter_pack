#ifndef __1986BE91_COMP_H
#define __1986BE91_COMP_H

#include "cm3_macro.h"

typedef struct {
  unsigned ON                                   : 1;
  unsigned CVRR                                 : 1;
  unsigned CVRSS                                : 1;
  unsigned CVREN                                : 1;
  unsigned CVR                                  : 4;
  unsigned CREF                                 : 1;
  unsigned CCH                                  : 2;
  unsigned INV                                  : 1;
  unsigned Ready                                : 1;
  unsigned CMPIE                                : 1;
  unsigned __dummy0                             : 18;
} _comp_cfg;

typedef volatile _comp_cfg _io_comp_cfg;

#define offs_COMP_CFG_ON                        0
#define offs_COMP_CFG_CVRR                      1
#define offs_COMP_CFG_CVRSS                     2
#define offs_COMP_CFG_CVREN                     3
#define offs_COMP_CFG_CVR                       4
#define offs_COMP_CFG_CREF                      8
#define offs_COMP_CFG_CCH                       9
#define offs_COMP_CFG_INV                       11
#define offs_COMP_CFG_Ready                     12
#define offs_COMP_CFG_CMPIE                     13

#define size_COMP_CFG_ON                        1
#define size_COMP_CFG_CVRR                      1
#define size_COMP_CFG_CVRSS                     1
#define size_COMP_CFG_CVREN                     1
#define size_COMP_CFG_CVR                       4
#define size_COMP_CFG_CREF                      1
#define size_COMP_CFG_CCH                       2
#define size_COMP_CFG_INV                       1
#define size_COMP_CFG_Ready                     1
#define size_COMP_CFG_CMPIE                     1

#define mask_COMP_CFG_ON                        ((unsigned long)0x00000001)
#define mask_COMP_CFG_CVRR                      ((unsigned long)0x00000002)
#define mask_COMP_CFG_CVRSS                     ((unsigned long)0x00000004)
#define mask_COMP_CFG_CVREN                     ((unsigned long)0x00000008)
#define mask_COMP_CFG_CVR                       ((unsigned long)0x000000F0)
#define mask_COMP_CFG_CREF                      ((unsigned long)0x00000100)
#define mask_COMP_CFG_CCH                       ((unsigned long)0x00000600)
#define mask_COMP_CFG_INV                       ((unsigned long)0x00000800)
#define mask_COMP_CFG_Ready                     ((unsigned long)0x00001000)
#define mask_COMP_CFG_CMPIE                     ((unsigned long)0x00002000)


typedef struct {
  unsigned Rslt_Sy                              : 1;
  unsigned Rslt_As                              : 1;
  unsigned Rst_lch                              : 1;
  unsigned __dummy0                             : 29;
} _comp_result;

typedef volatile _comp_result _io_comp_result;

#define offs_COMP_RESULT_Rslt_Sy                0
#define offs_COMP_RESULT_Rslt_As                1
#define offs_COMP_RESULT_Rst_lch                2

#define size_COMP_RESULT_Rslt_Sy                1
#define size_COMP_RESULT_Rslt_As                1
#define size_COMP_RESULT_Rst_lch                1

#define mask_COMP_RESULT_Rslt_Sy                ((unsigned long)0x00000001)
#define mask_COMP_RESULT_Rslt_As                ((unsigned long)0x00000002)
#define mask_COMP_RESULT_Rst_lch                ((unsigned long)0x00000004)


typedef struct {
	__io_reg CFG;
	__io_reg RESULT;
	__io_reg RESULT_LATCH;
} _comp;

#endif /* __1986BE91_COMP_H */
