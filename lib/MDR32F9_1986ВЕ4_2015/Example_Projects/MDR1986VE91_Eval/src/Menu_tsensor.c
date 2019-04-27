/**
  ******************************************************************************
  * @file    Menu_tsensor.c
  * @author  Phyton Application Team
  * @version V1.2.0
  * @date    21.10.2011
  * @brief   This file contains all the "Temperature" menu handlers.
  ******************************************************************************
  * <br><br>
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, PHYTON SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 Phyton</center></h2>
  */
/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_config.h"
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_adc.h>
#include "adc.h"
#include "Menu.h"
#include "Menu_items.h"
#include "lcd.h"
#include "text.h"
#include "joystick.h"
#include "systick.h"
#include "MDR32F9Qx_it.h"

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
  * @{
  */

/** @addtogroup Menu Menu
  * @{
  */

/** @addtogroup Menu_TSENSOR Menu TSENSOR
  * @{
  */

/** @defgroup Menu_TSENSOR_Private_Constants Menu TSENSOR Private Constants
  * @{
  */

/* Value ARC1_RESULT for 25° C */
#define V_25                             1700
/* Average Slope of the temperature curve */
#define Average_Slope                    6

#define Temp_Display_Column              33

/** @} */ /* End of group Menu_TSENSOR_Private_Constants */

/** @defgroup Menu_TSENSOR_Private_Types Menu TSENSOR Private Types
  * @{
  */

/** @} */ /* End of group Menu_TSENSOR_Private_Types */

/** @defgroup Menu_TSENSOR_Private_Macros Menu TSENSOR Private Macros
  * @{
  */


/** @} */ /* End of group Menu_TSENSOR_Private_Macros */

/** @defgroup Menu_TSENSOR_Private_Variables Menu TSENSOR Private Variables
  * @{
  */

static uint8_t  TempCelsius_Display[] = "    .    C";
static uint8_t  TempFahrenheit_Display[] = "    .    F";
static int32_t  Temp_Decimal, TempCelsius_Value, Temp_Value_Fahrenheit;

/** @} */ /* End of group Menu_TSENSOR_Private_Variables */

/** @defgroup Menu_TSENSOR_Private_Functions Menu TSENSOR Private Functions
  * @{
  */

/*******************************************************************************
* Function Name  : TSENSORFunc
* Description    : Demonstration of TSENSOR utilization.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TSENSORFunc(void)
{
  uint32_t key;
  uint32_t curr_ADC1_Value = 0;
  int32_t V_Since;

  sFONT *OldFont = CurrentFont;
  LCD_Method OldMethod = CurrentMethod;

  /* Print header */
  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;
  DisplayMenuTitle("Temperature");
  WAIT_UNTIL_KEY_RELEASED(SEL);

  /* Configure the Temperature Sensor */
  ADC_Temp_Sensor_Config();

  /* Enable interrupt on ADC */
  NVIC_EnableIRQ(ADC_IRQn);
  /* ADC1 enable */
  ADC1_Cmd(ENABLE);

  key = GetKey();

  /* Enable ADC1 end of conversion interrupt */
  ADC1_ITConfig(ADC1_FLAG_END_OF_CONVERSION, ENABLE);

  for (; key != SEL; key = GetKey())
  {
    ADC1_Value = ADC1_GetResult();
    if (!ADC1_Value)
    {
    	continue;
    }

    if (curr_ADC1_Value != ADC1_Value)
    {
			curr_ADC1_Value = ADC1_Value;

			/* Check that ADC1_Value contains data from TSENSOR measuring conversion */
			if (((ADC1_Value & ADC_RESULT_CHANNEL_Msk) >> ADC_RESULT_CHANNEL_Pos) == ADC_CH_TEMP_SENSOR)
			{
				V_Since = ADC1_Value & ADC_RESULT_Msk;

				TempCelsius_Value = (((V_Since - V_25) * 1000) / (Average_Slope * 1000)) + 25 * 1000;
				if (TempCelsius_Value < 0)
				{
					/* Negative temperature measured */
					TempCelsius_Display[0]='-';
					TempCelsius_Value = -TempCelsius_Value;
				}
				else
				{
					/* Positive temperature measured */
					TempCelsius_Display[0]='+';
				}
				Temp_Decimal = TempCelsius_Value % 1000;

				/* Convert temperature in Celsius to Fahrenheit */
				Temp_Value_Fahrenheit = (9 * TempCelsius_Value / 5) + 32000;
				if (Temp_Value_Fahrenheit < 0)
				{
					/* Negative temperature measured */
					TempFahrenheit_Display[0]='-';
					Temp_Value_Fahrenheit = -Temp_Value_Fahrenheit;
				}
				else
				{
					/* Positive temperature measured */
					TempFahrenheit_Display[0]='+';
				}

				TempCelsius_Value     = TempCelsius_Value / 1000;
				/* Calculate temperature digits in Celsius */
				TempCelsius_Display[1] = (TempCelsius_Value / 100) + 0x30;
				TempCelsius_Display[2] = ((TempCelsius_Value % 100) / 10) + 0x30;
				TempCelsius_Display[3] = ((TempCelsius_Value % 100) % 10) + 0x30;
				TempCelsius_Display[5] = (Temp_Decimal / 100) + 0x30;
				TempCelsius_Display[6] = ((Temp_Decimal % 100) / 10) + 0x30;
				TempCelsius_Display[7] = ((Temp_Decimal % 100) % 10) + 0x30;

				Temp_Decimal = Temp_Value_Fahrenheit % 1000;
				Temp_Value_Fahrenheit = Temp_Value_Fahrenheit / 1000;
				/* Calculate temperature digits in Fahrenheit */
				TempFahrenheit_Display[1] = (Temp_Value_Fahrenheit / 100) + 0x30;
				TempFahrenheit_Display[2] = ((Temp_Value_Fahrenheit % 100) / 10) + 0x30;
				TempFahrenheit_Display[3] = ((Temp_Value_Fahrenheit % 100) % 10) + 0x30;
				TempFahrenheit_Display[5] = (Temp_Decimal / 100) + 0x30;
				TempFahrenheit_Display[6] = ((Temp_Decimal % 100) / 10) + 0x30;
				TempFahrenheit_Display[7] = ((Temp_Decimal % 100) % 10) + 0x30;

				/* Display temperature value on LCD */
				LCD_PUTS(Temp_Display_Column, CurrentFont->Height * 4, TempCelsius_Display);
				LCD_PUTS(Temp_Display_Column, CurrentFont->Height * 5 + 2, TempFahrenheit_Display);
			}
    }
		ADC1_Value = 0;
	  /* Re-enable ADC1 end of conversion interrupt */
	  ADC1_ITConfig(ADC1_FLAG_END_OF_CONVERSION, ENABLE);
  }

  CurrentFont = OldFont;
  CurrentMethod = OldMethod;

  /* Disable interrupt on ADC */
  NVIC_DisableIRQ(ADC_IRQn);
  /* Disable ADC end of conversion interrupt */
  ADC1_ITConfig(ADC1_FLAG_END_OF_CONVERSION, DISABLE);
  /* ADC1 disable */
  ADC1_Cmd(DISABLE);
  DisplayMenu();
}

/** @} */ /* End of group Menu_TSENSOR_Private_Functions */

/** @} */ /* End of group Menu_TSENSOR */

/** @} */ /* End of group Menu */

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

/******************* (C) COPYRIGHT 2010 Phyton *******************
*
* END OF FILE Menu_tsensor.c */
