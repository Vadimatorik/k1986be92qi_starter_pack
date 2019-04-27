/**
  ******************************************************************************
  * @file	 main.c
  * @author	 sidorov.a
  * @version {version}
  * @date    01.04.2013
  * @brief   Main program body. 
  ******************************************************************************
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2013 Milandr </center></h2>
  ******************************************************************************
  * FILE main.c
  */

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR1986VE3_EVAL MDR1986VE3 Complexity Evaluation Board
  * @{
  */

/** @addtogroup Ethernet_X2 Ethernet_X2
 *  @{
 */

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_eeprom.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_uart.h"
#include "MDR32F9Qx_eth.h"
#include "MDR32F9Qx_timer.h"
#include "tcpip.h"


/*
#define MAC2_5				0x20
#define MAC2_4				0x6A
#define MAC2_3				0x8A
#define MAC2_2				0x16
#define MAC2_1				0xD2
#define MAC2_0				0x63
*/

#define MAC2_5				0xC8
#define MAC2_4				0x60
#define MAC2_3				0x00
#define MAC2_2				0x67
#define MAC2_1				0xB1
#define MAC2_0				0x6C



#define MY_MIL_STD_1553 MDR_MIL_STD_15531

#define ASSERT_INFO_FILE_ID FILEID__main_C

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define ONE_WORD_TIME_RECEIVING_mkS		20

/* Private macro -------------------------------------------------------------*/
#if defined (_USE_DEBUG_UART_)
		#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
		#define GETCHAR_PROTOTYPE int fgetc(         FILE *f)
	#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
	#define DEBUG_PRINTF(...)
#endif /* #if defined _USE_DEBUG_UART_ */
/* Varibles ------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static PORT_InitTypeDef PORT_InitStructure;
/* Private function prototypes -----------------------------------------------*/
#if defined (_USE_DEBUG_UART_)
	void DebugUARTInit ();
#endif /* #if defined _USE_DEBUG_UART_ */
void ClockConfigure ( void );

extern uint32_t InputFrame[1514/4];
extern uint32_t InputFrame1[1514/4] ;
void ETH_InputPachetHandler(MDR_ETHERNET_TypeDef * ETHERNETx);
void CopyEthFrame(MDR_ETHERNET_TypeDef * ETHERNET_SRC, MDR_ETHERNET_TypeDef * ETHERNET_DST);
void CopyEThFrameWithFIFO(MDR_ETHERNET_TypeDef * ETHERNET_SRC, MDR_ETHERNET_TypeDef * ETHERNET_DST);

#define N 512
volatile uint32_t DataLen[N];
volatile uint32_t TimeLen[N];
uint32_t Packet[378 + 1];
static uint32_t count = 0;
static uint32_t OldTime = 0;
static uint32_t PacketCounterSend = 0;
static uint32_t PacketCounterRecive = 0;

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
	static ETH_InitTypeDef  ETH_InitStruct;

	ETH_StatusPacketReceptionTypeDef ETH_StatusPacketReceptionStruct;
	uint32_t PacketLength, i, Rhead, Xtail, EthBaseBufferAddr, * ptr_InputFrame, *ptr_OutputFrame;
	uint16_t BufferMode;
	int32_t EthReceiverFreeBufferSize;

	/* Configure CPU clock */
	ClockConfigure();

#if defined (_USE_DEBUG_UART_)
	DebugUARTInit();
#endif /* #if defined (_USE_DEBUG_UART_) */

/* Enable peripheral clocks --------------------------------------------------*/
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);
	/* Reset PORTB settings */
	PORT_DeInit(MDR_PORTB);
	/* Reset PORTH settings */
	PORT_DeInit(MDR_PORTH);

	/* LEDs Port Init */
	/* Configure PORTB pins 2,3,4,5,6,7 */
	PORT_InitStructure.PORT_Pin = ( PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_4 |
								    PORT_Pin_5 | PORT_Pin_6 | PORT_Pin_7 );
	PORT_InitStructure.PORT_MODE 	= PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_OE  	= PORT_OE_OUT;
	PORT_InitStructure.PORT_SPEED 	= PORT_SPEED_MAXFAST;
	PORT_InitStructure.PORT_FUNC 	= PORT_FUNC_PORT;
	PORT_InitStructure.PORT_PD 		= PORT_PD_DRIVER;
	PORT_Init(MDR_PORTB, &PORT_InitStructure);

	DEBUG_PRINTF("Init LEDs PORT ... Ok\r\n");

	/* Reset ehernet clock settings */
	ETH_ClockDeInit();

	RST_CLK_PCLKcmd(RST_CLK_PCLK_DMA, ENABLE);

	/* Enable HSE2 oscillator */
	RST_CLK_HSE2config(RST_CLK_HSE2_ON);
	if(RST_CLK_HSE2status() == ERROR)
		while(1); /* Infinite loop */

	/* Config PHY clock */
	ETH_PHY_ClockConfig(ETH_PHY_CLOCK_SOURCE_HSE2, ETH_PHY_HCLKdiv1);

	/* Init the BRG ETHERNET */
	ETH_BRGInit(ETH_HCLKdiv1);

	/* Enable the ETHERNET clock */
	ETH_ClockCMD(ETH_CLK1, ENABLE);
	ETH_ClockCMD(ETH_CLK2, ENABLE);

	/* Reset to default ethernet settings */
	ETH_DeInit(MDR_ETHERNET1);
	ETH_DeInit(MDR_ETHERNET2);

	/* Init ETH_InitStruct members with its default value */
	ETH_StructInit((ETH_InitTypeDef * ) &ETH_InitStruct);
	/* Set the speed of the chennel */
	/*ETH_InitStruct.ETH_PHY_Mode = ETH_PHY_MODE_100BaseT_Full_Duplex;*/
	ETH_InitStruct.ETH_PHY_Mode = ETH_PHY_MODE_AutoNegotiation;
	ETH_InitStruct.ETH_Pause = ENABLE;
	ETH_InitStruct.ETH_Transmitter_RST = SET;
	ETH_InitStruct.ETH_Receiver_RST = SET;
	/*ETH_InitStruct.ETH_Receive_All_Packets = ENABLE;*/

	/* Set the buffer mode */
	ETH_InitStruct.ETH_Buffer_Mode = ETH_BUFFER_MODE_LINEAR;
	ETH_InitStruct.ETH_Buffer_Mode = ETH_BUFFER_MODE_FIFO;

	ETH_InitStruct.ETH_Source_Addr_HASH_Filter = DISABLE;
	ETH_InitStruct.ETH_Automatic_CRC_Strip = ENABLE;
	ETH_InitStruct.ETH_Automatic_IPG = ENABLE;
	ETH_InitStruct.ETH_Retry_Counter = 0x0F;

	/*ETH_InitStruct.ETH_Error_CRC_Frames_Reception = ENABLE;*/
	/*ETH_InitStruct.ETH_DBG_Mode = ETH_DBG_MODE_STOP;*/

	/* Set the MAC address. */
	ETH_InitStruct.ETH_MAC_Address[2] = (MAC_0<<8)|MAC_1;
	ETH_InitStruct.ETH_MAC_Address[1] = (MAC_2<<8)|MAC_3;
	ETH_InitStruct.ETH_MAC_Address[0] = (MAC_4<<8)|MAC_5;

	/* Set the buffer size of transmitter and receiver */
	ETH_InitStruct.ETH_Dilimiter = 0x1000;
	ETH_InitStruct.ETH_Receive_All_Packets = ENABLE;

	/* Init the ETHERNET 1 */
	ETH_Init(MDR_ETHERNET1, (ETH_InitTypeDef *) &ETH_InitStruct);



	ETH_PHYCmd(MDR_ETHERNET1, ENABLE);

	/* Enable PHY module */
	//ETH_PHYCmd(MDR_ETHERNET2, ENABLE);

	/* Set the MAC address. */
	ETH_InitStruct.ETH_MAC_Address[2] = (MAC2_0<<8)|MAC2_1;
	ETH_InitStruct.ETH_MAC_Address[1] = (MAC2_2<<8)|MAC2_3;
	ETH_InitStruct.ETH_MAC_Address[0] = (MAC2_4<<8)|MAC2_5;
	ETH_Init(MDR_ETHERNET2, (ETH_InitTypeDef *) &ETH_InitStruct);


	/* Enable PHY module */
	ETH_PHYCmd(MDR_ETHERNET2, ENABLE);

	TCPLowLevelInit();

	/* Start the ETHERNET1 */
	ETH_Start(MDR_ETHERNET1);
	ETH_Start(MDR_ETHERNET2);

	__IO uint32_t * ptr_ETH2SendFIFO = (uint32_t *)0x3C000004;
	__IO uint32_t * ptr_ETH2RecFIFO = (uint32_t *)0x3C000000;
	__IO uint32_t * ptr_ETH1SendFIFO = (uint32_t *)0x38000004;
	__IO uint32_t * ptr_ETH1RecFIFO = (uint32_t *)0x38000000;

	static int32_t len = 0;
	static uint32_t data = 0;

	//len =  ETH_ReadPHYRegister(MDR_ETHERNET1, ETH_InitStruct.ETH_PHY_Address, PHY_BCR);
	//len = ETH_ReadPHYRegister(MDR_ETHERNET1, ETH_InitStruct.ETH_PHY_Address, PHY_BSR);

    static TIMER_CntInitTypeDef TIMER_CntInitStruct;

    RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER1, ENABLE);
    TIMER_BRGInit(MDR_TIMER1,TIMER_HCLKdiv128);
    TIMER_DeInit(MDR_TIMER1);
    TIMER_CntStructInit(&TIMER_CntInitStruct);
    TIMER_CntInitStruct.TIMER_Prescaler = 0;
    TIMER_CntInitStruct.TIMER_Period = 0xFFFFFFFF;
    TIMER_CntInitStruct.TIMER_CounterDirection = TIMER_CntDir_Up;
    TIMER_CntInitStruct.TIMER_IniCounter = 0;
    TIMER_CntInit(MDR_TIMER1, &TIMER_CntInitStruct);
    TIMER_CntEventSourceConfig(MDR_TIMER1, TIMER_EvSrc_TM1);

    TIMER_CntEventSourceConfig(MDR_TIMER2, TIMER_EvSrc_TM1);

    TIMER_Cmd(MDR_TIMER1, ENABLE);


    Packet[0] = 1512;
    Packet[1] = 0xFFFFFFFF;
    Packet[2] = 0xFFFF0102;

    for(int i = 0; i < 376; i++){
    	Packet[i + 3] = i;
    }

	//ETH_SendFrame(MDR_ETHERNET1, &Packet[0], Packet[0]);
	/*ETH_SendFrame(MDR_ETHERNET2, &Packet[0], Packet[0]);*/

