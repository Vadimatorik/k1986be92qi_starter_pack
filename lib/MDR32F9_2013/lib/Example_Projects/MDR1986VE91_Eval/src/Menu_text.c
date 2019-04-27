/**
  ******************************************************************************
  * @file    Menu_text.c
  * @author  Phyton Application Team
  * @version V3.0.0
  * @date    10.09.2011
  * @brief   This file contains all the "Text" menu handlers
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
#include <string.h>
#include <MDR32F9Qx_adc.h>
#include "lcd.h"
#include "Menu.h"
#include "Menu_items.h"
#include "text.h"
#include "joystick.h"
#include "adc.h"

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
  * @{
  */

/** @addtogroup Menu Menu
  * @{
  */

/** @addtogroup Menu_Text Menu Text
  * @{
  */

/** @defgroup Menu_Text_Private_Functions Menu Text Private Functions
  * @{
  */

/*******************************************************************************
* Function Name  : FontFunc
* Description    : Prints font samples
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FontFunc(void)
{
  sFONT *OldFont = CurrentFont;

  /* Print the header and wait for key up */
  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;
  DisplayMenuTitle("Font examples");
  WAIT_UNTIL_KEY_RELEASED(SEL);

  /* Font parameters */
  LCD_PUTS(0, 12, "Font6X8");

  CurrentFont = &Font_12x16;
  LCD_PUTS(0, 20, "Font12X16");

  CurrentFont = &Font_7x10_thin;
  LCD_PUTS(0, 36, "Font7X10");

  CurrentFont = &Font_7x10_bold;
  LCD_PUTS(0, 47, "Font7X10 bold");

  /* Wait for SEL pressed and return to the main menu */
  CurrentFont = OldFont;
  BackToMenuOnSel();
}

/*******************************************************************************
* Function Name  : StyleFunc
* Description    : Prints style samples
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void StyleFunc(void)
{
  sFONT *OldFont = CurrentFont;

  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;

  /* Print prompt and wait for key SEL pressed */
  LCD_PUTS(0, 12, "Turn the Trimmer TRIM");
  LCD_PUTS(0, 22, "to control the delay");
  LCD_PUTS(0, 32, "between style frames.");
  LCD_PUTS(0, 42, "Push JoyStick SEL to");
  LCD_PUTS(0, 52, "start or stop.");

  while (!KEY_PRESSED(SEL))
  {
  }

  /* Configure ADC channel 7 */
  ADC_Config();
  /* ADC1 enable */
  ADC1_Cmd(ENABLE);

  /* Print the header and wait for key up */
  LCD_CLS();
  DisplayMenuTitle("Style examples");
  WAIT_UNTIL_KEY_RELEASED(SEL);

  /* Style samples */
  do
  {
    LCD_PUTS_Ex(0, 12, "Blink     ", StyleBlink);
    if (KEY_PRESSED(SEL)) break;
    LCD_PUTS_Ex(0, 32, "FlipFlop", StyleFlipFlop);
    if (KEY_PRESSED(SEL)) break;
    LCD_PUTS_Ex(0, 52, "Vibratory", StyleVibratory);
  } while (!KEY_PRESSED(SEL));

  /* SEL is pressed - return to the main menu */
  CurrentFont = OldFont;
  /* ADC1 disable */
  ADC1_Cmd(DISABLE);
  DisplayMenu();
}

/** @defgroup Menu_Text_Private_Constants Menu Text Private Constants
  * @{
  */

/* The text for "e-book" demonstration */
static uint8_t Book[16][22] = {
    {"Microcontrollers of  "},
    {"MDR32F9Qx series are "},
    {"microcontrollers     "},
    {"with embedded Flash  "},
    {"program memory; they "},
    {"are built on the     "},
    {"base of high perfo-  "},
    {"mance RISC processor "},
    {"core Cortex-M3.      "},
    {"Microcontroller works"},
    {"on the up to 80 Mhz  "},
    {"frecuency and        "},
    {"contains 128 K Flash "},
    {"program memory and   "},
    {"32 K of RAM.         "}
};

/** @} */ /* End of group Menu_Text_Private_Constants */

/*******************************************************************************
* Function Name  : BookFunc
* Description    : Prints "e-book" text
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BookFunc(void)
{
  uint32_t top_ind, key, i;

  /* Clear screen and wait for key up */
  LCD_CLS();
  CurrentMethod = MET_AND;
  WAIT_UNTIL_KEY_RELEASED(SEL);

  /* Key handling loop */
  for (top_ind = 0, key = NOKEY; key != SEL; )
  {
    /* Print the text and wait for key pressed */
    for (i = 0; i < 8; i++)
    {
      LCD_PUTS(0, (CurrentFont->Height) * i, Book[top_ind + i]);
    }
    WAIT_UNTIL_ANY_KEY;

    /* Key pressed handling */
    key = GetKey();
    switch (key)
    {
      /* Scroll up */
      case UP:
        if (top_ind > 0)
        {
          top_ind--;
        }
        break;
      /* Scroll down */
      case DOWN:
        if (top_ind < 7)
        {
          top_ind++;
        }
        break;
    }
  }

  /* SEL is pressed - return to main menu */
  WAIT_UNTIL_KEY_RELEASED(key);
  DisplayMenu();
}

/*******************************************************************************
* Function Name  : AboutFunc
* Description    : Displays "About"
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void AboutFunc(void)
{

#if defined (USE_MDR32F9Q1_Rev0) || defined (USE_MDR32F9Q1_Rev1)
#define EVAL_BOARD_NAME                "   Milandr MDR32F9Q1   "
#elif defined (USE_MDR32F9Q2_Rev0) || defined (USE_MDR32F9Q2_Rev1)
#define EVAL_BOARD_NAME                "   Milandr MDR32F9Q2  "
#elif defined (USE_MDR32F9Q3_Rev0) || defined (USE_MDR32F9Q3_Rev1)
#define EVAL_BOARD_NAME                "   Milandr MDR32F9Q3  "
#endif

  /* Display About text */
  LCD_CLS();
  CurrentMethod = MET_AND;

  LCD_PUTS(0, 0, EVAL_BOARD_NAME);
  LCD_PUTS(0, CurrentFont->Height + 1, "   Evaluation board  ");
  LCD_PUTS(0, (CurrentFont->Height) * 2 + 2, "          ");
  LCD_PUTS(0, (CurrentFont->Height) * 3 + 2, "          ");
  LCD_PUTS(0, (CurrentFont->Height) * 4 + 3, " Appl. example v.3.0");
  LCD_PUTS(0, (CurrentFont->Height) * 5 + 4, "     Phyton 2011   ");
  LCD_PUTS(0, (CurrentFont->Height) * 6 + 5, "    www.phyton.ru  ");

  /* Wait for SEL pressed and return to main menu */
  BackToMenuOnSel();
}

/** @} */ /* End of group Menu_Text_Private_Functions */

/** @} */ /* End of group Menu_Text */

/** @} */ /* End of group Menu */

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

/******************* (C) COPYRIGHT 2011 Phyton *********************************
*
* END OF FILE Menu_text.c */

