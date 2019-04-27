/**
  ******************************************************************************
  * @file	 main.c
  * @author	 sidorov.a
  * @version {version}
  * @date    01.04.2013
  * @brief   Main program body.
  ******************************************************************************
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
  * <h2><center>&copy; COPYRIGHT 2013 Milandr </center></h2>
  ******************************************************************************
  * FILE main.c
  */

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_eeprom.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_mil_std_1553.h"
#include "MDR32F9Qx_uart.h"
#include "MDR32F9Qx_timer.h"

#define MY_MIL_STD_1553 MDR_MIL_STD_15531

#define ASSERT_INFO_FILE_ID FILEID__main_C

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR1986VE3_EVAL MDR1986VE3 Complexity Evaluation Board
  * @{
  */

/** @addtogroup MIL_STD_1553_Terminal_Device_VE3 MIL_STD_1553 Terminal Device
 *  @{
 */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define ONE_WORD_TIME_RECEIVING_mkS		20

/* Private macro -------------------------------------------------------------*/
#if defined (_USE_DEBUG_UART_)
		#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
	#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
	#define DEBUG_PRINTF(...)
#endif /* #if defined _USE_DEBUG_UART_ */

/* Private variables ---------------------------------------------------------*/
static PORT_InitTypeDef PORT_InitStructure;
static MIL_STD_1553_InitTypeDef MIL_STD_1553InitStructure;
static TIMER_CntInitTypeDef TIMER1_CntInitStructure;
static RST_CLK_FreqTypeDef RST_CLK_FreqStructure;
/* Private function prototypes -----------------------------------------------*/
#if defined (_USE_DEBUG_UART_)
	void DebugUARTInit ();
#endif /* #if defined _USE_DEBUG_UART_ */
void ClockConfigure ( void );

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
	/* Configure CPU clock */
	ClockConfigure();

#if defined (_USE_DEBUG_UART_)
	DebugUARTInit();
#endif /* #if defined (_USE_DEBUG_UART_) */

	/*-- Enable peripheral clocks --------------------------------------------*/
	RST_CLK_PCLKcmd((RST_CLK_PCLK_MIL_STD_15532 | RST_CLK_PCLK_MIL_STD_15531) , ENABLE);
	RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD | RST_CLK_PCLK_PORTB), ENABLE);

	/* LEDs Port Init */
	PORT_InitStructure.PORT_Pin = ( PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 |
								    PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_6 | PORT_Pin_7 );
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_OE  = PORT_OE_OUT;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;

	PORT_Init(MDR_PORTB, &PORT_InitStructure);
	DEBUG_PRINTF("Init LEDs PORT ... Ok\r\n");

	/* Configure PORTC pins 13, 14, 15 */
	PORT_InitStructure.PORT_Pin = PORT_Pin_13 | PORT_Pin_14 | PORT_Pin_15;

	PORT_InitStructure.PORT_FUNC = PORT_FUNC_MAIN;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_Init(MDR_PORTC, &PORT_InitStructure);

	/* Configure PORTD pin 0 */
	PORT_InitStructure.PORT_Pin = PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 |
								  PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_6;
	PORT_Init(MDR_PORTD, &PORT_InitStructure);

	/* Reset all MIL_STD_15531 settings */
	MIL_STD_1553_DeInit(MY_MIL_STD_1553);

	MIL_STD_1553_BRGInit(MIL_STD_1553_HCLKdiv1);

	/*-- MIL_STD_15531 configuration -----------------------------------------*/
	MIL_STD_1553xStructInit(&MIL_STD_1553InitStructure);

	/* Initialize MIL_STD_1553_InitStructure */
	MIL_STD_1553InitStructure.MIL_STD_1553_Mode = MIL_STD_1553_ModeTerminal;
	MIL_STD_1553InitStructure.MIL_STD_1553_RERR = ENABLE;
	MIL_STD_1553InitStructure.MIL_STD_1553_DIV = 80;
	MIL_STD_1553InitStructure.MIL_STD_1553_RTA = MIL_STD_1553_TERMINAL_ADDRESS;
	MIL_STD_1553InitStructure.MIL_STD_1553_TRA = ENABLE;
	MIL_STD_1553InitStructure.MIL_STD_1553_TRB = ENABLE;

	/* Configure MIL_STD_15532 parameters*/
	MIL_STD_1553_Init(MY_MIL_STD_1553, &MIL_STD_1553InitStructure);

	MIL_STD_1553_ITConfig( MY_MIL_STD_1553,
						  (MIL_STD_1553_IT_ERRIE |
						   MIL_STD_1553_IT_VALMESSIE |
						   MIL_STD_1553_IT_RFLAGNIE), ENABLE);

	NVIC_EnableIRQ(MIL_STD_1553B2_IRQn);
	NVIC_EnableIRQ(MIL_STD_1553B1_IRQn);

	/*--  Init TIMER1 --------------------------------------------------------*/
	RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER1, ENABLE);

	TIMER_DeInit(MDR_TIMER1);

	TIMER_CntStructInit(&TIMER1_CntInitStructure);

	TIMER_BRGInit(MDR_TIMER1, TIMER_HCLKdiv1);

	RST_CLK_GetClocksFreq(&RST_CLK_FreqStructure);

	TIMER1_CntInitStructure.TIMER_CounterMode = TIMER_CntMode_ClkFixedDir;
	TIMER1_CntInitStructure.TIMER_Period = RST_CLK_FreqStructure.CPU_CLK_Frequency/1000000 * ONE_WORD_TIME_RECEIVING_mkS;

	TIMER_CntInit(MDR_TIMER1, &TIMER1_CntInitStructure);

	TIMER_ITConfig(MDR_TIMER1, TIMER_STATUS_CNT_ARR, ENABLE);

	NVIC_EnableIRQ(TIMER1_IRQn);

	/* Enables MIL_STD_15531 peripheral */
	MIL_STD_1553_Cmd(MY_MIL_STD_1553, ENABLE);

	DEBUG_PRINTF("Init MIL_STD_15531 ... Ok\r\n");

	/* Infinity loop */
	while(1);
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief	Configure CPU clock.
  * @param	None
  * @retval None
  */