/*
    volatile uint32_t kkk = 1000;
    while(kkk-- > 0);
*/




	/* Infinite loop */
	while(1){
#if 1

/*
		if(ETH_GetMACITStatus(MDR_ETHERNET1, ETH_MAC_IT_OVF))
			PORT_SetBits(MDR_PORTB, PORT_Pin_0);

		if(ETH_GetMACITStatus(MDR_ETHERNET2, ETH_MAC_IT_OVF))
			PORT_SetBits(MDR_PORTB, PORT_Pin_1);


		if(ETH_GetFlagStatus(MDR_ETHERNET1, ETH_MAC_FLAG_R_FULL))
			PORT_SetBits(MDR_PORTB, PORT_Pin_2);


		else
			PORT_ResetBits(MDR_PORTB, PORT_Pin_2);



		if(ETH_GetFlagStatus(MDR_ETHERNET1, ETH_MAC_FLAG_X_FULL))
			PORT_SetBits(MDR_PORTB, PORT_Pin_3);


		else
			PORT_ResetBits(MDR_PORTB, PORT_Pin_3);




		if(ETH_GetFlagStatus(MDR_ETHERNET2, ETH_MAC_FLAG_R_FULL))
			PORT_SetBits(MDR_PORTB, PORT_Pin_4);


		else
			PORT_ResetBits(MDR_PORTB, PORT_Pin_4);



		if(ETH_GetFlagStatus(MDR_ETHERNET2, ETH_MAC_FLAG_X_FULL))
			PORT_SetBits(MDR_PORTB, PORT_Pin_5);


		else
			PORT_ResetBits(MDR_PORTB, PORT_Pin_5);



		if(ETH_GetMACITStatus(MDR_ETHERNET1, ETH_MAC_IT_MISSED_F))
			PORT_SetBits(MDR_PORTB, PORT_Pin_6);
		else
			PORT_ResetBits(MDR_PORTB, PORT_Pin_6);

		if(ETH_GetMACITStatus(MDR_ETHERNET2, ETH_MAC_IT_MISSED_F))
			PORT_SetBits(MDR_PORTB, PORT_Pin_7);
		else
			PORT_ResetBits(MDR_PORTB, PORT_Pin_7);
*/

		/* Принимаем данные по первому интерфейсу */
		if(MDR_ETHERNET1->ETH_R_Head != MDR_ETHERNET1->ETH_R_Tail){
		//if(ETH_GetFlagStatus(MDR_ETHERNET1, ETH_MAC_IT_RF_OK)){

			/*OldTime = TIMER_GetCounter(MDR_TIMER1);*/
			/*InputFrame[0] = (0x0000FFFF & ETH_ReceivedFrame(MDR_ETHERNET1, (uint32_t *)&InputFrame[1])) - 4;*/
			/*DataLen[count] = InputFrame[0]*4;*/
			/*ETH_SendFrame(MDR_ETHERNET2, &InputFrame[0], InputFrame[0]);*/
			/*TimeLen[count] = TIMER_GetCounter(MDR_TIMER1) - OldTime;*/
			/*count = (count + 1)&(N-1);*/

			//CopyEthFrame(MDR_ETHERNET1, MDR_ETHERNET2);
			CopyEThFrameWithFIFO(MDR_ETHERNET1, MDR_ETHERNET2);
			/*ETH_SendFrame(MDR_ETHERNET1, &Packet[0], Packet[0]);*/

		}
		/* Принимаем данные по второму интерфейсу */
		if(MDR_ETHERNET2->ETH_R_Head != MDR_ETHERNET2->ETH_R_Tail){
		/*if(ETH_GetFlagStatus(MDR_ETHERNET2, ETH_MAC_IT_RF_OK)){*/

/*			OldTime = TIMER_GetCounter(MDR_TIMER1);*/
/*
			InputFrame[0] = 0x0000FFFF & ETH_ReceivedFrame(MDR_ETHERNET2, (uint32_t *)&InputFrame[1]) - 4;
			PacketCounterRecive++;
*/


/*			for(int i = 0; i < 378; i++){
				if(Packet[i+1] != InputFrame[i+1])
					PORT_SetBits(MDR_PORTB, PORT_Pin_0);
			}*/
			/*DataLen[count] = InputFrame[0]*4;*/
/*			ETH_SendFrame(MDR_ETHERNET1, &InputFrame[0], InputFrame[0]);*/
/*			TimeLen[count] = TIMER_GetCounter(MDR_TIMER1) - OldTime;*/
/*			count = (count + 1)&(N-1);*/


			//CopyEthFrame(MDR_ETHERNET2, MDR_ETHERNET1);
			CopyEThFrameWithFIFO(MDR_ETHERNET2, MDR_ETHERNET1);


		}
/*
		else{
			ETH_SendFrame(MDR_ETHERNET1, &Packet[0], Packet[0]);
			PacketCounterSend++;
			if(PacketCounterSend > (PacketCounterRecive + 1))
				PORT_SetBits(MDR_PORTB, PORT_Pin_3);
			volatile uint32_t ttt = 3000;
			while ((ttt--) > 0);
		}
*/
#else
		 ETH_InputPachetHandler(MDR_ETHERNET2);
		 DoNetworkStuff(MDR_ETHERNET2);
#endif
	}
}

