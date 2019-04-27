/**
 ******************************************************************************
 * @file    Examples/MDR1986VE3_EVAL/UART/Interrupt/main.c
 * @author  Milandr Application Team
 * @version V1.2.0
 * @date    04/07/2013
 * @brief   Main program body.
 ******************************************************************************
 * <br><br>
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2013 Milandr</center></h2>
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_uart.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR1986VE3_IT.h"

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
 * @{
 */

/** @addtogroup __MDR1986VE3_EVAL MDR1986VE3 Complexity Evaluation Board
 * @{
 */

/** @addtogroup UART_Interrupt_3T UART_Interrupt
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static PORT_InitTypeDef PortInit;
static UART_InitTypeDef UART_InitStructure;
uint32_t uart2_IT_TX_flag = RESET;
uint32_t uart2_IT_RX_flag = RESET;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
void main ( void )
{
	uint8_t DataByte = 0x00;
	static uint8_t ReciveByte = 0x00;

	/* Enables the HSI clock on PORTD */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);

	/* Fill PortInit structure*/
	PortInit.PORT_PULL_UP = PORT_PULL_UP_OFF;
	PortInit.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
	PortInit.PORT_PD_SHM = PORT_PD_SHM_OFF;
	PortInit.PORT_PD = PORT_PD_DRIVER;
	PortInit.PORT_GFEN = PORT_GFEN_OFF;
	PortInit.PORT_FUNC = PORT_FUNC_MAIN;
	PortInit.PORT_SPEED = PORT_SPEED_MAXFAST;
	PortInit.PORT_MODE = PORT_MODE_DIGITAL;

	/* Configure PORTD pins 13 (UART2_TX) as output */
	PortInit.PORT_OE = PORT_OE_OUT;
	PortInit.PORT_Pin = PORT_Pin_13;
	PORT_Init(MDR_PORTD, &PortInit);
	/* Configure PORTD pins 14 (UART2_RX) as input */
	PortInit.PORT_OE = PORT_OE_IN;
	PortInit.PORT_Pin = PORT_Pin_14;
	PORT_Init(MDR_PORTD, &PortInit);

	/* Select HSI/2 as CPU_CLK source*/
	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSIdiv2, 0);

	/* Enables the CPU_CLK clock on UART2 */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_UART2, ENABLE);

	/* Set the HCLK division factor = 1 for UART2*/
	UART_BRGInit(MDR_UART2, UART_HCLKdiv1 );

	NVIC_EnableIRQ(UART2_IRQn);

	/* Initialize UART_InitStructure */
	UART_InitStructure.UART_BaudRate = 9600;
	UART_InitStructure.UART_WordLength = UART_WordLength8b;
	UART_InitStructure.UART_StopBits = UART_StopBits1;
	UART_InitStructure.UART_Parity = UART_Parity_No;
	UART_InitStructure.UART_FIFOMode = UART_FIFO_OFF;
	UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_RXE
												| UART_HardwareFlowControl_TXE;

	/* Configure UART2 parameters*/
	UART_Init(MDR_UART2, &UART_InitStructure);

	/* Enable Receiver interrupt*/
	UART_ITConfig(MDR_UART2, (UART_IT_RX | UART_IT_TX), ENABLE);

	/* Enables UART2 peripheral */
	UART_Cmd(MDR_UART2, ENABLE);

	while (1) {
		/* Send Data from UART1 */
		UART_SendData(MDR_UART2, DataByte);

		/* Wait until uart1_IT_TX being SET */
		while (uart2_IT_TX_flag != SET);

		/* Clear uart1_IT_TX_flag */
		uart2_IT_TX_flag = RESET;

		/* Wait until uart2_IT_RX being SET */
		while (uart2_IT_RX_flag != SET);

		/* Clear uart2_IT_RX_flag */
		uart2_IT_RX_flag = RESET;

		/* Recive data*/
		ReciveByte = UART_ReceiveData(MDR_UART2 );

		/* Increment Data*/
		DataByte++;
	}
}

/**
 * @brief  Reports the source file ID, the source line number
 *         and expression text (if USE_ASSERT_INFO == 2) where
 *         the assert_param error has occurred.
 * @param  file_id: pointer to the source file name
 * @param  line: assert_param error line source number
 * @param  expr:
 * @retval None
 */
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint32_t file_id, uint32_t line)
{
	/* User can add his own implementation to report the source file ID and line number.
	 Ex: printf("Wrong parameters value: file Id %d on line %d\r\n", file_id, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint32_t file_id, uint32_t line, const uint8_t* expr);
{
	/* User can add his own implementation to report the source file ID, line number and
	 expression text.
	 Ex: printf("Wrong parameters value (%s): file Id %d on line %d\r\n", expr, file_id, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif /* USE_ASSERT_INFO */

/** @} *//* End of group UART_Interrupt_3T */

/** @} *//* End of group __MDR1986VE3_EVAL */

/** @} *//* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2013 Milandr *********/

/* END OF FILE main.c */

