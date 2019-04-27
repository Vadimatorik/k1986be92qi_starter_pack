/**
  ******************************************************************************
  * @file	 MIL_STD_1553_IT_Handler.h
  * @author	 sidorov.a
  * @version {version}
  * @date    03.04.2013
  * @brief   This file contains the user defines and typedef and functions
  * 		 prototypes.
  ******************************************************************************
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2013 Milandr </center></h2>
  ******************************************************************************
  * FILE MIL_STD_1553_IT_Handler.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MIL_STD_1553_IT_HANDLER_H_
#define MIL_STD_1553_IT_HANDLER_H_

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR1986VE1T_EVAL MDR1986VE1T Opora Evaluation Board
  * @{
  */

/** @addtogroup MIL_STD_1553_Bus_Controller_1T MIL_STD_1553 Bus Controller
 *  @{
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_mil_std_1553.h"



/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
void My_MIL_STD_1553_Handler( MDR_MIL_STD_1553_TypeDef * MIL_STD_1553x );

/** @} */ /* End of MIL_STD_1553_Bus_Controller */

/** @} */ /* End of group ____MDR1986VE1T_EVAL MDR1986VE1T Opora Evaluation Board */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */

#endif /* MIL_STD_1553_IT_HANDLER_H_ */

/******************* (C) COPYRIGHT 2013 Milandr ********************************
*
* END OF FILE MIL_STD_1553_IT_Handler.h */
