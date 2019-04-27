/**
  ******************************************************************************
  * @file    Menu_gl.c
  * @author  Milandr Application Team
  * @version V3.0.0
  * @date    10.09.2013
  * @brief   This file contains all the "Graphics" menu handlers
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
#include <MDR32F9Qx_adc.h>
#include "MDR32F9Qx_board.h"
#include <Menu.h>
#include "Menu_items.h"
#include "gl.h"
#include "lcd.h"
#include "joystick.h"
#include "systick.h"
#include "text.h"
#include "adc.h"

/** @addtogroup __MDR1986VE3_Eval_Demo MDR1986VE3 Demonstration Example
  * @{
  */

/** @addtogroup Menu Menu
  * @{
  */

/** @addtogroup Menu_Graphics Menu Graphics
  * @{
  */


/** @defgroup Menu_Graphics_Private_Constants Menu Graphics Private Constants
  * @{
  */

/** @} */ /* End of group Menu_Graphics_Private_Constants */

/** @addtogroup Menu_Graphics_Private_Functions Menu Graphics Private Functions
  * @{
  */

/** @addtogroup Menu_Graphics_Elements Menu Graphics Elements
  * @{
  */

/*******************************************************************************
* Function Name  : DisplayTriangle
* Description    : Draws unfilled right triangle
* Input          : up angle õ-coordinate
*                : up angle y-coordinate
*                : side - cathetus length, in pixels
* Output         : None
* Return         : None
*******************************************************************************/
static void DisplayTriangle (int32_t x, int32_t y, int32_t side)
{
  LCD_Line(x, y, x + side, y);
  LCD_Line(x + side, y, x + side, y + side);
  LCD_Line(x, y, x + side, y + side);
}

/*******************************************************************************
* Function Name  : DisplayFillingTriangle
* Description    : Draws filled right triangle
* Input          : up angle õ-coordinate
*                : up angle y-coordinate
*                : side - cathetus length, in pixels
* Output         : None
* Return         : None
*******************************************************************************/
static void DisplayFillingTriangle (int32_t x, int32_t y, int32_t side)
{
  int32_t i;

  for (i = 0; i < side + 1; i++)
  {
    LCD_Line(x + i, y + i, x + side, y + i);
  }
}

/*******************************************************************************
* Function Name  : DisplayFillingCircle
* Description    : Draws circle
* Input          : õ      - center x-coordinate
*                : y      - center y-coordinate
*                : radius - radius, in pixel
* Output         : None
* Return         : None
*******************************************************************************/
void DisplayFillingCircle (int32_t x, int32_t y, int32_t radius)
{
  int32_t i;

  for (i = 0; i < radius + 1; i++)
  {
    LCD_Circle(x, y, i);
  }
}

/*******************************************************************************
* Function Name  : DisplayRectangle
* Description    : Draws rectangle
* Input          : õ      - left up rectangle corner x-coordinate
*                : y      - left up rectangle corner y-coordinate
*                : side_x - horizontal side length, in pixels
*                : side_y - vertical side length, in pixels
* Output         : None
* Return         : None
*******************************************************************************/
void DisplayRectangle (int32_t x, int32_t y, int32_t side_x, int32_t side_y)
{
  LCD_Line(x, y, x + side_x, y);
  LCD_Line(x, y, x, y + side_y);
  LCD_Line(x + side_x, y, x + side_x, y + side_y);
  LCD_Line(x, y + side_y, x + side_x, y + side_y);
}

/*******************************************************************************
* Function Name  : DisplayFillingRectangle
* Description    : Draws block (filled rectangle)
* Input          : õ      - left up rectangle corner x-coordinate
*                : y      - left up rectangle corner y-coordinate
*                : side_x - horizontal side length, in pixels
*                : side_y - vertical side length, in pixels
* Output         : None
* Return         : None
*******************************************************************************/
void DisplayFillingRectangle (int32_t x, int32_t y, int32_t side_x, int32_t side_y)
{
  int32_t i;
  for (i = 0; i < side_y; i++)
  {
    LCD_Line(x, y + i, x + side_x, y + i);
  }
}

/** @} */ /* End of group Menu_Graphics_Elements */

/** @addtogroup Menu_Graphics_Functions Menu Graphics Functions
  * @{
  */

