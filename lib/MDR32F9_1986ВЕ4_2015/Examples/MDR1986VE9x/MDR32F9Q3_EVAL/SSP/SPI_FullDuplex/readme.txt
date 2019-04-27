  /**
  @page SPI_FullDuplex_93 SPI_FullDuplex for MDR32F9Q3 evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2011 Milandr ***********************************
  * @file    Examples/MDR32F9Q3_EVAL/SSP/SPI_FullDuplex/readme.txt
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    4/07/2011
  * @brief   Description of the SSP Example.
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

This example shows how to use SSP.
SSP configured to transfer data to itself for testing operability of the peripheral block SSP.
Configure PORTF lines 0,1,2,3 as SSP1TXD, SSP1CLK, SSP1FSS, SSP1RXD.
Configure SSP on an exchange with 16bit data frame, SPI transfer protocol and 7Kbit/s communication speed.
SSP1 transmit word on line SSP_TX and recive on line SSP_RX.
Once the transfer is completed a comparison is done and TransferStatus gives the data transfer status where it is PASSED if transmitted and received data are the same otherwise it is FAILED.

@par Directory "Examples/MDR32F9Q3_EVAL" contains:

  - MDR32F9Qx_config.h                Library Configuration file
  - MDR32F9Qx_board.h                 Evaluation board Configuration file
  - SSP/SPI_FullDuplex/main.c         Main program

@par Hardware and Software environment:

  - This example is intended to run on MDR32F9Q3 eval board with MDR32F9Q3 microcontroller.
  - Connect SSP1 TXD pin (X25.1.19) to SSP1 RXD pin (X25.1.22).

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add the required files from "Libraries" folder:
        MDR32F9Qx_port.c
        MDR32F9Qx_rst_clk.c
	      MDR32F9Qx_ssp.c
  - Edit the MDR32F9Qx_config.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2011 Milandr</center></h3>
 */
