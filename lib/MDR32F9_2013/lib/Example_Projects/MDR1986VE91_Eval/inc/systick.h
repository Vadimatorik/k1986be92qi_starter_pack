/**
  ******************************************************************************
  * @file    systick.h
  * @author  Phyton Application Team
  * @version V2.0.0
  * @date    08.09.2010
  * @brief   This file contains all the function prototypes of low-level
  *          utilities for work with the system timer.
  ******************************************************************************
  * <br><br>
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, PHYTON SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 Phyton</center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTICK_H
#define __SYSTICK_H

/* Includes ------------------------------------------------------------------*/
#include <MDR32Fx.h>
#include "types.h"

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
  * @{
  */

/** @defgroup Interrupt_Service_Routines Interrupt Service Routines
  * @{
  */

/** @defgroup Systick_Routines Systick Routines
  * @{
  */

/** @defgroup Systick_Exported_Functions Systick Exported Functions
  * @{
  */

/* System timer control */
void SysTickStart(uint32_t ticks);
void SysTickStop(void);

/* Delay function (systick-based) */
void SysTickDelay(uint32_t val);

/** @} */ /* End of group Systick_Exported_Functions */

/** @} */ /* End of group Systick_Routines */

/** @} */ /* End of group Interrupt_Service_Routines */

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

#endif /* __SYSTICK_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE systick.h */

