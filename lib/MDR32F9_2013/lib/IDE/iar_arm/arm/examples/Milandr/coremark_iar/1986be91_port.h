#ifndef __1986BE91_PORT_H
#define __1986BE91_PORT_H

#include "cm3_macro.h"

typedef struct {
  unsigned MODE0                                : 2;
  unsigned MODE1                                : 2;
  unsigned MODE2                                : 2;
  unsigned MODE3                                : 2;
  unsigned MODE4                                : 2;
  unsigned MODE5                                : 2;
  unsigned MODE6                                : 2;
  unsigned MODE7                                : 2;
  unsigned MODE8                                : 2;
  unsigned MODE9                                : 2;
  unsigned MODE10                               : 2;
  unsigned MODE11                               : 2;
  unsigned MODE12                               : 2;
  unsigned MODE13                               : 2;
  unsigned MODE14                               : 2;
  unsigned MODE15                               : 2;
} _port_func;

typedef volatile _port_func _io_port_func;

#define offs_PORT_FUNC_MODE0                    0
#define offs_PORT_FUNC_MODE1                    2
#define offs_PORT_FUNC_MODE2                    4
#define offs_PORT_FUNC_MODE3                    6
#define offs_PORT_FUNC_MODE4                    8
#define offs_PORT_FUNC_MODE5                    10
#define offs_PORT_FUNC_MODE6                    12
#define offs_PORT_FUNC_MODE7                    14
#define offs_PORT_FUNC_MODE8                    16
#define offs_PORT_FUNC_MODE9                    18
#define offs_PORT_FUNC_MODE10                   20
#define offs_PORT_FUNC_MODE11                   22
#define offs_PORT_FUNC_MODE12                   24
#define offs_PORT_FUNC_MODE13                   26
#define offs_PORT_FUNC_MODE14                   28
#define offs_PORT_FUNC_MODE15                   30

#define size_PORT_FUNC_MODE0                    2
#define size_PORT_FUNC_MODE1                    2
#define size_PORT_FUNC_MODE2                    2
#define size_PORT_FUNC_MODE3                    2
#define size_PORT_FUNC_MODE4                    2
#define size_PORT_FUNC_MODE5                    2
#define size_PORT_FUNC_MODE6                    2
#define size_PORT_FUNC_MODE7                    2
#define size_PORT_FUNC_MODE8                    2
#define size_PORT_FUNC_MODE9                    2
#define size_PORT_FUNC_MODE10                   2
#define size_PORT_FUNC_MODE11                   2
#define size_PORT_FUNC_MODE12                   2
#define size_PORT_FUNC_MODE13                   2
#define size_PORT_FUNC_MODE14                   2
#define size_PORT_FUNC_MODE15                   2

#define mask_PORT_FUNC_MODE0                    ((unsigned long)0x00000003)
#define mask_PORT_FUNC_MODE1                    ((unsigned long)0x0000000C)
#define mask_PORT_FUNC_MODE2                    ((unsigned long)0x00000030)
#define mask_PORT_FUNC_MODE3                    ((unsigned long)0x000000C0)
#define mask_PORT_FUNC_MODE4                    ((unsigned long)0x00000300)
#define mask_PORT_FUNC_MODE5                    ((unsigned long)0x00000C00)
#define mask_PORT_FUNC_MODE6                    ((unsigned long)0x00003000)
#define mask_PORT_FUNC_MODE7                    ((unsigned long)0x0000C000)
#define mask_PORT_FUNC_MODE8                    ((unsigned long)0x00030000)
#define mask_PORT_FUNC_MODE9                    ((unsigned long)0x000C0000)
#define mask_PORT_FUNC_MODE10                   ((unsigned long)0x00300000)
#define mask_PORT_FUNC_MODE11                   ((unsigned long)0x00C00000)
#define mask_PORT_FUNC_MODE12                   ((unsigned long)0x03000000)
#define mask_PORT_FUNC_MODE13                   ((unsigned long)0x0C000000)
#define mask_PORT_FUNC_MODE14                   ((unsigned long)0x30000000)
#define mask_PORT_FUNC_MODE15                   ((unsigned long)0xC0000000)


