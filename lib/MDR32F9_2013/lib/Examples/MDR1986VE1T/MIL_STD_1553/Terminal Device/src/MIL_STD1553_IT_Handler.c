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
#include "MDR32F9Qx_config.h"
#include "MIL_STD_1553_IT_Handler.h"
#include "MDR1986VE1T_IT.h"
#include "MDR32F9Qx_mil_std_1553.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_timer.h"

#define ASSERT_INFO_FILE_ID FILEID__MIL_STD_1553_IT_Handler_C

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR1986VE1T_EVAL MDR1986VE1T Opora Evaluation Board
  * @{
  */

/** @addtogroup MIL_STD_1553_Terminal_Device_IT MIL_STD_1553_Terminal_Device
 *  @{
 */

/* Private typedef -----------------------------------------------------------*/
typedef enum {
	RX_BC_TD 	   	= 0x0001,
	RX_BC_TD_GROUP	= 0x0080,
	RX_TD_TD		= 0x0004,
	RX_TD_TD_GROUP	= 0x0100,
	TX_TD_BC		= 0x0402,
	TX_TD_TD		= 0x1008,
	TX_TD_TD_GROUP	= 0x0200,
	CONTROL_COMMAND_NO_DATA 			= 0x0410,
	CONTROL_COMMAND_NO_DATA_GROUP 		= 0x0400,
	CONTROL_CPMMAND_WITH_DATA			= 0x2420,
	CONTROL_CPMMAND_WITH_DATA_TX		= 0x0040,
	CONTROL_CPMMAND_WITH_DATA_GROUP_TX	= 0x0800
}MSG_TypeDef;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
uint32_t CommandWordFlag = 0;
uint32_t GruopCommandFlag = 0;
uint32_t SaveModeDataFlag = 0;
uint32_t SetTDInDefaultFlag = 0;
uint32_t ReceivedNewControlWordflag = 0;
uint32_t CircularReturnDataFlag = 0;

uint32_t MIL_STD_1553_Data[32];
uint32_t MIL_STD_1553_Modedata;
uint32_t MIL_STD_1553_MSG;
uint32_t MIL_STD_1553_LastCommandWord = 0;
/* Private function prototypes -----------------------------------------------*/
Bool ISControlCommand(MIL_STD_1553_CommandWordTypeDef * CommandWord);

/**
  * @brief	The interrupt handler from the interface MIL_STD_15531.
  * @param	MIL_STD_1553x: Slect the MIL_STD_1553 peripheral.
  *         This parameter can be one of the following values:
  *         MIL_STD_15531, MIL_STD_15532.
  * @retval	None
  */
void My_MIL_STD_1553_Handler( MDR_MIL_STD_1553_TypeDef * MIL_STD_1553x )
{
	uint32_t MIL_STD_1553_Status;
	uint32_t MIL_STD_1553_Errors;
	MIL_STD_1553_CommandWordTypeDef MIL_STD_1553_CommandWord1 = {0};
	MIL_STD_1553_StatusWordTypeDef MIL_STD_1553StatusWord1 = {0};

	/* Get the Status register */
	MIL_STD_1553_Status = MIL_STD_1553_GetStatus(MIL_STD_1553x);
	/* Get the Errors register */
	MIL_STD_1553_Errors = MIL_STD_1553_GetErrorStatus(MIL_STD_1553x);

	/* Check for errors in the message */
	if ((MIL_STD_1553_Status & MIL_STD_1553_STATUS_ERR) != 0) {

		/* Enable interrupt at the transition to idle mode */
		MIL_STD_1553_ITConfig( MIL_STD_1553x,
		                      (MIL_STD_1553_IT_RFLAGNIE | MIL_STD_1553_IT_VALMESSIE | MIL_STD_1553_IT_ERRIE),
		                       DISABLE);
		MIL_STD_1553_ITConfig(MIL_STD_1553x, (MIL_STD_1553_IT_IDLEIE), ENABLE);

		/* Allow reset error */
		MIL_STD_1553_RERRCmd(MIL_STD_1553x, DISABLE);

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
		/* Check flag CommandWordFlag */
		if(CommandWordFlag){
			MIL_STD_1553StatusWord1.StatusWord = 0;
			MIL_STD_1553StatusWord1.Fields.TerminalDeviceAddress = MIL_STD_1553_TERMINAL_ADDRESS;
			MIL_STD_1553StatusWord1.Fields.ErrorBit = 1;

			/* Check flag GruopCommandFlag */
			if(GruopCommandFlag){
				MIL_STD_1553StatusWord1.Fields.GroupCommandBit = 1;
				GruopCommandFlag = 0;
			}
			/* Set status word */
			MIL_STD_1553_SetStatusWord( MIL_STD_1553x,
										MIL_STD_1553_STATUS_WORD1,
										&MIL_STD_1553StatusWord1);
			/* Reset flag */
			CommandWordFlag = 0;
		}
	}
	else {
		/* Set RERR bit in the CCONTROL register */
		MIL_STD_1553_RERRCmd(MIL_STD_1553x, ENABLE);
		/*--------------------------------------------------------------------*/
		/* Check that the controller is switched to the idle mode */
		if ((MIL_STD_1553_Status & MIL_STD_1553_STATUS_IDLE) != 0) {

			/* Enable interrapts */
			MIL_STD_1553_ITConfig( MIL_STD_1553x, MIL_STD_1553_IT_IDLEIE, DISABLE);

			MIL_STD_1553_ITConfig( MIL_STD_1553x,
								  (MIL_STD_1553_IT_RFLAGNIE |
								   MIL_STD_1553_IT_VALMESSIE |
								   MIL_STD_1553_IT_ERRIE),
								  ENABLE);
		} // if ((MIL_STD_1553_Status & MIL_STD_1553_STATUS_IDLE) != 0) {
		/*--------------------------------------------------------------------*/
		else{
			MIL_STD_1553_MSG = MIL_STD_1553_GetMSG(MIL_STD_1553x);
			/* Save the command word */
			MIL_STD_1553_CommandWord1.CommandWord = MIL_STD_1553_GetCommandWord( MIL_STD_1553x,
																				 MIL_STD_1553_COMMAND_WORD1);
			/* Check for the presence of the flag "the successful
			 * completion of the transaction in the channel" */
			/* Save MSG register */
			if ((MIL_STD_1553_Status & MIL_STD_1553_STATUS_VALMESS) != 0){
			/*----------------------------------------------------------------*/
				if ((MIL_STD_1553_Status & MIL_STD_1553_STATUS_RFLAGN) != 0){
					if( ( MIL_STD_1553_MSG == CONTROL_COMMAND_NO_DATA_GROUP ) &&
						( MIL_STD_1553_CommandWord1.Fields.ReadWriteBit ==
								MIL_STD_1553_TD_TO_BC)){
						/* Set the terminal addres is the status word */
						MIL_STD_1553StatusWord1.Fields.TerminalDeviceAddress = MIL_STD_1553_TERMINAL_ADDRESS;
						/* Set the attribute group team command */
						MIL_STD_1553StatusWord1.Fields.GroupCommandBit = 1;

						MIL_STD_1553_SetStatusWord( MIL_STD_1553x,
												MIL_STD_1553_STATUS_WORD1,
												&MIL_STD_1553StatusWord1);

						/*switch (MIL_STD_1553_CommandWord1.Fields.Data.Cmd){*/
						switch (MIL_STD_1553_CommandWord1.Fields.Data){
							case 0x01:	/* Synchronization 		*/
							case 0x03:	/* Start self-test TD 	*/
							case 0x06:	/* Block symptom TD 	*/
							case 0x07:	/* Unblock symptom TD 	*/
								break;
							case 0x04:	/* Block the transmitter */
								if (MIL_STD_1553_GetFlagStatus(MIL_STD_1553x,
										MIL_STD_1553_FLAG_RCVA) == SET){
									MIL_STD_1553_Transmitter_CMD(MIL_STD_1553x,
											MIL_STD_1553_TRANSMITTER_RESERVE,
											DISABLE);
								}
								else{
									MIL_STD_1553_Transmitter_CMD(MIL_STD_1553x,
											MIL_STD_1553_TRANSMITTER_MAIN,
											DISABLE);
								}
								break;
							case 0x05:	/* Unblock the transmitter	*/
								if (MIL_STD_1553_GetFlagStatus(MIL_STD_1553x,
										MIL_STD_1553_FLAG_RCVA) == SET){
									MIL_STD_1553_Transmitter_CMD(MIL_STD_1553x,
											MIL_STD_1553_TRANSMITTER_RESERVE,
											ENABLE);
								}
								else{
									MIL_STD_1553_Transmitter_CMD(MIL_STD_1553x,
											MIL_STD_1553_TRANSMITTER_MAIN,
											ENABLE);
								}
								break;
							case 0x08:	/* Set the าย to its original state */
								SetTDInDefaultFlag = 1;
								break;
							default:	/* In any other case, the error in the message */
								ErrorState(MIL_STD_1553x, MIL_STD_1553_MSG);
								return;
						}
					} /* if( ( MIL_STD_1553_MSG == CONTROL_COMMAND_NO_DATA_GROUP ) &&
						( MIL_STD_1553_CommandWord1.Fields.ReadWriteBit == MIL_STD_WRITE_BIT)){*/
					else {
						/* Took a group message with data */
						if((MIL_STD_1553_MSG == CONTROL_CPMMAND_WITH_DATA_GROUP_TX) &&
						   (MIL_STD_1553_CommandWord1.Fields.ReadWriteBit == MIL_STD_1553_BC_TO_TD)){
							/*switch(MIL_STD_1553_CommandWord1.Fields.Data.Cmd){*/
							switch (MIL_STD_1553_CommandWord1.Fields.Data){
								case 0x11:	/* Synchronization with data word	*/
								case 0x14:	/* Block the i-th transmitter 		*/
								case 0x15:	/* Unblock the i-th transmitter 	*/
									break;
								default:	/* In any other case, the error in the message */
									ErrorState(MIL_STD_1553x, MIL_STD_1553_MSG);
									return;
							}
							/* Set the request flag to save the data word */
							SaveModeDataFlag = 1;
						} /* if((MIL_STD_1553_MSG == CONTROL_CPMMAND_WITH_DATA_GROUP_TX) &&
						   (MIL_STD_1553_CommandWord1.Fields.ReadWriteBit == MIL_STD_READ_BIT)){ */
						else {
							if (MIL_STD_1553_MSG != TX_TD_TD) {
								ErrorState(MIL_STD_1553x, MIL_STD_1553_MSG);
								return;
							}
						}
					}
				} // if ((MIL_STD_1553_Status & MIL_STD_1553_STATUS_RFLAGN) != 0)	{

				/* Disabling interrupts reception end */
				MIL_STD_1553_ITConfig(MIL_STD_1553x, MIL_STD_1553_IT_VALMESSIE, DISABLE);

				/* Enabling interrupt in idle mode */
				MIL_STD_1553_ITConfig(MIL_STD_1553x, MIL_STD_1553_IT_IDLEIE, ENABLE);

				/* Save the last true command word */
				MIL_STD_1553_LastCommandWord = MIL_STD_1553_CommandWord1.CommandWord;

				/* Check flag SetTDInDefaultFlag  */
				if(SetTDInDefaultFlag){
					/* Set the TD in the inital state */
					//MILConfig();
					SetTDInDefaultFlag = 0;
				}

				/* Check flag CircularReturnDataFlag */
				if(CircularReturnDataFlag){
					/* Circular return data */
					MIL_STD_1553_ReceiveData( MIL_STD_1553x,
											  MIL_STD_1553_CommandWord1.Fields.Subaddress,
											  /*MIL_STD_1553_CommandWord1.Fields.Data.NumberDataWords,*/
											  MIL_STD_1553_CommandWord1.Fields.Data,
											  MIL_STD_1553_Data);

					MIL_STD_1553_WiteDataToSendBuffer( MIL_STD_1553x,
													   MIL_STD_1553_CommandWord1.Fields.Subaddress,
													   /*MIL_STD_1553_CommandWord1.Fields.Data.NumberDataWords,*/
													   MIL_STD_1553_CommandWord1.Fields.Data,
													   MIL_STD_1553_Data);
					CircularReturnDataFlag = 0;
				}

				/* Check flag SaveModeDataFlag */
				if(SaveModeDataFlag){
					/* Save the data word */
					MIL_STD_1553_Modedata = MIL_STD_1553_GetModeData(MIL_STD_1553x);
					SaveModeDataFlag = 0;
				}

				/* Reset flag obtain reliable control word */
				ReceivedNewControlWordflag = 0;
			} // if ((MIL_STD_1553_Status & MIL_STD_1553_STATUS_VALMESS) != 0) {
			/*----------------------------------------------------------------*/
			else{
				/* Event handling obtain reliable control word from the channel */
				if ((MIL_STD_1553_Status & MIL_STD_1553_STATUS_RFLAGN) != 0)	{

					/* Disable intterupt at the receiving command word from the channel */
					MIL_STD_1553_ITConfig( MIL_STD_1553x, MIL_STD_1553_IT_RFLAGNIE, DISABLE);
					/* Save MSG regiser */
					MIL_STD_1553_MSG = MIL_STD_1553_GetMSG(MIL_STD_1553x); // imsg
					/* Save command word */
					MIL_STD_1553_CommandWord1.CommandWord = MIL_STD_1553_GetCommandWord(MIL_STD_1553x, MIL_STD_1553_COMMAND_WORD1);

					switch (MIL_STD_1553_MSG){
						/*--- Control command, without data , not the group ---*/
						case CONTROL_COMMAND_NO_DATA:
							if ( (ISControlCommand(&MIL_STD_1553_CommandWord1) == FALSE) ||
								 (MIL_STD_1553_CommandWord1.Fields.ReadWriteBit == MIL_STD_1553_BC_TO_TD)){
								ErrorState(MIL_STD_1553x, MIL_STD_1553_MSG);
								return;
							}
							/*switch (MIL_STD_1553_CommandWord1.Fields.Data.Cmd){*/
							switch (MIL_STD_1553_CommandWord1.Fields.Data){
								case 0x02:	/* Transmits the response word */
									MIL_STD_1553_LastCommandWord = MIL_STD_1553_CommandWord1.CommandWord;
									ReceivedNewControlWordflag = 1;
									return;
								case 0x00: /* Take control of the interface */
								case 0x01: /* Synchronization 				*/
								case 0x03: /* Start self-test TD 			*/
								case 0x06: /* Block symptom TD 				*/
								case 0x07: /* Unblock symptom TD 			*/
									break;
								case 0x04:	/* Block the transmitter */
									if (MIL_STD_1553_GetFlagStatus(MIL_STD_1553x,
											MIL_STD_1553_FLAG_RCVA) == SET){
										MIL_STD_1553_Transmitter_CMD(MIL_STD_1553x,
												MIL_STD_1553_TRANSMITTER_RESERVE,
												DISABLE);
									}
									else{ MIL_STD_1553_Transmitter_CMD(MIL_STD_1553x,
												MIL_STD_1553_TRANSMITTER_MAIN,
												DISABLE);
									}
									break;
								case 0x05:	/* Unblock the transmitter */
									if (MIL_STD_1553_GetFlagStatus(MIL_STD_1553x,
											MIL_STD_1553_FLAG_RCVA) == SET){
										MIL_STD_1553_Transmitter_CMD(MIL_STD_1553x,
												MIL_STD_1553_TRANSMITTER_RESERVE,
												ENABLE);
									}
									else{ MIL_STD_1553_Transmitter_CMD(MIL_STD_1553x,
												MIL_STD_1553_TRANSMITTER_MAIN,
												ENABLE);
									}
									break;
								case 0x08:	/* Set the าย to its original state */
									SetTDInDefaultFlag = 1;
									break;
								default:	/* In any other case, the error in the message */
									ErrorState(MIL_STD_1553x, MIL_STD_1553_MSG);
									return;
							}
							break;
						/*--- Control command, with data, not the group ---*/
						case CONTROL_CPMMAND_WITH_DATA_TX:
							if ( (ISControlCommand(&MIL_STD_1553_CommandWord1) == FALSE) ||
								 (MIL_STD_1553_CommandWord1.Fields.ReadWriteBit == MIL_STD_1553_TD_TO_BC)){
								ErrorState(MIL_STD_1553x, MIL_STD_1553_MSG);
								return;
							}
							/*switch(MIL_STD_1553_CommandWord1.Fields.Data.Cmd){*/
							switch (MIL_STD_1553_CommandWord1.Fields.Data){
								case 0x11:	/* Synchronization with data word 	*/
								case 0x14:	/* Block the i-th transmitter 		*/
								case 0x15:	/* Unblock the i-th transmitter 	*/
									break;
								default:	/* In any other case, the error in the message */
									MIL_STD_1553x->ModeData = 0x00;
									ErrorState(MIL_STD_1553x, MIL_STD_1553_MSG);
									return;
							}
							SaveModeDataFlag = 1;
							break;
						/*--- Control command, without data , not the group, with transfer request data word ---*/
						case CONTROL_CPMMAND_WITH_DATA:
							if ((ISControlCommand(&MIL_STD_1553_CommandWord1) == FALSE) ||
								(MIL_STD_1553_CommandWord1.Fields.ReadWriteBit == MIL_STD_1553_BC_TO_TD)){
								ErrorState(MIL_STD_1553x, MIL_STD_1553_MSG);
								return;
							}
							/*switch (MIL_STD_1553_CommandWord1.Fields.Data.Cmd){*/
							switch (MIL_STD_1553_CommandWord1.Fields.Data){
								case 0x10:	/* Transmit the vector word */
									MIL_STD_1553x->ModeData = 0x1248;
									break;
								case 0x13:	/* Transmit VSK word */
									MIL_STD_1553x->ModeData = 0x0000;
									break;
								case 0x12:	/* Transmit last command */
									MIL_STD_1553x->ModeData = MIL_STD_1553_LastCommandWord;
									return;
								default:	/* In any other case, the error in the message */
									ErrorState(MIL_STD_1553x, MIL_STD_1553_MSG);
									return;
							}
							break;
						/*----- Commands data exchange -----*/
						/*----- Data exchange: Bus controller -> terminal device, no group -----*/
						case RX_BC_TD:
							if(ISControlCommand(&MIL_STD_1553_CommandWord1) == TRUE){
								ErrorState(MIL_STD_1553x, MIL_STD_1553_MSG);
								return;
							}
							/* Enable TIMER1 interrupt */
							TIMER_ITConfig(MDR_TIMER1, TIMER_STATUS_CNT_ARR, ENABLE);
							/* Start TIMER1 */
							TIMER_Cmd(MDR_TIMER1, ENABLE);

							break;
						/*----- Data exchange: Bus controller -> terminal device, group -----*/
						case RX_BC_TD_GROUP:
							if(ISControlCommand(&MIL_STD_1553_CommandWord1) == TRUE){
								ErrorState(MIL_STD_1553x, MIL_STD_1553_MSG);
								return;
							}
							TIMER_ITConfig(MDR_TIMER1, TIMER_STATUS_CNT_ARR, ENABLE);
							TIMER_Cmd(MDR_TIMER1, ENABLE);

							break;
						/*----- Data exchange: Terminal device -> bus controller, no group -----*/
						case TX_TD_BC:
							if(ISControlCommand(&MIL_STD_1553_CommandWord1) == TRUE){
								ErrorState(MIL_STD_1553x, MIL_STD_1553_MSG);
								return;
							}
							break;
						/*----- Data exchange: Terminal device -> terminal device, no group -----*/
						case TX_TD_TD:
							MIL_STD_1553_CommandWord1.CommandWord = MIL_STD_1553_GetCommandWord( MIL_STD_1553x,
																				     MIL_STD_1553_COMMAND_WORD2);
							break;
						/*----- Data exchange: Terminal device -> terminal device, group -----*/
						case TX_TD_TD_GROUP:
							if(ISControlCommand(&MIL_STD_1553_CommandWord1) == TRUE){
								ErrorState(MIL_STD_1553x, MIL_STD_1553_MSG);
								return;
							}
							MIL_STD_1553StatusWord1.Fields.GroupCommandBit = 1;
							MIL_STD_1553_CommandWord1.CommandWord = MIL_STD_1553_GetCommandWord( MIL_STD_1553x,
																				     MIL_STD_1553_COMMAND_WORD2);
							break;
						default: /* In any other case, the error in the message */
							ErrorState(MIL_STD_1553x, MIL_STD_1553_MSG);
							return;
					}
					/* Set the terminal address in the status word */
					MIL_STD_1553StatusWord1.Fields.TerminalDeviceAddress = MIL_STD_1553_TERMINAL_ADDRESS;
					/* Set status word  */
					MIL_STD_1553_SetStatusWord(MIL_STD_1553x, MIL_STD_1553_STATUS_WORD1, &MIL_STD_1553StatusWord1);
					/* Save the thrue command word */
					MIL_STD_1553_LastCommandWord = MIL_STD_1553_CommandWord1.CommandWord;
					/* Set the ReceivedNewControlWordflag flag  */
					ReceivedNewControlWordflag = 1;
				} // if ((MIL_STD_1553_Status & MIL_STD_1553_STATUS_RFLAGN) != 0)	{
			}
		}
	}
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief	Function checks hte received command for the control command.
  * @param	CommandWord: The received the command word.
  * @retval	The state submission of multicast addresses (TRUE or FALSE).
  */
Bool ISControlCommand(MIL_STD_1553_CommandWordTypeDef * CommandWord)
{
	if ( (CommandWord->Fields.Subaddress == 0) ||
		 (CommandWord->Fields.Subaddress == 0x1F) )
		return (TRUE);
	else
		return(FALSE);
}

/**
  * @brief	Set the status word with error bit.
  * @param	MIL_STD_1553x: Select the MIL_STD_1553 peripheral.
  *         This parameter can be one of the following values:
  *         MIL_STD_15531, MIL_STD_15532.
  * @param	msg: the value of the MSG register.
  * @retval None
  */
void ErrorState ( MDR_MIL_STD_1553_TypeDef * MIL_STD_1553x, uint32_t msg ) {

	/* Check the parameters */
	assert_param(IS_MIL_STD_1553_ALL_PERIPH(MIL_STD_1553x));

	MIL_STD_1553_StatusWordTypeDef StatusWord = {0};

	StatusWord.Fields.TerminalDeviceAddress = MIL_STD_1553_TERMINAL_ADDRESS;
	StatusWord.Fields.ErrorBit = 1;

	switch (msg) {
		/* Received group team */
		case 0x0080:
		case 0x0100:
		case 0x0200:
		case 0x0400:
		case 0x0800:
			StatusWord.Fields.GroupCommandBit = 1;
			break;
		/* Received non group team */
		default:
			break;
	}
	MIL_STD_1553_SetStatusWord(MIL_STD_1553x, MIL_STD_1553_STATUS_WORD1, &StatusWord);
}

/** @} */ /* End of group MIL_STD_1553_Terminal_Device */

/** @} */ /* End of group __MDR1986VE1T_EVAL MDR1986VE1T Opora Evaluation Board */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2013 Milandr ********************************
*
* END OF FILE MIL_STD_1553_IT_Handler.c */
