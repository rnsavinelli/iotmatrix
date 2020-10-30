/*
 * dr_systick.c
 *
 *  Created on: Sep 27, 2019
 *      Author: R. Nicolás Savinelli, Tomás Arbia, Kevin Chon, Juan Ignacio Piccardi
 */

#include "driv_matrix.h"
#include "driv_gpio.h"
#include "driv_systick.h"
#include "prim_systick.h"
#include "prim_uart.h"
#include "MdESistema.h"

uint8_t tim_flag[NTIMERS];
uint32_t tim_t[NTIMERS];

extern uint8_t  config_fin;

extern void disk_timerproc (void);

void InicializarSysTick(void)
{
	STRELOAD = (STCALIB+1)/10-1;	//1ms interruption
	STCURR = 0;						//Initial count

	CLKSOURCE = 1;	//CLKSOURCE: CCLK selected
	TICKINT = 1;	//TICKINT: interrupt enabled
	ENABLE = 1;		//ENABLE: counter enabled
}

void SysTick_Handler(void)
{
	//static uint8_t estado;
	GetTeclaSW();
	AnalizeTimer();
	BarridoMatrix();

	if(config_fin == 0)
		Recepcion_ModuloWifi();
	if(config_fin == 1)
		Recepcion_ModuloWifi_Data();

	disk_timerproc();	/* Disk timer process */
}

void AnalizeTimer(void)
{
	uint8_t i;
	for(i=0;i<NTIMERS;i++)
		if(tim_t[i])
		{
			tim_t[i]--;
			if(!tim_t[i])
				tim_flag[i]=1;
		}
}
