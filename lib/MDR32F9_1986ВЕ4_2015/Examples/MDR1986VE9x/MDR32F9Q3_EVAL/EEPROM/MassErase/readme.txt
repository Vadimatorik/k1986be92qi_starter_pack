  /**
  @page Mass_Erase_93 Mass_Erase for MDR32F9Q3 evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2011 Milandr *******************************
  * @file    Examples/MDR32F9Q3_EVAL/EEPROM/MassErase/readme.txt
  * @author  Milandr Application Team
  * @version V3.3.0
  * @date    16.06.2010
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

This example shows how to use EEPROM.
- Erase main and information memory banks
- Blank check main and information memory banks
- Word programm and verification main memory bank
- Word programm and verification information memory bank
- Erase main memory bank only
- Blank check main memory bank
- Verification information memory bank
- Word programm and verification main memory bank
- Erase main and information memory banks
- Blank check main and information memory banks

@par Directory "Examples/MDR32F9Q3_EVAL" contains:

  - MDR32F9Qx_config.h                   Library Configuration file
  - MDR32F9Qx_board.h                    Evaluation board Configuration file
  - EEPROM/MassErase/main.c              Main program

@par Hardware and Software environment:

  - This example is intended to run on MDR32F9Q3 eval board with MDR32F9Q3Y microcontroller.
  - VD2 (LED0), VD3 (LED1) are connected to PF.0, PF.1 pins, respectively.

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add the required files from "Library" folder:
        MDR32F9Qx_port.c
        MDR32F9Qx_rst_clk.c
        MDR32F9Qx_eeprom.c
  - Edit the MDR32F9Qx_conf.h to set appropriate run-time parameter checking level.
  - To allocate all code in RAM edit appropriate linker options.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2011 Milandr</center></h3>
 */
