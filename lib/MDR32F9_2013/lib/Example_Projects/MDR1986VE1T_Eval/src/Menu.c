/**
  ******************************************************************************
  * @file    Menu.c
  * @author  Milandr Application Team
  * @version V3.0.0
  * @date    10.09.2013
  * @brief   This file contains all the functions for hierarchical text menu.
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
#include <stddef.h>
#include "Menu.h"
#include "Menu_items.h"
#include "types.h"
#include "lcd.h"
#include "gl.h"
#include "text.h"
#include "joystick.h"
#include "leds.h"

/** @addtogroup __MDR1986VE1T_Eval_Demo MDR1986VE1T Demonstration Example
  * @{
  */

/** @addtogroup Menu Menu
  * @{
  */

/** @defgroup Menu_Private_Types Menu Private Types
  * @{
  */

/* Menu description */
typedef void (* tMenuFunc)(void);
typedef struct sMenuItem *tMenuItem;
typedef struct sMenu *tMenu;

/**
  * @brief  Menu item structure definition
  */
struct sMenuItem
{
  ucint8_t* psTitle;
  tMenuFunc pfMenuFunc;
  tMenu psSubMenu;
};

/**
  * @brief  Menu structure definition
  */
struct sMenu
{
  ucint8_t* psTitle;
  tMenuItem psItems;
  uint32_t nItems;
};

/** @} */ /* End of group Menu_Private_Types */

/* Service function and handler prototypes */
static void DisplayMenuItemString(uint32_t y, ucint8_t *ptr);
static void IdleFunc(void);
static void SelFunc(void);
static void UpFunc(void);
static void DownFunc(void);
static void ReturnFunc(void);

/** @defgroup Menu_Private_Variables Menu Private Variables
  * @{
  */

static uint32_t MenuItemIndex = 0, nMenuLevel = 0;

static tMenuItem psMenuItem, psCurrentMenuItem;
static tMenu psPrevMenu[MAX_MENU_LEVELS];
static tMenu psCurrentMenu;

/* Fourth level menu */
struct sMenuItem TimeMenuItems[] = {{"Adjust", TimeAdjustFunc, NULL},
                                    {"Show", TimeShowFunc, NULL},
                                    {"Return", ReturnFunc, NULL}};
struct sMenu TimeMenu = {"Time", TimeMenuItems, countof(TimeMenuItems)};

struct sMenuItem DateMenuItems[] = {{"Adjust", DateAdjustFunc, NULL},
                                    {"Show", DateShowFunc, NULL},
                                    {"Return", ReturnFunc, NULL}};
struct sMenu DateMenu = {"Date", DateMenuItems, countof(DateMenuItems)};

struct sMenuItem AlarmMenuItems[] = {{"Adjust", AlarmAdjustFunc, NULL},
                                     {"Show", AlarmShowFunc, NULL},
                                     {"Return", ReturnFunc, NULL}};
struct sMenu AlarmMenu = {"Alarm", AlarmMenuItems, countof(AlarmMenuItems)};

/*struct sMenuItem STOPMenuItems[] = {{"Exit on RTC Alarm", STOPMode_RTCAlarm, NULL},
                                    {"Return", ReturnFunc, NULL}};
struct sMenu STOPMenu = {"STOP Mode", STOPMenuItems, countof(STOPMenuItems)};*/

struct sMenuItem STANDBYMenuItems[] = {
                     {"Exit on Wakeup", STANDBYMode_WAKEUP, NULL},
                     {"Exit on RTC Alarm", STANDBYMode_RTCAlarm, NULL},
                                       {"Return", ReturnFunc, NULL}};
struct sMenu STANDBYMenu = {"STANDBY Mode", STANDBYMenuItems, countof(STANDBYMenuItems)};

struct sMenuItem UARTMenuItems[] = {{"With FIFO", UARTwFIFOFunc, NULL},
                                    {"Without FIFO", UARTFunc, NULL},
                                    {"Return", ReturnFunc, NULL}};
struct sMenu UARTMenu = {"UART", UARTMenuItems, countof(UARTMenuItems)};

struct sMenuItem RTCMenuItems[] = {{"Time", IdleFunc, &TimeMenu},
                                   {"Date", IdleFunc, &DateMenu},
                                   {"Alarm", IdleFunc, &AlarmMenu},
                                   {"Return", ReturnFunc, NULL}};
struct sMenu RTCMenu = {"Real Time Clock", RTCMenuItems, countof(RTCMenuItems)};

struct sMenuItem LowPowerMenuItems[] = {/*{"STOP", IdleFunc, &STOPMenu}, */
                                        {"STANDBY", IdleFunc, &STANDBYMenu},
                                        {"Return", ReturnFunc, NULL}};
struct sMenu LowPowerMenu = {"Low Power Mode", LowPowerMenuItems, countof(LowPowerMenuItems)};

/* Third level menu */
struct sMenuItem TextMenuItems[] = {{"Font", FontFunc, NULL},
                                    {"Style", StyleFunc, NULL},
                                    {"Book", BookFunc, NULL},
                                    {"Return", ReturnFunc, NULL}};
