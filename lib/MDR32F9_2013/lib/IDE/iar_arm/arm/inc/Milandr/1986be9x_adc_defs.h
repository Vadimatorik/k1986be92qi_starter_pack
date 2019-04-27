/**
  ******************************************************************************
  * @file    1986BE9x_adc_defs.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    24/09/2010
  * @brief   This file contains all the Special Function Registers definitions
  *          for the ADC peripheral unit used in the Milandr 1986BE9x
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
  * FILE 1986BE9x_adc_defs.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9X_ADC_DEFS_H
#define __1986BE9X_ADC_DEFS_H

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @addtogroup __1986BE9x_Peripheral_Units 1986BE9x Peripheral Units
  * @{
  */

/** @defgroup Periph_ADC ADC
  * @{
  */

/** @defgroup Periph_ADC_Data_Structures Data Structures
  * @{
  */

/** @defgroup Periph_ADC_TypeDef ADC_TypeDef
  * @{
  */

typedef struct
{
  __IO uint32_t ADC1_CFG;
  __IO uint32_t ADC2_CFG;
  __IO uint32_t ADC1_H_LEVEL;
  __IO uint32_t ADC2_H_LEVEL;
  __IO uint32_t ADC1_L_LEVEL;
  __IO uint32_t ADC2_L_LEVEL;
  __IO uint32_t ADC1_RESULT;
  __IO uint32_t ADC2_RESULT;
  __IO uint32_t ADC1_STATUS;
  __IO uint32_t ADC2_STATUS;
  __IO uint32_t ADC1_CHSEL;
  __IO uint32_t ADC2_CHSEL;
}ADC_TypeDef;

/** @} */ /* End of group Periph_ADC_TypeDef */

/** @} */ /* End of group Periph_ADC_Data_Structures */

/** @defgroup Periph_ADC_Defines Defines
  * @{
  */

/** @defgroup Periph_ADC_ADC1_CFG_Bits ADC1_CFG
  * @{
  */

#define ADC1_CFG_Cfg_REG_ADON_Pos               0
#define ADC1_CFG_Cfg_REG_ADON                   ((uint32_t)0x00000001)

#define ADC1_CFG_Cfg_REG_GO_Pos                 1
#define ADC1_CFG_Cfg_REG_GO                     ((uint32_t)0x00000002)

#define ADC1_CFG_Cfg_REG_CLKS_Pos               2
#define ADC1_CFG_Cfg_REG_CLKS                   ((uint32_t)0x00000004)

#define ADC1_CFG_Cfg_REG_SAMPLE_Pos             3
#define ADC1_CFG_Cfg_REG_SAMPLE                 ((uint32_t)0x00000008)

#define ADC1_CFG_Cfg_REG_CHS_Pos                4
#define ADC1_CFG_Cfg_REG_CHS_Msk                ((uint32_t)0x000001F0)

#define ADC1_CFG_Cfg_REG_CHCH_Pos               9
#define ADC1_CFG_Cfg_REG_CHCH                   ((uint32_t)0x00000200)

#define ADC1_CFG_Cfg_REG_RNGC_Pos               10
#define ADC1_CFG_Cfg_REG_RNGC                   ((uint32_t)0x00000400)

#define ADC1_CFG_Cfg_M_REF_Pos                  11
#define ADC1_CFG_Cfg_M_REF                      ((uint32_t)0x00000800)

#define ADC1_CFG_Cfg_REG_DIVCLK_Pos             12
#define ADC1_CFG_Cfg_REG_DIVCLK_Msk             ((uint32_t)0x0000F000)

#define ADC1_CFG_Cfg_Sync_Conver_Pos            16
#define ADC1_CFG_Cfg_Sync_Conver                ((uint32_t)0x00010000)

#define ADC1_CFG_TS_EN_Pos                      17
#define ADC1_CFG_TS_EN                          ((uint32_t)0x00020000)

#define ADC1_CFG_TS_BUF_EN_Pos                  18
#define ADC1_CFG_TS_BUF_EN                      ((uint32_t)0x00040000)

#define ADC1_CFG_SEL_TS_Pos                     19
#define ADC1_CFG_SEL_TS                         ((uint32_t)0x00080000)

#define ADC1_CFG_SEL_VREF_Pos                   20
#define ADC1_CFG_SEL_VREF                       ((uint32_t)0x00100000)

#define ADC1_CFG_TR_Pos                         21
#define ADC1_CFG_TR_Msk                         ((uint32_t)0x01E00000)

#define ADC1_CFG_Delay_Go_Pos                   25
#define ADC1_CFG_Delay_Go_Msk                   ((uint32_t)0x0E000000)

#define ADC1_CFG_Delay_ADC_Pos                  28
#define ADC1_CFG_Delay_ADC_Msk                  ((uint32_t)0xF0000000)


/** @} */ /* End of group Periph_ADC_ADC1_CFG_Bits */

/** @} */ /* End of group Periph_ADC_Defines */

/** @defgroup Periph_ADC_Defines Defines
  * @{
  */

/** @defgroup Periph_ADC_ADC2_CFG_Bits ADC2_CFG
  * @{
  */

#define ADC2_CFG_Cfg_REG_ADON_Pos               0
#define ADC2_CFG_Cfg_REG_ADON                   ((uint32_t)0x00000001)

#define ADC2_CFG_Cfg_REG_GO_Pos                 1
#define ADC2_CFG_Cfg_REG_GO                     ((uint32_t)0x00000002)

#define ADC2_CFG_Cfg_REG_CLKS_Pos               2
#define ADC2_CFG_Cfg_REG_CLKS                   ((uint32_t)0x00000004)

