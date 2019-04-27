/**
  ******************************************************************************
  * @file    Demo_Init.h
  * @author  Phyton Application Team
  * @version V2.0.0
  * @date    19.07.2011
  * @brief   Initializes the demonstration application.
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
#ifndef DEMO_INIT_H
#define DEMO_INIT_H

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
  * @{
  */

/** @defgroup Demo_Setup Demo Setup
  * @{
  */

/** @defgroup Demo_Setup_Exported_Variables Demo Setup Exported Variables
  * @{
  */

static PORT_InitTypeDef PortInitStructure;

/** @} */ /* End of group Demo_Setup_Exported_Variables */

/** @defgroup Demo_Setup_Exported_Functions Demo Setup Exported Functions
  * @{
  */

void Demo_Init(void);

/** @} */ /* End of group Demo_Setup_Exported_Functions */

/** @} */ /* End of group Demo_Setup */

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

#endif /* DEMO_INIT_H */

