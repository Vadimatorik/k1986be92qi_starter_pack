#ifndef __1986BE91_UART_H
#define __1986BE91_UART_H

#include "cm3_macro.h"

typedef struct {
  unsigned DATA                                 : 8;
  unsigned FE                                   : 1;
  unsigned PE                                   : 1;
  unsigned BE                                   : 1;
  unsigned OE                                   : 1;
  unsigned __dummy0                             : 20;
} _uart_dr;

typedef volatile _uart_dr _io_uart_dr;

#define offs_UART_DR_DATA                       0
#define offs_UART_DR_FE                         8
#define offs_UART_DR_PE                         9
#define offs_UART_DR_BE                         10
#define offs_UART_DR_OE                         11

#define size_UART_DR_DATA                       8
#define size_UART_DR_FE                         1
#define size_UART_DR_PE                         1
#define size_UART_DR_BE                         1
#define size_UART_DR_OE                         1

#define mask_UART_DR_DATA                       ((unsigned long)0x000000FF)
#define mask_UART_DR_FE                         ((unsigned long)0x00000100)
#define mask_UART_DR_PE                         ((unsigned long)0x00000200)
#define mask_UART_DR_BE                         ((unsigned long)0x00000400)
#define mask_UART_DR_OE                         ((unsigned long)0x00000800)


typedef struct {
  unsigned FE                                   : 1;
  unsigned PE                                   : 1;
  unsigned BE                                   : 1;
  unsigned OE                                   : 1;
  unsigned __dummy0                             : 28;
} _uart_rsr_ecr;

typedef volatile _uart_rsr_ecr _io_uart_rsr_ecr;

#define offs_UART_RSR_ECR_FE                    0
#define offs_UART_RSR_ECR_PE                    1
#define offs_UART_RSR_ECR_BE                    2
#define offs_UART_RSR_ECR_OE                    3

#define size_UART_RSR_ECR_FE                    1
#define size_UART_RSR_ECR_PE                    1
#define size_UART_RSR_ECR_BE                    1
#define size_UART_RSR_ECR_OE                    1

#define mask_UART_RSR_ECR_FE                    ((unsigned long)0x00000001)
#define mask_UART_RSR_ECR_PE                    ((unsigned long)0x00000002)
#define mask_UART_RSR_ECR_BE                    ((unsigned long)0x00000004)
#define mask_UART_RSR_ECR_OE                    ((unsigned long)0x00000008)


typedef struct {
  unsigned CTS                                  : 1;
  unsigned DSR                                  : 1;
  unsigned DCD                                  : 1;
  unsigned BUSY                                 : 1;
  unsigned RXFE                                 : 1;
  unsigned TXFF                                 : 1;
  unsigned RXFF                                 : 1;
  unsigned TXFE                                 : 1;
  unsigned RI                                   : 1;
  unsigned __dummy0                             : 23;
} _uart_fr;

typedef volatile _uart_fr _io_uart_fr;

#define offs_UART_FR_CTS                        0
#define offs_UART_FR_DSR                        1
#define offs_UART_FR_DCD                        2
#define offs_UART_FR_BUSY                       3
#define offs_UART_FR_RXFE                       4
#define offs_UART_FR_TXFF                       5
#define offs_UART_FR_RXFF                       6
#define offs_UART_FR_TXFE                       7
#define offs_UART_FR_RI                         8

#define size_UART_FR_CTS                        1
#define size_UART_FR_DSR                        1
#define size_UART_FR_DCD                        1
#define size_UART_FR_BUSY                       1
#define size_UART_FR_RXFE                       1
#define size_UART_FR_TXFF                       1
#define size_UART_FR_RXFF                       1
#define size_UART_FR_TXFE                       1
#define size_UART_FR_RI                         1

#define mask_UART_FR_CTS                        ((unsigned long)0x00000001)
#define mask_UART_FR_DSR                        ((unsigned long)0x00000002)
#define mask_UART_FR_DCD                        ((unsigned long)0x00000004)
#define mask_UART_FR_BUSY                       ((unsigned long)0x00000008)
#define mask_UART_FR_RXFE                       ((unsigned long)0x00000010)
#define mask_UART_FR_TXFF                       ((unsigned long)0x00000020)
#define mask_UART_FR_RXFF                       ((unsigned long)0x00000040)
#define mask_UART_FR_TXFE                       ((unsigned long)0x00000080)
#define mask_UART_FR_RI                         ((unsigned long)0x00000100)


