#ifndef __1986BE91_CAN_H
#define __1986BE91_CAN_H

#include "cm3_macro.h"

typedef struct {
  unsigned CAN_EN                               : 1;
  unsigned ROM                                  : 1;
  unsigned STM                                  : 1;
  unsigned SAP                                  : 1;
  unsigned ROP                                  : 1;
  unsigned __dummy0                             : 27;
} _can_control;

typedef volatile _can_control _io_can_control;

#define offs_CAN_CONTROL_CAN_EN                 0
#define offs_CAN_CONTROL_ROM                    1
#define offs_CAN_CONTROL_STM                    2
#define offs_CAN_CONTROL_SAP                    3
#define offs_CAN_CONTROL_ROP                    4

#define size_CAN_CONTROL_CAN_EN                 1
#define size_CAN_CONTROL_ROM                    1
#define size_CAN_CONTROL_STM                    1
#define size_CAN_CONTROL_SAP                    1
#define size_CAN_CONTROL_ROP                    1

#define mask_CAN_CONTROL_CAN_EN                 ((unsigned long)0x00000001)
#define mask_CAN_CONTROL_ROM                    ((unsigned long)0x00000002)
#define mask_CAN_CONTROL_STM                    ((unsigned long)0x00000004)
#define mask_CAN_CONTROL_SAP                    ((unsigned long)0x00000008)
#define mask_CAN_CONTROL_ROP                    ((unsigned long)0x00000010)


typedef struct {
  unsigned RX_READY                             : 1;
  unsigned TX_READY                             : 1;
  unsigned ERROR_OVER                           : 1;
  unsigned BIT_ERR                              : 1;
  unsigned BIT_STUFF_ERR                        : 1;
  unsigned CRC_ERR                              : 1;
  unsigned FRAME_ERR                            : 1;
  unsigned ACK_ERR                              : 1;
  unsigned IDLOWER                              : 1;
  unsigned ERR_STATUS                           : 2;
  unsigned RX_ERR_CNT8                          : 1;
  unsigned TX_ERR_CNT8                          : 1;
  unsigned __dummy0                             : 3;
  unsigned RX_ERR_CNT                           : 8;
  unsigned TX_ERR_CNT                           : 8;
} _can_status;

typedef volatile _can_status _io_can_status;

#define offs_CAN_STATUS_RX_READY                0
#define offs_CAN_STATUS_TX_READY                1
#define offs_CAN_STATUS_ERROR_OVER              2
#define offs_CAN_STATUS_BIT_ERR                 3
#define offs_CAN_STATUS_BIT_STUFF_ERR           4
#define offs_CAN_STATUS_CRC_ERR                 5
#define offs_CAN_STATUS_FRAME_ERR               6
#define offs_CAN_STATUS_ACK_ERR                 7
#define offs_CAN_STATUS_IDLOWER                 8
#define offs_CAN_STATUS_ERR_STATUS              9
#define offs_CAN_STATUS_RX_ERR_CNT8             11
#define offs_CAN_STATUS_TX_ERR_CNT8             12
#define offs_CAN_STATUS_RX_ERR_CNT              16
#define offs_CAN_STATUS_TX_ERR_CNT              24

#define size_CAN_STATUS_RX_READY                1
#define size_CAN_STATUS_TX_READY                1
#define size_CAN_STATUS_ERROR_OVER              1
#define size_CAN_STATUS_BIT_ERR                 1
#define size_CAN_STATUS_BIT_STUFF_ERR           1
#define size_CAN_STATUS_CRC_ERR                 1
#define size_CAN_STATUS_FRAME_ERR               1
#define size_CAN_STATUS_ACK_ERR                 1
#define size_CAN_STATUS_IDLOWER                 1
#define size_CAN_STATUS_ERR_STATUS              2
#define size_CAN_STATUS_RX_ERR_CNT8             1
#define size_CAN_STATUS_TX_ERR_CNT8             1
#define size_CAN_STATUS_RX_ERR_CNT              8
#define size_CAN_STATUS_TX_ERR_CNT              8

