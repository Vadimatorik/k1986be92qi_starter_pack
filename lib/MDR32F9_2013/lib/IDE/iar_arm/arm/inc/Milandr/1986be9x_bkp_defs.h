/**
  ******************************************************************************
  * @file    1986BE9x_bkp_defs.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    24/09/2010
  * @brief   This file contains all the Special Function Registers definitions
  *          for the BKP peripheral unit used in the Milandr 1986BE9x
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
  * FILE 1986BE9x_bkp_defs.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9X_BKP_DEFS_H
#define __1986BE9X_BKP_DEFS_H

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @addtogroup __1986BE9x_Peripheral_Units 1986BE9x Peripheral Units
  * @{
  */

/** @defgroup Periph_BKP BKP
  * @{
  */

/** @defgroup Periph_BKP_Data_Structures Data Structures
  * @{
  */

/** @defgroup Periph_BKP_TypeDef BKP_TypeDef
  * @{
  */

typedef struct
{
  __IO uint32_t REG_00;
  __IO uint32_t REG_01;
  __IO uint32_t REG_02;
  __IO uint32_t REG_03;
  __IO uint32_t REG_04;
  __IO uint32_t REG_05;
  __IO uint32_t REG_06;
  __IO uint32_t REG_07;
  __IO uint32_t REG_08;
  __IO uint32_t REG_09;
  __IO uint32_t REG_0A;
  __IO uint32_t REG_0B;
  __IO uint32_t REG_0C;
  __IO uint32_t REG_0D;
  __IO uint32_t REG_0E;
  __IO uint32_t REG_0F;
  __IO uint32_t RTC_CNT;
  __IO uint32_t RTC_DIV;
  __IO uint32_t RTC_PRL;
  __IO uint32_t RTC_ALRM;
  __IO uint32_t RTC_CS;
}BKP_TypeDef;

/** @} */ /* End of group Periph_BKP_TypeDef */

/** @} */ /* End of group Periph_BKP_Data_Structures */

/** @defgroup Periph_BKP_Defines Defines
  * @{
  */

/** @defgroup Periph_BKP_BKP_REG_0E_Bits BKP_REG_0E
  * @{
  */

#define BKP_REG_0E_LOW_Pos                      0
#define BKP_REG_0E_LOW_Msk                      ((uint32_t)0x00000007)

#define BKP_REG_0E_SelectRI_Pos                 3
#define BKP_REG_0E_SelectRI_Msk                 ((uint32_t)0x00000038)

#define BKP_REG_0E_JTAGA_Pos                    6
#define BKP_REG_0E_JTAGA                        ((uint32_t)0x00000040)

#define BKP_REG_0E_JTAGB_Pos                    7
#define BKP_REG_0E_JTAGB                        ((uint32_t)0x00000080)

#define BKP_REG_0E_Trim_Pos                     8
#define BKP_REG_0E_Trim_Msk                     ((uint32_t)0x00000700)

#define BKP_REG_0E_FPOR_Pos                     11
#define BKP_REG_0E_FPOR                         ((uint32_t)0x00000800)

#define BKP_REG_0E_BKP_REG_Pos                  12
#define BKP_REG_0E_BKP_REG_Msk                  ((uint32_t)0xFFFFF000)


/** @} */ /* End of group Periph_BKP_BKP_REG_0E_Bits */

/** @} */ /* End of group Periph_BKP_Defines */

/** @defgroup Periph_BKP_Defines Defines
  * @{
  */

/** @defgroup Periph_BKP_BKP_REG_0F_Bits BKP_REG_0F
  * @{
  */

#define BKP_REG_0F_LSE_ON_Pos                   0
#define BKP_REG_0F_LSE_ON                       ((uint32_t)0x00000001)

#define BKP_REG_0F_LSE_BYP_Pos                  1
#define BKP_REG_0F_LSE_BYP                      ((uint32_t)0x00000002)

