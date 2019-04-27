/**************************************************
 * Copyright 2004-2010 IAR Systems. All rights reserved.
 *
 * $Revision: 34539 $
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

#define FLASH1               ((uint32_t *)0x08001ff0)
#define FLASH2               ((uint32_t *)0x08001ff4)
#define FLASH3               ((uint32_t *)0x08001ff8)


/*************************************************************************
 * FMC module initialization
 *************************************************************************/
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

  if(RESULT_ERROR == FlashErase(base_of_flash,512)) return RESULT_ERROR;
  
  return RESULT_OK;
}


/*************************************************************************
 * FMC write data
 *************************************************************************/
uint32_t FlashWrite(void *block_start,
                    uint32_t offset_into_block,
                    uint32_t count,
                    char const *buffer)
{
uint32_t size = 0;
volatile uint32_t y = 0;
        RST_CLK->PER_CLOCK = 0xFFFFFFFF;
  	EEPROM->KEY = 0x8AAA5551;
  	EEPROM->CMD = 0x0001 ;
   	EEPROM->ADR = (uint32_t) block_start + offset_into_block + size;
  	EEPROM->DI  = *((flash_unit *)buffer);

        while( size < count )
        {
   	        EEPROM->ADR = (uint32_t) block_start + offset_into_block + size;
	  	for (y=0;y<80;y++)
	  	{	
	  	}
		EEPROM->CMD = 0x1041;	// Set PROG XE EN
	  	for (y=0;y<40;y++)
	  	{	
	  	}
		EEPROM->CMD = 0x3041; // SET NVSTR
	  	EEPROM->DI  = *((flash_unit *)buffer);
		EEPROM->CMD = 0x3043; // SET NVSTR
		EEPROM->CMD = 0x3041; // SET NVSTR
	  	for (y=0;y<100;y++)
	  	{	
	  	}
		EEPROM->CMD = 0x30C1; // SET YE

	  	for (y=0;y<400;y++)
	  	{	
	  	}
		EEPROM->CMD = 0x3041; // CLEAR YE
		EEPROM->CMD = 0x2041;	// CLER PROG 
  		for (y=0;y<40;y++)
  		{	
  		}
		EEPROM->CMD = 0x0001; // CLEAR NVSTR XE
  		for (y=0;y<40;y++)
  		{	
  		}
		EEPROM->CMD = 0x0000; // CLEAR NVSTR XE
      /*increment buffer ptr*/
      buffer += sizeof(flash_unit);
      /*increment data cntr*/
      size += sizeof(flash_unit);
                
        }
        
        
                
    EEPROM->CMD = 0x0;
    y= *FLASH1;
    y= *FLASH2;
    y= *FLASH3;
    return(RESULT_OK);
}

/*************************************************************************
 * FMC Block erase
 *************************************************************************/
uint32_t FlashErase(void *block_start,
                    uint32_t block_size)
{
  
    int i,y;
  RST_CLK->PER_CLOCK = 0xFFFFFFFF;    
  EEPROM->CMD = 0x1;
  EEPROM->KEY = 0x8AAA5551;

  for (y = 0; y<4;y++)
  {
   	EEPROM->ADR = y*4;
  	EEPROM->DI  = 0;
	EEPROM->CMD = 0x0041;
  	for (i=0;i<1000;i++)
  	{	
  	}
	EEPROM->CMD = 0x0c41 ;
  	for (i=0;i<4000;i++)
  	{	
  	}
	EEPROM->CMD = 0x2c41 ;
  	for (i=0;i<160000;i++)
  	{	
  	}
	EEPROM->CMD = 0x2841 ;
  	for (i=0;i<8000;i++)
  	{	
  	}
	EEPROM->CMD = 0x0001 ;
   }
  EEPROM->CMD = 0x0;
  
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