struct sMenu TextMenu = {"Text", TextMenuItems, countof(TextMenuItems)};

struct sMenuItem GraphicMenuItems[] = {{"Elements", ElementsFunc, NULL},
                                       {"Indicators", IndicatorsFunc, NULL},
                                       {"Return", ReturnFunc, NULL}};
struct sMenu GraphicMenu = {"Graphics", GraphicMenuItems, countof(GraphicMenuItems)};

struct sMenuItem LEDsMenuItems[] = {{"On", LightsOnFunc, NULL},
                                    {"Return", ReturnFunc, NULL}};
struct sMenu LEDsMenu = {"LEDs", LEDsMenuItems, countof(LEDsMenuItems)};

struct sMenuItem CommMenuItems[] = {{"UART", IdleFunc, &UARTMenu},
                                    {"USB. Virtual COM", VCOMFunc, NULL},
                                    {"Return", ReturnFunc, NULL}};
struct sMenu CommMenu = {"Communication", CommMenuItems, countof(CommMenuItems)};

struct sMenuItem OtherMenuItems[] = {{"Thermometer", TSENSORFunc, NULL},
                                     {"Real Time Clock", IdleFunc, &RTCMenu},
                                     {"Low Power", IdleFunc, &LowPowerMenu},
                                     {"Return", ReturnFunc, NULL}};
struct sMenu OtherMenu = {"Other devices", OtherMenuItems, countof(OtherMenuItems)};

/* Second level menu */
struct sMenuItem LCDMenuItems[] = {{"Text", IdleFunc, &TextMenu},
                                   {"Graphics", IdleFunc, &GraphicMenu},
                                   {"LEDs", IdleFunc, &LEDsMenu},
                                   {"Return", ReturnFunc, NULL}};
struct sMenu LCDMenu = {"Display", LCDMenuItems, countof(LCDMenuItems)};

struct sMenuItem DevMenuItems[] = {{"Communication", IdleFunc, &CommMenu},
                                   {"Other", IdleFunc, &OtherMenu},
                                   {"Return", ReturnFunc, NULL}};
struct sMenu DevMenu = {"Devices", DevMenuItems, countof(DevMenuItems)};

/* Main menu */
struct sMenuItem MainMenuItems[] = {
  {"Display", IdleFunc, &LCDMenu},
  {"Devices", IdleFunc, &DevMenu},
  {"About", AboutFunc, NULL}};
struct sMenu MainMenu = {"Main menu", MainMenuItems, countof(MainMenuItems)};

/** @} */ /* End of group Menu_Private_Variables */

/** @defgroup Menu_Private_Functions Menu Private Functions
  * @{
  */

/** @defgroup Menu_Service_Functions Menu Service Functions
  * @{
  */

/* Service functions for menu drawing */

/*******************************************************************************
* Function Name  : DisplayMenuItemString
* Description    : Prints menu line
* Input          : y   - line y-coordinate
*                : ptr - pointer to string
* Output         : None
* Return         : None
*******************************************************************************/
void DisplayMenuItemString(uint32_t y, ucint8_t *ptr)
{
  uint32_t x;

  LCD_PUTS(0, y, "                                        ");
  x = (MAX_X - (CurrentFont->Width * strlen((const char *)ptr))) / 2;
  LCD_PUTS(x, y, ptr);
}

/* Service handlers */

/*******************************************************************************
* Function Name  : IdleFunc
* Description    : Booby
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void IdleFunc(void)
{
}

/*******************************************************************************
* Function Name  : SelFunc
* Description    : SEL - jumps to the submenu and/or calls corresponding handler
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SelFunc(void)
{
  psCurrentMenuItem = psMenuItem;

  if(psMenuItem->psSubMenu != NULL)
  {
    MenuItemIndex = 0;
    psCurrentMenu = psMenuItem->psSubMenu;
    psMenuItem = &(psCurrentMenu->psItems)[MenuItemIndex];
    DisplayMenu();
    nMenuLevel++;
    psPrevMenu[nMenuLevel] = psCurrentMenu;
  }
  psCurrentMenuItem->pfMenuFunc();
}

/*******************************************************************************
* Function Name  : UpFunc
* Description    : UP - steps one one item up
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UpFunc(void)
{
  /* Display current menu item as non-selected */
  psMenuItem = &psCurrentMenu->psItems[MenuItemIndex];
  CurrentMethod = MET_AND;
  DisplayMenuItemString((MenuItemIndex * (CurrentFont->Height + 2) + CurrentFont->Height + 4), psMenuItem->psTitle);

  /* Determine new menu item (iteratively) */
  if(MenuItemIndex > 0)
  {
    MenuItemIndex--;
  }
  else
  {
    MenuItemIndex = psCurrentMenu->nItems - 1;
  }

  /* Display new menu item as selected */
  psMenuItem = &psCurrentMenu->psItems[MenuItemIndex];
  CurrentMethod = MET_NOT_XOR;
  LCD_PUTS(0, (MenuItemIndex * (CurrentFont->Height + 2) + CurrentFont->Height + 4), "                                        ");
}

