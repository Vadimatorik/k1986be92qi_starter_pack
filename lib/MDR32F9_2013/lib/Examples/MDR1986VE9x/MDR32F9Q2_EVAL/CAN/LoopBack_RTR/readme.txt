  /**
  @page CAN_LoopBack_RTR_92 CAN_LoopBack_RTR for MDR32F9Q2 evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2011 Milandr ***********************************
  * @file    Examples/MDR32F9Q2_EVAL/CAN/LoopBack_RTR/readme.txt
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    12/09/2011
  * @brief   Description of the CAN Example.
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

This example provides a description of how to set a communication with the CAN in loopback mode.
The CAN cell performs a transmission of a Remote Transmit Request at 500 Kbits/s. Reception remote frame is done in the interrupt handler. The received frame is checked and LED1 light up to indicate what the communication was successful, else LED2 light up.

@par Directory "Examples/MDR32F9Q2_EVAL" contains:

  - MDR32F9Qx_config.h                                Library Configuration file
  - MDR32F9Qx_board.h                                 Evaluation board Configuration file
  - CAN/LoopBack_RTR/main.c                           Main program
  - CAN/LoopBack_RTR/MDR32F9Qx_it.c                   Main Interrupt Service Routines
  - CAN/LoopBack_RTR/MDR32F9Qx_it.h                   Functions prototypes for the interrupt

@par Hardware and Software environment:

  - This example is intended to run on MDR32F9Q2 eval board with MDR32F9Q2 microcontroller.

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add the required files from "Libraries" folder:
        MDR32F9Qx_port.c
        MDR32F9Qx_rst_clk.c
	      MDR32F9Qx_can.c
  - Edit the MDR32F9Qx_config.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2011 Milandr</center></h3>
 */
