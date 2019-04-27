  /**
  @page Joystick_LEDs_3T Joystick_LEDs for MDR1986VE3 Complexity Evaluation Board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2013 Milandr ***********************************
  * @file    Examples/MDR1986VE3/PORT/Joystick_LEDs/readme.txt
  * @author Milandr Application Team
  * @version V1.0.0
  * @date    17/06/2013
  * @brief   Description of the PORT Example.
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

This example shows how to use input/output ports.
PORTG is configured for input. Its 7, 11, 12, 13, 14, 15 pins are connected to the joystick buttons.
PORTB is configured for output. Its 0..5 pins control LED indicators.

@par Directory "Examples/MDR1986VE3" contains:

  - MDR32F9Qx_config.h          Library Configuration file
  - MDR32F9Qx_board.h           Evaluation board Configuration file
  - PORT/Joystick_LEDs/main.c   Main program

@par Hardware and Software environment:

  - This example is intended to run on MDR1986VE3 eval board with MDR1986VE3 microcontroller.
  - "SEL", "UP", "DOWN", "LEFT", "BACK" and "RIGHT" joystick buttons are connected to
    PG.7, PG.11, PG.12, PG.12, PG.13, PG.14, PG.15 pins, respectively.
  - VD5, VD6, VD7, VD8, VD9, and VD10 LEDs are connected to
    PB.0, PB.1, PB.2, PB.3, PB.4 and PB.5 pins, respectively.

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add the required files from "Libraries" folder:
        MDR32F9Qx_port.c
        MDR32F9Qx_rst_clk.c
  - Edit the MDR32F9Qx_config.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2013 Milandr</center></h3>
 */
