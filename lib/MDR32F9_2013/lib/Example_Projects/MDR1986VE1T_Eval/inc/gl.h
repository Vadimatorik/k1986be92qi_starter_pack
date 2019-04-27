/**
  ******************************************************************************
  * @file    gl.h
  * @author  Milandr Application Team
  * @version V3.0.0
  * @date    09.09.2013
  * @brief   This file contains all the functions prototypes for the
  *          graphic primitive output to LCD.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GL_H
#define __GL_H

/* Includes ------------------------------------------------------------------*/
#include "types.h"

/** @addtogroup __MDR1986VE1T_Eval_Demo MDR1986VE1T Demonstration Example
  * @{
  */

/** @defgroup LCD_Graphics LCD Graphics
  * @{
  */

/** @defgroup LCD_Graphics_Exported_Functions LCD Graphics Exported Functions
  * @{
  */

void LCD_PutPixel(uint32_t x, uint32_t y);
void LCD_Line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
void LCD_Circle(uint32_t xc, uint32_t yc, uint32_t r);

/** @} */ /* End of group LCD_Graphics_Exported_Functions */

/** @} */ /* End of group LCD_Graphics */

/** @} */ /* End of group __MDR1986VE1T_Eval_Demo */

#endif /* __GL_H */

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE gl.h */

