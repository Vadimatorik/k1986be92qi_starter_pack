#ifndef __1986BE91_SPI_H
#define __1986BE91_SPI_H

#include "cm3_macro.h"

typedef struct {
  unsigned DSS                                  : 4;
  unsigned FRF                                  : 2;
  unsigned SPO                                  : 1;
  unsigned SPH                                  : 1;
  unsigned SCR                                  : 8;
  unsigned __dummy0                             : 16;
} _spi_cr0;

typedef volatile _spi_cr0 _io_spi_cr0;

#define offs_SPI_CR0_DSS                        0
#define offs_SPI_CR0_FRF                        4
#define offs_SPI_CR0_SPO                        6
#define offs_SPI_CR0_SPH                        7
#define offs_SPI_CR0_SCR                        8

#define size_SPI_CR0_DSS                        4
#define size_SPI_CR0_FRF                        2
#define size_SPI_CR0_SPO                        1
#define size_SPI_CR0_SPH                        1
#define size_SPI_CR0_SCR                        8

#define mask_SPI_CR0_DSS                        ((unsigned long)0x0000000F)
#define mask_SPI_CR0_FRF                        ((unsigned long)0x00000030)
#define mask_SPI_CR0_SPO                        ((unsigned long)0x00000040)
#define mask_SPI_CR0_SPH                        ((unsigned long)0x00000080)
#define mask_SPI_CR0_SCR                        ((unsigned long)0x0000FF00)


typedef struct {
  unsigned LBM                                  : 1;
  unsigned SSE                                  : 1;
  unsigned MS                                   : 1;
  unsigned SOD                                  : 1;
  unsigned __dummy0                             : 28;
} _spi_cr1;

typedef volatile _spi_cr1 _io_spi_cr1;

#define offs_SPI_CR1_LBM                        0
#define offs_SPI_CR1_SSE                        1
#define offs_SPI_CR1_MS                         2
#define offs_SPI_CR1_SOD                        3

#define size_SPI_CR1_LBM                        1
#define size_SPI_CR1_SSE                        1
#define size_SPI_CR1_MS                         1
#define size_SPI_CR1_SOD                        1

#define mask_SPI_CR1_LBM                        ((unsigned long)0x00000001)
#define mask_SPI_CR1_SSE                        ((unsigned long)0x00000002)
#define mask_SPI_CR1_MS                         ((unsigned long)0x00000004)
#define mask_SPI_CR1_SOD                        ((unsigned long)0x00000008)


typedef struct {
  unsigned TFE                                  : 1;
  unsigned TNF                                  : 1;
  unsigned RNE                                  : 1;
  unsigned RFF                                  : 1;
  unsigned BSY                                  : 1;
  unsigned __dummy0                             : 27;
} _spi_sr;

typedef volatile _spi_sr _io_spi_sr;

#define offs_SPI_SR_TFE                         0
#define offs_SPI_SR_TNF                         1
#define offs_SPI_SR_RNE                         2
#define offs_SPI_SR_RFF                         3
#define offs_SPI_SR_BSY                         4

#define size_SPI_SR_TFE                         1
#define size_SPI_SR_TNF                         1
#define size_SPI_SR_RNE                         1
#define size_SPI_SR_RFF                         1
#define size_SPI_SR_BSY                         1

#define mask_SPI_SR_TFE                         ((unsigned long)0x00000001)
#define mask_SPI_SR_TNF                         ((unsigned long)0x00000002)
#define mask_SPI_SR_RNE                         ((unsigned long)0x00000004)
#define mask_SPI_SR_RFF                         ((unsigned long)0x00000008)
#define mask_SPI_SR_BSY                         ((unsigned long)0x00000010)


typedef struct {
  unsigned RORIM                                : 1;
  unsigned RTIM                                 : 1;
  unsigned RXIM                                 : 1;
  unsigned TXIM                                 : 1;
  unsigned __dummy0                             : 28;
} _spi_imsc;

typedef volatile _spi_imsc _io_spi_imsc;

#define offs_SPI_IMSC_RORIM                     0
#define offs_SPI_IMSC_RTIM                      1
#define offs_SPI_IMSC_RXIM                      2
#define offs_SPI_IMSC_TXIM                      3

