/**
  ******************************************************************************
  * @file    1986BE9x.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    24/09/2010
  * @brief   This file contains all the Special Function Registers definitions
  *          for the Milandr 1986BE9X microcontroller.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, PHYTON SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 Phyton</center></h2>
  ******************************************************************************
  * FILE 1986BE9x.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9X_H
#define __1986BE9X_H

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @defgroup __1986BE9X 1986BE9X
  * @{
  */

/** @defgroup __Exported_types Exported types
  * @{
  */

/**
  * @brief 1986BE9x Interrupt Number Definition
  */

typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
  HardFault_IRQn              = -13,    /*!< 3 Cortex-M3 Hard Fault Interrupt                     */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */

/****** 1986BE9X specific Interrupt Numbers *******************************************************/
  CAN1_IRQn                   = 0,      /*!< CAN1 Interrupt                                       */
  CAN2_IRQn                   = 1,      /*!< CAN1 Interrupt                                       */
  USB_IRQn                    = 2,      /*!< USB Host Interrupt                                   */
  DMA_IRQn                    = 5,      /*!< DMA Interrupt                                        */
  UART1_IRQn                  = 6,      /*!< UART1 Interrupt                                      */
  UART2_IRQn                  = 7,      /*!< UART2 Interrupt                                      */
  SSP1_IRQn                   = 8,      /*!< SSP1 Interrupt                                       */
  I2C_IRQn                    = 10,     /*!< I2C Interrupt                                        */
  POWER_IRQn                  = 11,     /*!< POWER Detecor Interrupt                              */
  WWDG_IRQn                   = 12,     /*!< Window Watchdog Interrupt                            */
  Timer1_IRQn                 = 14,     /*!< Timer1 Interrupt                                     */
  Timer2_IRQn                 = 15,     /*!< Timer2 Interrupt                                     */
  Timer3_IRQn                 = 16,     /*!< Timer3 Interrupt                                     */
  ADC_IRQn                    = 17,     /*!< ADC Interrupt                                        */
  COMPARATOR_IRQn             = 19,     /*!< COMPARATOR Interrupt                                 */
  SSP2_IRQn                   = 20,     /*!< SSP2 Interrupt                                       */
  BACKUP_IRQn                 = 27,     /*!< BACKUP Interrupt                                     */
  EXT_INT1_IRQn               = 28,     /*!< EXT_INT1 Interrupt                                   */
  EXT_INT2_IRQn               = 29,     /*!< EXT_INT2 Interrupt                                   */
  EXT_INT3_IRQn               = 30,     /*!< EXT_INT3 Interrupt                                   */
  EXT_INT4_IRQn               = 31      /*!< EXT_INT4 Interrupt                                   */
}IRQn_Type;

/* Includes ------------------------------------------------------------------*/
#include "core_cm3.h"

#include "1986BE9x_can_defs.h"
#include "1986BE9x_usb_defs.h"
#include "1986BE9x_eeprom_defs.h"
#include "1986BE9x_rst_clk_defs.h"
#include "1986BE9x_dma_defs.h"
#include "1986BE9x_uart_defs.h"
#include "1986BE9x_spi_defs.h"
#include "1986BE9x_i2c_defs.h"
#include "1986BE9x_power_defs.h"
#include "1986BE9x_wwdg_defs.h"
#include "1986BE9x_iwdg_defs.h"
#include "1986BE9x_timer_defs.h"
#include "1986BE9x_adc_defs.h"
#include "1986BE9x_dac_defs.h"
#include "1986BE9x_comp_defs.h"
#include "1986BE9x_port_defs.h"
#include "1986BE9x_bkp_defs.h"
#include "1986BE9x_ext_bus_cntrl_defs.h"

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

/** @} */ /* End of group __Exported_types */


/** @defgroup __Peripheral_Memory_Map Peripheral Memory Map
  * @{
  */

#define CAN1_BASE           0x40000000
#define CAN2_BASE           0x40008000
#define USB_BASE            0x40010000
#define EEPROM_BASE         0x40018000
#define RST_CLK_BASE        0x40020000
#define DMA_BASE            0x40028000
#define UART1_BASE          0x40030000
#define UART2_BASE          0x40038000
#define SPI1_BASE           0x40040000
#define I2C_BASE            0x40050000
#define POWER_BASE          0x40058000
#define WWDG_BASE           0x40060000
#define IWDG_BASE           0x40068000
#define TIMER1_BASE         0x40070000
#define TIMER2_BASE         0x40078000
#define TIMER3_BASE         0x40080000
#define ADC_BASE            0x40088000
#define DAC_BASE            0x40090000
#define COMP_BASE           0x40098000
#define SPI2_BASE           0x400A0000
#define PORTA_BASE          0x400A8000
#define PORTB_BASE          0x400B0000
#define PORTC_BASE          0x400B8000
#define PORTD_BASE          0x400C0000
#define PORTE_BASE          0x400C8000
#define BKP_BASE            0x400D8000
#define PORTF_BASE          0x400E8000
#define EXT_BUS_CNTRL_BASE  0x400F0000

/** @} */ /* End of group __Peripheral_Memory_Map */

/** @defgroup __Peripheral_declaration Peripheral declaration
  * @{
  */

#define CAN1                ((CAN_TypeDef*)     CAN1_BASE)
#define CAN2                ((CAN_TypeDef*)     CAN2_BASE)
#define USB                 ((USB_TypeDef*)     USB_BASE)
#define EEPROM              ((EEPROM_TypeDef*)  EEPROM_BASE)
#define RST_CLK             ((RST_CLK_TypeDef*) RST_CLK_BASE)
#define DMA                 ((DMA_TypeDef*)     DMA_BASE)
#define UART1               ((UART_TypeDef*)    UART1_BASE)
#define UART2               ((UART_TypeDef*)    UART2_BASE)
#define SPI1                ((SPI_TypeDef*)     SPI1_BASE)
#define I2C                 ((I2C_TypeDef*)     I2C_BASE)
#define POWER               ((POWER_TypeDef*)   POWER_BASE)
#define WWDG                ((WWDG_TypeDef*)    WWDG_BASE)
#define IWDG                ((IWDG_TypeDef*)    IWDG_BASE)
#define TIMER1              ((TIMER_TypeDef*)   TIMER1_BASE)
#define TIMER2              ((TIMER_TypeDef*)   TIMER2_BASE)
#define TIMER3              ((TIMER_TypeDef*)   TIMER3_BASE)
#define ADC                 ((ADC_TypeDef*)     ADC_BASE)
#define DAC                 ((DAC_TypeDef*)     DAC_BASE)
#define COMP                ((COMP_TypeDef*)    COMP_BASE)
#define SPI2                ((SPI_TypeDef*)     SPI2_BASE)
#define PORTA               ((PORT_TypeDef*)    PORTA_BASE)
#define PORTB               ((PORT_TypeDef*)    PORTB_BASE)
#define PORTC               ((PORT_TypeDef*)    PORTC_BASE)
#define PORTD               ((PORT_TypeDef*)    PORTD_BASE)
#define PORTE               ((PORT_TypeDef*)    PORTE_BASE)
#define BKP                 ((BKP_TypeDef*)     BKP_BASE)
#define PORTF               ((PORT_TypeDef*)    PORTF_BASE)
#define EXT_BUS_CNTRL       ((EXT_BUS_CNTRL_TypeDef*)EXT_BUS_CNTRL_BASE)

/** @} */ /* End of group __Peripheral_declaration */

/** @} */ /* End of group __1986BE9X */

/** @} */ /* End of group __CMSIS */

#endif /* __1986BE9X_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x.h */
