/**
  ******************************************************************************
  * @file    joystick.h
  * @author  Phyton Application Team
  * @version V3.0.0
  * @date    09.09.2011
  * @brief   This file contains all the functions prototypes for the Joystick driver.
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
#ifndef __JOYSTICK_H
#define __JOYSTICK_H

/* Includes ------------------------------------------------------------------*/
#include <MDR32Fx.h>
#include "types.h"
#include "MDR32F9Qx_board.h"

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
  * @{
  */

/** @defgroup Joystick_Driver Joystick Driver
  * @{
  */

/** @defgroup Joystick_Exported_Types Joystick Exported Types
  * @{
  */

/* "Key codes" */
typedef enum
{
  SEL        = 0,
  UP         = 1,
  DOWN       = 2,
  LEFT       = 3,
  RIGHT      = 4,
  NOKEY      = 5,
  MULTIPLE   = 6,
  NUM_KEY_CODES
}KeyCode;

/** @} */ /* End of group Joystick_Exported_Types */

/** @defgroup Joystick_Exported_Constants Joystick Exported Constants
  * @{
  */

/* Joystick control port pins definitions */

#if defined (USE_MDR32F9Q1_Rev0) || defined (USE_MDR32F9Q1_Rev1)
#define SEL_PORT           MDR_PORTC          /*!< SEL key port for MDR32F9Q1 evaluation board */
#define SEL_PIN            PORT_Pin_10    /*!< SEL key pin for MDR32F9Q1 evaluation board */
#define UP_PORT            MDR_PORTC          /*!< UP key port for MDR32F9Q1 evaluation board */
#define UP_PIN             PORT_Pin_11    /*!< UP key pin for MDR32F9Q1 evaluation board */
#define DOWN_PORT          MDR_PORTC          /*!< DOWN key port for MDR32F9Q1 evaluation board */
#define DOWN_PIN           PORT_Pin_12    /*!< DOWN key pin for MDR32F9Q1 evaluation board */
#define LEFT_PORT          MDR_PORTC          /*!< LEFT key port for MDR32F9Q1 evaluation board */
#define LEFT_PIN           PORT_Pin_13    /*!< LEFT key pin for MDR32F9Q1 evaluation board */
#define RIGHT_PORT         MDR_PORTC          /*!< RIGHT key port for MDR32F9Q1 evaluation board */
#define RIGHT_PIN          PORT_Pin_14    /*!< RIGHT key pin for MDR32F9Q1 evaluation board */

#elif defined (USE_MDR32F9Q2_Rev0)
#define SEL_PORT           MDR_PORTC
#define SEL_PIN            PORT_Pin_2
#define UP_PORT            MDR_PORTD
#define UP_PIN             PORT_Pin_5
#define DOWN_PORT          MDR_PORTE
#define DOWN_PIN           PORT_Pin_1
#define LEFT_PORT          MDR_PORTE
#define LEFT_PIN           PORT_Pin_3
#define RIGHT_PORT         MDR_PORTF
#define RIGHT_PIN          PORT_Pin_6

#elif defined (USE_MDR32F9Q2_Rev1)
#define SEL_PORT           MDR_PORTC
#define SEL_PIN            PORT_Pin_2
#define UP_PORT            MDR_PORTB
#define UP_PIN             PORT_Pin_5
#define DOWN_PORT          MDR_PORTE
#define DOWN_PIN           PORT_Pin_1
#define LEFT_PORT          MDR_PORTE
#define LEFT_PIN           PORT_Pin_3
#define RIGHT_PORT         MDR_PORTB
#define RIGHT_PIN          PORT_Pin_6

#elif defined (USE_MDR32F9Q3_Rev0) || defined (USE_MDR32F9Q3_Rev1)
#define SEL_PORT           MDR_PORTC
#define SEL_PIN            PORT_Pin_0
#define UP_PORT            MDR_PORTD
#define UP_PIN             PORT_Pin_0
#define DOWN_PORT          MDR_PORTD
#define DOWN_PIN           PORT_Pin_1
#define LEFT_PORT          MDR_PORTE
#define LEFT_PIN           PORT_Pin_3
#define RIGHT_PORT         MDR_PORTE
#define RIGHT_PIN          PORT_Pin_6

#endif

/** @} */ /* End of group Joystick_Exported_Constants */

/** @defgroup Joystick_Exported_Macros Joystick Exported Macros
  * @{
  */

#define KEY_PRESSED(x)              (GetKey() == x)
#define WAIT_UNTIL_KEY_PRESSED(x)   while(!KEY_PRESSED(x)){}
#define WAIT_UNTIL_KEY_RELEASED(x)  while(KEY_PRESSED(x)){}
#define WAIT_UNTIL_ANY_KEY          while(GetKey() == NOKEY){}

/** @} */ /* End of group Joystick_Exported_Macros */

/** @defgroup Joystick_Exported_Functions Joystick Exported Functions
  * @{
  */

KeyCode GetKey(void);

/** @} */ /* End of group Joystick_Exported_Functions */

/** @} */ /* End of group Joystick_Driver */

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

#endif /* __JOYSTICK_H */

/******************* (C) COPYRIGHT 2011 Phyton *********************************
*
* END OF FILE joystick.h */

