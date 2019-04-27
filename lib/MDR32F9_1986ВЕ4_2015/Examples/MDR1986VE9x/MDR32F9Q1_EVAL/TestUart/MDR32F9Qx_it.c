/**
  ******************************************************************************
  * @file    Examples/MDR32F9Q1_EVAL/UART/Interrupt/MDR32F9Qx_it.c
  * @author  Milandr Application Team
  * @version V1.2.0
  * @date    04/07/2011
  * @brief   Main Interrupt Service Routines.
  *
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
  * <h2><center>&copy; COPYRIGHT 2011 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_it.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
/* Private variables ---------------------------------------------------------*/
uint8_t UART_Data1, UART_Data2;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : UART2_IRQHandler
* Description    : This function handles UART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART2_IRQHandler(void)
{
	if (UART_GetITStatusMasked(MDR_UART2, UART_IT_PE ) == SET) {
		UART_Data1 = UART_ReceiveData(MDR_UART2);

		while(UART_GetFlagStatus(MDR_UART2, UART_FLAG_RXFF) != SET);

		UART_Data2 = UART_ReceiveData(MDR_UART2);
		UART_ClearITPendingBit(MDR_UART2, UART_IT_PE );
		DEBUG_PRINTF("\r\nUART2 RX First = 0x%x\t",UART_Data1);

		DEBUG_PRINTF("UART2 RX Second = 0x%x\r\n\r\n",UART_Data2);
	}
}

/******************* (C) COPYRIGHT 2011 Milandr *********/

/* END OF FILE MDR32F9Qx_it.c */
