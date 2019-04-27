/**
  ******************************************************************************
  * @file    Menu_time.c
  * @author  Milandr Application Team
  * @version V1.2.0
  * @date    01.12.2013
  * @brief   This file contains all the "TIME" menu handlers.
  ******************************************************************************
  * <br><br>
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, Milandr SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 Milandr</center></h2>
  */
/* Includes ------------------------------------------------------------------*/
#include <MDR32F9Qx_config.h>
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_bkp.h>
#include <MDR32F9Qx_rst_clk.h>
#include "systick.h"
#include "Menu.h"
#include "Menu_items.h"
#include "leds.h"
#include "lcd.h"
#include "text.h"
#include "joystick.h"
#include "time.h"
#include "MDR1986VE1T_it.h"

/** @addtogroup __MDR1986VE1T_Eval_Demo MDR1986VE1T Demonstration Example
  * @{
  */

/** @addtogroup Menu Menu
  * @{
  */

/** @addtogroup Menu_TIME Menu TIME
  * @{
  */

/** @defgroup Menu_TIME_Private_Constants Menu TIME Private Constants
  * @{
  */

#define Time_Display_Column              33
#define Date_Display_Column              37

/* LCD lines */
#define LineTitle                        LineMessage3 + DefaultFontHeight + Interline
#define LineDigits                       LineTitle + DefaultFontHeight + Interline

/* LCD columns for Time digits */
#define TimeH_h                          Time_Display_Column
#define TimeH_l                          TimeH_h + DefaultFontWidth
#define TimeH_sep                        TimeH_l + DefaultFontWidth
#define TimeM_h                          TimeH_sep + DefaultFontWidth
#define TimeM_l                          TimeM_h + DefaultFontWidth
#define TimeM_sep                        TimeM_l + DefaultFontWidth
#define TimeS_h                          TimeM_sep + DefaultFontWidth
#define TimeS_l                          TimeS_h + DefaultFontWidth

/* LCD columns for Date digits */
#define DateD_h                          Date_Display_Column
#define DateD_l                          DateD_h + DefaultFontWidth
#define DateD_sep                        DateD_l + DefaultFontWidth
#define DateM_h                          DateD_sep + DefaultFontWidth
#define DateM_l                          DateM_h + DefaultFontWidth
#define DateM_sep                        DateM_l + DefaultFontWidth
#define DateY_1000                       DateM_sep + DefaultFontWidth
#define DateY_100                        DateY_1000 + DefaultFontWidth
#define DateY_10                         DateY_100 + DefaultFontWidth
#define DateY_1                          DateY_10 + DefaultFontWidth

/** @} */ /* End of group Menu_TIME_Private_Constants */

/** @defgroup Menu_TIME_Private_Types Menu TIME Private Types
  * @{
  */

/* Time Structure definition */
typedef struct
{
  uint8_t sec_l;
  uint8_t sec_h;
  uint8_t min_l;
  uint8_t min_h;
  uint8_t hour_l;
  uint8_t hour_h;
}tTime;

/* Alarm Structure definition */
typedef struct
{
  uint8_t sec_l;
  uint8_t sec_h;
  uint8_t min_l;
  uint8_t min_h;
  uint8_t hour_l;
  uint8_t hour_h;
}tAlarm;

/* Date Structure definition */
typedef struct
{
  uint8_t day;
  uint8_t month;
  uint16_t year;
}tDate;

/** @} */ /* End of group Menu_TIME_Private_Types */

/** @defgroup Menu_TIME_Private_Macros Menu TIME Private Macros
  * @{
  */

/** @} */ /* End of group Menu_TIME_Private_Macros */

/** @defgroup Menu_TIME_Private_Variables Menu TIME Private Variables
  * @{
  */

static tTime  sTime;
static tAlarm sAlarm;
static tDate  sDate;

/** @} */ /* End of group Menu_TIME_Private_Variables */

/** @defgroup Menu_TIME_Private_Functions Menu TIME Private Functions
  * @{
  */

