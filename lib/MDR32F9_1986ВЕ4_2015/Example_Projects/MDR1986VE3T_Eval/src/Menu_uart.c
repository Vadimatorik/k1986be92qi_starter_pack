/**
  ******************************************************************************
  * @file    Menu_uart.c
  * @author  Milandr Application Team
  * @version V1.2.0
  * @date    09.09.2010
  * @brief   This file contains all the "UART" menu handlers.
  *          Only UART1 is used in this example; output transmitter line
  *          UARTTXD is shortcutted to UARTRXD receiver input.
  ******************************************************************************
  * <br><br>
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, Milandr SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 Milandr</center></h2>
  */
/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_config.h"
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_uart.h>
#include "Menu.h"
#include "Menu_items.h"
#include "leds.h"
#include "lcd.h"
#include "text.h"
#include "joystick.h"
#include "MDR1986VE3_it.h"

/** @addtogroup __MDR1986VE3_Eval_Demo MDR1986VE3 Demonstration Example
  * @{
  */

/** @addtogroup Menu Menu
  * @{
  */

/** @addtogroup Menu_UART Menu UART
  * @{
  */

/** @defgroup Menu_UART_Private_Constants Menu UART Private Constants
  * @{
  */

#define SEND_STRING_START_COLUMN         6
#define SEND_STRING_LINE                 4
#define SEND_STRING_LINE_OFFS            8
#define RECEIVE_STRING_START_COLUMN      6
#define RECEIVE_STRING_LINE              5
#define RECEIVE_STRING_LINE_OFFS         10

#define SEND_STRING_SIZE                 14
#define SEND_BUFFER_SIZE                 (SEND_STRING_SIZE * SEND_STRING_SIZE)

#define RECEIVE_BUFFER_SIZE              SEND_BUFFER_SIZE

/* FIFO DMA Interrupt levels (possible values: 2,4,8,12,14) */
#define SEND_FIFO_LVL                    14
#define RECEIVE_FIFO_LVL                 14

/** @} */ /* End of group Menu_UART_Private_Constants */

/** @defgroup Menu_UART_Private_Types Menu UART Private Types
  * @{
  */

typedef enum {IT_On = 0, IT_Off = !IT_On} ITState;

/** @} */ /* End of group Menu_UART_Private_Types */

/** @defgroup Menu_UART_Private_Macros Menu UART Private Macros
  * @{
  */

#define FIFO_IT_LVL_TO_UART_IT_CONST(lvl) ((lvl) == 2  ? UART_IT_FIFO_LVL_2words :  \
                                           (lvl) == 4  ? UART_IT_FIFO_LVL_4words :  \
                                           (lvl) == 8  ? UART_IT_FIFO_LVL_8words :  \
                                           (lvl) == 12 ? UART_IT_FIFO_LVL_12words : \
                                           (lvl) == 14 ? UART_IT_FIFO_LVL_14words : \
                                           0xFFFF)    /* To invoke assert_param */

/** @} */ /* End of group Menu_UART_Private_Macros */

/** @defgroup Menu_UART_Private_Variables Menu UART Private Variables
  * @{
  */

static vuint8_t SendBuffer[SEND_BUFFER_SIZE];
static vuint8_t ReceiveBuffer[RECEIVE_BUFFER_SIZE];

static vuint32_t send_buffer_pos = 0;
static vuint32_t receive_buffer_pos = 0;

static vuint32_t error_flag = 0;

static uint8_t * SendData [4] = {
  "UP pressed    ",
  "DOWN pressed  ",
  "LEFT pressed  ",
  "RIGHT pressed "
};

static uint8_t * ErrorMessage [4] = {
  "Frame error   ",
  "Parity error  ",
  "Break line    ",
  "Overflow error"
};

static UART_InitTypeDef UARTInitStructure;

/** @} */ /* End of group Menu_UART_Private_Variables */

/** @defgroup Menu_UART_Private_Functions Menu UART Private Functions
  * @{
  */

/*******************************************************************************
* Function Name  : UARTConfiguration
* Description    : Configures the UART1.
*                : Configures the HCLK division factor and RTCHSE clock for UART1.
* Input          : IT_Flag - Interrupt status. This parameter can be one of the
*                : following values: IT_On, IT_Off.
* Output         : None
* Return         : None
*******************************************************************************/
void UARTConfiguration(ITState IT_Flag)
{
  /* Enable the RTCHSE clock on UART1 */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_UART2, ENABLE);

  /* Set the UART1 HCLK division factor */
  UART_BRGInit(MDR_UART2, UART_HCLKdiv1);

  UART_DeInit(MDR_UART2);

  if (IT_Flag == IT_On)
  {
    /* Enable interrupt on UART1 */
    NVIC_EnableIRQ(UART1_IRQn);
  }
  else
  {
    /* Disable interrupt on UART1 */
    NVIC_DisableIRQ(UART1_IRQn);
  }
}

