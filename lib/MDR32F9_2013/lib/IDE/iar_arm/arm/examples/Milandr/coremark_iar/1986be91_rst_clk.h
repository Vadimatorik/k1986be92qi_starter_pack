#ifndef __1986BE91_RST_CLK_H
#define __1986BE91_RST_CLK_H

#include "cm3_macro.h"

typedef struct {
  unsigned PLL_USB_RDY                          : 1;
  unsigned PLL_CPU_RDY                          : 1;
  unsigned HSE_RDY                              : 1;
  unsigned __dummy0                             : 29;
} _rst_clk_clock_status;

typedef volatile _rst_clk_clock_status _io_rst_clk_clock_status;

#define offs_RST_CLK_CLOCK_STATUS_PLL_USB_RDY   0
#define offs_RST_CLK_CLOCK_STATUS_PLL_CPU_RDY   1
#define offs_RST_CLK_CLOCK_STATUS_HSE_RDY       2

#define size_RST_CLK_CLOCK_STATUS_PLL_USB_RDY   1
#define size_RST_CLK_CLOCK_STATUS_PLL_CPU_RDY   1
#define size_RST_CLK_CLOCK_STATUS_HSE_RDY       1

#define mask_RST_CLK_CLOCK_STATUS_PLL_USB_RDY   ((unsigned long)0x00000001)
#define mask_RST_CLK_CLOCK_STATUS_PLL_CPU_RDY   ((unsigned long)0x00000002)
#define mask_RST_CLK_CLOCK_STATUS_HSE_RDY       ((unsigned long)0x00000004)


typedef struct {
  unsigned PLL_USB_ON                           : 1;
  unsigned PLL_USB_RLD                          : 1;
  unsigned PLL_CPU_ON                           : 1;
  unsigned PLL_CPU_PLD                          : 1;
  unsigned PLL_USB_MUL                          : 4;
  unsigned PLL_CPU_MUL                          : 4;
  unsigned __dummy0                             : 20;
} _rst_clk_pll_control;

typedef volatile _rst_clk_pll_control _io_rst_clk_pll_control;

#define offs_RST_CLK_PLL_CONTROL_PLL_USB_ON     0
#define offs_RST_CLK_PLL_CONTROL_PLL_USB_RLD    1
#define offs_RST_CLK_PLL_CONTROL_PLL_CPU_ON     2
#define offs_RST_CLK_PLL_CONTROL_PLL_CPU_PLD    3
#define offs_RST_CLK_PLL_CONTROL_PLL_USB_MUL    4
#define offs_RST_CLK_PLL_CONTROL_PLL_CPU_MUL    8

#define size_RST_CLK_PLL_CONTROL_PLL_USB_ON     1
#define size_RST_CLK_PLL_CONTROL_PLL_USB_RLD    1
#define size_RST_CLK_PLL_CONTROL_PLL_CPU_ON     1
#define size_RST_CLK_PLL_CONTROL_PLL_CPU_PLD    1
#define size_RST_CLK_PLL_CONTROL_PLL_USB_MUL    4
#define size_RST_CLK_PLL_CONTROL_PLL_CPU_MUL    4

#define mask_RST_CLK_PLL_CONTROL_PLL_USB_ON     ((unsigned long)0x00000001)
#define mask_RST_CLK_PLL_CONTROL_PLL_USB_RLD    ((unsigned long)0x00000002)
#define mask_RST_CLK_PLL_CONTROL_PLL_CPU_ON     ((unsigned long)0x00000004)
#define mask_RST_CLK_PLL_CONTROL_PLL_CPU_PLD    ((unsigned long)0x00000008)
#define mask_RST_CLK_PLL_CONTROL_PLL_USB_MUL    ((unsigned long)0x000000F0)
#define mask_RST_CLK_PLL_CONTROL_PLL_CPU_MUL    ((unsigned long)0x00000F00)


typedef struct {
  unsigned HSE_ON                               : 1;
  unsigned HSE_BYP                              : 1;
  unsigned __dummy0                             : 30;
} _rst_clk_hs_control;

typedef volatile _rst_clk_hs_control _io_rst_clk_hs_control;

#define offs_RST_CLK_HS_CONTROL_HSE_ON          0
#define offs_RST_CLK_HS_CONTROL_HSE_BYP         1

#define size_RST_CLK_HS_CONTROL_HSE_ON          1
#define size_RST_CLK_HS_CONTROL_HSE_BYP         1

#define mask_RST_CLK_HS_CONTROL_HSE_ON          ((unsigned long)0x00000001)
#define mask_RST_CLK_HS_CONTROL_HSE_BYP         ((unsigned long)0x00000002)


