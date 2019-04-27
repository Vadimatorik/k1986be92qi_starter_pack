#ifndef __1986BE91_TIMER_H
#define __1986BE91_TIMER_H

#include "cm3_macro.h"

typedef struct {
  unsigned CNT_EN                               : 1;
  unsigned ARRB_EN                              : 1;
  unsigned WR_CMPL                              : 1;
  unsigned DIR                                  : 1;
  unsigned FDTS                                 : 2;
  unsigned CNT_MODE                             : 2;
  unsigned EVENT_SEL                            : 4;
  unsigned __dummy0                             : 20;
} _timer_cntrl;

typedef volatile _timer_cntrl _io_timer_cntrl;

#define offs_TIMER_CNTRL_CNT_EN                 0
#define offs_TIMER_CNTRL_ARRB_EN                1
#define offs_TIMER_CNTRL_WR_CMPL                2
#define offs_TIMER_CNTRL_DIR                    3
#define offs_TIMER_CNTRL_FDTS                   4
#define offs_TIMER_CNTRL_CNT_MODE               6
#define offs_TIMER_CNTRL_EVENT_SEL              8

#define size_TIMER_CNTRL_CNT_EN                 1
#define size_TIMER_CNTRL_ARRB_EN                1
#define size_TIMER_CNTRL_WR_CMPL                1
#define size_TIMER_CNTRL_DIR                    1
#define size_TIMER_CNTRL_FDTS                   2
#define size_TIMER_CNTRL_CNT_MODE               2
#define size_TIMER_CNTRL_EVENT_SEL              4

#define mask_TIMER_CNTRL_CNT_EN                 ((unsigned long)0x00000001)
#define mask_TIMER_CNTRL_ARRB_EN                ((unsigned long)0x00000002)
#define mask_TIMER_CNTRL_WR_CMPL                ((unsigned long)0x00000004)
#define mask_TIMER_CNTRL_DIR                    ((unsigned long)0x00000008)
#define mask_TIMER_CNTRL_FDTS                   ((unsigned long)0x00000030)
#define mask_TIMER_CNTRL_CNT_MODE               ((unsigned long)0x000000C0)
#define mask_TIMER_CNTRL_EVENT_SEL              ((unsigned long)0x00000F00)


typedef struct {
  unsigned CHFLTR                               : 4;
  unsigned CHSEL                                : 2;
  unsigned CHPSC                                : 2;
  unsigned OCCE                                 : 1;
  unsigned OCCM                                 : 3;
  unsigned BRKEN                                : 1;
  unsigned ETREN                                : 1;
  unsigned WR_CMPL                              : 1;
  unsigned CAP_nPWM                             : 1;
  unsigned __dummy0                             : 16;
} _timer_ch_cntrl;

typedef volatile _timer_ch_cntrl _io_timer_ch_cntrl;

#define offs_TIMER_CH_CNTRL_CHFLTR              0
#define offs_TIMER_CH_CNTRL_CHSEL               4
#define offs_TIMER_CH_CNTRL_CHPSC               6
#define offs_TIMER_CH_CNTRL_OCCE                8
#define offs_TIMER_CH_CNTRL_OCCM                9
#define offs_TIMER_CH_CNTRL_BRKEN               12
#define offs_TIMER_CH_CNTRL_ETREN               13
#define offs_TIMER_CH_CNTRL_WR_CMPL             14
#define offs_TIMER_CH_CNTRL_CAP_nPWM            15

#define size_TIMER_CH_CNTRL_CHFLTR              4
#define size_TIMER_CH_CNTRL_CHSEL               2
#define size_TIMER_CH_CNTRL_CHPSC               2
#define size_TIMER_CH_CNTRL_OCCE                1
#define size_TIMER_CH_CNTRL_OCCM                3
#define size_TIMER_CH_CNTRL_BRKEN               1
#define size_TIMER_CH_CNTRL_ETREN               1
#define size_TIMER_CH_CNTRL_WR_CMPL             1
#define size_TIMER_CH_CNTRL_CAP_nPWM            1

#define mask_TIMER_CH_CNTRL_CHFLTR              ((unsigned long)0x0000000F)
#define mask_TIMER_CH_CNTRL_CHSEL               ((unsigned long)0x00000030)
#define mask_TIMER_CH_CNTRL_CHPSC               ((unsigned long)0x000000C0)
#define mask_TIMER_CH_CNTRL_OCCE                ((unsigned long)0x00000100)
#define mask_TIMER_CH_CNTRL_OCCM                ((unsigned long)0x00000E00)
#define mask_TIMER_CH_CNTRL_BRKEN               ((unsigned long)0x00001000)
#define mask_TIMER_CH_CNTRL_ETREN               ((unsigned long)0x00002000)
#define mask_TIMER_CH_CNTRL_WR_CMPL             ((unsigned long)0x00004000)
#define mask_TIMER_CH_CNTRL_CAP_nPWM            ((unsigned long)0x00008000)


