/**
  ******************************************************************************
  * @file    Demo_Init_MDR32F9Qx.c
  * @author  Phyton Application Team
  * @version V3.0.0
  * @date    09.09.2011
  * @brief   Initializes the demonstration application for MDR32F9Q2_Rev0,
  *          MDR32F9Q2_Rev1, MDR32F9Q3_Rev0 and MDR32F9Q3_Rev1 evaluation boards.
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

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_config.h"
#include <MDR32Fx.h>
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_uart.h>
#include "MDR32F9Qx_board.h"
#include "lcd.h"
#include "joystick.h"
#include "leds.h"
#include "demo_init.h"

#if defined (USE_MDR32F9Q2_Rev0) || defined (USE_MDR32F9Q2_Rev1) || \
    defined (USE_MDR32F9Q3_Rev0) || defined (USE_MDR32F9Q3_Rev1)

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
  * @{
  */

/** @addtogroup Demo_Setup Demo Setup
  * @{
  */

/** @defgroup __MDR32F9Qx_Demo_Setup MDR32F9Qx evaluation boards specific
  * @{
  */

/** @defgroup __MDR32F9Qx_Demo_Setup_Private_Constants MDR32F9Qx Demo Setup Private Constants
  * @{
  */

#define ALL_PORTS_CLK   (RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB | \
                         RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD | \
                         RST_CLK_PCLK_PORTE | RST_CLK_PCLK_PORTF)

/** @} */ /* End of group __MDR32F9Qx_Demo_Setup_Private_Constants */

/** @defgroup __MDR32F9Qx_Demo_Setup_Private_Variables MDR32F9Qx Demo Setup Private Variables
  * @{
  */

/** @} */ /* End of group __MDR32F9Qx_Demo_Setup_Private_Variables */

/** @defgroup __MDR32F9Qx_Demo_Setup_Private_Functions MDR32F9Qx Demo Setup Private Functions
  * @{
  */

/*******************************************************************************
* Function Name  : ClockConfigure
* Description    : Configures the CPU_PLL and RTCHSE clock.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ClockConfigure(void)
{
  /* Configure CPU_PLL clock */
  RST_CLK_CPU_PLLconfig (RST_CLK_CPU_PLLsrcHSIdiv1,0);

  /* Enables the RTCHSE clock on all ports */
  RST_CLK_PCLKcmd(ALL_PORTS_CLK, ENABLE);
}

/*******************************************************************************
* Function Name  : Demo_Init
* Description    : Initializes the demonstration application
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Demo_Init(void)
{
  ClockConfigure();

/************************ LCD Initialization *************************/

  /* Configure LCD_DATA_PORT for data transfer to/from LCD */
  PortInitStructure.PORT_Pin = LCD_DATA_BUS_8;
  PortInitStructure.PORT_FUNC = PORT_FUNC_PORT;
  PortInitStructure.PORT_OE = PORT_OE_IN;
  PortInitStructure.PORT_SPEED = PORT_SPEED_SLOW;
  PortInitStructure.PORT_MODE = PORT_MODE_DIGITAL;

  PORT_Init(LCD_DATA_PORT, &PortInitStructure);

  /* Configure LCD_RD_WR_PORT for read/write control */
  /* Switch LCD into data output mode */
  PORT_SetBits(LCD_RD_WR_PORT, LCD_RD_WR_PIN);

  PortInitStructure.PORT_Pin = LCD_RD_WR_PIN;
  PortInitStructure.PORT_OE = PORT_OE_OUT;

  PORT_Init(LCD_RD_WR_PORT, &PortInitStructure);

  /* Configure LCD_CLOCK_PORT for CLOCK signal control*/
  /* Set LCD CLOCK signal to its initial value (0) */
  PORT_ResetBits(LCD_CLOCK_PORT, LCD_CLOCK_PIN);

  PortInitStructure.PORT_Pin = LCD_CLOCK_PIN;
  PortInitStructure.PORT_SPEED = PORT_SPEED_FAST;

  PORT_Init(LCD_CLOCK_PORT, &PortInitStructure);

  /* Configure LCD_CRYSTAL_PORT for LCD crystal control */
  /* De-select both LCD crystals*/
  PORT_ResetBits(LCD_CRYSTAL_PORT, LCD_CRYSTAL_PINs);

  PortInitStructure.PORT_Pin = LCD_CRYSTAL_PINs;
  PortInitStructure.PORT_SPEED = PORT_SPEED_SLOW;

  PORT_Init(LCD_CRYSTAL_PORT, &PortInitStructure);

  /* Configure LCD_CMD_DATA_PORT for data/command mode switching */
  PortInitStructure.PORT_Pin = LCD_CMD_DATA_PIN;

  PORT_Init(LCD_CMD_DATA_PORT, &PortInitStructure);

  /* Configure LCD_RESET_PORT for RESET signal control */
  /* Zeroing LCD RES signal (initial state) */
  PORT_ResetBits(LCD_RESET_PORT, LCD_RESET_PIN);

  PortInitStructure.PORT_Pin = LCD_RESET_PIN;
  PortInitStructure.PORT_SPEED = PORT_SPEED_FAST;

  PORT_Init(LCD_RESET_PORT, &PortInitStructure);

  LCD_INIT();

/************************ Joystick Initialization *************************/

  /* Configure SEL_PORT for input to handle joystick event SEL */
  PortInitStructure.PORT_Pin   = SEL_PIN;
  PortInitStructure.PORT_OE    = PORT_OE_IN;
  PortInitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PortInitStructure.PORT_SPEED = PORT_SPEED_SLOW;

  PORT_Init(SEL_PORT, &PortInitStructure);

  /* Configure UP_PORT for input to handle joystick event UP */
  PortInitStructure.PORT_Pin   = UP_PIN;

  PORT_Init(UP_PORT, &PortInitStructure);

  /* Configure DOWN_PORT for input to handle joystick event DOWN */
  PortInitStructure.PORT_Pin   = DOWN_PIN;

  PORT_Init(DOWN_PORT, &PortInitStructure);

  /* Configure LEFT_PORT for input to handle joystick event LEFT */
  PortInitStructure.PORT_Pin   = LEFT_PIN;

  PORT_Init(LEFT_PORT, &PortInitStructure);

  /* Configure RIGHT_PORT for input to handle joystick event RIGHT */
  PortInitStructure.PORT_Pin   = RIGHT_PIN;

  PORT_Init(RIGHT_PORT, &PortInitStructure);

/************************ LEDs Initialization *************************/

  /* Configure LEDs_PORT for output to switch LEDs on/off */
  PortInitStructure.PORT_Pin   = LEDs_PINs;
  PortInitStructure.PORT_OE    = PORT_OE_OUT;
  PortInitStructure.PORT_FUNC  = PORT_FUNC_PORT;

  PORT_Init(LEDs_PORT, &PortInitStructure);

  /* All LEDs switch off */
  PORT_ResetBits(LEDs_PORT, LEDs_PINs);
}

/** @} */ /* End of group __MDR32F9Qx_Demo_Setup_Private_Functions */

/** @} */ /* End of group __MDR32F9Qx_Demo_Setup */

/** @} */ /* End of group Demo_Setup */

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

#endif /* USE_MDR32F9Q2_Rev0 || USE_MDR32F9Q2_Rev1 ||
        * USE_MDR32F9Q3_Rev0 || USE_MDR32F9Q3_Rev1 */

/******************* (C) COPYRIGHT 2011 Phyton *******************
*
* END OF FILE Demo_Init_MDR32F9Qx.c */

