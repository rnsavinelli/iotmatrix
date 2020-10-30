/*
 * prim_uart.h
 *
 *  Created on: Oct 17, 2019
 *      Author: R. Nicolás Savinelli, Tomás Arbia, Kevin Chon, Juan Ignacio Piccardi
 */

#ifndef PRIM_PRIM_UART_H_
#define PRIM_PRIM_UART_H_

#include "DR_tipos.h"

void 		Transmit_UART1(const uint8_t* datas, uint8_t cant);
void 		PushTX_UART1(uint8_t data);
uint8_t 	PopTX_UART1(void);

uint8_t 	Receive_UART1(void);
void 		PushRX_UART1(uint8_t data);
uint8_t 	PopRX_UART1(void);

void 		Recepcion_ModuloWifi(void);
uint8_t 	getRxModuloOK(void);

void 		Recepcion_ModuloWifi_Data(void);
uint8_t 	getRxModulo_stringrecibido_OK(void);


#endif /* PRIM_PRIM_UART_H_ */
