/**
  ******************************************************************************
  * @file    1986BE9x_timer_defs.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    24/09/2010
  * @brief   This file contains all the Special Function Registers definitions
  *          for the TIMER peripheral unit used in the Milandr 1986BE9x
  *          microcontrollers.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, PHYTON SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 Phyton</center></h2>
  ******************************************************************************
  * FILE 1986BE9x_timer_defs.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9X_TIMER_DEFS_H
#define __1986BE9X_TIMER_DEFS_H

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @addtogroup __1986BE9x_Peripheral_Units 1986BE9x Peripheral Units
  * @{
  */

/** @defgroup Periph_TIMER TIMER
  * @{
  */

/** @defgroup Periph_TIMER_Data_Structures Data Structures
  * @{
  */

/** @defgroup Periph_TIMER_TypeDef TIMER_TypeDef
  * @{
  */

typedef struct
{
  __IO uint32_t CNT;
  __IO uint32_t PSG;
  __IO uint32_t ARR;
  __IO uint32_t CNTRL;
  __IO uint32_t CCR1;
  __IO uint32_t CCR2;
  __IO uint32_t CCR3;
  __IO uint32_t CCR4;
  __IO uint32_t CH1_CNTRL;
  __IO uint32_t CH2_CNTRL;
  __IO uint32_t CH3_CNTRL;
  __IO uint32_t CH4_CNTRL;
  __IO uint32_t CH1_CNTRL1;
  __IO uint32_t CH2_CNTRL1;
  __IO uint32_t CH3_CNTRL1;
  __IO uint32_t CH4_CNTRL1;
  __IO uint32_t CH1_DTG;
  __IO uint32_t CH2_DTG;
  __IO uint32_t CH3_DTG;
  __IO uint32_t CH4_DTG;
  __IO uint32_t BRKETR_CNTRL;
  __IO uint32_t STATUS;
  __IO uint32_t IE;
  __IO uint32_t DMA_RE;
  __IO uint32_t CH1_CNTRL2;
  __IO uint32_t CH2_CNTRL2;
  __IO uint32_t CH3_CNTRL2;
  __IO uint32_t CH4_CNTRL2;
  __IO uint32_t CCR11;
  __IO uint32_t CCR21;
  __IO uint32_t CCR31;
  __IO uint32_t CCR41;
}TIMER_TypeDef;

/** @} */ /* End of group Periph_TIMER_TypeDef */

/** @} */ /* End of group Periph_TIMER_Data_Structures */

/** @defgroup Periph_TIMER_Defines Defines
  * @{
  */

/** @defgroup Periph_TIMER_TIMER_CNTRL_Bits TIMER_CNTRL
  * @{
  */

#define TIMER_CNTRL_CNT_EN_Pos                  0
#define TIMER_CNTRL_CNT_EN                      ((uint32_t)0x00000001)

#define TIMER_CNTRL_ARRB_EN_Pos                 1
#define TIMER_CNTRL_ARRB_EN                     ((uint32_t)0x00000002)

#define TIMER_CNTRL_WR_CMPL_Pos                 2
#define TIMER_CNTRL_WR_CMPL                     ((uint32_t)0x00000004)

#define TIMER_CNTRL_DIR_Pos                     3
#define TIMER_CNTRL_DIR                         ((uint32_t)0x00000008)

#define TIMER_CNTRL_FDTS_Pos                    4
#define TIMER_CNTRL_FDTS_Msk                    ((uint32_t)0x00000030)

#define TIMER_CNTRL_CNT_MODE_Pos                6
#define TIMER_CNTRL_CNT_MODE_Msk                ((uint32_t)0x000000C0)

#define TIMER_CNTRL_EVENT_SEL_Pos               8
#define TIMER_CNTRL_EVENT_SEL_Msk               ((uint32_t)0x00000F00)


/** @} */ /* End of group Periph_TIMER_TIMER_CNTRL_Bits */

