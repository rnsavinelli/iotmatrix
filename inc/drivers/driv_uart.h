/*
 * driv_uart.h
 *
 *  Created on: Oct 10, 2019
 *      Author: User
 */

#ifndef DRIV_UART_H_
#define DRIV_UART_H_

#include "DR_tipos.h"

#define PCONP 		(*( (__RW uint32_t *) 0x400FC0C4 ))
#define PCLKSEL_0 	*( (__RW uint32_t *) 0x400FC1A8 )
#define	PCLKSEL		( ( __RW uint32_t  * ) 0x400FC1A8UL )
#define	PCLKSEL_1	PCLKSEL[1]

//Registros de la UART0:

#define PORT_TXD0	0,2
#define PORT_RXD0	0,3

#define	UART0		( (__RW uint32_t *) 0x4000C000 )
	#define	U0LCR	UART0[3]
	//DLAB = 1
	#define	U0DLLSB	UART0[0]
	#define	U0DLMSB	UART0[1]
	#define UART0_BAUDRATE 9600
	//DLAB = 0
	#define	U0IER	UART0[1]
	#define	U0IIR	UART0[2]

#define	ISER		( ( uint32_t * ) 0xE000E100UL )
#define ISER0	ISER[0]

#define	U0THR		UART0[0]
#define	U0RBR		UART0[0]

#define	U0LSR		UART0[5]
	#define LSR_RDR		0x01
	#define LSR_OE		0x02
	#define LSR_PE		0x04
	#define LSR_FE		0x08
	#define LSR_BI		0x10
	#define LSR_THRE	0x20
	#define LSR_TEMT	0x40
	#define LSR_RXFE	0x80
	#define	U0RDR		(U0LSR & LSR_RDR)
	#define	U0THRE		((U0LSR & LSR_THRE) >>5)
#define	U0SCR	UART0[7]

#define TAM_BUFFTX 100
#define TAM_BUFFRX 100

//Registros de la UART1:

#define PORT_TXD1	0,15	//EXPANSION 19
#define PORT_RXD1	0,16	//EXPANSION 18

#define	UART1	( (__RW uint32_t *) 0x40010000UL )
	#define	U1LCR	UART1[3]
	//DLAB = 1
	#define	U1DLL	UART1[0]
	#define	U1DLM	UART1[1]
	#define UART1_BAUDRATE 115200
	//DLAB = 0
	#define	U1IER	UART1[1]
	#define	U1IIR	UART1[2]


#define		U1THR		UART1[0]
#define		U1RBR		UART1[0]


#define		U1FCR		UART1[2]

#define		U1MCR		UART1[4]
#define		U1LSR		UART1[5]
#define		U1MSR		UART1[6]
#define		U1SCR		UART1[7]

//!< //////////BITS DE ANALISIS para todas las UARTs   ////////////////////
#define 	IER_RBR		0x01
#define 	IER_THRE	0x02
#define 	IER_RLS		0x04

#define 	IIR_PEND	0x01
#define 	IIR_RLS		0x06
#define 	IIR_RDA		0x04
#define 	IIR_CTI		0x0C
#define 	IIR_THRE	0x02

#define 	LSR_RDR		0x01
#define 	LSR_OE		0x02
#define 	LSR_PE		0x04
#define 	LSR_FE		0x08
#define 	LSR_BI		0x10
#define 	LSR_THRE	0x20
#define 	LSR_TEMT	0x40
#define 	LSR_RXFE	0x80

//!< macros útiles para UARTs
#define		U0RDR		(U0LSR & LSR_RDR)
#define		U0THRE		((U0LSR & LSR_THRE) >>5)
#define		U1RDR		(U1LSR & LSR_RDR)
#define		U1THRE		((U1LSR & LSR_THRE) >>5)

void InitUART1(void);
void UART1_IRQHandler(void);



#endif