typedef struct {
  unsigned SELOE                                : 2;
  unsigned SELO                                 : 2;
  unsigned INV                                  : 1;
  unsigned __dummy0                             : 3;
  unsigned NSELOE                               : 2;
  unsigned NSELO                                : 2;
  unsigned NINV                                 : 1;
  unsigned __dummy1                             : 19;
} _timer_ch_cntrl1;

typedef volatile _timer_ch_cntrl1 _io_timer_ch_cntrl1;

#define offs_TIMER_CH_CNTRL1_SELOE              0
#define offs_TIMER_CH_CNTRL1_SELO               2
#define offs_TIMER_CH_CNTRL1_INV                4
#define offs_TIMER_CH_CNTRL1_NSELOE             8
#define offs_TIMER_CH_CNTRL1_NSELO              10
#define offs_TIMER_CH_CNTRL1_NINV               12

#define size_TIMER_CH_CNTRL1_SELOE              2
#define size_TIMER_CH_CNTRL1_SELO               2
#define size_TIMER_CH_CNTRL1_INV                1
#define size_TIMER_CH_CNTRL1_NSELOE             2
#define size_TIMER_CH_CNTRL1_NSELO              2
#define size_TIMER_CH_CNTRL1_NINV               1

#define mask_TIMER_CH_CNTRL1_SELOE              ((unsigned long)0x00000003)
#define mask_TIMER_CH_CNTRL1_SELO               ((unsigned long)0x0000000C)
#define mask_TIMER_CH_CNTRL1_INV                ((unsigned long)0x00000010)
#define mask_TIMER_CH_CNTRL1_NSELOE             ((unsigned long)0x00000300)
#define mask_TIMER_CH_CNTRL1_NSELO              ((unsigned long)0x00000C00)
#define mask_TIMER_CH_CNTRL1_NINV               ((unsigned long)0x00001000)


typedef struct {
  unsigned DTGx                                 : 4;
  unsigned EDTS                                 : 1;
  unsigned __dummy0                             : 3;
  unsigned DTG                                  : 8;
  unsigned __dummy1                             : 16;
} _timer_ch_dtg;

typedef volatile _timer_ch_dtg _io_timer_ch_dtg;

#define offs_TIMER_CH_DTG_DTGx                  0
#define offs_TIMER_CH_DTG_EDTS                  4
#define offs_TIMER_CH_DTG                       8

#define size_TIMER_CH_DTG_DTGx                  4
#define size_TIMER_CH_DTG_EDTS                  1
#define size_TIMER_CH_DTG                       8

#define mask_TIMER_CH_DTG_DTGx                  ((unsigned long)0x0000000F)
#define mask_TIMER_CH_DTG_EDTS                  ((unsigned long)0x00000010)
#define mask_TIMER_CH_DTG                       ((unsigned long)0x0000FF00)


typedef struct {
  unsigned BRK_INV                              : 1;
  unsigned ETR_INV                              : 1;
  unsigned ETR_PSC                              : 2;
  unsigned ETR_FILTER                           : 4;
  unsigned __dummy0                             : 24;
} _timer_brketr_cntrl;

typedef volatile _timer_brketr_cntrl _io_timer_brketr_cntrl;

#define offs_TIMER_BRKETR_CNTRL_BRK_INV         0
#define offs_TIMER_BRKETR_CNTRL_ETR_INV         1
#define offs_TIMER_BRKETR_CNTRL_ETR_PSC         2
#define offs_TIMER_BRKETR_CNTRL_ETR_FILTER      4

#define size_TIMER_BRKETR_CNTRL_BRK_INV         1
#define size_TIMER_BRKETR_CNTRL_ETR_INV         1
#define size_TIMER_BRKETR_CNTRL_ETR_PSC         2
#define size_TIMER_BRKETR_CNTRL_ETR_FILTER      4

#define mask_TIMER_BRKETR_CNTRL_BRK_INV         ((unsigned long)0x00000001)
#define mask_TIMER_BRKETR_CNTRL_ETR_INV         ((unsigned long)0x00000002)
#define mask_TIMER_BRKETR_CNTRL_ETR_PSC         ((unsigned long)0x0000000C)
#define mask_TIMER_BRKETR_CNTRL_ETR_FILTER      ((unsigned long)0x000000F0)


typedef struct {
  unsigned CNT_ZERO_EVENT                       : 1;
  unsigned CNT_ARR_EVENT                        : 1;
  unsigned ETR_RE_EVENT                         : 1;
  unsigned ETR_FE_EVENT                         : 1;
  unsigned BRK_EVENT                            : 1;
  unsigned CCR_CAP_EVENT                        : 4;
  unsigned CCR_REF_EVENT                        : 4;
  unsigned CCR1_CAP_EVENT                       : 4;
  unsigned __dummy0                             : 15;
} _timer_status;

