/**
 ******************************************************************************
 * @file    main.c
 * @author  Milandr Application Team
 * @version V1.2.0
 * @date    13/06/2013
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
#include "stdio.h"
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_bkp.h"
#include "MDR32F9Qx_uart.h"
#include "MDR32F9Qx_power.h"

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
 * @{
 */

/** @addtogroup __MDR1986VE3_EVAL MDR1986VE3 Complexity Evaluation Board
 * @{
 */

/** @addtogroup BKP_RTC_3T BKP_RTC
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define RTC_LSE_CLK

#define COUNT_VALUE		0
#define ALARM_VALUE		60
#define PRESC_VALUE_HS	8000000
#define PRESC_VALUE_LS	32768
#define RTCHS_PRESC		RST_CLK_HSIclkDIV8
/* Private macro -------------------------------------------------------------*/
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;
/* Private function prototypes -----------------------------------------------*/
void DebugUARTInit ();
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
void main ( void )
{
	uint32_t rtc_counter;

	/* Enables the HSI clock for BKP control */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_BKP, ENABLE);
	rtc_counter = BKP_RTC_GetCounter();

	/* Enable HSE (High Speed External) clock */
	RST_CLK_HSEconfig(RST_CLK_HSE_ON );
	if (RST_CLK_HSEstatus() == ERROR) {
		while (1);
	}

	/* Configures the CPU_PLL clock source */
	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul1 );

	/* Enables the CPU_PLL */
	RST_CLK_CPU_PLLcmd(ENABLE);
	if (RST_CLK_CPU_PLLstatus() == ERROR) {
		while (1);
	}

	/* Enables the RST_CLK_PCLK_EEPROM */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE);
	/* Sets the code latency value */
	//EEPROM_SetLatency(EEPROM_Latency_3);
	/* Select the CPU_PLL output as input for CPU_C3_SEL */
	RST_CLK_CPU_PLLuse(ENABLE);
	/* Set CPUClk Prescaler */
	RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1 );

	/* Select the CPU clock source */
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3 );

	DebugUARTInit();

	/* Enables the HSI clock on PORTD */
	//RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);
	//RST_CLK_PCLK2cmd(RST_CLK_PCLK2_PORTG, ENABLE);


	PORT_InitStructure.PORT_Pin = (PORT_Pin_10 | PORT_Pin_11);
	PORT_InitStructure.PORT_OE = PORT_OE_OUT;
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

	PORT_Init(MDR_PORTD, &PORT_InitStructure);

	int32_t i;

	if( (RST_CLK_LSEstatus() != SUCCESS) ||
		((MDR_BKP->REG_0F & BKP_REG_0F_RTC_EN) != BKP_REG_0F_RTC_EN) ){

		RST_CLK_LSEconfig(RST_CLK_LSE_ON);

		/* Wait till LSE is ready */
		while (RST_CLK_LSEstatus() != SUCCESS);
		PORT_SetBits(MDR_PORTB, PORT_Pin_0);

		/* Select the RTC Clock Source */
		BKP_RTCclkSource(BKP_RTC_LSEclk );
		/* Wait until last write operation on RTC registers has finished */
		BKP_RTC_WaitForUpdate();

		/* Sets the RTC prescaler */
		BKP_RTC_SetPrescaler(RTC_PRESCALER_VALUE);
		/* Wait until last write operation on RTC registers has finished */
		BKP_RTC_WaitForUpdate();

		/* Sets the RTC calibrator */
		BKP_RTC_Calibration(RTC_CalibratorValue);
		/* Wait until last write operation on RTC registers has finished */
		BKP_RTC_WaitForUpdate();

		/* Enable the RTC Clock */
		BKP_RTC_Enable(ENABLE);

		/* RTC enable */
		BKP_RTC_WaitForUpdate();
		BKP_RTC_Enable(ENABLE);

		BKP_RTC_WaitForUpdate();
		BKP_RTC_SetCounter(0);
	}

	/* Enable the Second interrupt */
	BKP_RTC_ITConfig(BKP_RTC_IT_SECF, ENABLE);
	NVIC_EnableIRQ(BACKUP_IRQn);

