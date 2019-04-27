/**
  ******************************************************************************
  * @file    Menu_leds.c
  * @author  Phyton Application Team
  * @version V3.0.0
  * @date    10.09.2011
  * @brief   This file contains all the "LEDs" menu handlers
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

#include <MDR32F9Qx_port.h>
#include "Menu.h"
#include "Menu_items.h"
#include "leds.h"
#include "lcd.h"
#include "text.h"
#include "joystick.h"

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
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

#if defined (USE_MDR32F9Q1_Rev0) || defined (USE_MDR32F9Q1_Rev1)
#define LED_PATTERN                      0xFDF05380
#define LED_DELAY                        35000
#elif defined (USE_MDR32F9Q2_Rev0) || defined (USE_MDR32F9Q2_Rev1) || \
      defined (USE_MDR32F9Q3_Rev0) || defined (USE_MDR32F9Q3_Rev1)
#define LED_PATTERN                      0xAAAAAAAA
#define LED_DELAY                        35000
#endif

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
#if defined (USE_MDR32F9Q2_Rev0) || defined (USE_MDR32F9Q2_Rev1) || \
    defined (USE_MDR32F9Q3_Rev0) || defined (USE_MDR32F9Q3_Rev1)
  uint32_t saveport;
#endif

  /* Display hint on the screen and wait for key up */
  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;
  LCD_PUTS(0, 0,                       "   Press SEL      ");
  LCD_PUTS(0, CurrentFont->Height + 2, "   for return     ");
  WAIT_UNTIL_KEY_RELEASED(SEL);

#if defined (USE_MDR32F9Q2_Rev0) || defined (USE_MDR32F9Q2_Rev1) || \
    defined (USE_MDR32F9Q3_Rev0) || defined (USE_MDR32F9Q3_Rev1)

  /* Save LEDs_PORT port current state, because LEDs pins are also used
   * for LCD control */
  saveport = PORT_ReadInputData(LEDs_PORT);
#endif

  /* All LEDs switch off */
  PORT_ResetBits(LEDs_PORT, LEDs_PINs);

  /* Invoke "special effect" */
  CurrentLights = __SHLC(LED_PATTERN, LEDs_OFS);
  for (tck = 0, tck_led = 0; !KEY_PRESSED(SEL); tck++)
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

#if defined (USE_MDR32F9Q2_Rev0) || defined (USE_MDR32F9Q2_Rev1) || \
    defined (USE_MDR32F9Q3_Rev0) || defined (USE_MDR32F9Q3_Rev1)

  /* Restore LEDs_PORT port state */
  PORT_Write(LEDs_PORT, saveport);
#endif

  DisplayMenu();
}

/** @} */ /* End of group Menu_LEDs_Private_Functions */

/** @} */ /* End of group Menu_LEDs */

/** @} */ /* End of group Menu */

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

/******************* (C) COPYRIGHT 2011 Phyton *********************************
*
* END OF FILE Menu_leds.c */

