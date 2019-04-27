/**
  ******************************************************************************
  * @file    Menu_items.h
  * @author  Milandr Application Team
  * @version V3.0.0
  * @date    08.09.2013
  * @brief   This file contains all the menu handler functions.
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
#ifndef __MENU_ITEMS_H
#define __MENU_ITEMS_H

/** @addtogroup __MDR1986VE1T_Eval_Demo MDR1986VE1T Demonstration Example
  * @{
  */

/** @addtogroup Menu Menu
  * @{
  */

/** @addtogroup Menu_Exported_Functions Menu Exported Functions
  * @{
  */

/** @defgroup Menu_Graphics_Functions Menu Graphics Functions
  * @{
  */

void ElementsFunc(void);
void IndicatorsFunc(void);

/** @} */ /* End of group Menu_Graphics_Functions */

/** @defgroup Menu_LEDs_Functions Menu LEDs Functions
  * @{
  */

void LightsOnFunc(void);

/** @} */ /* End of group Menu_LEDs_Functions */

/** @defgroup Menu_Text_Functions Menu Text Functions
  * @{
  */

void FontFunc(void);
void StyleFunc(void);
void ShiftFunc(void);
void BookFunc(void);
void AboutFunc(void);

/** @} */ /* End of group Menu_Text_Functions */

/** @defgroup Menu_UART_Functions Menu UART Functions
  * @{
  */

void UARTwFIFOFunc(void);
void UARTFunc(void);

/** @} */ /* End of group Menu_UART_Functions */

/** @defgroup Menu_TSENSOR_Functions Menu Temperature Sensor Functions
  * @{
  */

void TSENSORFunc(void);

/** @} */ /* End of group Menu_TSENSOR_Functions */

/** @defgroup Menu_Time_Functions Menu Time Functions
  * @{
  */

void TimeAdjustFunc(void);
void TimeShowFunc(void);
void DateAdjustFunc(void);
void DateShowFunc(void);
void AlarmAdjustFunc(void);
void AlarmShowFunc(void);

/** @} */ /* End of group Menu_Time_Functions */

/** @defgroup Menu_VCOM_Functions Menu USB Virtual COM Functions
  * @{
  */

void VCOMFunc(void);

/** @} */ /* End of group Menu_VCOM_Functions */

/** @defgroup Menu_LowPower_Functions Menu Low Power Functions
  * @{
  */

void STANDBYMode_WAKEUP(void);
void STANDBYMode_RTCAlarm(void);
void STOPMode_RTCAlarm(void);

/** @} */ /* End of group Menu_LowPower_Functions */

/** @} */ /* End of group Menu_Exported_Functions */

/** @} */ /* End of group Menu */

/** @} */ /* End of group __MDR1986VE1T_Eval_Demo */

#endif /* __MENU_ITEMS_H */

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE Menu_items.h */