/*
	PORT_InitStructure.PORT_Pin = (PORT_Pin_14);
	PORT_InitStructure.PORT_OE = PORT_OE_IN;
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

	PORT_Init(MDR_PORTG, &PORT_InitStructure);
*/

	while (1) {
		//if ((PORT_ReadInputData(MDR_PORTG) & (1 << 14)) == (1 << 14)) {
		if ((rtc_counter + 10) <= BKP_RTC_GetCounter() ) {
			rtc_counter = BKP_RTC_GetCounter();
			BKP_RTC_WaitForUpdate();
			BKP_RTC_SetAlarm(rtc_counter + 10);
			DEBUG_PRINTF("RTC counter befor STANDBY = %d\r\n", rtc_counter);
			//RST_CLK_PCLKcmd(RST_CLK_PCLK_BKP, DISABLE);
			POWER_EnterSTANDBYMode();
		}
	}
}

volatile uint32_t tmp;

void BACKUP_IRQHandler ( void )
{
	tmp = MDR_BKP ->RTC_CS;
	MDR_PORTD ->RXTX = (BKP_RTC_GetCounter() & 1) << 10;
	MDR_BKP ->RTC_CS = tmp;

}

void DebugUARTInit ()
{
	UART_InitTypeDef UART_InitStructure;
	uint32_t BaudRateStatus;
#if defined (USE_MDR1986VE3)
	RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTD | RST_CLK_PCLK_UART2 ), ENABLE);
#elif defined (USE_MDR1986VE9x)
	RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTF | RST_CLK_PCLK_UART2), ENABLE);
#endif

	/* Port Init Struture */
	PORT_InitStructure.PORT_Pin = DEBUG_UART_PINS;
	PORT_InitStructure.PORT_FUNC = DEBUG_UART_PINS_FUNCTION;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;

	PORT_Init(DEBUG_UART_PORT, &PORT_InitStructure);

	UART_DeInit(DEBUG_UART );

	/* UART	Init Structure */
	UART_InitStructure.UART_BaudRate = DEBUG_BAUD_RATE;
	UART_InitStructure.UART_WordLength = UART_WordLength8b;
	UART_InitStructure.UART_StopBits = UART_StopBits1;
	UART_InitStructure.UART_Parity = UART_Parity_No;
	UART_InitStructure.UART_FIFOMode = UART_FIFO_ON;
	UART_InitStructure.UART_HardwareFlowControl = (UART_HardwareFlowControl_RXE
			| UART_HardwareFlowControl_TXE );

	/* ----- Инициализация UART ----- */
	UART_BRGInit(DEBUG_UART, UART_HCLKdiv1 );
	BaudRateStatus = UART_Init(DEBUG_UART, &UART_InitStructure);
	if (BaudRateStatus == BaudRateValid) {
		UART_Cmd(DEBUG_UART, ENABLE);
	}
	else {
		while (1)
			;
	}
	DEBUG_PRINTF("==============System startup==============\n\r");
	DEBUG_PRINTF("Init Debug UART ... Ok\r\n");
}

PUTCHAR_PROTOTYPE {
	UART_SendData(DEBUG_UART, (uint8_t) ch);
	// Loop until the end of transmission
	while (UART_GetFlagStatus(DEBUG_UART, UART_FLAG_TXFF) == SET);
	return (ch);
}

/*GETCHAR_PROTOTYPE {
	while (UART_GetFlagStatus(DEBUG_UART, UART_FLAG_RXFE) == SET);

	return ( UART_ReceiveData( DEBUG_UART ) );
}*/

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

/** @} *//* End of group BKP_RTC_3T */

/** @} *//* End of group __MDR1986VE3_EVAL */

/** @} *//* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2013 Milandr *********/

/* END OF FILE main.c */
