/**
  ******************************************************************************
  * @file    Menu_leds.c
  * @author  Milandr Application Team
  * @version V3.0.0
  * @date    10.09.2013
  * @brief   This file contains all the "LEDs" menu handlers
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

#include <MDR32F9Qx_port.h>
#include "Menu.h"
#include "Menu_items.h"
#include "leds.h"
#include "lcd.h"
#include "text.h"
#include "joystick.h"

/** @addtogroup __MDR1986VE1T_Eval_Demo MDR1986VE1T Demonstration Example
  * @{
  */

/** @addtogroup Menu Menu
  * @{
  */

/** @addtogroup Menu_LEDs Menu LEDs
  * @{
  */

/** @defgroup Menu_LEDs_Private_Constants Menu LEDs Private Constants
  * @{
  */

#define LED_PATTERN                      0xFDF05380
#define LED_DELAY                        35000
//#define LED_PATTERN                      0xAAAAAAAA


/** @} */ /* End of group Menu_LEDs_Private_Constants */

/** @defgroup Menu_LEDs_Private_Functions Menu LEDs Private Functions
  * @{
  */


/*******************************************************************************
* Function Name  : LightsOnFunc
* Description    : Enables or disables LEDs toggling.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LightsOnFunc(void)
{
  uint32_t tck, tck_led;

  /* Display hint on the screen and wait for key up */
  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;
  LCD_PUTS(0, 0,                       "   Press BACK     ");
  LCD_PUTS(0, CurrentFont->Height + 2, "   for return     ");
  WAIT_UNTIL_KEY_RELEASED(SEL);


  /* All LEDs switch off */
  PORT_ResetBits(LEDs_PORT, LEDs_PINs);

  /* Invoke "special effect" */
  CurrentLights = __SHLC(LED_PATTERN, LEDs_OFS);
  for (tck = 0, tck_led = 0; !KEY_PRESSED(BACK); tck++)
  {
    if (tck == tck_led)
    {
      tck_led += LED_DELAY;
      ShiftLights();
    }
  }
  /* SEL is pressed - turn leds off and return to the menu */
  CurrentLights = 0x0;
  ShiftLights();
  DisplayMenu();
}

/** @} */ /* End of group Menu_LEDs_Private_Functions */

/** @} */ /* End of group Menu_LEDs */

/** @} */ /* End of group Menu */

/** @} */ /* End of group __MDR1986VE1T_Eval_Demo */

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE Menu_leds.c */

