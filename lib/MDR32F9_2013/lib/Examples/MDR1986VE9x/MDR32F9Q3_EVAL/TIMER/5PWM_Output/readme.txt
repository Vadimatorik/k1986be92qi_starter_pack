  /**
  @page TIMER_5PWM_Output_93 TIMER_5PWM_Output for MDR32F9Q3 evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2011 Milandr ***********************************
  * @file    Examples/MDR32F9Q3_EVAL/TIMER/5PWM_Output/readme.txt
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    4/07/2011
  * @brief   Description of the TIMER Example.
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

This example shows how to configure the TIM1 peripheral to generate 5 PWM signals with 3 different duty cycles.
TIM1CLK is fixed to 4 MHz, the TIM1 Prescaler is equal to 0 so the TIM1 counter clock used is 4 MHz.

TIM1 frequency is defined as follow: TIM1 frequency = TIM1CLK/(TIM1_Period + 1) = 1.95 KHz

The TIM1 CCR1 register value is equal to 0x7FF, so the TIM1 Channel 1 and TIM1 Channel 1N generate a PWM signal with a frequency equal to 1.95 KHz KHz and a duty cycle equal to: TIM1 Channel1 duty cycle = TIM1_CCR1 /( TIM1_Period + 1) = 50%.

The TIM1 CCR2 register value is equal to 0x3FF, so the TIM1 Channel 2 and TIM1 Channel 2N generate a PWM signal with a frequency equal to 1.95 KHz KHz and a duty cycle equal to: TIM1 Channel2 duty cycle = TIM1_CCR2 / ( TIM1_Period + 1) = 25%.

The TIM1 CCR3 register value is equal to 0x1FF, so the TIM1 Channel 3 generate a PWM signal with a frequency equal to 1.95 KHz KHz and a duty cycle equal to: TIM1 Channel3 duty cycle = TIM1_CCR3 / ( TIM1_Period + 1) = 12.5%.

The TIM1 waveform can be displayed using an oscilloscope.

@par Directory "Examples/MDR32F9Q3_EVAL" contains:

  - MDR32F9Qx_config.h                       Library Configuration file
  - MDR32F9Qx_board.h                        Evaluation board Configuration file
  - TIMER/5PWM_Output/main.c                 Main program

@par Hardware and Software environment:

  - This example is intended to run on MDR32F9Q3 eval board with MDR32F9Q3 microcontroller.

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add the required files from "Libraries" folder:
        MDR32F9Qx_port.c
        MDR32F9Qx_rst_clk.c
	      MDR32F9Qx_timer.c
  - Edit the MDR32F9Qx_config.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2011 Milandr</center></h3>
 */