/** @} */ /* End of group Periph_TIMER_Defines */

/** @defgroup Periph_TIMER_Defines Defines
  * @{
  */

/** @defgroup Periph_TIMER_TIMER_CH_CNTRL_Bits TIMER_CH_CNTRL
  * @{
  */

#define TIMER_CH_CNTRL_CHFLTR_Pos               0
#define TIMER_CH_CNTRL_CHFLTR_Msk               ((uint32_t)0x0000000F)

#define TIMER_CH_CNTRL_CHSEL_Pos                4
#define TIMER_CH_CNTRL_CHSEL_Msk                ((uint32_t)0x00000030)

#define TIMER_CH_CNTRL_CHPSC_Pos                6
#define TIMER_CH_CNTRL_CHPSC_Msk                ((uint32_t)0x000000C0)

#define TIMER_CH_CNTRL_OCCE_Pos                 8
#define TIMER_CH_CNTRL_OCCE                     ((uint32_t)0x00000100)

#define TIMER_CH_CNTRL_OCCM_Pos                 9
#define TIMER_CH_CNTRL_OCCM_Msk                 ((uint32_t)0x00000E00)

#define TIMER_CH_CNTRL_BRKEN_Pos                12
#define TIMER_CH_CNTRL_BRKEN                    ((uint32_t)0x00001000)

#define TIMER_CH_CNTRL_ETREN_Pos                13
#define TIMER_CH_CNTRL_ETREN                    ((uint32_t)0x00002000)

#define TIMER_CH_CNTRL_WR_CMPL_Pos              14
#define TIMER_CH_CNTRL_WR_CMPL                  ((uint32_t)0x00004000)

#define TIMER_CH_CNTRL_CAP_nPWM_Pos             15
#define TIMER_CH_CNTRL_CAP_nPWM                 ((uint32_t)0x00008000)


/** @} */ /* End of group Periph_TIMER_TIMER_CH_CNTRL_Bits */

/** @} */ /* End of group Periph_TIMER_Defines */

/** @defgroup Periph_TIMER_Defines Defines
  * @{
  */

/** @defgroup Periph_TIMER_TIMER_CH_CNTRL1_Bits TIMER_CH_CNTRL1
  * @{
  */

#define TIMER_CH_CNTRL1_SELOE_Pos               0
#define TIMER_CH_CNTRL1_SELOE_Msk               ((uint32_t)0x00000003)

#define TIMER_CH_CNTRL1_SELO_Pos                2
#define TIMER_CH_CNTRL1_SELO_Msk                ((uint32_t)0x0000000C)

#define TIMER_CH_CNTRL1_INV_Pos                 4
#define TIMER_CH_CNTRL1_INV                     ((uint32_t)0x00000010)

#define TIMER_CH_CNTRL1_NSELOE_Pos              8
#define TIMER_CH_CNTRL1_NSELOE_Msk              ((uint32_t)0x00000300)

#define TIMER_CH_CNTRL1_NSELO_Pos               10
#define TIMER_CH_CNTRL1_NSELO_Msk               ((uint32_t)0x00000C00)

#define TIMER_CH_CNTRL1_NINV_Pos                12
#define TIMER_CH_CNTRL1_NINV                    ((uint32_t)0x00001000)


/** @} */ /* End of group Periph_TIMER_TIMER_CH_CNTRL1_Bits */

/** @} */ /* End of group Periph_TIMER_Defines */

/** @defgroup Periph_TIMER_Defines Defines
  * @{
  */

/** @defgroup Periph_TIMER_TIMER_CH_DTG_Bits TIMER_CH_DTG
  * @{
  */

#define TIMER_CH_DTG_DTGx_Pos                   0
#define TIMER_CH_DTG_DTGx_Msk                   ((uint32_t)0x0000000F)

#define TIMER_CH_DTG_EDTS_Pos                   4
#define TIMER_CH_DTG_EDTS                       ((uint32_t)0x00000010)

