/**
  ******************************************************************************
  * @file    Menu.h
  * @author  Phyton Application Team
  * @version V3.0.0
  * @date    08.09.2011
  * @brief   This file contains all function prototypes for hierarchical text
  *          menu.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MENU_H
#define __MENU_H

/* Includes ------------------------------------------------------------------*/
#include "types.h"

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
  * @{
  */

/** @defgroup Menu Menu
  * @{
  */

/** @defgroup Menu_Exported_Constants Menu Exported Constants
  * @{
  */

#define  MAX_MENU_LEVELS 4

/** @} */ /* End of group Menu_Exported_Constants */

/** @defgroup Menu_Exported_Macros Menu Exported Macros
  * @{
  */

#define countof(a) (sizeof(a) / sizeof(*(a)))

/** @} */ /* End of group Menu_Exported_Macros */

/** @defgroup Menu_Exported_Functions Menu Exported Functions
  * @{
  */

void Menu_Init(void);
void DisplayMenuTitle(ucint8_t *ptr);
void DisplayMenu(void);
/* Waits for SEL pressed and returns to menu */
void BackToMenuOnSel(void);
/* Dispatcher function */
void ReadKey(void);

/** @} */ /* End of group Menu_Exported_Functions */

/** @} */ /* End of group Menu */

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

#endif /* __MENU_H */

/******************* (C) COPYRIGHT 2011 Phyton *********************************
*
* END OF FILE Menu.h */

