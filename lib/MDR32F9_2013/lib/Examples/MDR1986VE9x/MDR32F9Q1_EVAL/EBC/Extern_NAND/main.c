/**
  ******************************************************************************
  * @file    Examples/MDR32F9Q1_EVAL/EBC/Extern_NAND/main.c
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
#include "mdr32f9Qx_ebc.h"

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F9Q1_EVAL MDR32F9Q1 Evaluation Board
  * @{
  */

/** @addtogroup EXT_BUS_Extern_NAND_91 EXT_BUS_Extern_NAND
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;
EBC_InitTypeDef EBC_InitStruct;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
  /* Enables the HSI clock for EBC control */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_EBC,ENABLE);

  /* Initializes EBC_InitStruct by default values */
  EBC_StructInit(&EBC_InitStruct);

  /* Specifies external bus mode NAND */
  EBC_InitStruct.EBC_Mode = EBC_MODE_NAND;

  /* Calculates the t_rc number for 8 MHz frequency and time interval = 500 ns */
  EBC_InitStruct.EBC_NandTrc =  EBC_CalcNandCycles(8000,500);

  /* Calculates the t_wc number for 8 MHz frequency and time interval = 250 ns */
  EBC_InitStruct.EBC_NandTwc =  EBC_CalcNandCycles(8000,250);

  /* Calculates the t_rea number for 8 MHz frequency and time interval = 500 ns */
  EBC_InitStruct.EBC_NandTrea =  EBC_CalcNandCycles(8000,500);

  /* Calculates the t_wp number for 8 MHz frequency and time interval = 250 ns */
  EBC_InitStruct.EBC_NandTwp =  EBC_CalcNandCycles(8000,250);

  /* Calculates the t_whr number for 8 MHz frequency and time interval = 1200 ns */
  EBC_InitStruct.EBC_NandTwhr =  EBC_CalcNandCycles(8000,1200);

  /* Calculates the t_alea number for 8 MHz frequency and time interval = 800 ns */
  EBC_InitStruct.EBC_NandTalea =  EBC_CalcNandCycles(8000,800);

  /* Calculates the t_rr number for 8 MHz frequency and time interval = 750 ns */
  EBC_InitStruct.EBC_NandTrr =  EBC_CalcNandCycles(8000,750);

  /* Initializes the EBC peripheral registers */
  EBC_Init(&EBC_InitStruct);

  /* Infinite loop */
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

/** @} */ /* End of group EXT_BUS_Extern_NAND_91 */

/** @} */ /* End of group __MDR32F9Q1_EVAL */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2011 Milandr *********/

/* END OF FILE main.c */