typedef struct {
  unsigned CPU_C1_SEL                           : 2;
  unsigned CPU_C2_SEL                           : 1;
  unsigned __dummy0                             : 1;
  unsigned CPU_C3_SEL                           : 4;
  unsigned HCLK_SEL                             : 2;
  unsigned __dummy1                             : 22;
} _rst_clk_cpu_clock;

typedef volatile _rst_clk_cpu_clock _io_rst_clk_cpu_clock;

#define offs_RST_CLK_CPU_CLOCK_CPU_C1_SEL       0
#define offs_RST_CLK_CPU_CLOCK_CPU_C2_SEL       2
#define offs_RST_CLK_CPU_CLOCK_CPU_C3_SEL       4
#define offs_RST_CLK_CPU_CLOCK_HCLK_SEL         8

#define size_RST_CLK_CPU_CLOCK_CPU_C1_SEL       2
#define size_RST_CLK_CPU_CLOCK_CPU_C2_SEL       1
#define size_RST_CLK_CPU_CLOCK_CPU_C3_SEL       4
#define size_RST_CLK_CPU_CLOCK_HCLK_SEL         2

#define mask_RST_CLK_CPU_CLOCK_CPU_C1_SEL       ((unsigned long)0x00000003)
#define mask_RST_CLK_CPU_CLOCK_CPU_C2_SEL       ((unsigned long)0x00000004)
#define mask_RST_CLK_CPU_CLOCK_CPU_C3_SEL       ((unsigned long)0x000000F0)
#define mask_RST_CLK_CPU_CLOCK_HCLK_SEL         ((unsigned long)0x00000300)


typedef struct {
  unsigned USB_C1_SEL                           : 2;
  unsigned USB_C2_SEL                           : 1;
  unsigned __dummy0                             : 1;
  unsigned CPU_C3_SEL                           : 4;
  unsigned USB_CL_KEN                           : 1;
  unsigned __dummy1                             : 23;
} _rst_clk_usb_clock;

typedef volatile _rst_clk_usb_clock _io_rst_clk_usb_clock;

#define offs_RST_CLK_USB_CLOCK_USB_C1_SEL       0
#define offs_RST_CLK_USB_CLOCK_USB_C2_SEL       2
#define offs_RST_CLK_USB_CLOCK_CPU_C3_SEL       4
#define offs_RST_CLK_USB_CLOCK_USB_CL_KEN       8

#define size_RST_CLK_USB_CLOCK_USB_C1_SEL       2
#define size_RST_CLK_USB_CLOCK_USB_C2_SEL       1
#define size_RST_CLK_USB_CLOCK_CPU_C3_SEL       4
#define size_RST_CLK_USB_CLOCK_USB_CL_KEN       1

#define mask_RST_CLK_USB_CLOCK_USB_C1_SEL       ((unsigned long)0x00000003)
#define mask_RST_CLK_USB_CLOCK_USB_C2_SEL       ((unsigned long)0x00000004)
#define mask_RST_CLK_USB_CLOCK_CPU_C3_SEL       ((unsigned long)0x000000F0)
#define mask_RST_CLK_USB_CLOCK_USB_CL_KEN       ((unsigned long)0x00000100)


typedef struct {
  unsigned ADC_C1_SEL                           : 2;
  unsigned __dummy0                             : 2;
  unsigned ADC_C2_SEL                           : 2;
  unsigned __dummy1                             : 2;
  unsigned ADC_C3_SEL                           : 4;
  unsigned MCO_EN                               : 1;
  unsigned ADC_CLK_EN                           : 1;
  unsigned __dummy2                             : 18;
} _rst_clk_adc_mco_clock;

typedef volatile _rst_clk_adc_mco_clock _io_rst_clk_adc_mco_clock;

#define offs_RST_CLK_ADC_MCO_CLOCK_ADC_C1_SEL   0
#define offs_RST_CLK_ADC_MCO_CLOCK_ADC_C2_SEL   4
#define offs_RST_CLK_ADC_MCO_CLOCK_ADC_C3_SEL   8
#define offs_RST_CLK_ADC_MCO_CLOCK_MCO_EN       12
#define offs_RST_CLK_ADC_MCO_CLOCK_ADC_CLK_EN   13

#define size_RST_CLK_ADC_MCO_CLOCK_ADC_C1_SEL   2
#define size_RST_CLK_ADC_MCO_CLOCK_ADC_C2_SEL   2
#define size_RST_CLK_ADC_MCO_CLOCK_ADC_C3_SEL   4
#define size_RST_CLK_ADC_MCO_CLOCK_MCO_EN       1
#define size_RST_CLK_ADC_MCO_CLOCK_ADC_CLK_EN   1

