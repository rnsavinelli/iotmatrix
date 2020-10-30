/*
 * pr_rtc.c
 *
 *  Created on: Sep 27, 2019
 *      Author: R. Nicolás Savinelli, Tomás Arbia, Kevin Chon, Juan Ignacio Piccardi
 */

#include <driv_rtc.h>

char buff_hora[5];


void setTime(uint32_t sec, uint32_t min, uint32_t hour)
{
	SEC 	= sec;
	MINUTO 	= min;
	HOUR 	= hour;
}

void setDate(uint32_t dom, uint32_t month, uint32_t year)
{
	DOM 	= dom;
	MONTH 	= month;
	YEAR 	= year;
}

void getTime(uint32_t* sec, uint32_t* min, uint32_t* hour)
{
	*sec 	= SEC;
	*min	= MINUTO;
	*hour 	= HOUR;
}

void getDate(uint32_t* dom, uint32_t* month, uint32_t* year)
{
	*dom	= DOM;
	*month	= MONTH;
	*year	= YEAR;
}

void horaToStr(uint32_t hora , uint32_t minutos)
{
	buff_hora[0]= (uint8_t) ((hora/10)+48);  //48 to get ascii character
	buff_hora[1]= (uint8_t) ((hora%10)+48);
	buff_hora[2]= ':';
	buff_hora[3]= (uint8_t) ((minutos/10)+48);
	buff_hora[4]= (uint8_t) ((minutos%10)+48);
}
