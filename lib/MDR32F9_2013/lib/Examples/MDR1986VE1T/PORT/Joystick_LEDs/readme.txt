  /**
  @page Joystick_LEDs_1T Joystick_LEDs for MDR1986VE1T Opora Evaluation Board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2013 Milandr ***********************************
  * @file    Examples/MDR1986VE1T/PORT/Joystick_LEDs/readme.txt
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
PORTC is configured for input. Its 10..14 pins are connected to the joystick buttons.
PORTD is configured for output. Its 10..14 pins control LED indicators.

@par Directory "Examples/MDR1986VE1T" contains:

  - MDR32F9Qx_config.h          Library Configuration file
  - MDR32F9Qx_board.h           Evaluation board Configuration file
  - PORT/Joystick_LEDs/main.c   Main program

@par Hardware and Software environment:

  - This example is intended to run on MDR1986VE1T eval board with MDR1986VE1T microcontroller.
  - "SEL", "UP", "DOWN", "LEFT", "BACK" and "RIGHT" joystick buttons are connected to
    PE.5, PC.8, PE.9, PE.10, PE.22 and PE.15 pins, respectively.
  - VD6, VD7, VD8, VD9, VD10, and VD11 LEDs are connected to
    PD.7, PD.8, PD.9, PD.10, PD.11 and PD.12 pins, respectively.

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