typedef volatile _timer_status _io_timer_status;

#define offs_TIMER_STATUS_CNT_ZERO_EVENT        0
#define offs_TIMER_STATUS_CNT_ARR_EVENT         1
#define offs_TIMER_STATUS_ETR_RE_EVENT          2
#define offs_TIMER_STATUS_ETR_FE_EVENT          3
#define offs_TIMER_STATUS_BRK_EVENT             4
#define offs_TIMER_STATUS_CCR_CAP_EVENT         5
#define offs_TIMER_STATUS_CCR_REF_EVENT         9
#define offs_TIMER_STATUS_CCR1_CAP_EVENT        13

#define size_TIMER_STATUS_CNT_ZERO_EVENT        1
#define size_TIMER_STATUS_CNT_ARR_EVENT         1
#define size_TIMER_STATUS_ETR_RE_EVENT          1
#define size_TIMER_STATUS_ETR_FE_EVENT          1
#define size_TIMER_STATUS_BRK_EVENT             1
#define size_TIMER_STATUS_CCR_CAP_EVENT         4
#define size_TIMER_STATUS_CCR_REF_EVENT         4
#define size_TIMER_STATUS_CCR1_CAP_EVENT        4

#define mask_TIMER_STATUS_CNT_ZERO_EVENT        ((unsigned long)0x00000001)
#define mask_TIMER_STATUS_CNT_ARR_EVENT         ((unsigned long)0x00000002)
#define mask_TIMER_STATUS_ETR_RE_EVENT          ((unsigned long)0x00000004)
#define mask_TIMER_STATUS_ETR_FE_EVENT          ((unsigned long)0x00000008)
#define mask_TIMER_STATUS_BRK_EVENT             ((unsigned long)0x00000010)
#define mask_TIMER_STATUS_CCR_CAP_EVENT         ((unsigned long)0x000001E0)
#define mask_TIMER_STATUS_CCR_REF_EVENT         ((unsigned long)0x00001E00)
#define mask_TIMER_STATUS_CCR1_CAP_EVENT        ((unsigned long)0x0001E000)


typedef struct {
  unsigned CNT_ZERO_EVENT_IE                    : 1;
  unsigned CNT_ARR_EVENT_IE                     : 1;
  unsigned ETR_RE_EVENT_IE                      : 1;
  unsigned ETR_FE_EVENT_IE                      : 1;
  unsigned BRK_EVENT_IE                         : 1;
  unsigned CCR_CAP_EVENT_IE                     : 4;
  unsigned CCR_REF_EVENT_IE                     : 4;
  unsigned __dummy0                             : 19;
} _timer_ie;

typedef volatile _timer_ie _io_timer_ie;

#define offs_TIMER_IE_CNT_ZERO_EVENT_IE         0
#define offs_TIMER_IE_CNT_ARR_EVENT_IE          1
#define offs_TIMER_IE_ETR_RE_EVENT_IE           2
#define offs_TIMER_IE_ETR_FE_EVENT_IE           3
#define offs_TIMER_IE_BRK_EVENT_IE              4
#define offs_TIMER_IE_CCR_CAP_EVENT_IE          5
#define offs_TIMER_IE_CCR_REF_EVENT_IE          9

#define size_TIMER_IE_CNT_ZERO_EVENT_IE         1
#define size_TIMER_IE_CNT_ARR_EVENT_IE          1
#define size_TIMER_IE_ETR_RE_EVENT_IE           1
#define size_TIMER_IE_ETR_FE_EVENT_IE           1
#define size_TIMER_IE_BRK_EVENT_IE              1
#define size_TIMER_IE_CCR_CAP_EVENT_IE          4
#define size_TIMER_IE_CCR_REF_EVENT_IE          4

#define mask_TIMER_IE_CNT_ZERO_EVENT_IE         ((unsigned long)0x00000001)
#define mask_TIMER_IE_CNT_ARR_EVENT_IE          ((unsigned long)0x00000002)
#define mask_TIMER_IE_ETR_RE_EVENT_IE           ((unsigned long)0x00000004)
#define mask_TIMER_IE_ETR_FE_EVENT_IE           ((unsigned long)0x00000008)
#define mask_TIMER_IE_BRK_EVENT_IE              ((unsigned long)0x00000010)
#define mask_TIMER_IE_CCR_CAP_EVENT_IE          ((unsigned long)0x000001E0)
#define mask_TIMER_IE_CCR_REF_EVENT_IE          ((unsigned long)0x00001E00)


