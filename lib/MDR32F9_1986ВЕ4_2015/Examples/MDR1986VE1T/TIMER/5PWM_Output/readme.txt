  /**
  @page TIMER_5PWM_Output_1T TIMER_5PWM_Output for MDR1986VE1T Opora Evaluation Board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2013 Milandr ***********************************
  * @file    Examples/MDR1986VE1T_EVAL/TIMER/5PWM_Output/readme.txt
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    4/07/2013
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

  This example shows how to configure the TIM4 peripheral to generate 5 PWM signals with 3 different duty cycles.
  TIM4CLK is fixed to 4 MHz, the TIM4 Prescaler is equal to 0 so the TIM4 counter clock used is 4 MHz.

  TIM4 frequency is defined as follow: TIM4 frequency = TIM4CLK/(TIM4_Period + 1) = 1.95 KHz

  The TIM4 CCR1 register value is equal to 0x7FF, so the TIM4 Channel 1 and TIM4 Channel 1N generate a PWM signal with a frequency equal to 1.95 KHz KHz and a duty cycle equal to: TIM4 Channel1 duty cycle = TIM4_CCR1 /( TIM4_Period + 1) = 50%.

  The TIM4 CCR2 register value is equal to 0x3FF, so the TIM4 Channel 2 and TIM4 Channel 2N generate a PWM signal with a frequency equal to 1.95 KHz KHz and a duty cycle equal to: TIM4 Channel2 duty cycle = TIM4_CCR2 / ( TIM4_Period + 1) = 25%.

  The TIM4 CCR3 register value is equal to 0x1FF, so the TIM4 Channel 3 generate a PWM signal with a frequency equal to 1.95 KHz KHz and a duty cycle equal to: TIM4 Channel3 duty cycle = TIM4_CCR3 / ( TIM4_Period + 1) = 12.5%.

  The TIM4 waveform can be displayed using an oscilloscope.

@par Directory "Examples/MDR1986VE1T_EVAL" contains:

  - MDR32F9Qx_config.h                       Library Configuration file
  - MDR32F9Qx_board.h                        Evaluation board Configuration file
  - TIMER/5PWM_Output/main.c                 Main program

@par Hardware and Software environment:

  - This example is intended to run on MDR1986VE1T eval board with MDR1986VE1T microcontroller;
  - Set the jumper PA6 in position TIM4_CH1;
  - Set the jumper PA7 in position TIM4_CH1N;
  - Set the jumper PA8 in position TIM4_CH2;
  - Set the jumper PA9 in position TIM4_CH2N;
  - Set the jumper PA10 in position TIM4_CH3.
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

 * <h3><center>&copy; COPYRIGHT 2013 Milandr</center></h3>
 */
