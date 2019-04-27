/**
  ******************************************************************************
  * @file    Examples/MDR1986VE3/DMA/UART_RAM/main.c
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
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_dma.h"
#include "MDR32F9Qx_port.h"

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR1986VE3_EVAL MDR1986VE3 Complexity Evaluation Board
  * @{
  */

/** @addtogroup DMA_UART_RAM_3T DMA_UART_RAM
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define BufferSize         32

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
DMA_ChannelInitTypeDef DMA_InitStr;
DMA_CtrlDataInitTypeDef DMA_PriCtrlStr;
UART_InitTypeDef sUART;
PORT_InitTypeDef PORT_InitStructure;

uint16_t SrcBuf1[BufferSize] IAR_SECTION ("EXECUTABLE_MEMORY_SECTION") __attribute__((section("EXECUTABLE_MEMORY_SECTION")));
uint16_t DstBuf1[BufferSize] IAR_SECTION ("EXECUTABLE_MEMORY_SECTION") __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

volatile TestStatus TransferStatus1 = FAILED;

/* Private function prototypes -----------------------------------------------*/
void Init_RAM (uint16_t *addr, uint32_t size);
uint32_t ps_rand(uint32_t addr);
TestStatus Verif_mem (uint32_t BufSize, uint16_t *pBuffer1, uint16_t *pBuffer2);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
void main(void)
{
	RST_CLK_DeInit();

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
	//EEPROM_SetLatency(EEPROM_Latency_3);

	/* Select the CPU_PLL output as input for CPU_C3_SEL */
	RST_CLK_CPU_PLLuse(ENABLE);
	/* Set CPUClk Prescaler */
	RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);

	/* Select the CPU clock source */
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);



	/* Enable peripheral clocks --------------------------------------------------*/
	RST_CLK_PCLKcmd(
				(RST_CLK_PCLK_RST_CLK |
				 RST_CLK_PCLK_UART2   |
				 RST_CLK_PCLK_DMA),
				 ENABLE);
	RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTD), ENABLE);

	/* Disable all DMA request */
	MDR_DMA ->CHNL_REQ_MASK_CLR = 0xFFFFFFFF;
	MDR_DMA ->CHNL_USEBURST_CLR = 0xFFFFFFFF;

	/* Reset PORTC settings */
	PORT_DeInit(MDR_PORTD );

	/* Configure UART2 pins: RXD, TXD */

	/* Configure PORTC pins 13, 14 */
	PORT_InitStructure.PORT_Pin = PORT_Pin_14;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_MAIN;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_InitStructure.PORT_OE = PORT_OE_IN;
	PORT_Init(MDR_PORTD, &PORT_InitStructure);

	PORT_InitStructure.PORT_Pin = (PORT_Pin_13);
	PORT_InitStructure.PORT_OE = PORT_OE_OUT;
	PORT_Init(MDR_PORTD, &PORT_InitStructure);

	/* Init RAM */
	//Init_RAM(DstBuf1, BufferSize);
	Init_RAM(SrcBuf1, BufferSize);

	/* Reset all UART settings */

	UART_DeInit(MDR_UART2 );

	UART_BRGInit(MDR_UART2, UART_HCLKdiv1 );

	/* UART1 configuration ------------------------------------------------*/
	UART_StructInit(&sUART);

	sUART.UART_BaudRate 			= 1200;
	sUART.UART_WordLength 			= UART_WordLength8b;
	sUART.UART_StopBits 			= UART_StopBits1;
	sUART.UART_Parity 				= UART_Parity_No;
	sUART.UART_FIFOMode 			= UART_FIFO_ON;
	sUART.UART_HardwareFlowControl 	= (UART_HardwareFlowControl_RXE
									| UART_HardwareFlowControl_TXE );
	/* UART2 configuration ------------------------------------------------*/
	UART_Init(MDR_UART2, &sUART);
	UART_DMAConfig(MDR_UART2,
				   UART_IT_FIFO_LVL_8words,
				   UART_IT_FIFO_LVL_8words );

	/* Enable UART2 DMA Rx and Tx request */
	UART_DMACmd(MDR_UART2, (UART_DMA_RXE | UART_DMA_TXE ), ENABLE);

	/* Reset all DMA settings */
	DMA_DeInit();
	DMA_StructInit(&DMA_InitStr);

	/* DMA_Channel_UART1_RX configuration ---------------------------------*/
	/* Set Primary Control Data */
	DMA_PriCtrlStr.DMA_SourceBaseAddr 	= (uint32_t) (&(MDR_UART2->DR));
	DMA_PriCtrlStr.DMA_DestBaseAddr 	= (uint32_t) DstBuf1;
	DMA_PriCtrlStr.DMA_SourceIncSize 	= DMA_SourceIncNo;
	DMA_PriCtrlStr.DMA_DestIncSize 		= DMA_DestIncByte;
	DMA_PriCtrlStr.DMA_MemoryDataSize 	= DMA_MemoryDataSize_Byte;
	DMA_PriCtrlStr.DMA_Mode 			= DMA_Mode_Basic;
	DMA_PriCtrlStr.DMA_CycleSize 		= BufferSize;
	DMA_PriCtrlStr.DMA_NumContinuous 	= DMA_Transfers_8;
	DMA_PriCtrlStr.DMA_SourceProtCtrl 	= DMA_SourcePrivileged;
	DMA_PriCtrlStr.DMA_DestProtCtrl 	= DMA_DestPrivileged;
	/* Set Channel Structure */
	DMA_InitStr.DMA_PriCtrlData 		= &DMA_PriCtrlStr;
	DMA_InitStr.DMA_Priority 			= DMA_Priority_High;
	DMA_InitStr.DMA_UseBurst	 		= DMA_BurstClear;
	DMA_InitStr.DMA_SelectDataStructure = DMA_CTRL_DATA_PRIMARY;
	/* Init DMA channel */
	DMA_Init(DMA_Channel_REQ_UART2_RX, &DMA_InitStr);

	/* DMA_Channel_UART2_TX configuration ---------------------------------*/
	/* Set Primary Control Data */
	DMA_PriCtrlStr.DMA_SourceBaseAddr 	= (uint32_t) SrcBuf1;
	DMA_PriCtrlStr.DMA_DestBaseAddr 	= (uint32_t) (&(MDR_UART2 ->DR));
	DMA_PriCtrlStr.DMA_SourceIncSize 	= DMA_SourceIncByte;
	DMA_PriCtrlStr.DMA_DestIncSize 		= DMA_DestIncNo;
	DMA_InitStr.DMA_Priority 			= DMA_Priority_Default;
	/* Init DMA channel */
	DMA_Init(DMA_Channel_REQ_UART2_TX, &DMA_InitStr);

	/* Enable UART2 */
	UART_Cmd(MDR_UART2, ENABLE);

	/* Transfer complete */
	while ((DMA_GetFlagStatus(DMA_Channel_REQ_UART2_TX, DMA_FLAG_CHNL_ENA )));
	while ((DMA_GetFlagStatus(DMA_Channel_REQ_UART2_RX, DMA_FLAG_CHNL_ENA )));

	/* Check the corectness of written dada */
	TransferStatus1 = Verif_mem((BufferSize / 2), SrcBuf1, DstBuf1);
	/* TransferStatus1 = PASSED, if the data transmitted and received
	 are correct */
	/* TransferStatus1 = FAILED, if the data transmitted and received
	 are different */

	while (1);
}

