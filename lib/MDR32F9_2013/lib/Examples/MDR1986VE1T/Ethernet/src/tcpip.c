/******************************************************************
 *****                                                        *****
 *****  Name: tcpip.c                                         *****
 *****  Ver.: 1.0                                             *****
 *****  Date: 07/05/2001                                      *****
 *****  Auth: Andreas Dannenberg                              *****
 *****        HTWK Leipzig                                    *****
 *****        university of applied sciences                  *****
 *****        Germany                                         *****
 *****  Func: implements the TCP/IP-stack and provides a      *****
 *****        simple API to the user                          *****
 *****                                                        *****
 ******************************************************************/

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR1986VE1T_EVAL MDR1986VE1T Opora Evaluation Board
  * @{
  */

/** @addtogroup Ethernet_IT Ethernet
  * @{
  */

#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_eth.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_timer.h"
#include "tcpip.h"
#include "string.h"

#define DEBUG_PRINTF(...) printf(__VA_ARGS__)

/* Initalizes the LAN-controller, reset flags, starts timer-ISR */
#define DATA_SIZE 8296
#define DATA_LEN (int)DATA_SIZE/6
#define DATA_LEN5 DATA_SIZE - DATA_LEN*5
#define MAX_TCP_DATA_SIZE 1460

/* Global vars and flags */
uint32_t TCPRxDataCount = 0;              // nr. of bytes rec'd
uint32_t TCPTxDataCount = 0;              // nr. of bytes to send
uint16_t Ident = 1;

/* Pointer to output TCP data */
uint8_t *pData = NULL;

/* TCP ports */
uint16_t TCPLocalPort = 0;
uint16_t TCPRemotePort = 23;

/* MAC and IP of current TCP-session */
uint16_t RemoteMAC[3] = {0,0,0};
uint16_t RemoteIP[2] = {0,0};

/* The socket status */
uint8_t SocketStatus;

/* Internal variables */
TTCPStateMachine TCPStateMachine;         	// perhaps the most important var at all ;-)
TLastFrameSent LastFrameSent;             	// retransmission type

uint32_t ISNGenHigh = 0;                  	// upper word of our Initial Sequence Number
uint32_t TCPSeqNr = 0;                   	// next sequence number to send
uint32_t TCPUNASeqNr = 0;					// last unacknowledged sequence number
											// incremented AFTER sending data
uint32_t TCPAckNr = 0;                   	// next seq to receive and ack to send
                                            // incremented AFTER receiving data
uint8_t TCPTimer = 0;                   	// inc'd each 262ms
uint8_t RetryCounter = 0;               	// nr. of retransmissions

/* Properties of the just received frame */
uint32_t RecdFrameLength = 0;             	// CS8900 reported frame length
uint16_t RecdFrameMAC[3] = {0,0,0};     	// 48 bit MAC
uint16_t RecdFrameIP[2] = {0,0};        	// 32 bit IP
uint16_t RecdIPFrameLength = 0;         	// 16 bit IP packet length

/* The next 3 buffers must be word-aligned!*/
/* (here the 'RecdIPFrameLength' above does that)*/
uint8_t TxFrame1[ETH_CTRL_FIELD + ETH_HEADER_SIZE + IP_HEADER_SIZE + TCP_HEADER_SIZE + MAX_TCP_TX_DATA_SIZE] IAR_SECTION ("EXECUTABLE_MEMORY_SECTION");
uint8_t TxFrame2[ETH_CTRL_FIELD + ETH_HEADER_SIZE + MAX_ETH_TX_DATA_SIZE] 									 IAR_SECTION ("EXECUTABLE_MEMORY_SECTION");
// space for incoming packet
uint32_t InputFrame[1514/4] 																				 IAR_SECTION ("EXECUTABLE_MEMORY_SECTION");

uint32_t TxFrame1Size = 0;                // bytes to send in TxFrame1
uint32_t TxFrame2Size = 0;                // bytes to send in TxFrame2
uint8_t TransmitControl = 0;


/* Handles an incoming frame  */
pEthernetARP_Answer  EthernetARP_Answer;
pEthernetIP_Frame    EthernetIP_Frame;
pEthernetTCPIP_Frame EthernetTCPIP_Frame;
pARPHead pARP;
uint8_t TCPFlags;

/* "MYIP1.MYIP2.MYIP3.MYIP4" */
const uint16_t MyIP[] =
{
  MYIP_1 + (MYIP_2 << 8),
  MYIP_3 + (MYIP_4 << 8)
};

/* "SUBMASK1.SUBMASK2.SUBMASK3.SUBMASK4" */
const uint16_t SubnetMask[] =
{
  SUBMASK_1 + (SUBMASK_2 << 8),
  SUBMASK_3 + (SUBMASK_4 << 8)
};

/* "GWIP1.GWIP2.GWIP3.GWIP4" */
const uint16_t GatewayIP[] =
{
  GWIP_1 + (GWIP_2 << 8),
  GWIP_3 + (GWIP_4 << 8)
};


/**
  * @brief	Function copy data from received frame to destenation array.
  * @param	dest: pointer to dest array.
  * @param	src: pointer to src array.
  * @param	size: number elements to copt.
  * @retval None
  */
void CopyFromFrame(void * dest , uint16_t * src, uint32_t size){
    uint16_t * pDest	= (uint16_t * )dest;
    uint16_t * psrc 	= (uint16_t * )src;
    uint32_t   i = 0;
    while (size > 1) {
    	pDest[i] = psrc[i++];
    	size -= 2;
    }
    if (size)                                      	// check for leftover byte...
    	*(uint8_t *)&pDest[i] =  *(uint8_t *)&psrc[i];  	// the LAN-Controller will return 0
}

/**
  * @brief	Initialization of TCP/IP stack
  * @param	None
  * @retval	The state of TCP/IP stack.
  */
TTCPStateMachine * TCPIP_init( void )
{
    TCPLowLevelInit();
    return (&TCPStateMachine);
}

/**
  * @brief	Initialization of the timers and the TCP/IP state.
  * @param	None
  * @retval	None
  */
void TCPLowLevelInit(void)
{
	TIMER_CntInitTypeDef TIMER_CntInitStruct;

	/* Init DMA */
	ETH_DMAPrepare();

    /* Set local TCP port */
    TCPLocalPort = TCP_PORT_TELNET;

    RemoteIP[0] = 10 + (0<<8);
    RemoteIP[1] = 0 + (2<<8);

    /* Setting the interval timer to 200 ms */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER1, ENABLE);
	TIMER_BRGInit(MDR_TIMER1,TIMER_HCLKdiv1);
	TIMER_DeInit(MDR_TIMER1);
	TIMER_CntStructInit(&TIMER_CntInitStruct);
	TIMER_CntInitStruct.TIMER_Prescaler = 80;
	TIMER_CntInitStruct.TIMER_Period = 200000;
	TIMER_CntInit(MDR_TIMER1, &TIMER_CntInitStruct);
	TIMER_CntEventSourceConfig(MDR_TIMER1, TIMER_EvSrc_TM1);
    /* Start timer*/
	TIMER_Cmd(MDR_TIMER1, ENABLE);

    /* Reset TPC flags */
    TransmitControl = 0;
    TCPFlags = 0;
    TCPStateMachine = CLOSED;
    SocketStatus = 0;
}

/**
  * @brief	Does a passive open (listen on 'MyIP:TCPLocalPort' for an incoming
			connection.
  * @param	None
  * @retval	None
  */
void TCPPassiveOpen(void)
{
    if (TCPStateMachine == CLOSED){
        TCPFlags &= ~TCP_ACTIVE_OPEN;                // let's do a passive open!
        TCPStateMachine = LISTENING;
        SocketStatus = SOCK_ACTIVE;                  // reset, socket now active
    }
}

/**
  * @brief	Does an active open (tries to establish a connection between
  * 		'MyIP:TCPLocalPort' and 'RemoteIP:TCPRemotePort').
  * @param	None
  * @retval	None
  */
