#ifndef __1986BE91_WWDG_H
#define __1986BE91_WWDG_H

#include "cm3_macro.h"

typedef struct {
  unsigned T                                    : 7;
  unsigned WDGA                                 : 1;
  unsigned __dummy0                             : 24;
} _wwdg_cr;

typedef volatile _wwdg_cr _io_wwdg_cr;

#define offs_WWDG_CR_T                          0
#define offs_WWDG_CR_WDGA                       7

#define size_WWDG_CR_T                          7
#define size_WWDG_CR_WDGA                       1

#define mask_WWDG_CR_T                          ((unsigned long)0x0000007F)
#define mask_WWDG_CR_WDGA                       ((unsigned long)0x00000080)


typedef struct {
  unsigned W                                    : 7;
  unsigned WGTB                                 : 2;
  unsigned EWI                                  : 1;
  unsigned __dummy0                             : 22;
} _wwdg_cfr;

typedef volatile _wwdg_cfr _io_wwdg_cfr;

#define offs_WWDG_CFR_W                         0
#define offs_WWDG_CFR_WGTB                      7
#define offs_WWDG_CFR_EWI                       9

#define size_WWDG_CFR_W                         7
#define size_WWDG_CFR_WGTB                      2
#define size_WWDG_CFR_EWI                       1

#define mask_WWDG_CFR_W                         ((unsigned long)0x0000007F)
#define mask_WWDG_CFR_WGTB                      ((unsigned long)0x00000180)
#define mask_WWDG_CFR_EWI                       ((unsigned long)0x00000200)


typedef struct {
	__io_reg CR;
	__io_reg CFR;
	__io_reg SR;
} _wwdg;

#endif /* __1986BE91_WWDG_H */
