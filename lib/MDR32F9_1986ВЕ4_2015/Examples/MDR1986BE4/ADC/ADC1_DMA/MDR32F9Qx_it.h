/**
  ******************************************************************************
  * @file    Examples/MDR1986BE4_EVAL/ADC/ADC1_DMA/MDR32F9Qx_it.h
  * @author  Milandr Application Team
  * @version V1.2.0
  * @date    12/09/2014
  * @brief   This file contains all the functions prototypes for the interrupt.
  *
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2014 Milandr</center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR32F9QX_IT_H
#define __MDR32F9QX_IT_H

#include "MDR32F9Qx_adc.h"


void HardFault_Handler(void);
void DMA_IRQHandler(void);

#endif /* __MDR32F9QX_IT_H */

/******************* (C) COPYRIGHT 2014 Milandr *********/

/* END OF FILE MDR32F9Qx_it.h */
