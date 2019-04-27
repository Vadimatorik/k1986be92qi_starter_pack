/**
  ******************************************************************************
  * @file    Menu_VCOM.c
  * @author  Milandr Application Team
  * @version V1.2.0
  * @date    12.09.2013
  * @brief   This file contains all the "USB VCOM" menu handlers.
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
#include "MDR32F9Qx_config.h"
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_uart.h>
#include <MDR32F9Qx_usb_handlers.h>
#include "systick.h"
#include "Menu.h"
#include "Menu_items.h"
#include "leds.h"
#include "lcd.h"
#include "text.h"
#include "joystick.h"
#include "demo_init.h"
#include "MDR1986VE3_it.h"

/** @addtogroup __MDR1986VE3_Eval_Demo MDR1986VE3 Demonstration Example
  * @{
  */

/** @addtogroup Menu Menu
  * @{
  */

/** @addtogroup Menu_USB Menu USB VCOM
  * @{
  */

/** @defgroup Menu_USB_Private_Constants Menu USB VCOM Private Constants
  * @{
  */

#define BUFFER_LENGTH                        100

#define UART                                 MDR_UART2
#define RST_CLK_PCLK_UART                    RST_CLK_PCLK_UART2
#define UART_IRQn                            UART2_IRQn

/** @} */ /* End of group Menu_USB_Private_Constants */

/** @defgroup Menu_USB_Private_Types Menu USB VCOM Private Types
  * @{
  */

/** @} */ /* End of group Menu_USB_Private_Types */

/** @defgroup Menu_USB_Private_Macros Menu USB VCOM Private Macros
  * @{
  */

/** @} */ /* End of group Menu_USB_Private_Macros */

/** @defgroup Menu_USB_Private_Variables Menu USB VCOM Private Variables
  * @{
  */

static uint8_t SendBuffer[BUFFER_LENGTH];
static uint8_t ReceiveBuffer[BUFFER_LENGTH];

static vuint32_t send_data_length = 0;
static vuint32_t send_data_pos = 0;
static vuint32_t receive_data_length = 0;

PORT_InitTypeDef PORT_InitStructure;
USB_Clock_TypeDef USB_Clock_InitStruct;
USB_DeviceBUSParam_TypeDef USB_DeviceBUSParam;

static UART_InitTypeDef UARTInitStructure;

static uint32_t temp_CPU_CLOCK, temp_PLL_CONTROL;

#ifdef USB_CDC_LINE_CODING_SUPPORTED
static USB_CDC_LineCoding_TypeDef LineCoding;
#endif /* USB_CDC_LINE_CODING_SUPPORTED */

/** @} */ /* End of group Menu_USB_Private_Variables */

/** @defgroup Menu_USB_Private_Functions Menu USB VCOM Private Functions
  * @{
  */

/* Private function prototypes -----------------------------------------------*/
static void Setup_CPU_Clock(void);
static void Setup_USB(void);
static void UARTConfiguration(void);
static void SenderFunc(void);
static void ReceiverFunc(void);
#ifdef USB_CDC_STATE_REPORTING_SUPPORTED
static void LineStateFunc(uint32_t events);
#endif /* USB_CDC_STATE_REPORTING_SUPPORTED */

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Setup_CPU_Clock
* Description    : Frequencies setup
* Output         : None
* Return         : USB_Result
*******************************************************************************/
static void Setup_CPU_Clock(void)
{
  /* Enable HSE */
  RST_CLK_HSEconfig(RST_CLK_HSE_ON);
  if (RST_CLK_HSEstatus() != SUCCESS)
  {
    /* Trap */
    while (1)
    {
    }
  }

  /* CPU_C1_SEL = HSE */
  RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul10);
  RST_CLK_CPU_PLLcmd(ENABLE);
  if (RST_CLK_CPU_PLLstatus() != SUCCESS)
  {
    /* Trap */
    while (1)
    {
    }
  }

  /* CPU_C3_SEL = CPU_C2_SEL */
  RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);
  /* CPU_C2_SEL = PLL */
  RST_CLK_CPU_PLLuse(ENABLE);
  /* HCLK_SEL = CPU_C3_SEL */
  RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
}

