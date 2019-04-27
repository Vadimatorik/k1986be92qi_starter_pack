/**
  ******************************************************************************
  * @file    lcd_MDR32F9Q1.h
  * @author  Phyton Application Team
  * @version V3.0.0
  * @date    10.09.2011
  * @brief   This file contains all the specific types, constants and variables
  *          for the LCD driver for MDR32F9Q1_Rev0 and MDR32F9Q1_Rev1 evaluation
  *          boards.
  ******************************************************************************
  * <br><br>
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, PHYTON SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 Phyton</center></h2>
  */

#if defined (USE_MDR32F9Q1_Rev0) || defined (USE_MDR32F9Q1_Rev1)

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_MDR32F9Q1_H
#define __LCD_MDR32F9Q1_H

/* Includes ------------------------------------------------------------------*/
#include <MDR32Fx.h>
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include "types.h"
#include "lcd.h"

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
  * @{
  */

/** @addtogroup LCD_Driver LCD Driver
  * @{
  */

/** @defgroup __MDR32F9Q1_LCD MDR32F9Q1 evaluation boards specific
  * @{
  */

/** @defgroup __MDR32F9Q1_LCD_Exported_Types MDR32F9Q1 LCD Exported Types
  * @{
  */

/* LCD crystal ports */
typedef struct
{
    uint32_t Data;
    uint32_t Cmd;
}LCD_Ports;

/** @} */ /* End of group __MDR32F9Q1_LCD_Exported_Types */

/** @defgroup __MDR32F9Q1_LCD_Exported_Variables MDR32F9Q1 LCD Exported Variables
  * @{
  */

extern const LCD_Ports CrystalPorts[NUM_LCD_CRYSTALS];

/** @} */ /* End of group __MDR32F9Q1_LCD_Exported_Variables */

/** @defgroup __MDR32F9Q1_LCD_Exported_Macros MDR32F9Q1 LCD Exported Macros
  * @{
  */

#define LCD_DATA(x)                 (*((vuint32_t*)CrystalPorts[x].Data))
#define LCD_CMD(x)                  (*((vuint32_t*)CrystalPorts[x].Cmd))

/** @} */ /* End of group __MDR32F9Q1_LCD_Exported_Macros */

/** @} */ /* End of group __MDR32F9Q1_LCD */

/** @} */ /* End of group LCD_Driver */

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

#endif /* __LCD_MDR32F9Q1_H */

#endif /* USE_MDR32F9Q1_Rev0 || USE_MDR32F9Q1_Rev1 */

/******************* (C) COPYRIGHT 2011 Phyton *********************************
*
* END OF FILE lcd_MDR32F9Q1.h */

