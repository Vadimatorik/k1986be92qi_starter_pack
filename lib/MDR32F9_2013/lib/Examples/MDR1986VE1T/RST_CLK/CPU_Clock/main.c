/**
 ******************************************************************************
 * @file    Examples/MDR1986VE1T_EVAL/RST_CLK/CPU_Clock/main.c
 * @author  Milandr Application Team
 * @version V1.2.0
 * @date    04/07/2013
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

/** @addtogroup __MDR1986VE1T_EVAL MDR1986VE1T Opora Evaluation Board
 * @{
 */

/** @addtogroup RST_CLK_CPU_Clock_1T RST_CLK_CPU_Clock
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BLINK_NUM 5
#define BLINK_DELAY 40000

#define LED1            PORT_Pin_7
#define LED2            PORT_Pin_8
#define LED3            PORT_Pin_9

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
RST_CLK_FreqTypeDef CLK_FrequencyStructure;
PORT_InitTypeDef PORT_InitStructure;

/* Private function prototypes -----------------------------------------------*/
void Delay ( __IO uint32_t nCount );

/* Private functions ---------------------------------------------------------*/

void LEDOn ( uint32_t LED_Num )
{
	PORT_SetBits(MDR_PORTD, LED_Num);
}

void LEDOff ( uint32_t LED_Num )
{
	PORT_ResetBits(MDR_PORTD, LED_Num);
}

/**
 * @brief  Blink with LED1
 * @param  num - blinks number
 * @param  del - delay
 * @retval None
 */
void BlinkLED1 ( uint32_t num, uint32_t del )
{
	uint32_t cnt;

	for (cnt = 0; cnt < num; cnt++) {
		LEDOn(LED1);
		Delay(del);
		LEDOff(LED1);
		Delay(del);
	}
}

/**
 * @brief  Indicate error condition with LED3
 * @param  None
 * @retval None
 */