#define ADC2_CFG_Cfg_REG_SAMPLE_Pos             3
#define ADC2_CFG_Cfg_REG_SAMPLE                 ((uint32_t)0x00000008)

#define ADC2_CFG_Cfg_REG_CHS_Pos                4
#define ADC2_CFG_Cfg_REG_CHS_Msk                ((uint32_t)0x000001F0)

#define ADC2_CFG_Cfg_REG_CHCH_Pos               9
#define ADC2_CFG_Cfg_REG_CHCH                   ((uint32_t)0x00000200)

#define ADC2_CFG_Cfg_REG_RNGC_Pos               10
#define ADC2_CFG_Cfg_REG_RNGC                   ((uint32_t)0x00000400)

#define ADC2_CFG_Cfg_M_REF_Pos                  11
#define ADC2_CFG_Cfg_M_REF                      ((uint32_t)0x00000800)

#define ADC2_CFG_Cfg_REG_DIVCLK_Pos             12
#define ADC2_CFG_Cfg_REG_DIVCLK_Msk             ((uint32_t)0x0000F000)

#define ADC2_CFG_ADC1_OP_Pos                    17
#define ADC2_CFG_ADC1_OP                        ((uint32_t)0x00020000)

#define ADC2_CFG_ADC2_OP_Pos                    18
#define ADC2_CFG_ADC2_OP                        ((uint32_t)0x00040000)

#define ADC2_CFG_Delay_Go_Pos                   25
#define ADC2_CFG_Delay_Go_Msk                   ((uint32_t)0x0E000000)


/** @} */ /* End of group Periph_ADC_ADC2_CFG_Bits */

/** @} */ /* End of group Periph_ADC_Defines */

/** @defgroup Periph_ADC_Defines Defines
  * @{
  */

/** @defgroup Periph_ADC_ADC1_RESULT_Bits ADC1_RESULT
  * @{
  */

#define ADC1_RESULT_Pos                         0
#define ADC1_RESULT_Msk                         ((uint32_t)0x00000FFF)

#define ADC1_RESULT_CHANNEL_Pos                 16
#define ADC1_RESULT_CHANNEL_Msk                 ((uint32_t)0x0FFF0000)


/** @} */ /* End of group Periph_ADC_ADC1_RESULT_Bits */

/** @} */ /* End of group Periph_ADC_Defines */

/** @defgroup Periph_ADC_Defines Defines
  * @{
  */

/** @defgroup Periph_ADC_ADC2_RESULT_Bits ADC2_RESULT
  * @{
  */

#define ADC2_RESULT_Pos                         0
#define ADC2_RESULT_Msk                         ((uint32_t)0x00000FFF)

#define ADC2_RESULT_CHANNEL_Pos                 16
#define ADC2_RESULT_CHANNEL_Msk                 ((uint32_t)0x0FFF0000)


/** @} */ /* End of group Periph_ADC_ADC2_RESULT_Bits */

/** @} */ /* End of group Periph_ADC_Defines */

/** @defgroup Periph_ADC_Defines Defines
  * @{
  */

/** @defgroup Periph_ADC_ADC1_STATUS_Bits ADC1_STATUS
  * @{
  */

#define ADC1_STATUS_Flg_REG_OVERWRITE_Pos       0
#define ADC1_STATUS_Flg_REG_OVERWRITE           ((uint32_t)0x00000001)

#define ADC1_STATUS_Flg_REG_AWOIFEN_Pos         1
#define ADC1_STATUS_Flg_REG_AWOIFEN             ((uint32_t)0x00000002)

#define ADC1_STATUS_Flg_REG_EOCIF_Pos           2
#define ADC1_STATUS_Flg_REG_EOCIF               ((uint32_t)0x00000004)

#define ADC1_STATUS_AWOIF_IE_Pos                3
#define ADC1_STATUS_AWOIF_IE                    ((uint32_t)0x00000008)

#define ADC1_STATUS_ECOIF_IE_Pos                4
#define ADC1_STATUS_ECOIF_IE                    ((uint32_t)0x00000010)


/** @} */ /* End of group Periph_ADC_ADC1_STATUS_Bits */

/** @} */ /* End of group Periph_ADC_Defines */

/** @defgroup Periph_ADC_Defines Defines
  * @{
  */

/** @defgroup Periph_ADC_ADC2_STATUS_Bits ADC2_STATUS
  * @{
  */

#define ADC2_STATUS_Flg_REG_OVERWRITE_Pos       0
#define ADC2_STATUS_Flg_REG_OVERWRITE           ((uint32_t)0x00000001)

#define ADC2_STATUS_Flg_REG_AWOIFEN_Pos         1
#define ADC2_STATUS_Flg_REG_AWOIFEN             ((uint32_t)0x00000002)

#define ADC2_STATUS_Flg_REG_EOCIF_Pos           2
#define ADC2_STATUS_Flg_REG_EOCIF               ((uint32_t)0x00000004)

#define ADC2_STATUS_AWOIF_IE_Pos                3
#define ADC2_STATUS_AWOIF_IE                    ((uint32_t)0x00000008)

#define ADC2_STATUS_ECOIF_IE_Pos                4
#define ADC2_STATUS_ECOIF_IE                    ((uint32_t)0x00000010)


/** @} */ /* End of group Periph_ADC_ADC2_STATUS_Bits */

/** @} */ /* End of group Periph_ADC_Defines */

/** @} */ /* End of group Periph_ADC */

/** @} */ /* End of group __1986BE9x_Peripheral_Units */

/** @} */ /* End of group __CMSIS */

#endif /* __1986BE9X_ADC_DEFS_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_adc_defs.h */
