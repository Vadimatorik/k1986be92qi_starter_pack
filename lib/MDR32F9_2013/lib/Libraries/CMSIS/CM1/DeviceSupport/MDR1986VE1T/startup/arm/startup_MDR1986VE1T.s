;/*****************************************************************************/
;/* 1986VE1T.s: Startup file for ARM Cortex-M1 Device Family                   */
;/*****************************************************************************/
;/* <<< Use Configuration Wizard in Context Menu >>>                          */
;/*****************************************************************************/
;/* This file is part of the uVision/ARM development tools.                   */
;/* Copyright (c) 2005-2008 Keil Software. All rights reserved.               */
;/* This software may only be used under the terms of a valid, current,       */
;/* end user licence from KEIL for a compatible version of KEIL software      */
;/* development tools. Nothing else gives you the right to use this software. */
;/*****************************************************************************/


;// <h> Stack Configuration
;//   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;// </h>

Stack_Size      EQU     0x00001000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


;// <h> Heap Configuration
;//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;// </h>

Heap_Size       EQU     0x00001000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                
				DCD     MIL_STD_1553B2_Handler		;IRQ0
				DCD     MIL_STD_1553B1_Handler		;IRQ1
				DCD     USB_Handler					;IRQ2
				DCD     CAN1_Handler				;IRQ3
				DCD     CAN2_Handler				;IRQ4
				DCD     DMA_Handler					;IRQ5
				DCD     UART1_Handler				;IRQ6
				DCD     UART2_Handler				;IRQ7
				DCD     SSP1_Handler				;IRQ8
				DCD     BUSY_Handler				;IRQ9
				DCD     ARINC429R_Handler			;IRQ10
				DCD     POWER_Handler				;IRQ11
				DCD     WWDG_Handler				;IRQ12
				DCD     TIMER4_Handler				;IRQ13
				DCD     TIMER1_Handler				;IRQ14
				DCD     TIMER2_Handler				;IRQ15
				DCD     TIMER3_Handler				;IRQ16
				DCD     ADC_Handler					;IRQ17
				DCD     ETHERNET_Handler			;IRQ18
				DCD     SSP3_Handler				;IRQ19
				DCD     SSP2_Handler				;IRQ20
				DCD     ARINC429T1_Handler			;IRQ21
				DCD     ARINC429T2_Handler			;IRQ22
				DCD     ARINC429T3_Handler			;IRQ23
				DCD     ARINC429T4_Handler			;IRQ24
				DCD     0							;IRQ25
				DCD     0							;IRQ26
				DCD     BKP_Handler					;IRQ27
				DCD     EXT_INT1_Handler			;IRQ28
				DCD     EXT_INT2_Handler			;IRQ29
				DCD     EXT_INT3_Handler			;IRQ30
				DCD     EXT_INT4_Handler			;IRQ31

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler			[WEAK]
                IMPORT  __main
                LDR     R0,=__main
				BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)                

NMI_Handler     PROC
                EXPORT  NMI_Handler				[WEAK]
                B       .
                ENDP

HardFault_Handler PROC
                EXPORT  HardFault_Handler		[WEAK]
                B       .
                ENDP

SVC_Handler     PROC
                EXPORT  SVC_Handler				[WEAK]
                B       .
                ENDP

PendSV_Handler  PROC
                EXPORT  PendSV_Handler			[WEAK]
                B       .
                ENDP

SysTick_Handler PROC
                EXPORT  SysTick_Handler			[WEAK]
				B       .
                ENDP

; External Interrupts

MIL_STD_1553B2_Handler	PROC
                EXPORT  MIL_STD_1553B2_Handler	[WEAK]
				B       .
                ENDP

MIL_STD_1553B1_Handler	PROC
                EXPORT  MIL_STD_1553B1_Handler	[WEAK]
				B       .
                ENDP

USB_Handler		PROC
				EXPORT  USB_Handler				[WEAK]
				B       .
                ENDP
                
CAN1_Handler	PROC
				EXPORT  CAN1_Handler			[WEAK]
				B       .
                ENDP

CAN2_Handler	PROC
				EXPORT  CAN2_Handler			[WEAK]
				B       .
                ENDP

DMA_Handler		PROC
				EXPORT  DMA_Handler				[WEAK]
				B       .
                ENDP

UART1_Handler	PROC
				EXPORT  UART1_Handler			[WEAK]
				B       .
                ENDP

UART2_Handler	PROC
				EXPORT  UART2_Handler			[WEAK]
				B       .
                ENDP

SSP1_Handler	PROC
				EXPORT  SSP1_Handler			[WEAK]
				B       .
                ENDP

BUSY_Handler	PROC
				EXPORT  BUSY_Handler				[WEAK]
				B       .
                ENDP

ARINC429R_Handler	PROC
                EXPORT  ARINC429R_Handler		[WEAK]
				B       .
                ENDP

POWER_Handler	PROC
				EXPORT  POWER_Handler			[WEAK]
				B       .
                ENDP

WWDG_Handler	PROC
				EXPORT  WWDG_Handler			[WEAK]
				B       .
                ENDP

TIMER4_Handler	PROC
				EXPORT  TIMER4_Handler			[WEAK]
				B       .
                ENDP

TIMER1_Handler	PROC
				EXPORT  TIMER1_Handler			[WEAK]
				B       .
                ENDP

TIMER2_Handler	PROC
				EXPORT  TIMER2_Handler			[WEAK]
				B       .
                ENDP

TIMER3_Handler	PROC
				EXPORT  TIMER3_Handler			[WEAK]
				B       .
                ENDP

ADC_Handler		PROC
				EXPORT  ADC_Handler				[WEAK]
				B       .
                ENDP

ETHERNET_Handler	PROC
				EXPORT  ETHERNET_Handler		[WEAK]
				B       .
                ENDP

SSP3_Handler	PROC
				EXPORT  SSP3_Handler			[WEAK]
				B       .
                ENDP

SSP2_Handler	PROC
				EXPORT  SSP2_Handler			[WEAK]
				B       .
                ENDP

ARINC429T1_Handler	PROC
				EXPORT  ARINC429T1_Handler		[WEAK]
				B       .
                ENDP
                
ARINC429T2_Handler	PROC
				EXPORT  ARINC429T2_Handler		[WEAK]
				B       .
                ENDP

ARINC429T3_Handler	PROC
				EXPORT  ARINC429T3_Handler		[WEAK]
				B       .
                ENDP

ARINC429T4_Handler	PROC
				EXPORT  ARINC429T4_Handler		[WEAK]
				B       .
                ENDP

BKP_Handler		PROC
				EXPORT  BKP_Handler				[WEAK]
				B       .
                ENDP

EXT_INT1_Handler	PROC
				EXPORT  EXT_INT1_Handler		[WEAK]
				B       .
                ENDP

EXT_INT2_Handler	PROC
				EXPORT  EXT_INT2_Handler		[WEAK]
				B       .
                ENDP

EXT_INT3_Handler	PROC
				EXPORT  EXT_INT3_Handler		[WEAK]
				B       .
                ENDP

EXT_INT4_Handler	PROC
				EXPORT  EXT_INT4_Handler		[WEAK]
				B       .
                ENDP

                ALIGN



; User Initial Stack & Heap

                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
