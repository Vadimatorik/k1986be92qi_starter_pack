/**
  ******************************************************************************
  * @file    MDR32F9Qx_it.c
  * @author  Phyton Application Team
  * @version V2.0.0
  * @date    22.07.2011
  * @brief   Main Interrupt Service Routines.
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
/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_config.h"
#include <MDR32F9Qx_uart.h>
#include <MDR32F9Qx_adc.h>
#include <MDR32F9Qx_bkp.h>
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_it.h>
#include <MDR32F9Qx_dma.h>
#include <MDR32F9Qx_timer.h>
#include "leds.h"
#include "time.h"
#include "lowpower.h"


int tmp ;
extern __IO uint32_t H_Level;

extern DMA_ChannelInitTypeDef DMA_InitStr;
extern DMA_CtrlDataInitTypeDef DMA_PriCtrlStr;
extern DMA_CtrlDataInitTypeDef DMA_AltCtrlStr;

extern uint32_t uart2_IT_TX_flag;

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
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
  //UARTx_HandlerWork(MDR_UART1);
}

void UART2_IRQHandler(void)
{
	uint32_t temp_1;
	
  //UARTx_HandlerWork(MDR_UART2);
  if (UART_GetITStatusMasked(MDR_UART2, UART_IT_RX) == SET)
  {
		temp_1 = MDR_UART2->DR;
		
		UART_ClearITPendingBit(MDR_UART2, UART_IT_RX);

		while (UART_GetFlagStatus (MDR_UART2, UART_FLAG_TXFE)!= SET)
    {
    }
		//UART_SendData (MDR_UART2,0x44);
		
  }
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
  if(ADC1_GetFlagStatus(ADCx_IT_OUT_OF_RANGE) == SET)
  {
    /* Turns LED1 On */
    PORT_SetBits(MDR_PORTD, PORT_Pin_10);
  }
  else
  {
    /* Turns LED1 Off */
    PORT_ResetBits(MDR_PORTD, PORT_Pin_10);
  }
  tmp = MDR_ADC->ADC1_RESULT & 0x0FFF;
  if(tmp > H_Level)
  {
    /* Turns LED2 On */
    PORT_SetBits(MDR_PORTD, PORT_Pin_11);
  }
  else
  {
    /* Turns LED2 Off */
    PORT_ResetBits(MDR_PORTD, PORT_Pin_11);
  }
  /* Clear ADC1 OUT_OF_RANGE interrupt bit */
  MDR_ADC->ADC1_STATUS = (ADCx_IT_END_OF_CONVERSION | ADCx_IT_OUT_OF_RANGE)<<2;
}

/*******************************************************************************
* Function Name  : BACKUP_IRQHandler
* Description    : This function handles BACKUP global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BACKUP_IRQHandler(void)
{
  uint32_t tmp;
  vuint32_t i, j;

  if (BKP_RTC_GetFlagStatus(BKP_RTC_FLAG_ALRF) == SET)
  {
    if (STOPModeStatus)
    {
      /* Wake-up from STOP mode is handled by an RTC Alarm */
      /* Disable SLEEPONEXIT mode */
      tmp = SCB->SCR;
      tmp &= ~SCB_SCR_SLEEPONEXIT_Msk;
      SCB->SCR = tmp;

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

void DMA_IRQHandler(void)
{
	PORT_SetBits(MDR_PORTD, PORT_Pin_14);
  /* Reconfigure the inactive DMA data structure*/
  if((MDR_DMA->CHNL_PRI_ALT_SET & (1<<DMA_Channel_TIM1)) == (0<<DMA_Channel_TIM1))
  {
    DMA_AltCtrlStr.DMA_CycleSize = 32;
    DMA_Init(DMA_Channel_TIM1, &DMA_InitStr);
		  // DMA_CtrlInit(DMA_Channel_TIM1, DMA_CTRL_DATA_ALTERNATE,  &DMA_AltCtrlStr);

  }
  else if((MDR_DMA->CHNL_PRI_ALT_SET & (1<<DMA_Channel_TIM1)) == (1<<DMA_Channel_TIM1))
  {
    DMA_PriCtrlStr.DMA_CycleSize = 32;
    DMA_Init(DMA_Channel_TIM1, &DMA_InitStr);
		  // DMA_CtrlInit(DMA_Channel_TIM1, DMA_CTRL_DATA_PRIMARY, &DMA_PriCtrlStr);

  }
			PORT_ResetBits(MDR_PORTD, PORT_Pin_14);
}

void Timer1_IRQHandler(void)
{
	  if (TIMER_GetITStatus(MDR_TIMER1, TIMER_STATUS_CNT_ARR) == SET)
		{		
		//TIMER_ClearITPendingBit(MDR_TIMER1, TIMER_STATUS_CNT_ARR);
			  MDR_TIMER1->STATUS &= ~TIMER_STATUS_CNT_ARR;
			
			/*while (UART_GetFlagStatus (MDR_UART2, UART_FLAG_TXFE)!= SET)
			{
			}
			UART_SendData (MDR_UART2,0x35);*/
		}
}

/** @} */ /* End of group Interrupt_Service_Private_Functions */

/** @} */ /* End of group Interrupt_Service_Routines */

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

/******************* (C) COPYRIGHT 2011 Phyton *********************************
*
* END OF FILE MDR32F9Qx_it.c */


