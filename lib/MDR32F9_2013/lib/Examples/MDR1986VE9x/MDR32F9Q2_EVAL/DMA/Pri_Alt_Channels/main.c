/**
  ******************************************************************************
  * @file    Examples/MDR32F9Q2_EVAL/DMA/Pri_Alt_Channels/main.c
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
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_dma.h"

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F9Q2_EVAL MDR32F9Q2 Evaluation Board
  * @{
  */


/** @addtogroup DMA_Pri_Alt_Channels_92 DMA_Pri_Alt_Channels
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define SIZE        0x400

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
RST_CLK_FreqTypeDef CLK_FrequencyStructure;
uint32_t DestBuf[SIZE];
uint32_t PriBuf[SIZE];
uint32_t AltBuf[SIZE];

volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;

/* Private function prototypes -----------------------------------------------*/
void Init_RAM (uint32_t *addr, uint32_t size);
TestStatus Verif_mem (uint32_t BufSize, uint32_t *pBuffer1, uint32_t *pBuffer2);
uint32_t ps_rand(uint32_t addr);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initialisation memory pseudo random value
  * @param  addr - memory address
  * @param  size - memory size
  * @retval None
  */
void Init_RAM (uint32_t *addr, uint32_t size)
{
uint32_t i;

  for (i = 0; i < size; i++)
  {
    *addr++ = ps_rand((uint32_t)addr + i*4);
  }
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufSize: buffer's size
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Verif_mem (uint32_t BufSize, uint32_t *pBuffer1, uint32_t *pBuffer2)
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
  * @brief  Generation random values
  * @param  addr -
  * @retval None
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
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
  DMA_ChannelInitTypeDef DMA_InitStr;
  DMA_CtrlDataInitTypeDef DMA_PriCtrlStr;
  DMA_CtrlDataInitTypeDef DMA_AltCtrlStr;

  uint32_t DMA_Channel = 3;

  RST_CLK_DeInit();
  RST_CLK_PCLKcmd(RST_CLK_PCLK_DMA, ENABLE);

  /* Init RAM */
  Init_RAM (DestBuf, SIZE);
  Init_RAM (PriBuf, SIZE);
  Init_RAM (AltBuf, SIZE);

  /* Reset all settings */
  DMA_DeInit();
  DMA_StructInit(&DMA_InitStr);

  /* Set Primary Control Data */
  DMA_PriCtrlStr.DMA_SourceBaseAddr = (uint32_t)PriBuf;
  DMA_PriCtrlStr.DMA_DestBaseAddr = (uint32_t)DestBuf;
  DMA_PriCtrlStr.DMA_SourceIncSize = DMA_SourceIncWord;
  DMA_PriCtrlStr.DMA_DestIncSize = DMA_DestIncWord;
  DMA_PriCtrlStr.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
  DMA_PriCtrlStr.DMA_Mode = DMA_Mode_Basic;
  DMA_PriCtrlStr.DMA_CycleSize = SIZE;
  DMA_PriCtrlStr.DMA_NumContinuous = DMA_Transfers_16;
  DMA_PriCtrlStr.DMA_SourceProtCtrl = DMA_SourcePrivileged;
  DMA_PriCtrlStr.DMA_DestProtCtrl = DMA_DestPrivileged;

  /* Set Alternate Control Data */
  DMA_AltCtrlStr.DMA_SourceBaseAddr = (uint32_t)AltBuf;
  DMA_AltCtrlStr.DMA_DestBaseAddr   = (uint32_t)DestBuf;
  DMA_AltCtrlStr.DMA_SourceIncSize = DMA_SourceIncWord;
  DMA_AltCtrlStr.DMA_DestIncSize = DMA_DestIncWord;
  DMA_AltCtrlStr.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
  DMA_AltCtrlStr.DMA_Mode = DMA_Mode_AutoRequest;
  DMA_AltCtrlStr.DMA_CycleSize = SIZE;
  DMA_AltCtrlStr.DMA_NumContinuous = DMA_Transfers_16;
  DMA_AltCtrlStr.DMA_SourceProtCtrl = DMA_SourcePrivileged;
  DMA_AltCtrlStr.DMA_DestProtCtrl = DMA_DestPrivileged;

  /* Set Channel Structure */
  DMA_InitStr.DMA_PriCtrlData = &DMA_PriCtrlStr;
  DMA_InitStr.DMA_AltCtrlData = &DMA_AltCtrlStr;
  DMA_InitStr.DMA_Priority = DMA_Priority_Default;
  DMA_InitStr.DMA_UseBurst = DMA_BurstClear;
  DMA_InitStr.DMA_SelectDataStructure = DMA_CTRL_DATA_PRIMARY;

  /* Init DMA channel */
  DMA_Init(DMA_Channel, &DMA_InitStr);

  /* Run channel */
  DMA_Cmd(DMA_Channel, ENABLE);
  DMA_Request(DMA_Channel);

  /* Transfer complete */
  while (DMA_GetFlagStatus(DMA_Channel, DMA_FLAG_CHNL_ENA))
  {
    if((MDR_DMA->STATUS & 0x000000F0)==0x00000000)
    {
      DMA_Request(DMA_Channel);
    }
  }
  /* Check the corectness of written data */
  TransferStatus1 = Verif_mem(SIZE, PriBuf, DestBuf);
  /* TransferStatus1 = PASSED, if the data transmitted and received are correct */
  /* TransferStatus1 = FAILED, if the data transmitted and received are different */

  /* Set Channel Structure */
  DMA_InitStr.DMA_SelectDataStructure = DMA_CTRL_DATA_ALTERNATE;

  /* Init DMA channel */
  DMA_Init(DMA_Channel, &DMA_InitStr);

  /* Run channel */
  DMA_Cmd(DMA_Channel, ENABLE);
  DMA_Request(DMA_Channel);

  /* Transfer complete */
  while (DMA_GetFlagStatus(DMA_Channel, DMA_FLAG_CHNL_ENA))
  {
  }
  /* Check the corectness of written data */
  TransferStatus2 = Verif_mem(SIZE, AltBuf, DestBuf);
  /* TransferStatus2 = PASSED, if the data transmitted and received are correct */
  /* TransferStatus2 = FAILED, if the data transmitted and received are different */

  while (1)
  {
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

/** @} */ /* End of group DMA_Pri_Alt_Channels_92 */

/** @} */ /* End of group __MDR32F9Q2_EVAL */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */


/******************* (C) COPYRIGHT 2011 Milandr *********/

/* END OF FILE main.c */