/*******************************************************************************
* Function Name  : RTC_Configuration
* Description    : Configures the RTC.
* Input          : None.
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_Configuration(void)
{
  /* Configure LSE as RTC clock source */
  RST_CLK_LSEconfig(RST_CLK_LSE_ON);
  /* Wait till LSE is ready */
  while (RST_CLK_LSEstatus() != SUCCESS)
  {
  }

  /* Select the RTC Clock Source */
  BKP_RTCclkSource(BKP_RTC_LSEclk);
  /* Wait until last write operation on RTC registers has finished */
  BKP_RTC_WaitForUpdate();

  /* Sets the RTC prescaler */
  BKP_RTC_SetPrescaler(RTC_PRESCALER_VALUE);
  /* Wait until last write operation on RTC registers has finished */
  BKP_RTC_WaitForUpdate();

  /* Sets the RTC calibrator */
  BKP_RTC_Calibration(RTC_CalibratorValue);
  /* Wait until last write operation on RTC registers has finished */
  BKP_RTC_WaitForUpdate();

  /* Enable the RTC Clock */
  BKP_RTC_Enable(ENABLE);

  /* Enable the Second interrupt */
  BKP_RTC_ITConfig(BKP_RTC_IT_SECF, ENABLE);
  NVIC_EnableIRQ(BKP_IRQn);
}

/*******************************************************************************
* Function Name  : ShowSelDigit
* Description    : Prints on LCD the value of currently selected digit
* Input          : Col  - x-coordinate
*                : Line - y-coordinate
*                : ch   - symbol to print
* Output         : None
* Return         : Digit value
*******************************************************************************/
void ShowSelDigit(uint8_t Col, uint8_t Line, uint8_t ch)
{
  LCD_Method OldMethod = CurrentMethod;

  CurrentMethod = MET_AND;
  LCD_PUTC(Col, Line, ' ');
  CurrentMethod = MET_NOT_XOR;
  LCD_PUTC(Col, Line, ch);

  CurrentMethod = OldMethod;
}


/*******************************************************************************
* Function Name  : ReadDigit
* Description    : Reads digit entered by user with joystick navigation keys.
* Input          : ColBegin    - digit column
*                : CountBegin  - digit value
*                : ValueMax    - max limit
*                : ValueMin    - min limit
* Output         : None
* Return         : Digit value
*******************************************************************************/
uint8_t ReadDigit(uint8_t ColBegin, uint8_t CountBegin, uint8_t ValueMax, uint8_t ValueMin)
{
  uint32_t tmp = CountBegin;
  KeyCode key;

  /* Display selected digit */
  ShowSelDigit(ColBegin, LineDigits, (tmp + 0x30));

  for (key = GetKey(); key != SEL; key = GetKey())
  {
    /* If "UP" pushbutton is pressed */
    if(key == UP)
    {
      /* Increase the value of the digit */
      if(tmp >= ValueMax)
      {
        tmp = (ValueMin - 1);
      }
      /* Display new value */
      tmp++;
      ShowSelDigit(ColBegin, LineDigits, (tmp + 0x30));
    }
    /* If "DOWN" pushbutton is pressed */
    if(key == DOWN)
    {
      /* Decrease the value of the digit */
      if(tmp == ValueMin)
      {
        tmp = (ValueMax + 1);
      }
      /* Display new value */
      tmp--;
      CurrentMethod = MET_AND;
      ShowSelDigit(ColBegin, LineDigits, (tmp + 0x30));
    }
    WAIT_UNTIL_KEY_RELEASED(key);
  }
  /* "SEL" pushbutton is pressed */
  WAIT_UNTIL_KEY_RELEASED(SEL);
  CurrentMethod = MET_AND;
  LCD_PUTC(ColBegin, LineDigits, (tmp + 0x30));
  /* Return the digit value and exit */
  return tmp;
}