void TCPActiveOpen(void)
{
    if ((TCPStateMachine == CLOSED) || (TCPStateMachine == LISTENING)){
        TCPFlags |= TCP_ACTIVE_OPEN;                 // let's do an active open!
        TCPFlags &= ~IP_ADDR_RESOLVED;               // we haven't opponents MAC yet

        PrepareARP_REQUEST();                        // ask for MAC by sending a broadcast
        LastFrameSent = ARP_REQUEST;
        TCPStartRetryTimer();
        SocketStatus = SOCK_ACTIVE;                  // reset, socket now active
    }
}

/**
  * @brief	Closes an open connection.
  * @param	None
  * @retval	None
  */
void TCPClose(void)
{
    switch (TCPStateMachine){
        case LISTENING :
        case SYN_SENT :{
            TCPStateMachine = CLOSED;
            TCPFlags = 0;
            SocketStatus = 0;
            break;
        }
        case SYN_RECD :
        case ESTABLISHED :{
            TCPFlags |= TCP_CLOSE_REQUESTED;
            break;
        }
    }
}

/**
  * @brief	Releases the receive-buffer and allows easyWEB to store new data.
  * @note	Rx-buffer MUST be released periodically, else the other TCP
  *	    	get no ACKs for the data it sent.
  * @param	None
  * @retval	None
  */
void TCPReleaseRxBuffer(void)
{
  SocketStatus &= ~SOCK_DATA_AVAILABLE;
}

/**
  * @brief	Transmitts data stored in 'TCP_TX_BUF'.
  * @note	Number of bytes to transmit must have been written to 'TCPTxDataCount'.
  * @note	Data-count MUST NOT exceed 'MAX_TCP_TX_DATA_SIZE'.
  * @param	SizeToSend: number of the byte to send.
  * @param	Data: pointer to output array.
  * @retval	None
  */
void TCPTransmitTxBuffer(uint32_t SizeToSend, uint8_t * Data)
{
  if ((TCPStateMachine == ESTABLISHED) || (TCPStateMachine == CLOSE_WAIT))
      if (SocketStatus & SOCK_TX_BUF_RELEASED){

          pData = Data;
          TCPTxDataCount = SizeToSend;

          SocketStatus &= ~SOCK_TX_BUF_RELEASED;               // occupy tx-buffer
          TCPUNASeqNr += TCPTxDataCount;                       // advance UNA

          TxFrame1Size = ETH_HEADER_SIZE + IP_HEADER_SIZE + TCP_HEADER_SIZE + TCPTxDataCount;
          TransmitControl |= SEND_FRAME1;

          LastFrameSent = TCP_DATA_FRAME;
          TCPStartRetryTimer();
      }
}

/**
  * @brief	Main network function. must be called from user program
  * 		periodically (the often - the better) handles network,
  * 		TCP/IP-stack and user events.
  * @param	ETHERNETx: Slect the ETHERNET peripheral.
  *         This parameter can be one of the following values:
  *         MDR_ETHERNET1, MDR_ETHERNET2
  * @retval	None
  */
void DoNetworkStuff(MDR_ETHERNET_TypeDef * ETHERNETx)
{
	/* Is the interval timer stopped? */
	if(TIMER_GetFlagStatus(MDR_TIMER1, TIMER_STATUS_CNT_ARR)) {
		TIMER_ClearFlag(MDR_TIMER1, TIMER_STATUS_CNT_ARR);
		/* Processing shutdown timer */
		TCPClockHandler();
	}
	/* Is the retransmission timer started? */
	if (TCPFlags & TCP_TIMER_RUNNING) {
		/* Is repeat flag setframe transmission? */
		if (TCPFlags & TIMER_TYPE_RETRY) {
			/* Is retransmission required frame? */
			if (TCPTimer > RETRY_TIMEOUT) {
				TCPRestartTimer();                  				/* Installing a new timeout */
				/* Counter retransmission, = 0 */
				if (RetryCounter) {
					TCPHandleRetransmission(); 	 					/* Executing retransmission frame */
					RetryCounter--;
				}
				else {
					TCPStopTimer();
					TCPHandleTimeout();
				}
			}
		}
		else
			/* Wait FIN_TIMEOUT */
			if (TCPTimer > FIN_TIMEOUT) {
				TCPStateMachine = CLOSED;               			// Close connection
				TCPFlags = 0;  										// reset all flags, stop retransmission...
				SocketStatus &= SOCK_DATA_AVAILABLE;  				// clear all flags but data available
			}
	}

	switch (TCPStateMachine) {
		case CLOSED:
		case LISTENING: {
			if (TCPFlags & TCP_ACTIVE_OPEN)   						// stack has to open a connection?
				if (TCPFlags & IP_ADDR_RESOLVED)                 	// IP resolved?
					if (!(TransmitControl & SEND_FRAME2)){        	// buffer free?
						TCPSeqNr = (uint32_t) TIMER_GetCounter(MDR_TIMER1) << 16;
						TCPUNASeqNr = TCPSeqNr;
						TCPAckNr = 0;              					// we don't know what to ACK!
						TCPUNASeqNr++;                    			// count SYN as a byte
						PrepareTCP_FRAME(TCP_CODE_SYN);        		// send SYN frame
						LastFrameSent = TCP_SYN_FRAME;
						TCPStartRetryTimer();         				// we NEED a retry-timeout
						TCPStateMachine = SYN_SENT;
					}
			break;
		}
		case SYN_RECD:
		case ESTABLISHED: {
			if (TCPFlags & TCP_CLOSE_REQUESTED)  						// user has user initiated a close?
				if (!(TransmitControl & (SEND_FRAME2 | SEND_FRAME1)))  	// buffers free?
					if (TCPSeqNr == TCPUNASeqNr){              			// all data ACKed?
						TCPUNASeqNr++;
						PrepareTCP_FRAME(TCP_CODE_FIN | TCP_CODE_ACK);
						LastFrameSent = TCP_FIN_FRAME;
						TCPStartRetryTimer();
						TCPStateMachine = FIN_WAIT_1;
					}
			break;
		}
		case CLOSE_WAIT: {
			if (!(TransmitControl & (SEND_FRAME2 | SEND_FRAME1)))  		// buffers free?
				if (TCPSeqNr == TCPUNASeqNr) {                 			// all data ACKed?
					TCPUNASeqNr++;                        				// count FIN as a byte
					PrepareTCP_FRAME(TCP_CODE_FIN | TCP_CODE_ACK);  	// we NEED a retry-timeout
					LastFrameSent = TCP_FIN_FRAME;     					// time to say goodbye...
					TCPStartRetryTimer();
					TCPStateMachine = LAST_ACK;
				}
			break;
		}
	}

	if (TransmitControl & SEND_FRAME2) {
		ETH_SendFrame(ETHERNETx, (uint32_t *) TxFrame2, *(uint32_t*)&TxFrame2[0]);
		TransmitControl &= ~SEND_FRAME2;
	}
	if ((TCPStateMachine == ESTABLISHED) && ((SocketStatus & SOCK_TX_BUF_RELEASED) == SOCK_TX_BUF_RELEASED)) {
		if(SocketStatus & SOCK_DATA_AVAILABLE){
			TCPTransmitTxBuffer(TCPRxDataCount, (uint8_t *)(((uint8_t *)&InputFrame[0]) + TCP_DATA_OFS));
			TCPReleaseRxBuffer();
		}
	}

	if (TransmitControl & SEND_FRAME1) {
		PrepareTCP_DATA_FRAME();
		ETH_SendFrame(ETHERNETx, (uint32_t *) TxFrame1, *(uint32_t*)&TxFrame1[0]);
		TransmitControl &= ~SEND_FRAME1;
	}
}

/**
  * @brief	Handles an incoming broadcast frame.
  * @param	ptr_InputBuffer: pointer to incuming frame.
  * @param 	FrameLen: size of the incuming frame.
  * @retval	None
  */
