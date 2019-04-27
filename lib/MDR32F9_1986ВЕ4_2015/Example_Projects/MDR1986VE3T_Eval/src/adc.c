/**
  ******************************************************************************
  * @file    adc.c
  * @author  Milandr Application Team
  * @version V3.0.0
  * @date    09.09.2013
  * @brief   This file contains all the utilities for work with ADC
  ******************************************************************************
  * <br><br>
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, Milandr SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2013 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_adc.h>
#include "demo_init.h"
#include "MDR32F9Qx_board.h"

/** @addtogroup __MDR1986VE3_Eval_Demo MDR1986VE3 Demonstration Example
  * @{
  */

/** @addtogroup ADC_Routines ADC Routines
  * @{
  */

/** @defgroup ADC_Private_Constants ADC Private Constants
  * @{
  */

/** @} */ /* End of group ADC_Private_Constants */

/** @defgroup ADC_Variables ADC Variables
  * @{
  */

/* ADC Init structures */
ADC_InitTypeDef  ADC_InitStructure;
ADCx_InitTypeDef ADCx_InitStructure;

/** @} */ /* End of group ADC_Variables */

/** @defgroup ADC_Private_Functions ADC Private Functions
  * @{
  */

/*******************************************************************************
* Function Name  : ADC_Config
* Description    : Configure the ADC1 for TRIM using.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_Config(void)
{
  /* Enable the RTCHSE clock on ADC1 */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_ADC, ENABLE);

  /* ADC Configuration */
  /* Reset all ADC settings */
  ADC_DeInit();

  ADC_StructInit(&ADC_InitStructure);
  /* Use base voltage source to reduce the power consumption,
   * thus enable the temperature sensor */
  ADC_InitStructure.ADC_TempSensor           = ADC_TEMP_SENSOR_Enable;
  ADC_Init(&ADC_InitStructure);

  ADCx_StructInit(&ADCx_InitStructure);

  /* Enable ADC cyclic mode */
  ADCx_InitStructure.ADC_SamplingMode     = ADC_SAMPLING_MODE_CICLIC_CONV;
  ADCx_InitStructure.ADC_ChannelNumber    = ADC_CH_ADC7;
  ADC1_Init(&ADCx_InitStructure);
}

/*******************************************************************************
* Function Name  : ADC_Temp_Sensor_Config
* Description    : Configure the ADC1 for temperature sensor reading.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_Temp_Sensor_Config(void)
{
  /* Enable the RTCHSE clock on ADC1 */
  RST_CLK_PCLKcmd((RST_CLK_PCLK_ADC), ENABLE);

  /* ADC Configuration */
  /* Reset all ADC settings */
  ADC_DeInit();

  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_TempSensor           = ADC_TEMP_SENSOR_Enable;
  ADC_InitStructure.ADC_TempSensorAmplifier  = ADC_TEMP_SENSOR_AMPLIFIER_Enable;
  ADC_InitStructure.ADC_TempSensorConversion = ADC_TEMP_SENSOR_CONVERSION_Enable;

  ADC_Init (&ADC_InitStructure);
  ADCx_InitStructure.ADC_SamplingMode     = ADC_SAMPLING_MODE_CICLIC_CONV;
  ADCx_InitStructure.ADC_ChannelNumber    = ADC_CH_TEMP_SENSOR;
  ADCx_InitStructure.ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_EXACT;
  ADCx_InitStructure.ADC_Prescaler        = ADC_CLK_div_32768;
  ADCx_InitStructure.ADC_DelayGo          = 0x7;
  ADC1_Init (&ADCx_InitStructure);
}

/** @} */ /* End of group ADC_Private_Functions */

/** @} */ /* End of group ADC_Routines */

/** @} */ /* End of group __MDR1986VE3_Eval_Demo */

/******************* (C) COPYRIGHT 2013 Milandr *********************************
*
* END OF FILE adc.c */

