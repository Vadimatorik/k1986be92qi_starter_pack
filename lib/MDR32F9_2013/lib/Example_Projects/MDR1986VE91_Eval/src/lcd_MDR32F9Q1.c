/**
  ******************************************************************************
  * @file    lcd_MDR32F9Q1.c
  * @author  Phyton Application Team
  * @version V3.0.0
  * @date    10.09.2011
  * @brief   This file provides all the LCD driver functions for MDR32F9Q1_Rev0
  *          and MDR32F9Q1_Rev1 evaluation boards (LCD is connected to EBC).
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

#if defined (USE_MDR32F9Q1_Rev0) || defined (USE_MDR32F9Q1_Rev1)

/** @addtogroup __MDR32F9Qx_Eval_Demo MDR32F9Qx Demonstration Example
  * @{
  */

/** @addtogroup LCD_Driver LCD Driver
  * @{
  */

/** @defgroup __MDR32F9Q1_LCD MDR32F9Q1 evaluation boards specific
  * @{
  */

/** @defgroup __MDR32F9Q1_LCD_Private_Constants MDR32F9Q1 LCD Private Constants
  * @{
  */

#define EXTBUS_BASE         0x10000000
#define LCD_CRYSTAL1_OFFS   0x100000
#define LCD_CRYSTAL2_OFFS   0x200000
#define LCD_DATA_OFFS       0x8000000
#define LCD_CRYSTAL1_CMD    EXTBUS_BASE + LCD_CRYSTAL1_OFFS
#define LCD_CRYSTAL2_CMD    EXTBUS_BASE + LCD_CRYSTAL2_OFFS
#define LCD_CRYSTAL1_DATA   EXTBUS_BASE + LCD_CRYSTAL1_OFFS + LCD_DATA_OFFS
#define LCD_CRYSTAL2_DATA   EXTBUS_BASE + LCD_CRYSTAL2_OFFS + LCD_DATA_OFFS

/** @} */ /* End of group __MDR32F9Q1_LCD_Private_Constants */

/** @defgroup __MDR32F9Q1_LCD_Private_Macros MDR32F9Q1 LCD Private Macros
  * @{
  */

#define WAIT_BUSY           WhileStatus(LCD_BUSY_Msk)
#define WAIT_RESET          WhileStatus(LCD_RESET_Msk)
#define WAIT_ON             WhileStatus(LCD_ONOFF_Msk)

/** @} */ /* End of group __MDR32F9Q1_LCD_Private_Macros */

/** @defgroup __MDR32F9Q1_LCD_Variables MDR32F9Q1 LCD Variables
  * @{
  */

/* LCD ports */
const LCD_Ports CrystalPorts[NUM_LCD_CRYSTALS] = {
  /* Crystal #1 */
  { LCD_CRYSTAL1_DATA,
    LCD_CRYSTAL1_CMD },
  /* Crystal #2 */
  { LCD_CRYSTAL2_DATA,
    LCD_CRYSTAL2_CMD }
};

/* Display context */
LCD_Crystal CurrentCrystal = LCD_CRYSTAL1;  /*!< Currently selected crystal */
LCD_Method CurrentMethod = MET_AND;         /*!< Current display method    */

/** @} */ /* End of group __MDR32F9Q1_LCD_Variables */

/** @defgroup __MDR32F9Q1_LCD_Private_Functions MDR32F9Q1 LCD Private Functions
  * @{
  */

/* Private function prototypes -----------------------------------------------*/
static uint32_t GetStatus(void);
static void WhileStatus(uint32_t status);
static void Pause(void);

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : ResetLCD
* Description    : Resets the LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ResetLCD(void)
{
  PORT_SetBits(MDR_PORTC, PORT_Pin_9);
  PORT_ResetBits(MDR_PORTC, PORT_Pin_9);
  Pause();
  PORT_SetBits(MDR_PORTC, PORT_Pin_9);
  WhileStatus(LCD_BUSY_Msk | LCD_RESET_Msk);
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
  PORT_Write(MDR_PORTE, ((num + 1) << 4));
  WAIT_BUSY;
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
  LCD_CMD(CurrentCrystal) = val;
  WAIT_BUSY;
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
  LCD_DATA(CurrentCrystal) = val;
  WAIT_BUSY;
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
  uint32_t ret = LCD_CMD(CurrentCrystal);

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
  LCD_DATA(CurrentCrystal);     /* First reading is necessary to get correct data */
  WAIT_BUSY;
  ret = LCD_DATA(CurrentCrystal);
  WAIT_BUSY;
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
* Description    : Clears the LCD screen.
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

/** @} */ /* End of group __MDR32F9Q1_LCD_Private_Functions */

/** @} */ /* End of group __MDR32F9Q1_LCD */

/** @} */ /* End of group __MDR32F9Q1_LCD_Driver */

/** @} */ /* End of group __MDR32F9Qx_Eval_Demo */

#endif /* USE_MDR32F9Q1_Rev0 || USE_MDR32F9Q1_Rev1 */

/******************* (C) COPYRIGHT 2011 Phyton *********************************
*
* END OF FILE lcd_MDR32F9Q1.c */

