/**
  ******************************************************************************
  * @file    MDR32F9Qx_it.c
  * @author  Milandr Application Team
  * @version V2.0.0
  * @date    22.07.2013
  * @brief   Main Interrupt Service Routines.
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
#include "MDR32F9Qx_config.h"
#include <MDR32F9Qx_uart.h>
#include <MDR32F9Qx_adc.h>
#include <MDR32F9Qx_bkp.h>
#include <MDR32F9Qx_port.h>
#include <MDR1986VE1T_it.h>
#include "leds.h"
#include "time.h"
#include "lowpower.h"

/** @addtogroup __MDR1986VE1T_Eval_Demo MDR1986VE1T Demonstration Example
  * @{
  */

/** @addtogroup Interrupt_Service_Routines Interrupt Service Routines
  * @{
  */

/** @addtogroup Interrupt_Service_Private_Variables Interrupt Service Private Variables
  * @{
  */

/* Timer counter */
vuint32_t TimerCounter = 0;

/* Current value of the ADC1_RESULT register */
vuint32_t ADC1_Value = 0;

/* Pointers to UART send/receive interrupt handlers */
tUARTFunc pfUARTSenderFunc = 0;
tUARTFunc pfUARTReceiverFunc = 0;
tUARTLineStateFunc pfUARTLineStateFunc = 0;

/* Stop mode flag */
vuint32_t STOPModeStatus = 0;

/* Alarm flag */
vuint32_t AlarmSetStatus = 0;

/** @} */ /* End of group Interrupt_Service_Private_Variables */

/** @defgroup Interrupt_Service_Private_Functions Interrupt Service Private Functions
  * @{
  */


/*******************************************************************************
* Function Name  : SysTick_Handler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Handler(void)
{
  if (TimerCounter)
  {
    TimerCounter--;
  }
}

/*******************************************************************************
* Function Name  : UARTx_HandlerWork, UART1_IRQHandler, UART2_IRQHandler
* Description    : These functions handle UARTx global interrupt requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void UARTx_HandlerWork(MDR_UART_TypeDef* UARTx)
{
  uint32_t tmp_ris = UARTx->RIS;

  /* Clear all pending bits except for UART_IT_RX */
  UARTx->ICR |= (tmp_ris & (~UART_IT_RX));

  /* Receive handler */
  if ((tmp_ris & UART_IT_RX) && pfUARTReceiverFunc != 0)
  {
    pfUARTReceiverFunc();
  }

  /* Transmit handler */
  if ((tmp_ris & UART_IT_TX) && pfUARTSenderFunc != 0)
  {
    pfUARTSenderFunc();
  }

  /* Break/error handler */
  if (pfUARTLineStateFunc != 0)
  {
    tmp_ris &= UART_LINE_STATE_EVENTS;
    if (tmp_ris)
    {
      pfUARTLineStateFunc(tmp_ris);
    }
  }
}

void UART1_IRQHandler(void)
{
  UARTx_HandlerWork(MDR_UART1);
}

void UART2_IRQHandler(void)
{
  UARTx_HandlerWork(MDR_UART2);
}


/*******************************************************************************
* Function Name  : ADC_IRQHandler
* Description    : This function handles ADC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_IRQHandler(void)
{
  /* Disable ADC1 end of conversion interrupt */
  ADC1_ITConfig(ADC1_FLAG_END_OF_CONVERSION, DISABLE);

  if (ADC1_GetFlagStatus(ADC1_IT_END_OF_CONVERSION) == SET)
  {
    /* Read value of the ADC1_RUSULT register and clear (automatically)
     * ADC1_IT_END_OF_CONVERSION flag */
    ADC1_Value = ADC1_GetResult();
  }

  if (ADC1_GetFlagStatus(ADCx_FLAG_OVERWRITE) == SET)
  {
    ADC1_ClearOverwriteFlag();
  }
}

/*******************************************************************************
* Function Name  : BACKUP_IRQHandler
* Description    : This function handles BACKUP global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BKP_IRQHandler(void)
{
  uint32_t tmp;
  vuint32_t i, j;

  if (BKP_RTC_GetFlagStatus(BKP_RTC_FLAG_ALRF) == SET)
  {
    if (STOPModeStatus)
    {
      /* Wake-up from STOP mode is handled by an RTC Alarm */
      /* Disable SLEEPONEXIT mode */
      //tmp = SCB->SCR;
      //tmp &= ~SCB_SCR_SLEEPONEXIT_Msk;
      //SCB->SCR = tmp;

      STOPModeStatus = 0;
    }
    else
      /* RTC Alarm handling */
      if (AlarmSetStatus)
      {
        for (i = 0; i < 5; i++)
        {
          PORT_SetBits(LEDs_PORT, LEDs_PINs);
          for (j = 0; j < 300000; j++)
          {
          }
          PORT_ResetBits(LEDs_PORT, LEDs_PINs);
          for (j = 0; j < 300000; j++)
          {
          }
        }
      }
  }
  if (BKP_RTC_GetFlagStatus(BKP_RTC_FLAG_SECF) == SET)
  {
    BKP_RTC_ITConfig(BKP_RTC_IT_SECF, DISABLE);

    /* If counter is equal to 86339: one day was elapsed */
    tmp = BKP_RTC_GetCounter();
    if ((tmp / 3600 == 23) &&
        (((tmp % 3600) / 60) == 59) &&
        (((tmp % 3600) % 60) == 59))
    {
      /* Wait until last write operation on RTC registers has finished */
      BKP_RTC_WaitForUpdate();
      /* Reset counter value */
      BKP_RTC_SetCounter(0);
      /* Wait until last write operation on RTC registers has finished */
      BKP_RTC_WaitForUpdate();

      /* Increment the date */
      Date_Update();
    }
    BKP_RTC_ITConfig(BKP_RTC_IT_SECF, ENABLE);
  }
}

/** @} */ /* End of group Interrupt_Service_Private_Functions */

/** @} */ /* End of group Interrupt_Service_Routines */

/** @} */ /* End of group __MDR1986VE1T_Eval_Demo */

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE MDR32F9Qx_it.c */


