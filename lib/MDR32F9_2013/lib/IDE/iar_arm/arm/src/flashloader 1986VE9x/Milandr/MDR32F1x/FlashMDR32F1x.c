/**************************************************
 * Copyright 2004-2010 IAR Systems. All rights reserved.
 *
 * $Revision: 29 $
 **************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Milandr\1986be9x.h>

#include "flash_loader.h"

#define STANDBY 0x30L
#define READ    0x00L
#define PROGRAM 0x21L
#define PGERASE 0x22L
#define READCDI 0x0BL
#define READDID 0x0CL

#define flash_unit uint32_t

#define FLASH1               ((uint32_t *)0x00001ff0)
#define FLASH2               ((uint32_t *)0x00001ff4)
#define FLASH3               ((uint32_t *)0x00001ff8)


/*************************************************************************
 * FMC module initialization
 *************************************************************************/

void ProgramDelay(uint32_t Loops)
{
  volatile uint32_t i = Loops;
  for (; i > 0; i--);
}
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

PUTCHAR_PROTOTYPE{
        UART2->DR = ch;
        // Loop until the end of transmission
        while(0 == (UART2->FR & (1UL << 7)));
  return (ch);
}
#if USE_ARGC_ARGV
uint32_t FlashInit(void *base_of_flash, uint32_t image_size,
                   uint32_t link_address, uint32_t flags,
                   int argc, char const *argv[])
#else
uint32_t FlashInit(void *base_of_flash, uint32_t image_size,
                   uint32_t link_address, uint32_t flags)
#endif
{
  /*Enable ISP Clock*/
  /*Enable ISP function*/
  /*Enable ISP function*/
  RST_CLK->PER_CLOCK = 0xFFFFFFFF;
  
  //uint32_t * per2_clock = (uint32_t *)(0x4002000 + 0x38);
  //uint32_t * uart_ssp = (uint32_t *)(0x4002000 + 0x3C);

/*  
  // включаем HSE
  RST_CLK->HS_CONTROL = 1<<0;
  
  while((RST_CLK->CLOCK_STATUS & (1<<2)) == 0);
  
  RST_CLK->CPU_CLOCK = (1<<1) | (1<<8);
  
    // Отладка
  PORTF->FUNC = (3<<0*2) | (3<<1*2);
  PORTF->ANALOG = 0xFFFFFFFF;
  PORTF->PWR = 0xFFFFFFFF;
  
  
  RST_CLK->UART_CLOCK = 1 << 25;
  
  // Настройка UART
  
  UART2->FBRD = 6;
  UART2->IBRD = 52;
  
  UART2->CR = (1<<7) | (1<<8) | (1<<0);
  
  UART2->LCR_H = 3 << 5;
  
  printf("test");

  //UART2->DR = 0x30;
  //while(0 == (UART2->FR & (1UL << 7)));
  
	if(RESULT_ERROR == FlashErase(base_of_flash,512)) 
	  return RESULT_ERROR;
*/  
  
  return RESULT_OK;
}


uint32_t FlashWrite(void *block_start,
                    uint32_t offset_into_block,
                    uint32_t count,
                    char const *buffer)
{
    //printf("\t\tFlashWrite block_start 0x%x, offset_into_block 0x%x, count 0x%X, buffer 0x%x\n\r",(uint32_t)block_start,offset_into_block,count,(uint32_t)buffer);
	
	uint32_t * ptr_buffer = (uint32_t *)buffer;
	
	//for(uint32_t i = 0; i < 16; i++)
	//  printf("data = 0x%x\r\n",ptr_buffer[i]);
	
	//uint32_t * ptr = (uint32_t *)(((uint32_t)block_start) + offset_into_block);
  
	uint32_t size = 0;
	volatile uint32_t y = 0;


	
    RST_CLK->PER_CLOCK = 0xFFFFFFFF;
	while( size < count/4 ){
	  
		EEPROM->KEY = 0x8AAA5551;
		
		EEPROM->CMD = 0x0001 ;
		EEPROM->ADR = (uint32_t) ((uint32_t)block_start + offset_into_block + size*4);
		EEPROM->DI  = ptr_buffer[size];
		
		EEPROM->CMD = 0x1041;	// Set PROG XE EN
		for (y=0;y<40;y++); // 5 мкс
		
		EEPROM->CMD = 0x3041; // SET NVSTR
		for (y=0;y<80;y++);	//10 мкс
		
		EEPROM->CMD = 0x30C1; // SET YE
		for (y=0;y<400;y++); 	//40 мкс
		
		EEPROM->CMD = 0x3041; // CLEAR YE
		EEPROM->CMD = 0x2041;	// CLER PROG 
		for (y=0;y<40;y++);		// 5 мкс
		
		EEPROM->CMD = 0x0001; // CLEAR NVSTR XE
		for (y=0;y<10;y++);
		
		EEPROM->CMD = 0x0000; // CLEAR NVSTR XE
		EEPROM->KEY = 0;
		    
		size++;
	}                

	//for(int i = 0; i < 16; i++)
	//  printf("\tflash_data = 0x%x\r\n", ptr[i]);

    return(RESULT_OK);
}

/*************************************************************************
 * FMC Block erase
 *************************************************************************/
uint32_t FlashErase(void *block_start,
                    uint32_t block_size)
{
	//printf("FlasErase block_start 0x%x, block_size 0x%x\n\r",(uint32_t)block_start,block_size);
	
	if ( (((uint32_t)block_start - 0x08000000)%0x1000) == 0){ 
		//printf("Erasing...\r\n");
		volatile int i,y;
		for(i = 0; i < 4; i++){
			
			RST_CLK->PER_CLOCK = 0xFFFFFFFF;    
			EEPROM->KEY = 0x8AAA5551;
			
			EEPROM->CMD = 0x1;
			EEPROM->ADR = ((uint32_t)block_start) + i*4;
			EEPROM->DI = 0x00;
			//printf("ERASE ADDR = 0x%d\r\n", EEPROM->ADR);
			
			EEPROM->CMD = 0x0441;
			for (y=0;y<40;y++);		// 5 мкс
			
			EEPROM->CMD = 0x2441;
			for (y=0;y<320000/2;y++);
			
			EEPROM->CMD = 0x2041;
			for (y=0;y<40;y++);		// 5 мкс
			
			EEPROM->CMD = 0x0001;
			for (y=0;y<8;y++);		// 1 мкс
			EEPROM->CMD = 0x0;
			EEPROM->KEY = 0;
		}
	}

	return(RESULT_OK);
}



/*************************************************************************
 * FMC deinit
 *************************************************************************/
uint32_t FlashSignoff()
{
  /*Enable ISP function*/
  /*Enable ISP function*/

  
  return RESULT_OK;
}
