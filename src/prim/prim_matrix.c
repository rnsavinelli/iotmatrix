/*
 * prim_matrix.c
 *
 *  Created on: Oct 26, 2019
 *      Author: R. Nicolás Savinelli, Tomás Arbia, Kevin Chon, Juan Ignacio Piccardi
 */

#include "driv_matrix.h"
#include "prim_matrix.h"
#include "MdESistema.h"

extern uint8_t buffer_DIN[32];
extern uint8_t orientation;

uint8_t vueltas = 0; //cuenta las veces que termina de imprimir todo el texto

uint8_t tablaMatriz[100][5]=
{
	{0,0,0,0,0},		//espacio	ASCII:32
	{0,0,125,0,0},		//!			ASCII:33
	{0,112,0,112,0},	//¨			ASCII:34
	{20,62,20,62,20},	//#			ASCII:35
	{18,42,127,42,36},	//$			ASCII:36
	{98,100,8,19,35},	//%			ASCII:37
	{38,89,89,38,9},	//&			ASCII:38
	{0,0,96,0,0},		//'			ASCII:39	falta
	{62,65,0,0,0},		//(			ASCII:40
	{0,0,0,65,62},		//)			ASCII:41
	{0,16,56,16,0},		//*			ASCII:42
	{8,8,62,8,8},		//+			ASCII:43
	{0,1,6,0,0},		//,			ASCII:44
	{8,8,8,8,8},		//-			ASCII:45
	{0,0,1,0,0},		//.			ASCII:46
	{2,4,8,16,32},		///			ASCII:47	falta
	{62,65,65,65,62},	//0			ASCII:48
	{17,33,127,1,1},	//1			ASCII:49
	{33,67,69,73,49},	//2			ASCII:50
	{34,65,65,73,54},	//3			ASCII:51
	{120,8,8,8,127},	//4			ASCII:52
	{122,73,73,73,70},	//5			ASCII:53
	{62,73,73,73,38},	//6			ASCII:54
	{64,64,79,80,96},	//7			ASCII:55
	{54,73,73,73,54},	//8			ASCII:56
	{50,73,73,73,62},	//9			ASCII:57
	{0,0,20,0,0},		//:			ASCII:58
	{0,1,22,0,0},		//;			ASCII:59
	{0,8,20,34,65},		//<			ASCII:60
	{20,20,20,20,20},	//=			ASCII:61
	{65,34,20,8,0},		//>			ASCII:62
	{0,32,77,72,48},	//?			ASCII:63
	{62,65,93,85,61},	//@			ASCII:64
	{63,72,72,72,63},	//A 		ASCII:65
	{127,73,73,73,54},	//B 		ASCII:66
	{62,65,65,65,54},	//C			ASCII:67
	{127,65,65,65,62},	//D			ASCII:68
	{127,73,73,73,65},	//E			ASCII:69
	{127,72,72,72,64},	//F			ASCII:70
	{62,65,69,69,54},	//G			ASCII:71
	{127,8,8,8,127},	//H			ASCII:72
	{65,65,127,65,65},	//I			ASCII:73
	{70,65,65,65,126},	//J			ASCII:74
	{127,8,20,34,65},	//K			ASCII:75
	{127,1,1,1,1},		//L			ASCII:76
	{127,32,16,32,127}, //M			ASCII:77
	{127,16,8,4,127},	//N			ASCII:78
	{62,65,65,65,62},	//O			ASCII:79
	{127,72,72,72,48},	//P			ASCII:80
	{60,66,70,66,61},	//Q			ASCII:81
	{127,72,76,74,49},	//R			ASCII:82
	{38,81,73,69,50},	//S			ASCII:83
	{64,64,127,64,64},	//T			ASCII:84
	{126,1,1,1,126},	//U			ASCII:85
	{124,2,1,2,124},	//V			ASCII:86
	{127,2,4,2,127},	//W			ASCII:87
	{99,20,8,20,99},	//X			ASCII:88
	{96,16,15,16,96},	//Y			ASCII:89
	{67,69,73,81,97},	//Z			ASCII:90
	{0,127,65,65,0},	//[			ASCII:91
	{64,48,8,6,1},		///			ASCII:92
	{0,65,65,127,0},	//]			ASCII:93
	{8,16,32,16,8},		//^			ASCII:94
	{1,1,1,1,1},		//_			ASCII:95
	{16,96,0,0,0},		//´			ASCII:96
	{14,17,17,14,1},	//a			ASCII:97
	{63,9,9,6,0},		//b			ASCII:98
	{14,17,17,10,0},	//c			ASCII:99
	{6,9,9,63,0},		//d			ASCII:100
	{14,21,21,13,0},	//e			ASCII:101
	{0,31,36,36,0},		//f			ASCII:102
	{25,37,37,30},		//g			ASCII:103
	{63,8,8,7,0},		//h			ASCII:104
	{0,0,47,0,0},		//i			ASCII:105
	{2,1,1,94,0},		//j			ASCII:106
	{63,4,10,17,0},		//k			ASCII:107
	{0,0,63,0,0},		//l			ASCII:108
	{15,16,8,16,15},	//m			ASCII:109
	{31,8,16,15},		//n			ASCII:110
	{14,17,17,14,0},	//o			ASCII:111
	{63,36,36,24,0},	//p			ASCII:112
	{24,36,36,63,0},	//q			ASCII:113
	{31,8,16,16,0},		//r			ASCII:114
	{18,41,37,18,0},	//s			ASCII:115
	{0,62,9,9,0},		//t			ASCII:116
	{30,1,1,30,0},		//u			ASCII:117
	{28,2,1,2,28},		//v			ASCII:118
	{30,1,2,1,30},		//w			ASCII:119
	{17,10,4,10,17},	//x			ASCII:120
	{32,16,15,16,32},	//Y			ASCII:121
	{17,19,21,25,17},	//Z			ASCII:122
	{8,54,65,65,0},		//{			ASCII:123
	{0,0,127,0,0},		//|			ASCII:124
	{0,65,65,54,8},		//}			ASCII:125
	{0,12,8,24,0}		//~			ASCII:126
};

