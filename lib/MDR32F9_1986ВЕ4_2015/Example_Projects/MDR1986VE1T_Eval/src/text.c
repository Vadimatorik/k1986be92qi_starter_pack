/**
  ******************************************************************************
  * @file    text.c
  * @author  Milandr Application Team
  * @version V3.0.0
  * @date    10.09.2013
  * @brief   This file provides all the functions for the symbol  and text
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
#include <string.h>
#include <MDR32F9Qx_adc.h>
#include "lcd.h"
#include "text.h"
#include "joystick.h"
#include "systick.h"
#include "menu.h"

/** @addtogroup __MDR1986VE1T_Eval_Demo MDR1986VE1T Demonstration Example
  * @{
  */

/** @addtogroup LCD_Text LCD Text
  * @{
  */

/** @defgroup LCD_Text_Private_Constants LCD Text Private Constants
  * @{
  */

/** @} */ /* End of group LCD_Text_Private_Constants */

/** @defgroup LCD_Text_Variables LCD Text Variables
  * @{
  */

/* The selected font for text output */
sFONT *CurrentFont = &Font_6x8;

/** @} */ /* End of group LCD_Text_Variables */

/** @defgroup LCD_Text_Private_Functions LCD Text Private Functions
  * @{
  */

/*******************************************************************************
* Function Name  : LCD_PUT_BYTE
* Description    : Outputs one byte to the given screen coordinates.
* Input          : õ    - x-coordinate
*                : y    - y-coordinate
*                : data - byte to output
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_PUT_BYTE(uint8_t x, uint8_t y, uint8_t data)
{
  uint32_t tmp_data, page, shift_num, shift_num_ex;

  if ((x>MAX_X)|(y>MAX_Y))
  {
    return;
  }

  /* Select crystal and x offset */
  SetCrystal((LCD_Crystal)(x/64));
  x %= 64;
  /* Determine first page and y offset */
  page = y/8;
  shift_num = y%8;
  shift_num_ex = 8 - shift_num;

  /* First page */

  /* Read current value */
  LCD_SET_PAGE(page);
  LCD_SET_ADDRESS(x);
  tmp_data = ReadLCD_Data();
  /* Write modified value */
  LCD_SET_PAGE(page);
  LCD_SET_ADDRESS(x);
  switch (CurrentMethod)
  {
    case MET_OR:
      WriteLCD_Data(tmp_data | (data << shift_num));
      break;
    case MET_XOR:
      WriteLCD_Data(tmp_data ^ (data << shift_num));
      break;
    case MET_NOT_OR:
      WriteLCD_Data(tmp_data | ((data ^ 0xFF) << shift_num));
      break;
    case MET_NOT_XOR:
      WriteLCD_Data(tmp_data ^ ((data ^ 0xFF) << shift_num));
      break;
    case MET_AND:
      WriteLCD_Data(tmp_data & (0xFF >> shift_num_ex) | (data << shift_num));
      break;
  }

  /* Second page (if any) */
  if (shift_num > 0)
  {
    /* Read current value */
    LCD_SET_PAGE(page+1);
    LCD_SET_ADDRESS(x);
    tmp_data = ReadLCD_Data();
    /* Write modified value */
    LCD_SET_PAGE(page+1);
    LCD_SET_ADDRESS(x);
    switch (CurrentMethod)
    {
      case MET_OR:
        WriteLCD_Data(tmp_data | (data >> shift_num_ex));
        break;
      case MET_XOR:
        WriteLCD_Data(tmp_data ^ (data >> shift_num_ex));
        break;
      case MET_NOT_OR:
        WriteLCD_Data(tmp_data | ((data ^ 0xFF) >> shift_num_ex));
        break;
      case MET_NOT_XOR:
        WriteLCD_Data(tmp_data ^ ((data ^ 0xFF)>> shift_num_ex));
        break;
      case MET_AND:
        WriteLCD_Data(tmp_data & (0xFF << shift_num) | (data >> shift_num_ex));
        break;
    }
  }
}

/*----------------- Printing of symbols and strings using current font -----------------*/

/*******************************************************************************
* Function Name  : LCD_PUTC
* Description    : Prints one symbol to the given screen coordinates.
* Input          : õ  - x-coordinate
*                : y  - y-coordinate
*                : ch - symbol to print
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_PUTC(uint8_t x, uint8_t y, uint8_t ch)
{
  uint32_t i, j, line;
  ucint8_t *sym;

  sym = Get_Char_Data_Addr(ch);
  line = CurrentFont->Height / 8;
  if (CurrentFont->Height % 8)
  {
    line++;
  }

  for (j = 0; j < line; j++)
  {
    for( i = 0; i < CurrentFont->Width; i++)
    {
      LCD_PUT_BYTE(x + i, y + j*8, sym[i + CurrentFont->Width*j]);
    }
  }
}

/*******************************************************************************
* Function Name  : LCD_PUTS
* Description    : Prints the string to the given screen coordinates.
* Input          : õ  - x-coordinate
*                : y  - y-coordinate
*                : str - pointer to string
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_PUTS(uint8_t x, uint8_t y, ucint8_t* str)
{
  uint32_t i;

  for (i=0; str[i]; i++)
  {
    LCD_PUTC(x + i*CurrentFont->Width, y, str[i]);
  }
}

/*******************************************************************************
* Function Name  : LCD_PUTS_Ex
* Description    : Prints the string using the dedicated style.
* Input          : õ  - x-coordinate
*                : y  - y-coordinate
*                : str - pointer to string
*                : style - style
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_PUTS_Ex(uint8_t x, uint8_t y, ucint8_t* str, uint8_t style)
{
  uint32_t i, DelayCount;

  LCD_Method OldMethod = CurrentMethod;

  /* Trimming results in animation speed changes */
  DelayCount = (ADC1_GetResult() & ADC_RESULT_Msk) + 51;

  switch (style)
  {
    /* Simple string */
    case StyleSimple:
      CurrentMethod = MET_AND;
      LCD_PUTS(x, y, str);
      break;
    /* Blinking strings */
    case StyleBlink:
      CurrentMethod = MET_AND;
      LCD_PUTS(x, y, str);
      SysTickDelay(DelayCount);
      for (i = 0; i < strlen((const char *)str); i++)
        LCD_PUTC(x + ((CurrentFont->Width) * i), y, 0x20);
      break;
    /* String with modified background */
    case StyleFlipFlop:
      CurrentMethod = MET_AND;
      LCD_PUTS(x, y, str);
      CurrentMethod = MET_XOR;
      LCD_PUTS(x, y, str);
      CurrentMethod = MET_NOT_XOR;
      LCD_PUTS(x, y, str);
      SysTickDelay(DelayCount * 2);
      CurrentMethod = MET_AND;
      LCD_PUTS(x, y, str);
      SysTickDelay(DelayCount);
      break;
    /* Shiver string */
    case StyleVibratory:
      CurrentMethod = MET_AND;
      LCD_PUTS(x, y, str);
      SysTickDelay(DelayCount);
      LCD_PUTS(x+1, y+1, str);
      break;
  }
  CurrentMethod = OldMethod;
}

/** @} */ /* End of group LCD_Text_Private_Functions */

/** @} */ /* End of group LCD_Text */

/** @} */ /* End of group __MDR1986VE1T_Eval_Demo */

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE text.c */

