/*
 * dr_matrix.h
 *
 *  Created on: Sep 27, 2019
 *      Author: R. Nicolás Savinelli, Tomás Arbia, Kevin Chon, Juan Ignacio Piccardi
 */

#ifndef DRIV_MATRIX_H_
#define DRIV_MATRIX_H_

#include "bibliotecaInfoII.h"

/*Funciones*/
void InitMatrixLeds(void);

void ClearMatrixRegisters(void);

void TransferToMAX7219(uint8_t address);

void TransferToAllMAX7219(uint8_t address, uint8_t data);
	#define AD_DECODEMODE	0x09
	#define AD_INTENSITY	0x0A
	#define AD_SCANLIMIT	0x0B
	#define AD_SHUTDOWN		0x0C
	#define AD_DISPLAYTEST	0x0F

void BarridoMatrix(void);

/*Buffers*/
extern uint8_t buffer_DIN[32];

#define NUM_MATRIX 4

#endif /* DRIV_MATRIX_H_ */