#define mask_CAN_STATUS_RX_READY                ((unsigned long)0x00000001)
#define mask_CAN_STATUS_TX_READY                ((unsigned long)0x00000002)
#define mask_CAN_STATUS_ERROR_OVER              ((unsigned long)0x00000004)
#define mask_CAN_STATUS_BIT_ERR                 ((unsigned long)0x00000008)
#define mask_CAN_STATUS_BIT_STUFF_ERR           ((unsigned long)0x00000010)
#define mask_CAN_STATUS_CRC_ERR                 ((unsigned long)0x00000020)
#define mask_CAN_STATUS_FRAME_ERR               ((unsigned long)0x00000040)
#define mask_CAN_STATUS_ACK_ERR                 ((unsigned long)0x00000080)
#define mask_CAN_STATUS_IDLOWER                 ((unsigned long)0x00000100)
#define mask_CAN_STATUS_ERR_STATUS              ((unsigned long)0x00000600)
#define mask_CAN_STATUS_RX_ERR_CNT8             ((unsigned long)0x00000800)
#define mask_CAN_STATUS_TX_ERR_CNT8             ((unsigned long)0x00001000)
#define mask_CAN_STATUS_RX_ERR_CNT              ((unsigned long)0x00FF0000)
#define mask_CAN_STATUS_TX_ERR_CNT              ((unsigned long)0xFF000000)


typedef struct {
  unsigned BRP                                  : 16;
  unsigned PSEG                                 : 3;
  unsigned SEG1                                 : 3;
  unsigned SEG2                                 : 3;
  unsigned SJW                                  : 2;
  unsigned SB                                   : 1;
  unsigned __dummy0                             : 4;
} _can_bittmng;

typedef volatile _can_bittmng _io_can_bittmng;

#define offs_CAN_BITTMNG_BRP                    0
#define offs_CAN_BITTMNG_PSEG                   16
#define offs_CAN_BITTMNG_SEG1                   19
#define offs_CAN_BITTMNG_SEG2                   22
#define offs_CAN_BITTMNG_SJW                    25
#define offs_CAN_BITTMNG_SB                     27

#define size_CAN_BITTMNG_BRP                    16
#define size_CAN_BITTMNG_PSEG                   3
#define size_CAN_BITTMNG_SEG1                   3
#define size_CAN_BITTMNG_SEG2                   3
#define size_CAN_BITTMNG_SJW                    2
#define size_CAN_BITTMNG_SB                     1

#define mask_CAN_BITTMNG_BRP                    ((unsigned long)0x0000FFFF)
#define mask_CAN_BITTMNG_PSEG                   ((unsigned long)0x00070000)
#define mask_CAN_BITTMNG_SEG1                   ((unsigned long)0x00380000)
#define mask_CAN_BITTMNG_SEG2                   ((unsigned long)0x01C00000)
#define mask_CAN_BITTMNG_SJW                    ((unsigned long)0x06000000)
#define mask_CAN_BITTMNG_SB                     ((unsigned long)0x08000000)


typedef struct {
  unsigned GLB_INT_EN                           : 1;
  unsigned RX_INT_EN                            : 1;
  unsigned TX_INT_EN                            : 1;
  unsigned ERR_INT_EN                           : 1;
  unsigned ERR_OVER_INT_EN                      : 1;
  unsigned __dummy0                             : 27;
} _can_int_en;

typedef volatile _can_int_en _io_can_int_en;

#define offs_CAN_INT_EN_GLB_INT_EN              0
#define offs_CAN_INT_EN_RX_INT_EN               1
#define offs_CAN_INT_EN_TX_INT_EN               2
#define offs_CAN_INT_EN_ERR_INT_EN              3
#define offs_CAN_INT_EN_ERR_OVER_INT_EN         4

#define size_CAN_INT_EN_GLB_INT_EN              1
#define size_CAN_INT_EN_RX_INT_EN               1
#define size_CAN_INT_EN_TX_INT_EN               1
#define size_CAN_INT_EN_ERR_INT_EN              1
#define size_CAN_INT_EN_ERR_OVER_INT_EN         1

#define mask_CAN_INT_EN_GLB_INT_EN              ((unsigned long)0x00000001)
#define mask_CAN_INT_EN_RX_INT_EN               ((unsigned long)0x00000002)
#define mask_CAN_INT_EN_TX_INT_EN               ((unsigned long)0x00000004)
#define mask_CAN_INT_EN_ERR_INT_EN              ((unsigned long)0x00000008)
#define mask_CAN_INT_EN_ERR_OVER_INT_EN         ((unsigned long)0x00000010)


