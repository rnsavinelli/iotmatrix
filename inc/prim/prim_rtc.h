/*
 * pr_rtc.h
 *
 *  Created on: Sep 27, 2019
 *      Author: R. Nicolás Savinelli, Tomás Arbia, Kevin Chon, Juan Ignacio Piccardi
 */

#ifndef PRIM_PRIM_RTC_H_
#define PRIM_PRIM_RTC_H_


/*Funciones*/
void setTime(uint32_t sec, uint32_t min, uint32_t hour);
void setDate(uint32_t dom, uint32_t month, uint32_t year);
void getTime(uint32_t* sec, uint32_t* min, uint32_t* hour);
void getDate(uint32_t* dom, uint32_t* month, uint32_t* year);
void horaToStr(uint32_t hora , uint32_t minutos);


#endif /* PRIM_PRIM_RTC_H_ */
