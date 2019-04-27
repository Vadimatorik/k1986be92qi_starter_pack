/**
  ******************************************************************************
  * @file    Examples/MDR32F9Q1_EVAL/TIMER/TIMER_DMA/main.c
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
#include "MDR32F9Qx_timer.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_dma.h"
#include "MDR32F9Qx_port.h"

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F9Q1_EVAL MDR32F9Q1 Evaluation Board
  * @{
  */

/** @addtogroup TIMER_DMA_91 TIMER_DMA
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
TIMER_CntInitTypeDef sTIM_CntInit;
TIMER_ChnInitTypeDef sTIM_ChnInit;
TIMER_ChnOutInitTypeDef sTIM_ChnOutInit;
PORT_InitTypeDef PORT_InitStructure;

uint16_t DstBuf[BufferSize];

volatile TestStatus TransferStatus = FAILED;

/* Private function prototypes -----------------------------------------------*/
void Init_RAM (uint16_t *addr, uint32_t size);
uint32_t ps_rand(uint32_t addr);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
void main(void)
{
uint32_t i;

  RST_CLK_DeInit();
  RST_CLK_CPU_PLLconfig (RST_CLK_CPU_PLLsrcHSIdiv2,0);
  /* Enable peripheral clocks --------------------------------------------------*/
  RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_TIMER1 | RST_CLK_PCLK_DMA),ENABLE);
  RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTA), ENABLE);

  /* Init NVIC */
  SCB->AIRCR = 0x05FA0000 | ((uint32_t)0x500);
  SCB->VTOR = 0x08000000;
  /* Disable all interrupt */
  NVIC->ICPR[0] = 0xFFFFFFFF;
  NVIC->ICER[0] = 0xFFFFFFFF;

  /* Disable all DMA request */
  MDR_DMA->CHNL_REQ_MASK_CLR = 0xFFFFFFFF;
  MDR_DMA->CHNL_USEBURST_CLR = 0xFFFFFFFF;

  /* Reset PORTB settings */
  PORT_DeInit(MDR_PORTB);
  /* Reset PORTF settings */
  PORT_DeInit(MDR_PORTF);

  /* Configure TIMER1 pins: CH1, CH2 */

  /* Configure PORTA pins 1, 3 */
  PORT_InitStructure.PORT_Pin   = PORT_Pin_1;
  PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
  PORT_InitStructure.PORT_FUNC  = PORT_FUNC_ALTER;
  PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_FAST;
  PORT_Init(MDR_PORTA, &PORT_InitStructure);
  PORT_InitStructure.PORT_Pin   = PORT_Pin_3;
  PORT_InitStructure.PORT_OE    = PORT_OE_IN;
  PORT_Init(MDR_PORTA, &PORT_InitStructure);

  /* Init RAM */
  Init_RAM (DstBuf, BufferSize);

  /* Reset all TIMER1 settings */
  TIMER_DeInit(MDR_TIMER1);

  TIMER_BRGInit(MDR_TIMER1,TIMER_HCLKdiv1);

  /* TIM1 configuration ------------------------------------------------*/
  /* Initializes the TIMERx Counter ------------------------------------*/
  sTIM_CntInit.TIMER_Prescaler                = 0x10;
  sTIM_CntInit.TIMER_Period                   = 0x200;
  sTIM_CntInit.TIMER_CounterMode              = TIMER_CntMode_ClkFixedDir;
  sTIM_CntInit.TIMER_CounterDirection         = TIMER_CntDir_Up;
  sTIM_CntInit.TIMER_EventSource              = TIMER_EvSrc_None;
  sTIM_CntInit.TIMER_FilterSampling           = TIMER_FDTS_TIMER_CLK_div_1;
  sTIM_CntInit.TIMER_ARR_UpdateMode           = TIMER_ARR_Update_Immediately;
  sTIM_CntInit.TIMER_ETR_FilterConf           = TIMER_Filter_1FF_at_TIMER_CLK;
  sTIM_CntInit.TIMER_ETR_Prescaler            = TIMER_ETR_Prescaler_None;
  sTIM_CntInit.TIMER_ETR_Polarity             = TIMER_ETRPolarity_NonInverted;
  sTIM_CntInit.TIMER_BRK_Polarity             = TIMER_BRKPolarity_NonInverted;
  TIMER_CntInit (MDR_TIMER1,&sTIM_CntInit);

  /* Initializes the TIMER1 Channel1 -------------------------------------*/
  TIMER_ChnStructInit(&sTIM_ChnInit);

  sTIM_ChnInit.TIMER_CH_Number              = TIMER_CHANNEL1;
  sTIM_ChnInit.TIMER_CH_Mode                = TIMER_CH_MODE_PWM;
  sTIM_ChnInit.TIMER_CH_REF_Format          = TIMER_CH_REF_Format3;

  TIMER_ChnInit(MDR_TIMER1, &sTIM_ChnInit);

  TIMER_SetChnCompare(MDR_TIMER1, TIMER_CHANNEL1, 0x100);

  /* Initializes the TIMER1 Channel1 Output -------------------------------*/

  TIMER_ChnOutStructInit(&sTIM_ChnOutInit);

  sTIM_ChnOutInit.TIMER_CH_Number                   = TIMER_CHANNEL1;
  sTIM_ChnOutInit.TIMER_CH_DirOut_Polarity          = TIMER_CHOPolarity_NonInverted;
  sTIM_ChnOutInit.TIMER_CH_DirOut_Source            = TIMER_CH_OutSrc_REF;
  sTIM_ChnOutInit.TIMER_CH_DirOut_Mode              = TIMER_CH_OutMode_Output;

  TIMER_ChnOutInit(MDR_TIMER1, &sTIM_ChnOutInit);

  /* Initializes the TIMER1 Channel2 -------------------------------------*/
  TIMER_ChnStructInit(&sTIM_ChnInit);

  sTIM_ChnInit.TIMER_CH_Number              = TIMER_CHANNEL2;
  sTIM_ChnInit.TIMER_CH_Mode                = TIMER_CH_MODE_CAPTURE;

  TIMER_ChnInit(MDR_TIMER1, &sTIM_ChnInit);

  /* Initializes the TIMER1 Channel2 Output -------------------------------*/

  TIMER_ChnOutStructInit(&sTIM_ChnOutInit);

  sTIM_ChnOutInit.TIMER_CH_Number                   = TIMER_CHANNEL2;
  sTIM_ChnOutInit.TIMER_CH_DirOut_Polarity          = TIMER_CHOPolarity_NonInverted;
  sTIM_ChnOutInit.TIMER_CH_DirOut_Source            = TIMER_CH_OutSrc_Only_0;
  sTIM_ChnOutInit.TIMER_CH_DirOut_Mode              = TIMER_CH_OutMode_Input;

  TIMER_ChnOutInit(MDR_TIMER1, &sTIM_ChnOutInit);

  /* Enable TIMER1 DMA request */
  TIMER_DMACmd(MDR_TIMER1,(TIMER_STATUS_CCR_CAP_CH2), ENABLE);

  /* Reset all DMA settings */
  DMA_DeInit();
  DMA_StructInit(&DMA_InitStr);

  /* DMA_Channel_TIM1 configuration ---------------------------------*/
  /* Set Primary Control Data */
  DMA_PriCtrlStr.DMA_SourceBaseAddr = (uint32_t)(&(MDR_TIMER1->CCR2));
  DMA_PriCtrlStr.DMA_DestBaseAddr = (uint32_t)DstBuf;
  DMA_PriCtrlStr.DMA_SourceIncSize = DMA_SourceIncNo;
  DMA_PriCtrlStr.DMA_DestIncSize = DMA_DestIncHalfword;
  DMA_PriCtrlStr.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_PriCtrlStr.DMA_Mode = DMA_Mode_Basic;
  DMA_PriCtrlStr.DMA_CycleSize = BufferSize;
  DMA_PriCtrlStr.DMA_NumContinuous = DMA_Transfers_1;
  DMA_PriCtrlStr.DMA_SourceProtCtrl = DMA_SourcePrivileged;
  DMA_PriCtrlStr.DMA_DestProtCtrl = DMA_DestPrivileged;
  /* Set Channel Structure */
  DMA_InitStr.DMA_PriCtrlData = &DMA_PriCtrlStr;
  DMA_InitStr.DMA_Priority = DMA_Priority_High;
  DMA_InitStr.DMA_UseBurst = DMA_BurstClear;
  DMA_InitStr.DMA_SelectDataStructure = DMA_CTRL_DATA_PRIMARY;
  /* Init DMA channel */
  DMA_Init(DMA_Channel_TIM1, &DMA_InitStr);

  /* Enable TIMER1 */
  TIMER_Cmd(MDR_TIMER1,ENABLE);

  /* Transfer complete */
  while((DMA_GetFlagStatus(DMA_Channel_TIM1, DMA_FLAG_CHNL_ENA)))
  {
  }

  /* Check the corectness of written dada */
  for(i = 0; i < BufferSize; i++)
  {
    if (DstBuf[i] != MDR_TIMER1->CCR1)
    {
      TransferStatus &= FAILED;
      break;
    }
    else
    {
      TransferStatus = PASSED;
    }
  }
  /* TransferStatus = PASSED, if the data transmitted are correct */
  /* TransferStatus = FAILED, if the data transmitted are not correct */

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

/** @} */ /* End of group TIMER_DMA_91 */

/** @} */ /* End of group __MDR32F9Q1_EVAL */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */


/******************* (C) COPYRIGHT 2011 Milandr *********/

/* END OF FILE main.c */