/*******************************************************************************
* Function Name  : Time_Display
* Description    : Displays current time.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Time_Display()
{
  uint32_t TimeVar = BKP_RTC_GetCounter();

  /* Display hours */
  sTime.hour_h = (uint8_t)(TimeVar / 3600) / 10;
  LCD_PUTC(TimeH_h, LineDigits, (sTime.hour_h + 0x30));
  sTime.hour_l = (uint8_t)(((TimeVar) / 3600) % 10);
  LCD_PUTC(TimeH_l, LineDigits, (sTime.hour_l + 0x30));

  /* Display separator */
  LCD_PUTC(TimeH_sep, LineDigits, ':');

  /* Display minutes */
  sTime.min_h = (uint8_t)(((TimeVar) % 3600) / 60) / 10;
  LCD_PUTC(TimeM_h, LineDigits, (sTime.min_h + 0x30));
  sTime.min_l = (uint8_t)(((TimeVar) % 3600) / 60) % 10;
  LCD_PUTC(TimeM_l, LineDigits, (sTime.min_l + 0x30));

  /* Display separator */
  LCD_PUTC(TimeM_sep, LineDigits, ':');

  /* Display seconds */
  sTime.sec_h = (uint8_t)(((TimeVar) % 3600) % 60) / 10;
  LCD_PUTC(TimeS_h, LineDigits, (sTime.sec_h + 0x30));
  sTime.sec_l = (uint8_t)(((TimeVar) % 3600) % 60) % 10;
  LCD_PUTC(TimeS_l, LineDigits, (sTime.sec_l + 0x30));
}

/*******************************************************************************
* Function Name  : Time_Regulate
* Description    : Returns the time entered by user with joystick navigation keys.
* Input          : None
* Output         : None
* Return         : Current time RTC counter value
*******************************************************************************/
uint32_t Time_Regulate(void)
{
  uint32_t Tmp_HH, Tmp_MM, Tmp_SS;

  /* Read hours */
  Tmp_HH = ReadDigit(TimeH_h, sTime.hour_h, 0x2, 0x0);
  if(Tmp_HH == 2)
  {
    if(sTime.hour_l > 3)
    {
      sTime.hour_l = 0;
    }
    Tmp_HH = Tmp_HH*10 + ReadDigit(TimeH_l, sTime.hour_l, 0x3, 0x0);
  }
  else
  {
    Tmp_HH = Tmp_HH*10 + ReadDigit(TimeH_l, sTime.hour_l, 0x9, 0x0);
  }
  /* Read minutes */
  Tmp_MM = ReadDigit(TimeM_h, sTime.min_h, 0x5, 0x0);
  Tmp_MM = Tmp_MM*10 + ReadDigit(TimeM_l, sTime.min_l, 0x9, 0x0);
  /* Read seconds */
  Tmp_SS = ReadDigit(TimeS_h, sTime.sec_h, 0x5, 0x0);
  Tmp_SS = Tmp_SS*10 + ReadDigit(TimeS_l, sTime.sec_l, 0x9, 0x0);

  /* Return the value that to be stored in RTC counter register */
  return((Tmp_HH*3600 + Tmp_MM*60 + Tmp_SS));
}

/*******************************************************************************
* Function Name  : RTCHelp
* Description    : Prints hint to the screen.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTCHelp(void)
{
  LCD_PUTS(0, LineMessage1, "RTC is not configured");
  LCD_PUTS(0, LineMessage2, "Please, use the ");
  LCD_PUTS(0, LineMessage3, "Time Adjust menu.    ");
  WAIT_UNTIL_KEY_PRESSED(SEL);
  WAIT_UNTIL_KEY_RELEASED(SEL);
}

/*******************************************************************************
* Function Name  : TimePreAdjustFunc
* Description    : Enables the user to adjust current time with joystick keys.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TimePreAdjustFunc(void)
{
  sFONT *OldFont = CurrentFont;
  LCD_Method OldMethod = CurrentMethod;

  /* Print the header */
  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;
  DisplayMenuTitle("Time adjust");
  WAIT_UNTIL_KEY_RELEASED(SEL);

  if((MDR_BKP->REG_00 != 0x1234) || (MDR_BKP->RTC_PRL != RTC_PRESCALER_VALUE))
  {
    LCD_PUTS(0, LineTitle, "RTC is configured...");
    /* Reset Backup Domain */
    /* RTC reset */
    BKP_RTC_Reset(ENABLE);
    BKP_RTC_Reset(DISABLE);
    /* RTC Configuration */
    RTC_Configuration();
    /* Set the RTC counter value */
    BKP_RTC_SetCounter(0);
    /* Wait until last write operation on RTC registers has finished */
    BKP_RTC_WaitForUpdate();

    LCD_PUTS(0, LineTitle, "        TIME        ");

    /* Display the current time */
    Time_Display();

    /* Change the current time */
    BKP_RTC_SetCounter(Time_Regulate());
    /* Wait until last write operation on RTC registers has finished */
    BKP_RTC_WaitForUpdate();

    MDR_BKP->REG_00 = 0x1234;
    /* Wait until last write operation on RTC registers has finished */
    BKP_RTC_WaitForUpdate();
  }
  else
  {
    LCD_PUTS(0, LineTitle, "        TIME        ");

    /* Display the current time */
    Time_Display();

    /* Change the current time */
    BKP_RTC_SetCounter(Time_Regulate());
    /* Wait until last write operation on RTC registers has finished */
    BKP_RTC_WaitForUpdate();
  }
  CurrentMethod = OldMethod;
  CurrentFont = OldFont;
}

