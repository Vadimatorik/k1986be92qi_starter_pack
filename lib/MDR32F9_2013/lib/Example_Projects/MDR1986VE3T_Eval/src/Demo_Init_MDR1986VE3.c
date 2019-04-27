/**
  ******************************************************************************
  * @file    Demo_Init_MDR1986VE3.c
  * @author  Milandr Application Team
  * @version V3.0.0
  * @date    09.09.2013
  * @brief   Initializes the demonstration application for MDR1986VE3_Rev0 and
  *          MDR1986VE3_Rev1 evaluation boards
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
#include "MDR32F9Qx_config.h"
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_uart.h>
#include <MDR32F9Qx_ebc.h>
#include <MDR32F9Qx_eeprom.h>
#include "MDR32F9Qx_board.h"
#include "lcd.h"
#include "leds.h"
#include "demo_init.h"

/** @addtogroup __MDR1986VE3_Eval_Demo MDR1986VE3 Demonstration Example
  * @{
  */

/** @addtogroup Demo_Setup Demo Setup
  * @{
  */

/** @defgroup __MDR1986VE3_Demo_Setup MDR1986VE3 evaluation boards specific
  * @{
  */

/** @defgroup __MDR1986VE3_Demo_Setup_Private_Constants MDR1986VE3 Demo Setup Private Constants
  * @{
  */

#define ALL_PORTS_CLK   (RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB | \
                         RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD | \
                         RST_CLK_PCLK_PORTE | RST_CLK_PCLK_PORTF)

/** @} */ /* End of group __MDR1986VE3_Demo_Setup_Private_Constants */

/** @defgroup __MDR1986VE3_Demo_Setup_Private_Variables MDR1986VE3 Demo Setup Private Variables
  * @{
  */

/** @} */ /* End of group __MDR1986VE3_Demo_Setup_Private_Variables */

/** @defgroup __MDR1986VE3_Demo_Setup_Private_Functions MDR1986VE3 Demo Setup Private Functions
  * @{
  */

/*******************************************************************************
* Function Name  : ExtBus_Setup
* Description    : Configures the External Bus.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ExtBus_Setup(void)
{
  EBC_InitTypeDef EBC_InitStruct;

  /* Enables the RTCHSE clock on the EBC */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_EBC, ENABLE);

  EBC_StructInit(&EBC_InitStruct);

  /* Configure External Bus */
  EBC_InitStruct.EBC_WaitState = EBC_WAIT_STATE_12HCLK;
  EBC_InitStruct.EBC_Mode          = EBC_MODE_ROM;

  EBC_Init(&EBC_InitStruct);
}

