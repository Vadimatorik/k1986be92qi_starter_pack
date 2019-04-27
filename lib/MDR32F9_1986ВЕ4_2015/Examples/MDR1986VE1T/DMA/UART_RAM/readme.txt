  /**
  @page UART_RAM_1T UART_RAM for MDR1986VE1T Opora Evaluation Board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2013 Milandr ***********************************
  * @file    Examples/MDR1986VE1T/DMA/UART_RAM/readme.txt
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    4/07/2013
  * @brief   Description of the DMA UART Example.
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

  This example provides a basic communication between UART1 and UART2 using DMA capability.
  First, the DMA transfers data from SrcBuf1 buffer to UART1 Transmit data register,
  then this data is sent to UART2.
  Data received by USART2 is transferred by DMA and stored in DstBuf2 then compared with
  the send ones and the result of this comparison is stored in the "TransferStatus2" variable.

  In the same time, the DMA transfers data from SrcBuf2 buffer to UART2 Transmit data register,
  then this data is sent to UART1. Data received by UART1 is transferred by DMA and stored in
  DstBuf1 then compared with the send ones and the result of this comparison is stored in the
  "TransferStatus1" variable.

  UART1 and UART2 configured as follow:

  - BaudRate = 1200 baud
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - FIFO enable
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled


@par Directory "Examples/MDR1986VE1T" contains:

  - MDR32F9Qx_config.h            Library Configuration file
  - MDR32F9Qx_board.h             Evaluation board Configuration file
  - DMA/UART_RAM/main.c           Main program

@par Hardware and Software environment:

  - This example is intended to run on MDR1986VE1T eval board with MDR1986VE1T microcontroller.
  - Connect UART1 RXD (PC4) pin (XP19.1) to UART2 TXD (PD14) pin (XP19.6).
  - Connect UART1 TXD (PC3) pin (XP19.4) to UART2 RXD (PD13) pin (XP19.3).

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add the required files from "Libraries" folder:
        MDR32F9Qx_port.c
        MDR32F9Qx_rst_clk.c
      	MDR32F9Qx_uart.c
	      MDR32F9Qx_dma.c
  - Edit the MDR32F9Qx_config.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2013 Milandr</center></h3>
 */
