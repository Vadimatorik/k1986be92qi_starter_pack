/**
  ******************************************************************************
  * @file	 MT_107_MELT.c
  * @author	 sidorov.a
  * @version 1.0
  * @date    24.03.2014
  * @brief   This file contains display control function.
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
  * <h2><center>&copy; COPYRIGHT 2014 Milandr </center></h2>
  ******************************************************************************
  * FILE MT_107_MELT.c
  */

#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_port.h"
#include "MT_107_MELT.h"

const uint8_t digits_low[]={0xe,0x00,0xf,0xd,0x1,0xd,0xf,0x8,0xf,0xd};
const uint8_t digits_hi[]={0xe,0x6,0x2,0x6,0xe,0x0C,0x0C,0x6,0xe,0xe};

/** @brief	Init display MT107 MELT
 *	@param	None
 *	@retval	None
 */
void Display_Init(void)
{
	PORT_InitTypeDef PORT_InitStructure;

	PORT_StructInit(&PORT_InitStructure);

	/* Port Init */
	PORT_InitStructure.PORT_Pin = PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 |
								  PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_14 | PORT_Pin_15;
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_OE = PORT_OE_OUT;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;

	PORT_Init(MDR_PORTA, &PORT_InitStructure);

	PORT_SetBits(MDR_PORTA, PORT_Pin_4);
	PORT_ResetBits(MDR_PORTA, PORT_Pin_15);

	Display_UnLock();
	Display_Clear();
}

/** @brief 	Clear display
 *	@param 	None
 *	@retval	None
 */
void Display_Clear(void)
{
	int i;

	for(i = 0; i < 10; i++){
		Display_PutChar(i, 0x00);
	}
}

/**
 * @brief	Displays the specified character at a specific position
 * 			of the display.
 * @param 	char_position: character position on dispaly.
 * @param 	put_char: specified character.
 * @retval	None
 */
void Display_PutChar(uint8_t char_position, uint8_t put_char)
{

	uint32_t tmp = 0;

	/* Write address */
	PORT_ResetBits(MDR_PORTA, PORT_Pin_4);
	PORT_ResetBits(MDR_PORTA, PORT_Pin_15);
	PORT_SetBits(MDR_PORTA, PORT_Pin_14);
	Delay();
	tmp =( (PORT_ReadInputData(MDR_PORTA) & (~0x0F)) | char_position)  & ~PORT_JTAG_Msk;
	PORT_Write(MDR_PORTA, tmp);
	Delay();

	PORT_ResetBits(MDR_PORTA, PORT_Pin_14);
	PORT_SetBits(MDR_PORTA, PORT_Pin_4);
	PORT_SetBits(MDR_PORTA, PORT_Pin_15);

	Delay();

	/* Write LO data */
	PORT_ResetBits(MDR_PORTA, PORT_Pin_15);
	PORT_SetBits(MDR_PORTA, PORT_Pin_14);
	Delay();
	tmp = ((PORT_ReadInputData(MDR_PORTA) & (~0x0F)) | (put_char&0x0F))  & ~PORT_JTAG_Msk;
	PORT_Write(MDR_PORTA, tmp);
	Delay();
	PORT_ResetBits(MDR_PORTA, PORT_Pin_14);
	PORT_SetBits(MDR_PORTA, PORT_Pin_15);

	Delay();

	/* Write LO data */
	PORT_ResetBits(MDR_PORTA, PORT_Pin_15);
	PORT_SetBits(MDR_PORTA, PORT_Pin_14);
	Delay();
	tmp = ((PORT_ReadInputData(MDR_PORTA) & (~0x0F)) | ((put_char >> 4)&0x0F))  & ~PORT_JTAG_Msk;
	PORT_Write(MDR_PORTA, tmp);
	Delay();
	PORT_ResetBits(MDR_PORTA, PORT_Pin_14);
	PORT_SetBits(MDR_PORTA, PORT_Pin_15);
	Delay();
}

/**
 * @brief	Displays the specified digital number at a specific position
 * 			of the display.
 * @param 	char_position: character position on dispaly.
 * @param 	digit: output digital number.
 */
void Display_PutDigit(uint8_t char_position, uint8_t digit)
{
	uint8_t tmp;

	if(digit < 10){
		tmp = (digits_hi[digit]<<4)| (digits_low[digit]);
	}
	else{
		tmp = 0xFF;
	}
	Display_PutChar(char_position, tmp);
}

/**
 *	@brief Lock dispaly
 */
void Display_Lock(void )
{
	Display_PutChar(0x0F, 0);
}

/**
 *	@brief Unlock dispaly
 */
void Display_UnLock(void)
{
	Display_PutChar(0x0F, 0xFF);
}

/**
 *	@brief Delay
 */
void Delay(void )
{
	int i;
	for(i = 0; i < 10; i++);
}


/******************* (C) COPYRIGHT 2014 Milandr ********************************
*
* END OF FILE MT_107_MELT.c */