/*******************************************************************************
* Function Name  : Setup_USB
* Description    : USB Device layer setup and powering on
* Output         : None
* Return         : USB_Result
*******************************************************************************/
static void Setup_USB(void)
{
  /* Enables the CPU_CLK clock on USB */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_USB, ENABLE);

  /* Device layer initialization */
  USB_Clock_InitStruct.USB_USBC1_Source = USB_C1HSEdiv2;
  USB_Clock_InitStruct.USB_PLLUSBMUL    = USB_PLLUSBMUL12;

  USB_DeviceBUSParam.MODE  = USB_SC_SCFSP_Full;
  USB_DeviceBUSParam.SPEED = USB_SC_SCFSR_12Mb;
  USB_DeviceBUSParam.PULL  = USB_HSCR_DP_PULLUP_Set;

  USB_DeviceInit(&USB_Clock_InitStruct, &USB_DeviceBUSParam);

  /* Enable all USB interrupts */
  USB_SetSIM(USB_SIS_Msk);

  USB_DevicePowerOn();

  /* Enable interrupt on USB */
#ifdef USB_INT_HANDLE_REQUIRED
  NVIC_EnableIRQ(USB_IRQn);
#endif /* USB_INT_HANDLE_REQUIRED */

  USB_DEVICE_HANDLE_RESET;
}


/*******************************************************************************
* Function Name  : USB_CDC_RecieveData
* Description    : CDC data reception handler.
*                : Transfers received data to UART
* Output         : None
* Return         : USB_Result
*******************************************************************************/
USB_Result USB_CDC_RecieveData(uint8_t* Buffer, uint32_t Length)
{
  /* Initiate UART transmission */
  send_data_length = Length;
  send_data_pos = 0;

  SenderFunc();

  return USB_SUCCESS;
}


#ifdef USB_CDC_LINE_CODING_SUPPORTED

/*******************************************************************************
* Function Name  : USB_CDC_GetLineCoding
* Description    : GetLineCoding CDC request handler.
*                : Sends back current line coding settings.
* Output         : None
* Return         : USB_Result
*******************************************************************************/
USB_Result USB_CDC_GetLineCoding(uint16_t wINDEX, USB_CDC_LineCoding_TypeDef* DATA)
{
  assert_param(DATA);
  if (wINDEX != 0)
  {
    /* Invalid interface */
    return USB_ERR_INV_REQ;
  }

  /* Just send back settings stored earlier */
  *DATA = LineCoding;

  return USB_SUCCESS;
}


/*******************************************************************************
* Function Name  : USB_CDC_SetLineCoding
* Description    : SetLineCoding CDC request handler.
*                : Stores received line coding settings and adjusts UART.
* Output         : None
* Return         : USB_Result
*******************************************************************************/
USB_Result USB_CDC_SetLineCoding(uint16_t wINDEX, const USB_CDC_LineCoding_TypeDef* DATA)
{
  assert_param(DATA);
  if (wINDEX != 0)
  {
    /* Invalid interface */
    return USB_ERR_INV_REQ;
  }

  /* Adjust UART settings */

  /* Baud rate */
  UARTInitStructure.UART_BaudRate = DATA->dwDTERate;

  /* Stop bits */
  switch (DATA->bCharFormat)
  {
    case USB_CDC_STOP_BITS1:
      UARTInitStructure.UART_StopBits = UART_StopBits1;
      break;
    case USB_CDC_STOP_BITS2:
      UARTInitStructure.UART_StopBits = UART_StopBits2;
      break;
    default :
      return USB_ERR_INV_REQ;
  }

  /* Parity */
  switch (DATA->bParityType)
  {
    case USB_CDC_PARITY_NONE:
      UARTInitStructure.UART_Parity = UART_Parity_No;
      break;
    case USB_CDC_PARITY_ODD:
      UARTInitStructure.UART_Parity = UART_Parity_Odd;
      break;
    case USB_CDC_PARITY_EVEN:
      UARTInitStructure.UART_Parity = UART_Parity_Even;
      break;
    case USB_CDC_PARITY_MARK:
      UARTInitStructure.UART_Parity = UART_Parity_0;
      break;
    case USB_CDC_PARITY_SPACE:
      UARTInitStructure.UART_Parity = UART_Parity_1;
      break;
    default :
      return USB_ERR_INV_REQ;
  }

  /* Data bits */
  switch (DATA->bDataBits)
  {
    case USB_CDC_DATA_BITS5:
      UARTInitStructure.UART_WordLength = UART_WordLength5b;
      break;
    case USB_CDC_DATA_BITS6:
      UARTInitStructure.UART_WordLength = UART_WordLength6b;
      break;
    case USB_CDC_DATA_BITS7:
      UARTInitStructure.UART_WordLength = UART_WordLength7b;
      break;
    case USB_CDC_DATA_BITS8:
      UARTInitStructure.UART_WordLength = UART_WordLength8b;
      break;
    default :
      return USB_ERR_INV_REQ;
  }

  /* Re-initialize UART */
  UART_Cmd(UART, DISABLE);
  UART_DeInit(UART);
  UART_Init(UART, &UARTInitStructure);
  /* Enable sender, receiver and line state interrupts */
  UART_ITConfig (UART, UART_IT_TX | UART_IT_RX
#ifdef USB_CDC_STATE_REPORTING_SUPPORTED
              | UART_LINE_STATE_EVENTS
#endif /* USB_CDC_STATE_REPORTING_SUPPORTED */
              , ENABLE);
  UART_Cmd(UART, ENABLE);

  /* On success, store new values for GetLineCoding request fastening */
  LineCoding = *DATA;

  return USB_SUCCESS;
}