/*******************************************************************************
* Function Name  : ElementsFunc
* Description    : Graphical elements drawing
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ElementsFunc(void)
{
#define base_x 25
#define base_y 14
#define side   16

#define offs_x 8
#define offs_y 5

#define circle_radius side / 2
#define circle_x base_x + side + offs_x + circle_radius
#define circle_y base_y + circle_radius
#define circle_filling_y circle_y + circle_radius * 2 + offs_y

#define rectangle_x base_x + side * 2 + offs_x * 2
#define block_y  base_y + side + offs_y

  /* Header output */
  LCD_CLS();
  CurrentMethod = MET_OR;
  DisplayMenuTitle("Elements");

  /* Build primitives and wait for key up */
  DisplayTriangle (base_x, base_y, side);
  DisplayFillingTriangle (base_x, base_y + side + offs_y, side);

  LCD_Circle(circle_x, circle_y, circle_radius);
  DisplayFillingCircle (circle_x, circle_filling_y, circle_radius);

  DisplayRectangle (rectangle_x, base_y, side * 2, side);
  DisplayFillingRectangle (rectangle_x, block_y, side * 2, side);

  WAIT_UNTIL_KEY_RELEASED(SEL);

  /* Wait for SEL pressed and return to main menu */
  BackToMenuOnBack();//BackToMenuOnSel();
}

/*******************************************************************************
* Function Name  : IndicatorsFunc
* Description    : Indicators drawing
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void IndicatorsFunc(void)
{
#define side_x 4

  int32_t i, sign, DelayCount;

  sFONT *OldFont = CurrentFont;

  LCD_Method OldMethod = CurrentMethod;

  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;

  /* Print prompt and wait for key SEL pressed */
  LCD_PUTS(0, 12, "Turn the Trimmer TRIM");
  LCD_PUTS(0, 22, "to control the delay");
  LCD_PUTS(0, 32, "between style frames.");
  LCD_PUTS(0, 42, "Push JoyStick SEL to");
  LCD_PUTS(0, 52, "start, BACK to stop.");

  while (!KEY_PRESSED(SEL))
  {

  }

  /* Configure ADC channel 7 */
  ADC_Config();
  /* ADC1 enable */
  ADC1_Cmd(ENABLE);

  /* Print header and wait for key up */
  LCD_CLS();
  CurrentMethod = MET_OR;
  DisplayMenuTitle("Indicators");
  WAIT_UNTIL_KEY_RELEASED(SEL);

  /* Draw the progress bar */
  LCD_PUTS(24,18,"0");
  DisplayRectangle (32, 14, 64, 14);
  LCD_PUTS(97,18,"100");
  /* Draw the scale */
  LCD_Circle(63, 63, 30);
  LCD_Line(63, 34, 63, 41);
  LCD_Line(35, 53, 42, 56);
  LCD_Line(91, 53, 84, 56);
  LCD_Line(45, 39, 51, 45);
  LCD_Line(81, 39, 75, 45);

  /* Emulate progress - from 0 to 100% and back */
  /* Emulate scale bar trembling */
  CurrentMethod = MET_XOR;
  for (i = 0, sign = 1; !KEY_PRESSED(BACK); )
  {
    int32_t ni = i + side_x * sign;

    /* Trimming results in animation speed changes */
    DelayCount = (ADC1_GetResult() & ADC_RESULT_Msk) + 51;

    /* Draw the bar */
    DisplayFillingRectangle (i + 34, 16, side_x - 1, 11);
    if (ni > 60 || ni < 0)
    {
      sign = -sign;
    }
    else
    {
      i = ni;
    }
    DelayCount /= 10;
    SysTickDelay(DelayCount);

    /* Draw the arrow */
    LCD_Line(86, 46, 63, 63);
    SysTickDelay(DelayCount);
    LCD_Line(86, 46, 63, 63);
    SysTickDelay(DelayCount);
    LCD_Line(84, 44, 63, 63);
    SysTickDelay(DelayCount);
    LCD_Line(84, 44, 63, 63);
    SysTickDelay(DelayCount);
  }

  /* SEL is pressed - return to the main menu */
  CurrentFont = OldFont;
  CurrentMethod = OldMethod;
  /* ADC1 disable */
  ADC1_Cmd(DISABLE);
  DisplayMenu();
}

/** @} */ /* End of group Menu_Graphics_Functions */

/** @} */ /* End of group Menu_Graphics_Private_Functions */

/** @} */ /* End of group Menu_Graphics */

/** @} */ /* End of group Menu */

/** @} */ /* End of group __MDR1986VE3_Eval_Demo */

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE Menu_gl.c */