#define ESPACIADO 24

extern uint8_t signal_test;

void DisplayMatrix(uint8_t *text, uint8_t len)
{
	static uint8_t nColumna = 0;	//Indica la columna de la nPos del texto a imprimir
	static uint8_t nPos = 0;		//Indica la posicion de la letra a imprimir del texto
	uint8_t nFila = 0;				//Indica la fila de la nPos del texto a imprimir
	static uint8_t espaciado = 0;	//Indica la separacion entre el ultimo caracter y la reimpresion del primer caracter

	static uint8_t orientation_anterior = LEFT;
	static uint8_t orientation_actual 	= LEFT;

	orientation_actual = orientation;

	//1. Si hay un cambio de orientacion, empieza de cero la columna a imprimir
	if(orientation_anterior != orientation_actual || signal_test == 1)
	{
		orientation_anterior = orientation_actual;
		if(orientation == RIGHT)
		{
			nPos = len-1;
			nColumna = 5;
		}
		else if(orientation == LEFT)
		{
			nPos = 0;
			nColumna = 0;
		}
	}

	//2. Cuando se imprime todo el texto, imprime espacio hasta llegar a ESPACIADO
	if((nPos == len && orientation == LEFT)||(nPos == 255 && orientation == RIGHT))	//Si termino de imprimir todo el texto
	{
		//No termino con el espaciado hasta que haya 'ESPACIADO' espaciados
		if(espaciado == ESPACIADO)
		{
			if(orientation == RIGHT)
				nPos = len-1;
			else if(orientation == LEFT)
				nPos = 0;

			espaciado = 0;
			vueltas++;
		}

		//ESPACIADO en blanco
		for(nFila = 0; nFila < 8; nFila++)
			if(orientation == RIGHT)
				buffer_DIN[nFila]&=~(0x01);
			else if(orientation == LEFT)
				buffer_DIN[8*(NUM_MATRIX-1)+nFila]&=~(0x01<<7);

		//Voy agregando espaciado
		espaciado++;
	}
	//3. Imprime texto
	else	//Si sigue imprimiendo el texto
	{
		for(nFila = 0; nFila < 8; nFila++)
		{
			if(nColumna != 5)	//Si es un caracter del texto
			{
				if(orientation == RIGHT)
				{
					//Cargo el buffer
					//restar 32 para coincidir con el indice de la tabla por ser ascii
					if((tablaMatriz[text[len-nPos-1]-32][4-nColumna]>>nFila)&(0x01))
						buffer_DIN[nFila]|=0x01;
					else
						buffer_DIN[nFila]&=~(0x01);
				}
				else if(orientation == LEFT)
				{
					//Cargo el buffer
					if((tablaMatriz[text[nPos]-32][nColumna]>>nFila)&(0x01))
						buffer_DIN[8*(NUM_MATRIX-1)+nFila]|=(0x01<<7);
					else
						buffer_DIN[8*(NUM_MATRIX-1)+nFila]&=~(0x01<<7);
				}
			}
			else				//Espacio en blanco entre palabras
			{
				if(orientation == RIGHT)
				{
					buffer_DIN[nFila]&=~(0x01);
				}
				else if(orientation == LEFT)
				{
					buffer_DIN[8*(NUM_MATRIX-1)+nFila]&=~(0x01<<7);
				}
			}
		}


		if(orientation == LEFT)
		{
			nColumna++;
			if(nColumna == 6)	//Si termino de imprimir toda la letra mas un espacio
			{
				nColumna = 0;
				nPos++;
			}
		}
		else if(orientation == RIGHT)
		{
			nColumna--;
			if(nColumna == 255)	//Si termino de imprimir toda la letra mas un espacio
			{
				nColumna = 5;
				nPos--;
			}
		}

	}
}


