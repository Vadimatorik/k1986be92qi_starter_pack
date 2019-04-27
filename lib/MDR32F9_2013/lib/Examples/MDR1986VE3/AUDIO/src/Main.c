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
#include "MDR32F9Qx_audio.h"

#define ASSERT_INFO_FILE_ID FILEID__main_C

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR1986VE3_EVAL MDR1986VE3 Complexity Evaluation Board
  * @{
  */

/** @addtogroup AUDIO_IP_VE3 AUDIO_IP
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
	AUDIO_IP_InitTypeDef AUDIO_IP_InitStruct;
	/* Configure CPU clock */
	ClockConfigure();

#if defined (_USE_DEBUG_UART_)
	DebugUARTInit();
#endif /* #if defined (_USE_DEBUG_UART_) */

/* Enable peripheral clocks --------------------------------------------------*/
	RST_CLK_AUCclkDeInit();
	RST_CLK_AUCclkSelection(RST_CLK_AUCclkHSE_2_C1);
	RST_CLK_AUCclkPrescaler(RST_CLK_AUCclkDIV1);
	RST_CLK_AUCclkCMD(ENABLE);
	RST_CLK_PCLK2cmd(RST_CLK_PCLK2_AUDIO_IP, ENABLE);

	/* AUDIO_IP Configuration 	*/
	/* Reset all settings 		*/
	AUDIO_IP_DeInit();
	AUDIO_IP_StructInit(&AUDIO_IP_InitStruct);

	/* AUDIO_IP ADC Configuration */
	AUDIO_IP_InitStruct.ADCAnalogInput 				= AUDIO_IP_ANALOG_INPUT_SOURCE_MICIN_INT;
	AUDIO_IP_InitStruct.ADCInputControl				= ENABLE;
	/* AUDIO_IP DAC Configuration */
	AUDIO_IP_InitStruct.DACBIASOffsetSchemeState	= ENABLE;
	AUDIO_IP_InitStruct.DACAnalogState				= ENABLE;
	AUDIO_IP_InitStruct.DACSideToneLoopBack 		= AUDIO_IP_DAC_SIDE_TONE_LOOP_BACK_MUTE;
	AUDIO_IP_InitStruct.DACOutputAmplifier			= ENABLE;
	AUDIO_IP_InitStruct.DACState					= ENABLE;
	AUDIO_IP_Init(&AUDIO_IP_InitStruct);

	/* Enable AUDIO_IP ADCNSM interrupt  */
	AUDIO_IP_ITConfig(AUDIO_IP_IT_ADCNSM, ENABLE);
	/* Enable global AUDIO_IP IRQ */
	NVIC_EnableIRQ(AUDIO_IP_IRQn);

	/* Enable AUDIO_IP ADC */
	AUDIO_IP_ADCCmd(ENABLE);
	/* Enable AUDIO_DAC ADC */
	AUDIO_IP_DACCmd(ENABLE);

	/* Infinite loop */
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

/** @} */ /* End of group AUDIO_IP_VE3 */

/** @} */ /* End of group MDR1986VE3_Complexity_Evaluation_Board */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2013 Milandr ********************************
*
* END OF FILE main.c */