void ProcessEthBroadcastFrame(uint32_t * ptr_InputBuffer, uint32_t FrameLen  )
{
    uint16_t TargetIP[2];

    pARP = (pARPHead)ptr_InputBuffer;
    CopyFromFrame(&RecdFrameMAC,pARP->SrcAddr, 6);      						// store SA (for our answer)
    /* Check for ARP protocol */
    if (SWAPB(pARP->FrameType) == FRAME_ARP)
        if (SWAPB(pARP->HardwareType) == HARDW_ETH10)
            if (SWAPB(pARP->ProtocolType) == FRAME_IP)
                if (SWAPB(pARP-> HardSizeProtSize) == IP_HLEN_PLEN)
                    if (SWAPB(pARP->Opcode) == OP_ARP_REQUEST){
                        CopyFromFrame(RecdFrameIP, pARP->SenderIPAddr, 4);     	// read sender's protocol address
                        CopyFromFrame(TargetIP,    pARP->TargetIPAddr, 4);      // read target's protocol address
                        if (!memcmp(MyIP, TargetIP, 4)){                      	// is it for us?
                            PrepareARP_ANSWER();                                // yes->create ARP_ANSWER frame
                        }
                    }
}

/**
  * @brief	Handles an incoming unicast frame.
  * @param	ptr_InputBuffer: pointer to incuming frame.
  * @param 	FrameLen: size of the incuming frame.
  * @retval
  */
void ProcessEthIAFrame(uint32_t * ptr_InputBuffer, uint32_t FrameLen  )
{
	uint16_t TargetIP[2];
	uint8_t ProtocolType;

	EthernetARP_Answer = (pEthernetARP_Answer)ptr_InputBuffer;
	EthernetIP_Frame = (pEthernetIP_Frame)ptr_InputBuffer;
	EthernetTCPIP_Frame = (pEthernetTCPIP_Frame)ptr_InputBuffer;
    pARP = (pARPHead)ptr_InputBuffer;


	CopyFromFrame(RecdFrameMAC, EthernetARP_Answer->SrcAddr, 6);            	// store SA (for our answer)

	switch (SWAPB(EthernetARP_Answer->FrameType)){                     			// get frame type
	case FRAME_ARP :                                                      		// check for ARP
			if ((TCPFlags & (TCP_ACTIVE_OPEN | IP_ADDR_RESOLVED)) == TCP_ACTIVE_OPEN){
				if (SWAPB(EthernetARP_Answer->HardwareType) == HARDW_ETH10)
					if (SWAPB(EthernetARP_Answer->ProtocolType) == FRAME_IP)
						if (SWAPB(EthernetARP_Answer->HardSizeProtSize) == IP_HLEN_PLEN)
							if (SWAPB(EthernetARP_Answer->Opcode) == OP_ARP_ANSWER) {
								TCPStopTimer();  // OK, now we've the MAC we wanted ;-)
								CopyFromFrame(RemoteMAC, EthernetARP_Answer->SenderMacAddr, 6);  // extract opponents MAC
								TCPFlags |= IP_ADDR_RESOLVED;
							}
				}
				else{
					if (SWAPB(pARP->HardwareType) == HARDW_ETH10){
						if (SWAPB(pARP->ProtocolType) == FRAME_IP)
							if (SWAPB(pARP-> HardSizeProtSize) == IP_HLEN_PLEN)
								if (SWAPB(pARP->Opcode) == OP_ARP_REQUEST){
									CopyFromFrame(RecdFrameIP, pARP->SenderIPAddr, 4);     	// read sender's protocol address
									CopyFromFrame(TargetIP,    pARP->TargetIPAddr, 4);      // read target's protocol address
									if (!memcmp(MyIP, TargetIP, 4)){                      	// is it for us?
										PrepareARP_ANSWER();                                // yes->create ARP_ANSWER frame
									}
								}
					}
				}
	break;
	case FRAME_IP:                                      						// check for IP-type
		if ((SWAPB(EthernetIP_Frame->IPVerIHL) & 0xFF00) == IP_VER_IHL) {      	// IPv4, IHL=5 (20 Bytes Header)	// ignore Type Of Service
			RecdIPFrameLength = SWAPB(EthernetIP_Frame->FrameLength); 	 	  	// get IP frame's length 			// ignore identification
			if (!(SWAPB(EthernetIP_Frame->Flags_Offset) & (IP_FLAG_MOREFRAG | IP_FRAGOFS_MASK))) {  				// only unfragm. frames
				ProtocolType = SWAPB(EthernetIP_Frame->ProtocolType_TTL);  		// get protocol, ignore TTL		 	// ignore checksum
				CopyFromFrame(RecdFrameIP, EthernetIP_Frame->SenderIPAddr, 4);  // get source IP
				CopyFromFrame(TargetIP, EthernetIP_Frame->TargetIPAddr, 4);     // get destination IP
				if (!memcmp(MyIP, TargetIP, 4))           						// is it for us?
					switch (ProtocolType) {
						case PROT_ICMP:
							if(ProcessICMPFrame())
							break;
						case PROT_TCP:
							ProcessTCPFrame();
							break;
						case PROT_UDP:
						break;                           						// not implemented!
					}
			}
		}
		break;
	}
}

/**
  * @brief	We've just rec'd an ICMP-frame (Internet Control Message Protocol)
  * 		check what to do and branch to the appropriate sub-function.
  * @param	None
  * @retval	None
  */
uint32_t ProcessICMPFrame ( void )
{

	unsigned short ICMPTypeAndCode;
	ICMPTypeAndCode = SWAPB(EthernetIP_Frame->Type_and_Code);  // get Message Type and Code
															   // ignore ICMP checksum
	switch (ICMPTypeAndCode >> 8) {                // check type
		case ICMP_ECHO:                             // is echo request?
			PrepareICMP_ECHO_REPLY();               // echo as much as we can...
			return (1);
		break;
	}
	return (0);
}

/**
  * @brief	We've just rec'd an TCP-frame (Transmission Control Protocol)
  * 		this function mainly implements the TCP state machine according to RFC793.
  * @param	None
  * @retval	None
  */
