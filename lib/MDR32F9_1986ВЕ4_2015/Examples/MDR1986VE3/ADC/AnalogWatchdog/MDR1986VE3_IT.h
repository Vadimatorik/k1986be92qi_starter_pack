/**
  ******************************************************************************
  * @file    Examples/MDR1986VE3_EVAL/UART/Interrupt/MDR1986VE3_IT.h
  * @author  Milandr Application Team
  * @version V1.2.0
  * @date    03/04/2013
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
  * <h2><center>&copy; COPYRIGHT 2013 Milandr</center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR1986VE3_IT_H
#define __MDR1986VE3_IT_H

/* Function prototypes -----------------------------------------------*/
void HardFault_Handler(void);
void ADC_IRQHandler(void);

#endif /* __MDR1986VE3_IT_H */

/******************* (C) COPYRIGHT 2013 Milandr *********/

/* END OF FILE MDR1986VE3_IT.h */
