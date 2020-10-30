/*
 * dr_gpio.h
 *
 *  Created on: Sep 27, 2019
 *      Author: R. Nicolás Savinelli, Tomás Arbia, Kevin Chon, Juan Ignacio Piccardi
 */

#ifndef DR_GPIO_H_
#define DR_GPIO_H_
#endif /* DR_GPIO_H_ */

#include "DR_tipos.h"

/*GPIO Register Directions*/
#define GPIO   	( ( __RW uint32_t * )  0x2009C000 )
	#define ENTRADA 	0
	#define SALIDA 		1
#define PINSEL 	( ( __RW uint32_t * )  0x4002C000 )
#define PINMODE	( ( __RW uint32_t * )  0x4002C040 )
	#define PULLUP 		0
	#define REPEATER 	1
	#define NONE 		2
	#define PULLDOWN 	3

/*PORTS*/
//->para manejar la matriz de leds
#define M_DIN 2,7	//DIN: DataIn		Expansion 0
#define M_CLK 1,19	//CLK: Clock		Expansion 9
#define M_CS 1,27	//CS: ChipSelect	Expansion 12
//->para manejar SW
#define BUTTON1 	2,10	//Velocity down
#define BUTTON2 	0,18	//Velocity up
#define BUTTON3 	0,11	//Toggle direction
#define BUTTON4 	2,13	//Toggle mode
//->para manejar led rgb stick
#define GREEN 	3,25
#define BLUE 	3,26
#define RED 	0,22
//->para manejar modulo wifi
#define RST 	2,12	//RST: Reset	Expansion 17
#define CH_PD 	3,26	//CH_PD:		Expansion 16

/*DEFINES*/
#define K0 		0
#define K1		1
#define K2 		2
#define K3 		3
#define NO_K 	255

#define MAX_REBOTES 5

/*Functions*/
//->Teclado, RGB
void InitButtons(void);
	uint8_t GetTeclaHW(void);
	void GetTeclaSW(void);
void InitLedRGB(void);
void InitModuloWifi(void);

//->GPIO
void SetPINSEL_    	(uint8_t port, uint8_t pin, uint8_t sel);
void SetMODE_   	(uint8_t port, uint8_t pin, uint8_t sel);
void SetDIR_        (uint8_t port, uint8_t pin, uint8_t dir);
void SetPIN_        (uint8_t port, uint8_t pin, uint8_t est);
uint8_t GetPIN_    	(uint8_t port, uint8_t pin);



