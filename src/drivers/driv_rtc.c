/*
 * dr_rtc.c
 *
 *  Created on: Sep 27, 2019
 *      Author: oem
 */
#include <driv_rtc.h>

void InitRTC(void)
{
	PCRTC 	= 1; 	//Powers RTC
	CCR[0] 	= 1; 	//CLKEN: Enable clock for time counter
	CCR[1] 	= 0;	//CTCRST: No reset
	CCR[2] 	= 0;	//Recommendation for normal operation
	CCR[3] 	= 0;	//Recommendation for normal operation
	CCR[4]	= 0; 	//CCALEN: Calibration counter enabled

	//Setting initial time...
	SEC 	= 0;
	MINUTO 	= 0;
	HOUR 	= 0;
	DOM 	= 11;
	DOW 	= 2;
	DOY 	= 300;
	MONTH 	= 11;
	YEAR 	= 2019;
}