void ProcessTCPFrame(void)
{
	uint32_t TCPSegSeq;						// segment's sequence number
	uint32_t TCPSegAck;						// segment's acknowledge number
	uint16_t TCPSegSourcePort;				// segment's source port
	uint16_t TCPSegDestPort;				// segment's destination port
	uint16_t TCPCode;						// TCP code and header length
	uint16_t TCPHeaderSize;					// real TCP header length
	uint16_t NrOfDataBytes;					// real number of data

	TCPSegSourcePort = SWAPB(EthernetTCPIP_Frame->SRC_port);  			// get ports
	TCPSegDestPort = SWAPB(EthernetTCPIP_Frame->DEST_port);

	if (TCPSegDestPort != TCPLocalPort)
		return;                            								// drop segment if port doesn't match

	TCPSegSeq = ((unsigned int) SWAPB(EthernetTCPIP_Frame->Sequence_number_HI)) << 16;  		// get segment sequence nr.
	TCPSegSeq |= SWAPB(EthernetTCPIP_Frame->Sequence_number_LO);

	TCPSegAck = ((unsigned int) SWAPB(EthernetTCPIP_Frame->Acknowlegement_HI)) << 16;  			// get segment acknowledge nr.
	TCPSegAck |= SWAPB(EthernetTCPIP_Frame->Acknowlegement_LO);

	TCPCode = (unsigned short) SWAPB(EthernetTCPIP_Frame->Offset_data_and_Flags);  				// get control bits, header length...

	TCPHeaderSize = (TCPCode & DATA_OFS_MASK) >> 10;   					// header length in bytes
	NrOfDataBytes = RecdIPFrameLength - IP_HEADER_SIZE - TCPHeaderSize; // seg. text length

	if (NrOfDataBytes > MAX_TCP_RX_DATA_SIZE)
		return;                                							// packet too large for us :...-(

	switch (TCPStateMachine){                  							// implement the TCP state machine
		case CLOSED: {
			if (!(TCPCode & TCP_CODE_RST)) {
				TCPRemotePort = TCPSegSourcePort;
				memcpy(&RemoteMAC, &RecdFrameMAC, 6); 					// save opponents MAC and IP
				memcpy(&RemoteIP, &RecdFrameIP, 4);             		// for later use

				if (TCPCode & TCP_CODE_ACK)           					// make the reset sequence
				{                                     					// acceptable to the other
					TCPSeqNr = TCPSegAck;                            	// TCP
					PrepareTCP_FRAME(TCP_CODE_RST);
				}
				else {
					TCPSeqNr = 0;
					TCPAckNr = TCPSegSeq + NrOfDataBytes;
					if (TCPCode & (TCP_CODE_SYN | TCP_CODE_FIN))
						TCPAckNr++;
					PrepareTCP_FRAME(TCP_CODE_RST | TCP_CODE_ACK);
				}
			}
			break;
		}
		case LISTENING: {
			if (!(TCPCode & TCP_CODE_RST)){      						// ignore segment containing RST
				TCPRemotePort = TCPSegSourcePort;
				memcpy(&RemoteMAC, &RecdFrameMAC, 6);  					// save opponents MAC and IP
				memcpy(&RemoteIP, &RecdFrameIP, 4);             		// for later use

				if (TCPCode & TCP_CODE_ACK){                       		// reset a bad
                  														// acknowledgement
					TCPSeqNr = TCPSegAck;
					PrepareTCP_FRAME(TCP_CODE_RST);
				}
				else
					if (TCPCode & TCP_CODE_SYN) {
						TCPAckNr = TCPSegSeq + 1; 						// get remote ISN, next byte we expect
						TCPSeqNr = ((unsigned long) ISNGenHigh << 16);
						TCPUNASeqNr = TCPSeqNr + 1;  					// one byte out -> increase by one
						PrepareTCP_FRAME(TCP_CODE_SYN | TCP_CODE_ACK);
						LastFrameSent = TCP_SYN_ACK_FRAME;
						TCPStartRetryTimer();
						TCPStateMachine = SYN_RECD;
					}
			}
			break;
		}
		case SYN_SENT: {
			if (memcmp(&RemoteIP, &RecdFrameIP, 4))
				break;  												// drop segment if its IP doesn't belong
																		// to current session
			if (TCPSegSourcePort != TCPRemotePort)
				break;  											 	// drop segment if port doesn't match

			if (TCPCode & TCP_CODE_ACK)                					// ACK field significant?
				if (TCPSegAck != TCPUNASeqNr){               			// is our ISN ACKed?
					if (!(TCPCode & TCP_CODE_RST)) {
						TCPSeqNr = TCPSegAck;
						PrepareTCP_FRAME(TCP_CODE_RST);
					}
					break;                                 				// drop segment
				}

			if (TCPCode & TCP_CODE_RST){               					// RST??
				if (TCPCode & TCP_CODE_ACK){      						// if ACK was acceptable, reset connection
					TCPStateMachine = CLOSED;
					TCPFlags = 0;     									// reset all flags, stop retransmission...
					SocketStatus = SOCK_ERR_CONN_RESET;
				}
				break;                                   				// drop segment
			}

			if (TCPCode & TCP_CODE_SYN){               					// SYN??
				TCPAckNr = TCPSegSeq;                    				// get opponents ISN
				TCPAckNr++;                              				// inc. by one...
				if (TCPCode & TCP_CODE_ACK) {
					TCPStopTimer();  									// stop retransmission, other TCP got our SYN
					TCPSeqNr = TCPUNASeqNr;       						// advance our sequence number

					PrepareTCP_FRAME(TCP_CODE_ACK);        				// ACK this ISN
					TCPStateMachine = ESTABLISHED;
					SocketStatus |= SOCK_CONNECTED;
					SocketStatus |= SOCK_TX_BUF_RELEASED;  				// user may send data now :-)
				}
				else {
					TCPStopTimer();
					PrepareTCP_FRAME(TCP_CODE_SYN | TCP_CODE_ACK);  	// our SYN isn't ACKed yet,
					LastFrameSent = TCP_SYN_ACK_FRAME; 					// now continue with sending
					TCPStartRetryTimer();                      			// SYN_ACK frames
					TCPStateMachine = SYN_RECD;
				}
			}
			break;
		}
		default: {
			if (memcmp(&RemoteIP, &RecdFrameIP, 4))
				break;  												// drop segment if IP doesn't belong to current session
			if (TCPSegSourcePort != TCPRemotePort)
				break;   												// drop segment if port doesn't match
			if (TCPSegSeq != TCPAckNr)
				break;               									// drop if it's not the segment we expect
			if (TCPCode & TCP_CODE_RST){              	 				// RST??
				TCPStateMachine = CLOSED;             					// close the state machine
				TCPFlags = 0;         									// reset all flags, stop retransmission...
				SocketStatus = SOCK_ERR_CONN_RESET;  					// indicate an error to user
				break;
			}
			if (TCPCode & TCP_CODE_SYN){                				// SYN??
				PrepareTCP_FRAME(TCP_CODE_RST);  						// is NOT allowed here! send a reset,
				TCPStateMachine = CLOSED;                				// close connection...
				TCPFlags = 0;         									// reset all flags, stop retransmission...
				SocketStatus = SOCK_ERR_REMOTE;         	 			// fatal error!
				break;                                  				// ...and drop the frame
			}
			if (!(TCPCode & TCP_CODE_ACK))
				break;      											// drop segment if the ACK bit is off

			if (TCPSegAck == TCPUNASeqNr){        						// is our last data sent ACKed?
				TCPStopTimer();                          				// stop retransmission
				TCPSeqNr = TCPUNASeqNr;           						// advance our sequence number
				switch (TCPStateMachine){            					// change state if necessary
					case SYN_RECD:                        				// ACK of our SYN?
						TCPStateMachine = ESTABLISHED;  				// user may send data now :-)
						SocketStatus |= SOCK_CONNECTED;
						break;
					case FIN_WAIT_1:
						TCPStateMachine = FIN_WAIT_2;
						break;
																		// ACK of our FIN?
					case CLOSING:
						TCPStateMachine = TIME_WAIT;
						break;
																		// ACK of our FIN?
					case LAST_ACK:                            			// ACK of our FIN?
						TCPStateMachine = CLOSED;
						TCPFlags = 0;  									// reset all flags, stop retransmission...
						SocketStatus &= SOCK_DATA_AVAILABLE;  			// clear all flags but data available
						break;
					case TIME_WAIT:
						PrepareTCP_FRAME(TCP_CODE_ACK);  				// ACK a retransmission of remote FIN
						TCPRestartTimer();          					// restart TIME_WAIT timeout
						break;
				}
				if (TCPStateMachine == ESTABLISHED)  					// if true, give the frame buffer back
					SocketStatus |= SOCK_TX_BUF_RELEASED;  				// to user
			}
			if ((TCPStateMachine == ESTABLISHED)
					|| (TCPStateMachine == FIN_WAIT_1)
					|| (TCPStateMachine == FIN_WAIT_2))
				if (NrOfDataBytes)                            			// data available?
					if (!(SocketStatus & SOCK_DATA_AVAILABLE)){  		// rx data-buffer empty?
						TCPRxDataCount = NrOfDataBytes;   				// ...tell the user...
						SocketStatus |= SOCK_DATA_AVAILABLE;  			// indicate the new data to user
						TCPAckNr += NrOfDataBytes;
						PrepareTCP_FRAME(TCP_CODE_ACK);        			// ACK rec'd data
						//TCPReleaseRxBuffer();
					}
			if (TCPCode & TCP_CODE_FIN){               					// FIN??
				switch (TCPStateMachine) {
					case SYN_RECD:
					case ESTABLISHED:
						TCPStateMachine = CLOSE_WAIT;
						break;
					case FIN_WAIT_1:									// if our FIN was ACKed, we automatically
						TCPStateMachine = CLOSING;  					// enter FIN_WAIT_2 (look above) and therefore
						SocketStatus &= ~SOCK_CONNECTED;     			// TIME_WAIT
						break;
					case FIN_WAIT_2:
						TCPStartTimeWaitTimer();
						TCPStateMachine = TIME_WAIT;
						SocketStatus &= ~SOCK_CONNECTED;
						break;
					case TIME_WAIT:
						TCPRestartTimer();
						break;
				}
				TCPAckNr++;                             // ACK remote's FIN flag
				PrepareTCP_FRAME(TCP_CODE_ACK);
			}
			break;
		}
	}
}