/*******************************************************************************
* Function Name  : UARTHelp
* Description    : Prints hint to the screen.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UARTHelp(void)
{
  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;
  LCD_PUTS(0, 0,                           "Press: DOWN, LEFT, UP");
  LCD_PUTS(0, CurrentFont->Height + 2,     "or RIGHT keys, for   ");
  LCD_PUTS(0, CurrentFont->Height * 2 + 4, "start sending.       ");
  LCD_PUTS(0, CurrentFont->Height * 3 + 6, "Press BACK for return.");

  LCD_PUTS(0, CurrentFont->Height * 4 + 8, "Send:                ");
  LCD_PUTS(0, CurrentFont->Height * 5 + 8, "Rec.:                ");
}


/*******************************************************************************
* Function Name  : UARTDisplayError
* Description    : Prints the message about UART error on LCD
* Input          : flags - UART flags.
* Output         : None
* Return         : None
*******************************************************************************/
void UARTDisplayError(uint8_t flags)
{
  uint32_t i, j;

  for (i = flags, j = 0; i > 0; j++, i >>= 1)
  {
    if ((i & 0x01) != 0)
    {
      LCD_PUTS(CurrentFont->Width * RECEIVE_STRING_START_COLUMN,
               CurrentFont->Height * RECEIVE_STRING_LINE + RECEIVE_STRING_LINE_OFFS,
               ErrorMessage[j]);
      while (!KEY_PRESSED(SEL));
      WAIT_UNTIL_KEY_RELEASED(SEL);
    }
  }
}

/*******************************************************************************
* Function Name  : SenderFuncFIFODemo
* Description    : Sender interrupt handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SenderFuncFIFODemo(void)
{
  if (error_flag == 0)
  {
    for (; ((UART_GetFlagStatus (MDR_UART2, UART_FLAG_TXFF) == RESET) && (send_buffer_pos < SEND_BUFFER_SIZE)); send_buffer_pos++)
    {
      UART_SendData(MDR_UART2, SendBuffer[send_buffer_pos]);
    }
  }
}

/*******************************************************************************
* Function Name  : ReceiverFuncFIFODemo
* Description    : Receiver interrupt handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ReceiverFuncFIFODemo(void)
{
  uint16_t receive_data;

  if (error_flag == 0)
  {
    for (; ((UART_GetFlagStatus(MDR_UART2, UART_FLAG_RXFE) == RESET) && (receive_buffer_pos < RECEIVE_BUFFER_SIZE) && (error_flag == 0));
             receive_buffer_pos++)
    {
      receive_data = UART_ReceiveData(MDR_UART2);

      /* Check for errors */
      if (UART_Flags(receive_data) != 0)
      {
        /* Print appropriate messages on LCD in case of errors */
        UARTDisplayError(UART_Flags(receive_data));
        error_flag = 1;
      }
      else
      {
        ReceiveBuffer[receive_buffer_pos] = UART_Data(receive_data);
      }
    }
  }
}

