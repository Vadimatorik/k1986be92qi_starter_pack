  /**
  @page ARINC_1T ARINC for MDR1986VE1T Opora Evaluation Board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2013 Milandr ***********************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    13/09/2013
  * @brief   Description of the ARINC Example.
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

This example provides a description of how to set a communication with the ARINC.
The ARINC transmitter send the data array and the ARINC receiver take the data
in the interrupt on presence of of data in the FIFO.
The received frame is checked and LED1 light up to indicate what the 
communication was successful, else LED2 light up.

@par Directory "Examples/MDR1986VE1T/ARINC" contains:
  - ARINC/src/main.c                Main program
  - ARINC/src/MDR1986VE1T_IT.c      Main Interrupt Service Routines
  - ARINC/inc/MDR1986VE1T_IT.h      Functions prototypes for the interrupt

@par Hardware and Software environment:

  - This example is intended to run on MDR1986VE1T eval board with 
  	MDR1986VE1T microcontroller.
  - Pin PB0 must be connected to pin PD13.
  - Pin PB1 must be connected to pin PD14.
  - VD6 jamper must be enable.
  - VD7 jamper must be enable.

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add the required files from "Libraries" folder:
        MDR32F9Qx_port.c
        MDR32F9Qx_rst_clk.c
	    MDR32F9Qx_arinc429r.c
	    MDR32F9Qx_arinc429t.c
	    MDR32F9Qx_uart.c
  - Edit the MDR32F9Qx_config.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2013 Milandr</center></h3>
 */
