/**
  ******************************************************************************
  * @file    ADC.h
  * @author  Milandr Application Team
  * @version V3.0.0
  * @date    09.09.2013
  * @brief   This file contains all the function prototypes for work with ADC
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
#ifndef __ADC_H
#define __ADC_H

/* Includes ------------------------------------------------------------------*/
#include <MDR32F9Qx_config.h>
#include "types.h"

/** @addtogroup __MDR1986VE3_Eval_Demo MDR1986VE3 Demonstration Example
  * @{
  */

/** @defgroup ADC_Routines ADC Routines
  * @{
  */

/** @defgroup ADC_Exported_Constants ADC Exported Constants
  * @{
  */


/** @} */ /* End of group ADC_Exported_Constants */

/** @defgroup ADC_Exported_Macros ADC Exported Macros
  * @{
  */


/** @} */ /* End of group ADC_Exported_Macros */

/** @defgroup ADC_Exported_Functions ADC Exported Functions
  * @{
  */

void ADC_Config(void);
void ADC_Temp_Sensor_Config(void);

/** @} */ /* End of group ADC_Exported_Functions */

/** @} */ /* End of group ADC_Routines */

/** @} */ /* End of group __MDR1986VE3_Eval_Demo */

#endif /* __ADC_H */

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE ADC.h */

