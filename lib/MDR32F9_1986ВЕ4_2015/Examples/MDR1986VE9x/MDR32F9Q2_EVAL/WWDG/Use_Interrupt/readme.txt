  /**
  @page WWDG_Use_Interrupt_92 WWDG_Use_Interrupt for MDR32F9Q2 evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2011 Milandr ***********************************
  * @file    Examples/MDR32F9Q2_EVAL/WWDG/Use_Interrupt/readme.txt
  * @author Milandr Application Team
  * @version V1.0.0
  * @date    4/07/2011
  * @brief   Description of the WWDG Example.
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

This example shows how to use WWDG module functions.
That action includes the following steps:
  - WWDG module initialization;
  - Enable interrupt for WWDG;
  - Get interrupts status;
  - Clear interrupt pending bit;
  - EWI flag clearing;
  - Counter value setting.

LED1 is used to indicate the EWI flag state.

@par Directory "Examples/MDR32F9Q2_EVAL" contains:

  - MDR32F9Qx_config.h                  Library Configuration file
  - MDR32F9Qx_board.h                   Evaluation board Configuration file
  - WWDG/Use_Interrupt/main.c           Main program
  - WWDG/Use_Interrupt/MDR32F9Qx_it.c   Main Interrupt Service Routines
  - WWDG/Use_Interrupt/MDR32F9Qx_it.h   Functions prototypes for the interrupt

@par Hardware and Software environment:

  - This example is intended to run on MDR32F9Q2 eval board with MDR32F9Q2 microcontroller.
  - VD3 (LED1) are connected to PC.0 pin.

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add MDR32F9Qx_it.c and MDR32F9Qx_it.h files.
  - Add the required files from "Libraries" folder:
        MDR32F9Qx_port.c
        MDR32F9Qx_rst_clk.c
        MDR32F9Qx_wwdg.c
  - Edit the MDR32F9Qx_config.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2011 Milandr</center></h3>
 */
