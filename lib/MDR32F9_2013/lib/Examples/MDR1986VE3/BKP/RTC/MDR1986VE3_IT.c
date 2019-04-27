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
#include "MDR1986VE3_IT.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_bkp.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#if defined (_USE_DEBUG_UART_)
	#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
	#define DEBUG_PRINTF(...)
#endif /* #if defined _USE_DEBUG_UART_ */

/* Private variables ---------------------------------------------------------*/
uint32_t Counter = 0;
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
* Function Name  : BKP_IRQHandler
* Description    : This function handles BKP global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BKP_IRQHandler ( void )
{
	if (BKP_RTC_GetFlagStatus(BKP_RTC_FLAG_SECF) == SET) {
		if (PORT_ReadInputDataBit(MDR_PORTB, PORT_Pin_0) == 0) {
			PORT_SetBits(MDR_PORTB, PORT_Pin_0);
		}
		else {
			PORT_ResetBits(MDR_PORTB, PORT_Pin_0);
		}
	}
	if (BKP_RTC_GetFlagStatus(BKP_RTC_FLAG_ALRF) == SET) {
		PORT_SetBits(MDR_PORTB, PORT_Pin_1);
	}
	MDR_BKP->RTC_CS |= 0x06;
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