typedef struct {
  unsigned EID                                  : 18;
  unsigned SID                                  : 11;
  unsigned __dummy0                             : 3;
} _can_rxid;

typedef volatile _can_rxid _io_can_rxid;

#define offs_CAN_RXID_EID                       0
#define offs_CAN_RXID_SID                       18

#define size_CAN_RXID_EID                       18
#define size_CAN_RXID_SID                       11

#define mask_CAN_RXID_EID                       ((unsigned long)0x0003FFFF)
#define mask_CAN_RXID_SID                       ((unsigned long)0x1FFC0000)


typedef struct {
  unsigned DLC                                  : 4;
  unsigned __dummy0                             : 4;
  unsigned RTR                                  : 1;
  unsigned R1                                   : 1;
  unsigned R0                                   : 1;
  unsigned SSR                                  : 1;
  unsigned IDE                                  : 1;
  unsigned __dummy1                             : 19;
} _can_rxdlc;

typedef volatile _can_rxdlc _io_can_rxdlc;

#define offs_CAN_RXDLC                          0
#define offs_CAN_RXDLC_RTR                      8
#define offs_CAN_RXDLC_R1                       9
#define offs_CAN_RXDLC_R0                       10
#define offs_CAN_RXDLC_SSR                      11
#define offs_CAN_RXDLC_IDE                      12

#define size_CAN_RXDLC                          4
#define size_CAN_RXDLC_RTR                      1
#define size_CAN_RXDLC_R1                       1
#define size_CAN_RXDLC_R0                       1
#define size_CAN_RXDLC_SSR                      1
#define size_CAN_RXDLC_IDE                      1

#define mask_CAN_RXDLC                          ((unsigned long)0x0000000F)
#define mask_CAN_RXDLC_RTR                      ((unsigned long)0x00000100)
#define mask_CAN_RXDLC_R1                       ((unsigned long)0x00000200)
#define mask_CAN_RXDLC_R0                       ((unsigned long)0x00000400)
#define mask_CAN_RXDLC_SSR                      ((unsigned long)0x00000800)
#define mask_CAN_RXDLC_IDE                      ((unsigned long)0x00001000)


typedef struct {
  unsigned DB0                                  : 8;
  unsigned DB1                                  : 8;
  unsigned DB2                                  : 8;
  unsigned DB3                                  : 8;
} _can_rxdatal;

typedef volatile _can_rxdatal _io_can_rxdatal;

#define offs_CAN_RXDATAL_DB0                    0
#define offs_CAN_RXDATAL_DB1                    8
#define offs_CAN_RXDATAL_DB2                    16
#define offs_CAN_RXDATAL_DB3                    24

#define size_CAN_RXDATAL_DB0                    8
#define size_CAN_RXDATAL_DB1                    8
#define size_CAN_RXDATAL_DB2                    8
#define size_CAN_RXDATAL_DB3                    8

#define mask_CAN_RXDATAL_DB0                    ((unsigned long)0x000000FF)
#define mask_CAN_RXDATAL_DB1                    ((unsigned long)0x0000FF00)
#define mask_CAN_RXDATAL_DB2                    ((unsigned long)0x00FF0000)
#define mask_CAN_RXDATAL_DB3                    ((unsigned long)0xFF000000)


typedef struct {
  unsigned DB4                                  : 8;
  unsigned DB5                                  : 8;
  unsigned DB6                                  : 8;
  unsigned DB7                                  : 8;
} _can_rxdatah;

typedef volatile _can_rxdatah _io_can_rxdatah;

#define offs_CAN_RXDATAH_DB4                    0
#define offs_CAN_RXDATAH_DB5                    8
#define offs_CAN_RXDATAH_DB6                    16
#define offs_CAN_RXDATAH_DB7                    24

#define size_CAN_RXDATAH_DB4                    8
#define size_CAN_RXDATAH_DB5                    8
#define size_CAN_RXDATAH_DB6                    8
#define size_CAN_RXDATAH_DB7                    8

#define mask_CAN_RXDATAH_DB4                    ((unsigned long)0x000000FF)
#define mask_CAN_RXDATAH_DB5                    ((unsigned long)0x0000FF00)
#define mask_CAN_RXDATAH_DB6                    ((unsigned long)0x00FF0000)
#define mask_CAN_RXDATAH_DB7                    ((unsigned long)0xFF000000)


