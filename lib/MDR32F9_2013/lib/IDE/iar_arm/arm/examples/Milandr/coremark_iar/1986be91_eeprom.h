#ifndef __1986BE91_EEPROM_H
#define __1986BE91_EEPROM_H

#include "cm3_macro.h"

typedef struct {
  unsigned CON                                  : 1;
  unsigned WR                                   : 1;
  unsigned RD                                   : 1;
  unsigned Delay                                : 3;
  unsigned XE                                   : 1;
  unsigned YE                                   : 1;
  unsigned SE                                   : 1;
  unsigned IFREN                                : 1;
  unsigned ERASE                                : 1;
  unsigned MAS1                                 : 1;
  unsigned PROG                                 : 1;
  unsigned NVSTR                                : 1;
  unsigned __dummy0                             : 18;
} _eeprom_cmd;

typedef volatile _eeprom_cmd _io_eeprom_cmd;

#define offs_EEPROM_CMD_CON                     0
#define offs_EEPROM_CMD_WR                      1
#define offs_EEPROM_CMD_RD                      2
#define offs_EEPROM_CMD_Delay                   3
#define offs_EEPROM_CMD_XE                      6
#define offs_EEPROM_CMD_YE                      7
#define offs_EEPROM_CMD_SE                      8
#define offs_EEPROM_CMD_IFREN                   9
#define offs_EEPROM_CMD_ERASE                   10
#define offs_EEPROM_CMD_MAS1                    11
#define offs_EEPROM_CMD_PROG                    12
#define offs_EEPROM_CMD_NVSTR                   13

#define size_EEPROM_CMD_CON                     1
#define size_EEPROM_CMD_WR                      1
#define size_EEPROM_CMD_RD                      1
#define size_EEPROM_CMD_Delay                   3
#define size_EEPROM_CMD_XE                      1
#define size_EEPROM_CMD_YE                      1
#define size_EEPROM_CMD_SE                      1
#define size_EEPROM_CMD_IFREN                   1
#define size_EEPROM_CMD_ERASE                   1
#define size_EEPROM_CMD_MAS1                    1
#define size_EEPROM_CMD_PROG                    1
#define size_EEPROM_CMD_NVSTR                   1

#define mask_EEPROM_CMD_CON                     ((unsigned long)0x00000001)
#define mask_EEPROM_CMD_WR                      ((unsigned long)0x00000002)
#define mask_EEPROM_CMD_RD                      ((unsigned long)0x00000004)
#define mask_EEPROM_CMD_Delay                   ((unsigned long)0x00000038)
#define mask_EEPROM_CMD_XE                      ((unsigned long)0x00000040)
#define mask_EEPROM_CMD_YE                      ((unsigned long)0x00000080)
#define mask_EEPROM_CMD_SE                      ((unsigned long)0x00000100)
#define mask_EEPROM_CMD_IFREN                   ((unsigned long)0x00000200)
#define mask_EEPROM_CMD_ERASE                   ((unsigned long)0x00000400)
#define mask_EEPROM_CMD_MAS1                    ((unsigned long)0x00000800)
#define mask_EEPROM_CMD_PROG                    ((unsigned long)0x00001000)
#define mask_EEPROM_CMD_NVSTR                   ((unsigned long)0x00002000)


typedef struct {
	__io_reg CMD;
	__io_reg ADR;
	__io_reg DI;
	__io_reg DO;
	__io_reg KEY;
	__io_reg CNTRL;
} _eeprom;

#endif /* __1986BE91_EEPROM_H */