/*******************************************************************************
* Function Name  : TimeAdjustFunc
* Description    : Adjust time menu item handler
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TimeAdjustFunc(void)
{
  TimePreAdjustFunc();
  /* Display the menu */
  DisplayMenu();
}

/*******************************************************************************
* Function Name  : TimeShowFunc
* Description    : Displays the current time (HH:MM:SS) on LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TimeShowFunc(void)
{
  sFONT *OldFont = CurrentFont;
  LCD_Method OldMethod = CurrentMethod;

  /* Print the header */
  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;
  DisplayMenuTitle("Time show");
  WAIT_UNTIL_KEY_RELEASED(SEL);

  if((MDR_BKP->REG_00 != 0x1234) || (MDR_BKP->RTC_PRL != RTC_PRESCALER_VALUE))
  {
    RTCHelp();
  }
  else
  {
    LCD_PUTS(0, LineTitle, "        TIME        ");
    while (GetKey() != BACK)
    {
      /* Display the current time */
      Time_Display();
    }
    WAIT_UNTIL_KEY_RELEASED(BACK);
  }

  CurrentMethod = OldMethod;
  CurrentFont = OldFont;

  /* Display the menu */
  DisplayMenu();

}

/*******************************************************************************
* Function Name  : IsLeapYear
* Description    : Check whether the passed year is Leap or not.
* Input          : nYear - Year value
* Output         : None
* Return         : 1: leap year
*                : 0: not leap year
*******************************************************************************/
static uint32_t IsLeapYear(uint32_t nYear)
{
  if(nYear % 4 != 0) return 0;
  if(nYear % 100 != 0) return 1;
  return (uint8_t)(nYear % 400 == 0);
}

/*******************************************************************************
* Function Name  : Date_Update
* Description    : Updates date when time is 23:59:59.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Date_Update(void)
{
  if(sDate.month == 1 || sDate.month == 3 || sDate.month == 5 || sDate.month == 7 ||
     sDate.month == 8 || sDate.month == 10 || sDate.month == 12)
  {
    if(sDate.day < 31)
    {
      sDate.day++;
    }
    /* Date structure member: sDate.day = 31 */
    else
    {
      if(sDate.month != 12)
      {
        sDate.month++;
        sDate.day = 1;
      }
      /* Date structure member: sDate.day = 31 & sDate.month =12 */
      else
      {
        sDate.month = 1;
        sDate.day = 1;
        sDate.year++;
      }
    }
  }
  else if(sDate.month == 4 || sDate.month == 6 || sDate.month == 9 ||
          sDate.month == 11)
  {
    if(sDate.day < 30)
    {
      sDate.day++;
    }
    /* Date structure member: sDate.day = 30 */
    else
    {
      sDate.month++;
      sDate.day = 1;
    }
  }
  else if(sDate.month == 2)
  {
    if(sDate.day < 28)
    {
      sDate.day++;
    }
    else if(sDate.day == 28)
    {
      /* Leap year */
      if(IsLeapYear(sDate.year))
      {
        sDate.day++;
      }
      else
      {
        sDate.month++;
        sDate.day = 1;
      }
    }
    else if(sDate.day == 29)
    {
      sDate.month++;
      sDate.day = 1;
    }
  }

  MDR_BKP->REG_01 = sDate.year + (sDate.month << 16) + (sDate.day << 24);
  /* Wait until last write operation on RTC registers has finished */
  BKP_RTC_WaitForUpdate();
}