/*******************************************************************************
* Function Name  : UARTwFIFOFunc
* Description    : Demonstration of UART utilization with FIFO and interrupts.
*                : Waits for joystick key press and calls sender interrupt
*                : handler to initiate send/receive process. Prints sent and
*                : received data on LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UARTwFIFOFunc(void) {
  uint8_t *pdata;
  uint8_t  lcd_string[SEND_STRING_SIZE + 1];
  uint32_t key, i, data_size;
  uint32_t send_string_pos, receive_string_pos;

  UARTConfiguration(IT_On);

  /* UART1 configuration */
  UARTInitStructure.UART_BaudRate                = 115200;
  UARTInitStructure.UART_WordLength              = UART_WordLength8b;
  UARTInitStructure.UART_StopBits                = UART_StopBits1;
  UARTInitStructure.UART_Parity                  = UART_Parity_No;
  UARTInitStructure.UART_FIFOMode                = UART_FIFO_ON;
  /* With LBE bit set, output line of UARTTXD transmitter becomes to be bound to
   * UARTRXD receiver input */
  UARTInitStructure.UART_HardwareFlowControl     = UART_HardwareFlowControl_RXE | \
                                                   UART_HardwareFlowControl_TXE | \
                                                   UART_HardwareFlowControl_LBE;

  UART_Init (MDR_UART2,&UARTInitStructure);

  /* Clear FIFO */
  while(UART_GetFlagStatus(MDR_UART2, UART_FLAG_RXFE) != 1){
	  UART_ReceiveData(MDR_UART2);
  }

  /* Set interrupt handlers */
  pfUARTReceiverFunc = ReceiverFuncFIFODemo;
  pfUARTSenderFunc = SenderFuncFIFODemo;

  /* Enable sender and receiver interrupts */
  UART_ITConfig (MDR_UART2, UART_IT_TX | UART_IT_RX, ENABLE);

  /* Adjust sender and receiver interrupt levels */
  UART_DMAConfig (MDR_UART2, FIFO_IT_LVL_TO_UART_IT_CONST(RECEIVE_FIFO_LVL),
                         FIFO_IT_LVL_TO_UART_IT_CONST(SEND_FIFO_LVL));
  /* Enable DMA interrupts */
  UART_DMACmd(MDR_UART2, UART_DMA_TXE | UART_DMA_RXE, ENABLE);

  UART_Cmd(MDR_UART2,ENABLE);

  UARTHelp();

  key = GetKey();
  for (; key != BACK; key = GetKey())
  {
    if ((key != NOKEY) && (key != MULTIPLE))
    {
      /* Form strings to be transmitted in the buffer.
       * An algorithm is the following: copy data_size symbols
       * from the corresponding SendData array element;
       * fill the rest with '#' symbols. */
      pdata = SendData[key - 1];
      for (send_string_pos = 0, data_size = 1; send_string_pos < SEND_BUFFER_SIZE; data_size++)
      {
        for (i = 0; i < data_size; send_string_pos++, i++)
        {
          SendBuffer[send_string_pos] = pdata[i];
        }
        for (; ((i < SEND_STRING_SIZE) && (send_string_pos < SEND_BUFFER_SIZE)); send_string_pos++, i++)
        {
          SendBuffer[send_string_pos] = '#';
        }
      }

      error_flag = 0;

      receive_string_pos = 0;
      receive_buffer_pos = 182;
      send_string_pos = 0;
      send_buffer_pos = 182;

      /* Initiate transmit */
      SenderFuncFIFODemo();

      /* Interrupt-based processing */
      while ((receive_buffer_pos < (RECEIVE_BUFFER_SIZE - RECEIVE_FIFO_LVL)) && (error_flag == 0))
      {
        /* Process send buffer to output transmitted strings to LCD */
        if ((send_buffer_pos - send_string_pos) >= SEND_STRING_SIZE)
        {
          for (i = 0; i < SEND_STRING_SIZE; i++, send_string_pos++)
          {
            lcd_string[i] = SendBuffer[send_string_pos];
          }
          lcd_string[i] = 0x00;
          /* Print string on LCD */
          LCD_PUTS(CurrentFont->Width * (SEND_STRING_START_COLUMN),
                   CurrentFont->Height * SEND_STRING_LINE + SEND_STRING_LINE_OFFS,
                   lcd_string);
        }

        /* Process receiver buffer to output transmitted strings to LCD */
        if ((receive_buffer_pos - receive_string_pos) >= SEND_STRING_SIZE)
        {
          for (i = 0; i < SEND_STRING_SIZE; i++, receive_string_pos++)
          {
            lcd_string[i] = ReceiveBuffer[receive_string_pos];
          }
          lcd_string[i] = 0x00;
          /* Print string on LCD */
          LCD_PUTS(CurrentFont->Width * (RECEIVE_STRING_START_COLUMN),
                   CurrentFont->Height * RECEIVE_STRING_LINE + RECEIVE_STRING_LINE_OFFS,
                   lcd_string);
        }
      }
      /* Print on LCD remaining strings (from send buffer) */
      while ((send_buffer_pos - send_string_pos) >= SEND_STRING_SIZE)
      {
        for (i = 0; i < SEND_STRING_SIZE; i++, send_string_pos++)
        {
          lcd_string[i] = SendBuffer[send_string_pos];
        }
        lcd_string[i] = 0x00;
        /* Print string on LCD */
        LCD_PUTS(CurrentFont->Width * (SEND_STRING_START_COLUMN),
                 CurrentFont->Height * SEND_STRING_LINE + SEND_STRING_LINE_OFFS,
                 lcd_string);
      }
      /* Read data not handled by interrupts */
      while ((receive_buffer_pos < RECEIVE_BUFFER_SIZE) && (error_flag == 0))
      {
        ReceiverFuncFIFODemo();
      }
      while ((receive_string_pos < receive_buffer_pos) && (error_flag == 0))
      {
          for (i = 0; ((i < SEND_STRING_SIZE) && (receive_string_pos < receive_buffer_pos)); i++, receive_string_pos++)
          {
            lcd_string[i] = ReceiveBuffer[receive_string_pos];
          }
          lcd_string[i] = 0x00;
          /* Print string on LCD */
          LCD_PUTS(CurrentFont->Width * (RECEIVE_STRING_START_COLUMN),
                   CurrentFont->Height * RECEIVE_STRING_LINE + RECEIVE_STRING_LINE_OFFS,
                   lcd_string);
      }

    }
    WAIT_UNTIL_KEY_RELEASED(key);
  }

  UART_Cmd(MDR_UART2,DISABLE);
  DisplayMenu();
}

