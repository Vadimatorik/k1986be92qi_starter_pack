/**
  ******************************************************************************
  * @file    Examples/MDR32F9Q2_EVAL/CAN/LoopBack_RTR/main.c
  * @author  Milandr Application Team
  * @version V1.2.0
  * @date    13/09/2011
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
  * <h2><center>&copy; COPYRIGHT 2011 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32Fx.h"
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_board.h"
#include "MDR32F9Qx_can.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_it.h"

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F9Q2_EVAL MDR32F9Q2 Evaluation Board
  * @{
  */

/** @addtogroup CAN_LoopBack_RTR_92 CAN_LoopBack_RTR
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/
#define LED1            PORT_Pin_0
#define LED2            PORT_Pin_1
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t ret = 0; /* for return of the interrupt handling */
__IO uint32_t rx_buf = 0;
__IO uint32_t rtr_request_buf = 1;
__IO uint32_t rtr_reply_buf = 2;
volatile TestStatus TestRx;
PORT_InitTypeDef PORT_InitStructure;
/* Private function prototypes -----------------------------------------------*/
TestStatus CAN_Interrupt(void);
void LEDOn(uint32_t LED_Num);
void LEDOff(uint32_t LED_Num);
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
uint32_t main(void)
{
  RST_CLK_DeInit();
  /* Select HSI/2 as CPU_CLK source*/
  RST_CLK_CPU_PLLconfig (RST_CLK_CPU_PLLsrcHSIdiv2,0);
  /* Periph clocks enable */
  RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_CAN1),ENABLE);
  RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC,ENABLE);

  /* Reset PORTC settings */
  PORT_DeInit(MDR_PORTC);

  /* Configure PORTC pin 0,1 for output to switch LED on/off */
  PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_Pin   = PORT_Pin_0 | PORT_Pin_1;
  PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
  PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;
  PORT_Init(MDR_PORTC, &PORT_InitStructure);

/* CAN transmit at 500Kb/s and receive by interrupt in loopback mode */
  TestRx = CAN_Interrupt();
  if (TestRx == FAILED)
  {
    /* Turn on led LED2 */
    LEDOn(LED2);
  }
  else
  {
    /* Turn on led LED1 */
    LEDOn(LED1);
  }

  while(1);
}
/**
  * @brief  Configures the CAN, transmit and receive using interrupt.
  * @param  None
  * @retval PASSED if the reception is well done, FAILED in other case
  */
TestStatus CAN_Interrupt(void)
{
  CAN_InitTypeDef  sCAN;
  CAN_TxMsgTypeDef TxMsg;
  CAN_RTRReplyTypeDef RTRReply;
  CAN_RTRMessageTypeDef RTRMes;
  CAN_FilterInitTypeDef Filter;
  uint32_t i = 0;

  /* Set the HCLK division factor = 1 for CAN1*/
  CAN_BRGInit(MDR_CAN1,CAN_HCLKdiv1);

  /* CAN register init */
  CAN_DeInit(MDR_CAN1);

  /* CAN cell init */
  CAN_StructInit (&sCAN);

  sCAN.CAN_ROP  = ENABLE;
  sCAN.CAN_SAP  = ENABLE;
  sCAN.CAN_STM  = ENABLE;
  sCAN.CAN_ROM  = DISABLE;
  sCAN.CAN_PSEG = CAN_PSEG_Mul_2TQ;
  sCAN.CAN_SEG1 = CAN_SEG1_Mul_3TQ;
  sCAN.CAN_SEG2 = CAN_SEG2_Mul_2TQ;
  sCAN.CAN_SJW  = CAN_SJW_Mul_2TQ;
  sCAN.CAN_SB   = CAN_SB_3_SAMPLE;
  sCAN.CAN_BRP  = 1;
  CAN_Init (MDR_CAN1,&sCAN);

  CAN_Cmd(MDR_CAN1, ENABLE);

    /* Turn on led LED2 */
  NVIC_EnableIRQ(CAN1_IRQn);
  /* Enable CAN1 GLB_INT and RX_INT interrupts */
  CAN_ITConfig( MDR_CAN1, CAN_IT_GLBINTEN | CAN_IT_RXINTEN, ENABLE);

  /* Enable CAN1 interrupt from receive buffer */
  CAN_RxITConfig( MDR_CAN1 ,(1<<rx_buf), ENABLE);

  /* config buffer for receive RTR reply*/
  CAN_Receive(MDR_CAN1, rx_buf, DISABLE);
  Filter.Filter_ID = 0x00005678;
  Filter.Mask_ID = 0x0000FFFF;
  CAN_FilterInit(MDR_CAN1, rx_buf, &Filter);

  /* config buffer for transmit RTR reply*/
  RTRReply.ID = 0x00005678;
  RTRReply.IDE = CAN_ID_EXT;
  RTRReply.DLC = 2;
  RTRReply.Data[0] = 0x7777;
  RTRReply.Data[1] = 0x0;

  CAN_RTRReply(MDR_CAN1, rtr_reply_buf, &RTRReply);

  Filter.Filter_ID = 0x00001234;
  Filter.Mask_ID = 0x0000FFFF;
  CAN_FilterInit(MDR_CAN1, rtr_reply_buf, &Filter);

  /* config buffer for transmit RTR request*/
  RTRMes.ID = 0x00001234;
  RTRMes.IDE = CAN_ID_EXT;
  RTRMes.PRIOR_0 = DISABLE;

  /* transmit RTR*/
  CAN_SendRTR(MDR_CAN1, rtr_request_buf, &RTRMes);

  /* initialize the value that will be returned */
  ret = 0xFF;

  /* receive message with interrupt handling */
  i=0;
  while((ret == 0xFF) && (i < 0xFFF))
  {
    i++;
  }

  if (i == 0xFFF)
  {
    ret=0;
  }

  /* disable interrupt handling */
  CAN_ITConfig(MDR_CAN1, CAN_IT_GLBINTEN | CAN_IT_RXINTEN, DISABLE);

  return (TestStatus)ret;

}
/**
  * @brief  Turns selected LED On.
  * @param  LED_Num: Specifies the Led to be set on.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  * @retval None
  */
void LEDOn(uint32_t LED_Num)
{
  PORT_SetBits(MDR_PORTC, LED_Num);
}
/**
  * @brief  Turns selected LED Off.
  * @param  LED_Num: Specifies the Led to be set off.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  * @retval None
  */
void LEDOff(uint32_t LED_Num)
{
  PORT_ResetBits(MDR_PORTC, LED_Num);
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

/** @} */ /* End of group CAN_LoopBack_92 */

/** @} */ /* End of group __MDR32F9Q2_EVAL */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2011 Milandr *********/

/* END OF FILE main.c */