void ClockConfigure ( void )
{
	/* Enable HSE (High Speed External) clock */
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);
	if (RST_CLK_HSEstatus() == ERROR) {
		while (1);
	}

	/* Configures the CPU_PLL clock source */
	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul10);

	/* Enables the CPU_PLL */
	RST_CLK_CPU_PLLcmd(ENABLE);
	if (RST_CLK_CPU_PLLstatus() == ERROR) {
		while (1);
	}

	/* Enables the RST_CLK_PCLK_EEPROM */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE);
	/* Sets the code latency value */
	EEPROM_SetLatency(EEPROM_Latency_3);

	/* Select the CPU_PLL output as input for CPU_C3_SEL */
	RST_CLK_CPU_PLLuse(ENABLE);
	/* Set CPUClk Prescaler */
	RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);

	/* Select the CPU clock source */
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);

}

#if defined (_USE_DEBUG_UART_)
/**
  * @brief	Inint the debug UART
  * @param	None
  * @retval	None
  */
void DebugUARTInit()
{
	UART_InitTypeDef UART_InitStructure;
	uint32_t BaudRateStatus;
#if defined (USE_MDR1986VE3)
	RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTD | RST_CLK_PCLK_UART2), ENABLE);
#elif defined (USE_MDR1986VE9x)
	RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTF | RST_CLK_PCLK_UART2), ENABLE);
#endif

	/* Port Init Struture */
	PORT_InitStructure.PORT_Pin = DEBUG_UART_PINS;
	PORT_InitStructure.PORT_FUNC = DEBUG_UART_PINS_FUNCTION;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;

	PORT_Init(DEBUG_UART_PORT, &PORT_InitStructure);

	UART_DeInit(DEBUG_UART);

  	/* UART	Init Structure */
	UART_InitStructure.UART_BaudRate            = DEBUG_BAUD_RATE;
	UART_InitStructure.UART_WordLength          = UART_WordLength8b;
	UART_InitStructure.UART_StopBits            = UART_StopBits1;
	UART_InitStructure.UART_Parity              = UART_Parity_No;
	UART_InitStructure.UART_FIFOMode            = UART_FIFO_ON;
	UART_InitStructure.UART_HardwareFlowControl = ( UART_HardwareFlowControl_RXE |
											   UART_HardwareFlowControl_TXE );

	/* ----- Инициализация UART ----- */
	UART_BRGInit(DEBUG_UART, UART_HCLKdiv1);
        BaudRateStatus = UART_Init(DEBUG_UART, &UART_InitStructure);
	if(BaudRateStatus == BaudRateValid){
		UART_Cmd(DEBUG_UART,ENABLE);
	}
	else{
		while(1);
	}
	DEBUG_PRINTF("==============System startup==============\n\r");
	DEBUG_PRINTF("Init Debug UART ... Ok\r\n");
}

PUTCHAR_PROTOTYPE{
        UART_SendData(DEBUG_UART, (uint8_t) ch);
        // Loop until the end of transmission
        while (UART_GetFlagStatus(DEBUG_UART, UART_FLAG_TXFF) == SET);
  return (ch);
}

#endif /* #if defined (_USE_DEBUG_UART_) */

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

/** @} */ /* ENd of group MIL_STD_1553_Terminal_Device */

/** @} */ /* End of group MDR1986VE3_Complexity_Evaluation_Board */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2013 Milandr ********************************
*
* END OF FILE main.c */