/*******************************************************************************
* Function Name  : IsValidDate
* Description    : Checks if the given date valid.
* Input          : Day   - Day value
*                : Month - Month value
*                : Year  - Year value
* Input          : None
* Output         : None
* Return         : SUCCESS if the date is valid, ERROR otherwise.
*******************************************************************************/
ErrorStatus IsValidDate(uint32_t Day, uint32_t Month, uint32_t Year)
{
  if(Day == 0 || Month == 0 || Month > 12 || Year == 0)
  {
    return ERROR;
  }
  if((Month == 1 || Month == 3 || Month == 5 || Month == 7 ||
     Month == 8 || Month == 10 || Month == 12) && (Day > 31))
  {
    return ERROR;
  }
  if((Month == 4 || Month == 6 || Month == 9 || Month == 11) && (Day > 30))
  {
    return ERROR;
  }
  if(Month == 2)
  {
    if (IsLeapYear(Year))
    {
      if (Day > 29)
      return ERROR;
    }
    else
    {
      if (Day > 28)
      return ERROR;
    }
  }
  return SUCCESS;
}

/*******************************************************************************
* Function Name  : Date_Display
* Description    : Displays the current date.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Date_Display(void)
{
  uint8_t tmp;
  uint32_t temp_date;

  /* Initialize Date structure */
  temp_date   = MDR_BKP->REG_01;
  sDate.day   = temp_date >> 24;
  sDate.month = (temp_date >> 16) & 0xFF;
  sDate.year  = temp_date & 0xFFFF;

  /* Display day */
  tmp = (uint8_t)(sDate.day / 10);
  LCD_PUTC(DateD_h, LineDigits, (tmp + 0x30));
  tmp = (uint8_t)(sDate.day % 10);
  LCD_PUTC(DateD_l, LineDigits, (tmp + 0x30));

  /* Display separator */
  LCD_PUTC(DateD_sep, LineDigits, '.');

  /* Display month */
  tmp = (uint8_t)(sDate.month / 10);
  LCD_PUTC(DateM_h, LineDigits, (tmp + 0x30));
  tmp = (uint8_t)(sDate.month % 10);
  LCD_PUTC(DateM_l, LineDigits, (tmp + 0x30));

  /* Display separator */
  LCD_PUTC(DateM_sep, LineDigits, '.');

  /* Display year */
  tmp = (uint8_t)(sDate.year / 1000);
  LCD_PUTC(DateY_1000, LineDigits, (tmp + 0x30));
  tmp = (uint8_t)((sDate.year / 100) % 10);
  LCD_PUTC(DateY_100, LineDigits, (tmp + 0x30));
  tmp = (uint8_t)((sDate.year / 10) % 10);
  LCD_PUTC(DateY_10, LineDigits, (tmp + 0x30));
  tmp = (uint8_t)(sDate.year % 10);
  LCD_PUTC(DateY_1, LineDigits, (tmp + 0x30));
}