#define size_SPI_IMSC_RORIM                     1
#define size_SPI_IMSC_RTIM                      1
#define size_SPI_IMSC_RXIM                      1
#define size_SPI_IMSC_TXIM                      1

#define mask_SPI_IMSC_RORIM                     ((unsigned long)0x00000001)
#define mask_SPI_IMSC_RTIM                      ((unsigned long)0x00000002)
#define mask_SPI_IMSC_RXIM                      ((unsigned long)0x00000004)
#define mask_SPI_IMSC_TXIM                      ((unsigned long)0x00000008)


typedef struct {
  unsigned RORRIS                               : 1;
  unsigned RTRIS                                : 1;
  unsigned RXRIS                                : 1;
  unsigned TXRIS                                : 1;
  unsigned __dummy0                             : 28;
} _spi_ris;

typedef volatile _spi_ris _io_spi_ris;

#define offs_SPI_RIS_RORRIS                     0
#define offs_SPI_RIS_RTRIS                      1
#define offs_SPI_RIS_RXRIS                      2
#define offs_SPI_RIS_TXRIS                      3

#define size_SPI_RIS_RORRIS                     1
#define size_SPI_RIS_RTRIS                      1
#define size_SPI_RIS_RXRIS                      1
#define size_SPI_RIS_TXRIS                      1

#define mask_SPI_RIS_RORRIS                     ((unsigned long)0x00000001)
#define mask_SPI_RIS_RTRIS                      ((unsigned long)0x00000002)
#define mask_SPI_RIS_RXRIS                      ((unsigned long)0x00000004)
#define mask_SPI_RIS_TXRIS                      ((unsigned long)0x00000008)


typedef struct {
  unsigned RORMIS                               : 1;
  unsigned RTMIS                                : 1;
  unsigned RXMIS                                : 1;
  unsigned TXMIS                                : 1;
  unsigned __dummy0                             : 28;
} _spi_mis;

typedef volatile _spi_mis _io_spi_mis;

#define offs_SPI_MIS_RORMIS                     0
#define offs_SPI_MIS_RTMIS                      1
#define offs_SPI_MIS_RXMIS                      2
#define offs_SPI_MIS_TXMIS                      3

#define size_SPI_MIS_RORMIS                     1
#define size_SPI_MIS_RTMIS                      1
#define size_SPI_MIS_RXMIS                      1
#define size_SPI_MIS_TXMIS                      1

#define mask_SPI_MIS_RORMIS                     ((unsigned long)0x00000001)
#define mask_SPI_MIS_RTMIS                      ((unsigned long)0x00000002)
#define mask_SPI_MIS_RXMIS                      ((unsigned long)0x00000004)
#define mask_SPI_MIS_TXMIS                      ((unsigned long)0x00000008)


typedef struct {
  unsigned RORIC                                : 1;
  unsigned RTIC                                 : 1;
  unsigned __dummy0                             : 30;
} _spi_icr;

typedef volatile _spi_icr _io_spi_icr;

#define offs_SPI_ICR_RORIC                      0
#define offs_SPI_ICR_RTIC                       1

#define size_SPI_ICR_RORIC                      1
#define size_SPI_ICR_RTIC                       1

#define mask_SPI_ICR_RORIC                      ((unsigned long)0x00000001)
#define mask_SPI_ICR_RTIC                       ((unsigned long)0x00000002)


typedef struct {
  unsigned RXDMAE                               : 1;
  unsigned TXDMAE                               : 1;
  unsigned __dummy0                             : 30;
} _spi_dmacr;

typedef volatile _spi_dmacr _io_spi_dmacr;

#define offs_SPI_DMACR_RXDMAE                   0
#define offs_SPI_DMACR_TXDMAE                   1

#define size_SPI_DMACR_RXDMAE                   1
#define size_SPI_DMACR_TXDMAE                   1

#define mask_SPI_DMACR_RXDMAE                   ((unsigned long)0x00000001)
#define mask_SPI_DMACR_TXDMAE                   ((unsigned long)0x00000002)


typedef struct {
	__io_reg CR0;
	__io_reg CR1;
	__io_reg DR;
	__io_reg SR;
	__io_reg CPSR;
	__io_reg IMSC;
	__io_reg RIS;
	__io_reg MIS;
	__io_reg ICR;
	__io_reg DMACR;
} _spi;

#endif /* __1986BE91_SPI_H */
