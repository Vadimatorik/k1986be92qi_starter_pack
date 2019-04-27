  /**
  @page ADC_ADC1_IT  ADC_ADC1_IT for MDR1986VE1T Opora Evaluation Board.
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2013 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    13/06/2013
  * @brief   Description of the ADC Example.
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

This example describes how to use the ADC1 to transfer continuously converted 
data from ADC1 to memory. The ADC1 is configured to converts continuously 
ADC channel31 - Temperature Sensor. Each time an end of conversion occurs the IT, 
the converted data from ADC1 RESULT register to the ADC_ConvertedValue[10] 
array of variables.

@par Directory "Examples/MDR1986VE1T/ADC/ADC_IT" contains:

  - ADC/ADC1_DMA/main.c              Main program
  - ADC/ADC1_IT/MDR1986VE1T_IT.c     Main Interrupt Service Routines
  - ADC/ADC1_IT/MDR1986VE1T_IT.h     Functions prototypes for the interrupt

@par Hardware and Software environment:

  - This example is intended to run on MDR1986VE1T eval board with MDR1986VE1T 
  microcontroller.

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add MDR1986VE1T_IT.c and MDR1986VE1T_IT.h files.
  - Add the required files from "Libraries" folder:
        MDR32F9Qx_port.c
        MDR32F9Qx_rst_clk.c
	    MDR32F9Qx_adc.c
	    MDR32F9Qx_uart.h
	    MDR32F9Qx_eeprom.h
	    MDR32F9Qx_rst_clk.h
	    MDR32F9Qx_config.h
	      
  - Edit the MDR32F9Qx_config.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2013 Milandr</center></h3>
 */
