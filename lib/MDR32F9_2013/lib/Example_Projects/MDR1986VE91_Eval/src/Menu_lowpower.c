/**
  ******************************************************************************
  * @file    Menu_lowpower.c
  * @author  Phyton Application Team
  * @version V1.2.0
  * @date    05.12.2011
  * @brief   This file contains all the "Low Power" menu handlers.
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
#include <MDR32F9Qx_power.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_bkp.h>
#include "systick.h"
#include "Menu.h"
#include "Menu_items.h"
#include "leds.h"
#include "lcd.h"
#include "text.h"
#include "joystick.h"
#include "time.h"
#include "demo_init.h"
#include "MDR32F9Qx_it.h"

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
  * @{
  */

/** @addtogroup Menu Menu
  * @{
  */

/** @addtogroup Menu_LowPower Menu Low Power
  * @{
  */

/** @defgroup Menu_LowPower_Private_Constants Menu Low Power Private Constants
  * @{
  */

/** @} */ /* End of group Menu_LowPower_Private_Constants */

/** @defgroup Menu_LowPower_Private_Types Menu Low Power Private Types
  * @{
  */

typedef struct
{
  uint32_t OE;
  uint32_t FUNC;
  uint32_t ANALOG;
  uint32_t PULL;
  uint32_t PD;
  uint32_t PWR;
  uint32_t GFEN;
}PORTConfigData;

typedef struct
{
  uint32_t PVDCS;
  uint32_t CPU_CLOCK;
  uint32_t PER_CLOCK;
#if defined (USE_MDR32F9Q1_Rev0) || defined (USE_MDR32F9Q1_Rev1)
  uint32_t EBC_CONTROL;
#endif
}ClockConfigData;

/** @} */ /* End of group Menu_LowPower_Private_Types */

/** @defgroup Menu_LowPower_Private_Macros Menu Low Power Private Macros
  * @{
  */

/** @} */ /* End of group Menu_LowPower_Private_Macros */

/** @defgroup Menu_LowPower_Private_Variables Menu Low Power Private Variables
  * @{
  */
static PORTConfigData PORTA_Data, PORTB_Data, PORTC_Data, PORTD_Data, PORTE_Data,
                      PORTF_Data;

static ClockConfigData ClockData;

/** @} */ /* End of group Menu_LowPower_Private_Variables */

/** @defgroup Menu_LowPower_Private_Functions Menu Low Power Private Functions
  * @{
  */