void ShiftMatrix(void)
{
	if(orientation == LEFT)
		ShiftLeftMatrix();
	else if(orientation == RIGHT)
		ShiftRightMatrix();
}

void ShiftRightMatrix(void)
{
	uint8_t nFila;
	uint8_t carry0 = 0,carry1 = 0,carry2 = 0,carry3 = 0;

	for(nFila = 0; nFila < 8; nFila++)
	{
		//Si tiene un valor en la 8ta columna, habilito el carry
		if((buffer_DIN[nFila]>>7)&0x01)
			carry0 = 1;
		buffer_DIN[nFila]=buffer_DIN[nFila]<<1;

		if((buffer_DIN[nFila+8]>>7)&0x01)
			carry1 = 1;
		buffer_DIN[nFila+8]=buffer_DIN[nFila+8]<<1;
		if(carry0)
		{
			carry0 = 0;
			buffer_DIN[nFila+8]+=0x01;
		}

		if((buffer_DIN[nFila+16]>>7)&0x01)
			carry2 = 1;
		buffer_DIN[nFila+16]=buffer_DIN[nFila+16]<<1;
		if(carry1)
		{
			carry1 = 0;
			buffer_DIN[nFila+16]+=0x01;
		}

		if((buffer_DIN[nFila+24]>>7)&0x01)
			carry3 = 1;
		buffer_DIN[nFila+24]=buffer_DIN[nFila+24]<<1;
		if(carry2)
		{
			carry2 = 0;
			buffer_DIN[nFila+24]+=0x01;
		}

		if(carry3)
		{
			carry3 = 0;
			buffer_DIN[nFila]+=0x01;
		}
	}
}

void ShiftLeftMatrix(void)
{
	uint8_t nFila;
	uint8_t carry0 = 0,carry1 = 0,carry2 = 0,carry3 = 0;
	for(nFila = 0; nFila < 8; nFila++)
	{
		if((buffer_DIN[nFila+24])&0x01)
			carry3 = 1;
		buffer_DIN[nFila+24]=buffer_DIN[nFila+24]>>1;

		if((buffer_DIN[nFila+16])&0x01)
			carry2 = 1;
		buffer_DIN[nFila+16]=buffer_DIN[nFila+16]>>1;
		if(carry3)
		{
			carry3=0;
			buffer_DIN[nFila+16]+=(0x01<<7);
		}

		if((buffer_DIN[nFila+8])&0x01)
			carry1 = 1;
		buffer_DIN[nFila+8]=buffer_DIN[nFila+8]>>1;
		if(carry2)
		{
			carry2=0;
			buffer_DIN[nFila+8]+=(0x01<<7);
		}

		if((buffer_DIN[nFila])&0x01)
			carry0 = 1;
		buffer_DIN[nFila]=buffer_DIN[nFila]>>1;
		if(carry1)
		{
			carry1=0;
			buffer_DIN[nFila]+=(0x01<<7);
		}

		if(carry0)
		{
			carry0=0;
			buffer_DIN[nFila+24]+=(0x01<<7);
		}
	}
}

void ClearMatrix(void)
{
	uint8_t nFila;
	for(nFila = 0; nFila < NUM_MATRIX*8; nFila++)
	{
		buffer_DIN[nFila] = 0x00;
	}
}