#endif /* USB_CDC_LINE_CODING_SUPPORTED */

/*******************************************************************************
* Function Name  : UARTConfiguration
* Description    : Configures the UART.
*                : Configures the HCLK division factor and RTCHSE clock for UART.
* Output         : None
* Return         : None
*******************************************************************************/
static void UARTConfiguration(void)
{
  /* Enable the RTCHSE clock on UART */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_UART, ENABLE);

  /* Set the UART HCLK division factor */
  UART_BRGInit(UART, UART_HCLKdiv16);

  UART_DeInit(UART);

  /* Configure PORTD pins for data transfer to/from UART */
  PORT_StructInit(&PORT_InitStructure);
  PortInitStructure.PORT_Pin   = PORT_Pin_13 | PORT_Pin_14;
  PortInitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PortInitStructure.PORT_FUNC  = PORT_FUNC_MAIN;
  PortInitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;

  PORT_Init(MDR_PORTD, &PortInitStructure);
  /* Enable interrupt on UART */
  NVIC_EnableIRQ(UART_IRQn);
}

/*******************************************************************************
* Function Name  : VCOMHelp
* Description    : Prints hint to the screen.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void VCOMHelp(void)
{
  sFONT *OldFont = CurrentFont;
  LCD_Method OldMethod = CurrentMethod;

  LCD_CLS();
  CurrentMethod = MET_AND;
  CurrentFont = &Font_6x8;
  DisplayMenuTitle("MDR_USB. Virtual COM");
  WAIT_UNTIL_KEY_RELEASED(SEL);
  LCD_PUTS(0, CurrentFont->Height * 2 + 2,     " To stop Press BACK");

  CurrentMethod = OldMethod;
  CurrentFont = OldFont;
}

/*******************************************************************************
* Function Name  : SenderFunc
* Description    : Sender interrupt handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void SenderFunc(void)
{
  for (; (send_data_pos < send_data_length && (UART_GetFlagStatus (UART, UART_FLAG_TXFF) == RESET)); send_data_pos++)
  {
    UART_SendData(UART, SendBuffer[send_data_pos]);
  }
}

/*******************************************************************************
* Function Name  : ReceiverFunc
* Description    : Receiver interrupt handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void ReceiverFunc(void)
{
  uint16_t receive_data;

  /* Read data from UART */
  for (receive_data_length = 0; ((UART_GetFlagStatus(UART, UART_FLAG_RXFE) == RESET) && (receive_data_length < BUFFER_LENGTH)); )
  {
    receive_data = UART_ReceiveData(UART);

    if (UART_Flags(receive_data) == 0)
    {
      ReceiveBuffer[receive_data_length++] = UART_Data(receive_data);
    }
  }
  /* Initiate data portion sending via USB */
  USB_CDC_SendData(ReceiveBuffer, receive_data_length);
}

#ifdef USB_CDC_STATE_REPORTING_SUPPORTED
/*******************************************************************************
* Function Name  : LineStateFunc
* Description    : Line state event interrupt handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void LineStateFunc(uint32_t events)
{
  uint16_t lineState = 0;
  if (events & UART_IT_OE)
  {
  lineState |= USB_CDC_bOverRun;
  }
  if (events & UART_IT_BE)
  {
  lineState |= USB_CDC_bBreak;
  }
  if (events & UART_IT_PE)
  {
  lineState |= USB_CDC_bParity;
  }
  if (events & UART_IT_FE)
  {
  lineState |= USB_CDC_bFraming;
  }
  if (events & UART_IT_DSR)
  {
  lineState |= USB_CDC_bTxCarrier;
  }
  if (events & UART_IT_DCD)
  {
  lineState |= USB_CDC_bRxCarrier;
  }
  if (events & UART_IT_RI)
  {
  lineState |= USB_CDC_bRingSignal;
  }

  if (lineState)
  {
    USB_CDC_ReportState(lineState);
  }
}
#endif /* USB_CDC_STATE_REPORTING_SUPPORTED */

