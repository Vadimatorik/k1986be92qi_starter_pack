/**
  ******************************************************************************
  * @file    leds.h
  * @author  Milandr Application Team
  * @version V3.0.0
  * @date    09.09.2013
  * @brief   This file contains all the functions prototypes for the LEDs
  *          utilities.
  ******************************************************************************
  * <br><br>
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, Milandr SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2013 Milandr</center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LEDS_H
#define __LEDS_H

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_config.h"
#include "types.h"
#include "MDR32F9Qx_board.h"

/** @addtogroup __MDR1986VE1T_Eval_Demo MDR1986VE1T Demonstration Example
  * @{
  */

/** @defgroup LEDs_Control LEDs Control
  * @{
  */

/** @defgroup LEDs_Exported_Constants LEDs Exported Constants
  * @{
  */
#define LEDs_PORT       MDR_PORTD                          /*!< LEDs port for MDR1986VE1T evaluation board */
#define LEDs_PINs       (PORT_Pin_7 | PORT_Pin_8 | \
                         PORT_Pin_9 | PORT_Pin_10 | \
                         PORT_Pin_11 | PORT_Pin_12 |\
             PORT_Pin_13 | PORT_Pin_14)                  /*!< LEDs pins for MDR1986VE1T evaluation board */
#define NUM_LEDs        8                              /*!< Number of LEDs on MDR1986VE1T evaluation board */
#define LEDs_OFS        7                             /*!< Offset of first LED pin in the port (for MDR1986VE1T evaluation board) */

/** @} */ /* End of group LEDs_Exported_Constants */

/** @defgroup LEDs_Exported_Macros LEDs Exported Macros
  * @{
  */
/* ROL */
#define __SHLC(val, cnt) ((val << (cnt & 31)) | (val >> ((32 - cnt) & 31)))

/** @} */ /* End of group LEDs_Exported_Macros */

/** @defgroup LEDs_Exported_Variables LEDs Exported Variables
  * @{
  */

extern uint32_t CurrentLights;          /*!< LEDs on mask */

/** @} */ /* End of group LEDs_Exported_Variables */

/** @defgroup LEDs_Exported_Functions LEDs Exported Functions
  * @{
  */

void ShiftLights(void);

/** @} */ /* End of group LEDs_Exported_Functions */

/** @} */ /* End of group LEDs_Control */

/** @} */ /* End of group __MDR1986VE1T_Eval_Demo */

#endif /* __LEDS_H */

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE leds.h */