#define BKP_REG_0F_RTC_SEL_Pos                  2
#define BKP_REG_0F_RTC_SEL_Msk                  ((uint32_t)0x0000000C)

#define BKP_REG_0F_RTC_EN_Pos                   4
#define BKP_REG_0F_RTC_EN                       ((uint32_t)0x00000010)

#define BKP_REG_0F_CAL_Pos                      5
#define BKP_REG_0F_CAL_Msk                      ((uint32_t)0x00001FE0)

#define BKP_REG_0F_LSE_RDY_Pos                  13
#define BKP_REG_0F_LSE_RDY                      ((uint32_t)0x00002000)

#define BKP_REG_0F_BKP_REG_Pos                  14
#define BKP_REG_0F_BKP_REG                      ((uint32_t)0x00004000)

#define BKP_REG_0F_LSI_ON_Pos                   15
#define BKP_REG_0F_LSI_ON                       ((uint32_t)0x00008000)

#define BKP_REG_0F_LSI_TRIM_Pos                 16
#define BKP_REG_0F_LSI_TRIM_Msk                 ((uint32_t)0x001F0000)

#define BKP_REG_0F_LSI_RDY_Pos                  21
#define BKP_REG_0F_LSI_RDY                      ((uint32_t)0x00200000)

#define BKP_REG_0F_HSI_ON_Pos                   22
#define BKP_REG_0F_HSI_ON                       ((uint32_t)0x00400000)

#define BKP_REG_0F_HSI_RDY_Pos                  23
#define BKP_REG_0F_HSI_RDY                      ((uint32_t)0x00800000)

#define BKP_REG_0F_HSI_TRIM_Pos                 24
#define BKP_REG_0F_HSI_TRIM_Msk                 ((uint32_t)0x3F000000)

#define BKP_REG_0F_STANDBY_Pos                  30
#define BKP_REG_0F_STANDBY                      ((uint32_t)0x40000000)

#define BKP_REG_0F_RTC_RESET_Pos                31
#define BKP_REG_0F_RTC_RESET                    ((uint32_t)0x80000000)


/** @} */ /* End of group Periph_BKP_BKP_REG_0F_Bits */

/** @} */ /* End of group Periph_BKP_Defines */

/** @defgroup Periph_BKP_Defines Defines
  * @{
  */

/** @defgroup Periph_BKP_BKP_RTC_CS_Bits BKP_RTC_CS
  * @{
  */

#define BKP_RTC_CS_OWF_Pos                      0
#define BKP_RTC_CS_OWF                          ((uint32_t)0x00000001)

#define BKP_RTC_CS_SECF_Pos                     1
#define BKP_RTC_CS_SECF                         ((uint32_t)0x00000002)

#define BKP_RTC_CS_ALRF_Pos                     2
#define BKP_RTC_CS_ALRF                         ((uint32_t)0x00000004)

#define BKP_RTC_CS_OWF_IE_Pos                   3
#define BKP_RTC_CS_OWF_IE                       ((uint32_t)0x00000008)

#define BKP_RTC_CS_SECF_IE_Pos                  4
#define BKP_RTC_CS_SECF_IE                      ((uint32_t)0x00000010)

#define BKP_RTC_CS_ALRF_IE_Pos                  5
#define BKP_RTC_CS_ALRF_IE                      ((uint32_t)0x00000020)

#define BKP_RTC_CS_WEC_Pos                      6
#define BKP_RTC_CS_WEC                          ((uint32_t)0x00000040)


/** @} */ /* End of group Periph_BKP_BKP_RTC_CS_Bits */

/** @} */ /* End of group Periph_BKP_Defines */

/** @} */ /* End of group Periph_BKP */

/** @} */ /* End of group __1986BE9x_Peripheral_Units */

/** @} */ /* End of group __CMSIS */

#endif /* __1986BE9X_BKP_DEFS_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_bkp_defs.h */
