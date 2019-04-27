/**
  ******************************************************************************
  * @file    MDR1986VE3_IT.c
  * @author  Milandr Application Team
  * @version V1.2.0
  * @date    03/04/2013
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
  * <h2><center>&copy; COPYRIGHT 2013 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_uart.h"
#include "MDR1986VE3_IT.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#if defined (_USE_DEBUG_UART_)
	#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
	#define DEBUG_PRINTF(...)
#endif /* #if defined _USE_DEBUG_UART_ */
/* Extern variables ----------------------------------------------------------*/
extern uint32_t uart2_IT_TX_flag;
extern uint32_t uart2_IT_RX_flag;
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
	unsigned int contr_reg;
	contr_reg = __get_CONTROL();
	if(contr_reg&2)
	{
	  asm("MRS R0, PSP");
	}
	else{
	  asm("MRS R0, MSP");
	}
	//top of stack is in R0. It is passed to C-function.
	asm("BL (Hard_fault_handler_c)");

	/* Go to infinite loop when Hard Fault exception occurs */
	while (1);
}

/*******************************************************************************
* Function Name  : UART2_IRQHandler
* Description    : This function handles UART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART2_IRQHandler(void)
{
  if (UART_GetITStatusMasked(MDR_UART2, UART_IT_RX) == SET)
  {
    UART_ClearITPendingBit(MDR_UART2, UART_IT_RX);
    uart2_IT_RX_flag = SET;
  }
  else{
	  if(UART_GetITStatusMasked(MDR_UART2, UART_IT_TX) == SET){
		  UART_ClearITPendingBit(MDR_UART2, UART_IT_TX);
		  uart2_IT_TX_flag = SET;
	  }
  }
}

/**
  * @brief
  * @param
  * @retval
  */
void Hard_fault_handler_c(unsigned int* hardfault_args)
{
   unsigned int stacked_r0;
   unsigned int stacked_r1;
   unsigned int stacked_r2;
   unsigned int stacked_r3;
   unsigned int stacked_r12;
   unsigned int stacked_lr;
   unsigned int stacked_pc;
   unsigned int stacked_psr;

   stacked_r0 = ((unsigned long) hardfault_args[0]);
   stacked_r1 = ((unsigned long) hardfault_args[1]);
   stacked_r2 = ((unsigned long) hardfault_args[2]);
   stacked_r3 = ((unsigned long) hardfault_args[3]);

   stacked_r12 = ((unsigned long) hardfault_args[4]);
   stacked_lr = ((unsigned long) hardfault_args[5]);
   stacked_pc = ((unsigned long) hardfault_args[6]);
   stacked_psr = ((unsigned long) hardfault_args[7]);

   DEBUG_PRINTF("[Hard fault handler]\r\n");
   DEBUG_PRINTF("R0 = 0x%x\r\n", stacked_r0);
   DEBUG_PRINTF("R1 = 0x%x\r\n", stacked_r1);
   DEBUG_PRINTF("R2 = 0x%x\r\n", stacked_r2);
   DEBUG_PRINTF("R3 = 0x%x\r\n", stacked_r3);
   DEBUG_PRINTF("R12 = 0x%x\r\n", stacked_r12);
   DEBUG_PRINTF("LR = 0x%x\r\n", stacked_lr);
   DEBUG_PRINTF("PC = 0x%x\r\n", stacked_pc);
   DEBUG_PRINTF("PSR = 0x%x\r\n", stacked_psr);

	/* Go to infinite loop when Hard Fault exception occurs */
	while (1);
}
/******************* (C) COPYRIGHT 2013 Milandr *********/

/* END OF FILE MDR1986VE3_IT.c */
