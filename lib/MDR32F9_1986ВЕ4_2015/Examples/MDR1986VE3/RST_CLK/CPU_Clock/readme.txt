  /**
  @page CPU_Clock_3T CPU_Clock for MDR1986VE3 Complexity Evaluation Board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2013 Milandr ***********************************
  * @file    Examples/MDR1986VE3_EVAL/RST_CLK/CPU_Clock/readme.txt
  * @author Milandr Application Team
  * @version V1.0.0
  * @date    4/07/2013
  * @brief   Description of the RST_CLK Example.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
  @endverbatim
  @endlatexonly
@par Example Description

This example shows how to use RST_CLK module functions to choose particular
CPU_CLK frequency. That action includes the following steps:
- RST_CLK module deinitialization;
- RST_CLK module initialization;
- - enable PORTB clock;
- - enable BKP clock;
- RST_CLK module initialization;
- Set CPU_CLK = HSI clock and blink with LED1 using this clock;
- Set CPU_CLK = HSI/2 clock and blink with LED1 using this clock;
- Set CPU_CLK = 7*HSE/2 clock and blink with LED1 using this clock;
- Set CPU_CLK = LSI clock and blink with LED1 using this clock;

LED1 is used for frequency indication;
LED2 - for new frequensy setting up indication;
LED3 - for frequensy setting error.

@par Directory "Examples/MDR1986VE3_EVAL" contains:

  - MDR32F9Qx_config.h                 Library Configuration file
  - MDR32F9Qx_board.h                  Evaluation board Configuration file
  - RST_CLK/CPU_Clock/main.c           Main program

@par Hardware and Software environment:

  - This example is intended to run on MDR1986VE3 eval board with MDR1986VE3 microcontroller.
  - VD5 (LED0), VD6 (LED1), VD7 (LED0) are connected to
    PB.0, PB.1, PB.2 pins, respectively.

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add the required files from "Libraries" folder:
        MDR32F9Qx_port.c
        MDR32F9Qx_rst_clk.c
  - Edit the MDR32F9Qx_config.h to set appropriate run-time parameter checking level.
  - Edit the main.c to set appropriate LEDs blink count and rate.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2013 Milandr</center></h3>
 */