/*******************************************************************************
* Function Name  : ClockConfigure
* Description    : Configures the CPU_PLL and RTCHSE clock.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ClockConfigure(void)
{
  /* Enable HSE (High Speed External) clock */
  RST_CLK_HSEconfig(RST_CLK_HSE_ON);
  if (RST_CLK_HSEstatus() == ERROR) {
    while (1);
  }

  /* Configures the CPU_PLL clock source */
  RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul1);

  /* Enables the CPU_PLL */
  RST_CLK_CPU_PLLcmd(ENABLE);
  if (RST_CLK_CPU_PLLstatus() == ERROR) {
    while (1);
  }

  /* Enables the RST_CLK_PCLK_EEPROM */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE);
  /* Sets the code latency value */
  EEPROM_SetLatency(EEPROM_Latency_3);

  /* Select the CPU_PLL output as input for CPU_C3_SEL */
  RST_CLK_CPU_PLLuse(ENABLE);
  /* Set CPUClk Prescaler */
  RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);

  /* Select the CPU clock source */
  RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);

    /* Enables the RTCHSE clock on all ports */
    RST_CLK_PCLKcmd(ALL_PORTS_CLK, ENABLE);

  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;
  MDR_RST_CLK->PER2_CLOCK = 0xFFFFFFFF;
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

  /* Configure PORTA pins for data transfer to/from LCD */
  PortInitStructure.PORT_Pin = LCD_DATA_BUS_8;
  PortInitStructure.PORT_FUNC = PORT_FUNC_MAIN;
  PortInitStructure.PORT_SPEED = PORT_SPEED_SLOW;
  PortInitStructure.PORT_MODE = PORT_MODE_DIGITAL;
  PortInitStructure.PORT_OE = PORT_OE_IN;

  PORT_Init(MDR_PORTA, &PortInitStructure);

  /* Configure PORTE pin13 and pin14 for LCD crystals control */
  PortInitStructure.PORT_Pin = PORT_Pin_13 | PORT_Pin_14;
  PortInitStructure.PORT_FUNC = PORT_FUNC_ALTER;

  PORT_Init(MDR_PORTE, &PortInitStructure);

  /* Configure PORTE pin12 for data/command mode switching */
  PortInitStructure.PORT_Pin = PORT_Pin_12;

  PORT_Init(MDR_PORTE, &PortInitStructure);

  /* Configure PORTC pin0 for read/write control */
  PortInitStructure.PORT_Pin = PORT_Pin_0;
  PortInitStructure.PORT_FUNC = PORT_FUNC_MAIN;

  PORT_Init(MDR_PORTC, &PortInitStructure);

  /* Configure PORTC pin2 for CLOCK signal control */
  PortInitStructure.PORT_Pin = PORT_Pin_2;
  PortInitStructure.PORT_SPEED = PORT_SPEED_FAST;
  PortInitStructure.PORT_FUNC = PORT_FUNC_ALTER;

  PORT_Init(MDR_PORTC, &PortInitStructure);

  /* Configure PORTF pin0 for RESET signal control */
  PortInitStructure.PORT_Pin = PORT_Pin_12;
  PortInitStructure.PORT_OE = PORT_OE_OUT;
  PortInitStructure.PORT_FUNC = PORT_FUNC_PORT;
  PortInitStructure.PORT_SPEED = PORT_SPEED_SLOW;

  PORT_Init(MDR_PORTD, &PortInitStructure);

  ExtBus_Setup();

  LCD_INIT();

/************************ Joystick Initialization *************************/

  /* Configure PORTG pins 10..14 for input to handle joystick events */
  PortInitStructure.PORT_Pin   = (PORT_Pin_7 | PORT_Pin_11 | PORT_Pin_12 |
                                  PORT_Pin_13 | PORT_Pin_14 | PORT_Pin_15);
  PortInitStructure.PORT_OE    = PORT_OE_IN;
  PortInitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PortInitStructure.PORT_SPEED = PORT_OUTPUT_OFF;

  PORT_Init(MDR_PORTG, &PortInitStructure);

/************************ LEDs Initialization *************************/

  /* Configure PORTD pins 10..14 for output to switch LEDs on/off */
  PortInitStructure.PORT_Pin   = LEDs_PINs;
  PortInitStructure.PORT_OE    = PORT_OE_OUT;
  PortInitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PortInitStructure.PORT_SPEED = PORT_SPEED_SLOW;

  PORT_Init(MDR_PORTB, &PortInitStructure);

  /* All LEDs switch off */
  PORT_ResetBits(MDR_PORTB, LEDs_PINs);

/************************ UART Initialization *************************/
    /* Configure PORTD pins 3..4 for output to switch LEDs on/off */
  PortInitStructure.PORT_Pin   = PORT_Pin_13 | PORT_Pin_14;
  PortInitStructure.PORT_FUNC  = PORT_FUNC_MAIN;
  PortInitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;

  PORT_Init(MDR_PORTD, &PortInitStructure);

}

/** @} */ /* End of group __MDR1986VE3_Demo_Setup_Private_Functions */

/** @} */ /* End of group __MDR1986VE3_Demo_Setup */

/** @} */ /* End of group Demo_Setup */

/** @} */ /* End of group __MDR1986VE3_Eval_Demo */

/******************* (C) COPYRIGHT 2013 Milandr *******************
*
* END OF FILE Demo_Init_MDR1986VE3.c */