/**
  * @brief  Initialisation memory pseudo random value
  * @param  addr - memory address
  * @param  size - memory size
  * @retval None
  */
void Init_RAM (uint16_t *addr, uint32_t size)
{
uint32_t i;

  for (i = 0; i < size; i++)
  {
    *addr++ = ps_rand((uint32_t)addr) + (i*4);
  }
}

/**
  * @brief  Generation random values
  * @param  addr:
  * @retval random value
  */
uint32_t ps_rand(uint32_t addr)
{
uint32_t hash = 0;
uint32_t i;
char *key = (char *)&addr;

  for (i = 0; i < 4; i++)
  {
    hash += key[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  for (i = 0; i < 256; i++)
  {
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);

  return hash;
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufSize: buffer's size
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Verif_mem (uint32_t BufSize, uint16_t *pBuffer1, uint16_t *pBuffer2)
{
uint32_t i;

  for(i = 0; i < BufSize; i++)
  {
    if (*pBuffer1++ != *pBuffer2++)
    {
      return(FAILED);
    }
  }

  return(PASSED);
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

/** @} */ /* End of group DMA_UART_RAM_3T */

/** @} */ /* End of group __MDR1986VE3 */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */


/******************* (C) COPYRIGHT 2013 Milandr *********/

/* END OF FILE main.c */
