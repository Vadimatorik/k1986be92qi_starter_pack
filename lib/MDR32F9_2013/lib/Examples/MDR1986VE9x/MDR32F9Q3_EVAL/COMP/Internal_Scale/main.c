/**
  ******************************************************************************
  * @file    Examples/MDR32F9Q3_EVAL/COMP/Internal_Scale/main.c
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
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_comp.h"

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F9Q3_EVAL MDR32F9Q3 Evaluation Board
  * @{
  */

/** @addtogroup COMP_Internal_Scale_93 COMP_Internal_Scale
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define USE_INVERTION
#define RANGE			COMP_CVREF_RANGE_Up;
#define SCALE			COMP_CVREF_SCALE_8_div_32;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;
COMP_InitTypeDef COMP_InitStructure;
COMP_CVRefInitTypeDef COMP_CVRefInitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
static uint32_t CompRezAs = 0;
static uint32_t CompRezSy = 0;

  /* Enables the HSI clock on PORTE */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTE,ENABLE);

  /* Fill PortInit structure*/
  PORT_InitStructure.PORT_PULL_UP = PORT_PULL_UP_OFF;
  PORT_InitStructure.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
  PORT_InitStructure.PORT_MODE = PORT_MODE_ANALOG;

  /* Configure PORTE pins 2 (COMP_IN1) */
  PORT_InitStructure.PORT_OE = PORT_OE_OUT;
  PORT_InitStructure.PORT_Pin = PORT_Pin_2;
  PORT_Init(MDR_PORTE, &PORT_InitStructure);

  /* Enables the HSI clock for COMP control */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_COMP,ENABLE);

  /* Fills each COMP_InitStructure member with its default value */
  COMP_StructInit(&COMP_InitStructure);

  /* Initialize COMP_InitStructure */
  COMP_InitStructure.COMP_PlusInputSource = COMP_PlusInput_CVREF;
  COMP_InitStructure.COMP_MinusInputSource = COMP_MinusInput_IN1;
#ifdef USE_INVERTION
  COMP_InitStructure.COMP_OutInversion = COMP_OUT_INV_Enable;
#endif

  /* Configure COMP */
  COMP_Init(&COMP_InitStructure);

  /* Fills each COMP_CVRefInitStructure member with its default value */
  COMP_CVRefStructInit(&COMP_CVRefInitStructure);

  /* Initialize COMP_CVRefInitStructure */
  COMP_CVRefInitStructure.COMP_CVRefSource = COMP_CVREF_SOURCE_AVdd;
  COMP_CVRefInitStructure.COMP_CVRefRange = RANGE;
  COMP_CVRefInitStructure.COMP_CVRefScale = SCALE;

  /* Configure COMP CVRef */
  COMP_CVRefInit(&COMP_CVRefInitStructure);

  /* Enables COMP peripheral */
  COMP_Cmd(ENABLE);

  /* Check READY flag */
  while(COMP_GetCfgFlagStatus(COMP_CFG_FLAG_READY) != SET);

  /* Enables COMP CVRef */
  COMP_CVRefCmd(ENABLE);

  /* Infinite loop */
  while (1)
  {
    CompRezAs = COMP_GetFlagStatus(COMP_STATUS_FLAG_AS);
	CompRezSy = COMP_GetFlagStatus(COMP_STATUS_FLAG_SY);
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

/** @} */ /* End of group COMP_Internal_Scale_93 */

/** @} */ /* End of group __MDR32F9Q3_EVAL */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2011 Milandr *********/

/* END OF FILE main.c */