/*******************************************************************************
* Function Name  : Date_Regulate
* Description    : Allows user to enter the date with joystick keys, stores it
*                : in Backup register REG_01.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Date_Regulate(void)
{
  uint32_t Tmp_day, Tmp_month, Tmp_year;
  FlagStatus ValidDateFlag;

  do
  {
    ValidDateFlag = SET;
    /* Read day */
    Tmp_day  = ReadDigit(DateD_h, (sDate.day / 10), 0x3, 0x0);
    Tmp_day  = Tmp_day * 10 + ReadDigit(DateD_l, (sDate.day % 10), (Tmp_day < 3) ? 0x9 : 0x1, 0x0);
    /* Read month */
    Tmp_month = ReadDigit(DateM_h, (sDate.month / 10), 0x1, 0x0);
    Tmp_month = Tmp_month * 10 + ReadDigit(DateM_l, (sDate.month % 10), (Tmp_month < 1) ? 0x9 : 0x2, 0x0);
    /* Read year */
    Tmp_year = ReadDigit(DateY_1000, (sDate.year / 1000), 0x2, 0x1) * 1000;
    Tmp_year = Tmp_year + (ReadDigit(DateY_100, ((sDate.year / 100) % 10), 0x9, 0x0) * 100);
    Tmp_year = Tmp_year + (ReadDigit(DateY_10, ((sDate.year / 10) % 10), 0x9, 0x0) * 10);
    Tmp_year = Tmp_year + ReadDigit(DateY_1, (sDate.year % 10), 0x9, 0x0);
    if (!IsValidDate(Tmp_day, Tmp_month, Tmp_year))
    {
      ValidDateFlag = RESET;
      LCD_PUTS(0, LineMessage1, "   Invalid date." );
      LCD_PUTS(0, LineMessage2, "   Repeat, please.");
      SysTickDelay(2500);
      LCD_PUTS(0, LineMessage1, "                " );
      LCD_PUTS(0, LineMessage2, "                  ");
      sDate.day   = Tmp_day;
      sDate.month = Tmp_month;
      sDate.year  = Tmp_year;
    }
  } while (ValidDateFlag == RESET);
  MDR_BKP->REG_01 = Tmp_year + (Tmp_month << 16) + (Tmp_day << 24);
  /* Wait until last write operation on RTC registers has finished */
  BKP_RTC_WaitForUpdate();
}

/*******************************************************************************
* Function Name  : DatePreAdjustFunc
* Description    : Adjust date menu item handler work function.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DatePreAdjustFunc(void)
{
  sFONT *OldFont = CurrentFont;
  LCD_Method OldMethod = CurrentMethod;

  /* Print the header */
  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;
  DisplayMenuTitle("Date adjust");
  WAIT_UNTIL_KEY_RELEASED(SEL);

  if((MDR_BKP->REG_00 != 0x1234) || (MDR_BKP->RTC_PRL != RTC_PRESCALER_VALUE))
  {
    RTCHelp();
  }
  else
  {
    LCD_PUTS(0, LineTitle, "DATE  DD.MM.YYYY");

    /* Display the current Date */
    Date_Display();
    /* Change the current Date */
    Date_Regulate();
  }

  CurrentMethod = OldMethod;
  CurrentFont = OldFont;
}

/*******************************************************************************
* Function Name  : DateAdjustFunc
* Description    : Adjust date menu item handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DateAdjustFunc(void)
{
  DatePreAdjustFunc();
  /* Display the menu */
  DisplayMenu();
}

/*******************************************************************************
* Function Name  : DateShowFunc
* Description    : Displays current date on LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DateShowFunc(void)
{
  sFONT *OldFont = CurrentFont;
  LCD_Method OldMethod = CurrentMethod;

  /* Print header */
  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;
  DisplayMenuTitle("Date show");
  WAIT_UNTIL_KEY_RELEASED(SEL);

  if((MDR_BKP->REG_00 != 0x1234) || (MDR_BKP->RTC_PRL != RTC_PRESCALER_VALUE))
  {
    RTCHelp();
  }
  else
  {
    LCD_PUTS(0, LineTitle, "DATE  DD.MM.YYYY");

    while (GetKey() != BACK)
    {
      /* Display the current Date */
      Date_Display();
    }
    WAIT_UNTIL_KEY_RELEASED(BACK);
  }

  CurrentMethod = OldMethod;
  CurrentFont = OldFont;

  /* Display menu */
  DisplayMenu();
}