#define TIMER_CH_DTG_Pos                        8
#define TIMER_CH_DTG_Msk                        ((uint32_t)0x0000FF00)


/** @} */ /* End of group Periph_TIMER_TIMER_CH_DTG_Bits */

/** @} */ /* End of group Periph_TIMER_Defines */

/** @defgroup Periph_TIMER_Defines Defines
  * @{
  */

/** @defgroup Periph_TIMER_TIMER_BRKETR_CNTRL_Bits TIMER_BRKETR_CNTRL
  * @{
  */

#define TIMER_BRKETR_CNTRL_BRK_INV_Pos          0
#define TIMER_BRKETR_CNTRL_BRK_INV              ((uint32_t)0x00000001)

#define TIMER_BRKETR_CNTRL_ETR_INV_Pos          1
#define TIMER_BRKETR_CNTRL_ETR_INV              ((uint32_t)0x00000002)

#define TIMER_BRKETR_CNTRL_ETR_PSC_Pos          2
#define TIMER_BRKETR_CNTRL_ETR_PSC_Msk          ((uint32_t)0x0000000C)

#define TIMER_BRKETR_CNTRL_ETR_FILTER_Pos       4
#define TIMER_BRKETR_CNTRL_ETR_FILTER_Msk       ((uint32_t)0x000000F0)


/** @} */ /* End of group Periph_TIMER_TIMER_BRKETR_CNTRL_Bits */

/** @} */ /* End of group Periph_TIMER_Defines */

/** @defgroup Periph_TIMER_Defines Defines
  * @{
  */

/** @defgroup Periph_TIMER_TIMER_STATUS_Bits TIMER_STATUS
  * @{
  */

#define TIMER_STATUS_CNT_ZERO_EVENT_Pos         0
#define TIMER_STATUS_CNT_ZERO_EVENT             ((uint32_t)0x00000001)

#define TIMER_STATUS_CNT_ARR_EVENT_Pos          1
#define TIMER_STATUS_CNT_ARR_EVENT              ((uint32_t)0x00000002)

#define TIMER_STATUS_ETR_RE_EVENT_Pos           2
#define TIMER_STATUS_ETR_RE_EVENT               ((uint32_t)0x00000004)

#define TIMER_STATUS_ETR_FE_EVENT_Pos           3
#define TIMER_STATUS_ETR_FE_EVENT               ((uint32_t)0x00000008)

#define TIMER_STATUS_BRK_EVENT_Pos              4
#define TIMER_STATUS_BRK_EVENT                  ((uint32_t)0x00000010)

#define TIMER_STATUS_CCR_CAP_EVENT_Pos          5
#define TIMER_STATUS_CCR_CAP_EVENT_Msk          ((uint32_t)0x000001E0)

#define TIMER_STATUS_CCR_REF_EVENT_Pos          9
#define TIMER_STATUS_CCR_REF_EVENT_Msk          ((uint32_t)0x00001E00)

#define TIMER_STATUS_CCR1_CAP_EVENT_Pos         13
#define TIMER_STATUS_CCR1_CAP_EVENT_Msk         ((uint32_t)0x0001E000)


/** @} */ /* End of group Periph_TIMER_TIMER_STATUS_Bits */

/** @} */ /* End of group Periph_TIMER_Defines */

/** @defgroup Periph_TIMER_Defines Defines
  * @{
  */

/** @defgroup Periph_TIMER_TIMER_IE_Bits TIMER_IE
  * @{
  */

#define TIMER_IE_CNT_ZERO_EVENT_IE_Pos          0
#define TIMER_IE_CNT_ZERO_EVENT_IE              ((uint32_t)0x00000001)

#define TIMER_IE_CNT_ARR_EVENT_IE_Pos           1
#define TIMER_IE_CNT_ARR_EVENT_IE               ((uint32_t)0x00000002)

