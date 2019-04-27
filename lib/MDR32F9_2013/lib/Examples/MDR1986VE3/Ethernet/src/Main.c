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
#include "MDR32F9Qx_eth.h"
#include "MDR32F9Qx_timer.h"
#include "tcpip.h"

#define ASSERT_INFO_FILE_ID FILEID__main_C

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR1986VE3_EVAL MDR1986VE3 Complexity Evaluation Board
  * @{
  */

/** @addtogroup Ethernet_VE3 Ethernet
 *  @{
 */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define ONE_WORD_TIME_RECEIVING_mkS		20

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

extern uint32_t InputFrame[1514/4];
void ETH_InputPachetHandler(MDR_ETHERNET_TypeDef * ETHERNETx);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
	static ETH_InitTypeDef  ETH_InitStruct;
	/* Configure CPU clock */
	ClockConfigure();

#if defined (_USE_DEBUG_UART_)
	DebugUARTInit();
#endif /* #if defined (_USE_DEBUG_UART_) */

/* Enable peripheral clocks --------------------------------------------------*/
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);
	/* Reset PORTB settings */
	PORT_DeInit(MDR_PORTB);
	/* Reset PORTH settings */
	PORT_DeInit(MDR_PORTH);

	/* LEDs Port Init */
	/* Configure PORTB pins 2,3,4,5,6,7 */
	PORT_InitStructure.PORT_Pin = ( PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_4 |
								    PORT_Pin_5 | PORT_Pin_6 | PORT_Pin_7 );
	PORT_InitStructure.PORT_MODE 	= PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_OE  	= PORT_OE_OUT;
	PORT_InitStructure.PORT_SPEED 	= PORT_SPEED_MAXFAST;
	PORT_InitStructure.PORT_FUNC 	= PORT_FUNC_PORT;
	PORT_InitStructure.PORT_PD 		= PORT_PD_DRIVER;
	PORT_Init(MDR_PORTB, &PORT_InitStructure);

	DEBUG_PRINTF("Init LEDs PORT ... Ok\r\n");

	/* Reset ehernet clock settings */
	ETH_ClockDeInit();

	RST_CLK_PCLKcmd(RST_CLK_PCLK_DMA, ENABLE);

	/* Enable HSE2 oscillator */
	RST_CLK_HSE2config(RST_CLK_HSE2_ON);
	if(RST_CLK_HSE2status() == ERROR)
		while(1); /* Infinite loop */

	/* Config PHY clock */
	ETH_PHY_ClockConfig(ETH_PHY_CLOCK_SOURCE_HSE2, ETH_PHY_HCLKdiv1);

	/* Init the BRG ETHERNET */
	ETH_BRGInit(ETH_HCLKdiv1);

	/* Enable the ETHERNET clock */
	ETH_ClockCMD(ETH_CLK1, ENABLE);

	/* Reset to default ethernet settings */
	ETH_DeInit(MDR_ETHERNET1);

	/* Init ETH_InitStruct members with its default value */
	ETH_StructInit((ETH_InitTypeDef * ) &ETH_InitStruct);
	/* Set the speed of the chennel */
	ETH_InitStruct.ETH_PHY_Mode = ETH_PHY_MODE_AutoNegotiation;
	ETH_InitStruct.ETH_Transmitter_RST = SET;
	ETH_InitStruct.ETH_Receiver_RST = SET;
	/* Set the buffer mode */
	ETH_InitStruct.ETH_Buffer_Mode = ETH_BUFFER_MODE_LINEAR;

	ETH_InitStruct.ETH_Source_Addr_HASH_Filter = DISABLE;

	/* Set the MAC address. */
	ETH_InitStruct.ETH_MAC_Address[2] = (MAC_0<<8)|MAC_1;
	ETH_InitStruct.ETH_MAC_Address[1] = (MAC_2<<8)|MAC_3;
	ETH_InitStruct.ETH_MAC_Address[0] = (MAC_4<<8)|MAC_5;

	/* Set the buffer size of transmitter and receiver */
	ETH_InitStruct.ETH_Dilimiter = 0x1000;

	/* Init the ETHERNET 1 */
	ETH_Init(MDR_ETHERNET1, (ETH_InitTypeDef *) &ETH_InitStruct);

	/* Enable PHY module */
	ETH_PHYCmd(MDR_ETHERNET1, ENABLE);

	TCPLowLevelInit();

	/* Start the ETHERNET1 */
	ETH_Start(MDR_ETHERNET1);

	/* Infinite loop */
	while(1){
		 ETH_InputPachetHandler(MDR_ETHERNET1);
		 DoNetworkStuff(MDR_ETHERNET1);
	}
}

void ETH_InputPachetHandler(MDR_ETHERNET_TypeDef * ETHERNETx){

	uint16_t status_reg;
	ETH_StatusPacketReceptionTypeDef ETH_StatusPacketReceptionStruct;

	/* Check that the packet is received */
	status_reg = ETH_GetMACITStatusRegister(ETHERNETx);

	if(ETHERNETx->ETH_R_Head != ETHERNETx->ETH_R_Tail){
	/*if(status_reg & ETH_MAC_IT_RF_OK ){*/
		ETH_StatusPacketReceptionStruct.Status = ETH_ReceivedFrame(ETHERNETx, InputFrame);

		if(ETH_StatusPacketReceptionStruct.Fields.UCA)
			 ProcessEthIAFrame(InputFrame, ETH_StatusPacketReceptionStruct.Fields.Length);
		if(ETH_StatusPacketReceptionStruct.Fields.BCA)
			 ProcessEthBroadcastFrame(InputFrame, ETH_StatusPacketReceptionStruct.Fields.Length);
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

	RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTD | RST_CLK_PCLK_UART2), ENABLE);

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
void assert_failed(uint32_t file_id, uint32_t line, const uint8_t* expr)
{
  /* User can add his own implementation to report the source file ID, line number and
     expression text.
     Ex: printf("Wrong parameters value (%s): file Id %d on line %d\r\n", expr, file_id, line) */
	DEBUG_PRINTF("Wrong parameters value (%s): file Id %d on line %d\r\n", expr, file_id, line);

  /* Infinite loop */
  while (1);
}
#endif /* USE_ASSERT_INFO */

/** @} */ /* End of group Ethernet */

/** @} */ /* End of group MDR1986VE3_Complexity_Evaluation_Board */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2013 Milandr ********************************
*
* END OF FILE main.c */
