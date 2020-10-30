/*
 * prim_systick.c
 *
 *  Created on: Oct 4, 2019
 *      Author: R. Nicolás Savinelli, Tomás Arbia, Kevin Chon, Juan Ignacio Piccardi
 */
#include "prim_systick.h"
#include "driv_systick.h"
#include "bibliotecaInfoII.h"

uint8_t TimEvent(uint8_t nrotimer)
{
	if(tim_flag[nrotimer])
	{
		tim_flag[nrotimer] = 0;
		return VENC;
	}
	return NO_VENC;
}


void TimStart(uint8_t nrotimer, uint32_t time, uint8_t base)
{
	if(base == MSEG)
		tim_t[nrotimer] = time;
	else if(base == SEG)
		tim_t[nrotimer] = time * 1000;
	else if(base == MIN)
		tim_t[nrotimer] = time * 60000;

	tim_flag[nrotimer] = 0;

}

void TimStop(uint8_t nrotimer)
{
	tim_t[nrotimer] = 0;
	tim_flag[nrotimer] = 0;
}
