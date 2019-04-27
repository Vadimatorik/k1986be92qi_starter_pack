/**
  ******************************************************************************
  * @file    Examples/MDR1986BE4_EVAL/PORT/Joystick_LEDs/main.c
  * @author  Milandr Application Team
  * @version V1.2.0
  * @date    04/07/2014
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
  * <h2><center>&copy; COPYRIGHT 2014 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MT_107_MELT.h"

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR1986BE4_EVAL MDR1986BE4 Evaluation Board
  * @{
  */

/** @addtogroup PORT_Joystick_LEDs PORT_Joystick_LEDs
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ALL_PORTS_CLK (RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB | RST_CLK_PCLK_PORTC)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void Init_All_Ports(void)
{
  /* Enable the RTCHSE clock on all ports */
  RST_CLK_PCLKcmd(ALL_PORTS_CLK, ENABLE);

  /* Configure all ports to the state as after reset, i.e. low power consumption */
  PORT_StructInit(&PORT_InitStructure);
  PORT_Init(MDR_PORTA, &PORT_InitStructure);
  PORT_Init(MDR_PORTB, &PORT_InitStructure);
  PORT_Init(MDR_PORTC, &PORT_InitStructure);

  /* Disable the RTCHSE clock on all ports */
  RST_CLK_PCLKcmd(ALL_PORTS_CLK, DISABLE);
}


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
#ifdef __CC_ARM
int main(void)
#else
void main(void)
#endif
{
	uint32_t tmp_port_pin;

  /*!< Usually, reset is done before the program is to be loaded into microcontroller,
       and there is no need to perform any special operations to switch the ports
       to low power consumption mode explicitly. So, the function Init_All_Ports
       is used here for demonstration purpose only.
  */
  Init_All_Ports();

  /* Enables the RTCHSE clock on PORTC and PORTD */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB, ENABLE);

  Display_Init();

  /* Configure PORTB pins 9..12 for input to handle joystick events */

  PORT_InitStructure.PORT_Pin   = (PORT_Pin_9 | PORT_Pin_10 | PORT_Pin_11 |
                                   PORT_Pin_12);
  PORT_InitStructure.PORT_OE    = PORT_OE_IN;
  PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

  PORT_Init(MDR_PORTB, &PORT_InitStructure);


  /* In this infinite loop, PORTB pins 9..12 (joystick) are iteratively scanned and
     PORTA output pins (LED display) are appropriately set/cleared.
     Note: in this example, the following fact about MDR1986BE4 eval board is used: the
     joystic input pin numbers exactly match LED output pins, i.e:
         UP     => 3
         DOWN   => 1
         LEFT   => 4
         RIGHT  => 2
  */
  while(1){
	  tmp_port_pin = PORT_ReadInputData(MDR_PORTB);

	  switch ((~tmp_port_pin >> 9) & 0xF){
		  case 0:
			  Display_Clear();
			  break;
		  case 0x01:
			  Display_PutDigit(0, 1);
			  break;
		  case 0x02:
			  Display_PutDigit(0, 2);
			  break;
		  case 4:
			  Display_PutDigit(0, 3);
			  break;
		  case 8:
			  Display_PutDigit(0, 4);
			  break;
		  default:
			  Display_PutDigit(0, 0);
			  break;
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

/** @} */ /* End of group PORT_Joystick_LEDs */

/** @} */ /* End of group __MDR1986BE4_EVAL */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */


/******************* (C) COPYRIGHT 2014 Milandr *********/

/* END OF FILE main.c */
