/*
 * prim_systick.h
 *
 *  Created on: Oct 4, 2019
 *      Author: User
 */

#ifndef PRIM_PRIM_SYSTICK_H_
#define PRIM_PRIM_SYSTICK_H_

#include "bibliotecaInfoII.h"

/*DEFINES*/
#define MSEG	0
#define SEG		1
#define MIN		2

#define VENC	1
#define NO_VENC 0

/*Functions*/
uint8_t TimEvent(uint8_t nrotimer);
void TimStart(uint8_t nrotimer, uint32_t time, uint8_t base);
void TimStop(uint8_t nrotimer);


#endif /* PRIM_PRIM_SYSTICK_H_ */
