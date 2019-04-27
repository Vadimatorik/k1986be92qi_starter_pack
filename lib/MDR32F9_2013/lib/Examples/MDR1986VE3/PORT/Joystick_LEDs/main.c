/**
 ******************************************************************************
 * @file    Examples/MDR1986VE3/PORT/Joystick_LEDs/main.c
 * @author  Milandr Application Team
 * @version V1.2.0
 * @date    17/06/2013
 * @brief   Main program body.
 ******************************************************************************
 * <br><br>
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2013 Milandr</center></h2>
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
 * @{
 */

/** @addtogroup __MDR1986VE3_EVAL MDR1986VE3 Complexity Evaluation Board
 * @{
 */

/** @addtogroup PORT_Joystick_LEDs_3T PORT_Joystick_LEDs
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ALL_PORTS_CLK 		(RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB | \
                       	     RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD | \
                       	   	 RST_CLK_PCLK_PORTE | RST_CLK_PCLK_PORTF)
#define PORTS_PER2_CLK		(RST_CLK_PCLK2_PORTH | RST_CLK_PCLK2_PORTG | RST_CLK_PCLK2_PORTI)
#define LEDO_Pos	   0
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;
uint32_t LEDS_Pin[6] = {PORT_Pin_7 , PORT_Pin_11 , PORT_Pin_12 ,
						PORT_Pin_13 , PORT_Pin_14 , PORT_Pin_15};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void Init_All_Ports ( void )
{
	/* Enable the RTCHSE clock on all ports */
	RST_CLK_PCLKcmd(ALL_PORTS_CLK, ENABLE);
	RST_CLK_PCLK2cmd(PORTS_PER2_CLK, ENABLE);

	/* Configure all ports to the state as after reset, i.e. low power consumption */
	PORT_StructInit(&PORT_InitStructure);
	PORT_Init(MDR_PORTA, &PORT_InitStructure);
	PORT_Init(MDR_PORTB, &PORT_InitStructure);
	PORT_Init(MDR_PORTC, &PORT_InitStructure);
	PORT_Init(MDR_PORTD, &PORT_InitStructure);
	PORT_Init(MDR_PORTE, &PORT_InitStructure);
	PORT_Init(MDR_PORTF, &PORT_InitStructure);
	PORT_Init(MDR_PORTG, &PORT_InitStructure);
	PORT_Init(MDR_PORTH, &PORT_InitStructure);
	PORT_Init(MDR_PORTI, &PORT_InitStructure);

	/* Disable the RTCHSE clock on all ports */
	RST_CLK_PCLKcmd(ALL_PORTS_CLK, DISABLE);
	RST_CLK_PCLK2cmd(PORTS_PER2_CLK, DISABLE);
}

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
void main ( void )
{
	uint32_t tmp_port_pin;
	uint32_t i;

	/*!< Usually, reset is done before the program is to be loaded into microcontroller,
	 and there is no need to perform any special operations to switch the ports
	 to low power consumption mode explicitly. So, the function Init_All_Ports
	 is used here for demonstration purpose only.
	 */
	Init_All_Ports();

	/* Enables the RTCHSE clock on PORTC and PORTD */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);
	RST_CLK_PCLK2cmd(RST_CLK_PCLK2_PORTG, ENABLE);

	/* Configure PORTG pins 7, 11, 12, 13, 14, 15 for input to handle joystick events */

	PORT_InitStructure.PORT_Pin = (PORT_Pin_7 | PORT_Pin_11 | PORT_Pin_12
			| PORT_Pin_13 | PORT_Pin_14 | PORT_Pin_15);
	PORT_InitStructure.PORT_OE = PORT_OE_IN;
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

	PORT_Init(MDR_PORTG, &PORT_InitStructure);

	/* Configure PORTB pins 0...5 for output to switch LEDs on/off */

	PORT_InitStructure.PORT_Pin = (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2
			| PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5);
	PORT_InitStructure.PORT_OE = PORT_OE_OUT;
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;

	PORT_Init(MDR_PORTB, &PORT_InitStructure);

	/* In this infinite loop, joystick are iteratively scanned and
	 PORTD output pins (LED indicators) are appropriately set/cleared.
	 Note: in this example, the following fact about MDR1986VE3 eval board is used: the
	 joystic input pin numbers exactly match LED output pins, i.e:
	 SEL    => VD9
	 UP     => VD7
	 DOWN   => VD10
	 LEFT   => VD5
	 RIGHT  => VD6
	 BACK	=> VD8
	 */

	while (1) {
		tmp_port_pin = PORT_ReadInputData(MDR_PORTG );
		for (i = 0; i < 6; i++) {
			if ((tmp_port_pin & LEDS_Pin[i]) == LEDS_Pin[i])
				PORT_SetBits(MDR_PORTB, 1 << LEDO_Pos + i);
			else
				PORT_ResetBits(MDR_PORTB, 1 << LEDO_Pos + i);
		}
	}
}

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

/** @} *//* End of group PORT_Joystick_LEDs_3T */

/** @} *//* End of group __MDR1986VE3 */

/** @} *//* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2013 Milandr *********/

/* END OF FILE main.c */
