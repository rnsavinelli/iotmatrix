/*
 * prim_uart.c
 *
 *  Created on: Oct 17, 2019
 *      Author: User
 */

#include "prim_uart.h"
#include "driv_uart.h"

extern uint8_t bufferTX[TAM_BUFFTX];
extern uint16_t in_tx;
extern uint16_t out_tx;

extern uint8_t bufferRX[TAM_BUFFRX];
extern uint16_t in_rx;
extern uint16_t out_rx;

extern uint8_t transmitiendo;

uint8_t rxOK = 0;
uint8_t stringrecibido[74];
uint8_t stringrecibido_ok = 0; //con este flag aviso cuando ya tengo un string listo recibido por el modulo

#define SIGNAL_SAVE			'0'
#define SIGNAL_DISCONNECT	'1'
#define SIGNAL_TEST			'2'
#define SIGNAL_FINISH		'3'

extern uint8_t signal_connect;
extern uint8_t signal_test;
extern uint8_t signal_save;
extern uint8_t signal_disconnect;

void Recepcion_ModuloWifi(void)
{
	static uint8_t estado = 0;
	uint8_t datarx;

	datarx = PopRX_UART1();

	if(datarx != 255)
	{
		switch(estado)
		{
			case 0:
				if(datarx == 'O')
				{
					estado = 1;
				}
				break;
			case 1:
				if(datarx == 'K')
				{
					estado = 0;
					rxOK = 1;
				}
				break;
			default:
				estado = 0;
		}
	}
}

void Recepcion_ModuloWifi_Data(void)
{
	static uint8_t estado = 0;
	uint8_t datarx;
	static uint8_t signal_recibido = 255;
	static uint8_t i = 0; //Recorro el vector 'stringrecibido' para ir llenandolo de datos recibidos por el modulo
	uint8_t j;

	datarx = PopRX_UART1();

	if(datarx != 255)
	{
		switch(estado)
		{
			case 0:
				if(datarx == '#')
				{
					for(j=0; j<72;j++)
						stringrecibido[j]='\0';
					estado = 1;
				}
				break;
			case 1:
				if(datarx == '#')
					estado = 2;
				break;
			case 2:
				if(datarx == SIGNAL_SAVE)
				{
					signal_recibido = datarx;
					estado = 3;
				}
				if(datarx == SIGNAL_DISCONNECT)
				{
					signal_recibido = datarx;
					estado = 3;
				}
				if(datarx == SIGNAL_TEST)
				{
					signal_recibido = datarx;
					estado = 3;
				}
				if(datarx == SIGNAL_FINISH)
				{
					signal_recibido = datarx;
					estado = 3;
				}
				break;
			case 3:
				if(datarx == '#')
					estado = 4;
				break;
			case 4:
				if(datarx == '~')
					estado = 5;
				else if(datarx == '#') //Este caso es un error
					estado = 5;
				else
				{
					stringrecibido[i] = datarx;
					i++;
				}
				break;
			case 5:
				if(datarx == '~')
				{
					stringrecibido_ok = 1;
					estado = 0;
					i = 0;
					if(signal_recibido == SIGNAL_SAVE)
						signal_save = 1;
					if(signal_recibido == SIGNAL_DISCONNECT)
						signal_disconnect = 1;
					if(signal_recibido == SIGNAL_TEST)
						signal_test = 1;
					if(signal_recibido == SIGNAL_FINISH)
						signal_test = 0;
				}
				break;
			default:
				estado = 0;
		}
	}

}

uint8_t getRxModuloOK(void)
{
	uint8_t aux = 0;

	if(rxOK)
	{
		aux = 1;
		rxOK = 0;
	}

	return aux;
}

uint8_t getRxModulo_stringrecibido_OK(void)
{
	uint8_t aux = 0;

	if(stringrecibido_ok)
	{
		aux = 1;
		stringrecibido_ok = 0;
	}

	return aux;
}

void Transmit_UART1(const uint8_t* datas, uint8_t cant)
{
	uint8_t i;
	for(i = 0; i < cant ; i++)
		PushTX_UART1(datas[i]);
}

void PushTX_UART1(uint8_t data)
{
	//Si esta vacio, envio el dato sin incrementar out_tx
	//si incrementara out_tx, generaria interrupciones ciclicas

	bufferTX[in_tx] = data;
	in_tx ++;
	in_tx %= TAM_BUFFTX;

	if( !transmitiendo )
	{
		U1THR = PopTX_UART1();
	    transmitiendo = 1;
	}
}

uint8_t PopTX_UART1(void)
{
	uint8_t aux = 255;	//Si esta vacio, -1

	if(out_tx != in_tx)
	{
		aux = bufferTX[out_tx];
		out_tx++;
		out_tx %= TAM_BUFFTX;
	}

	return aux;
}

uint8_t Receive_UART1(void)
{
	return PopRX_UART1();
}

void PushRX_UART1(uint8_t data)
{
	bufferTX[in_rx] = data;
	in_rx ++;
	in_rx %= TAM_BUFFRX;
}

uint8_t PopRX_UART1(void)
{
	uint8_t aux = 255;	//Si esta vacio, -1

	if(out_rx != in_rx)
	{
		aux = bufferTX[out_rx];
		out_rx++;
		out_rx %= TAM_BUFFRX;
	}

	return aux;
}

