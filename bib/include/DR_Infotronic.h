/*******************************************************************************************************************************//**
 *
 * @file		Infotronic.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		2 de jun. de 2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DRIVERINFOTRONIC_DR_INFOTRONIC_H_
#define DRIVERINFOTRONIC_DR_INFOTRONIC_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_Entradas.h"
#include "PR_7seg.h"
#include "DR_7seg.h"
#include "DR_gpio.h"
#include "DR_Inicializacion.h"
#include "DR_pinsel.h"
#include "DR_PLL.h"
#include "DR_SysTick.h"
#include "DR_tipos.h"
#include "DR_Timers.h"
#include "PR_Timers.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
//!< Salidas Digitales
#define		OUT0			PORT2,0
#define		OUT1			PORT0,23
#define		OUT2			PORT0,21
#define		OUT3			PORT0,27

#define		led0			PORT2,1
#define		led1			PORT2,2
#define		led2			PORT2,3

//!< Entradas Digitales
#define 	IN0				PORT1,26
#define 	IN1				PORT4,29
#define 	IN2				PORT2,11

//!< Teclas (teclado 4x1)
#define		KEY0			PORT2,10
#define		KEY1			PORT0,18
#define		KEY2			PORT0,11
#define		KEY3			PORT2,13		// EINT3

//!< LCD
#define		LCD_D4			PORT0,5
#define		LCD_D5			PORT0,10
#define		LCD_D6			PORT2,4
#define		LCD_D7			PORT2,5
#define		LCD_RS			PORT2,6
#define		LCD_BF			PORT0,28
#define		LCD_EN			PORT0,4

//!< Display siete segmentos
#define    dg0       		PORT0,19    // exp 5
#define    dg1       		PORT1,20   	// exp 4
#define    dg2      		PORT1,23   	// exp 3
#define    dg3       		PORT4,28   	// exp 2
#define    dg4       		PORT1,29   	// exp1
#define    dg5       		PORT2,7    	// exp0

#define    seg_a        	PORT2,9 	// exp6 Correcto P3.26
#define    seg_b       	 	PORT1,18	// exp15
#define    seg_c        	PORT1,21	// exp14
#define    seg_d        	PORT1,24	// exp13
#define    seg_e        	PORT1,27	// exp12
#define    seg_f        	PORT3,25	// exp11
#define    seg_g        	PORT0,20	// exp10

#define    seg_dp        	PORT1,19// P1.19  exp9

#define    DIGITO_0         0
#define    DIGITO_1         1
#define    DIGITO_2         2
#define    DIGITO_3         3
#define    DIGITO_4         4
#define    DIGITO_5         5

#define		BUZZER	PORT0,28

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
// extern tipo nombreVariable;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/

#endif /* DRIVERINFOTRONIC_DR_INFOTRONIC_H_ */
