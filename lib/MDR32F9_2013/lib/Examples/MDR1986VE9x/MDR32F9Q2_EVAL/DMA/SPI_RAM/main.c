/**
  ******************************************************************************
  * @file    Examples/MDR32F9Q2_EVAL/DMA/SPI_RAM/main.c
  * @author  Milandr Application Team
  * @version V1.2.0
  * @date    04/07/2011
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
  * <h2><center>&copy; COPYRIGHT 2011 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_board.h"
#include "MDR32F9Qx_config.h"
#include "MDR32Fx.h"
#include "MDR32F9Qx_ssp.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_dma.h"
#include "MDR32F9Qx_port.h"

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F9Q2_EVAL MDR32F9Q2 Evaluation Board
  * @{
  */

/** @addtogroup DMA_SPI_RAM_92 DMA_SPI_RAM
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
SSP_InitTypeDef sSSP;
PORT_InitTypeDef PORT_InitStructure;

uint16_t SrcBuf1[BufferSize];
uint16_t SrcBuf2[BufferSize];
uint16_t DstBuf1[BufferSize];
uint16_t DstBuf2[BufferSize];

volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;

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
  RST_CLK_CPU_PLLconfig (RST_CLK_CPU_PLLsrcHSIdiv2,0);
  /* Enable peripheral clocks --------------------------------------------------*/
  RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_SSP1 | RST_CLK_PCLK_SSP2 | RST_CLK_PCLK_DMA),ENABLE);
  RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTF | RST_CLK_PCLK_PORTD), ENABLE);

  /* Init NVIC */
  SCB->AIRCR = 0x05FA0000 | ((uint32_t)0x500);
  SCB->VTOR = 0x08000000;
  /* Disable all interrupt */
  NVIC->ICPR[0] = 0xFFFFFFFF;
  NVIC->ICER[0] = 0xFFFFFFFF;

  /* Disable all DMA request */
  MDR_DMA->CHNL_REQ_MASK_CLR = 0xFFFFFFFF;
  MDR_DMA->CHNL_USEBURST_CLR = 0xFFFFFFFF;

  /* Reset PORTD settings */
  PORT_DeInit(MDR_PORTD);
  /* Reset PORTF settings */
  PORT_DeInit(MDR_PORTF);

  /* Configure SSP2 pins: FSS, CLK, RXD, TXD */

  /* Configure PORTD pins 2, 3, 5, 6 */
  PORT_InitStructure.PORT_Pin   = (PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_5);
  PORT_InitStructure.PORT_OE    = PORT_OE_IN;
  PORT_InitStructure.PORT_FUNC  = PORT_FUNC_ALTER;
  PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_FAST;
  PORT_Init(MDR_PORTD, &PORT_InitStructure);
  PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
  PORT_InitStructure.PORT_Pin   = (PORT_Pin_6);
  PORT_Init(MDR_PORTD, &PORT_InitStructure);

  /* Configure SSP1 pins: FSS, CLK, RXD, TXD */

  /* Configure PORTF pins 0, 1, 2, 3 */
  PORT_InitStructure.PORT_Pin   = (PORT_Pin_3);
  PORT_InitStructure.PORT_OE    = PORT_OE_IN;
  PORT_Init(MDR_PORTF, &PORT_InitStructure);
  PORT_InitStructure.PORT_Pin   = (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2);
  PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
  PORT_Init(MDR_PORTF, &PORT_InitStructure);


  /* Init RAM */
  Init_RAM (DstBuf1, BufferSize);
  Init_RAM (SrcBuf1, BufferSize);
  Init_RAM (DstBuf2, BufferSize);
  Init_RAM (SrcBuf2, BufferSize);

  /* Reset all SSP settings */
  SSP_DeInit(MDR_SSP1);
  SSP_DeInit(MDR_SSP2);

  SSP_BRGInit(MDR_SSP1,SSP_HCLKdiv16);
  SSP_BRGInit(MDR_SSP2,SSP_HCLKdiv16);

  /* SSP1 MASTER configuration ------------------------------------------------*/
  SSP_StructInit (&sSSP);

  sSSP.SSP_SCR  = 0x10;
  sSSP.SSP_CPSDVSR = 2;
  sSSP.SSP_Mode = SSP_ModeMaster;
  sSSP.SSP_WordLength = SSP_WordLength16b;
  sSSP.SSP_SPH = SSP_SPH_1Edge;
  sSSP.SSP_SPO = SSP_SPO_Low;
  sSSP.SSP_FRF = SSP_FRF_SPI_Motorola;
  sSSP.SSP_HardwareFlowControl = SSP_HardwareFlowControl_SSE;
  SSP_Init (MDR_SSP1,&sSSP);

  /* SSP2 SLAVE configuration ------------------------------------------------*/
  sSSP.SSP_SPH = SSP_SPH_1Edge;
  sSSP.SSP_SPO = SSP_SPO_Low;
  sSSP.SSP_CPSDVSR = 12;
  sSSP.SSP_Mode = SSP_ModeSlave;
  SSP_Init (MDR_SSP2,&sSSP);

  /* Enable SSP1 DMA Rx and Tx request */
  SSP_DMACmd(MDR_SSP1,(SSP_DMA_RXE | SSP_DMA_TXE), ENABLE);
  /* Enable SSP2 DMA Rx and Tx request */
  SSP_DMACmd(MDR_SSP2,(SSP_DMA_RXE | SSP_DMA_TXE), ENABLE);

  /* Reset all DMA settings */
  DMA_DeInit();
  DMA_StructInit(&DMA_InitStr);

  /* DMA_Channel_SSP1_RX configuration ---------------------------------*/
  /* Set Primary Control Data */
  DMA_PriCtrlStr.DMA_SourceBaseAddr = (uint32_t)(&(MDR_SSP1->DR));
  DMA_PriCtrlStr.DMA_DestBaseAddr = (uint32_t)DstBuf1;
  DMA_PriCtrlStr.DMA_SourceIncSize = DMA_SourceIncNo;
  DMA_PriCtrlStr.DMA_DestIncSize = DMA_DestIncHalfword;
  DMA_PriCtrlStr.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_PriCtrlStr.DMA_Mode = DMA_Mode_Basic;
  DMA_PriCtrlStr.DMA_CycleSize = BufferSize;
  DMA_PriCtrlStr.DMA_NumContinuous = DMA_Transfers_4;
  DMA_PriCtrlStr.DMA_SourceProtCtrl = DMA_SourcePrivileged;
  DMA_PriCtrlStr.DMA_DestProtCtrl = DMA_DestPrivileged;
  /* Set Channel Structure */
  DMA_InitStr.DMA_PriCtrlData = &DMA_PriCtrlStr;
  DMA_InitStr.DMA_Priority = DMA_Priority_High;
  DMA_InitStr.DMA_UseBurst = DMA_BurstClear;
  DMA_InitStr.DMA_SelectDataStructure = DMA_CTRL_DATA_PRIMARY;
  /* Init DMA channel */
  DMA_Init(DMA_Channel_SSP1_RX, &DMA_InitStr);

  /* DMA_Channel_SSP2_RX configuration ---------------------------------*/
  /* Set Primary Control Data */
  DMA_PriCtrlStr.DMA_SourceBaseAddr = (uint32_t)(&(MDR_SSP2->DR));
  DMA_PriCtrlStr.DMA_DestBaseAddr = (uint32_t)DstBuf2;
  /* Init DMA channel */
  DMA_Init(DMA_Channel_SSP2_RX, &DMA_InitStr);

  /* DMA_Channel_SSP1_TX configuration ---------------------------------*/
  /* Set Primary Control Data */
  DMA_PriCtrlStr.DMA_SourceBaseAddr = (uint32_t)SrcBuf1;
  DMA_PriCtrlStr.DMA_DestBaseAddr = (uint32_t)(&(MDR_SSP1->DR));
  DMA_PriCtrlStr.DMA_SourceIncSize = DMA_SourceIncHalfword;
  DMA_PriCtrlStr.DMA_DestIncSize = DMA_DestIncNo;
  DMA_InitStr.DMA_Priority = DMA_Priority_Default;
  /* Init DMA channel */
  DMA_Init(DMA_Channel_SSP1_TX, &DMA_InitStr);

  /* DMA_Channel_SSP2_TX configuration ---------------------------------*/
  /* Set Primary Control Data */
  DMA_PriCtrlStr.DMA_SourceBaseAddr = (uint32_t)SrcBuf2;
  DMA_PriCtrlStr.DMA_DestBaseAddr = (uint32_t)(&(MDR_SSP2->DR));
  /* Init DMA channel */
  DMA_Init(DMA_Channel_SSP2_TX, &DMA_InitStr);

  /* Enable SSP1 */
  SSP_Cmd(MDR_SSP1, ENABLE);
  /* Enable SSP2 */
  SSP_Cmd(MDR_SSP2, ENABLE);

  /* Transfer complete */
  while((SSP_GetFlagStatus(MDR_SSP1, SSP_FLAG_BSY)))
  {
  }
  while((SSP_GetFlagStatus(MDR_SSP2, SSP_FLAG_BSY)))
  {
  }

  /* Check the corectness of written dada */
  TransferStatus1 = Verif_mem ((BufferSize), SrcBuf1, DstBuf2);
  TransferStatus2 = Verif_mem ((BufferSize), SrcBuf2, DstBuf1);
  /* TransferStatus1, TransferStatus2 = PASSED, if the data transmitted and received
     are correct */
  /* TransferStatus1, TransferStatus2 = FAILED, if the data transmitted and received
     are different */

  while(1)
  {
  }
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

/** @} */ /* End of group DMA_SPI_RAM_92 */

/** @} */ /* End of group __MDR32F9Q2_EVAL */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2011 Milandr *********/

/* END OF FILE main.c */

