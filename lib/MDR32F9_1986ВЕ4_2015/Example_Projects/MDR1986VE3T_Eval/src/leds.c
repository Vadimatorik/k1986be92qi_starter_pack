/**
  ******************************************************************************
  * @file    leds.c
  * @author  Milandr Application Team
  * @version V3.0.0
  * @date    10.09.2013
  * @brief   This file provides the LEDs utilities.
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

/* Includes ------------------------------------------------------------------*/
#include <MDR32F9Qx_port.h>
#include "leds.h"

/** @addtogroup __MDR1986VE3_Eval_Demo MDR1986VE3 Demonstration Example
  * @{
  */

/** @addtogroup LEDs_Control LEDs Control
  * @{
  */

/** @defgroup LEDs_Variables LEDs Variables
  * @{
  */

uint32_t CurrentLights;         /*!< LEDs on mask */

/** @} */ /* End of group LEDs_Variables */

/** @defgroup LEDs_Private_Functions LEDs Private Functions
  * @{
  */

/*******************************************************************************
* Function Name  : ShiftLights
* Description    : Controls LEDs on/off.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ShiftLights(void)
{
  uint32_t ovf;
  uint32_t portdata;

  portdata = PORT_ReadInputData(LEDs_PORT);
  PORT_Write(LEDs_PORT, (portdata & ~LEDs_PINs) | (CurrentLights & LEDs_PINs));
  ovf = (CurrentLights & (1UL << 31)) != 0;
  CurrentLights <<= 1;
  CurrentLights |= ovf;
}

/** @} */ /* End of group LEDs_Private_Functions */

/** @} */ /* End of group LEDs_Control */

/** @} */ /* End of group __MDR1986VE3_Eval_Demo */

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE leds.c */

