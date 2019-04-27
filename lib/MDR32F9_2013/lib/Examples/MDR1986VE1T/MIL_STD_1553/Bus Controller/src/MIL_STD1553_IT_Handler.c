/**
  ******************************************************************************
  * @file	 MIL_STD_1553_IT_Handler.c
  * @author	 sidorov.a
  * @version {version}
  * @date    03.04.2013
  * @brief   This file contains user interrupt handler for the MIL_STD_15531.
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
  * FILE MIL_STD1553_IT_Handler.c
  */

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "MDR32F9Qx_config.h"
#include "MIL_STD_1553_IT_Handler.h"
#include "MDR1986VE1T_IT.h"
#include "MDR1986VE1T.h"
#include "MDR32F9Qx_mil_std_1553.h"
#include "MDR32F9Qx_port.h"
#include "MIL_STD_1553_BusController.h"

#define ASSERT_INFO_FILE_ID FILEID__MIL_STD_1553_IT_Handler_C

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR1986VE1T_EVAL MDR1986VE1T Opora Evaluation Board
  * @{
  */

/** @addtogroup MIL_STD_1553_Bus_Controller_1T MIL_STD_1553 Bus Controller
 *  @{
 */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
uint32_t MIL_STD_1553_Data[32];
extern uint32_t MIL_STD_1553_LastRequest;
extern MIL_STD_1553_CommandWordTypeDef CommandWord;

/* Private function prototypes -----------------------------------------------*/
#if defined (_USE_DEBUG_UART_)
	#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
	#define DEBUG_PRINTF(...)
#endif /* #if defined _USE_DEBUG_UART_ */


//// TODO Добавить описание функции
/**
  * @brief
  * @param	MIL_STD_1553x: Slect the MIL_STD_1553 peripheral.
  *         This parameter can be one of the following values:
  *         MIL_STD_15531, MIL_STD_15532.
  * @retval	None
  */
void My_MIL_STD_1553_Handler( MDR_MIL_STD_1553_TypeDef * MIL_STD_1553x )
{

	uint32_t MIL_STD_1553_Status;
	uint32_t MIL_STD_1553_Errors;
	uint32_t i = 0;
	uint32_t NunberDataWord = 0;

	/* Get the Status register */
	MIL_STD_1553_Status = MIL_STD_1553_GetStatus(MIL_STD_1553x);
	/* Get the Errors register */
	MIL_STD_1553_Errors = MIL_STD_1553_GetErrorStatus(MIL_STD_1553x);

	/* Check for errors in the message */
	if ((MIL_STD_1553_Status & MIL_STD_1553_STATUS_ERR) != 0) {
		switch (MIL_STD_1553_Errors) {
			case MIL_STD_1553_ERROR_NORCV:
				/* Reception error */
				PORT_SetBits(MDR_PORTB, PORT_Pin_0);
				break;
			case MIL_STD_1553_ERROR_MANERR:
				/* NRZ decoding error code */
				PORT_SetBits(MDR_PORTB, PORT_Pin_1);
				break;
			case MIL_STD_1553_ERROR_SYNCERR:
				/* Synchronization data error */
				PORT_SetBits(MDR_PORTB, PORT_Pin_2);
				break;
			case MIL_STD_1553_ERROR_SEQERR:
				/* Synchronization command error */
				PORT_SetBits(MDR_PORTB, PORT_Pin_3);
				break;
			case MIL_STD_1553_ERROR_GAPERR:
				/* Error invalid activity on the bus */
				PORT_SetBits(MDR_PORTB, PORT_Pin_4);
				break;
			case MIL_STD_1553_ERROR_CONERR:
				/* Error message of continuity */
				PORT_SetBits(MDR_PORTB, PORT_Pin_5);
				break;
			case MIL_STD_1553_ERROR_PROERR:
				/* Protocol error */
				PORT_SetBits(MDR_PORTB, PORT_Pin_6);
				break;
			default:
				/* Other errors */
				PORT_SetBits(MDR_PORTB, PORT_Pin_7);
				break;
		}
		MIL_STD_1553_ITConfig(MIL_STD_1553x, MIL_STD_1553_IT_ERRIE, DISABLE);
		DEBUG_PRINTF("Test error\r\n");
	}
	/* Check for the presence of the flag "the successful
	 * completion of the transaction in the channel" */
	if ((MIL_STD_1553_Status & MIL_STD_1553_STATUS_VALMESS) != 0){
		/* Disabling interrupts reception end */
		MIL_STD_1553_ITConfig(MIL_STD_1553x, MIL_STD_1553_IT_VALMESSIE, DISABLE);
		switch(MIL_STD_1553_LastRequest){
			case (READ_DATA):
				MIL_STD_1553_ReceiveData(MIL_STD_1553x,CommandWord.Fields.Subaddress, CommandWord.Fields.Data, MIL_STD_1553_Data);
				if(CommandWord.Fields.Data == 0)
					NunberDataWord = 32;
				else
					NunberDataWord = CommandWord.Fields.Data;
				/* Print the received data */
				for(i = 0; i < NunberDataWord; i++)
					DEBUG_PRINTF("MIL_STD_1553_Data[%d] = 0x%x\r\n",i, MIL_STD_1553_Data[i]);
			break;
			case (WRITE_DATA):
			break;
			case (REQUEST_LAST_COMMAND):
				DEBUG_PRINTF("Last Command Word = 0x%x", MIL_STD_1553_GetModeData(MIL_STD_1553x));
			break;
			case (REQUEST_STATUS_WORD):
				DEBUG_PRINTF("Status Word = 0x%x", MIL_STD_1553_GetStatusWord(MIL_STD_1553x, MIL_STD_1553_STATUS_WORD1));
			break;
		}
	} // if ((MIL_STD_1553_Status & MIL_STD_1553_STATUS_VALMESS) != 0) {
}

/* Private functions ---------------------------------------------------------*/

/** @} */ /* End of group MIL_STD_1553_Bus_Controller */

/** @} */ /* End of group __MDR1986VE1T_EVAL MDR1986VE1T Opora Evaluation Board */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2013 Milandr ********************************
*
* END OF FILE MIL_STD_1553_IT_Handler.c */
