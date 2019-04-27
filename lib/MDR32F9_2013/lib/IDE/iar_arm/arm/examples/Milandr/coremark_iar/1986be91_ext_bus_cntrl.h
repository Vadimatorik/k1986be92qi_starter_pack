#ifndef __1986BE91_EXT_BUS_CNTRL_H
#define __1986BE91_EXT_BUS_CNTRL_H

#include "cm3_macro.h"

typedef struct {
  unsigned t_rc                                 : 4;
  unsigned t_wc                                 : 4;
  unsigned t_rea                                : 4;
  unsigned t_wp                                 : 4;
  unsigned t_whr                                : 4;
  unsigned t_alea                               : 4;
  unsigned t_rr                                 : 4;
  unsigned __dummy0                             : 4;
} _ext_bus_cntrl_nand_cycles;

typedef volatile _ext_bus_cntrl_nand_cycles _io_ext_bus_cntrl_nand_cycles;

#define offs_EXT_BUS_CNTRL_NAND_CYCLES_t_rc     0
#define offs_EXT_BUS_CNTRL_NAND_CYCLES_t_wc     4
#define offs_EXT_BUS_CNTRL_NAND_CYCLES_t_rea    8
#define offs_EXT_BUS_CNTRL_NAND_CYCLES_t_wp     12
#define offs_EXT_BUS_CNTRL_NAND_CYCLES_t_whr    16
#define offs_EXT_BUS_CNTRL_NAND_CYCLES_t_alea   20
#define offs_EXT_BUS_CNTRL_NAND_CYCLES_t_rr     24

#define size_EXT_BUS_CNTRL_NAND_CYCLES_t_rc     4
#define size_EXT_BUS_CNTRL_NAND_CYCLES_t_wc     4
#define size_EXT_BUS_CNTRL_NAND_CYCLES_t_rea    4
#define size_EXT_BUS_CNTRL_NAND_CYCLES_t_wp     4
#define size_EXT_BUS_CNTRL_NAND_CYCLES_t_whr    4
#define size_EXT_BUS_CNTRL_NAND_CYCLES_t_alea   4
#define size_EXT_BUS_CNTRL_NAND_CYCLES_t_rr     4

#define mask_EXT_BUS_CNTRL_NAND_CYCLES_t_rc     ((unsigned long)0x0000000F)
#define mask_EXT_BUS_CNTRL_NAND_CYCLES_t_wc     ((unsigned long)0x000000F0)
#define mask_EXT_BUS_CNTRL_NAND_CYCLES_t_rea    ((unsigned long)0x00000F00)
#define mask_EXT_BUS_CNTRL_NAND_CYCLES_t_wp     ((unsigned long)0x0000F000)
#define mask_EXT_BUS_CNTRL_NAND_CYCLES_t_whr    ((unsigned long)0x000F0000)
#define mask_EXT_BUS_CNTRL_NAND_CYCLES_t_alea   ((unsigned long)0x00F00000)
#define mask_EXT_BUS_CNTRL_NAND_CYCLES_t_rr     ((unsigned long)0x0F000000)


typedef struct {
  unsigned ROM                                  : 1;
  unsigned RAM                                  : 1;
  unsigned NAND                                 : 1;
  unsigned CPOL                                 : 1;
  unsigned __dummy0                             : 3;
  unsigned BUSY                                 : 1;
  unsigned __dummy1                             : 4;
  unsigned WAIT_STATE                           : 4;
  unsigned __dummy2                             : 16;
} _ext_bus_cntrl_ext_bus_control;

typedef volatile _ext_bus_cntrl_ext_bus_control _io_ext_bus_cntrl_ext_bus_control;

#define offs_EXT_BUS_CNTRL_EXT_BUS_CONTROL_ROM  0
#define offs_EXT_BUS_CNTRL_EXT_BUS_CONTROL_RAM  1
#define offs_EXT_BUS_CNTRL_EXT_BUS_CONTROL_NAND 2
#define offs_EXT_BUS_CNTRL_EXT_BUS_CONTROL_CPOL 3
#define offs_EXT_BUS_CNTRL_EXT_BUS_CONTROL_BUSY 7
#define offs_EXT_BUS_CNTRL_EXT_BUS_CONTROL_WAIT_STATE 12

#define size_EXT_BUS_CNTRL_EXT_BUS_CONTROL_ROM  1
#define size_EXT_BUS_CNTRL_EXT_BUS_CONTROL_RAM  1
#define size_EXT_BUS_CNTRL_EXT_BUS_CONTROL_NAND 1
#define size_EXT_BUS_CNTRL_EXT_BUS_CONTROL_CPOL 1
#define size_EXT_BUS_CNTRL_EXT_BUS_CONTROL_BUSY 1
#define size_EXT_BUS_CNTRL_EXT_BUS_CONTROL_WAIT_STATE 4

#define mask_EXT_BUS_CNTRL_EXT_BUS_CONTROL_ROM  ((unsigned long)0x00000001)
#define mask_EXT_BUS_CNTRL_EXT_BUS_CONTROL_RAM  ((unsigned long)0x00000002)
#define mask_EXT_BUS_CNTRL_EXT_BUS_CONTROL_NAND ((unsigned long)0x00000004)
#define mask_EXT_BUS_CNTRL_EXT_BUS_CONTROL_CPOL ((unsigned long)0x00000008)
#define mask_EXT_BUS_CNTRL_EXT_BUS_CONTROL_BUSY ((unsigned long)0x00000080)
#define mask_EXT_BUS_CNTRL_EXT_BUS_CONTROL_WAIT_STATE ((unsigned long)0x0000F000)


typedef struct {
	__io_reg __dummy0[20];
	__io_reg NAND_CYCLES;
	__io_reg EXT_BUS_CONTROL;
} _ext_bus_cntrl;

#endif /* __1986BE91_EXT_BUS_CNTRL_H */
