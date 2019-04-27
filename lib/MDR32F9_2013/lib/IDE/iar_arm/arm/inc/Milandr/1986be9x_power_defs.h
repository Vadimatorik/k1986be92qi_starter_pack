/**
  ******************************************************************************
  * @file    1986BE9x_power_defs.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    24/09/2010
  * @brief   This file contains all the Special Function Registers definitions
  *          for the POWER peripheral unit used in the Milandr 1986BE9x
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
  * FILE 1986BE9x_power_defs.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9X_POWER_DEFS_H
#define __1986BE9X_POWER_DEFS_H

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @addtogroup __1986BE9x_Peripheral_Units 1986BE9x Peripheral Units
  * @{
  */

/** @defgroup Periph_POWER POWER
  * @{
  */

/** @defgroup Periph_POWER_Data_Structures Data Structures
  * @{
  */

/** @defgroup Periph_POWER_TypeDef POWER_TypeDef
  * @{
  */

typedef struct
{
  __IO uint32_t PVDCS;
}POWER_TypeDef;

/** @} */ /* End of group Periph_POWER_TypeDef */

/** @} */ /* End of group Periph_POWER_Data_Structures */

/** @defgroup Periph_POWER_Defines Defines
  * @{
  */

/** @defgroup Periph_POWER_POWER_PVDCS_Bits POWER_PVDCS
  * @{
  */

#define POWER_PVDCS_PVDEN_Pos                   0
#define POWER_PVDCS_PVDEN                       ((uint32_t)0x00000001)

#define POWER_PVDCS_PBLS_Pos                    1
#define POWER_PVDCS_PBLS_Msk                    ((uint32_t)0x00000006)

#define POWER_PVDCS_PLS_Pos                     3
#define POWER_PVDCS_PLS_Msk                     ((uint32_t)0x00000038)

#define POWER_PVDCS_PVBD_Pos                    6
#define POWER_PVDCS_PVBD                        ((uint32_t)0x00000040)

#define POWER_PVDCS_PVD_Pos                     7
#define POWER_PVDCS_PVD                         ((uint32_t)0x00000080)

#define POWER_PVDCS_IEPVBD_Pos                  8
#define POWER_PVDCS_IEPVBD                      ((uint32_t)0x00000100)

#define POWER_PVDCS_IEPVD_Pos                   9
#define POWER_PVDCS_IEPVD                       ((uint32_t)0x00000200)

#define POWER_PVDCS_INVB_Pos                    10
#define POWER_PVDCS_INVB                        ((uint32_t)0x00000400)

#define POWER_PVDCS_INV_Pos                     11
#define POWER_PVDCS_INV                         ((uint32_t)0x00000800)


/** @} */ /* End of group Periph_POWER_POWER_PVDCS_Bits */

/** @} */ /* End of group Periph_POWER_Defines */

/** @} */ /* End of group Periph_POWER */

/** @} */ /* End of group __1986BE9x_Peripheral_Units */

/** @} */ /* End of group __CMSIS */

#endif /* __1986BE9X_POWER_DEFS_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_power_defs.h */