typedef struct {
  unsigned EID                                  : 18;
  unsigned SID                                  : 11;
  unsigned __dummy0                             : 3;
} _can_txid;

typedef volatile _can_txid _io_can_txid;

#define offs_CAN_TXID_EID                       0
#define offs_CAN_TXID_SID                       18

#define size_CAN_TXID_EID                       18
#define size_CAN_TXID_SID                       11

#define mask_CAN_TXID_EID                       ((unsigned long)0x0003FFFF)
#define mask_CAN_TXID_SID                       ((unsigned long)0x1FFC0000)


typedef struct {
  unsigned DLC                                  : 4;
  unsigned __dummy0                             : 4;
  unsigned RTR                                  : 1;
  unsigned R1                                   : 1;
  unsigned R0                                   : 1;
  unsigned SSR                                  : 1;
  unsigned IDE                                  : 1;
  unsigned __dummy1                             : 19;
} _can_txdlc;

typedef volatile _can_txdlc _io_can_txdlc;

#define offs_CAN_TXDLC                          0
#define offs_CAN_TXDLC_RTR                      8
#define offs_CAN_TXDLC_R1                       9
#define offs_CAN_TXDLC_R0                       10
#define offs_CAN_TXDLC_SSR                      11
#define offs_CAN_TXDLC_IDE                      12

#define size_CAN_TXDLC                          4
#define size_CAN_TXDLC_RTR                      1
#define size_CAN_TXDLC_R1                       1
#define size_CAN_TXDLC_R0                       1
#define size_CAN_TXDLC_SSR                      1
#define size_CAN_TXDLC_IDE                      1

#define mask_CAN_TXDLC                          ((unsigned long)0x0000000F)
#define mask_CAN_TXDLC_RTR                      ((unsigned long)0x00000100)
#define mask_CAN_TXDLC_R1                       ((unsigned long)0x00000200)
#define mask_CAN_TXDLC_R0                       ((unsigned long)0x00000400)
#define mask_CAN_TXDLC_SSR                      ((unsigned long)0x00000800)
#define mask_CAN_TXDLC_IDE                      ((unsigned long)0x00001000)


typedef struct {
  unsigned DB0                                  : 8;
  unsigned DB1                                  : 8;
  unsigned DB2                                  : 8;
  unsigned DB3                                  : 8;
} _can_datal;

typedef volatile _can_datal _io_can_datal;

#define offs_CAN_DATAL_DB0                      0
#define offs_CAN_DATAL_DB1                      8
#define offs_CAN_DATAL_DB2                      16
#define offs_CAN_DATAL_DB3                      24

#define size_CAN_DATAL_DB0                      8
#define size_CAN_DATAL_DB1                      8
#define size_CAN_DATAL_DB2                      8
#define size_CAN_DATAL_DB3                      8

#define mask_CAN_DATAL_DB0                      ((unsigned long)0x000000FF)
#define mask_CAN_DATAL_DB1                      ((unsigned long)0x0000FF00)
#define mask_CAN_DATAL_DB2                      ((unsigned long)0x00FF0000)
#define mask_CAN_DATAL_DB3                      ((unsigned long)0xFF000000)


typedef struct {
  unsigned DB4                                  : 8;
  unsigned DB5                                  : 8;
  unsigned DB6                                  : 8;
  unsigned DB7                                  : 8;
} _can_datah;

typedef volatile _can_datah _io_can_datah;

#define offs_CAN_DATAH_DB4                      0
#define offs_CAN_DATAH_DB5                      8
#define offs_CAN_DATAH_DB6                      16
#define offs_CAN_DATAH_DB7                      24

#define size_CAN_DATAH_DB4                      8
#define size_CAN_DATAH_DB5                      8
#define size_CAN_DATAH_DB6                      8
#define size_CAN_DATAH_DB7                      8

#define mask_CAN_DATAH_DB4                      ((unsigned long)0x000000FF)
#define mask_CAN_DATAH_DB5                      ((unsigned long)0x0000FF00)
#define mask_CAN_DATAH_DB6                      ((unsigned long)0x00FF0000)
#define mask_CAN_DATAH_DB7                      ((unsigned long)0xFF000000)


