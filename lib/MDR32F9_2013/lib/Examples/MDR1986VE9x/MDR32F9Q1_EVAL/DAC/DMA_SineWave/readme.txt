  /**
  @page DAC_DMA_SineWave_91  DAC_DMA_SineWave for MDR32F9Q1 evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2011 Milandr ***********************************
  * @file    Examples/MDR32F9Q1_EVAL/DAC/DMA_SineWave/readme.txt
  * @author Milandr Application Team
  * @version V1.0.0
  * @date    12/09/2011
  * @brief   Description of the DAC Example.
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

This example describes how to use DAC with DMA to generate sine waves on DAC channel output.
Configure PORTE line 9 as DAC1_OUT .
DMA channel10 is configured to transfer ping-pong mode, word by word, a 32-word buffer to DAC register DAC1_DATA.
The transfered 32 buffer is made to have a sine wave generation on DAC channel output. DAC channel1 is enabled.
Once TIM1 is enabled, each TIM1 CNT_ARR_EVENT generate a DMA request which transfer data to the  DAC DATA register and DAC conversion is started. The sine waves can be visualized by connecting DAC_OUT jack to an oscilloscope.

@par Directory "Examples/MDR32F9Q1_EVAL" contains:

  - MDR32F9Qx_config.h                              Library Configuration file
  - MDR32F9Qx_board.h                               Evaluation board Configuration file
  - DAC/DMA_SineWave/main.c                         Main program
  - DAC/DMA_SineWave/MDR32F9Qx_it.c                 Main Interrupt Service Routines
  - DAC/DMA_SineWave/MDR32F9Qx_it.h                 Functions prototypes for the interrupt

@par Hardware and Software environment:

  - This example is intended to run on MDR32F9Q1 eval board with MDR32F9Q1 microcontroller.
  -  DAC_OUT_SEL jamper must be switched into a state EXT_CON.

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add MDR32F9Qx_it.c and MDR32F9Qx_it.h files.
  - Add the required files from "Libraries" folder:
        MDR32F9Qx_port.c
        MDR32F9Qx_rst_clk.c
	      MDR32F9Qx_dac.c
	      MDR32F9Qx_timer.c
	      MDR32F9Qx_dma.c
  - Edit the MDR32F9Qx_config.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2011 Milandr</center></h3>
 */
