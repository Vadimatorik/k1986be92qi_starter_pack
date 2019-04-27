  /**
  @page Ethernet_1T  for MDR1986VE1T Opora Evaluation Board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2013 Milandr ***********************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    13/09/2013
  * @brief   Description of the Ethernet Example.
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

This example contain:
  - the example of ICMP echo server.
  - the example of TELNET echo server.

@par Directory "Examples/MDR1986VE1T/Ethernet" contains:
  - Ethernet/src/main.c                Main program.
  - Ethernet/src/MDR1986VE1T_IT.c      Main Interrupt Service Routines.
  - Ethernet/src/tcpip.c			   Functions for processing ethernet frames.
  - Ethernet/inc/MDR1986VE1T_IT.h      Functions prototypes for the interrupt.
  - Ethernet/inc/tcpip.h			   Functions prototypes Functions prototypes for the interrupt.

@par Hardware and Software environment:

  - This example is intended to run on MDR1986VE1T eval board with 
  	MDR1986VE1T microcontroller.

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add the required files from "Libraries" folder:
        MDR32F9Qx_port.c
        MDR32F9Qx_rst_clk.c
	    MDR32F9Qx_eth.c
	    MDR32F9Qx_timer.c
	    MDR32F9Qx_eeprom.c
	    MDR32F9Qx_uart.c
  - Edit the MDR32F9Qx_config.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2013 Milandr</center></h3>
 */
