/**
  ******************************************************************************
  * @file    joystick.h
  * @author  Milandr Application Team
  * @version V3.0.0
  * @date    09.09.2013
  * @brief   This file contains all the functions prototypes for the Joystick driver.
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
#ifndef __JOYSTICK_H
#define __JOYSTICK_H

/* Includes ------------------------------------------------------------------*/
#include <MDR32F9Qx_config.h>
#include "types.h"
#include "MDR32F9Qx_board.h"

/** @addtogroup __MDR1986VE1T_Eval_Demo MDR1986VE1T Demonstration Example
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
  BACK		 = 5,
  NOKEY      = 6,
  MULTIPLE   = 7,
  NUM_KEY_CODES
}KeyCode;

/** @} */ /* End of group Joystick_Exported_Types */

/** @defgroup Joystick_Exported_Constants Joystick Exported Constants
  * @{
  */

/* Joystick control port pins definitions */


#define SEL_PORT           MDR_PORTE     /*!< SEL key port for MDR1986VE1T evaluation board */
#define SEL_PIN            PORT_Pin_9    /*!< SEL key pin for MDR1986VE1T evaluation board */
#define UP_PORT            MDR_PORTE     /*!< UP key port for MDR1986VE1T evaluation board */
#define UP_PIN             PORT_Pin_8    /*!< UP key pin for MDR1986VE1T evaluation board */
#define DOWN_PORT          MDR_PORTE     /*!< DOWN key port for MDR1986VE1T evaluation board */
#define DOWN_PIN           PORT_Pin_15   /*!< DOWN key pin for MDR1986VE1T evaluation board */
#define LEFT_PORT          MDR_PORTE     /*!< LEFT key port for MDR1986VE1T evaluation board */
#define LEFT_PIN           PORT_Pin_10   /*!< LEFT key pin for MDR1986VE1T evaluation board */
#define RIGHT_PORT         MDR_PORTE     /*!< RIGHT key port for MDR1986VE1T evaluation board */
#define RIGHT_PIN          PORT_Pin_5    /*!< RIGHT key pin for MDR1986VE1T evaluation board */
#define BACK_PORT	       MDR_PORTE	 /*!< BACK key port for MDR1986VE1T evaluation board */
#define BACK_Pin		   PORT_Pin_11	 /*!< BACK key pin for MDR1986VE1T evaluation board */

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

/** @} */ /* End of group __MDR1986VE1T_Eval_Demo */

#endif /* __JOYSTICK_H */

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE joystick.h */

