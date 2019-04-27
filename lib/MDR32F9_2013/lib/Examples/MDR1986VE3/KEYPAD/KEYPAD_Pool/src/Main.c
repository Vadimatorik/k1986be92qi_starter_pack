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
#include "MDR32F9Qx_uart.h"
#include "MDR32F9Qx_timer.h"
#include "MDR32F9Qx_keypad.h"

#define ASSERT_INFO_FILE_ID FILEID__main_C

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR1986VE3_EVAL MDR1986VE3 Complexity Evaluation Board
  * @{
  */

/** @addtogroup KEYPAD_IP_VE3 KEYPAD_IP
 *  @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#if defined (_USE_DEBUG_UART_)
		#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
		#define GETCHAR_PROTOTYPE int fgetc(         FILE *f)
	#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
	#define DEBUG_PRINTF(...)
#endif /* #if defined _USE_DEBUG_UART_ */
/* Varibles ------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static PORT_InitTypeDef PORT_InitStructure;
static TIMER_CntInitTypeDef TIMER_CntInitStruct;
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
	uint32_t key1, key2;
	KEYPAD_InitTypeDef KEYPAD_InitStruct;
	/* Configure CPU clock */
	ClockConfigure();

#if defined (_USE_DEBUG_UART_)
	DebugUARTInit();
#endif /* #if defined (_USE_DEBUG_UART_) */
    /* Setting the interval timer to 200 ms */

	RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER1, ENABLE);
	TIMER_BRGInit(MDR_TIMER1,TIMER_HCLKdiv1);
	TIMER_DeInit(MDR_TIMER1);
	TIMER_CntStructInit(&TIMER_CntInitStruct);
	TIMER_CntInitStruct.TIMER_Prescaler = 80;
	TIMER_CntInitStruct.TIMER_Period = 200000;
	TIMER_CntInit(MDR_TIMER1, &TIMER_CntInitStruct);
	TIMER_CntEventSourceConfig(MDR_TIMER1, TIMER_EvSrc_TM1);

	/* Enable CLK for the PORTE */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTE, ENABLE);
	/* Enable CLK for the PORTH */
	RST_CLK_PCLK2cmd(RST_CLK_PCLK2_PORTH, ENABLE);

	/* Reset setting for the PORTE */
	PORT_DeInit(MDR_PORTE);

	PORT_StructInit(&PORT_InitStructure);
	/* Config the PORTE at the reads port of the KEYPAD. */
	PORT_InitStructure.PORT_Pin 	= PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5;
	PORT_InitStructure.PORT_MODE 	= PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_FUNC 	= PORT_FUNC_OVERRID;
	PORT_InitStructure.PORT_SPEED 	= PORT_SPEED_MAXFAST;
	PORT_InitStructure.PORT_OE 		= PORT_OE_IN;
	PORT_InitStructure.PORT_PULL_UP = PORT_PULL_UP_OFF;
	PORT_Init(MDR_PORTE, &PORT_InitStructure);

	/* Config the PORTE at the reads port of the KEYPAD. */
	PORT_DeInit(MDR_PORTH);
	PORT_InitStructure.PORT_Pin	 	= PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3;
	PORT_InitStructure.PORT_FUNC 	= PORT_FUNC_MAIN;
	PORT_InitStructure.PORT_OE 		= PORT_OE_OUT;;
	PORT_Init(MDR_PORTH, &PORT_InitStructure);

	/* Enable peripheral clocks ----------------------------------------------*/
	RST_CLK_PCLK2cmd(RST_CLK_PCLK2_KEYBOARD, ENABLE);

	/* Reset the current settings of the KEYPAD */
	KEYPAD_DeInit();
	/* Config the CLK DIV for the KEYPAD. */
	KEYPAD_BRGInit(KEYPAD_BRG_1024);

	/* Init the KEYPAD_InitStruct. */
	KEYPAD_StructInit(&KEYPAD_InitStruct);
	KEYPAD_InitStruct.KeyRow 					= KEYPAD_KEY_ROW_3;
	KEYPAD_InitStruct.KeyColumn 				= KEYPAD_KEY_COLUMN_4;
	KEYPAD_InitStruct.DelayBetweenScansConfig 	= KEYPAD_DELAY_BETWEEN_SCANS_2048_CYCLES;
	KEYPAD_InitStruct.DelayBetweenScansState 	= ENABLE;
	KEYPAD_InitStruct.ContactChatteringState 	= ENABLE;
	KEYPAD_InitStruct.ContactChatteringTimer 	= KEYPAD_CONTACT_CHATTERING_TIMER_2048_CYCLES;

	/* Init the KEYPAD. */
	KEYPAD_Init(&KEYPAD_InitStruct);

    /* Start timer*/
	TIMER_Cmd(MDR_TIMER1, ENABLE);

	/* Infinite loop */
	while(1){
		while(TIMER_GetFlagStatus(MDR_TIMER1, TIMER_STATUS_CNT_ARR) != 1);
		TIMER_SetCounter(MDR_TIMER1, 0);
		TIMER_ClearFlag(MDR_TIMER1, TIMER_STATUS_CNT_ARR);
		/* Enable the KEYPAD */
		KEYPAD_Cmd(ENABLE);
		if(KEYPAD_GetFlagStatus(KEYPAD_FLAG_PCHATF)){
			/* Clear the KEYPAD_FLAG_PCHATF. */
			KEYPAD_ClearFlag(KEYPAD_FLAG_PCHATF);
			/* Disable the KEYPAD */
			KEYPAD_Cmd(DISABLE);
			if(KEYPAD_GetFlagStatus(KEYPAD_FLAG_PT1F)){
				/* Clear the KEYPAD_FLAG_PT1F */
				KEYPAD_ClearFlag(KEYPAD_FLAG_PT1F);
				/* Read the first key. */
				key1 = KEYPAD_GetPressedFirstKey();
				DEBUG_PRINTF("Pressed the first button with the code %d\r\n", key1);

			}
			if(KEYPAD_GetFlagStatus(KEYPAD_FLAG_PT2F)){
				/* Clear the  KEYPAD_FLAG_PT2F */
				KEYPAD_ClearFlag(KEYPAD_FLAG_PT2F);
				/* Read the second key */
				key2 = KEYPAD_GetPressedSecondKey();
				DEBUG_PRINTF("Pressed the second button with the code %d\r\n", key2);
			}
		}
	}
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
  * @brief
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

GETCHAR_PROTOTYPE{
	while (UART_GetFlagStatus(DEBUG_UART, UART_FLAG_RXFE) == SET);

	return ( UART_ReceiveData( DEBUG_UART ) );
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

/** @} */ /* End of group KEYPAD_IP_VE3 */

/** @} */ /* End of group MDR1986VE3_Complexity_Evaluation_Board */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2013 Milandr ********************************
*
* END OF FILE main.c */
