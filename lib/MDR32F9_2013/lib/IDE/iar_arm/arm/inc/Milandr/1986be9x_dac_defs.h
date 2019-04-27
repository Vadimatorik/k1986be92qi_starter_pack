/**
  ******************************************************************************
  * @file    1986BE9x_dac_defs.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    24/09/2010
  * @brief   This file contains all the Special Function Registers definitions
  *          for the DAC peripheral unit used in the Milandr 1986BE9x
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
  * FILE 1986BE9x_dac_defs.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9X_DAC_DEFS_H
#define __1986BE9X_DAC_DEFS_H

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @addtogroup __1986BE9x_Peripheral_Units 1986BE9x Peripheral Units
  * @{
  */

/** @defgroup Periph_DAC DAC
  * @{
  */

/** @defgroup Periph_DAC_Data_Structures Data Structures
  * @{
  */

/** @defgroup Periph_DAC_TypeDef DAC_TypeDef
  * @{
  */

typedef struct
{
  __IO uint32_t CFG;
  __IO uint32_t DAC1_DATA;
  __IO uint32_t DAC2_DATA;
}DAC_TypeDef;

/** @} */ /* End of group Periph_DAC_TypeDef */

/** @} */ /* End of group Periph_DAC_Data_Structures */

/** @defgroup Periph_DAC_Defines Defines
  * @{
  */

/** @defgroup Periph_DAC_DAC_CFG_Bits DAC_CFG
  * @{
  */

#define DAC_CFG_Cfg_M_REF0_Pos                  0
#define DAC_CFG_Cfg_M_REF0                      ((uint32_t)0x00000001)

#define DAC_CFG_Cfg_M_REF1_Pos                  1
#define DAC_CFG_Cfg_M_REF1                      ((uint32_t)0x00000002)

#define DAC_CFG_Cfg_ON_DAC0_Pos                 2
#define DAC_CFG_Cfg_ON_DAC0                     ((uint32_t)0x00000004)

#define DAC_CFG_Cfg_ON_DAC1_Pos                 3
#define DAC_CFG_Cfg_ON_DAC1                     ((uint32_t)0x00000008)

#define DAC_CFG_Cfg_SYNC_A_Pos                  4
#define DAC_CFG_Cfg_SYNC_A                      ((uint32_t)0x00000010)


/** @} */ /* End of group Periph_DAC_DAC_CFG_Bits */

/** @} */ /* End of group Periph_DAC_Defines */

/** @defgroup Periph_DAC_Defines Defines
  * @{
  */

/** @defgroup Periph_DAC_DAC1_DATA_Bits DAC1_DATA
  * @{
  */

#define DAC1_DATA_DAC0DATA_Pos                  0
#define DAC1_DATA_DAC0DATA_Msk                  ((uint32_t)0x00000FFF)

#define DAC1_DATA_DAC1DATA_Pos                  16
#define DAC1_DATA_DAC1DATA_Msk                  ((uint32_t)0x0FFF0000)


/** @} */ /* End of group Periph_DAC_DAC1_DATA_Bits */

/** @} */ /* End of group Periph_DAC_Defines */

/** @defgroup Periph_DAC_Defines Defines
  * @{
  */

/** @defgroup Periph_DAC_DAC2_DATA_Bits DAC2_DATA
  * @{
  */

#define DAC2_DATA_DAC1DATA_Pos                  0
#define DAC2_DATA_DAC1DATA_Msk                  ((uint32_t)0x00000FFF)

#define DAC2_DATA_DAC0DATA_Pos                  16
#define DAC2_DATA_DAC0DATA_Msk                  ((uint32_t)0x0FFF0000)


/** @} */ /* End of group Periph_DAC_DAC2_DATA_Bits */

/** @} */ /* End of group Periph_DAC_Defines */

/** @} */ /* End of group Periph_DAC */

/** @} */ /* End of group __1986BE9x_Peripheral_Units */

/** @} */ /* End of group __CMSIS */

#endif /* __1986BE9X_DAC_DEFS_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_dac_defs.h */
