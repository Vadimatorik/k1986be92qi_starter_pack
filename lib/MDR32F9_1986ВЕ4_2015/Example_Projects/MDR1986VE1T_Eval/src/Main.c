/**
  ******************************************************************************
  * @file    Main.c
  * @author  Milandr Application Team
  * @version V3.0.0
  * @date    10.09.2013
  * @brief   Main program body
  ******************************************************************************
  * <br><br>
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, Milandr SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2013 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "types.h"
#include "lcd.h"
#include "gl.h"
#include "text.h"
#include "joystick.h"
#include "leds.h"
#include "menu.h"
#include "time.h"
#include "lowpower.h"
#include "Demo_Init.h"

/** @addtogroup __MDR1986VE1T_Eval_Demo MDR1986VE1T Demonstration Example
  * @{
  */

/** @addtogroup Main Main
  * @{
  */

/** @defgroup Main_Functions Main Functions
  * @{
  */

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
#ifdef __CC_ARM
int main(void)
#else
void main(void)
#endif
{

  Demo_Init();
  Calendar_Init();
  Menu_Init();
  LowPower_Init();
  DisplayMenu();
  ReadKey();
}

/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the source file ID, the source line number
*                : and (if USE_ASSERT_INFO == 2) expression text where
*                : the assert_param error has occurred.
* Input          : file_id - pointer to the source file name
*                : line - assert_param error line source number
*                : expr - expression text
* Output         : None
* Return         : None
*******************************************************************************/

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

  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_ASSERT_INFO */

/** @} */ /* End of group Main_Functions */

/** @} */ /* End of group Main */

/** @} */ /* End of group __MDR1986VE1T_Eval_Demo */

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE Main.c */

