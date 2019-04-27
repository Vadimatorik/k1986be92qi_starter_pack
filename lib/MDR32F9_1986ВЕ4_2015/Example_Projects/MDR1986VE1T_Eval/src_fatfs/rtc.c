/*------------------------------------------------------------------------/
/  RTC control module
/-------------------------------------------------------------------------/
/
/  Copyright (C) 2013, ChaN, all right reserved.
/  Copyright (C) 2012, Milandr.
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-------------------------------------------------------------------------*/

#include "rtc.h"
#include <MDR32F9Qx_bkp.h>

/*---------------------------------------------------------*/
/* User Provided RTC Function for FatFs module             */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called from     */
/* FatFs module. Any valid time must be returned even if   */
/* the system does not support an RTC.                     */
/* This function is not required in read-only cfg.         */


DWORD get_fattime ()
{
	RTC rtc;

	/* Get local time */
	rtc_gettime(&rtc);

	/* Pack date and time into a DWORD variable */
	return	  ((DWORD)(rtc.year - 1980) << 25)
			| ((DWORD)rtc.month << 21)
			| ((DWORD)rtc.mday << 16)
			| ((DWORD)rtc.hour << 11)
			| ((DWORD)rtc.min << 5)
			| ((DWORD)rtc.sec >> 1);
}


int rtc_initialize (void)
{

	return 1;
}



int rtc_gettime (RTC *rtc)
{

  ULONG TimeVar, temp_date;

    TimeVar = BKP_RTC_GetCounter();
    temp_date   = MDR_BKP->REG_01;

	rtc->sec = (BYTE)(((TimeVar) % 3600) % 60);
	rtc->min = (BYTE)(((TimeVar) % 3600) / 60);
	rtc->hour = (BYTE)(TimeVar / 3600);
	rtc->wday = 0;
	rtc->mday = temp_date >> 24;
	rtc->month = (temp_date >> 16) & 0xFF;
	rtc->year = temp_date & 0xFFFF;
	return 1;
}




int rtc_settime (const RTC *rtc)
{
	return 1;
}


