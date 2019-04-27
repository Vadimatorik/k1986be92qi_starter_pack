/**
  ******************************************************************************
  * @file    systick.c
  * @author  Milandr Application Team
  * @version V2.0.0
  * @date    10.09.2010
  * @brief   This file contains all the low-level utilities for work with
  *          the system timer.
  ******************************************************************************
  * <br><br>
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, Milandr SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VE3_it.h"

/** @addtogroup __MDR1986VE3_Eval_Demo MDR1986VE3 Demonstration Example
  * @{
  */

/** @addtogroup Interrupt_Service_Routines Interrupt Service Routines
  * @{
  */

/** @addtogroup Systick_Routines Systick Routines
  * @{
  */

/** @defgroup Systick_Private_Functions Systick Private Functions
  * @{
  */

/*******************************************************************************
* Function Name  : SysTickStart
* Description    : Starts the timer
* Input          : ticks - starting timer value
* Output         : None
* Return         : None
*******************************************************************************/
void SysTickStart(uint32_t ticks)
{
  SysTick->LOAD = ticks;
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | \
                  SysTick_CTRL_CLKSOURCE_Msk;
  NVIC_EnableIRQ(SysTick_IRQn);
}

/*******************************************************************************
* Function Name  : SysTickStop
* Description    : Stops the timer
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTickStop(void)
{
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

/*******************************************************************************
* Function Name  : SysTickDelay
* Description    : Delay function (systick-based)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTickDelay(uint32_t ticks)
{
  if (ticks)
  {
    TimerCounter = ticks;
    SysTickStart(ticks);
    while (TimerCounter);
    SysTickStop();
  }
}

/** @} */ /* End of group Systick_Private_Functions */

/** @} */ /* End of group Systick_Routines */

/** @} */ /* End of group Interrupt_Service_Routines */

/** @} */ /* End of group __MDR1986VE3_Eval_Demo */

/******************* (C) COPYRIGHT 2010 Milandr *********************************
*
* END OF FILE systick.c */

