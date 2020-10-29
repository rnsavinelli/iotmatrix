/*
 * dr_gpio.c
 *
 *  Created on: Sep 27, 2019
 *      Author: oem
 */

#include "driv_gpio.h"
#include "prim_gpio.h"

extern uint8_t teclado;

uint8_t GetTeclaHW(void)
{
	uint8_t state = NO_K;

	if(!GetPIN_(BUTTON1))
		state = K0;
	else if(!GetPIN_(BUTTON2))
		state = K1;
	else if(!GetPIN_(BUTTON3))
		state = K2;
	else if(!GetPIN_(BUTTON4))
		state = K3;
	else
		state = NO_K;

	return state;
}

void GetTeclaSW(void)
{
	static uint8_t lastKey = NO_K;
	static uint8_t contador = 0;
	uint8_t key;

	key = GetTeclaHW();

	if(lastKey == key && contador < MAX_REBOTES)
	{
		contador++;
		if(contador == MAX_REBOTES)
			teclado = key;
	}
	else if(lastKey != key)
		contador = 0;

	lastKey = key;
}

void InitLedRGB(void)
{
	//LED RGB Micro
	SetPINSEL_(RED,0);
	SetPINSEL_(GREEN,0);
	SetPINSEL_(BLUE,0);

	SetDIR_(RED,SALIDA);
	SetDIR_(GREEN,SALIDA);
	SetDIR_(BLUE,SALIDA);

	//LED RGB Infotronic
	SetPINSEL_(2,0,0);
	SetPINSEL_(2,1,0);
	SetPINSEL_(2,2,0);

	SetDIR_(2,0,SALIDA);
	SetDIR_(2,1,SALIDA);
	SetDIR_(2,2,SALIDA);
}

void InitButtons(void)
{
	SetPINSEL_(BUTTON1,0);	//Velocity up
	SetPINSEL_(BUTTON2,0);	//Velocity down
	SetPINSEL_(BUTTON3,0);	//Toggle direction
	SetPINSEL_(BUTTON4,0);	//Toggle mode

	SetDIR_(BUTTON1,ENTRADA);
	SetDIR_(BUTTON2,ENTRADA);
	SetDIR_(BUTTON3,ENTRADA);
	SetDIR_(BUTTON4,ENTRADA);

	SetMODE_(BUTTON1,PULLUP);
	SetMODE_(BUTTON2,PULLUP);
	SetMODE_(BUTTON3,PULLUP);
	SetMODE_(BUTTON4,PULLUP);
}

/*FUNCIONES PARA TOCAR REGISTROS*/
void SetPINSEL_(uint8_t port, uint8_t pin, uint8_t sel)
{
    PINSEL[2*port+pin/16] &= ~(0x03 <<pin*2);    //Borro el par de bits del (port,pin) determinado
    PINSEL[2*port+pin/16] |= (sel <<pin*2);        //Escribo el par de bits
}

void SetMODE_(uint8_t port, uint8_t pin, uint8_t sel)
{
    PINMODE[2*port+pin/16] &= ~(0x03 <<pin*2);    //Borro el par de bits del (port,pin) determinado
    PINMODE[2*port+pin/16] |= (sel <<pin*2);    //Escribo el par de bits
}

void SetDIR_(uint8_t port, uint8_t pin, uint8_t dir)
{
    if(!dir)
        GPIO[port*8]&=~(1<<pin);
    else
        GPIO[port*8]|=(1<<pin);
}

void SetPIN_(uint8_t port, uint8_t pin, uint8_t est)
{
    if(!est)
        GPIO[port*8+5]&=~(1<<pin);
    else
        GPIO[port*8+5]|=(1<<pin);
}

uint8_t GetPIN_(uint8_t port, uint8_t pin)
{
    return (GPIO[port*8+5]&(1<<pin))>>pin;
}
