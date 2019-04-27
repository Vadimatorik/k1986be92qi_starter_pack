  /**
  @page UART_WordSend_93 UART_WordSend for MDR32F9Q3 evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2011 Milandr ***********************************
  * @file    Examples/MDR32F9Q3_EVAL/UART/UART_WordSend/readme.txt
  * @author Milandr Application Team
  * @version V1.0.0
  * @date    4/07/2011
  * @brief   Description of the UART Example.
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

This example shows how to use UART.
Configure PORTB lines 5,6 as UART1_TX,UART1_RX.
Configure PORTD lines 0,1 as UART2_RX,UART2_TX.
Configure UARTs on an exchange with 9600 Baud rate, 8 bit data size, 2 stop-bit and parity Even check.
Check TXFE flag before transmit.
UART2 transmit word.
Check RXFF flag before recive.
UART1 recive word.

@par Directory "Examples" contains:

  - MDR32F9Qx_config.h                         Library Configuration file
  - MDR32F9Qx_board.h                          Evaluation board Configuration file
  - UART/UART_WordSend/main.c                  Main program

@par Hardware and Software environment:

  - This example is intended to run on MDR32F9Q3 eval board with MDR32F9Q3T1 microcontroller.
  - Pin 19 of X24.1 and Pin 6 X24.2 must be connected together.

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add the required files from "Library" folder:
        MDR32F9Qx_port.c
        MDR32F9Qx_rst_clk.c
	      MDR32F9Qx_uart.c
  - Edit the MDR32F9Qx_conf.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2011 Milandr</center></h3>
 */