void ETH_InputPachetHandler(MDR_ETHERNET_TypeDef * ETHERNETx){

	uint16_t status_reg;
	ETH_StatusPacketReceptionTypeDef ETH_StatusPacketReceptionStruct;

	/* Check that the packet is received */
	status_reg = ETH_GetMACITStatusRegister(ETHERNETx);

	if(ETHERNETx->ETH_R_Head != ETHERNETx->ETH_R_Tail){
	/*if(status_reg & ETH_MAC_FLAG_RF_OK )*/
		ETH_StatusPacketReceptionStruct.Status = ETH_ReceivedFrame(ETHERNETx, InputFrame);

		if(ETH_StatusPacketReceptionStruct.Fields.UCA)
			 ProcessEthIAFrame(InputFrame, ETH_StatusPacketReceptionStruct.Fields.Length);
		if(ETH_StatusPacketReceptionStruct.Fields.BCA)
			 ProcessEthBroadcastFrame(InputFrame, ETH_StatusPacketReceptionStruct.Fields.Length);

		ETH_StatusPacketReceptionStruct.Status = 0;
	}
}

void CopyEthFrame(MDR_ETHERNET_TypeDef * ETHERNET_SRC, MDR_ETHERNET_TypeDef * ETHERNET_DST)
{
	uint32_t Rhead, *ptr_InputFrame, EthBaseBufferAddr, Xtail, ptr_OutputFrame,  PacketLength;
	ETH_StatusPacketReceptionTypeDef ETH_StatusPacketReceptionStruct;


	uint32_t *ptr1;
	uint32_t *ptr2;

	volatile static uint32_t data1;

/*	OldTime = TIMER_GetCounter(MDR_TIMER1);*/

	Rhead = ETHERNET_SRC->ETH_R_Head;
	/* Set pointer to the status word reading message */
	ptr_InputFrame = (uint32_t *)((EthBaseBufferAddr = ((uint32_t)ETHERNET_SRC) + 0x08000000) + Rhead);
	/* Read the status of the receiving a packet */
	ETH_StatusPacketReceptionStruct.Status = (uint32_t)*ptr_InputFrame++;
	PacketLength = (ETH_StatusPacketReceptionStruct.Fields.Length + 3)/4;

	Xtail = ETHERNET_DST->ETH_X_Tail;
	/* Set pointer to output buffer */
	ptr_OutputFrame = (uint32_t )((((uint32_t)ETHERNET_DST) + 0x08000000));

	DataLen[count] = *(uint32_t*)((uint32_t)ptr_OutputFrame | Xtail) = ETH_StatusPacketReceptionStruct.Fields.Length - 4;

	/* Increase the write pointer */
	Xtail = ((Xtail + 4)&0x1FFF)|(0x01000);

	/* Read the input frame */
	uint32_t mask1 = EthBaseBufferAddr | 0xFFC;
	uint32_t mask2 = (uint32_t)ptr_OutputFrame | 0x1FFC;

	EthBaseBufferAddr += Rhead;
	ptr_OutputFrame   += Xtail;

	ptr1 = (uint32_t*)EthBaseBufferAddr;
	ptr2 = (uint32_t*)ptr_OutputFrame;

	while((PacketLength - 1) > 64){

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		PacketLength -= 64;
	}

	while((PacketLength - 1) > 16){

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);

		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);


		PacketLength -= 16;
	}


	for(int i = 0; i < PacketLength - 1; i++){


		*(uint32_t * ) ptr_OutputFrame  = *((uint32_t*)((EthBaseBufferAddr = (EthBaseBufferAddr + 4) & mask1)));
		ptr_OutputFrame = (((ptr_OutputFrame + 4) & mask2) | 0x01000);


	}