/**
  * @brief	Prepares the TxFrame2-buffer to send an ARP-request.
  * @param	None
  * @retval	None
  */
void PrepareARP_REQUEST(void)
{
	uint8_t * ptr_OutFrame = (uint8_t * )&TxFrame2[4];

	// Ethernet
	*(uint32_t *) &ptr_OutFrame[0] = (((((uint8_t) (RecdFrameMAC[1] >> 8) & 0xFF) << 24)
			                       | (((uint8_t) RecdFrameMAC[1] & 0xFF) << 16)
			                       | (((uint8_t) (RecdFrameMAC[0] >> 8) & 0xFF) << 8)
			                       | ((uint8_t) RecdFrameMAC[0] & 0xFF)));

	*(uint16_t *) &ptr_OutFrame[4] = ((((uint8_t) (RecdFrameMAC[2] >> 8) & 0xFF) << 8)
							       | ((uint8_t) RecdFrameMAC[2] & 0xFF));
	/* Set our MAC address */
	ptr_OutFrame[6] = MAC_5;
	ptr_OutFrame[7] = MAC_4;
	ptr_OutFrame[8] = MAC_3;
	ptr_OutFrame[9] = MAC_2;
	ptr_OutFrame[10] = MAC_1;
	ptr_OutFrame[11] = MAC_0;

	// ARP
	*(uint16_t *)&ptr_OutFrame[ETH_TYPE_OFS]		= SWAPB(FRAME_ARP);
	*(uint16_t *) &TxFrame2[ARP_HARDW_OFS] 			= SWAPB(HARDW_ETH10);
	*(uint16_t *) &TxFrame2[ARP_PROT_OFS] 			= SWAPB(FRAME_IP);
	*(uint16_t *) &TxFrame2[ARP_HLEN_PLEN_OFS] 		= SWAPB(IP_HLEN_PLEN);
	*(uint16_t *) &TxFrame2[ARP_OPCODE_OFS] 		= SWAPB(OP_ARP_REQUEST);
	*(uint8_t *) &TxFrame2[ARP_SENDER_HA_OFS + 0] 	= MAC_5;
	*(uint8_t *) &TxFrame2[ARP_SENDER_HA_OFS + 1] 	= MAC_4;
	*(uint8_t *) &TxFrame2[ARP_SENDER_HA_OFS + 2] 	= MAC_3;
	*(uint8_t *) &TxFrame2[ARP_SENDER_HA_OFS + 3] 	= MAC_2;
	*(uint8_t *) &TxFrame2[ARP_SENDER_HA_OFS + 4] 	= MAC_1;
	*(uint8_t *) &TxFrame2[ARP_SENDER_HA_OFS + 5] 	= MAC_0;

	memcpy(&TxFrame2[ARP_SENDER_IP_OFS], MyIP, 4);
	memset(&TxFrame2[ARP_TARGET_HA_OFS], 0x00, 6);  // we don't know opposites MAC!

	if (((RemoteIP[0] ^ MyIP[0]) & SubnetMask[0]) || ((RemoteIP[1] ^ MyIP[1]) & SubnetMask[1]))
		memcpy(&TxFrame2[ARP_TARGET_IP_OFS], GatewayIP, 4);  // IP not in subnet, use gateway
	else
		memcpy(&TxFrame2[ARP_TARGET_IP_OFS], RemoteIP, 4);  // other IP is next to us...

	/* Set the length of the send frame */
	*(uint32_t *)&TxFrame2[0] = (ARP_FRAME_SIZE + ETH_HEADER_SIZE);
	TransmitControl |= SEND_FRAME2;
}

/**
  * @brief	Prepares the TxFrame2-buffer to send an ARP-answer (reply).
  * @param	None
  * @retval	None
  */
void PrepareARP_ANSWER(void)
{
	uint8_t * ptr_OutFrame = (uint8_t * )&TxFrame2[4];
	/* Ethernet */
	/* Set destanation MAC address */
	*(uint32_t *) &ptr_OutFrame[0] = (((((uint8_t) (RecdFrameMAC[1] >> 8) & 0xFF) << 24)
			                       | (((uint8_t) RecdFrameMAC[1] & 0xFF) << 16)
			                       | (((uint8_t) (RecdFrameMAC[0] >> 8) & 0xFF) << 8)
			                       | ((uint8_t) RecdFrameMAC[0] & 0xFF)));

	*(uint16_t *) &ptr_OutFrame[4] = ((((uint8_t) (RecdFrameMAC[2] >> 8) & 0xFF) << 8)
							       | ((uint8_t) RecdFrameMAC[2] & 0xFF));

	/* Set our MAC address */
	ptr_OutFrame[6] = MAC_5;
	ptr_OutFrame[7] = MAC_4;
	ptr_OutFrame[8] = MAC_3;
	ptr_OutFrame[9] = MAC_2;
	ptr_OutFrame[10] = MAC_1;
	ptr_OutFrame[11] = MAC_0;

	// ARP
	*(uint16_t *)&ptr_OutFrame[ETH_TYPE_OFS]			= SWAPB(FRAME_ARP);
	*(uint16_t *)&ptr_OutFrame[ARP_HARDW_OFS] 			= SWAPB(HARDW_ETH10);
	*(uint16_t *)&ptr_OutFrame[ARP_PROT_OFS] 			= SWAPB(FRAME_IP);
	*(uint16_t *)&ptr_OutFrame[ARP_HLEN_PLEN_OFS] 		= SWAPB(IP_HLEN_PLEN);
	*(uint16_t *)&ptr_OutFrame[ARP_OPCODE_OFS] 			= SWAPB(OP_ARP_ANSWER);
	*(uint8_t *) &ptr_OutFrame[ARP_SENDER_HA_OFS + 0] 	= MAC_5;
	*(uint8_t *) &ptr_OutFrame[ARP_SENDER_HA_OFS + 1] 	= MAC_4;
	*(uint8_t *) &ptr_OutFrame[ARP_SENDER_HA_OFS + 2] 	= MAC_3;
	*(uint8_t *) &ptr_OutFrame[ARP_SENDER_HA_OFS + 3] 	= MAC_2;
	*(uint8_t *) &ptr_OutFrame[ARP_SENDER_HA_OFS + 4] 	= MAC_1;
	*(uint8_t *) &ptr_OutFrame[ARP_SENDER_HA_OFS + 5] 	= MAC_0;

	/* IP */
	memcpy(&ptr_OutFrame[ARP_SENDER_IP_OFS], &MyIP, 4);
	memcpy(&ptr_OutFrame[ARP_TARGET_HA_OFS], &RecdFrameMAC, 6);
	memcpy(&ptr_OutFrame[ARP_TARGET_IP_OFS], &RecdFrameIP, 4);

	/* Set the length of the send frame */
	*(uint32_t *)&TxFrame2[0] = (ARP_FRAME_SIZE + ETH_HEADER_SIZE);
	TransmitControl |= SEND_FRAME2;
}

/**
  * @brief	Prepares the TxFrame2-buffer to send an ICMP-echo-reply
  * @param	None
  * @retval	None
  */