typedef struct {
  unsigned BRK                                  : 1;
  unsigned PEN                                  : 1;
  unsigned EPS                                  : 1;
  unsigned STP2                                 : 1;
  unsigned FEN                                  : 1;
  unsigned WLEN                                 : 2;
  unsigned SPS                                  : 1;
  unsigned __dummy0                             : 24;
} _uart_lcr_h;

typedef volatile _uart_lcr_h _io_uart_lcr_h;

#define offs_UART_LCR_H_BRK                     0
#define offs_UART_LCR_H_PEN                     1
#define offs_UART_LCR_H_EPS                     2
#define offs_UART_LCR_H_STP2                    3
#define offs_UART_LCR_H_FEN                     4
#define offs_UART_LCR_H_WLEN                    5
#define offs_UART_LCR_H_SPS                     7

#define size_UART_LCR_H_BRK                     1
#define size_UART_LCR_H_PEN                     1
#define size_UART_LCR_H_EPS                     1
#define size_UART_LCR_H_STP2                    1
#define size_UART_LCR_H_FEN                     1
#define size_UART_LCR_H_WLEN                    2
#define size_UART_LCR_H_SPS                     1

#define mask_UART_LCR_H_BRK                     ((unsigned long)0x00000001)
#define mask_UART_LCR_H_PEN                     ((unsigned long)0x00000002)
#define mask_UART_LCR_H_EPS                     ((unsigned long)0x00000004)
#define mask_UART_LCR_H_STP2                    ((unsigned long)0x00000008)
#define mask_UART_LCR_H_FEN                     ((unsigned long)0x00000010)
#define mask_UART_LCR_H_WLEN                    ((unsigned long)0x00000060)
#define mask_UART_LCR_H_SPS                     ((unsigned long)0x00000080)


typedef struct {
  unsigned UARTEN                               : 1;
  unsigned SIREN                                : 1;
  unsigned SIRLP                                : 1;
  unsigned __dummy0                             : 4;
  unsigned LBE                                  : 1;
  unsigned TXE                                  : 1;
  unsigned RXE                                  : 1;
  unsigned DTR                                  : 1;
  unsigned RTS                                  : 1;
  unsigned Out1                                 : 1;
  unsigned Out2                                 : 1;
  unsigned RTSEn                                : 1;
  unsigned CTSEn                                : 1;
  unsigned __dummy1                             : 16;
} _uart_cr;

typedef volatile _uart_cr _io_uart_cr;

#define offs_UART_CR_UARTEN                     0
#define offs_UART_CR_SIREN                      1
#define offs_UART_CR_SIRLP                      2
#define offs_UART_CR_LBE                        7
#define offs_UART_CR_TXE                        8
#define offs_UART_CR_RXE                        9
#define offs_UART_CR_DTR                        10
#define offs_UART_CR_RTS                        11
#define offs_UART_CR_Out1                       12
#define offs_UART_CR_Out2                       13
#define offs_UART_CR_RTSEn                      14
#define offs_UART_CR_CTSEn                      15

#define size_UART_CR_UARTEN                     1
#define size_UART_CR_SIREN                      1
#define size_UART_CR_SIRLP                      1
#define size_UART_CR_LBE                        1
#define size_UART_CR_TXE                        1
#define size_UART_CR_RXE                        1
#define size_UART_CR_DTR                        1
#define size_UART_CR_RTS                        1
#define size_UART_CR_Out1                       1
#define size_UART_CR_Out2                       1
#define size_UART_CR_RTSEn                      1
#define size_UART_CR_CTSEn                      1

#define mask_UART_CR_UARTEN                     ((unsigned long)0x00000001)
#define mask_UART_CR_SIREN                      ((unsigned long)0x00000002)
#define mask_UART_CR_SIRLP                      ((unsigned long)0x00000004)
#define mask_UART_CR_LBE                        ((unsigned long)0x00000080)
#define mask_UART_CR_TXE                        ((unsigned long)0x00000100)
#define mask_UART_CR_RXE                        ((unsigned long)0x00000200)
#define mask_UART_CR_DTR                        ((unsigned long)0x00000400)
#define mask_UART_CR_RTS                        ((unsigned long)0x00000800)
#define mask_UART_CR_Out1                       ((unsigned long)0x00001000)
#define mask_UART_CR_Out2                       ((unsigned long)0x00002000)
#define mask_UART_CR_RTSEn                      ((unsigned long)0x00004000)
#define mask_UART_CR_CTSEn                      ((unsigned long)0x00008000)