typedef struct {
  unsigned CNT_ZERO_EVENT_RE                    : 1;
  unsigned CNT_ARR_EVENT_RE                     : 1;
  unsigned ETR_RE_EVENT_RE                      : 1;
  unsigned ETR_FE_EVENT_RE                      : 1;
  unsigned BRK_EVENT_RE                         : 1;
  unsigned CCR_CAP_EVENT_RE                     : 4;
  unsigned CCR_REF_EVENT_RE                     : 4;
  unsigned __dummy0                             : 19;
} _timer_dma_re;

typedef volatile _timer_dma_re _io_timer_dma_re;

#define offs_TIMER_DMA_RE_CNT_ZERO_EVENT_RE     0
#define offs_TIMER_DMA_RE_CNT_ARR_EVENT_RE      1
#define offs_TIMER_DMA_RE_ETR_RE_EVENT_RE       2
#define offs_TIMER_DMA_RE_ETR_FE_EVENT_RE       3
#define offs_TIMER_DMA_RE_BRK_EVENT_RE          4
#define offs_TIMER_DMA_RE_CCR_CAP_EVENT_RE      5
#define offs_TIMER_DMA_RE_CCR_REF_EVENT_RE      9

#define size_TIMER_DMA_RE_CNT_ZERO_EVENT_RE     1
#define size_TIMER_DMA_RE_CNT_ARR_EVENT_RE      1
#define size_TIMER_DMA_RE_ETR_RE_EVENT_RE       1
#define size_TIMER_DMA_RE_ETR_FE_EVENT_RE       1
#define size_TIMER_DMA_RE_BRK_EVENT_RE          1
#define size_TIMER_DMA_RE_CCR_CAP_EVENT_RE      4
#define size_TIMER_DMA_RE_CCR_REF_EVENT_RE      4

#define mask_TIMER_DMA_RE_CNT_ZERO_EVENT_RE     ((unsigned long)0x00000001)
#define mask_TIMER_DMA_RE_CNT_ARR_EVENT_RE      ((unsigned long)0x00000002)
#define mask_TIMER_DMA_RE_ETR_RE_EVENT_RE       ((unsigned long)0x00000004)
#define mask_TIMER_DMA_RE_ETR_FE_EVENT_RE       ((unsigned long)0x00000008)
#define mask_TIMER_DMA_RE_BRK_EVENT_RE          ((unsigned long)0x00000010)
#define mask_TIMER_DMA_RE_CCR_CAP_EVENT_RE      ((unsigned long)0x000001E0)
#define mask_TIMER_DMA_RE_CCR_REF_EVENT_RE      ((unsigned long)0x00001E00)


typedef struct {
  unsigned CHSEL1                               : 2;
  unsigned CCR1_EN                              : 1;
  unsigned CCRRLD                               : 1;
  unsigned __dummy0                             : 28;
} _timer_ch_cntrl2;

typedef volatile _timer_ch_cntrl2 _io_timer_ch_cntrl2;

#define offs_TIMER_CH_CNTRL2_CHSEL1             0
#define offs_TIMER_CH_CNTRL2_CCR1_EN            2
#define offs_TIMER_CH_CNTRL2_CCRRLD             3

#define size_TIMER_CH_CNTRL2_CHSEL1             2
#define size_TIMER_CH_CNTRL2_CCR1_EN            1
#define size_TIMER_CH_CNTRL2_CCRRLD             1

#define mask_TIMER_CH_CNTRL2_CHSEL1             ((unsigned long)0x00000003)
#define mask_TIMER_CH_CNTRL2_CCR1_EN            ((unsigned long)0x00000004)
#define mask_TIMER_CH_CNTRL2_CCRRLD             ((unsigned long)0x00000008)


typedef struct {
	__io_reg CNT;
	__io_reg PSG;
	__io_reg ARR;
	__io_reg CNTRL;
	__io_reg CCR1;
	__io_reg CCR2;
	__io_reg CCR3;
	__io_reg CCR4;
	__io_reg CH1_CNTRL;
	__io_reg CH2_CNTRL;
	__io_reg CH3_CNTRL;
	__io_reg CH4_CNTRL;
	__io_reg CH1_CNTRL1;
	__io_reg CH2_CNTRL1;
	__io_reg CH3_CNTRL1;
	__io_reg CH4_CNTRL1;
	__io_reg CH1_DTG;
	__io_reg CH2_DTG;
	__io_reg CH3_DTG;
	__io_reg CH4_DTG;
	__io_reg BRKETR_CNTRL;
	__io_reg STATUS;
	__io_reg IE;
	__io_reg DMA_RE;
	__io_reg CH1_CNTRL2;
	__io_reg CH2_CNTRL2;
	__io_reg CH3_CNTRL2;
	__io_reg CH4_CNTRL2;
	__io_reg CCR11;
	__io_reg CCR21;
	__io_reg CCR31;
	__io_reg CCR41;
} _timer;

#endif /* __1986BE91_TIMER_H */
