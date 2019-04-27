/**
  ******************************************************************************
  * @file    1986BE9x_eeprom_defs.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    24/09/2010
  * @brief   This file contains all the Special Function Registers definitions
  *          for the EEPROM peripheral unit used in the Milandr 1986BE9x
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
  * FILE 1986BE9x_eeprom_defs.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9X_EEPROM_DEFS_H
#define __1986BE9X_EEPROM_DEFS_H

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @addtogroup __1986BE9x_Peripheral_Units 1986BE9x Peripheral Units
  * @{
  */

/** @defgroup Periph_EEPROM EEPROM
  * @{
  */

/** @defgroup Periph_EEPROM_Data_Structures Data Structures
  * @{
  */

/** @defgroup Periph_EEPROM_TypeDef EEPROM_TypeDef
  * @{
  */

typedef struct
{
  __IO uint32_t CMD;
  __IO uint32_t ADR;
  __IO uint32_t DI;
  __IO uint32_t DO;
  __IO uint32_t KEY;
}EEPROM_TypeDef;

/** @} */ /* End of group Periph_EEPROM_TypeDef */

/** @} */ /* End of group Periph_EEPROM_Data_Structures */

/** @defgroup Periph_EEPROM_Defines Defines
  * @{
  */

/** @defgroup Periph_EEPROM_EEPROM_CMD_Bits EEPROM_CMD
  * @{
  */

#define EEPROM_CMD_CON_Pos                      0
#define EEPROM_CMD_CON                          ((uint32_t)0x00000001)

#define EEPROM_CMD_WR_Pos                       1
#define EEPROM_CMD_WR                           ((uint32_t)0x00000002)

#define EEPROM_CMD_RD_Pos                       2
#define EEPROM_CMD_RD                           ((uint32_t)0x00000004)

#define EEPROM_CMD_Delay_Pos                    3
#define EEPROM_CMD_Delay_Msk                    ((uint32_t)0x00000038)

#define EEPROM_CMD_XE_Pos                       6
#define EEPROM_CMD_XE                           ((uint32_t)0x00000040)

#define EEPROM_CMD_YE_Pos                       7
#define EEPROM_CMD_YE                           ((uint32_t)0x00000080)

#define EEPROM_CMD_SE_Pos                       8
#define EEPROM_CMD_SE                           ((uint32_t)0x00000100)

#define EEPROM_CMD_IFREN_Pos                    9
#define EEPROM_CMD_IFREN                        ((uint32_t)0x00000200)

#define EEPROM_CMD_ERASE_Pos                    10
#define EEPROM_CMD_ERASE                        ((uint32_t)0x00000400)

#define EEPROM_CMD_MAS1_Pos                     11
#define EEPROM_CMD_MAS1                         ((uint32_t)0x00000800)

#define EEPROM_CMD_PROG_Pos                     12
#define EEPROM_CMD_PROG                         ((uint32_t)0x00001000)

#define EEPROM_CMD_NVSTR_Pos                    13
#define EEPROM_CMD_NVSTR                        ((uint32_t)0x00002000)


/** @} */ /* End of group Periph_EEPROM_EEPROM_CMD_Bits */

/** @} */ /* End of group Periph_EEPROM_Defines */

/** @} */ /* End of group Periph_EEPROM */

/** @} */ /* End of group __1986BE9x_Peripheral_Units */

/** @} */ /* End of group __CMSIS */

#endif /* __1986BE9X_EEPROM_DEFS_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_eeprom_defs.h */