void PrepareICMP_ECHO_REPLY(void)
{
	uint16_t ICMPDataCount;
	uint8_t * ptr_OutFrame = (uint8_t * )&TxFrame2[4];

	if (RecdIPFrameLength > MAX_ETH_TX_DATA_SIZE)    // don't overload TX-buffer
		ICMPDataCount = MAX_ETH_TX_DATA_SIZE - IP_HEADER_SIZE - ICMP_HEADER_SIZE;
	else
		ICMPDataCount = RecdIPFrameLength - IP_HEADER_SIZE - ICMP_HEADER_SIZE;

	TxFrame2Size = IP_HEADER_SIZE + ICMP_HEADER_SIZE + ICMPDataCount;

	// Ethernet
	/* Set destanation MAC address */
	*(uint32_t *) &ptr_OutFrame[0] = (((((uint8_t) (RecdFrameMAC[1] >> 8) & 0xFF) << 24)
			                       | (((uint8_t) RecdFrameMAC[1] & 0xFF) << 16)
			                       | (((uint8_t) (RecdFrameMAC[0] >> 8) & 0xFF) << 8)
			                       | ((uint8_t) RecdFrameMAC[0] & 0xFF)));

	*(uint16_t *) &ptr_OutFrame[4] = ((((uint8_t) (RecdFrameMAC[2] >> 8) & 0xFF) << 8)
							       | ((uint8_t) RecdFrameMAC[2] & 0xFF));

	/* Set our MAC address */
	ptr_OutFrame[6] = MAC_5;
	ptr_OutFrame[7] = MAC_4;
	ptr_OutFrame[8] = MAC_3;
	ptr_OutFrame[9] = MAC_2;
	ptr_OutFrame[10] = MAC_1;
	ptr_OutFrame[11] = MAC_0;

	// IP
	*(uint16_t *)&ptr_OutFrame[ETH_TYPE_OFS]			= SWAPB(FRAME_IP);
	*(uint16_t *)&ptr_OutFrame[IP_VER_IHL_TOS_OFS] 		= SWAPB(IP_VER_IHL);
	WriteWBE(&ptr_OutFrame[IP_TOTAL_LENGTH_OFS], IP_HEADER_SIZE + ICMP_HEADER_SIZE + ICMPDataCount);
	*(uint16_t *)&ptr_OutFrame[IP_IDENT_OFS] 			= EthernetIP_Frame->Identification;//PROT_ICMP;
	*(uint16_t *)&ptr_OutFrame[IP_FLAGS_FRAG_OFS] 		= 0x00;
	*(uint16_t *)&ptr_OutFrame[IP_TTL_PROT_OFS] 		= SWAPB((DEFAULT_TTL << 8) | PROT_ICMP);
	*(uint16_t *)&ptr_OutFrame[IP_HEAD_CHKSUM_OFS] 		= 0;
	memcpy(&ptr_OutFrame[IP_SOURCE_OFS], MyIP, 4);
	memcpy(&ptr_OutFrame[IP_DESTINATION_OFS], RecdFrameIP, 4);
	*(uint16_t *)&ptr_OutFrame[IP_HEAD_CHKSUM_OFS] 		= CalcChecksum(&ptr_OutFrame[IP_VER_IHL_TOS_OFS], IP_HEADER_SIZE, 0);

	// ICMP
	*(uint16_t *)&ptr_OutFrame[ICMP_TYPE_CODE_OFS]		= SWAPB(ICMP_ECHO_REPLY << 8);
	*(uint16_t *)&ptr_OutFrame[ICMP_CHKSUM_OFS] 		= 0;                   // initialize checksum field
	*(uint16_t *)&ptr_OutFrame[ICMP_ID]			 		= EthernetIP_Frame->Identifier;
	*(uint16_t *)&ptr_OutFrame[ICMP_SEQ_NUM] 			= EthernetIP_Frame->Sequence_number;

	/* Compute chech sum */
	CopyFromFrame(&ptr_OutFrame[ICMP_DATA_OFS],&EthernetIP_Frame->Data, ICMPDataCount);        // get data to echo...
	*(uint16_t *)&ptr_OutFrame[ICMP_CHKSUM_OFS] = standard_chksum_opt(&ptr_OutFrame[IP_DATA_OFS], ICMPDataCount + ICMP_HEADER_SIZE, 0);

	/* Set the length of the send frame */
	*(uint32_t*)&TxFrame2[0] = ETH_HEADER_SIZE + IP_HEADER_SIZE + ICMP_HEADER_SIZE + ICMPDataCount;
	TransmitControl |= SEND_FRAME2;
}

/**
  * @brief	Prepares the TxFrame2-buffer to send a general TCP frame
  * 		the TCPCode-field is passed as an argument.
  * @param	None
  * @retval	None
  */
void PrepareTCP_FRAME(unsigned short TCPCode)
{
	uint8_t * ptr_OutFrame = (uint8_t *) &TxFrame2[4];

	// Ethernet
	/* Set destanation MAC address */
	*(uint32_t *) &ptr_OutFrame[0] = (((((uint8_t) (RecdFrameMAC[1] >> 8) & 0xFF) << 24)
			                       | (((uint8_t) RecdFrameMAC[1] & 0xFF) << 16)
			                       | (((uint8_t) (RecdFrameMAC[0] >> 8) & 0xFF) << 8)
			                       | ((uint8_t) RecdFrameMAC[0] & 0xFF)));

	*(uint16_t *) &ptr_OutFrame[4] = ((((uint8_t) (RecdFrameMAC[2] >> 8) & 0xFF) << 8)
							       | ((uint8_t) RecdFrameMAC[2] & 0xFF));
	/* Set our MAC address */
	ptr_OutFrame[6] 	= MAC_5;
	ptr_OutFrame[7] 	= MAC_4;
	ptr_OutFrame[8] 	= MAC_3;
	ptr_OutFrame[9] 	= MAC_2;
	ptr_OutFrame[10] 	= MAC_1;
	ptr_OutFrame[11] 	= MAC_0;

	if (TCPCode & TCP_CODE_SYN)
		TxFrame2Size = IP_HEADER_SIZE + TCP_HEADER_SIZE + TCP_OPT_MSS_SIZE;
	else
		TxFrame2Size = IP_HEADER_SIZE + TCP_HEADER_SIZE;

	// IP
	*(uint16_t *) &ptr_OutFrame[ETH_TYPE_OFS] 			= SWAPB(FRAME_IP);
	*(uint16_t *) &ptr_OutFrame[IP_VER_IHL_TOS_OFS] 	= SWAPB(IP_VER_IHL);
	// if SYN, we want to use the MSS option
	if (TCPCode & TCP_CODE_SYN){
		*(uint16_t *) &ptr_OutFrame[IP_TOTAL_LENGTH_OFS] = SWAPB(IP_HEADER_SIZE + TCP_HEADER_SIZE + TCP_OPT_MSS_SIZE);
	}
	else{
		*(uint16_t *) &ptr_OutFrame[IP_TOTAL_LENGTH_OFS] = SWAPB(IP_HEADER_SIZE + TCP_HEADER_SIZE);
	}
	*(uint16_t *) &ptr_OutFrame[IP_IDENT_OFS] 		= 0;
	*(uint16_t *) &ptr_OutFrame[IP_FLAGS_FRAG_OFS] 	= 0;
	*(uint16_t *) &ptr_OutFrame[IP_TTL_PROT_OFS] 	= SWAPB((DEFAULT_TTL << 8) | PROT_TCP);
	*(uint16_t *) &ptr_OutFrame[IP_HEAD_CHKSUM_OFS] = 0;
	memcpy(&ptr_OutFrame[IP_SOURCE_OFS], MyIP, 4);
	memcpy(&ptr_OutFrame[IP_DESTINATION_OFS], RemoteIP, 4);
	*(uint16_t *) &ptr_OutFrame[IP_HEAD_CHKSUM_OFS] = CalcChecksum( &ptr_OutFrame[IP_VER_IHL_TOS_OFS], IP_HEADER_SIZE, 0);

	// TCP
	WriteWBE(&ptr_OutFrame[TCP_SRCPORT_OFS], TCPLocalPort);
	WriteWBE(&ptr_OutFrame[TCP_DESTPORT_OFS], TCPRemotePort);
	WriteDWBE(&ptr_OutFrame[TCP_SEQNR_OFS], TCPSeqNr);
	WriteDWBE(&ptr_OutFrame[TCP_ACKNR_OFS], TCPAckNr);
	*(uint16_t *) &ptr_OutFrame[TCP_WINDOW_OFS] = SWAPB(MAX_TCP_RX_DATA_SIZE);  			// data bytes to accept
	*(uint16_t *) &ptr_OutFrame[TCP_CHKSUM_OFS] = 0;    	 								// initalize checksum
	*(uint16_t *) &ptr_OutFrame[TCP_URGENT_OFS] = 0;

	if (TCPCode & TCP_CODE_SYN){         													// if SYN, we want to use the MSS option
		*(uint16_t *) &ptr_OutFrame[TCP_DATA_CODE_OFS] 	= SWAPB( 0x6000 | TCPCode); 		// TCP header length = 24
		*(uint16_t *) &ptr_OutFrame[TCP_DATA_OFS] 		= SWAPB(TCP_OPT_MSS);  				// MSS option
		*(uint16_t *) &ptr_OutFrame[TCP_DATA_OFS + 2] 	= SWAPB(MAX_TCP_RX_DATA_SIZE);		// max. length of TCP-data we accept
		*(uint16_t *) &ptr_OutFrame[TCP_CHKSUM_OFS] 	= CalcChecksum(&ptr_OutFrame[TCP_SRCPORT_OFS], TCP_HEADER_SIZE + TCP_OPT_MSS_SIZE, 1);
		*(uint32_t*)&TxFrame2[0] = ETH_HEADER_SIZE + IP_HEADER_SIZE + TCP_HEADER_SIZE + TCP_OPT_MSS_SIZE;
	}
	else {
		*(uint16_t *) &ptr_OutFrame[TCP_DATA_CODE_OFS] 	= SWAPB(0x5000 | TCPCode);   // TCP header length = 20
		*(uint16_t *) &ptr_OutFrame[TCP_CHKSUM_OFS] 	= standard_chksum_opt(&ptr_OutFrame[TCP_SRCPORT_OFS], TCP_HEADER_SIZE, 1);
		*(uint32_t*)&TxFrame2[0] = ETH_HEADER_SIZE + IP_HEADER_SIZE + TCP_HEADER_SIZE;
	}
	TransmitControl |= SEND_FRAME2;
}

