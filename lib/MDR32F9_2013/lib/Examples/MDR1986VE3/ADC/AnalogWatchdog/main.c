/**
  ******************************************************************************
  * @file    Examples/MDR1986VE3_EVAL/ADC/AnalogWatchdog/main.c
  * @author  Milandr Application Team
  * @version V1.2.0
  * @date    12/09/2013
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
#include "MDR32F9Qx_uart.h"
#include "MDR32F9Qx_adc.h"
#include "MDR1986VE3_IT.h"
#include "MDR32F9Qx_eeprom.h"

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR1986VE3_EVAL MDR1986VE3 Complexity Evaluation Board
  * @{
  */

/** @addtogroup ADC_AnalogWatchdog_3T ADC_AnalogWatchdog
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
#if defined (_USE_DEBUG_UART_)
		#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
		#define GETCHAR_PROTOTYPE int fgetc(         FILE *f)
	#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
	#define DEBUG_PRINTF(...)
#endif /* #if defined _USE_DEBUG_UART_ */

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t H_Level = 0x900;
__IO uint32_t L_Level = 0x800;

PORT_InitTypeDef PORT_InitStructure;
ADC_InitTypeDef sADC;
ADCx_InitTypeDef sADCx;

/* Private function prototypes -----------------------------------------------*/
void ClockConfigure(void);
#if defined  (_USE_DEBUG_UART_)
	void DebugUARTInit();
#endif
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
	ClockConfigure();
#if defined (_USE_DEBUG_UART_)
	DebugUARTInit();
#endif /* #if defined (_USE_DEBUG_UART_) */
	/* Enable peripheral clocks ----------------------------------------------*/
	RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK |
			         RST_CLK_PCLK_ADC     |
			         RST_CLK_PCLK_PORTD	  |
			         RST_CLK_PCLK_PORTB),
			         ENABLE);

	/* Reset PORTD settings */
	PORT_DeInit(MDR_PORTD );

	/* Configure ADC pin: ADC2 */
	/* Configure PORTD pin 9 */
	PORT_InitStructure.PORT_Pin = PORT_Pin_9;
	PORT_InitStructure.PORT_OE = PORT_OE_IN;
	PORT_InitStructure.PORT_MODE = PORT_MODE_ANALOG;
	PORT_Init(MDR_PORTD, &PORT_InitStructure);

	/* Configure PORTB pins 0, 1 for output to switch LED1,2 on/off */
	/* Configure PORTB pins 0, 1 */
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
	PORT_InitStructure.PORT_Pin = PORT_Pin_0 | PORT_Pin_1;
	PORT_InitStructure.PORT_OE = PORT_OE_OUT;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_Init(MDR_PORTB, &PORT_InitStructure);

	/* ADC Configuration */
	/* Reset all ADC settings */
	ADC_DeInit();
	DEBUG_PRINTF("ADC Init...");
	// Inti clock ADC
	RST_CLK_ADCclkSelection(RST_CLK_ADCclkCPU_C1);
	RST_CLK_ADCclkPrescaler(RST_CLK_ADCclkDIV2);
	// Enable clock ADC
	RST_CLK_ADCclkEnable(ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_ADC, ENABLE);
	ADC_StructInit(&sADC);
	sADC.ADC_StartDelay 			= 0;
	sADC.ADC_TempSensor 			= ADC_TEMP_SENSOR_Enable;
	sADC.ADC_TempSensorAmplifier 	= ADC_TEMP_SENSOR_AMPLIFIER_Enable;
	sADC.ADC_TempSensorConversion	= ADC_TEMP_SENSOR_CONVERSION_Disable;
	sADC.ADC_IntVRefConversion 		= ADC_VREF_CONVERSION_Disable;
	sADC.ADC_IntVRefTrimming 		= 0;
	sADC.ADC_IntVRefAmplifier 		= ADC_INT_VREF_AMPLIFIER_Enable;
	ADC_Init(&sADC);

	ADCx_StructInit(&sADCx);
	sADCx.ADC_ClockSource 		= ADC_CLOCK_SOURCE_CPU;
	sADCx.ADC_SamplingMode 		= ADC_SAMPLING_MODE_CICLIC_CONV;
	sADCx.ADC_ChannelSwitching 	= ADC_CH_SWITCHING_Disable;
	sADCx.ADC_ChannelNumber 	= ADC_CH_ADC2;
	sADCx.ADC_Channels 			= 0;
	sADCx.ADC_LevelControl 		= ADC_LEVEL_CONTROL_Enable;
	sADCx.ADC_LowLevel 			= L_Level;
	sADCx.ADC_HighLevel 		= H_Level;
	sADCx.ADC_VRefSource 		= ADC_VREF_SOURCE_INTERNAL;
	sADCx.ADC_IntVRefSource 	= ADC_INT_VREF_SOURCE_INEXACT;
	sADCx.ADC_Prescaler 		= ADC_CLK_div_16;
	sADCx.ADC_DelayGo 			= 0xF;
	ADC1_Init(&sADCx);

	/* Enable ADC1 EOCIF and AWOIFEN interupts */
	ADC1_ITConfig((ADCx_IT_END_OF_CONVERSION | ADCx_IT_OUT_OF_RANGE), ENABLE);
	NVIC_EnableIRQ(ADC_IRQn);

	/* ADC1 enable */
	ADC1_Cmd(ENABLE);

	while (1);
}

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
#elif defined (USE_MDR1986VE3)
	RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTC | RST_CLK_PCLK_UART1), ENABLE);
#endif

	/* Port Init Struture */
	PORT_InitStructure.PORT_Pin = DEBUG_UART_PINS;
	PORT_InitStructure.PORT_FUNC = DEBUG_UART_PINS_FUNCTION;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_InitStructure.PORT_PD = PORT_PD_DRIVER;

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

/** @} */ /* End of group ADC_AnalogWatchdog_3T */

/** @} */ /* End of group __MDR1986VE3_EVAL */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2013 Milandr *********/

/* END OF FILE main.c */
