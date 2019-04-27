/**
  ******************************************************************************
  * @file    lcd_MDR32F9Qx.c
  * @author  Phyton Application Team
  * @version V3.0.0
  * @date    10.09.2011
  * @brief   This file provides all the LCD driver functions for MDR32F9Q2_Rev0,
  *          MDR32F9Q2_Rev1, MDR32F9Q3_Rev0 and MDR32F9Q3_Rev1 evaluation boards.
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
#include "lcd.h"

#if defined (USE_MDR32F9Q2_Rev0)  || defined (USE_MDR32F9Q2_Rev1) || \
    defined (USE_MDR32F9Q3_Rev0) || defined (USE_MDR32F9Q3_Rev1)

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
  * @{
  */

/** @addtogroup LCD_Driver LCD Driver
  * @{
  */

/** @defgroup __MDR32F9Qx_LCD MDR32F9Q2Y and MDR32F9Q3Y evaluation boards specific
  * @{
  */

/** @defgroup __MDR32F9Qx_LCD_Private_Constants MDR32F9Qx LCD Private Constants
  * @{
  */

#define LCD_DATA_BAS_8  (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 | \
                         PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_6 | PORT_Pin_7)

/** @} */ /* End of group __MDR32F9Qx_LCD_Private_Constants */

/** @defgroup __MDR32F9Qx_LCD_Private_Macros MDR32F9Qx LCD Private Macros
  * @{
  */

#define WAIT_BUSY           WhileStatus(LCD_BUSY_Msk)
#define WAIT_RESET          WhileStatus(LCD_RESET_Msk)
#define WAIT_ON             WhileStatus(LCD_ONOFF_Msk)

/** @} */ /* End of group __MDR32F9Qx_LCD_Private_Macros */

/** @defgroup __MDR32F9Qx_LCD_Variables MDR32F9Qx LCD Variables
  * @{
  */

/* Display context */
LCD_Crystal CurrentCrystal = LCD_CRYSTAL1;  /*!< Currently selected crystal */
LCD_Method CurrentMethod;                   /*!< Current display method    */

/** @} */ /* End of group __MDR32F9Qx_LCD_Variables */

/** @defgroup __MDR32F9Qx_LCD_Private_Functions MDR32F9Qx LCD Private Functions
  * @{
  */

/* Private function prototypes -----------------------------------------------*/
static uint32_t GetStatus(void);
static void WhileStatus(uint32_t status);
static void Pause(void);

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : LCDClock
* Description    : Gating data.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCDClock(void)
{
  PORT_SetBits(LCD_CLOCK_PORT, LCD_CLOCK_PIN);
  PORT_ResetBits(LCD_CLOCK_PORT, LCD_CLOCK_PIN);
}

/*******************************************************************************
* Function Name  : ResetLCD
* Description    : Resets the LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ResetLCD(void)
{
  PORT_SetBits(LCD_RESET_PORT, LCD_RESET_PIN);
  PORT_ResetBits(LCD_RESET_PORT, LCD_RESET_PIN);
  Pause();
  PORT_SetBits(LCD_RESET_PORT, LCD_RESET_PIN);
}

/*******************************************************************************
* Function Name  : SetCrystal
* Description    : Sets the current LCD crystal.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SetCrystal(LCD_Crystal num)
{
  PORT_ResetBits(LCD_CRYSTAL_PORT, LCD_CRYSTAL_PINs);
  PORT_SetBits(LCD_CRYSTAL_PORT, ((num + 1) << LCD_CRYSTAL_POS));
  LCDClock();
  CurrentCrystal = num;
}

/*******************************************************************************
* Function Name  : WriteLCD_Cmd
* Description    : Writes command to the current LCD crystal.
* Input          : LCD command
* Output         : None
* Return         : None
*******************************************************************************/
void WriteLCD_Cmd(uint32_t val)
{
  uint32_t portdata;

  portdata = PORT_ReadInputData(LCD_DATA_PORT) & (~LCD_DATA_BAS_8);
  portdata |= val;
  /* Switch LCD to the command mode */
  PORT_ResetBits(LCD_CMD_DATA_PORT, LCD_CMD_DATA_PIN);
  /* Switch LCD to the data input mode */
  PORT_ResetBits(LCD_RD_WR_PORT, LCD_RD_WR_PIN);

  PORT_Write(LCD_DATA_PORT, portdata);
  /* Switch LCD_DATA_PORT to the data output mode */
  LCD_DATA_PORT->OE |= LCD_DATA_BAS_8;

  LCDClock();

  /* Switch LCD_DATA_PORT to the data input mode */
  LCD_DATA_PORT->OE &= ~LCD_DATA_BAS_8;

  /* Switch LCD to the data output mode */
  PORT_SetBits(LCD_RD_WR_PORT, LCD_RD_WR_PIN);
}

