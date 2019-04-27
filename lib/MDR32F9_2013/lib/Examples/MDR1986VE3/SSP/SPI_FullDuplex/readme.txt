  /**
  @page SPI_FullDuplex_3T SPI_FullDuplex for MDR1986VE3 Complexity Evaluation Board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2013 Milandr ***********************************
  * @file    Examples/MDR1986VE3_EVAL/SSP/SPI_FullDuplex/readme.txt
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    4/07/2013
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

This example provides a description of how to set a communication between SPI2 and SPI4 in full-duplex mode and performs a
transfer from Master to Slave.
Both SPIs are configured with 16bit data frame and a 7Kbit/s communication speed.
The master SPI1 starts the SrcBuf1 transfer while the slave SPI2 transmit SrcBuf2. Once the transfer is
completed a comparison is done and TransferStatus1 and TransferStatus2 gives the data transfer status for each data transfer
direction where it is PASSED if transmitted and received data are the same otherwise it is FAILED.

@par Directory "Examples/MDR1986VE3_EVAL" contains:

  - MDR32F9Qx_config.h            Library Configuration file
  - MDR32F9Qx_board.h             Evaluation board Configuration file
  - SSP/SPI_FullDuplex/main.c     Main program

@par Hardware and Software environment:

  - This example is intended to run on MDR1986VE3 eval board with MDR1986VE3 microcontroller.
  - Connect SSP2 FSS (PC12) pin (XP26.8) to SSP4 FSS (PI11) pin (XP54.13).
  - Connect SSP2 CLK (PC11) pin (XP26.7) to SSP4 CLK (PI12) pin (XP54.14).
  - Connect SSP2 RXD (PC10) pin (XP26.6) to SSP4 TXD (PI13) pin (XP54.15).
  - Connect SSP2 TXD (PC9)  pin (XP26.5) to SSP4 RXD (PI14) pin (XP54.16).

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

 * <h3><center>&copy; COPYRIGHT 2013 Milandr</center></h3>
 */