typedef struct {
  unsigned TXIFLSEL                             : 3;
  unsigned RXIFLSEL                             : 3;
  unsigned __dummy0                             : 26;
} _uart_ifls;

typedef volatile _uart_ifls _io_uart_ifls;

#define offs_UART_IFLS_TXIFLSEL                 0
#define offs_UART_IFLS_RXIFLSEL                 3

#define size_UART_IFLS_TXIFLSEL                 3
#define size_UART_IFLS_RXIFLSEL                 3

#define mask_UART_IFLS_TXIFLSEL                 ((unsigned long)0x00000007)
#define mask_UART_IFLS_RXIFLSEL                 ((unsigned long)0x00000038)


typedef struct {
  unsigned RIMIM                                : 1;
  unsigned CTSMIM                               : 1;
  unsigned DCDMIM                               : 1;
  unsigned DSRMIM                               : 1;
  unsigned RXIM                                 : 1;
  unsigned TXIM                                 : 1;
  unsigned RTIM                                 : 1;
  unsigned FEIM                                 : 1;
  unsigned PEIM                                 : 1;
  unsigned BEIM                                 : 1;
  unsigned OEIM                                 : 1;
  unsigned __dummy0                             : 21;
} _uart_imsc;

typedef volatile _uart_imsc _io_uart_imsc;

#define offs_UART_IMSC_RIMIM                    0
#define offs_UART_IMSC_CTSMIM                   1
#define offs_UART_IMSC_DCDMIM                   2
#define offs_UART_IMSC_DSRMIM                   3
#define offs_UART_IMSC_RXIM                     4
#define offs_UART_IMSC_TXIM                     5
#define offs_UART_IMSC_RTIM                     6
#define offs_UART_IMSC_FEIM                     7
#define offs_UART_IMSC_PEIM                     8
#define offs_UART_IMSC_BEIM                     9
#define offs_UART_IMSC_OEIM                     10

#define size_UART_IMSC_RIMIM                    1
#define size_UART_IMSC_CTSMIM                   1
#define size_UART_IMSC_DCDMIM                   1
#define size_UART_IMSC_DSRMIM                   1
#define size_UART_IMSC_RXIM                     1
#define size_UART_IMSC_TXIM                     1
#define size_UART_IMSC_RTIM                     1
#define size_UART_IMSC_FEIM                     1
#define size_UART_IMSC_PEIM                     1
#define size_UART_IMSC_BEIM                     1
#define size_UART_IMSC_OEIM                     1

#define mask_UART_IMSC_RIMIM                    ((unsigned long)0x00000001)
#define mask_UART_IMSC_CTSMIM                   ((unsigned long)0x00000002)
#define mask_UART_IMSC_DCDMIM                   ((unsigned long)0x00000004)
#define mask_UART_IMSC_DSRMIM                   ((unsigned long)0x00000008)
#define mask_UART_IMSC_RXIM                     ((unsigned long)0x00000010)
#define mask_UART_IMSC_TXIM                     ((unsigned long)0x00000020)
#define mask_UART_IMSC_RTIM                     ((unsigned long)0x00000040)
#define mask_UART_IMSC_FEIM                     ((unsigned long)0x00000080)
#define mask_UART_IMSC_PEIM                     ((unsigned long)0x00000100)
#define mask_UART_IMSC_BEIM                     ((unsigned long)0x00000200)
#define mask_UART_IMSC_OEIM                     ((unsigned long)0x00000400)


typedef struct {
  unsigned RIRMIS                               : 1;
  unsigned CTSRMIS                              : 1;
  unsigned DCDRMIS                              : 1;
  unsigned DSRRMIS                              : 1;
  unsigned RXRIS                                : 1;
  unsigned TXRIS                                : 1;
  unsigned RTRIS                                : 1;
  unsigned FERIS                                : 1;
  unsigned PERIS                                : 1;
  unsigned BERIS                                : 1;
  unsigned OERIS                                : 1;
  unsigned __dummy0                             : 21;
} _uart_ris;

typedef volatile _uart_ris _io_uart_ris;