/*
	data1 = *((uint32_t*)(EthBaseBufferAddr | ((Rhead+=4)&0xFFC)));
	Rhead = (Rhead + 4 )&0xFFC;
*/

	data1 = *((uint32_t*)((EthBaseBufferAddr += 4) & mask1));

	Rhead = (EthBaseBufferAddr + 4 )&0xFFC;

	/* Set the new value of the ETH_R_Head register */
	ETHERNET_SRC->ETH_R_Head = Rhead&0xFFC;

	/*Xtail = ((Xtail + 4)&0x1FFF)|(0x01000);*/


	//Xtail = ((ptr_OutputFrame + 4)&0x1FFF)|(0x01000);
	Xtail = ((ptr_OutputFrame + 4)&0x1FFF)|(0x01000);


	/* Write the new value of the ETH_X_Tail register */
	ETHERNET_DST->ETH_X_Tail = Xtail;

/*
	TimeLen[count] = TIMER_GetCounter(MDR_TIMER1) - OldTime;
	count = (count + 1)&(N-1);*/
}


void CopyEThFrameWithFIFO(MDR_ETHERNET_TypeDef * ETHERNET_SRC, MDR_ETHERNET_TypeDef * ETHERNET_DST)
{
	volatile uint32_t *ptr_InputFrame, * ptr_OutputFrame,  PacketLength;
	ETH_StatusPacketReceptionTypeDef ETH_StatusPacketReceptionStruct;
	volatile static uint32_t data1;

/*	OldTime = TIMER_GetCounter(MDR_TIMER1);*/


	/* Set pointer to the status word reading message */
	ptr_InputFrame = (volatile uint32_t *)(((uint32_t)ETHERNET_SRC) + 0x08000000);
	/* Read the status of the receiving a packet */
	ETH_StatusPacketReceptionStruct.Status = (uint32_t)*ptr_InputFrame;
	PacketLength = (ETH_StatusPacketReceptionStruct.Fields.Length + 3)/4;


	/* Set pointer to output buffer */
	ptr_OutputFrame = (volatile uint32_t * )(((uint32_t)ETHERNET_DST) + (0x08000000 | 0x1000) );

	DataLen[count] = *ptr_OutputFrame = ETH_StatusPacketReceptionStruct.Fields.Length - 4;


	/* Read the input frame */
	for(int i = 0; i < PacketLength - 1; i++){
		DataLen[i+1] = *ptr_OutputFrame  = *ptr_InputFrame;
		if(i > N)
			PORT_SetBits(MDR_PORTB, PORT_Pin_0);
	}
/*
	data1 = *((uint32_t*)(EthBaseBufferAddr | ((Rhead+=4)&0xFFC)));
	Rhead = (Rhead + 4 )&0xFFC;
*/

	data1 = *ptr_InputFrame;
	*ptr_OutputFrame = 0;

/*
	TimeLen[count] = TIMER_GetCounter(MDR_TIMER1) - OldTime;
	count = (count + 1)&(N-1);
*/
}