#define TIMER_IE_ETR_RE_EVENT_IE_Pos            2
#define TIMER_IE_ETR_RE_EVENT_IE                ((uint32_t)0x00000004)

#define TIMER_IE_ETR_FE_EVENT_IE_Pos            3
#define TIMER_IE_ETR_FE_EVENT_IE                ((uint32_t)0x00000008)

#define TIMER_IE_BRK_EVENT_IE_Pos               4
#define TIMER_IE_BRK_EVENT_IE                   ((uint32_t)0x00000010)

#define TIMER_IE_CCR_CAP_EVENT_IE_Pos           5
#define TIMER_IE_CCR_CAP_EVENT_IE_Msk           ((uint32_t)0x000001E0)

#define TIMER_IE_CCR_REF_EVENT_IE_Pos           9
#define TIMER_IE_CCR_REF_EVENT_IE_Msk           ((uint32_t)0x00001E00)


/** @} */ /* End of group Periph_TIMER_TIMER_IE_Bits */

/** @} */ /* End of group Periph_TIMER_Defines */

/** @defgroup Periph_TIMER_Defines Defines
  * @{
  */

/** @defgroup Periph_TIMER_TIMER_DMA_RE_Bits TIMER_DMA_RE
  * @{
  */

#define TIMER_DMA_RE_CNT_ZERO_EVENT_RE_Pos      0
#define TIMER_DMA_RE_CNT_ZERO_EVENT_RE          ((uint32_t)0x00000001)

#define TIMER_DMA_RE_CNT_ARR_EVENT_RE_Pos       1
#define TIMER_DMA_RE_CNT_ARR_EVENT_RE           ((uint32_t)0x00000002)

#define TIMER_DMA_RE_ETR_RE_EVENT_RE_Pos        2
#define TIMER_DMA_RE_ETR_RE_EVENT_RE            ((uint32_t)0x00000004)

#define TIMER_DMA_RE_ETR_FE_EVENT_RE_Pos        3
#define TIMER_DMA_RE_ETR_FE_EVENT_RE            ((uint32_t)0x00000008)

#define TIMER_DMA_RE_BRK_EVENT_RE_Pos           4
#define TIMER_DMA_RE_BRK_EVENT_RE               ((uint32_t)0x00000010)

#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_Pos       5
#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_Msk       ((uint32_t)0x000001E0)

#define TIMER_DMA_RE_CCR_REF_EVENT_RE_Pos       9
#define TIMER_DMA_RE_CCR_REF_EVENT_RE_Msk       ((uint32_t)0x00001E00)


/** @} */ /* End of group Periph_TIMER_TIMER_DMA_RE_Bits */

/** @} */ /* End of group Periph_TIMER_Defines */

/** @defgroup Periph_TIMER_Defines Defines
  * @{
  */

/** @defgroup Periph_TIMER_TIMER_CH_CNTRL2_Bits TIMER_CH_CNTRL2
  * @{
  */

#define TIMER_CH_CNTRL2_CHSEL1_Pos              0
#define TIMER_CH_CNTRL2_CHSEL1_Msk              ((uint32_t)0x00000003)

#define TIMER_CH_CNTRL2_CCR1_EN_Pos             2
#define TIMER_CH_CNTRL2_CCR1_EN                 ((uint32_t)0x00000004)

#define TIMER_CH_CNTRL2_CCRRLD_Pos              3
#define TIMER_CH_CNTRL2_CCRRLD                  ((uint32_t)0x00000008)


/** @} */ /* End of group Periph_TIMER_TIMER_CH_CNTRL2_Bits */

/** @} */ /* End of group Periph_TIMER_Defines */

/** @} */ /* End of group Periph_TIMER */

/** @} */ /* End of group __1986BE9x_Peripheral_Units */

/** @} */ /* End of group __CMSIS */

#endif /* __1986BE9X_TIMER_DEFS_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_timer_defs.h */
