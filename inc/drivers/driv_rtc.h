/*
 * dr_rtc.h
 *
 *  Created on: Sep 27, 2019
 *      Author: R. Nicolás Savinelli, Tomás Arbia, Kevin Chon, Juan Ignacio Piccardi
 */

#ifndef DRIV_RTC_H_
#define DRIV_RTC_H_

#include "DR_tipos.h"

/*REGISTROS*/
//->energizar perifericos
#define PCONP	( ( __RW uint32_t * ) 0x400FC0C4 )
	#define PCRTC	PCONP[9]
//->inicializaciones
#define CCR 	( ( __RW uint32_t * ) 0x40024008 )
//->de solo lectura que contiene los tiempos
#define CTIME0  ( ( __RW uint32_t * ) 0x40024014 )
#define CTIME1  ( ( __RW uint32_t * ) 0x40024018 )
#define CTIME2  ( ( __RW uint32_t * ) 0x4002401C )
//->de escritura y lectura que contiene los tiempos
#define SEC 	*( ( __RW uint32_t * ) 0x40024020 )
#define MINUTO 	*( ( __RW uint32_t * ) 0x40024024 )
#define HOUR 	*( ( __RW uint32_t * ) 0x40024028 )
#define DOM 	*( ( __RW uint32_t * ) 0x4002402C )
#define DOW 	*( ( __RW uint32_t * ) 0x40024030 )
#define DOY 	*( ( __RW uint32_t * ) 0x40024034 )
#define MONTH 	*( ( __RW uint32_t * ) 0x40024038 )
#define YEAR 	*( ( __RW uint32_t * ) 0x4002403C )



/*Funciones*/
void InitRTC(void);

#endif /* DRIV_RTC_H_ */