typedef struct {
  unsigned EN                                   : 1;
  unsigned RX_TXn                               : 1;
  unsigned OVER_EN                              : 1;
  unsigned RTR_EN                               : 1;
  unsigned PRIOR_0                              : 1;
  unsigned TX_REQ                               : 1;
  unsigned RX_FULL                              : 1;
  unsigned OVER_WR                              : 1;
  unsigned __dummy0                             : 24;
} _can_buf__con;

typedef volatile _can_buf__con _io_can_buf__con;

#define offs_CAN_BUF__CON_EN                    0
#define offs_CAN_BUF__CON_RX_TXn                1
#define offs_CAN_BUF__CON_OVER_EN               2
#define offs_CAN_BUF__CON_RTR_EN                3
#define offs_CAN_BUF__CON_PRIOR_0               4
#define offs_CAN_BUF__CON_TX_REQ                5
#define offs_CAN_BUF__CON_RX_FULL               6
#define offs_CAN_BUF__CON_OVER_WR               7

#define size_CAN_BUF__CON_EN                    1
#define size_CAN_BUF__CON_RX_TXn                1
#define size_CAN_BUF__CON_OVER_EN               1
#define size_CAN_BUF__CON_RTR_EN                1
#define size_CAN_BUF__CON_PRIOR_0               1
#define size_CAN_BUF__CON_TX_REQ                1
#define size_CAN_BUF__CON_RX_FULL               1
#define size_CAN_BUF__CON_OVER_WR               1

#define mask_CAN_BUF__CON_EN                    ((unsigned long)0x00000001)
#define mask_CAN_BUF__CON_RX_TXn                ((unsigned long)0x00000002)
#define mask_CAN_BUF__CON_OVER_EN               ((unsigned long)0x00000004)
#define mask_CAN_BUF__CON_RTR_EN                ((unsigned long)0x00000008)
#define mask_CAN_BUF__CON_PRIOR_0               ((unsigned long)0x00000010)
#define mask_CAN_BUF__CON_TX_REQ                ((unsigned long)0x00000020)
#define mask_CAN_BUF__CON_RX_FULL               ((unsigned long)0x00000040)
#define mask_CAN_BUF__CON_OVER_WR               ((unsigned long)0x00000080)


typedef struct {
  unsigned EID                                  : 18;
  unsigned SID                                  : 11;
  unsigned __dummy0                             : 3;
} _can_buf_id;

typedef volatile _can_buf_id _io_can_buf_id;

#define offs_CAN_BUF_ID_EID                     0
#define offs_CAN_BUF_ID_SID                     18

#define size_CAN_BUF_ID_EID                     18
#define size_CAN_BUF_ID_SID                     11

#define mask_CAN_BUF_ID_EID                     ((unsigned long)0x0003FFFF)
#define mask_CAN_BUF_ID_SID                     ((unsigned long)0x1FFC0000)


typedef struct {
  unsigned DLC                                  : 4;
  unsigned __dummy0                             : 4;
  unsigned RTR                                  : 1;
  unsigned R1                                   : 1;
  unsigned R0                                   : 1;
  unsigned SSR                                  : 1;
  unsigned IDE                                  : 1;
  unsigned __dummy1                             : 19;
} _can_buf_dlc;

typedef volatile _can_buf_dlc _io_can_buf_dlc;

#define offs_CAN_BUF_DLC                        0
#define offs_CAN_BUF_DLC_RTR                    8
#define offs_CAN_BUF_DLC_R1                     9
#define offs_CAN_BUF_DLC_R0                     10
#define offs_CAN_BUF_DLC_SSR                    11
#define offs_CAN_BUF_DLC_IDE                    12

#define size_CAN_BUF_DLC                        4
#define size_CAN_BUF_DLC_RTR                    1
#define size_CAN_BUF_DLC_R1                     1
#define size_CAN_BUF_DLC_R0                     1
#define size_CAN_BUF_DLC_SSR                    1
#define size_CAN_BUF_DLC_IDE                    1

#define mask_CAN_BUF_DLC                        ((unsigned long)0x0000000F)
#define mask_CAN_BUF_DLC_RTR                    ((unsigned long)0x00000100)
#define mask_CAN_BUF_DLC_R1                     ((unsigned long)0x00000200)
#define mask_CAN_BUF_DLC_R0                     ((unsigned long)0x00000400)
#define mask_CAN_BUF_DLC_SSR                    ((unsigned long)0x00000800)
#define mask_CAN_BUF_DLC_IDE                    ((unsigned long)0x00001000)


