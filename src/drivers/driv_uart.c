/*
 * driv_uart.c
 *
 *  Created on: Oct 10, 2019
 *      Author: User
 */

#include "driv_gpio.h"
#include "driv_uart.h"
#include "prim_uart.h"

uint8_t bufferTX[TAM_BUFFTX];
uint16_t in_tx = 0;
uint16_t out_tx = 0;

uint8_t bufferRX[TAM_BUFFRX];
uint16_t in_rx = 0;
uint16_t out_rx = 0;

uint8_t transmitiendo = 0;

void InitUART1(void)
{
	//1. Alimento el periferico
	PCONP |= (0x01 << 4);
	//2. Selecciono su fuente de clock CCLK/4
	PCLKSEL_0 &= ~(0x03 << 8);
	PCLKSEL_1 &= ~(0x03 << 8);
	//3. Configuro los pines como TXD y RXD
	SetPINSEL_(PORT_TXD1,1);
	SetPINSEL_(PORT_RXD1,1);
	//4. Configuro la trama de transmision
	U1LCR = 3; //8,N,1

	/* Seleccionando DLABA = 1 */
	U1LCR |= (0x01 << 7);
	//5. Configuro divisores para el BAUDRATE
	U1DLL = ((uint32_t) (25000000/(16*UART1_BAUDRATE)))&(0xFF);
	U1DLM = (((uint32_t) (25000000/(16*UART1_BAUDRATE)))&(0xFF<<8))>>8;

	/* Seleccionando DLABA = 0 */
	U1LCR &= ~(0x01 << 7);
	//6.Configuro el tipo de interrupcion
	U1IER = 3; //por tx y rx
	//7.Habilito interrupcion en la NVIC
	ISER0 |= (0x01<<6);
}

void UART1_IRQHandler(void)
{
	uint8_t iir_register;
	uint8_t datoRx;
	uint8_t datoTx;

	do
	{
		iir_register = U1IIR;
		if(iir_register&(0x01<<1))//Interrupcion por Tx
		{
			datoTx = PopTX_UART1();
			if(datoTx != 255) // distinto de vacio, todavia hay datos por mandar
				U1THR = datoTx;
			else
				transmitiendo = 0;
		}
		if(iir_register&(0x01<<2))//Interrupcion por Rx
		{
			datoRx = U1RBR;
			PushRX_UART1(datoRx);
		}
	}
	while(!(iir_register&0x01));

}