#define offs_UART_RIS_RIRMIS                    0
#define offs_UART_RIS_CTSRMIS                   1
#define offs_UART_RIS_DCDRMIS                   2
#define offs_UART_RIS_DSRRMIS                   3
#define offs_UART_RIS_RXRIS                     4
#define offs_UART_RIS_TXRIS                     5
#define offs_UART_RIS_RTRIS                     6
#define offs_UART_RIS_FERIS                     7
#define offs_UART_RIS_PERIS                     8
#define offs_UART_RIS_BERIS                     9
#define offs_UART_RIS_OERIS                     10

#define size_UART_RIS_RIRMIS                    1
#define size_UART_RIS_CTSRMIS                   1
#define size_UART_RIS_DCDRMIS                   1
#define size_UART_RIS_DSRRMIS                   1
#define size_UART_RIS_RXRIS                     1
#define size_UART_RIS_TXRIS                     1
#define size_UART_RIS_RTRIS                     1
#define size_UART_RIS_FERIS                     1
#define size_UART_RIS_PERIS                     1
#define size_UART_RIS_BERIS                     1
#define size_UART_RIS_OERIS                     1

#define mask_UART_RIS_RIRMIS                    ((unsigned long)0x00000001)
#define mask_UART_RIS_CTSRMIS                   ((unsigned long)0x00000002)
#define mask_UART_RIS_DCDRMIS                   ((unsigned long)0x00000004)
#define mask_UART_RIS_DSRRMIS                   ((unsigned long)0x00000008)
#define mask_UART_RIS_RXRIS                     ((unsigned long)0x00000010)
#define mask_UART_RIS_TXRIS                     ((unsigned long)0x00000020)
#define mask_UART_RIS_RTRIS                     ((unsigned long)0x00000040)
#define mask_UART_RIS_FERIS                     ((unsigned long)0x00000080)
#define mask_UART_RIS_PERIS                     ((unsigned long)0x00000100)
#define mask_UART_RIS_BERIS                     ((unsigned long)0x00000200)
#define mask_UART_RIS_OERIS                     ((unsigned long)0x00000400)


typedef struct {
  unsigned RIMMIS                               : 1;
  unsigned CTSMMIS                              : 1;
  unsigned DCDMMIS                              : 1;
  unsigned DSRMMIS                              : 1;
  unsigned RXMIS                                : 1;
  unsigned TXMIS                                : 1;
  unsigned RTMIS                                : 1;
  unsigned FEMIS                                : 1;
  unsigned PEMIS                                : 1;
  unsigned BEMIS                                : 1;
  unsigned OEMIS                                : 1;
  unsigned __dummy0                             : 21;
} _uart_mis;

typedef volatile _uart_mis _io_uart_mis;

#define offs_UART_MIS_RIMMIS                    0
#define offs_UART_MIS_CTSMMIS                   1
#define offs_UART_MIS_DCDMMIS                   2
#define offs_UART_MIS_DSRMMIS                   3
#define offs_UART_MIS_RXMIS                     4
#define offs_UART_MIS_TXMIS                     5
#define offs_UART_MIS_RTMIS                     6
#define offs_UART_MIS_FEMIS                     7
#define offs_UART_MIS_PEMIS                     8
#define offs_UART_MIS_BEMIS                     9
#define offs_UART_MIS_OEMIS                     10

#define size_UART_MIS_RIMMIS                    1
#define size_UART_MIS_CTSMMIS                   1
#define size_UART_MIS_DCDMMIS                   1
#define size_UART_MIS_DSRMMIS                   1
#define size_UART_MIS_RXMIS                     1
#define size_UART_MIS_TXMIS                     1
#define size_UART_MIS_RTMIS                     1
#define size_UART_MIS_FEMIS                     1
#define size_UART_MIS_PEMIS                     1
#define size_UART_MIS_BEMIS                     1
#define size_UART_MIS_OEMIS                     1

#define mask_UART_MIS_RIMMIS                    ((unsigned long)0x00000001)
#define mask_UART_MIS_CTSMMIS                   ((unsigned long)0x00000002)
#define mask_UART_MIS_DCDMMIS                   ((unsigned long)0x00000004)
#define mask_UART_MIS_DSRMMIS                   ((unsigned long)0x00000008)
#define mask_UART_MIS_RXMIS                     ((unsigned long)0x00000010)
#define mask_UART_MIS_TXMIS                     ((unsigned long)0x00000020)
#define mask_UART_MIS_RTMIS                     ((unsigned long)0x00000040)
#define mask_UART_MIS_FEMIS                     ((unsigned long)0x00000080)
#define mask_UART_MIS_PEMIS                     ((unsigned long)0x00000100)
#define mask_UART_MIS_BEMIS                     ((unsigned long)0x00000200)
#define mask_UART_MIS_OEMIS                     ((unsigned long)0x00000400)