/*******************************************************************************
* Function Name  : Alarm_Display
* Description    : Displays alarm time.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Alarm_Display()
{
  uint32_t AlarmVar = MDR_BKP->RTC_ALRM;

  /* Display time separators ":" */
  LCD_PUTS(Time_Display_Column, LineDigits, "  :  :");

  /* Display alarm hours */
  sAlarm.hour_h = (uint8_t)(AlarmVar / 3600) / 10;
  LCD_PUTC(TimeH_h, LineDigits, (sAlarm.hour_h + 0x30));
  sAlarm.hour_l = (uint8_t)(((AlarmVar) / 3600) % 10);
  LCD_PUTC(TimeH_l, LineDigits, (sAlarm.hour_l + 0x30));

  /* Display alarm minutes */
  sAlarm.min_h = (uint8_t)(((AlarmVar) % 3600) / 60) / 10;
  LCD_PUTC(TimeM_h, LineDigits, (sAlarm.min_h + 0x30));
  sAlarm.min_l = (uint8_t)(((AlarmVar) % 3600) / 60) % 10;
  LCD_PUTC(TimeM_l, LineDigits, (sAlarm.min_l + 0x30));

  /* Display alarm seconds */
  sAlarm.sec_h = (uint8_t)(((AlarmVar) % 3600) % 60) / 10;
  LCD_PUTC(TimeS_h, LineDigits, (sAlarm.sec_h + 0x30));
  sAlarm.sec_l = (uint8_t)(((AlarmVar) % 3600) % 60) % 10;
  LCD_PUTC(TimeS_l, LineDigits, (sAlarm.sec_l + 0x30));
}

/*******************************************************************************
* Function Name  : Alarm_Regulate
* Description    : Returns the alarm time entered by user, using joystick keys.
* Input          : None
* Output         : None
* Return         : Alarm time value to be loaded in RTC alarm register.
*******************************************************************************/
uint32_t Alarm_Regulate(void)
{
  uint32_t Alarm_HH, Alarm_MM, Alarm_SS;

  /* Read alarm hours */
  Alarm_HH = ReadDigit(TimeH_h, sAlarm.hour_h, 0x2, 0x0);
  if(Alarm_HH == 2)
  {
    if(sAlarm.hour_l > 3)
    {
      sAlarm.hour_l = 0;
    }
    Alarm_HH = Alarm_HH*10 + ReadDigit(TimeH_l, sAlarm.hour_l, 0x3, 0x0);
  }
  else
  {
    Alarm_HH = Alarm_HH*10 + ReadDigit(TimeH_l, sAlarm.hour_l, 0x9, 0x0);
  }
  /* Read time minutes */
  Alarm_MM = ReadDigit(TimeM_h, sAlarm.min_h, 0x5, 0x0);
  Alarm_MM = Alarm_MM*10 + ReadDigit(TimeM_l, sAlarm.min_l, 0x9, 0x0);
  /* Read time seconds */
  Alarm_SS = ReadDigit(TimeS_h, sAlarm.sec_h, 0x5, 0x0);
  Alarm_SS = Alarm_SS*10 + ReadDigit(TimeS_l, sAlarm.sec_l, 0x9, 0x0);

  /* Save the Alarm value in the Backup register REG_02 */
  MDR_BKP->REG_02 = Alarm_HH*3600 + Alarm_MM*60 + Alarm_SS;

  /* Return the value to store in RTC alarm register */
  return((Alarm_HH*3600 + Alarm_MM*60 + Alarm_SS));
}

/*******************************************************************************
* Function Name  : AlarmAdjustFunc
* Description    : Allows the user to set alarm event.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void AlarmAdjustFunc(void)
{
  sFONT *OldFont = CurrentFont;
  LCD_Method OldMethod = CurrentMethod;

  /* Print header */
  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;
  DisplayMenuTitle("Alarm adjust");
  WAIT_UNTIL_KEY_RELEASED(SEL);

  if((MDR_BKP->REG_00 != 0x1234) || (MDR_BKP->RTC_PRL != RTC_PRESCALER_VALUE))
  {
    RTCHelp();
  }
  else
  {
    LCD_PUTS(Time_Display_Column - DefaultFontWidth, LineTitle, "ALARM TIME");

    /* Initialize the RTC Alarm register */
    BKP_RTC_SetAlarm(MDR_BKP->REG_02);

    /* Display the Alarm time */
    Alarm_Display();

    /* Change the current alarm time */
    BKP_RTC_SetAlarm(Alarm_Regulate());
    /* Wait until last write operation on RTC registers has finished */
    BKP_RTC_WaitForUpdate();
    /* Enable the Alarm interrupt  */
    BKP_RTC_ITConfig(BKP_RTC_IT_ALRF, ENABLE);
    AlarmSetStatus = 1;
  }
  CurrentMethod = OldMethod;
  CurrentFont = OldFont;

  /* Display the menu */
  DisplayMenu();
}

