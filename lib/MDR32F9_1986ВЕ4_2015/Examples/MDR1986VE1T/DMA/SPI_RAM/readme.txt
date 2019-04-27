  /**
  @page SPI_RAM_1T SPI_RAM for MDR1986VE1T Opora Evaluation Board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2013 Milandr ***********************************
  * @file    Examples/MDR1986VE1T/DMA/SPI_RAM/readme.txt
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    4/07/2013
  * @brief   Description of the DMA SPI Example.
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

@par Directory "Examples/MDR1986VE1T" contains:

  - MDR32F9Qx_config.h            Library Configuration file
  - MDR32F9Qx_board.h             Evaluation board Configuration file
  - DMA/SPI_RAM/main.c            Main program

@par Hardware and Software environment:

  - This example is intended to run on MDR1986VE1T eval board with MDR1986VE1T microcontroller.
  - Connect SSP1 FSS (PC8) pin (XP6.24) to SSP2 FSS (PD10) pin (XP16.8).
  - Connect SSP1 CLK (PC7) pin (XP6.12) to SSP2 CLK (PD9)  pin (XP16.6).
  - Connect SSP1 RXD (PC6) pin (XP6.5)  to SSP2 RXD (PD8)  pin (XP16.4).
  - Connect SSP1 TXD (PC5) pin (XP6.8)  to SSP2 TXD (PD7)  pin (XP16.2).

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

 * <h3><center>&copy; COPYRIGHT 2013 Milandr</center></h3>
 */