/*******************************************************************************
* Function Name  : LowPower_Init
* Description    : Initializes Low Power application.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LowPower_Init(void)
{
  RST_CLK_PCLKcmd(RST_CLK_PCLK_POWER, ENABLE);
}

/*******************************************************************************
* Function Name  : PORT_SaveConfig
* Description    : Save all PORTs Configurations.
* Input          : None
* Output         : PORTA_Data, PORTB_Data, PORTC_Data, PORTD_Data, PORTE_Data,
*                : PORTF_Data.
* Return         : None
*******************************************************************************/
static void PORT_SaveConfig(void)
{
  PORTA_Data.ANALOG = MDR_PORTA->ANALOG;
  PORTA_Data.FUNC   = MDR_PORTA->FUNC;
  PORTA_Data.GFEN   = MDR_PORTA->GFEN;
  PORTA_Data.OE     = MDR_PORTA->OE;
  PORTA_Data.PD     = MDR_PORTA->PD;
  PORTA_Data.PULL   = MDR_PORTA->PULL;
  PORTA_Data.PWR    = MDR_PORTA->PWR;

  PORTB_Data.ANALOG = MDR_PORTB->ANALOG;
  PORTB_Data.FUNC   = MDR_PORTB->FUNC;
  PORTB_Data.GFEN   = MDR_PORTB->GFEN;
  PORTB_Data.OE     = MDR_PORTB->OE;
  PORTB_Data.PD     = MDR_PORTB->PD;
  PORTB_Data.PULL   = MDR_PORTB->PULL;
  PORTB_Data.PWR    = MDR_PORTB->PWR;

  PORTC_Data.ANALOG = MDR_PORTC->ANALOG;
  PORTC_Data.FUNC   = MDR_PORTC->FUNC;
  PORTC_Data.GFEN   = MDR_PORTC->GFEN;
  PORTC_Data.OE     = MDR_PORTC->OE;
  PORTC_Data.PD     = MDR_PORTC->PD;
  PORTC_Data.PULL   = MDR_PORTC->PULL;
  PORTC_Data.PWR    = MDR_PORTC->PWR;

  PORTD_Data.ANALOG = MDR_PORTD->ANALOG;
  PORTD_Data.FUNC   = MDR_PORTD->FUNC;
  PORTD_Data.GFEN   = MDR_PORTD->GFEN;
  PORTD_Data.OE     = MDR_PORTD->OE;
  PORTD_Data.PD     = MDR_PORTD->PD;
  PORTD_Data.PULL   = MDR_PORTD->PULL;
  PORTD_Data.PWR    = MDR_PORTD->PWR;

  PORTE_Data.ANALOG = MDR_PORTE->ANALOG;
  PORTE_Data.FUNC   = MDR_PORTE->FUNC;
  PORTE_Data.GFEN   = MDR_PORTE->GFEN;
  PORTE_Data.OE     = MDR_PORTE->OE;
  PORTE_Data.PD     = MDR_PORTE->PD;
  PORTE_Data.PULL   = MDR_PORTE->PULL;
  PORTE_Data.PWR    = MDR_PORTE->PWR;

  PORTF_Data.ANALOG = MDR_PORTF->ANALOG;
  PORTF_Data.FUNC   = MDR_PORTF->FUNC;
  PORTF_Data.GFEN   = MDR_PORTF->GFEN;
  PORTF_Data.OE     = MDR_PORTF->OE;
  PORTF_Data.PD     = MDR_PORTF->PD;
  PORTF_Data.PULL   = MDR_PORTF->PULL;
  PORTF_Data.PWR    = MDR_PORTF->PWR;

  /* Configure all PORTs for low power consumption */
  PORT_DeInit(MDR_PORTA);
  PORT_DeInit(MDR_PORTB);
  PORT_DeInit(MDR_PORTC);
  PORT_DeInit(MDR_PORTD);
  PORT_DeInit(MDR_PORTE);
  PORT_DeInit(MDR_PORTF);
}

