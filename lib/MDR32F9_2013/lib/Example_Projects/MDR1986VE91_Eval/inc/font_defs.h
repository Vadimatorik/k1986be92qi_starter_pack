/**
  ******************************************************************************
  * @file    font_defs.h
  * @author  Phyton Application Team
  * @version V3.0.0
  * @date    08.09.2011
  * @brief   This file contains all the LCD fonts definition.
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
#ifndef __FONT_DEFS_H
#define __FONT_DEFS_H

/* Includes ------------------------------------------------------------------*/
#include "types.h"

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
  * @{
  */

/** @defgroup Fonts Fonts
  * @{
  */

/** @defgroup Fonts_Exported_Types Fonts Exported Types
  * @{
  */

/**
  * @brief  Font structure definition
  */
typedef struct
{
  uint32_t  Height;        /*!< Specifies the character height in pixels          */
  uint32_t  Width;         /*!< Specifies the character width in pixels           */
  uint32_t  Count;         /*!< Specifies the count of characters in the font - 1 */
  ucint8_t  *pData;        /*!< Specifies the font table address                 */
}sFONT;

/** @} */ /* End of group Fonts_Exported_Types */

/** @defgroup Fonts_Exported_Variables Fonts Exported Variables
  * @{
  */

extern sFONT Font_6x8;           /*!< Font  6 õ 8  pixels (normal) */
extern sFONT Font_7x10_thin;     /*!< Font  7 õ 10 pixels (thin)   */
extern sFONT Font_7x10_bold;     /*!< Font  7 õ 10 pixels (bold)   */
extern sFONT Font_12x16;         /*!< Font 12 õ 16 pixels (normal) */

/** @} */ /* End of group Fonts_Exported_Variables */

/** @} */ /* End of group Fonts */

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

#endif /* __FONT_DEFS_H */

/******************* (C) COPYRIGHT 2011 Phyton *********************************
*
* END OF FILE leds.h */