/*******************************************************************************
* Function Name  : UARTFunc
* Description    : Demonstration of UART utilization without FIFO and interrupts.
*                : Waits for joystick key press, then sends byte-per-byte
*                : corresponding string to LCD (Send: string) and to UART1 transmitter.
*                : Reads data from UART1 receiver and prints it on LCD (Rec.: string)
*                : If error is detected, aborts the transmition.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UARTFunc(void) {
  uint32_t key, i;
  uint8_t * pdata;
  uint16_t receive_data;

  UARTConfiguration(IT_Off);

  /* UART1 configuration */
  UARTInitStructure.UART_BaudRate                = 115200;
  UARTInitStructure.UART_WordLength              = UART_WordLength8b;
  UARTInitStructure.UART_StopBits                = UART_StopBits1;
  UARTInitStructure.UART_Parity                  = UART_Parity_No;
  UARTInitStructure.UART_FIFOMode                = UART_FIFO_OFF;
  /* With LBE bit set, output line of UARTTXD transmitter becomes to be bound to
   * UARTRXD receiver input */
  UARTInitStructure.UART_HardwareFlowControl     = UART_HardwareFlowControl_RXE | \
                                                   UART_HardwareFlowControl_TXE | \
                                                   UART_HardwareFlowControl_LBE;

  UART_Init (MDR_UART2,&UARTInitStructure);
  UART_Cmd(MDR_UART2,ENABLE);

  UARTHelp();

  key = GetKey();
  for (; key != BACK; key = GetKey())
  {
    if ((key != NOKEY) && (key != MULTIPLE))
    {
      /* The receiver buffer may be non-empty, so clean it */
      while (UART_GetFlagStatus (MDR_UART2, UART_FLAG_RXFF) == SET)
      {
        UART_ReceiveData (MDR_UART2);
      }

      error_flag = 0;
      for (pdata = SendData[key - 1], i = 0; ((*pdata != 0) && (error_flag == 0)); pdata++, i++)
      {
        LCD_PUTC(CurrentFont->Width * (SEND_STRING_START_COLUMN + i),
                 CurrentFont->Height * SEND_STRING_LINE + SEND_STRING_LINE_OFFS,
                 *pdata);
        UART_SendData (MDR_UART2, *pdata);
        /* Wait for transmition end */
        while (UART_GetFlagStatus (MDR_UART2, UART_FLAG_TXFF) == SET);
        while (UART_GetFlagStatus (MDR_UART2, UART_FLAG_BUSY) == SET);
        /* Wait for any data in the receiver buffer */
        while (UART_GetFlagStatus (MDR_UART2, UART_FLAG_RXFE) == SET);
        receive_data = UART_ReceiveData (MDR_UART2);

        /* Check for errors */
        if (UART_Flags(receive_data) != 0)
        {
          /* If there are an error, print error message on LCD */
          UARTDisplayError(UART_Flags(receive_data));
          error_flag = 1;
        }
        else
        {
          /* If there are no errors, print the symbol */
          LCD_PUTC(CurrentFont->Width * (RECEIVE_STRING_START_COLUMN + i),
                   CurrentFont->Height * RECEIVE_STRING_LINE + RECEIVE_STRING_LINE_OFFS,
                   UART_Data(receive_data));
        }
      }
    }
    WAIT_UNTIL_KEY_RELEASED(key);
  }

  UART_Cmd(MDR_UART2,DISABLE);
  DisplayMenu();
}

/** @} */ /* End of group Menu_UART_Private_Functions */

/** @} */ /* End of group Menu_UART */

/** @} */ /* End of group Menu */

/** @} */ /* End of group __MDR1986VE3_Eval_Demo */

/******************* (C) COPYRIGHT 2010 Milandr *******************
*
* END OF FILE Menu_uart.c */


