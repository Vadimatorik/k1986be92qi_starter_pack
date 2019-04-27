/**
  ******************************************************************************
  * @file    text.h
  * @author  Phyton Application Team
  * @version V2.0.0
  * @date    09.09.2010
  * @brief   This file contains all the functions prototypes for the symbol
  *          and text output to LCD.
  ******************************************************************************
  * <br><br>
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, PHYTON SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 Phyton</center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TEXT_H
#define __TEXT_H

/* Includes ------------------------------------------------------------------*/
#include "font_defs.h"

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
  * @{
  */

/** @defgroup LCD_Text LCD Text
  * @{
  */

/** @defgroup LCD_Text_Exported_Constants LCD Text Exported Constants
  * @{
  */

#define DefaultFontWidth                 6
#define DefaultFontHeight                8

/* LCD lines */
#define Interline                        2
#define LineMessage1                     DefaultFontHeight + 4
#define LineMessage2                     LineMessage1 + DefaultFontHeight + Interline
#define LineMessage3                     LineMessage2 + DefaultFontHeight + Interline
#define LineMessage4                     LineMessage3 + DefaultFontHeight + Interline
#define LineMessage5                     LineMessage4 + DefaultFontHeight + Interline

/** @} */ /* End of group LCD_Text_Exported_Constants */

/** @defgroup LCD_Text_Exported_Types LCD Text Exported Types
  * @{
  */

/* Styles */
typedef enum
{
  StyleSimple,
  StyleBlink,
  StyleFlipFlop,
  StyleVibratory
}TextStyle;

/** @} */ /* End of group LCD_Text_Exported_Types */

/** @defgroup LCD_Text_Exported_Macros LCD Text Exported Macros
  * @{
  */

/* Macro for calculation of an address of symbol description structure in the
 * symbol description table. Gets symbol code and font description address,
 * returns symbol description address. */
#define Get_Char_Data_Addr(ch)    \
  (CurrentFont)->pData + (ch) * (CurrentFont)->Width * ((((CurrentFont)->Height % 8) != 0) ? (1 + (CurrentFont)->Height / 8) : ((CurrentFont)->Height / 8))

/** @} */ /* End of group LCD_Text_Exported_Macros */

/** @defgroup LCD_Text_Exported_Variables LCD Text Exported Variables
  * @{
  */

/* Selected font (used for symbol output) */
extern sFONT *CurrentFont;

/** @} */ /* End of group LCD_Text_Exported_Variables */

/** @defgroup LCD_Text_Exported_Functions LCD Text Exported Functions
  * @{
  */

/* Byte to screen output */
void LCD_PUT_BYTE(uint8_t x, uint8_t y, uint8_t data);
/* Output symbols to screen using current font */
void LCD_PUTC(uint8_t x, uint8_t y, uint8_t ch);
void LCD_PUTS(uint8_t x, uint8_t y, ucint8_t* str);
void LCD_PUTS_Ex(uint8_t x, uint8_t y, ucint8_t* str, uint8_t style);

/** @} */ /* End of group LCD_Text_Exported_Functions */

/** @} */ /* End of group LCD_Text */

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

#endif /*__TEXT_H*/

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE text.h */