typedef struct {
  unsigned DB0                                  : 8;
  unsigned DB1                                  : 8;
  unsigned DB2                                  : 8;
  unsigned DB3                                  : 8;
} _can_buf_datal;

typedef volatile _can_buf_datal _io_can_buf_datal;

#define offs_CAN_BUF_DATAL_DB0                  0
#define offs_CAN_BUF_DATAL_DB1                  8
#define offs_CAN_BUF_DATAL_DB2                  16
#define offs_CAN_BUF_DATAL_DB3                  24

#define size_CAN_BUF_DATAL_DB0                  8
#define size_CAN_BUF_DATAL_DB1                  8
#define size_CAN_BUF_DATAL_DB2                  8
#define size_CAN_BUF_DATAL_DB3                  8

#define mask_CAN_BUF_DATAL_DB0                  ((unsigned long)0x000000FF)
#define mask_CAN_BUF_DATAL_DB1                  ((unsigned long)0x0000FF00)
#define mask_CAN_BUF_DATAL_DB2                  ((unsigned long)0x00FF0000)
#define mask_CAN_BUF_DATAL_DB3                  ((unsigned long)0xFF000000)


typedef struct {
  unsigned DB4                                  : 8;
  unsigned DB5                                  : 8;
  unsigned DB6                                  : 8;
  unsigned DB7                                  : 8;
} _can_buf_datah;

typedef volatile _can_buf_datah _io_can_buf_datah;

#define offs_CAN_BUF_DATAH_DB4                  0
#define offs_CAN_BUF_DATAH_DB5                  8
#define offs_CAN_BUF_DATAH_DB6                  16
#define offs_CAN_BUF_DATAH_DB7                  24

#define size_CAN_BUF_DATAH_DB4                  8
#define size_CAN_BUF_DATAH_DB5                  8
#define size_CAN_BUF_DATAH_DB6                  8
#define size_CAN_BUF_DATAH_DB7                  8

#define mask_CAN_BUF_DATAH_DB4                  ((unsigned long)0x000000FF)
#define mask_CAN_BUF_DATAH_DB5                  ((unsigned long)0x0000FF00)
#define mask_CAN_BUF_DATAH_DB6                  ((unsigned long)0x00FF0000)
#define mask_CAN_BUF_DATAH_DB7                  ((unsigned long)0xFF000000)


typedef struct {
	__io_reg ID;
	__io_reg DLC;
	__io_reg DATAL;
	__io_reg DATAH;
} _can_buf;

typedef struct {
	__io_reg MASK;
	__io_reg FILTER;
} _can_buf0;

