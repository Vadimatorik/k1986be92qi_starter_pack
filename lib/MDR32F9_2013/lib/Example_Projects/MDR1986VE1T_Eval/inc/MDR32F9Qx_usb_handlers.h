/**
  ******************************************************************************
  * @file    MDR32F9Qx_usb_handlers.h
  * @author  Milandr Application Team
  * @version V1.2.0
  * @date    18/03/2013
  * @brief   USB Library user-defined handlers definition file.
  ******************************************************************************
  * <br><br>
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2013 Milandr</center></h2>
  * FILE MDR32F9Qx_usb_handlers.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR32F9Qx_USB_HANDLERS_H
#define __MDR32F9Qx_USB_HANDLERS_H

/* Includes ------------------------------------------------------------------*/
#include <MDR32F9Qx_usb_default_handlers.h>

/* Configuration file MDR32F9Qx_config.h should be included before */
#ifndef __MDR32F9Qx_CONFIG_H
#error "Configuration file MDR32F9Qx_config.h should be included before"
#endif


/** @addtogroup __MDR1986VE1T_Eval_Demo MDR1986VE1T Demonstration Example
  * @{
  */

/** @addtogroup Menu Menu
  * @{
  */

/** @addtogroup  Menu_USB Menu USB VCOM
  * @{
  */

/** @defgroup USB_Virtual_COM_Port_Handlers USB Virtual COM Port Handlers
  * @{
  */

#undef USB_CDC_HANDLE_DATA_RECEIVE
#define USB_CDC_HANDLE_DATA_RECEIVE(BUFFER, LENGTH)   USB_CDC_RecieveData(BUFFER, LENGTH)

#ifdef USB_CDC_LINE_CODING_SUPPORTED
#undef USB_CDC_HANDLE_GET_LINE_CODING
#define USB_CDC_HANDLE_GET_LINE_CODING(wINDEX, DATA)  USB_CDC_GetLineCoding(wINDEX, DATA)
#undef USB_CDC_HANDLE_SET_LINE_CODING
#define USB_CDC_HANDLE_SET_LINE_CODING(wINDEX, DATA)  USB_CDC_SetLineCoding(wINDEX, DATA)
#endif /* USB_CDC_LINE_CODING_SUPPORTED */

#ifdef USB_CDC_CONTROL_LINE_STATE_SUPPORTED
#undef USB_CDC_HANDLE_CONTROL_LINE_STATE
#define USB_CDC_HANDLE_CONTROL_LINE_STATE(wVALUE, wINDEX)       USB_SUCCESS
#endif /* USB_CDC_CONTROL_LINE_STATE_SUPPORTED */

/** @} */ /* End of group USB_Virtual_COM_Port_Handlers */


/** @defgroup USB_Virtual_COM_Port_Handler_Functions USB Virtual COM Port Handler Functions
  * @{
  */

USB_Result USB_CDC_RecieveData(uint8_t* Buffer, uint32_t Length);

#ifdef USB_CDC_LINE_CODING_SUPPORTED
USB_Result USB_CDC_GetLineCoding(uint16_t wINDEX, USB_CDC_LineCoding_TypeDef* DATA);
USB_Result USB_CDC_SetLineCoding(uint16_t wINDEX, const USB_CDC_LineCoding_TypeDef* DATA);
#endif /* USB_CDC_LINE_CODING_SUPPORTED */

/** @} */ /* End of group USB_Virtual_COM_Port_Handler_Functions */

/** @} */ /* End of group Menu_USB */

/** @} */ /* End of group Menu */

/** @} */ /* End of group __MDR1986VE1T_Eval_Demo */

#endif /* __MDR32F9Qx_USB_HANDLERS_H */

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE MDR32F9Qx_usb_handlers.h */

