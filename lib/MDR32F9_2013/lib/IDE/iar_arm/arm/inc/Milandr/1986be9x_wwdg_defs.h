/**
  ******************************************************************************
  * @file    1986BE9x_wwdg_defs.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    24/09/2010
  * @brief   This file contains all the Special Function Registers definitions
  *          for the WWDG peripheral unit used in the Milandr 1986BE9x
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
  * FILE 1986BE9x_wwdg_defs.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9X_WWDG_DEFS_H
#define __1986BE9X_WWDG_DEFS_H

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @addtogroup __1986BE9x_Peripheral_Units 1986BE9x Peripheral Units
  * @{
  */

/** @defgroup Periph_WWDG WWDG
  * @{
  */

/** @defgroup Periph_WWDG_Data_Structures Data Structures
  * @{
  */

/** @defgroup Periph_WWDG_TypeDef WWDG_TypeDef
  * @{
  */

typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t CFR;
  __IO uint32_t SR;
}WWDG_TypeDef;

/** @} */ /* End of group Periph_WWDG_TypeDef */

/** @} */ /* End of group Periph_WWDG_Data_Structures */

/** @defgroup Periph_WWDG_Defines Defines
  * @{
  */

/** @defgroup Periph_WWDG_WWDG_CR_Bits WWDG_CR
  * @{
  */

#define WWDG_CR_T_Pos                           0
#define WWDG_CR_T_Msk                           ((uint32_t)0x0000007F)

#define WWDG_CR_WDGA_Pos                        7
#define WWDG_CR_WDGA                            ((uint32_t)0x00000080)


/** @} */ /* End of group Periph_WWDG_WWDG_CR_Bits */

/** @} */ /* End of group Periph_WWDG_Defines */

/** @defgroup Periph_WWDG_Defines Defines
  * @{
  */

/** @defgroup Periph_WWDG_WWDG_CFR_Bits WWDG_CFR
  * @{
  */

#define WWDG_CFR_W_Pos                          0
#define WWDG_CFR_W_Msk                          ((uint32_t)0x0000007F)

#define WWDG_CFR_WGTB_Pos                       7
#define WWDG_CFR_WGTB_Msk                       ((uint32_t)0x00000180)

#define WWDG_CFR_EWI_Pos                        9
#define WWDG_CFR_EWI                            ((uint32_t)0x00000200)


/** @} */ /* End of group Periph_WWDG_WWDG_CFR_Bits */

/** @} */ /* End of group Periph_WWDG_Defines */

/** @} */ /* End of group Periph_WWDG */

/** @} */ /* End of group __1986BE9x_Peripheral_Units */

/** @} */ /* End of group __CMSIS */

#endif /* __1986BE9X_WWDG_DEFS_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_wwdg_defs.h */