/* Private functions ---------------------------------------------------------*/

/**
  * @brief	Configure CPU clock.
  * @param	None
  * @retval None
  */
void ClockConfigure ( void )
{
	/* Enable HSE (High Speed External) clock */
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);
	if (RST_CLK_HSEstatus() == ERROR) {
		while (1);
	}

	/* Configures the CPU_PLL clock source */
	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul16);

	/* Enables the CPU_PLL */
	RST_CLK_CPU_PLLcmd(ENABLE);
	if (RST_CLK_CPU_PLLstatus() == ERROR) {
		while (1);
	}

	/* Enables the RST_CLK_PCLK_EEPROM */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE);
	/* Sets the code latency value */
	EEPROM_SetLatency(EEPROM_Latency_4);

	/* Select the CPU_PLL output as input for CPU_C3_SEL */
	RST_CLK_CPU_PLLuse(ENABLE);
	/* Set CPUClk Prescaler */
	RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);

	/* Select the CPU clock source */
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
}

#if defined (_USE_DEBUG_UART_)
/**
  * @brief
  * @param	None
  * @retval	None
  */
void DebugUARTInit()
{
	UART_InitTypeDef UART_InitStructure;
	uint32_t BaudRateStatus;
#if defined (USE_MDR1986VE3)
	RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTD | RST_CLK_PCLK_UART2), ENABLE);