/*******************************************************************************
* Function Name  : WriteLCD_Data
* Description    : Writes data to the current LCD crystal.
* Input          : Data
* Output         : None
* Return         : None
*******************************************************************************/
void WriteLCD_Data(uint32_t val)
{
  uint32_t portdata;

  portdata = PORT_ReadInputData(LCD_DATA_PORT) & (~LCD_DATA_BAS_8);
  portdata |= val;
  /* Switch LCD to the data mode */
  PORT_SetBits(LCD_CMD_DATA_PORT, LCD_CMD_DATA_PIN);
  /* Switch LCD to the data input mode */
  PORT_ResetBits(LCD_RD_WR_PORT, LCD_RD_WR_PIN);

  PORT_Write(LCD_DATA_PORT, portdata);
  /* Switch LCD_DATA_PORT to the data output mode */
  LCD_DATA_PORT->OE |= LCD_DATA_BAS_8;

  LCDClock();

  /* Switch LCD_DATA_PORT to the data input mode */
  LCD_DATA_PORT->OE &= ~LCD_DATA_BAS_8;

  /* Switch LCD to the data output mode */
  PORT_SetBits(LCD_RD_WR_PORT, LCD_RD_WR_PIN);
}

/*******************************************************************************
* Function Name  : ReadLCD_Cmd
* Description    : Reads command from the current LCD crystal.
* Input          : None
* Output         : None
* Return         : LCD command
*******************************************************************************/
uint32_t ReadLCD_Cmd(void)
{
  uint32_t ret;

  /* Switch LCD to the command mode */
  PORT_ResetBits(LCD_CMD_DATA_PORT, LCD_CMD_DATA_PIN);

  PORT_SetBits(LCD_CLOCK_PORT, LCD_CLOCK_PIN);
  ret = PORT_ReadInputData(LCD_DATA_PORT) & LCD_DATA_BAS_8;
  PORT_ResetBits(LCD_CLOCK_PORT, LCD_CLOCK_PIN);

  return ret;
}

/*******************************************************************************
* Function Name  : ReadLCD_Data
* Description    : Reads data from the current LCD crystal.
* Input          : None
* Output         : None
* Return         : LCD data
*******************************************************************************/
uint32_t ReadLCD_Data()
{
  uint32_t ret;

  /* Switch LCD to the data mode */
  PORT_SetBits(LCD_CMD_DATA_PORT, LCD_CMD_DATA_PIN);
  LCDClock();              /* Dummy reading is necessary to get correct data */
  PORT_SetBits(LCD_CLOCK_PORT, LCD_CLOCK_PIN);
  ret = PORT_ReadInputData(LCD_DATA_PORT) & LCD_DATA_BAS_8;
  PORT_ResetBits(LCD_CLOCK_PORT, LCD_CLOCK_PIN);

  return ret;
}

/*******************************************************************************
* Function Name  : LCD_INIT
* Description    : Initializes all LCD crystals.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_INIT(void)
{
  uint32_t crystal;

  ResetLCD();

  for (crystal = LCD_CRYSTAL1; crystal < NUM_LCD_CRYSTALS; crystal++)
  {
    SetCrystal((LCD_Crystal)crystal);
    WAIT_BUSY;
    LCD_ON;
    WAIT_ON;
    LCD_START_LINE(0);
  }
}

/*******************************************************************************
* Function Name  : LCD_CLS
* Description    : Clears LCD screen.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_CLS(void)
{
  uint32_t i, j, crystal;

  for (crystal = LCD_CRYSTAL1; crystal < NUM_LCD_CRYSTALS; crystal++)
  {
    SetCrystal((LCD_Crystal)crystal);
    WAIT_BUSY;
    LCD_OFF;
    LCD_SET_ADDRESS(0);
    for (i = 0; i < 8; i++)
    {
      LCD_SET_PAGE(i);
      for (j = 0; j < 64; j++)
      {
        WriteLCD_Data(0x00);
      }
    }
    LCD_ON;
  }
}

/*******************************************************************************
* Function Name  : GetStatus
* Description    : Returns the current LCD status.
* Input          : None
* Output         : None
* Return         : LCD status
*******************************************************************************/
static uint32_t GetStatus(void)
{
  uint32_t ret;

  ret = ReadLCD_Cmd();
  return ret;
}

/*******************************************************************************
* Function Name  : WhileStatus
* Description    : Wait until the specific LCD status changes.
* Input          : LCD status. This parameter can be one of the following
*                : values: LCD_BUSY, LCD_ONOFF, LCD_RESET.
* Output         : None
* Return         : None
*******************************************************************************/
static void WhileStatus(uint32_t status)
{

  uint32_t stat;
  for (stat = GetStatus(); (stat & status) != 0; stat = GetStatus())
  {
  }
}

/*******************************************************************************
* Function Name  : Pause
* Description    : Delay for approx. 15*3 CPU clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Pause(void)
{
  vuint32_t i;

  for (i = 15; i > 0; i--);
}

/** @} */ /* End of group __MDR32F9Qx_LCD_Private_Functions */

/** @} */ /* End of group __MDR32F9Qx_LCD */

/** @} */ /* End of group LCD_Driver */

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

#endif /* USE_MDR32F9Q2_Rev0  || USE_MDR32F9Q2_Rev1 ||
        * USE_MDR32F9Q3_Rev0 || USE_MDR32F9Q3_Rev1 */

/******************* (C) COPYRIGHT 2011 Phyton *********************************
*
* END OF FILE lcd_MDR32F9Qx.c */