typedef struct {
  unsigned RIMIC                                : 1;
  unsigned CTSMIC                               : 1;
  unsigned DCDMIC                               : 1;
  unsigned DSRMIC                               : 1;
  unsigned RXIC                                 : 1;
  unsigned TXIC                                 : 1;
  unsigned RTIC                                 : 1;
  unsigned FEIC                                 : 1;
  unsigned PEIC                                 : 1;
  unsigned BEIC                                 : 1;
  unsigned OEIC                                 : 1;
  unsigned __dummy0                             : 21;
} _uart_icr;

typedef volatile _uart_icr _io_uart_icr;

#define offs_UART_ICR_RIMIC                     0
#define offs_UART_ICR_CTSMIC                    1
#define offs_UART_ICR_DCDMIC                    2
#define offs_UART_ICR_DSRMIC                    3
#define offs_UART_ICR_RXIC                      4
#define offs_UART_ICR_TXIC                      5
#define offs_UART_ICR_RTIC                      6
#define offs_UART_ICR_FEIC                      7
#define offs_UART_ICR_PEIC                      8
#define offs_UART_ICR_BEIC                      9
#define offs_UART_ICR_OEIC                      10

#define size_UART_ICR_RIMIC                     1
#define size_UART_ICR_CTSMIC                    1
#define size_UART_ICR_DCDMIC                    1
#define size_UART_ICR_DSRMIC                    1
#define size_UART_ICR_RXIC                      1
#define size_UART_ICR_TXIC                      1
#define size_UART_ICR_RTIC                      1
#define size_UART_ICR_FEIC                      1
#define size_UART_ICR_PEIC                      1
#define size_UART_ICR_BEIC                      1
#define size_UART_ICR_OEIC                      1

#define mask_UART_ICR_RIMIC                     ((unsigned long)0x00000001)
#define mask_UART_ICR_CTSMIC                    ((unsigned long)0x00000002)
#define mask_UART_ICR_DCDMIC                    ((unsigned long)0x00000004)
#define mask_UART_ICR_DSRMIC                    ((unsigned long)0x00000008)
#define mask_UART_ICR_RXIC                      ((unsigned long)0x00000010)
#define mask_UART_ICR_TXIC                      ((unsigned long)0x00000020)
#define mask_UART_ICR_RTIC                      ((unsigned long)0x00000040)
#define mask_UART_ICR_FEIC                      ((unsigned long)0x00000080)
#define mask_UART_ICR_PEIC                      ((unsigned long)0x00000100)
#define mask_UART_ICR_BEIC                      ((unsigned long)0x00000200)
#define mask_UART_ICR_OEIC                      ((unsigned long)0x00000400)


typedef struct {
  unsigned RXDMAE                               : 1;
  unsigned TXDMAE                               : 1;
  unsigned DMAONERR                             : 1;
  unsigned __dummy0                             : 29;
} _uart_dmacr;

typedef volatile _uart_dmacr _io_uart_dmacr;

#define offs_UART_DMACR_RXDMAE                  0
#define offs_UART_DMACR_TXDMAE                  1
#define offs_UART_DMACR_DMAONERR                2

#define size_UART_DMACR_RXDMAE                  1
#define size_UART_DMACR_TXDMAE                  1
#define size_UART_DMACR_DMAONERR                1

#define mask_UART_DMACR_RXDMAE                  ((unsigned long)0x00000001)
#define mask_UART_DMACR_TXDMAE                  ((unsigned long)0x00000002)
#define mask_UART_DMACR_DMAONERR                ((unsigned long)0x00000004)


typedef struct {
	__io_reg DR;
	__io_reg RSR_ECR;
	__io_reg __dummy0[4];
	__io_reg FR;
	__io_reg __dummy1;
	__io_reg ILPR;
	__io_reg IBRD;
	__io_reg FBRD;
	__io_reg LCR_H;
	__io_reg CR;
	__io_reg IFLS;
	__io_reg IMSC;
	__io_reg RIS;
	__io_reg MIS;
	__io_reg ICR;
	__io_reg DMACR;
} _uart;

#endif /* __1986BE91_UART_H */