/*******************************************************************************
* Function Name  : PORT_RestoreConfig
* Description    : Restores all PORTs Configurations.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void PORT_RestoreConfig(void)
{
  MDR_PORTA->ANALOG = PORTA_Data.ANALOG;
  MDR_PORTA->FUNC   = PORTA_Data.FUNC;
  MDR_PORTA->GFEN   = PORTA_Data.GFEN;
  MDR_PORTA->OE     = PORTA_Data.OE;
  MDR_PORTA->PD     = PORTA_Data.PD;
  MDR_PORTA->PULL   = PORTA_Data.PULL;
  MDR_PORTA->PWR    = PORTA_Data.PWR;

  MDR_PORTB->ANALOG = PORTB_Data.ANALOG;
  MDR_PORTB->FUNC   = PORTB_Data.FUNC;
  MDR_PORTB->GFEN   = PORTB_Data.GFEN;
  MDR_PORTB->OE     = PORTB_Data.OE;
  MDR_PORTB->PD     = PORTB_Data.PD;
  MDR_PORTB->PULL   = PORTB_Data.PULL;
  MDR_PORTB->PWR    = PORTB_Data.PWR;

  MDR_PORTC->ANALOG = PORTC_Data.ANALOG;
  MDR_PORTC->FUNC   = PORTC_Data.FUNC;
  MDR_PORTC->GFEN   = PORTC_Data.GFEN;
  MDR_PORTC->OE     = PORTC_Data.OE;
  MDR_PORTC->PD     = PORTC_Data.PD;
  MDR_PORTC->PULL   = PORTC_Data.PULL;
  MDR_PORTC->PWR    = PORTC_Data.PWR;

  MDR_PORTD->ANALOG = PORTD_Data.ANALOG;
  MDR_PORTD->FUNC   = PORTD_Data.FUNC;
  MDR_PORTD->GFEN   = PORTD_Data.GFEN;
  MDR_PORTD->OE     = PORTD_Data.OE;
  MDR_PORTD->PD     = PORTD_Data.PD;
  MDR_PORTD->PULL   = PORTD_Data.PULL;
  MDR_PORTD->PWR    = PORTD_Data.PWR;

  MDR_PORTE->ANALOG = PORTE_Data.ANALOG;
  MDR_PORTE->FUNC   = PORTE_Data.FUNC;
  MDR_PORTE->GFEN   = PORTE_Data.GFEN;
  MDR_PORTE->OE     = PORTE_Data.OE;
  MDR_PORTE->PD     = PORTE_Data.PD;
  MDR_PORTE->PULL   = PORTE_Data.PULL;
  MDR_PORTE->PWR    = PORTE_Data.PWR;

  MDR_PORTF->ANALOG = PORTF_Data.ANALOG;
  MDR_PORTF->FUNC   = PORTF_Data.FUNC;
  MDR_PORTF->GFEN   = PORTF_Data.GFEN;
  MDR_PORTF->OE     = PORTF_Data.OE;
  MDR_PORTF->PD     = PORTF_Data.PD;
  MDR_PORTF->PULL   = PORTF_Data.PULL;
  MDR_PORTF->PWR    = PORTF_Data.PWR;
}

/*******************************************************************************
* Function Name  : Clock_SaveConfig
* Description    : Save the Power and Clock configuration.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Clock_SaveConfig(void)
{
  ClockData.PVDCS           = MDR_POWER->PVDCS;
  ClockData.CPU_CLOCK       = MDR_RST_CLK->CPU_CLOCK;
  ClockData.PER_CLOCK       = MDR_RST_CLK->PER_CLOCK;
#if defined (USE_MDR32F9Q1_Rev0) || defined (USE_MDR32F9Q1_Rev1)
  ClockData.EBC_CONTROL = MDR_EBC->CONTROL;
#endif
}

/*******************************************************************************
* Function Name  : Clock_RestoreConfig
* Description    : Restore the Power and Clock configuration.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Clock_RestoreConfig(void)
{
  MDR_POWER->PVDCS       = ClockData.PVDCS;
  MDR_RST_CLK->CPU_CLOCK = ClockData.CPU_CLOCK;
  MDR_RST_CLK->PER_CLOCK = ClockData.PER_CLOCK;
#if defined (USE_MDR32F9Q1_Rev0) || defined (USE_MDR32F9Q1_Rev1)
  MDR_EBC->CONTROL   = ClockData.EBC_CONTROL;
#endif
}

/*******************************************************************************
* Function Name  : STANDBYMode_WAKEUP
* Description    : Enters MCU in STANDBY mode.
*                : Attention: the wake-up from STANDBY mode is performed on
*                : WAKEUP pin low level. After STANDBY mode exiting, power on
*                : reset is occurred.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void STANDBYMode_WAKEUP(void)
{
  /* Print the header */
  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;
  DisplayMenuTitle("STANDBY. Exit: WAKEUP");
  WAIT_UNTIL_KEY_RELEASED(SEL);

  LCD_PUTS(0, LineMessage1, "                    ");
  LCD_PUTS(0, LineMessage2, "                    ");
  LCD_PUTS(0, LineMessage3, "MCU in STANDBY Mode ");
  LCD_PUTS(0, LineMessage4, "To exit press Wakeup");
  LCD_PUTS(0, LineMessage5, "                     ");

  /* Request to enter STANDBY mode */
  POWER_EnterSTANDBYMode();
}