/**
  * @brief	Prepares the TxFrame1-buffer to send a payload-packet.
  * @param	None
  * @retval None
  */
void PrepareTCP_DATA_FRAME(void)
{
	uint8_t * ptr_OutFrame = (uint8_t *) &TxFrame1[4];
	// Ethernet
	/* Set destanation MAC address */
	*(uint32_t *) &ptr_OutFrame[0] = (((((uint8_t) (RecdFrameMAC[1] >> 8) & 0xFF) << 24)
			                       | (((uint8_t) RecdFrameMAC[1] & 0xFF) << 16)
			                       | (((uint8_t) (RecdFrameMAC[0] >> 8) & 0xFF) << 8)
			                       | ((uint8_t) RecdFrameMAC[0] & 0xFF)));

	*(uint16_t *) &ptr_OutFrame[4] = ((((uint8_t) (RecdFrameMAC[2] >> 8) & 0xFF) << 8)
							       | ((uint8_t) RecdFrameMAC[2] & 0xFF));
	/* Set our MAC address */
	ptr_OutFrame[6] 	= MAC_5;
	ptr_OutFrame[7] 	= MAC_4;
	ptr_OutFrame[8] 	= MAC_3;
	ptr_OutFrame[9] 	= MAC_2;
	ptr_OutFrame[10] 	= MAC_1;
	ptr_OutFrame[11] 	= MAC_0;
	// IP
	*(uint16_t *) &ptr_OutFrame[ETH_TYPE_OFS] 		= SWAPB(FRAME_IP);
	*(uint16_t *) &ptr_OutFrame[IP_VER_IHL_TOS_OFS]	= SWAPB(IP_VER_IHL);
	WriteWBE(&ptr_OutFrame[IP_TOTAL_LENGTH_OFS], IP_HEADER_SIZE + TCP_HEADER_SIZE + TCPTxDataCount);
	*(uint16_t *) &ptr_OutFrame[IP_IDENT_OFS] 		= SWAPB(Ident++);
	if ((Ident * DATA_LEN) > 65535)
		Ident = 1;
	*(uint16_t *) &ptr_OutFrame[IP_FLAGS_FRAG_OFS] 	= 0;
	*(uint16_t *) &ptr_OutFrame[IP_TTL_PROT_OFS] 	= SWAPB((DEFAULT_TTL << 8) | PROT_TCP);
	*(uint16_t *) &ptr_OutFrame[IP_HEAD_CHKSUM_OFS] = 0;
	memcpy(&ptr_OutFrame[IP_SOURCE_OFS], MyIP, 4);
	memcpy(&ptr_OutFrame[IP_DESTINATION_OFS], RemoteIP, 4);
	*(uint16_t *) &ptr_OutFrame[IP_HEAD_CHKSUM_OFS] = CalcChecksum(&ptr_OutFrame[IP_VER_IHL_TOS_OFS], IP_HEADER_SIZE, 0);

	// TCP
	WriteWBE(&ptr_OutFrame[TCP_SRCPORT_OFS], TCPLocalPort);
	WriteWBE(&ptr_OutFrame[TCP_DESTPORT_OFS], TCPRemotePort);

	WriteDWBE(&ptr_OutFrame[TCP_SEQNR_OFS], TCPSeqNr);
	WriteDWBE(&ptr_OutFrame[TCP_ACKNR_OFS], TCPAckNr);
	*(uint16_t *) &ptr_OutFrame[TCP_DATA_CODE_OFS] 	= SWAPB(0x5000 | TCP_CODE_ACK);   // TCP header length = 20
	*(uint16_t *) &ptr_OutFrame[TCP_WINDOW_OFS] 	= SWAPB(MAX_TCP_RX_DATA_SIZE);       // data bytes to accept
	*(uint16_t *) &ptr_OutFrame[TCP_CHKSUM_OFS] 	= 0;
	*(uint16_t *) &ptr_OutFrame[TCP_URGENT_OFS] 	= 0;
	*(uint16_t *) &ptr_OutFrame[TCP_CHKSUM_OFS] 	= CalcChecksum_TCP(&ptr_OutFrame[TCP_SRCPORT_OFS], pData, TCP_HEADER_SIZE, TCPTxDataCount, 1);

	/*  */
	uint32_t i = 0;;
	while(i < TCPTxDataCount){
		*(uint16_t *)&ptr_OutFrame[i + TCP_DATA_OFS] = *(uint16_t *)&pData[i];
		i += 2;
	}
	if(i)
		*(uint16_t *)&ptr_OutFrame[i + TCP_DATA_OFS] = *(uint16_t *)&pData[i];

	*(uint32_t *)&TxFrame1[0] = TxFrame1Size;
}

/**
  * @brief	Calculates the TCP/IP checksum. if 'IsTCP != 0', the TCP pseudo-header
  * 		will be included.
  * @param	Start: pointer to input array.
  * @param	Count: number of the half-word in the input array.
  * @parma	IsTCP: a sign, which requires TCP checksum.
  * @retval	Checksum.
  */
uint16_t CalcChecksum(void * Start, uint16_t Count, uint16_t IsTCP)
{
  unsigned long Sum = 0;
  unsigned short * piStart;

  if (IsTCP) {                                   // if we've a TCP frame...
    Sum += MyIP[0];                              // ...include TCP pseudo-header
    Sum += MyIP[1];
    Sum += RemoteIP[0];
    Sum += RemoteIP[1];
    Sum += SwapBytes(Count);                     // TCP header length plus data length
    Sum += SWAPB(PROT_TCP);
  }

  piStart = Start;
  while (Count > 1) {                            // sum words
    Sum += *piStart++;
    Count -= 2;
  }

  if (Count)                                     // add left-over byte, if any
    Sum += *(unsigned char *)piStart;

  while (Sum >> 16)                              // fold 32-bit sum to 16 bits
    Sum = (Sum & 0xFFFF) + (Sum >> 16);

  return (~Sum);
}

/**
  * @brief	Calculates the TCP/IP data checksum.
  * @param	Start: pointer to input array.
  * @param	Count: number of the half-word in the input array.
  * @param 	CData: number of TCP/IP data.
  * @parma	IsTCP: a sign, which requires TCP checksum.
  * @retval	Checksum.
  */
