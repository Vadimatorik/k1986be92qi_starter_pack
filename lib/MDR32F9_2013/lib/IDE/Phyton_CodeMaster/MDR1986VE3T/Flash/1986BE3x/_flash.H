#ifndef __FLASH_H__
#define __FLASH_H__

#include "..\..\Common\Common.h"

//extern ulong JTAG_Part_ID;
//extern uchar JTAG_Flash_Status;

//void IAP_PrepareMCU();
void IAP_EraseAllFlash();
//void JTAG_RdID();
//uchar JTAG_EraseAll_woConf();
//void InitSFRs();

//void PrepareConfig();
//void JTAG_SetConfiguration(uchar Remap);
//void JTAG_GetConfiguration();

//uchar ErrAnyBankParams(ulong Remap, uchar EnaMsg);

#include "1986BE3.h"


#ifdef __DEBUG__
//#undef __DEBUG__
#endif

//#define __GENERIC_CHIP__

#endif
