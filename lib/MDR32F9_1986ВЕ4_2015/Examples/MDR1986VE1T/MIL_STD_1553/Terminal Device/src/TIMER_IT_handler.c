/**
  ******************************************************************************
  * @file	 TIMER_IT_handler.c
  * @author	 sidorov.a
  * @version {version}
  * @date    05.04.2013
  * @brief   This file contains user interrupt handler for the TIMER1.
  ******************************************************************************
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2013 Milandr </center></h2>
  ******************************************************************************
  * FILE TIMER_IT_handler.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_config.h"
#include "TIMER_IT_handler.h"
#include "MDR32F9Qx_timer.h"
#include "MDR32F9Qx_mil_std_1553.h"
#include "MIL_STD_1553_IT_handler.h"

#define ASSERT_INFO_FILE_ID FILEID__TIMER_IT_handler_C

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR1986VE1T_EVAL MDR1986VE1T Opora Evaluation Board
  * @{
  */

/** @addtogroup MIL_STD_1553_Terminal_Device_IT MIL_STD_1553 Terminal Device
 *  @{
 */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
uint32_t MIl_STD_1553CommandWord2;

/* External variables --------------------------------------------------------*/
extern uint32_t MIL_STD_1553_MSG;
extern uint32_t CircularReturnDataFlag;
extern uint32_t ReceivedNewControlWordflag;
extern uint32_t MIL_STD_1553_LastCommandWord;
/* Private function prototypes -----------------------------------------------*/


/**
  * @brief	The user interrupt handler from the TIMER1.
  * @param	TIMERx: Select the TIMER peripheral.
  * 		This parameter can be  one of the followinf values:
  * 		MDR_TIMER1, MDR_TIMER2, MDR_TIMER3, MDR_TIMER4.
  * @param 	MIL_STD_1553x: Slect the MIL_STD_1553 peripheral.
  *         This parameter can be one of the following values:
  *         MIL_STD_15531, MIL_STD_15532.
  * @retval None
  */
void My_TIMER1_IRQ_Handler(MDR_TIMER_TypeDef * TIMERx, MDR_MIL_STD_1553_TypeDef * MIL_STD_1553x)
{
	uint32_t MIL_STD_1553_Status;
	MIL_STD_1553_StatusWordTypeDef MIL_STD_1553StatusWord1 = {0};
	MIL_STD_1553_CommandWordTypeDef MIL_STD_1553_CommandWord1 = {0};

	/* Disable TIMER1 and reset IT_flag */
	TIMER_ITConfig(TIMERx, TIMER_STATUS_CNT_ARR, DISABLE);
	TIMER_Cmd(TIMERx, DISABLE);
	TIMER_ClearFlag(TIMERx, TIMER_STATUS_CNT_ARR);
	TIMER_SetCounter(TIMERx, 0);


	MIL_STD_1553_Status= MIL_STD_1553_GetStatus(MIL_STD_1553x);

	MIL_STD_1553StatusWord1.Fields.TerminalDeviceAddress = MIL_STD_1553_TERMINAL_ADDRESS;
	MIL_STD_1553_CommandWord1.CommandWord = MIL_STD_1553_GetCommandWord(MIL_STD_1553x, MIL_STD_1553_COMMAND_WORD1);

	switch (MIL_STD_1553_MSG){
			case 0x0001:
			if((MIL_STD_1553_Status & MIL_STD_1553_STATUS_ERR) != 0){
				ErrorState(MIL_STD_1553x, MIL_STD_1553_MSG);
				return;
			}
			if(MIL_STD_1553_GetMSG(MIL_STD_1553x) == 0x0004){
				/* Have group komanada terminal device -> terminal devic */
				MIL_STD_1553_MSG = MIL_STD_1553_GetMSG(MIL_STD_1553x);
				MIl_STD_1553CommandWord2 = MIL_STD_1553_GetCommandWord(MIL_STD_1553x, MIL_STD_1553_COMMAND_WORD2);
			}
			else{
				/* Data exchange: Bus controller -> terminal device, no group */
				if(MIL_STD_1553_CommandWord1.Fields.Subaddress == 0x1E){
					CircularReturnDataFlag = 1;
				}
			}
			break;
			case 0x0080:
				if((MIL_STD_1553_Status & MIL_STD_1553_STATUS_ERR) != 0){
					ErrorState(MIL_STD_1553x, MIL_STD_1553_MSG);
					return;
				}
				MIL_STD_1553StatusWord1.Fields.GroupCommandBit = 1;

				if(MIL_STD_1553_GetMSG(MIL_STD_1553x) == 0x0004){
					/* Have not group komanada terminal device -> terminal devic */
					MIL_STD_1553_MSG = MIL_STD_1553_GetMSG(MIL_STD_1553x);
					MIl_STD_1553CommandWord2 = MIL_STD_1553_GetCommandWord(MIL_STD_1553x, MIL_STD_1553_COMMAND_WORD2);
				}
				else{
					/* Have group komanada terminal device -> terminal devic */
					if(MIL_STD_1553_CommandWord1.Fields.Subaddress == 0x1E){
						CircularReturnDataFlag = 1;
					}
				}
			break;
		}

		MIL_STD_1553_SetStatusWord(MIL_STD_1553x, MIL_STD_1553_STATUS_WORD1, &MIL_STD_1553StatusWord1);

		MIL_STD_1553_LastCommandWord = MIL_STD_1553_CommandWord1.CommandWord;
		ReceivedNewControlWordflag = 1;
}

/** @} */ /* End of group MIL_STD_1553_Terminal_Device */

/** @} */ /* End of group ____MDR1986VE1T_EVAL MDR1986VE1T Opora Evaluation Board */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2013 Milandr ********************************
*
* END OF FILE TIMER_IT_handler.c */
