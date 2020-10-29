/*
 * MdESistema.h
 *
 *  Created on: Sep 27, 2019
 *      Author: oem
 */

#ifndef MDESISTEMA_H_
#define MDESISTEMA_H_

#include "DR_tipos.h"
#include "diskio.h"
#include "fatfs.h"
#include "ff.h"	  //funciones importantes
#include "ffconf.h"
#include "integer.h"

#define DESCONECTADO	0	//equivale al estado: FUNCIONANDO
#define CONECTADO		1	//equivale al estado: CONFIGURANDO

void InitMdESistema(void);
void InitMdEDesconectado(FIL* fil, UINT* written);
void InitMdEConectado(void);

void MdESistema(FIL* fil, UINT* written);
void MdEDesconectado(FIL* fil, UINT* written);
	void IncreaseVel_Matrix(void);
	void DecreaseVel_Matrix(void);
	void ToggleOrientation_Matrix(void);
	void ChangeMode_Matrix(void);
void MdEConectado(FIL* fil, UINT* written);

uint8_t Coneccion(void);

extern uint8_t vel;
	#define VELMAX 	10
	#define VELMIN 	1
extern uint8_t orientation;
	#define RIGHT 	0
	#define LEFT 	1
extern uint8_t mode;

#endif /* MDESISTEMA_H_ */
