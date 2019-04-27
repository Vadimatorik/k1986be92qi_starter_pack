/**
  ******************************************************************************
  * @file    lcd_MDR32F9Qx.h
  * @author  Phyton Application Team
  * @version V3.0.0
  * @date    10.09.2011
  * @brief   This file contains all the specific types, constants and variables
  *          for the LCD driver for MDR32F9Q2_Rev0, MDR32F9Q2_Rev1,
  *          MDR32F9Q3_Rev0 and MDR32F9Q3_Rev1 evaluation boards.
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

#if defined (USE_MDR32F9Q2_Rev0)  || defined (USE_MDR32F9Q2_Rev1) || \
    defined (USE_MDR32F9Q3_Rev0) || defined (USE_MDR32F9Q3_Rev1)

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_H
#define __LCD_H

/* Includes ------------------------------------------------------------------*/
#include <MDR32Fx.h>
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include "types.h"
#include "MDR32F9Qx_board.h"

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
  * @{
  */

/** @addtogroup LCD_Driver LCD Driver
  * @{
  */

/** @defgroup __MDR32F9Qx_LCD MDR32F9Q2Y and MDR32F9Q3Y evaluation boards specific
  * @{
  */

/** @defgroup __MDR32F9Qx_LCD_Exported_Constants MDR32F9Qx LCD Exported Constants
  * @{
  */

/* LCD control port pins definitions */

/* LCD crystals control */
#if defined (USE_MDR32F9Q2_Rev0) || defined (USE_MDR32F9Q2_Rev1)
#define LCD_CRYSTAL_PINs                 (PORT_Pin_7 | PORT_Pin_8)
#define LCD_CRYSTAL_POS                  7
#define LCD_CRYSTAL_PORT                 MDR_PORTB
#elif defined (USE_MDR32F9Q3_Rev0) || defined (USE_MDR32F9Q3_Rev1)
#define LCD_CRYSTAL_PINs                 (PORT_Pin_0 | PORT_Pin_1)
#define LCD_CRYSTAL_POS                  0
#define LCD_CRYSTAL_PORT                 MDR_PORTF
#endif

/* LCD command/data switching */
#if defined (USE_MDR32F9Q2_Rev0) || defined (USE_MDR32F9Q2_Rev1)
#define LCD_CMD_DATA_PIN                 (PORT_Pin_0)
#define LCD_CMD_DATA_PORT                MDR_PORTC
#elif defined (USE_MDR32F9Q3_Rev0) || defined (USE_MDR32F9Q3_Rev1)
#define LCD_CMD_DATA_PIN                 (PORT_Pin_4)
#define LCD_CMD_DATA_PORT                MDR_PORTF
#endif

/* LCD read/write switching */
#if defined (USE_MDR32F9Q2_Rev0) || defined (USE_MDR32F9Q2_Rev1)
#define LCD_RD_WR_PIN                    (PORT_Pin_10)
#define LCD_RD_WR_PORT                   MDR_PORTB
#elif defined (USE_MDR32F9Q3_Rev0) || defined (USE_MDR32F9Q3_Rev1)
#define LCD_RD_WR_PIN                    (PORT_Pin_3)
#define LCD_RD_WR_PORT                   MDR_PORTF
#endif

/* LCD CLOCK signal control */
#if defined (USE_MDR32F9Q2_Rev0) || defined (USE_MDR32F9Q2_Rev1)
#define LCD_CLOCK_PIN                    (PORT_Pin_1)
#define LCD_CLOCK_PORT                   MDR_PORTC
#elif defined (USE_MDR32F9Q3_Rev0) || defined (USE_MDR32F9Q3_Rev1)
#define LCD_CLOCK_PIN                    (PORT_Pin_3)
#define LCD_CLOCK_PORT                   MDR_PORTD
#endif

/* LCD RESET signal control */
#if defined (USE_MDR32F9Q2_Rev0) || defined (USE_MDR32F9Q2_Rev1)
#define LCD_RESET_PIN                    (PORT_Pin_9)
#define LCD_RESET_PORT                   MDR_PORTB
#elif defined (USE_MDR32F9Q3_Rev0) || defined (USE_MDR32F9Q3_Rev1)
#define LCD_RESET_PIN                    (PORT_Pin_2)
#define LCD_RESET_PORT                   MDR_PORTF
#endif

/** @} */ /* End of group __MDR32F9Qx_LCD_Exported_Constants */

/** @} */ /* End of group __MDR32F9Qx_LCD */

/** @} */ /* End of group LCD_Driver */

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

#endif /* __LCD_H */

#endif /* USE_MDR32F9Q2_Rev0  || USE_MDR32F9Q2_Rev1 ||
        * USE_MDR32F9Q3_Rev0  || USE_MDR32F9Q3_Rev1 */

/******************* (C) COPYRIGHT 2011 Phyton *********************************
*
* END OF FILE lcd_MDR32F9Qx.h */

