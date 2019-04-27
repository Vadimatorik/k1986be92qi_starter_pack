/**
  ******************************************************************************
  * @file    1986BE9x_port_defs.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    24/09/2010
  * @brief   This file contains all the Special Function Registers definitions
  *          for the PORT peripheral unit used in the Milandr 1986BE9x
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
  * FILE 1986BE9x_port_defs.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9X_PORT_DEFS_H
#define __1986BE9X_PORT_DEFS_H

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @addtogroup __1986BE9x_Peripheral_Units 1986BE9x Peripheral Units
  * @{
  */

/** @defgroup Periph_PORT PORT
  * @{
  */

/** @defgroup Periph_PORT_Data_Structures Data Structures
  * @{
  */

/** @defgroup Periph_PORT_TypeDef PORT_TypeDef
  * @{
  */

typedef struct
{
  __IO uint32_t RXTX;
  __IO uint32_t OE;
  __IO uint32_t FUNC;
  __IO uint32_t ANALOG;
  __IO uint32_t PULL;
  __IO uint32_t PD;
  __IO uint32_t PWR;
  __IO uint32_t GFEN;
}PORT_TypeDef;

/** @} */ /* End of group Periph_PORT_TypeDef */

/** @} */ /* End of group Periph_PORT_Data_Structures */

/** @defgroup Periph_PORT_Defines Defines
  * @{
  */

/** @defgroup Periph_PORT_PORT_FUNC_Bits PORT_FUNC
  * @{
  */

#define PORT_FUNC_MODE0_Pos                     0
#define PORT_FUNC_MODE0_Msk                     ((uint32_t)0x00000003)

#define PORT_FUNC_MODE1_Pos                     2
#define PORT_FUNC_MODE1_Msk                     ((uint32_t)0x0000000C)

#define PORT_FUNC_MODE2_Pos                     4
#define PORT_FUNC_MODE2_Msk                     ((uint32_t)0x00000030)

#define PORT_FUNC_MODE3_Pos                     6
#define PORT_FUNC_MODE3_Msk                     ((uint32_t)0x000000C0)

#define PORT_FUNC_MODE4_Pos                     8
#define PORT_FUNC_MODE4_Msk                     ((uint32_t)0x00000300)

#define PORT_FUNC_MODE5_Pos                     10
#define PORT_FUNC_MODE5_Msk                     ((uint32_t)0x00000C00)

#define PORT_FUNC_MODE6_Pos                     12
#define PORT_FUNC_MODE6_Msk                     ((uint32_t)0x00003000)

#define PORT_FUNC_MODE7_Pos                     14
#define PORT_FUNC_MODE7_Msk                     ((uint32_t)0x0000C000)

#define PORT_FUNC_MODE8_Pos                     16
#define PORT_FUNC_MODE8_Msk                     ((uint32_t)0x00030000)

#define PORT_FUNC_MODE9_Pos                     18
#define PORT_FUNC_MODE9_Msk                     ((uint32_t)0x000C0000)

#define PORT_FUNC_MODE10_Pos                    20
#define PORT_FUNC_MODE10_Msk                    ((uint32_t)0x00300000)

#define PORT_FUNC_MODE11_Pos                    22
#define PORT_FUNC_MODE11_Msk                    ((uint32_t)0x00C00000)

#define PORT_FUNC_MODE12_Pos                    24
#define PORT_FUNC_MODE12_Msk                    ((uint32_t)0x03000000)

#define PORT_FUNC_MODE13_Pos                    26
#define PORT_FUNC_MODE13_Msk                    ((uint32_t)0x0C000000)

#define PORT_FUNC_MODE14_Pos                    28
#define PORT_FUNC_MODE14_Msk                    ((uint32_t)0x30000000)

#define PORT_FUNC_MODE15_Pos                    30
#define PORT_FUNC_MODE15_Msk                    ((uint32_t)0xC0000000)


/** @} */ /* End of group Periph_PORT_PORT_FUNC_Bits */

/** @} */ /* End of group Periph_PORT_Defines */

/** @defgroup Periph_PORT_Defines Defines
  * @{
  */

/** @defgroup Periph_PORT_PORT_PWR_Bits PORT_PWR
  * @{
  */

#define PORT_PWR_PWR0_Pos                       0
#define PORT_PWR_PWR0_Msk                       ((uint32_t)0x00000003)

#define PORT_PWR_PWR1_Pos                       2
#define PORT_PWR_PWR1_Msk                       ((uint32_t)0x0000000C)

#define PORT_PWR_PWR2_Pos                       4
#define PORT_PWR_PWR2_Msk                       ((uint32_t)0x00000030)

#define PORT_PWR_PWR3_Pos                       6
#define PORT_PWR_PWR3_Msk                       ((uint32_t)0x000000C0)

#define PORT_PWR_PWR4_Pos                       8
#define PORT_PWR_PWR4_Msk                       ((uint32_t)0x00000300)

#define PORT_PWR_PWR5_Pos                       10
#define PORT_PWR_PWR5_Msk                       ((uint32_t)0x00000C00)

#define PORT_PWR_PWR6_Pos                       12
#define PORT_PWR_PWR6_Msk                       ((uint32_t)0x00003000)

#define PORT_PWR_PWR7_Pos                       14
#define PORT_PWR_PWR7_Msk                       ((uint32_t)0x0000C000)

#define PORT_PWR_PWR8_Pos                       16
#define PORT_PWR_PWR8_Msk                       ((uint32_t)0x00030000)

#define PORT_PWR_PWR9_Pos                       18
#define PORT_PWR_PWR9_Msk                       ((uint32_t)0x000C0000)

#define PORT_PWR_PWR10_Pos                      20
#define PORT_PWR_PWR10_Msk                      ((uint32_t)0x00300000)

#define PORT_PWR_PWR11_Pos                      22
#define PORT_PWR_PWR11_Msk                      ((uint32_t)0x00C00000)

#define PORT_PWR_PWR12_Pos                      24
#define PORT_PWR_PWR12_Msk                      ((uint32_t)0x03000000)

#define PORT_PWR_PWR13_Pos                      26
#define PORT_PWR_PWR13_Msk                      ((uint32_t)0x0C000000)

#define PORT_PWR_PWR14_Pos                      28
#define PORT_PWR_PWR14_Msk                      ((uint32_t)0x30000000)

#define PORT_PWR_PWR15_Pos                      30
#define PORT_PWR_PWR15_Msk                      ((uint32_t)0xC0000000)


/** @} */ /* End of group Periph_PORT_PORT_PWR_Bits */

/** @} */ /* End of group Periph_PORT_Defines */

/** @} */ /* End of group Periph_PORT */

/** @} */ /* End of group __1986BE9x_Peripheral_Units */

/** @} */ /* End of group __CMSIS */

#endif /* __1986BE9X_PORT_DEFS_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_port_defs.h */