#elif defined (USE_MDR1986VE9x)
	RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTF | RST_CLK_PCLK_UART2), ENABLE);
#endif

	/* Port Init Struture */
	PORT_InitStructure.PORT_Pin = DEBUG_UART_PINS;
	PORT_InitStructure.PORT_FUNC = DEBUG_UART_PINS_FUNCTION;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;

	PORT_Init(DEBUG_UART_PORT, &PORT_InitStructure);

	UART_DeInit(DEBUG_UART);

  	/* UART	Init Structure */
	UART_InitStructure.UART_BaudRate            = DEBUG_BAUD_RATE;
	UART_InitStructure.UART_WordLength          = UART_WordLength8b;
	UART_InitStructure.UART_StopBits            = UART_StopBits1;
	UART_InitStructure.UART_Parity              = UART_Parity_No;
	UART_InitStructure.UART_FIFOMode            = UART_FIFO_ON;
	UART_InitStructure.UART_HardwareFlowControl = ( UART_HardwareFlowControl_RXE |
											   UART_HardwareFlowControl_TXE );

	/* ----- Инициализация UART ----- */
	UART_BRGInit(DEBUG_UART, UART_HCLKdiv1);
        BaudRateStatus = UART_Init(DEBUG_UART, &UART_InitStructure);
	if(BaudRateStatus == BaudRateValid){
		UART_Cmd(DEBUG_UART,ENABLE);
	}
	else{
		while(1);
	}
	DEBUG_PRINTF("==============System startup==============\n\r");
	DEBUG_PRINTF("Init Debug UART ... Ok\r\n");
}

PUTCHAR_PROTOTYPE{
        UART_SendData(DEBUG_UART, (uint8_t) ch);
        // Loop until the end of transmission
        while (UART_GetFlagStatus(DEBUG_UART, UART_FLAG_TXFF) == SET);
  return (ch);
}

GETCHAR_PROTOTYPE{
	while (UART_GetFlagStatus(DEBUG_UART, UART_FLAG_RXFE) == SET);

	return ( UART_ReceiveData( DEBUG_UART ) );
}

#endif /* #if defined (_USE_DEBUG_UART_) */

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
void assert_failed(uint32_t file_id, uint32_t line, const uint8_t* expr)
{
  /* User can add his own implementation to report the source file ID, line number and
     expression text.
     Ex: printf("Wrong parameters value (%s): file Id %d on line %d\r\n", expr, file_id, line) */
	DEBUG_PRINTF("Wrong parameters value (%s): file Id %d on line %d\r\n", expr, file_id, line);

  /* Infinite loop */
  while (1);
}
#endif /* USE_ASSERT_INFO */

/** @} */ /* End of group Ethernet_X2 */

/** @} */ /* End of group MDR1986VE3_Complexity_Evaluation_Board */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2013 Milandr ********************************
*
* END OF FILE main.c */
