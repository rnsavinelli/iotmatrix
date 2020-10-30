/*
 * dr_matrix.c
 *
 *  Created on: Sep 27, 2019
 *      Author: R. Nicolás Savinelli, Tomás Arbia, Kevin Chon, Juan Ignacio Piccardi
 */
#include "driv_gpio.h"
#include "driv_matrix.h"
#include "MdESistema.h"

extern uint8_t orientation;

uint8_t buffer_DIN[32] =
{
	0,0,0,0,0,0,0,0,	//Matriz 1
	0,0,0,0,0,0,0,0,	//Matriz 2
	0,0,0,0,0,0,0,0,	//Matriz 3
	0,0,0,0,0,0,0,0,	//Matriz 4
};

//heart: 0,24,60,126,255,255,102,0,

void BarridoMatrix(void)
{
	static uint8_t fil = 0;
	static uint8_t orientation_anterior = LEFT;
	static uint8_t orientation_actual = LEFT;

	orientation_actual = orientation;

	//Si hay un cambio de orientacion, empieza de cero la columna a imprimir
	if(orientation_anterior != orientation_actual)
	{
		orientation_anterior = orientation_actual;
		fil = 0;
	}

	TransferToMAX7219(fil+1);
	fil++;
	fil%=8;
}

void InitMatrixLeds(void)
{
	SetPINSEL_(M_DIN,0); //CLK
	SetPINSEL_(M_CLK,0); //DIN
	SetPINSEL_(M_CS,0); //CS

	SetDIR_(M_DIN,SALIDA);
	SetDIR_(M_CLK,SALIDA);
	SetDIR_(M_CS,SALIDA);

	SetMODE_(M_DIN,PULLUP);
	SetMODE_(M_CLK,PULLUP);
	SetMODE_(M_CS,PULLUP);

	SetPIN_(M_DIN,0);
	SetPIN_(M_CLK,0);
	SetPIN_(M_CS,0);

	ClearMatrixRegisters();

	TransferToAllMAX7219(AD_SHUTDOWN,0x00);
	TransferToAllMAX7219(AD_DISPLAYTEST,0x00);
	TransferToAllMAX7219(AD_INTENSITY,0x00);
	TransferToAllMAX7219(AD_SCANLIMIT,0x07);
	TransferToAllMAX7219(AD_DECODEMODE,0x00);
	TransferToAllMAX7219(AD_SHUTDOWN,0x01);
}

void ClearMatrixRegisters(void)
{
	uint8_t j;

	for(j=0;j<13;j++)
		TransferToAllMAX7219(j,0x00);

	TransferToAllMAX7219(15,0x00);
}

void TransferToMAX7219(uint8_t address)
{
	uint8_t i,j;
	static uint8_t nFila = 0;

	static uint8_t orientation_anterior = LEFT;
	static uint8_t orientation_actual = LEFT;

	orientation_actual = orientation;
	//Si hay un cambio de orientacion, empieza de cero la fila a imprimir
	if(orientation_anterior != orientation_actual)
	{
		orientation_anterior = orientation_actual;
		nFila = 0;
	}

	SetPIN_(M_CS,0);
	for(j=0;j<NUM_MATRIX;j++)
	{
		for(i = 8; i > 0; i--)
		{
			SetPIN_(M_DIN,(address>>(i-1))&0x01);
			SetPIN_(M_CLK,1);
			SetPIN_(M_CLK,0);
		}
		for(i = 8; i > 0; i--)
		{
			SetPIN_(M_DIN,((buffer_DIN[j*8+nFila])>>(i-1))&0x01);
			SetPIN_(M_CLK,1);
			SetPIN_(M_CLK,0);
		}
	}
	SetPIN_(M_CS,1);

	nFila++;
	nFila%=8;
}

void TransferToAllMAX7219(uint8_t address, uint8_t data)
{
	uint8_t i,j;

	SetPIN_(M_CS,0);
	for(j=0;j<NUM_MATRIX;j++)
	{
		for(i = 8; i > 0; i--)
		{
			SetPIN_(M_DIN,(address>>(i-1))&0x01);
			SetPIN_(M_CLK,1);
			SetPIN_(M_CLK,0);
		}
		for(i = 8; i > 0; i--)
		{
			SetPIN_(M_DIN,(data>>(i-1))&0x01);
			SetPIN_(M_CLK,1);
			SetPIN_(M_CLK,0);
		}
	}
	SetPIN_(M_CS,1);
}
