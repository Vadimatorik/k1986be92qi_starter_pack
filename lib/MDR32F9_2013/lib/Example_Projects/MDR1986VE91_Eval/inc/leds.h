/**
  ******************************************************************************
  * @file    leds.h
  * @author  Phyton Application Team
  * @version V3.0.0
  * @date    09.09.2011
  * @brief   This file contains all the functions prototypes for the LEDs
  *          utilities.
  ******************************************************************************
  * <br><br>
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, PHYTON SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 Phyton</center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LEDS_H
#define __LEDS_H

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_config.h"
#include <MDR32Fx.h>
#include "types.h"
#include "MDR32F9Qx_board.h"

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
  * @{
  */

/** @defgroup LEDs_Control LEDs Control
  * @{
  */

/** @defgroup LEDs_Exported_Constants LEDs Exported Constants
  * @{
  */

#if defined (USE_MDR32F9Q1_Rev0) || defined (USE_MDR32F9Q1_Rev1)
#define LEDs_PORT       MDR_PORTD                          /*!< LEDs port for MDR32F9Q1 evaluation board */
#define LEDs_PINs       (PORT_Pin_10 | PORT_Pin_11 | \
                         PORT_Pin_12 | PORT_Pin_13 | \
                         PORT_Pin_14)                  /*!< LEDs pins for MDR32F9Q1 evaluation board */
#define NUM_LEDs        5                              /*!< Number of LEDs on MDR32F9Q1 evaluation board */
#define LEDs_OFS        10                             /*!< Offset of first LED pin in the port (for MDR32F9Q1 evaluation board) */

#elif defined (USE_MDR32F9Q2_Rev0) || defined (USE_MDR32F9Q2_Rev1)
#define LEDs_PORT       MDR_PORTC
#define LEDs_PINs       (PORT_Pin_0 | PORT_Pin_1)
#define NUM_LEDs        2
#define LEDs_OFS        0

#elif defined (USE_MDR32F9Q3_Rev0)
#define LEDs_PORT       MDR_PORTF
#define LEDs_PINs       (PORT_Pin_0 | PORT_Pin_1)
#define NUM_LEDs        2
#define LEDs_OFS        0

#elif defined (USE_MDR32F9Q3_Rev1)
#define LEDs_PORT       MDR_PORTD
#define LEDs_PINs        (PORT_Pin_0 | PORT_Pin_1)
#define NUM_LEDs        2
#define LEDs_OFS        0

#endif

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

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

#endif /* __LEDS_H */

/******************* (C) COPYRIGHT 2011 Phyton *********************************
*
* END OF FILE leds.h */