#define mask_RST_CLK_ADC_MCO_CLOCK_ADC_C1_SEL   ((unsigned long)0x00000003)
#define mask_RST_CLK_ADC_MCO_CLOCK_ADC_C2_SEL   ((unsigned long)0x00000030)
#define mask_RST_CLK_ADC_MCO_CLOCK_ADC_C3_SEL   ((unsigned long)0x00000F00)
#define mask_RST_CLK_ADC_MCO_CLOCK_MCO_EN       ((unsigned long)0x00001000)
#define mask_RST_CLK_ADC_MCO_CLOCK_ADC_CLK_EN   ((unsigned long)0x00002000)


typedef struct {
  unsigned HSE_SEL                              : 4;
  unsigned HSI_SEL                              : 4;
  unsigned HSE_RTC_EN                           : 1;
  unsigned HSI_RTC_EN                           : 1;
  unsigned __dummy0                             : 22;
} _rst_clk_rtc_clock;

typedef volatile _rst_clk_rtc_clock _io_rst_clk_rtc_clock;

#define offs_RST_CLK_RTC_CLOCK_HSE_SEL          0
#define offs_RST_CLK_RTC_CLOCK_HSI_SEL          4
#define offs_RST_CLK_RTC_CLOCK_HSE_RTC_EN       8
#define offs_RST_CLK_RTC_CLOCK_HSI_RTC_EN       9

#define size_RST_CLK_RTC_CLOCK_HSE_SEL          4
#define size_RST_CLK_RTC_CLOCK_HSI_SEL          4
#define size_RST_CLK_RTC_CLOCK_HSE_RTC_EN       1
#define size_RST_CLK_RTC_CLOCK_HSI_RTC_EN       1

#define mask_RST_CLK_RTC_CLOCK_HSE_SEL          ((unsigned long)0x0000000F)
#define mask_RST_CLK_RTC_CLOCK_HSI_SEL          ((unsigned long)0x000000F0)
#define mask_RST_CLK_RTC_CLOCK_HSE_RTC_EN       ((unsigned long)0x00000100)
#define mask_RST_CLK_RTC_CLOCK_HSI_RTC_EN       ((unsigned long)0x00000200)


typedef struct {
  unsigned CAN1_BRG                             : 8;
  unsigned CAN2_BRG                             : 8;
  unsigned __dummy0                             : 8;
  unsigned CAN1_CLK_EN                          : 1;
  unsigned CAN2_CLK_EN                          : 1;
  unsigned __dummy1                             : 6;
} _rst_clk_can_clock;

typedef volatile _rst_clk_can_clock _io_rst_clk_can_clock;

#define offs_RST_CLK_CAN_CLOCK_CAN1_BRG         0
#define offs_RST_CLK_CAN_CLOCK_CAN2_BRG         8
#define offs_RST_CLK_CAN_CLOCK_CAN1_CLK_EN      24
#define offs_RST_CLK_CAN_CLOCK_CAN2_CLK_EN      25

#define size_RST_CLK_CAN_CLOCK_CAN1_BRG         8
#define size_RST_CLK_CAN_CLOCK_CAN2_BRG         8
#define size_RST_CLK_CAN_CLOCK_CAN1_CLK_EN      1
#define size_RST_CLK_CAN_CLOCK_CAN2_CLK_EN      1

#define mask_RST_CLK_CAN_CLOCK_CAN1_BRG         ((unsigned long)0x000000FF)
#define mask_RST_CLK_CAN_CLOCK_CAN2_BRG         ((unsigned long)0x0000FF00)
#define mask_RST_CLK_CAN_CLOCK_CAN1_CLK_EN      ((unsigned long)0x01000000)
#define mask_RST_CLK_CAN_CLOCK_CAN2_CLK_EN      ((unsigned long)0x02000000)


typedef struct {
  unsigned TIM1_BRG                             : 8;
  unsigned TIM2_BRG                             : 8;
  unsigned TIM3_BRG                             : 8;
  unsigned TIM1_CLK_EN                          : 1;
  unsigned TIM2_CLK_EN                          : 1;
  unsigned TIM3_CLK_EN                          : 1;
  unsigned __dummy0                             : 5;
} _rst_clk_tim_clock;

typedef volatile _rst_clk_tim_clock _io_rst_clk_tim_clock;

#define offs_RST_CLK_TIM_CLOCK_TIM1_BRG         0
#define offs_RST_CLK_TIM_CLOCK_TIM2_BRG         8
#define offs_RST_CLK_TIM_CLOCK_TIM3_BRG         16
#define offs_RST_CLK_TIM_CLOCK_TIM1_CLK_EN      24
#define offs_RST_CLK_TIM_CLOCK_TIM2_CLK_EN      25
#define offs_RST_CLK_TIM_CLOCK_TIM3_CLK_EN      26

