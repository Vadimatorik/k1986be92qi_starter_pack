/**
  ******************************************************************************
  * @file    lcd_MDR1986VE3.h
  * @author  Milandr Application Team
  * @version V3.0.0
  * @date    10.09.2013
  * @brief   This file contains all the specific types, constants and variables
  *          for the LCD driver for MDR1986VE3_Rev0 and MDR1986VE3_Rev1 evaluation
  *          boards.
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
#ifndef __LCD_MDR1986VE3_H
#define __LCD_MDR1986VE3_H

/* Includes ------------------------------------------------------------------*/
#include <MDR32F9Qx_config.h>
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include "types.h"
#include "lcd.h"

/** @addtogroup __MDR1986VE3_Eval_Demo MDR1986VE3 Demonstration Example
  * @{
  */

/** @addtogroup LCD_Driver LCD Driver
  * @{
  */

/** @defgroup __MDR1986VE3_LCD MDR1986VE3 evaluation boards specific
  * @{
  */

/** @defgroup __MDR1986VE3_LCD_Exported_Types MDR1986VE3 LCD Exported Types
  * @{
  */

/* LCD crystal ports */
typedef struct
{
    uint32_t Data;
    uint32_t Cmd;
}LCD_Ports;

/** @} */ /* End of group __MDR1986VE3_LCD_Exported_Types */

/** @defgroup __MDR1986VE3_LCD_Exported_Variables MDR1986VE3 LCD Exported Variables
  * @{
  */

extern const LCD_Ports CrystalPorts[NUM_LCD_CRYSTALS];

/** @} */ /* End of group __MDR1986VE3_LCD_Exported_Variables */

/** @defgroup __MDR1986VE3_LCD_Exported_Macros MDR1986VE3 LCD Exported Macros
  * @{
  */

#define LCD_DATA(x)                 (*((vuint32_t*)CrystalPorts[x].Data))
#define LCD_CMD(x)                  (*((vuint32_t*)CrystalPorts[x].Cmd))

/** @} */ /* End of group __MDR1986VE3_LCD_Exported_Macros */

/** @} */ /* End of group __MDR1986VE3_LCD */

/** @} */ /* End of group LCD_Driver */

/** @} */ /* End of group __MDR1986VE3_Eval_Demo */

#endif /* __LCD_MDR1986VE3_H */

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE lcd_MDR1986VE3.h */

