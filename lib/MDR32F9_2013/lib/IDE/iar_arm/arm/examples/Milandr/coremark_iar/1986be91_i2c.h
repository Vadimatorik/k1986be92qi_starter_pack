#ifndef __1986BE91_I2C_H
#define __1986BE91_I2C_H

#include "cm3_macro.h"

typedef struct {
  unsigned S_I2C                                : 1;
  unsigned EN_INT                               : 1;
  unsigned EN_I2C                               : 1;
  unsigned __dummy0                             : 24;
} _i2c_ctr;

typedef volatile _i2c_ctr _io_i2c_ctr;

#define offs_I2C_CTR_S_I2C                      0
#define offs_I2C_CTR_EN_INT                     1
#define offs_I2C_CTR_EN_I2C                     2

#define size_I2C_CTR_S_I2C                      1
#define size_I2C_CTR_EN_INT                     1
#define size_I2C_CTR_EN_I2C                     1

#define mask_I2C_CTR_S_I2C                      ((unsigned long)0x00000001)
#define mask_I2C_CTR_EN_INT                     ((unsigned long)0x00000002)
#define mask_I2C_CTR_EN_I2C                     ((unsigned long)0x00000004)


typedef struct {
  unsigned INT                                  : 1;
  unsigned TR_PROG                              : 1;
  unsigned __dummy0                             : 3;
  unsigned LOST_ARB                             : 1;
  unsigned BUSY                                 : 1;
  unsigned Rx_ACK                               : 1;
  unsigned __dummy1                             : 24;
} _i2c_sta;

typedef volatile _i2c_sta _io_i2c_sta;

#define offs_I2C_STA_INT                        0
#define offs_I2C_STA_TR_PROG                    1
#define offs_I2C_STA_LOST_ARB                   5
#define offs_I2C_STA_BUSY                       6
#define offs_I2C_STA_Rx_ACK                     7

#define size_I2C_STA_INT                        1
#define size_I2C_STA_TR_PROG                    1
#define size_I2C_STA_LOST_ARB                   1
#define size_I2C_STA_BUSY                       1
#define size_I2C_STA_Rx_ACK                     1

#define mask_I2C_STA_INT                        ((unsigned long)0x00000001)
#define mask_I2C_STA_TR_PROG                    ((unsigned long)0x00000002)
#define mask_I2C_STA_LOST_ARB                   ((unsigned long)0x00000020)
#define mask_I2C_STA_BUSY                       ((unsigned long)0x00000040)
#define mask_I2C_STA_Rx_ACK                     ((unsigned long)0x00000080)


typedef struct {
  unsigned CLRINT                               : 1;
  unsigned __dummy0                             : 2;
  unsigned ACK                                  : 1;
  unsigned WR                                   : 1;
  unsigned RD                                   : 1;
  unsigned STOP                                 : 1;
  unsigned START                                : 1;
  unsigned __dummy1                             : 24;
} _i2c_cmd;

typedef volatile _i2c_cmd _io_i2c_cmd;

#define offs_I2C_CMD_CLRINT                     0
#define offs_I2C_CMD_ACK                        3
#define offs_I2C_CMD_WR                         4
#define offs_I2C_CMD_RD                         5
#define offs_I2C_CMD_STOP                       6
#define offs_I2C_CMD_START                      7

#define size_I2C_CMD_CLRINT                     1
#define size_I2C_CMD_ACK                        1
#define size_I2C_CMD_WR                         1
#define size_I2C_CMD_RD                         1
#define size_I2C_CMD_STOP                       1
#define size_I2C_CMD_START                      1

#define mask_I2C_CMD_CLRINT                     ((unsigned long)0x00000001)
#define mask_I2C_CMD_ACK                        ((unsigned long)0x00000008)
#define mask_I2C_CMD_WR                         ((unsigned long)0x00000010)
#define mask_I2C_CMD_RD                         ((unsigned long)0x00000020)
#define mask_I2C_CMD_STOP                       ((unsigned long)0x00000040)
#define mask_I2C_CMD_START                      ((unsigned long)0x00000080)


typedef struct {
	__io_reg PRL;
	__io_reg PRP;
	__io_reg CTR;
	__io_reg RXD;
	__io_reg STA;
	__io_reg TXD;
	__io_reg CMD;
} _i2c;

#endif /* __1986BE91_I2C_H */