#define size_RST_CLK_TIM_CLOCK_TIM1_BRG         8
#define size_RST_CLK_TIM_CLOCK_TIM2_BRG         8
#define size_RST_CLK_TIM_CLOCK_TIM3_BRG         8
#define size_RST_CLK_TIM_CLOCK_TIM1_CLK_EN      1
#define size_RST_CLK_TIM_CLOCK_TIM2_CLK_EN      1
#define size_RST_CLK_TIM_CLOCK_TIM3_CLK_EN      1

#define mask_RST_CLK_TIM_CLOCK_TIM1_BRG         ((unsigned long)0x000000FF)
#define mask_RST_CLK_TIM_CLOCK_TIM2_BRG         ((unsigned long)0x0000FF00)
#define mask_RST_CLK_TIM_CLOCK_TIM3_BRG         ((unsigned long)0x00FF0000)
#define mask_RST_CLK_TIM_CLOCK_TIM1_CLK_EN      ((unsigned long)0x01000000)
#define mask_RST_CLK_TIM_CLOCK_TIM2_CLK_EN      ((unsigned long)0x02000000)
#define mask_RST_CLK_TIM_CLOCK_TIM3_CLK_EN      ((unsigned long)0x04000000)


typedef struct {
  unsigned UART1_BRG                            : 8;
  unsigned UART2_BRG                            : 8;
  unsigned __dummy0                             : 8;
  unsigned UART1_CLK_EN                         : 1;
  unsigned UART2_CLK_EN                         : 1;
  unsigned __dummy1                             : 6;
} _rst_clk_uart_clock;

typedef volatile _rst_clk_uart_clock _io_rst_clk_uart_clock;

#define offs_RST_CLK_UART_CLOCK_UART1_BRG       0
#define offs_RST_CLK_UART_CLOCK_UART2_BRG       8
#define offs_RST_CLK_UART_CLOCK_UART1_CLK_EN    24
#define offs_RST_CLK_UART_CLOCK_UART2_CLK_EN    25

#define size_RST_CLK_UART_CLOCK_UART1_BRG       8
#define size_RST_CLK_UART_CLOCK_UART2_BRG       8
#define size_RST_CLK_UART_CLOCK_UART1_CLK_EN    1
#define size_RST_CLK_UART_CLOCK_UART2_CLK_EN    1

#define mask_RST_CLK_UART_CLOCK_UART1_BRG       ((unsigned long)0x000000FF)
#define mask_RST_CLK_UART_CLOCK_UART2_BRG       ((unsigned long)0x0000FF00)
#define mask_RST_CLK_UART_CLOCK_UART1_CLK_EN    ((unsigned long)0x01000000)
#define mask_RST_CLK_UART_CLOCK_UART2_CLK_EN    ((unsigned long)0x02000000)


typedef struct {
  unsigned SSP1_BRG                             : 8;
  unsigned SSP2_BRG                             : 8;
  unsigned __dummy0                             : 8;
  unsigned SSP1_CLK_EN                          : 1;
  unsigned SSP2_CLK_EN                          : 1;
  unsigned __dummy1                             : 6;
} _rst_clk_ssp_clock;

typedef volatile _rst_clk_ssp_clock _io_rst_clk_ssp_clock;

#define offs_RST_CLK_SSP_CLOCK_SSP1_BRG         0
#define offs_RST_CLK_SSP_CLOCK_SSP2_BRG         8
#define offs_RST_CLK_SSP_CLOCK_SSP1_CLK_EN      24
#define offs_RST_CLK_SSP_CLOCK_SSP2_CLK_EN      25

#define size_RST_CLK_SSP_CLOCK_SSP1_BRG         8
#define size_RST_CLK_SSP_CLOCK_SSP2_BRG         8
#define size_RST_CLK_SSP_CLOCK_SSP1_CLK_EN      1
#define size_RST_CLK_SSP_CLOCK_SSP2_CLK_EN      1

#define mask_RST_CLK_SSP_CLOCK_SSP1_BRG         ((unsigned long)0x000000FF)
#define mask_RST_CLK_SSP_CLOCK_SSP2_BRG         ((unsigned long)0x0000FF00)
#define mask_RST_CLK_SSP_CLOCK_SSP1_CLK_EN      ((unsigned long)0x01000000)
#define mask_RST_CLK_SSP_CLOCK_SSP2_CLK_EN      ((unsigned long)0x02000000)


typedef struct {
	__io_reg CLOCK_STATUS;
	__io_reg PLL_CONTROL;
	__io_reg HS_CONTROL;
	__io_reg CPU_CLOCK;
	__io_reg USB_CLOCK;
	__io_reg ADC_MCO_CLOCK;
	__io_reg RTC_CLOCK;
	__io_reg PER_CLOCK;
	__io_reg CAN_CLOCK;
	__io_reg TIM_CLOCK;
	__io_reg UART_CLOCK;
	__io_reg SSP_CLOCK;
} _rst_clk;

#endif /* __1986BE91_RST_CLK_H */