/*******************************************************************************
* Function Name  : DownFunc
* Description    : DOWN - steps one one item down
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DownFunc(void)
{
  /* Display current menu item as non-selected */
  psMenuItem = &psCurrentMenu->psItems[MenuItemIndex];
  CurrentMethod = MET_AND;

  DisplayMenuItemString((MenuItemIndex * (CurrentFont->Height + 2) + CurrentFont->Height + 4), psMenuItem->psTitle);

  /* Determine new menu item (iteratively) */
  if(MenuItemIndex >= ((psCurrentMenu->nItems)-1))
  {
    MenuItemIndex = 0;
  }
  else
  {
    MenuItemIndex++;
  }
  psMenuItem = &(psCurrentMenu->psItems[MenuItemIndex]);

  /* Display new menu item as selected */
  CurrentMethod = MET_NOT_XOR;
  LCD_PUTS(0, (MenuItemIndex * (CurrentFont->Height + 2) + CurrentFont->Height + 4), "                                        ");
}

/*******************************************************************************
* Function Name  : ReturnFunc
* Description    : Jumps to upper level menu
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ReturnFunc(void) {
  if(nMenuLevel == 0)
  {
    nMenuLevel++;
  }

  psCurrentMenu = psPrevMenu[nMenuLevel-1];
  psMenuItem = &psCurrentMenu->psItems[0];
  MenuItemIndex = 0;
  nMenuLevel--;

  DisplayMenu();
}

/*******************************************************************************
* Function Name  : BackToMenuOnSel
* Description    : Waits for SEL pressed and returns to the menu
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BackToMenuOnSel(void)
{
  WAIT_UNTIL_KEY_PRESSED(SEL);
  DisplayMenu();
}

/*******************************************************************************
* Function Name  : BackToMenuOnBack
* Description    : Waits for BACK pressed and returns to the menu
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BackToMenuOnBack(void)
{
  WAIT_UNTIL_KEY_PRESSED(BACK);
  DisplayMenu();
}

/*******************************************************************************
* Function Name  : ReadKey
* Description    : Dispatcher function
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ReadKey(void)
{
  uint32_t key;

  while (1)
  {
    key = GetKey();
    switch (key)
    {
      case SEL:   SelFunc();  break;
      case UP:    UpFunc();   break;
      case DOWN:  DownFunc(); break;
      case BACK:  ReturnFunc();break;
    }
  WAIT_UNTIL_KEY_RELEASED(key);
  }
}

/** @} */ /* End of group Menu_Service_Functions */

/** @defgroup Menu_Functions Menu Functions
  * @{
  */

/*----------------- Interface functions -----------------*/

/*******************************************************************************
* Function Name  : DisplayMenuTitle
* Description    : Prints menu header
* Input          : ptr - pointer to header string
* Output         : None
* Return         : None
*******************************************************************************/
void DisplayMenuTitle(ucint8_t *ptr)
{
  uint32_t x, y;
  sFONT *OldFont = CurrentFont;
  LCD_Method OldMethod = CurrentMethod;

  CurrentFont = &Font_6x8;
  CurrentMethod = MET_AND;

  x = (MAX_X - (CurrentFont->Width * strlen((const char *)ptr))) / 2;
  LCD_PUTS(x, 0, ptr);

  y = CurrentFont->Height + 1;
  CurrentMethod = MET_OR;
  LCD_Line(0, y, MAX_X, y);

  CurrentFont = OldFont;
  CurrentMethod = OldMethod;
}

/*******************************************************************************
* Function Name  : Menu_Init
* Description    : Menu initialization
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Menu_Init(void)
{
  psCurrentMenu = &MainMenu;
  psPrevMenu[nMenuLevel] = psCurrentMenu;
  psMenuItem = MainMenuItems;
  CurrentFont = &Font_6x8;
}

/*******************************************************************************
* Function Name  : DisplayMenu
* Description    : Displays the current menu
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DisplayMenu(void)
{
  uint32_t y, index;
  tMenuItem psMenuItem2;

  LCD_CLS();
  CurrentMethod = MET_AND;

  /* Display menu header */
  DisplayMenuTitle(psCurrentMenu->psTitle);
  /* Display menu items */
  for (index = 0, y = CurrentFont->Height + 4;
       index < psCurrentMenu->nItems;
       index++, y += CurrentFont->Height + 2)
  {
    psMenuItem2 = &(psCurrentMenu->psItems[index]);
    DisplayMenuItemString(y, psMenuItem2->psTitle);
  }

  /* Determine current item */
  psMenuItem = &(psCurrentMenu->psItems[MenuItemIndex]);
  CurrentMethod = MET_NOT_XOR;
  LCD_PUTS(0, (MenuItemIndex * (CurrentFont->Height + 2) + CurrentFont->Height + 4), "                                        ");
}

/** @} */ /* End of group Menu_Functions */

/** @} */ /* End of group Menu_Private_Functions */

/** @} */ /* End of group Menu */

/** @} */ /* End of group __MDR1986VE1T_Eval_Demo */

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE Menu.c */

