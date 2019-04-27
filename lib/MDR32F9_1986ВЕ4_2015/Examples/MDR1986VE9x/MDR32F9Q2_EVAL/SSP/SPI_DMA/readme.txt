  /**
  @page SPI_DMA_92 SPI_DMA for MDR32F9Q2 evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2011 Milandr ***********************************
  * @file    Examples/MDR32F9Q2_EVAL/SSP/SPI_DMA/readme.txt
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

This example provides a description of how to use four DMA channels to transfer a data
buffer from memory to SPI_SLAVE(SSP2) through SPI_MASTER(SSP1) and a second data buffer
from memory to SPI_MASTER through SPI_SLAVE in full-duplex mode.
For each SSP DMA Tx/Rx requests are enabled.
In this example both transmission and reception are managed through DMA and the received
data are stored into buffers declared in the SRAM. The DMA channels involved in this
transfer depend on the used SPIs.
A polling on all Transfer complete flags are done for all used DMA channels to check the
end of all DMA channels transfers.
The transmitted and received buffers are compared to check that all data have been correctly
transferred.

@par Directory "Examples/MDR32F9Q2_EVAL" contains:

  - MDR32F9Qx_config.h            Library Configuration file
  - MDR32F9Qx_board.h             Evaluation board Configuration file
  - SSP/SPI_DMA/main.c            Main program

@par Hardware and Software environment:

  - This example is intended to run on MDR32F9Q2 eval board with MDR32F9Q2 microcontroller.
  - Connect SSP1 FSS pin (X26.1. 8) to SSP2 FSS pin (X27.1.21).
  - Connect SSP1 CLK pin (X26.1.10) to SSP2 CLK pin (X27.1.20).
  - Connect SSP1 RXD pin (X26.1. 7) to SSP2 TXD pin (X27.1.19).
  - Connect SSP1 TXD pin (X26.1.11) to SSP2 RXD pin (X27.1.22).

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add the required files from "Libraries" folder:
        MDR32F9Qx_port.c
        MDR32F9Qx_rst_clk.c
	      MDR32F9Qx_ssp.c
	      MDR32F9Qx_dma.c
  - Edit the MDR32F9Qx_config.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2011 Milandr</center></h3>
 */