uint16_t CalcChecksum_TCP(void * Start, void * data, uint16_t Count, uint32_t CData,  uint8_t IsTCP)
{
  uint32_t Sum = 0;
  uint16_t * piStart;                        	// Keil: Pointer added to correct expression

  if (IsTCP) {                                   	// if we've a TCP frame...
    Sum += MyIP[0];                              	// ...include TCP pseudo-header
    Sum += MyIP[1];
    Sum += RemoteIP[0];
    Sum += RemoteIP[1];
    Sum += SwapBytes(Count + CData);                // TCP header length plus data length
    Sum += SWAPB(PROT_TCP);
  }

  piStart = Start;                               	// Keil: Line added
  while (Count > 1) {                            	// sum words
    Sum += *piStart++;
    Count -= 2;
  }

  if (Count)                                     	// add left-over byte, if any
    Sum += *(uint8_t *)piStart;

  piStart = data;                               	// Keil: Line added
  while (CData > 1) {                            	// sum words
    Sum += *piStart++;
    CData -= 2;
  }

  if (CData)                                     	// add left-over byte, if any
    Sum += *(uint8_t *)piStart;

  while (Sum >> 16)                              	// fold 32-bit sum to 16 bits
    Sum = (Sum & 0xFFFF) + (Sum >> 16);

  return (~Sum);

}

#define FOLD_U32T(u)          (((u) >> 16) + ((u) & 0x0000ffffUL))
#define SWAP_BYTES_IN_WORD(w) (((w) & 0xff) << 8) | (((w) & 0xff00) >> 8)
/**
  * @brief	An optimized checksum routine. Basically, it uses loop-unrolling on
 * 			the checksum loop, treating the head and tail bytes specially, whereas
 * 			the inner loop acts on 8 bytes at a time.
  * @param	dataptr: start of buffer to be checksummed. May be an odd byte address.
  * @param  len: number of bytes in the buffer to be checksummed.
  * @parma	IsTCP: a sign, which requires TCP checksum.
  * @retval Checksum.
  */
uint16_t standard_chksum_opt(void *dataptr,  uint32_t len, uint8_t IsTCP)
{
	uint8_t *pb = (uint8_t *) dataptr;
	uint16_t *ps, t = 0;
	uint32_t *pl;
	uint32_t sum = 0, tmp;
	/* starts at odd byte address? */
	int32_t odd = ((uint32_t) pb & 1);

	if (IsTCP) {                                   // if we've a TCP frame...
		sum += MyIP[0];                          // ...include TCP pseudo-header
		sum += MyIP[1];
		sum += RemoteIP[0];
		sum += RemoteIP[1];
		sum += SwapBytes(len);            		 // TCP header length plus data length
		sum += SWAPB(PROT_TCP);
	}

	if (odd && len > 0) {
		((uint8_t *) &t)[1] = *pb++;
		len--;
	}

	ps = (uint16_t *) pb;

	if (((uint32_t) ps & 3) && len > 1) {
		sum += *ps++;
		len -= 2;
	}

	pl = (uint32_t *) ps;

	while (len > 7) {
		tmp = sum + *pl++; /* ping */
		if (tmp < sum) {
			tmp++; /* add back carry */
		}

		sum = tmp + *pl++; /* pong */
		if (sum < tmp) {
			sum++; /* add back carry */
		}

		len -= 8;
	}

	/* make room in upper bits */
	sum = FOLD_U32T(sum);

	ps = (uint16_t *) pl;

	/* 16-bit aligned word remaining? */
	while (len > 1) {
		sum += *ps++;
		len -= 2;
	}

	/* dangling tail byte remaining? */
	if (len > 0) { /* include odd byte */
		((uint8_t *) &t)[0] = *(uint8_t *) ps;
	}

	sum += t; /* add end bytes */

	/* Fold 32-bit sum to 16 bits
	 calling this twice is propably faster than if statements... */
	sum = FOLD_U32T(sum);
	sum = FOLD_U32T(sum);

	if (odd) {
		sum = SWAP_BYTES_IN_WORD(sum);
	}

	return ((uint16_t) ~sum);
}

/**
  * @brief	Starts the timer as a retry-timer (used for retransmission-timeout).
  * @param	None
  * @retval	None
  */
void TCPStartRetryTimer(void)
{
  TCPTimer = 0;
  RetryCounter = MAX_RETRYS;
  TCPFlags |= TCP_TIMER_RUNNING;
  TCPFlags |= TIMER_TYPE_RETRY;
}

/**
  * @brief	Starts the timer as a 'TIME_WAIT'-timer (used to finish a TCP-session).
  * @param	None
  * @retval	None
  */
void TCPStartTimeWaitTimer(void)
{
  TCPTimer = 0;
  TCPFlags |= TCP_TIMER_RUNNING;
  TCPFlags &= ~TIMER_TYPE_RETRY;
}

/**
  * @brief	Restarts the timer.
  * @param	None
  * @retval	None
  */
void TCPRestartTimer(void)
{
  TCPTimer = 0;
}

/**
  * @brief	Stopps the timer.
  * @param	None
  * @retval	None
  */
void TCPStopTimer(void)
{
  TCPFlags &= ~TCP_TIMER_RUNNING;
}

/**
  * @brief	If a retransmission-timeout occured, check which packet	to resend.
  * @param	None
  * @retval	None
  */
void TCPHandleRetransmission(void)
{
  switch (LastFrameSent)
  {
    case ARP_REQUEST :       { PrepareARP_REQUEST(); break; }
    case TCP_SYN_FRAME :     { PrepareTCP_FRAME(TCP_CODE_SYN); break; }
    case TCP_SYN_ACK_FRAME : { PrepareTCP_FRAME(TCP_CODE_SYN | TCP_CODE_ACK); break; }
    case TCP_FIN_FRAME :     { PrepareTCP_FRAME(TCP_CODE_FIN | TCP_CODE_ACK); break; }
    case TCP_DATA_FRAME :    { TransmitControl |= SEND_FRAME1; break; }
  }
}

/**
  * @brief	If all retransmissions failed, close connection and indicate an error.
  * @param	None
  * @retval	None
  */
void TCPHandleTimeout(void)
{
  TCPStateMachine = CLOSED;

  if ((TCPFlags & (TCP_ACTIVE_OPEN | IP_ADDR_RESOLVED)) == TCP_ACTIVE_OPEN)
    SocketStatus = SOCK_ERR_ARP_TIMEOUT;         // indicate an error to user
  else
    SocketStatus = SOCK_ERR_TCP_TIMEOUT;

  TCPFlags = 0;                                  // clear all flags
}

/**
  * @brief	Function executed every 0.210s by the CPU. used for the
  * @param	initial sequence number generator (ISN) and the TCP-timer.
  * @retval	None
  */
void TCPClockHandler ( void )   // Keil: interrupt service routine for timer 3
{
	TIMER_Cmd(MDR_TIMER1, DISABLE);
	TIMER_SetCounter(MDR_TIMER1, 0);

	ISNGenHigh++;                    				// upper 16 bits of initial sequence number
	TCPTimer++;                                    	// timer for retransmissions
	if (TCPStateMachine == CLOSED)
		TCPPassiveOpen();

	TIMER_Cmd(MDR_TIMER1, ENABLE);
}

/**
  * @brief	Help function to write a WORD in big-endian byte-order to MCU-memory.
  * @param	Add: pointer to memory.
  * @param	Data: input value.
  * @retval	None
  */
void WriteWBE(uint8_t * Add, uint16_t Data)
{
  *Add++ = Data >> 8;
  *Add = Data;
}

/**
  * @brief	help function to write a DWORD in big-endian byte-order
  * 		to MCU-memory.
  * @param	Add: pointer to memory.
  * @param	Data: input value.
  * @retval
  */
void WriteDWBE(uint8_t *Add, uint32_t Data)
{
  *Add++ = Data >> 24;
  *Add++ = Data >> 16;
  *Add++ = Data >> 8;
  *Add = Data;
}

/**
  * @brief	Help function to swap the byte order of a WORDþ
  * @param	Data: input value.
  * @retval	swaped data.
  */
uint16_t SwapBytes(uint16_t Data)
{
  return ((Data >> 8) | (Data << 8));
}

/** @} */ /* End of group Ethernet_1T */

/** @} */ /* End of group __MDR1986VE1T_EVAL MDR1986VE1T Opora Evaluation Board */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Examples */
