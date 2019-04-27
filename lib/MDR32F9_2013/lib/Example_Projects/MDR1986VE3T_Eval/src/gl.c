/**
  ******************************************************************************
  * @file    gl.c
  * @author  Milandr Application Team
  * @version V3.0.0
  * @date    10.09.2013
  * @brief   This file provides all the functions for the graphic primitive
  *          output to LCD.
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
#include "lcd.h"
#include "gl.h"
#include "joystick.h"

/** @addtogroup __MDR1986VE3_Eval_Demo MDR1986VE3 Demonstration Example
  * @{
  */

/** @addtogroup LCD_Graphics LCD Graphics
  * @{
  */

/** @defgroup LCD_Graphics_Private_Functions LCD Graphics Private Functions
  * @{
  */

/*******************************************************************************
* Function Name  : LCD_PutPixel
* Description    : Outputs one pixel to the given screen coordinates.
* Input          : õ - x-coordinate
*                : y - y-coordinate
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_PutPixel(uint32_t x, uint32_t y)
{
  uint32_t shifted, page;
  uint32_t data;

  if ((x>MAX_X)|(y>MAX_Y))
  {
    return;
  }

  SetCrystal((LCD_Crystal)(x/64));
  x %= 64;

  page = y/8;
  shifted = (1 << (y%8));
  LCD_SET_PAGE(page);
  LCD_SET_ADDRESS(x);
  data = ReadLCD_Data();
  switch (CurrentMethod)
  {
    case MET_OR :   data |= shifted;    break;
    case MET_XOR :  data ^= shifted;    break;
    case MET_AND :  data &= ~shifted;  	break;
  }
  LCD_SET_ADDRESS(x);
  WriteLCD_Data(data);
}

/*******************************************************************************
* Function Name  : LCD_Line
* Description    : Outputs line from (x1,y1) point to (x2,y2) point.
* Input          : õ1 - start point x-coordinate
*                : y1 - start point y-coordinate
*                : x2 - end point x-coordinate
*                : y2 - end point y-coordinate
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
  int32_t dx, dy, i1, i2, i, kx, ky;
  int32_t d;
  int32_t x, y;
  int32_t flag;

  dy = y2 - y1;
  dx = x2 - x1;
  if (dx == 0 && dy == 0)
  {
    LCD_PutPixel(x1, y1);
    return;
  }

  flag = kx = ky = 1;

  if (dx < 0)
  {
    dx = -dx;
    kx = -1;
  }
  else if (dx == 0)
  {
    kx = 0;
  }

  if (dy < 0)
  {
    dy = -dy;
    ky = -1;
  }

  if (dx < dy)
  {
    flag = 0;
    d = dx;
    dx = dy;
    dy = d;
  }

  i1 = dy + dy;
  d = i1 - dx;
  i2 = d - dx;
  x = x1;
  y = y1;

  for (i=0; ; i++)
  {
    LCD_PutPixel(x,y);
    if (i >= dx)
    {
      break;
    }
    if (flag)
    {
      x += kx;
    }
    else
    {
      y += ky;
    }

    if (d < 0)
    {
      d += i1;
    }
    else
    {
      d += i2;
      if (flag)
      {
        y += ky;
      }
      else
      {
        x += kx;
      }
    }
  }
}

/*******************************************************************************
* Function Name  : LCD_Circle
* Description    : Draws circle with radius r and center in (x,y) point.
* Input          : õ - center x-coordinate
*                : y - center y-coordinate
*                : r - radius (in pixels)s
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Circle(uint32_t xc, uint32_t yc, uint32_t r)
{
  int32_t d, x, y;

  for (x = 0, y = r, d = 3-2*r; ;)
  {
    LCD_PutPixel(x+xc, y+yc);
    LCD_PutPixel(x+xc, -y+yc);
    LCD_PutPixel(-x+xc, -y+yc);
    LCD_PutPixel(-x+xc, y+yc);
    LCD_PutPixel(y+xc, x+yc);
    LCD_PutPixel(y+xc, -x+yc);
    LCD_PutPixel(-y+xc, -x+yc);
    LCD_PutPixel(-y+xc, x+yc);

    if (x >= y)
    {
      break;
    }

    if (d <= 0)
    {
      d += 4*x+6;
    }
    else
    {
      d += 4*(x-y)+10;
      y--;
    }
    x++;
  }
}

/** @} */ /* End of group LCD_Graphics_Private_Functions */

/** @} */ /* End of group LCD_Graphics */

/** @} */ /* End of group __MDR1986VE3_Eval_Demo */

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE gl.c */

