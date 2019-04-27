/**
  ******************************************************************************
  * @file    time.h
  * @author  Milandr Application Team
  * @version V1.2.0
  * @date    09.10.2013
  * @brief   This file contains all the functions prototypes for the date/time
  *          driver.
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
#ifndef __TIME_H
#define __TIME_H

/* Includes ------------------------------------------------------------------*/

/** @addtogroup __MDR1986VE1T_Eval_Demo MDR1986VE1T Demonstration Example
  * @{
  */

/** @addtogroup Menu Menu
  * @{
  */

/** @defgroup Menu_TIME Menu TIME
  * @{
  */

/** @defgroup RTC_Exported_Constants RTC Exported Private Constants
  * @{
  */

/** @} */ /* End of group RTC_Exported_Constants */

/** @defgroup RTC_Exported_Functions RTC Exported Functions
  * @{
  */

void Date_Update(void);
void Calendar_Init(void);

/** @} */ /* End of group RTC_Exported_Functions */

/** @} */ /* End of group Menu_TIME */

/** @} */ /* End of group Menu */

/** @} */ /* End of group __MDR1986VE1T_Eval_Demo */

#endif /*__TIME_H*/

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE time.h */

