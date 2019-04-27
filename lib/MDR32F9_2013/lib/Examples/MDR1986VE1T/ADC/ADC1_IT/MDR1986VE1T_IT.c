/**
  ******************************************************************************
  * @file    MDR1986VE1T_IT.c
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
#include "MDR1986VE1T_IT.h"
#include "MDR32F9Qx_adc.h"
#include "MDR32F9Qx_port.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#if defined (_USE_DEBUG_UART_)
	#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
	#define DEBUG_PRINTF(...)
#endif /* #if defined _USE_DEBUG_UART_ */

#define NUM_ADC_SAMPLING 16

/* Extern variables ----------------------------------------------------------*/
extern uint16_t ADCConvertedValue[NUM_ADC_SAMPLING];
/* Private variables ---------------------------------------------------------*/
uint32_t Counter = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
}

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
* Function Name  : SVC_Handler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVC_Handler(void)
{
}

/*******************************************************************************
* Function Name  : PendSV_Handler
* Description    : This function handles Debug PendSV exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSV_Handler(void)
{
}

/*******************************************************************************
* Function Name  : SysTick_Handler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Handler(void)
{
}

/*******************************************************************************
* Function Name  : MIL_STD_1553B2_IRQHandler
* Description    : This function handles MIL_STD_1553B2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MIL_STD_1553B2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : MIL_STD_1553B1_IRQHandler
* Description    : This function handles MIL_STD_1553B1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MIL_STD_1553B1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USB_IRQHandler
* Description    : This function handles USB global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*
void USB_IRQHandler(void)
{
}
*/

/*******************************************************************************
* Function Name  : CAN1_IRQHandler
* Description    : This function handles CAN1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN1_IRQHandler(void)
{
}

/*******************************************************************************

* Function Name  : CAN2_IRQHandler
* Description    : This function handles CAN2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA_IRQHandler
* Description    : This function handles DMA global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA_IRQHandler ( void )
{
}

/*******************************************************************************
* Function Name  : UART1_IRQHandler
* Description    : This function handles UART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART1_IRQHandler(void)
{
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
}

/*******************************************************************************
* Function Name  : SSP1_IRQHandler
* Description    : This function handles SSP1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : BUSY_IRQHandler
* Description    : This function handles BUSY global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BUSY_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : ARINC429R_IRQHandler
* Description    : This function handles ARINC429R global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ARINC429R_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : POWER_IRQHandler
* Description    : This function handles POWER global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void POWER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : WWDG_IRQHandler
* Description    : This function handles WWDG global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIMER4_IRQHandler
* Description    : This function handles TIMER4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIMER4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : Timer1_IRQHandler
* Description    : This function handles Timer1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : Timer2_IRQHandler
* Description    : This function handles Timer2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : Timer3_IRQHandler
* Description    : This function handles Timer3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer3_IRQHandler(void)
{
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
	if(ADC_GetITStatus(ADC1_IT_END_OF_CONVERSION) == SET){
		ADCConvertedValue[Counter] = ADC1_GetResult();
		Counter  = (Counter+1) & (NUM_ADC_SAMPLING - 1);
		if(Counter == 0){
			ADC1_Cmd(DISABLE);
			DEBUG_PRINTF("ADC Conversion Complete\r\n");
			while(Counter < NUM_ADC_SAMPLING){
				DEBUG_PRINTF("ADC_Value[%d] = 0x%4x\r\n", Counter, ADCConvertedValue[Counter]&0x0FFF);
				Counter++;
			}
		}
	}
}

/*******************************************************************************
* Function Name  : ETHERNET_IRQHandler
* Description    : This function handles ETHERNET global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ETHERNET_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SSP3_IRQHandler
* Description    : This function handles SSP3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SSP2_IRQHandler
* Description    : This function handles SSP2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : ARINC429T1_IRQHandler
* Description    : This function handles ARINC429T1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ARINC429T1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : ARINC429T2_IRQHandler
* Description    : This function handles ARINC429T2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ARINC429T2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : ARINC429T3_IRQHandler
* Description    : This function handles ARINC429T3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ARINC429T3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : ARINC429T3_IRQHandler
* Description    : This function handles ARINC429T3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ARINC429T4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : BKP_IRQHandler
* Description    : This function handles BKP global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BKP_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXT_INT1_IRQHandler
* Description    : This function handles EXT_INT1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXT_INT2_IRQHandler
* Description    : This function handles EXT_INT2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXT_INT3_IRQHandler
* Description    : This function handles EXT_INT3 global interrupt request.
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXT_INT4_IRQHandler
* Description    : This function handles EXT_INT4 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT4_IRQHandler(void)
{
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

/* END OF FILE MDR1986VE1T_IT.c */
