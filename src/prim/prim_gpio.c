/*
 * pr_gpio.c
 *
 *  Created on: Sep 27, 2019
 *      Author: oem
 */
#include "driv_gpio.h"
#include "prim_gpio.h"

uint8_t teclado;

uint8_t GetTecla(void)
{
	uint8_t aux = NO_K;

	if(teclado != NO_K)
	{
		aux = teclado;
		teclado = NO_K;
	}

	return aux;
}