/*******************************************************************************
* Function Name  : AlarmShowFunc
* Description    : Displays the alarm time (HH:MM:SS) on LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void AlarmShowFunc(void)
{
  sFONT *OldFont = CurrentFont;
  LCD_Method OldMethod = CurrentMethod;

  /* Print header */
  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;
  DisplayMenuTitle("Alarm show");
  WAIT_UNTIL_KEY_RELEASED(SEL);

  if((MDR_BKP->REG_00 != 0x1234) || (MDR_BKP->RTC_PRL != RTC_PRESCALER_VALUE))
  {
    RTCHelp();
  }
  else
  {
    LCD_PUTS(Time_Display_Column - DefaultFontWidth, LineTitle, "ALARM TIME");
    /* Display the current alarm time */
    Alarm_Display();
    WAIT_UNTIL_KEY_PRESSED(BACK);
    WAIT_UNTIL_KEY_RELEASED(BACK);
  }

  CurrentMethod = OldMethod;
  CurrentFont = OldFont;

  /* Display the menu */
  DisplayMenu();
}

/*******************************************************************************
* Function Name  : Calendar_Init
* Description    : Allows the user to initialize time and date values.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Calendar_Init(void)
{
  uint32_t tmp, i;
  KeyCode key;

  /* Enables the HSE clock for BKP control */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_BKP,ENABLE);

  RTC_Configuration();

  if(MDR_BKP->REG_00 != 0x1234)
  {
    LCD_CLS();
    LCD_PUTS(0, LineMessage1, " To configuring Time ");
    LCD_PUTS(0, LineMessage2, " and Date press SEL, ");
    LCD_PUTS(0, LineMessage3, " else press any key. ");

    for (key = NOKEY; key == NOKEY; key = GetKey())
    {
    }
    if (key == SEL)
    {
      WAIT_UNTIL_KEY_RELEASED(key);
      TimePreAdjustFunc();
      DatePreAdjustFunc();
    }
    else
    {
      /* Initialize Date structure with default values */
      sDate.day   = 1;
      sDate.month = 1;
      sDate.year  = 2010;
      MDR_BKP->REG_01 = sDate.year + (sDate.month << 16) + (sDate.day << 24);
      /* Wait until last write operation on RTC registers has finished */
      BKP_RTC_WaitForUpdate();
      /* Initialize Alarm backup register */
      MDR_BKP->REG_02 = 0;
      /* Wait until last write operation on RTC registers has finished */
      BKP_RTC_WaitForUpdate();
    }
    WAIT_UNTIL_KEY_RELEASED(key);
  }
  else
  {
    /* Initialize Date structure */
    tmp = MDR_BKP->REG_01;
    sDate.day   = tmp >> 24;
    sDate.month = (tmp >> 16) & 0xFF;
    sDate.year  = tmp & 0xFFFF;

    tmp = BKP_RTC_GetCounter();
    if(tmp / 86399 != 0)
    {
      for(i = 0; i < (tmp / 86399); i++)
      {
        Date_Update();
      }
      BKP_RTC_SetCounter(tmp % 86399);
    }
  }
}

/** @} */ /* End of group Menu_TIME_Private_Functions */

/** @} */ /* End of group Menu_TIME */

/** @} */ /* End of group Menu */

/** @} */ /* End of group __MDR1986VE1T_Eval_Demo */

/******************* (C) COPYRIGHT 2010 Milandr *******************
*
* END OF FILE Menu_time.c */