/*******************************************************************************
* Function Name  : VCOMFunc
* Description    : Demonstration of USB-to-UART VCOM bridge.
*                : Displays prompt on LCD, enables the bridge and waits for
*                : joystick SEL key pressed to stop bridging and return
*                : to main menu.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void VCOMFunc(void) {
  uint32_t key;

  /* Display prompt */
  VCOMHelp();

  /* Save current CPU CLOCK configuration */
  temp_CPU_CLOCK   = MDR_RST_CLK->CPU_CLOCK;
  temp_PLL_CONTROL = MDR_RST_CLK->PLL_CONTROL;

  RST_CLK_HSIcmd(ENABLE);
  RST_CLK_HSIstatus();
  RST_CLK_CPUclkSelection(RST_CLK_CPUclkHSI);

  Setup_CPU_Clock();

  UARTConfiguration();

  /* CDC layer initialization */
  USB_CDC_Init(SendBuffer, 1, SET);

  /* UART configuration */
  UARTInitStructure.UART_BaudRate                = 115200;
  UARTInitStructure.UART_WordLength              = UART_WordLength8b;
  UARTInitStructure.UART_StopBits                = UART_StopBits1;
  UARTInitStructure.UART_Parity                  = UART_Parity_No;
  UARTInitStructure.UART_FIFOMode                = UART_FIFO_OFF;
  UARTInitStructure.UART_HardwareFlowControl     = UART_HardwareFlowControl_RXE | \
                                                   UART_HardwareFlowControl_TXE;
  /* With LBE bit set, output line of UARTTXD transmitter becomes to be bound to
   * UARTRXD receiver input. In order to run this example with UART physically
   * connected to PC, just comment this line */
/*  UARTInitStructure.UART_HardwareFlowControl     |= UART_HardwareFlowControl_LBE; */

  UART_Init (UART,&UARTInitStructure);

#ifdef USB_CDC_LINE_CODING_SUPPORTED
  /* Set line coding initial settings accordingly to UART ones above */
  LineCoding.dwDTERate = UARTInitStructure.UART_BaudRate;
  LineCoding.bCharFormat = USB_CDC_STOP_BITS1;
  LineCoding.bParityType = USB_CDC_PARITY_NONE;
  LineCoding.bDataBits = USB_CDC_DATA_BITS8;
#endif /* USB_CDC_LINE_CODING_SUPPORTED */

  /* Set interrupt handlers */
  pfUARTReceiverFunc = ReceiverFunc;
  pfUARTSenderFunc = SenderFunc;
#ifdef USB_CDC_STATE_REPORTING_SUPPORTED
  pfUARTLineStateFunc = LineStateFunc;
#endif /* USB_CDC_STATE_REPORTING_SUPPORTED */

  /* Enable sender, receiver and line state interrupts */
  UART_ITConfig (UART, UART_IT_TX | UART_IT_RX
#ifdef USB_CDC_STATE_REPORTING_SUPPORTED
              | UART_LINE_STATE_EVENTS
#endif /* USB_CDC_STATE_REPORTING_SUPPORTED */
              , ENABLE);

  /* Enable bridge */
  UART_Cmd(UART, ENABLE);
  Setup_USB();

  /* Wait for SEL to quit */
  key = GetKey();
  for (; key != BACK; key = GetKey())
  {
  }
  WAIT_UNTIL_KEY_RELEASED(SEL);

  /* Disable bridge */
  UART_Cmd(UART, DISABLE);

  USB_CDC_ReceiveStop();
  USB_DevicePowerOff();

  /* Restore original CPU CLOCK configuration */
  MDR_RST_CLK->CPU_CLOCK   = temp_CPU_CLOCK;
  MDR_RST_CLK->PLL_CONTROL = temp_PLL_CONTROL;

  DisplayMenu();
}


/** @} */ /* End of group Menu_USB_Private_Functions */

/** @} */ /* End of group Menu_USB */

/** @} */ /* End of group Menu */

/** @} */ /* End of group __MDR1986VE3_Eval_Demo */

/******************* (C) COPYRIGHT 2013 Milandr *******************
*
* END OF FILE Menu_VCOM.c */

