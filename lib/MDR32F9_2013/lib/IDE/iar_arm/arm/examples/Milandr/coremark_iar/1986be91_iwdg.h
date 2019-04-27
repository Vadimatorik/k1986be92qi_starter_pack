#ifndef __1986BE91_IWDG_H
#define __1986BE91_IWDG_H

#include "cm3_macro.h"

typedef struct {
  unsigned PVU                                  : 1;
  unsigned RVU                                  : 1;
  unsigned __dummy0                             : 30;
} _iwdg_sr;

typedef volatile _iwdg_sr _io_iwdg_sr;

#define offs_IWDG_SR_PVU                        0
#define offs_IWDG_SR_RVU                        1

#define size_IWDG_SR_PVU                        1
#define size_IWDG_SR_RVU                        1

#define mask_IWDG_SR_PVU                        ((unsigned long)0x00000001)
#define mask_IWDG_SR_RVU                        ((unsigned long)0x00000002)


typedef struct {
	__io_reg KR;
	__io_reg PR;
	__io_reg PRL;
	__io_reg SR;
} _iwdg;

#endif /* __1986BE91_IWDG_H */