typedef struct {
  unsigned PWR0                                 : 2;
  unsigned PWR1                                 : 2;
  unsigned PWR2                                 : 2;
  unsigned PWR3                                 : 2;
  unsigned PWR4                                 : 2;
  unsigned PWR5                                 : 2;
  unsigned PWR6                                 : 2;
  unsigned PWR7                                 : 2;
  unsigned PWR8                                 : 2;
  unsigned PWR9                                 : 2;
  unsigned PWR10                                : 2;
  unsigned PWR11                                : 2;
  unsigned PWR12                                : 2;
  unsigned PWR13                                : 2;
  unsigned PWR14                                : 2;
  unsigned PWR15                                : 2;
} _port_pwr;

typedef volatile _port_pwr _io_port_pwr;

#define offs_PORT_PWR_PWR0                      0
#define offs_PORT_PWR_PWR1                      2
#define offs_PORT_PWR_PWR2                      4
#define offs_PORT_PWR_PWR3                      6
#define offs_PORT_PWR_PWR4                      8
#define offs_PORT_PWR_PWR5                      10
#define offs_PORT_PWR_PWR6                      12
#define offs_PORT_PWR_PWR7                      14
#define offs_PORT_PWR_PWR8                      16
#define offs_PORT_PWR_PWR9                      18
#define offs_PORT_PWR_PWR10                     20
#define offs_PORT_PWR_PWR11                     22
#define offs_PORT_PWR_PWR12                     24
#define offs_PORT_PWR_PWR13                     26
#define offs_PORT_PWR_PWR14                     28
#define offs_PORT_PWR_PWR15                     30

#define size_PORT_PWR_PWR0                      2
#define size_PORT_PWR_PWR1                      2
#define size_PORT_PWR_PWR2                      2
#define size_PORT_PWR_PWR3                      2
#define size_PORT_PWR_PWR4                      2
#define size_PORT_PWR_PWR5                      2
#define size_PORT_PWR_PWR6                      2
#define size_PORT_PWR_PWR7                      2
#define size_PORT_PWR_PWR8                      2
#define size_PORT_PWR_PWR9                      2
#define size_PORT_PWR_PWR10                     2
#define size_PORT_PWR_PWR11                     2
#define size_PORT_PWR_PWR12                     2
#define size_PORT_PWR_PWR13                     2
#define size_PORT_PWR_PWR14                     2
#define size_PORT_PWR_PWR15                     2

#define mask_PORT_PWR_PWR0                      ((unsigned long)0x00000003)
#define mask_PORT_PWR_PWR1                      ((unsigned long)0x0000000C)
#define mask_PORT_PWR_PWR2                      ((unsigned long)0x00000030)
#define mask_PORT_PWR_PWR3                      ((unsigned long)0x000000C0)
#define mask_PORT_PWR_PWR4                      ((unsigned long)0x00000300)
#define mask_PORT_PWR_PWR5                      ((unsigned long)0x00000C00)
#define mask_PORT_PWR_PWR6                      ((unsigned long)0x00003000)
#define mask_PORT_PWR_PWR7                      ((unsigned long)0x0000C000)
#define mask_PORT_PWR_PWR8                      ((unsigned long)0x00030000)
#define mask_PORT_PWR_PWR9                      ((unsigned long)0x000C0000)
#define mask_PORT_PWR_PWR10                     ((unsigned long)0x00300000)
#define mask_PORT_PWR_PWR11                     ((unsigned long)0x00C00000)
#define mask_PORT_PWR_PWR12                     ((unsigned long)0x03000000)
#define mask_PORT_PWR_PWR13                     ((unsigned long)0x0C000000)
#define mask_PORT_PWR_PWR14                     ((unsigned long)0x30000000)
#define mask_PORT_PWR_PWR15                     ((unsigned long)0xC0000000)


typedef struct {
	__io_reg RXTX;
	__io_reg OE;
	__io_reg FUNC;
	__io_reg ANALOG;
	__io_reg PULL;
	__io_reg PD;
	__io_reg PWR;
	__io_reg GFEN;
} _port;

#endif /* __1986BE91_PORT_H */