typedef struct {
	__io_reg CONTROL;
	__io_reg STATUS;
	__io_reg BITTMNG;
	__io_reg __dummy0;
	__io_reg INT_EN;
	__io_reg __dummy1[2];
	__io_reg OVER;
	__io_reg RXID;
	__io_reg RXDLC;
	__io_reg RXDATAL;
	__io_reg RXDATAH;
	__io_reg TXID;
	__io_reg TXDLC;
	__io_reg DATAL;
	__io_reg DATAH;
	__io_reg BUF_01_CON;
	__io_reg BUF_02_CON;
	__io_reg BUF_03_CON;
	__io_reg BUF_04_CON;
	__io_reg BUF_05_CON;
	__io_reg BUF_06_CON;
	__io_reg BUF_07_CON;
	__io_reg BUF_08_CON;
	__io_reg BUF_09_CON;
	__io_reg BUF_10_CON;
	__io_reg BUF_11_CON;
	__io_reg BUF_12_CON;
	__io_reg BUF_13_CON;
	__io_reg BUF_14_CON;
	__io_reg BUF_15_CON;
	__io_reg BUF_16_CON;
	__io_reg BUF_17_CON;
	__io_reg BUF_18_CON;
	__io_reg BUF_19_CON;
	__io_reg BUF_20_CON;
	__io_reg BUF_21_CON;
	__io_reg BUF_22_CON;
	__io_reg BUF_23_CON;
	__io_reg BUF_24_CON;
	__io_reg BUF_25_CON;
	__io_reg BUF_26_CON;
	__io_reg BUF_27_CON;
	__io_reg BUF_28_CON;
	__io_reg BUF_29_CON;
	__io_reg BUF_30_CON;
	__io_reg BUF_31_CON;
	__io_reg BUF_32_CON;
	__io_reg INT_RX;
	__io_reg RX;
	__io_reg INT_TX;
	__io_reg TX;
	__io_reg __dummy2[76];
	__io_reg BUF_01_ID;
	__io_reg BUF_01_DLC;
	__io_reg BUF_01_DATAL;
	__io_reg BUF_01_DATAH;
	__io_reg BUF_02_ID;
	__io_reg BUF_02_DLC;
	__io_reg BUF_02_DATAL;
	__io_reg BUF_02_DATAH;
	__io_reg BUF_03_ID;
	__io_reg BUF_03_DLC;
	__io_reg BUF_03_DATAL;
	__io_reg BUF_03_DATAH;
	__io_reg BUF_04_ID;
	__io_reg BUF_04_DLC;
	__io_reg BUF_04_DATAL;
	__io_reg BUF_04_DATAH;
	__io_reg BUF_05_ID;
	__io_reg BUF_05_DLC;
	__io_reg BUF_05_DATAL;
	__io_reg BUF_05_DATAH;
	__io_reg BUF_06_ID;
	__io_reg BUF_06_DLC;
	__io_reg BUF_06_DATAL;
	__io_reg BUF_06_DATAH;
	__io_reg BUF_07_ID;
	__io_reg BUF_07_DLC;
	__io_reg BUF_07_DATAL;
	__io_reg BUF_07_DATAH;
	__io_reg BUF_08_ID;
	__io_reg BUF_08_DLC;
	__io_reg BUF_08_DATAL;
	__io_reg BUF_08_DATAH;
	__io_reg BUF_09_ID;
	__io_reg BUF_09_DLC;
	__io_reg BUF_09_DATAL;
	__io_reg BUF_09_DATAH;
	__io_reg BUF_10_ID;
	__io_reg BUF_10_DLC;
	__io_reg BUF_10_DATAL;
	__io_reg BUF_10_DATAH;
	__io_reg BUF_11_ID;
	__io_reg BUF_11_DLC;
	__io_reg BUF_11_DATAL;
	__io_reg BUF_11_DATAH;
	__io_reg BUF_12_ID;
	__io_reg BUF_12_DLC;
	__io_reg BUF_12_DATAL;
	__io_reg BUF_12_DATAH;
	__io_reg BUF_13_ID;
	__io_reg BUF_13_DLC;
	__io_reg BUF_13_DATAL;
	__io_reg BUF_13_DATAH;
	__io_reg BUF_14_ID;
	__io_reg BUF_14_DLC;
	__io_reg BUF_14_DATAL;
	__io_reg BUF_14_DATAH;
	__io_reg BUF_15_ID;
	__io_reg BUF_15_DLC;
	__io_reg BUF_15_DATAL;
	__io_reg BUF_15_DATAH;
	__io_reg BUF_16_ID;
	__io_reg BUF_16_DLC;
	__io_reg BUF_16_DATAL;
	__io_reg BUF_16_DATAH;
	__io_reg BUF_17_ID;
	__io_reg BUF_17_DLC;
	__io_reg BUF_17_DATAL;
	__io_reg BUF_17_DATAH;
	__io_reg BUF_18_ID;
	__io_reg BUF_18_DLC;
	__io_reg BUF_18_DATAL;
	__io_reg BUF_18_DATAH;
	__io_reg BUF_19_ID;
	__io_reg BUF_19_DLC;
	__io_reg BUF_19_DATAL;
	__io_reg BUF_19_DATAH;
	__io_reg BUF_20_ID;
	__io_reg BUF_20_DLC;
	__io_reg BUF_20_DATAL;
	__io_reg BUF_20_DATAH;
	__io_reg BUF_21_ID;
	__io_reg BUF_21_DLC;
	__io_reg BUF_21_DATAL;
	__io_reg BUF_21_DATAH;
	__io_reg BUF_22_ID;
	__io_reg BUF_22_DLC;
	__io_reg BUF_22_DATAL;
	__io_reg BUF_22_DATAH;
	__io_reg BUF_23_ID;
	__io_reg BUF_23_DLC;
	__io_reg BUF_23_DATAL;
	__io_reg BUF_23_DATAH;
	__io_reg BUF_24_ID;
	__io_reg BUF_24_DLC;
	__io_reg BUF_24_DATAL;
	__io_reg BUF_24_DATAH;
	__io_reg BUF_25_ID;
	__io_reg BUF_25_DLC;
	__io_reg BUF_25_DATAL;
	__io_reg BUF_25_DATAH;
	__io_reg BUF_26_ID;
	__io_reg BUF_26_DLC;
	__io_reg BUF_26_DATAL;
	__io_reg BUF_26_DATAH;
	__io_reg BUF_27_ID;
	__io_reg BUF_27_DLC;
	__io_reg BUF_27_DATAL;
	__io_reg BUF_27_DATAH;
	__io_reg BUF_28_ID;
	__io_reg BUF_28_DLC;
	__io_reg BUF_28_DATAL;
	__io_reg BUF_28_DATAH;
	__io_reg BUF_29_ID;
	__io_reg BUF_29_DLC;
	__io_reg BUF_29_DATAL;
	__io_reg BUF_29_DATAH;
	__io_reg BUF_30_ID;
	__io_reg BUF_30_DLC;
	__io_reg BUF_30_DATAL;
	__io_reg BUF_30_DATAH;
	__io_reg BUF_31_ID;
	__io_reg BUF_31_DLC;
	__io_reg BUF_31_DATAL;
	__io_reg BUF_31_DATAH;
	__io_reg BUF_32_ID;
	__io_reg BUF_32_DLC;
	__io_reg BUF_32_DATAL;
	__io_reg BUF_32_DATAH;
	__io_reg __dummy3[64];
	__io_reg BUF_01_MASK;
	__io_reg BUF_01_FILTER;
	__io_reg BUF_02_MASK;
	__io_reg BUF_02_FILTER;
	__io_reg BUF_03_MASK;
	__io_reg BUF_03_FILTER;
	__io_reg BUF_04_MASK;
	__io_reg BUF_04_FILTER;
	__io_reg BUF_05_MASK;
	__io_reg BUF_05_FILTER;
	__io_reg BUF_06_MASK;
	__io_reg BUF_06_FILTER;
	__io_reg BUF_07_MASK;
	__io_reg BUF_07_FILTER;
	__io_reg BUF_08_MASK;
	__io_reg BUF_08_FILTER;
	__io_reg BUF_09_MASK;
	__io_reg BUF_09_FILTER;
	__io_reg BUF_10_MASK;
	__io_reg BUF_10_FILTER;
	__io_reg BUF_11_MASK;
	__io_reg BUF_11_FILTER;
	__io_reg BUF_12_MASK;
	__io_reg BUF_12_FILTER;
	__io_reg BUF_13_MASK;
	__io_reg BUF_13_FILTER;
	__io_reg BUF_14_MASK;
	__io_reg BUF_14_FILTER;
	__io_reg BUF_15_MASK;
	__io_reg BUF_15_FILTER;
	__io_reg BUF_16_MASK;
	__io_reg BUF_16_FILTER;
	__io_reg BUF_17_MASK;
	__io_reg BUF_17_FILTER;
	__io_reg BUF_18_MASK;
	__io_reg BUF_18_FILTER;
	__io_reg BUF_19_MASK;
	__io_reg BUF_19_FILTER;
	__io_reg BUF_20_MASK;
	__io_reg BUF_20_FILTER;
	__io_reg BUF_21_MASK;
	__io_reg BUF_21_FILTER;
	__io_reg BUF_22_MASK;
	__io_reg BUF_22_FILTER;
	__io_reg BUF_23_MASK;
	__io_reg BUF_23_FILTER;
	__io_reg BUF_24_MASK;
	__io_reg BUF_24_FILTER;
	__io_reg BUF_25_MASK;
	__io_reg BUF_25_FILTER;
	__io_reg BUF_26_MASK;
	__io_reg BUF_26_FILTER;
	__io_reg BUF_27_MASK;
	__io_reg BUF_27_FILTER;
	__io_reg BUF_28_MASK;
	__io_reg BUF_28_FILTER;
	__io_reg BUF_29_MASK;
	__io_reg BUF_29_FILTER;
	__io_reg BUF_30_MASK;
	__io_reg BUF_30_FILTER;
	__io_reg BUF_31_MASK;
	__io_reg BUF_31_FILTER;
	__io_reg BUF_32_MASK;
	__io_reg BUF_32_FILTER;
} _can;

#endif /* __1986BE91_CAN_H */