/*******************************************************************************
* Function Name  : STANDBYMode_RTCAlarm
* Description    : Enters MCU in STANDBY mode.
*                : Attention: the wake-up from STANDBY mode is performed on
*                : RTC Alarm event. After STANDBY mode exiting, power on
*                : reset is occurred.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void STANDBYMode_RTCAlarm(void)
{
  /* Print the header */
  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;
  DisplayMenuTitle("STANDBY. Exit: Alarm");
  WAIT_UNTIL_KEY_RELEASED(SEL);

  if((MDR_BKP->REG_00 != 0x1234) || (MDR_BKP->RTC_PRL != RTC_PRESCALER_VALUE))
  {
    LCD_PUTS(0, LineMessage1, "RTC is not configured");
    LCD_PUTS(0, LineMessage2, "Please, use the ");
    LCD_PUTS(0, LineMessage3, "Time Adjust menu and ");
    LCD_PUTS(0, LineMessage4, "Alarm Adjust menu to ");
    LCD_PUTS(0, LineMessage5, "set the Alarm time. ");
    WAIT_UNTIL_KEY_PRESSED(SEL);
    WAIT_UNTIL_KEY_RELEASED(SEL);

    /* Display the menu */
    DisplayMenu();
    return;
  }

  LCD_PUTS(0, LineMessage1, "                    ");
  LCD_PUTS(0, LineMessage2, "                    ");
  LCD_PUTS(0, LineMessage3, " MCU in STANDBY Mode");
  LCD_PUTS(0, LineMessage4, " Wait For RTC Alarm ");
  LCD_PUTS(0, LineMessage5, "                     ");

  /* Request to enter STANDBY mode */
  POWER_EnterSTANDBYMode();
}

/*******************************************************************************
* Function Name  : STOPMode_RTCAlarm
* Description    : Enters MCU in STOP mode. The wake-up from STOP mode is
*                  performed by RTC Alarm.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void STOPMode_RTCAlarm(void)
{
  uint32_t tmp;

  /* Print the header */
  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;
  DisplayMenuTitle("STOP. Exit: Alarm");
  WAIT_UNTIL_KEY_RELEASED(SEL);

  if((MDR_BKP->REG_00 != 0x1234) || (MDR_BKP->RTC_PRL != RTC_PRESCALER_VALUE))
  {
    LCD_PUTS(0, LineMessage1, "RTC is not configured");
    LCD_PUTS(0, LineMessage2, "Please, use the ");
    LCD_PUTS(0, LineMessage3, "Time Adjust menu and ");
    LCD_PUTS(0, LineMessage4, "Alarm Adjust menu to ");
    LCD_PUTS(0, LineMessage5, "set the Alarm time.");
    WAIT_UNTIL_KEY_PRESSED(SEL);
    WAIT_UNTIL_KEY_RELEASED(SEL);

    /* Display the menu */
    DisplayMenu();
    return;
  }

  STOPModeStatus = 1;

  LCD_PUTS(0, LineMessage1, "                     ");
  LCD_PUTS(0, LineMessage2, "                     ");
  LCD_PUTS(0, LineMessage3, "  MCU in STOP Mode   ");
  LCD_PUTS(0, LineMessage4, " Wait For RTC Alarm  ");
  LCD_PUTS(0, LineMessage5, "                     ");

  /* Save the all PORTs current configuration, then
   * configure all PORTs for low power consumption */
  PORT_SaveConfig();

  /* Save the Power and Clock current configuration */
  Clock_SaveConfig();

  /* Enable SLEEPONEXIT mode */
  tmp = SCB->SCR;
  tmp |= SCB_SCR_SLEEPONEXIT_Msk;
  SCB->SCR = tmp;

  /* Request to enter STOP mode with regulator ON */
  POWER_EnterSTOPMode(ENABLE, POWER_STOPentry_WFI);

  /* Restore the Power and Clock */
  Clock_RestoreConfig();

  /* Restore the PORTs Configurations*/
  PORT_RestoreConfig();

  LCD_PUTS(0, LineMessage3, "Wake-Up by RTC Alarm");
  LCD_PUTS(0, LineMessage4, "Press SEL to continue");

  /* Wait for SEL to continue */
  WAIT_UNTIL_KEY_PRESSED(SEL);
  WAIT_UNTIL_KEY_RELEASED(SEL);

  /* Display the previous menu */
  DisplayMenu();
}

/** @} */ /* End of group Menu_LowPower_Private_Functions */

/** @} */ /* End of group Menu_LowPower */

/** @} */ /* End of group Menu */

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

/******************* (C) COPYRIGHT 2011 Phyton *******************
*
* END OF FILE Menu_lowpower.c */

