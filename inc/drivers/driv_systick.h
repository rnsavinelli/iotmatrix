/*
 * dr_systick.h
 *
 *  Created on: Sep 27, 2019
 *      Author: oem
 */

#ifndef DR_SYSTICK_H_
#define DR_SYSTICK_H_
#endif /* DR_SYSTICK_H_ */

#include "bibliotecaInfoII.h"

void InicializarSysTick(void);
void SysTick_Handler(void);
void AnalizeTimer(void);

#define NTIMERS 8

extern uint8_t tim_flag[NTIMERS];
extern uint32_t tim_t[NTIMERS];
