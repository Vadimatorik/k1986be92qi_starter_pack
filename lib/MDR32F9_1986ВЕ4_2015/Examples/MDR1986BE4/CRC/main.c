/**
  ******************************************************************************
  * @file	 main.c
  * @author	 sidorov.a
  * @version 1.0
  * @date    28.03.2014
  * @brief   Main program body.
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
  * FILE main.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_crc.h"

#define ASSERT_INFO_FILE_ID FILEID__main_C

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR1986BE4_EVAL MDR1986BE4 Evaluation Board
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CRC_ARRAY_SIZE	9

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;
CRC_InitTypeDef CRC_InitStruct;
uint8_t test_array[CRC_ARRAY_SIZE];
const unsigned short Crc16Table[256] = {
		0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
		    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
		    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
		    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
		    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
		    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
		    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
		    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
		    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
		    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
		    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
		    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
		    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
		    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
		    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
		    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
		    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
		    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
		    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
		    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
		    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
		    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
		    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
		    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
		    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
		    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
		    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
		    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
		    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
		    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
		    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
		    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};
/* Private function prototypes -----------------------------------------------*/
uint16_t Crc16(uint8_t * pcBlock, uint16_t len);
uint16_t ReverseBits(uint16_t crc);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
	uint32_t i;
	uint16_t crc16_soft;
	uint16_t crc16_hard;

	/* Reset clock setting */
	RST_CLK_DeInit();

	/* Enable HSE */
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);

	/* Wait untile HSE not ready */
	if(RST_CLK_HSEstatus() == ERROR)
		while(1);

	/* cConfig the PLL */
	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul4);

	/* Enable PLL */
	RST_CLK_CPU_PLLcmd(ENABLE);

	/* Wait until PLL not ready */
	if(RST_CLK_CPU_PLLstatus() == ERROR)
		while(1);

	/* Use PLL */
	RST_CLK_CPU_PLLuse(ENABLE);
	/* Set clock prescaller */
	RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);
	/* Set CPU_C3 clock source */
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);

	/* Enable the adciu clock and port a clock */
	RST_CLK_PCLKcmd((RST_CLK_PCLK_CRC | RST_CLK_PCLK_PORTA), ENABLE);

	/* Init the PORTA */
	PORT_InitStructure.PORT_Pin = PORT_Pin_11;
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_OE = PORT_OE_OUT;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;

	PORT_Init(MDR_PORTA, &PORT_InitStructure);

	/* Reset the crc block*/
	CRC_DeInit();

	/* Init the CRC_InitStruct */
	CRC_StructInit(&CRC_InitStruct);

	/* Init crc block */
	CRC_InitStruct.CRC_Polynom = 0x8005;
	CRC_InitStruct.CRC_StartValue = 0xFFFF;
	CRC_Init(&CRC_InitStruct);

	/* Fill the test array */
	for(i = 0; i < CRC_ARRAY_SIZE; i++)
		test_array[i] = i + 0x31;

	/* Software crc calculation */
	crc16_soft = Crc16(test_array, CRC_ARRAY_SIZE);

	/* Hardware crc calculation */
	CRC_Cmd(ENABLE);

	/* Fill the FIFO crc block */
	for(i = 0; i < CRC_ARRAY_SIZE; i++){
		while(CRC_GetFlagStatus(CRC_FIFO_FULL) == SET);
		CRC_WriteData(test_array[i]);
	}

	/* Wait until crc not computed */
	while(CRC_GetFlagStatus(CRC_CONV_COMP) != 1);

	/* Disable crc  */
	CRC_Cmd(DISABLE);

	/* Read the crc value */
	crc16_hard = CRC_GetCRC();

	/* reverse CRC result */
	crc16_hard = ReverseBits(crc16_hard);

	/* Check the crc */
	if(crc16_soft == crc16_hard){
		PORT_SetBits(MDR_PORTA, PORT_Pin_11);
	}

	while(1);
}

/**
 * @brief	Software crc calculation.
 * @param 	buf: pointer to input data/
 * @param 	len: number of data byte;
 * @return	crc: crc value.
 */
uint16_t Crc16(uint8_t * pcBlock, uint16_t len)
{
    uint16_t crc = 0xFFFF;

    while (len--)
    	crc = (crc >> 8) ^ Crc16Table[(crc & 0xFF) ^ *pcBlock++];

    return crc;
}

/**
 * @brief	Revert bits in CRC value.
 * @param 	crc: input CRC value.
 * @return	Invers CRC value.
 */
uint16_t ReverseBits(uint16_t crc)
{
	uint16_t reverse_crc = 0;
	int32_t i;

	for(i = 15; i >= 0; i--){
		reverse_crc |= ((crc >> i) & 1) << (15 - i);
	}
	return (reverse_crc);
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Reports the source file ID, the source line number
  *         and expression text (if USE_ASSERT_INFO == 2) where
  *         the assert_param error has occurred.
  * @param  file_id: pointer to the source file name
  * @param  line: assert_param error line source number
  * @param  expr:
  * @retval None
  */
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint32_t file_id, uint32_t line)
{
  /* User can add his own implementation to report the source file ID and line number.
     Ex: printf("Wrong parameters value: file Id %d on line %d\r\n", file_id, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint32_t file_id, uint32_t line, const uint8_t* expr);
{
  /* User can add his own implementation to report the source file ID, line number and
     expression text.
     Ex: printf("Wrong parameters value (%s): file Id %d on line %d\r\n", expr, file_id, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_ASSERT_INFO */

/** @} */ /* End of group __MDR1986BE4_EVAL MDR1986BE4 Evaluation Board */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2014 Milandr ********************************
*
* END OF FILE main.c */