void IndicateError ( void )
{
	/* Switch LED3 on and off in case of error */
	LEDOn(LED3);
	Delay(BLINK_DELAY);
	LEDOff(LED3);
}

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
void main ( void )
{

	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);

	/* Configure all unused PORT pins to low power consumption */

	PORT_StructInit(&PORT_InitStructure);
	PORT_InitStructure.PORT_Pin = (PORT_Pin_All
			& ~(PORT_Pin_7 | PORT_Pin_8 | PORT_Pin_9 | PORT_Pin_10
					| PORT_Pin_11));
	PORT_Init(MDR_PORTD, &PORT_InitStructure);

	/* Configure PORTD pins 7..11 for output to switch LEDs on/off */
	PORT_InitStructure.PORT_Pin = (PORT_Pin_7 | PORT_Pin_8 | PORT_Pin_9
			| PORT_Pin_10 | PORT_Pin_11);
	PORT_InitStructure.PORT_OE = PORT_OE_OUT;
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

	PORT_Init(MDR_PORTD, &PORT_InitStructure);

	/* Consequently turn all three used LEDs on and off */

	LEDOn(LED1);
	Delay(4 * BLINK_DELAY);
	LEDOff(LED1);
	Delay(4 * BLINK_DELAY);
	LEDOn(LED2);
	Delay(4 * BLINK_DELAY);
	LEDOff(LED2);
	Delay(4 * BLINK_DELAY);
	LEDOn(LED3);
	Delay(4 * BLINK_DELAY);
	LEDOff(LED3);
	Delay(4 * BLINK_DELAY);

	/* Infinite loop that demonstrates different input clock sources using */

	while (1) {
		/* Set RST_CLK to default */
		RST_CLK_DeInit();
		RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);

		/* 1. CPU_CLK = HSI clock */

		/* Enable HSI clock source */
		RST_CLK_HSIcmd(ENABLE);
		/* Switch LED2 on and wait for HSI ready status */
		LEDOn(LED2);
		Delay(BLINK_DELAY);
		if (RST_CLK_HSIstatus() == SUCCESS) /* Good HSI clock */
		{
			/* Switch LED2 off */
			LEDOff(LED2);
			/* Select HSI clock on the CPU clock MUX */
			RST_CLK_CPUclkSelection(RST_CLK_CPUclkHSI );
			/* LED1 blinking with HSI clock as input clock source */
			BlinkLED1(BLINK_NUM, BLINK_DELAY);
		}
		else /* HSI timeout */
		{
			IndicateError();
		}

		/* 2. CPU_CLK = HSI/2 clock */

		/* Enable HSI clock source */
		RST_CLK_HSIcmd(ENABLE);
		/* Disable CPU_PLL */
		RST_CLK_CPU_PLLcmd(DISABLE);
		/* Select HSI/2 clock as CPU_PLL input clock source */
		RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSIdiv2, 1);
		/* Switch LED2 on and wait for HSI ready status */
		LEDOn(LED2);
		Delay(BLINK_DELAY);
		if (RST_CLK_HSIstatus() == SUCCESS) /* Good HSI clock */
		{
			/* Switch LED2 off */
			LEDOff(LED2);
			/* Set CPU_C3_prescaler to 1 */
			RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1 );
			/* Switch CPU_C2_SEL to CPU_C1 clock instead of CPU_PLL output */
			RST_CLK_CPU_PLLuse(DISABLE);
			/* LED1 blinking with HSI/2 clock as input clock source */
			BlinkLED1(BLINK_NUM, BLINK_DELAY);
		}
		else /* HSI timeout */
		{
			IndicateError();
		}

		/* 3. CPU_CLK = 7*HSE/2 clock */

		/* Enable HSE clock oscillator */
		RST_CLK_HSEconfig(RST_CLK_HSE_ON );
		/* Switch LED2 on and wait for HSE ready status */
		LEDOn(LED2);
		Delay(BLINK_DELAY);
		if (RST_CLK_HSEstatus() == SUCCESS) /* Good HSE clock */
		{
			/* Select HSE clock as CPU_PLL input clock source */
			/* Set PLL multiplier to 7                        */
			RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, 7);
			/* Enable CPU_PLL */
			RST_CLK_CPU_PLLcmd(ENABLE);
			/* Switch LED2 on and wait for PLL ready status */
			if (RST_CLK_HSEstatus() == SUCCESS) /* Good CPU PLL */
			{
				/* Switch LED2 off */
				LEDOff(LED2);
				/* Set CPU_C3_prescaler to 2 */
				RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV2 );
				/* Set CPU_C2_SEL to CPU_PLL output instead of CPU_C1 clock */
				RST_CLK_CPU_PLLuse(ENABLE);
				/* LED1 blinking with 7*HSE/2 clock as input clock source */
				BlinkLED1(BLINK_NUM, BLINK_DELAY);
			}
			else /* CPU_PLL timeout */
			{
				IndicateError();
			}
		}
		else /* HSE timeout */
		{
			IndicateError();
		}

		/* 4. CPU_CLK = LSI clock */

		/* Enable LSI clock source */
		RST_CLK_LSIcmd(ENABLE);
		/* Switch LED2 on and wait for LSI ready status */
		LEDOn(LED2);
		Delay(BLINK_DELAY);
		if (RST_CLK_LSIstatus() == SUCCESS) /* Good LSI clock */
		{
			/* Switch LED2 off */
			LEDOff(LED2);
			/* Select LSI clock on the CPU clock MUX */
			RST_CLK_CPUclkSelection(RST_CLK_CPUclkLSI );
			/* LED1 blinking with LSI clock as input clock source */
			BlinkLED1(BLINK_NUM, BLINK_DELAY);
		}
		else /* LSI timeout */
		{
			IndicateError();
		}
	}
}

/**
 * @brief  Executes delay loop.
 * @param  nCount: specifies the delay.
 * @retval None
 */
void Delay ( __IO uint32_t nCount )
{
	for (; nCount != 0; nCount--)
		;
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

/** @} *//* End of group RST_CLK_CPU_Clock_1T */

/** @} *//* End of group __MDR1986VE1T_EVAL */

/** @} *//* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2013 Milandr *********/

/* END OF FILE main.c */

