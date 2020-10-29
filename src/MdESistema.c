/*
 * MdESistema.c
 *
 *  Created on: Sep 27, 2019
 *      Author: oem
 */

#include "DR_tipos.h"
#include "MdESistema.h"
#include "driv_gpio.h"
#include "prim_gpio.h"
#include "driv_systick.h"
#include "prim_systick.h"
#include "driv_rtc.h"
#include "driv_matrix.h"
#include "prim_matrix.h"
#include "driv_uart.h"
#include "prim_uart.h"
#include "driv_spi.h"
#include <string.h>
#include "diskio.h"
#include "fatfs.h"
#include "ff.h"	  //funciones importantes
#include "ffconf.h"
#include "integer.h"
#include "rtc176x.h"
#include "prim_dataprocess.h"

extern uint8_t velocity;
extern uint8_t orientation;
extern uint8_t mode;
extern uint8_t bright;
extern uint8_t text[64];
extern uint8_t buff_hora[5];

#define MAX_INTENTOS_MODULO 2
#define RED_WIFI_PASS 	"AT+CWJAP=\"elhub\",\"dientefrio1\"\r\n"
#define RED_IP_PORT		"AT+CIPSTART=\"TCP\",\"192.168.43.161\",1519\r\n"

uint8_t status_sd = 0;
#define NO_SD 0
#define OK_SD 1

/*Comunicacion UART*/
uint8_t flag_estadoDeConeccion = DESCONECTADO;

uint8_t signal_connect = 0;
//0: desconectado
//1: conectado
uint8_t signal_test = 0;
//0: testeando
//1: testeo finalizado
uint8_t signal_save = 0;
//0: default sin guardar
//1: guardar en la SD los datos del buffer (propiedades)
uint8_t signal_disconnect = 1;

uint8_t config_fin = 0;

uint8_t escribir = 0;
uint8_t leer = 0;

extern uint8_t vueltas;
uint8_t timer_started = 0;	//revisa si hay algun timer activo

extern uint8_t stringrecibido[74]; //lo que recibe por el modulo
extern uint8_t data[72];
uint8_t line[80]; //lo que lee de la sd
extern uint8_t dataOk;

void MdESistema(FIL* fil, UINT* written)
{
	switch(flag_estadoDeConeccion)
	{
		case DESCONECTADO:
			MdEDesconectado(fil,written);
			if(Coneccion())
			{
				if(getRxModuloOK())
				{
					InitMdEConectado();
					flag_estadoDeConeccion = CONECTADO;
				}
			}
			break;

		case CONECTADO:
			MdEConectado(fil,written);
			if(!Coneccion())
			{
				InitMdEDesconectado(fil,written);
				flag_estadoDeConeccion = DESCONECTADO;
			}
			break;

		default:
			InitMdEDesconectado(fil,written);
			flag_estadoDeConeccion = DESCONECTADO;
	}
}

void InitMdESistema(void)
{
	InitButtons();
	InitMatrixLeds();
	InitRTC();
	InicializarSysTick();
	InitLedRGB();
	InitSPI();
	InitUART1();

	setTime(0,32,18);
	ClearMatrix();
	config_fin = 0;
	TimStart(0,1,SEG);
}

void InitMdEDesconectado(FIL* fil, UINT* written)
{
	ClearMatrix();
	TimStop(0);
	TransferToAllMAX7219(0x0A,bright);
	TimStart(0,4,SEG);
	config_fin = 0;
}

void InitMdEConectado(void)
{
	ClearMatrix();
	TimStop(0);
	Transmit_UART1("AT+CWMODE=3\r\n",13);
	TimStart(0,10,SEG);
	timer_started = 1;
}



void MdEDesconectado(FIL* fil, UINT* written)
{
	static uint8_t  i = 0;
	uint8_t key;
	static uint8_t boot = 0;
	uint32_t hora, min, sec;

	SetPIN_(RED,(i>>0)&0x01);
	SetPIN_(GREEN,(i>>1)&0x01);
	SetPIN_(BLUE,(i>>2)&0x01);

	/*
	if(escribir == 1)
	{
		f_open_SD(fil,"config.txt",FA_CREATE_ALWAYS| FA_WRITE | FA_READ);
		f_write(fil,"writing",sizeof("writing"),written);
		f_close_SD(fil);
		escribir = 0;
	}

	if(leer == 1)
	{
		f_open_SD(fil,"config.txt",FA_OPEN_EXISTING | FA_READ);
		f_gets_SD(line, sizeof(line),fil);
		f_close_SD(fil);
		stringToData(line);
		leer = 0;
	}
	*/

	if(TimEvent(0))
	{
		ShiftMatrix();
		if(mode == 0)
		{
			if(vueltas < 3)
			{
				DisplayMatrix((uint8_t*)text,dataLen(text));
			}
			else
			{
				getTime(&sec,&min,&hora);
				horaToStr(hora,min);
				DisplayMatrix((uint8_t*)buff_hora,5);
				if(vueltas >= 4)
					vueltas = 0;
			}
		}
		else if(mode == 1)
		{
			getTime(&sec,&min,&hora);
			horaToStr(hora,min);
			DisplayMatrix((uint8_t*)buff_hora,5);
		}
		else if(mode == 2)
			DisplayMatrix((uint8_t*)text,dataLen(text));

		TimStart(0,velocity*50,MSEG);
		i++;
		i%=8;
	}

	key = GetTecla();
	switch(key)
	{
		case K0:
			if(boot == 0)
				boot = 1;
			else
				ChangeMode_Matrix();
			break;
		case K1:
			ToggleOrientation_Matrix();
			break;
		case K2:
			DecreaseVel_Matrix();
			break;
		case K3:
			IncreaseVel_Matrix();
			break;
	}
}

void IncreaseVel_Matrix(void)
{
	velocity--;
	if(velocity <= VELMIN)
		velocity = VELMIN;

//	bright++;
//	if(bright >= 10)
//		bright = 10;
//	TransferToAllMAX7219(0x0A,bright);
}

void DecreaseVel_Matrix(void)
{
	velocity++;
	if(velocity >= VELMAX)
		velocity = VELMAX;

//	bright--;
//	if(bright <= 1)
//		bright = 1;
//	TransferToAllMAX7219(0x0A,bright);
}

void ToggleOrientation_Matrix(void)
{
	ClearMatrix();
	TimStop(0);
	TimStart(0,velocity*50,MSEG);
	if(!orientation)
		orientation = 1;
	else
		orientation = 0;
	//leer = 1;
}

void ChangeMode_Matrix(void)
{
	//escribir = 1;
	ClearMatrix();
	TimStop(0);

	signal_connect^=1;
	Transmit_UART1("AT\r\n",4);
}

void MdEConectado(FIL* fil, UINT* written)
{
	static uint8_t estado = 0;
	static uint8_t cont_intentos = 0;	//cuento la cantidad de veces que vencio el timer
	uint8_t key;
	uint32_t i = 0;
	uint32_t hora, min, sec;

	switch(estado)
	{
		//1. Configuro como CLIENTE
		//NOTA: PONER TIMERS POR SI NO RESPONDE EL MODULO Y VOLVER A DESCONECTADO!!!
		case 0:
			if(getRxModuloOK())
			{
				Transmit_UART1("AT+CIPMUX=0\r\n",13);
				TimStop(0);
				timer_started = 0;
				cont_intentos = 0;
				estado = 1;
				TimStart(0,10,SEG);
				timer_started = 1;
			}
			else if(timer_started == 0)	//si no hay timer activo...
			{
				TimStart(0,10,SEG);
				timer_started = 1;
			}
			else if(TimEvent(0))		//si vencio timer reenvio el codigo maximo 3 veces...
			{
				Transmit_UART1("AT+CWMODE=3\r\n",13);
				timer_started = 0;
				cont_intentos++;
			}
			else if(cont_intentos == MAX_INTENTOS_MODULO)	//si llega a la cant max de intentos...
			{
				timer_started = 0;
				cont_intentos = 0;
				estado = 0;
				signal_connect = 0;
				signal_disconnect = 1;
				config_fin = 0;
			}
			break;
		//2. Establezco coneccion unica
		case 1:
			if(getRxModuloOK())
			{
				Transmit_UART1(RED_WIFI_PASS,32);
				TimStop(0);
				timer_started = 0;
				cont_intentos = 0;
				estado = 2;
				TimStart(0,20,SEG);
				timer_started = 1;
			}
			else if(timer_started == 0)	//si no hay timer activo...
			{
				TimStart(0,10,SEG);
				timer_started = 1;
			}
			else if(TimEvent(0))		//si vencio timer reenvio el codigo maximo 3 veces...
			{
				Transmit_UART1("AT+CIPMUX=0\r\n",13);
				timer_started = 0;
				cont_intentos++;
			}
			else if(cont_intentos == MAX_INTENTOS_MODULO)	//si llega a la cant max de intentos...
			{
				timer_started = 0;
				cont_intentos = 0;
				estado = 0;
				signal_connect = 0;
				signal_disconnect = 1;
				config_fin = 0;
			}
			break;
		//3. Conecto a un access point
		case 2:
			if(getRxModuloOK())
			{
				Transmit_UART1(RED_IP_PORT,41);
				TimStop(0);
				timer_started = 0;
				cont_intentos = 0;
				estado = 3;
				TimStart(0,40,SEG);
				timer_started = 1;
			}
			else if(timer_started == 0)	//si no hay timer activo...
			{
				TimStart(0,20,SEG);
				timer_started = 1;
			}
			else if(TimEvent(0))		//si vencio timer reenvio el codigo maximo 3 veces...
			{
				Transmit_UART1(RED_WIFI_PASS,32);
				timer_started = 0;
				cont_intentos++;
			}
			else if(cont_intentos == MAX_INTENTOS_MODULO)	//si llega a la cant max de intentos...
			{
				timer_started = 0;
				cont_intentos = 0;
				estado = 0;
				signal_connect = 0;
				signal_disconnect = 1;
				config_fin = 0;
			}
			break;
		//4. Conecto al IP y puerto
		case 3:
			if(getRxModuloOK())
			{
				Transmit_UART1("AT+CIPSEND=22\r\n",15);
				for(i = 0; i < 20000; i++);
				Transmit_UART1("CONNECTION ESTABLISHED",22);
				config_fin = 1;

				TimStop(0);
				timer_started = 0;
				cont_intentos = 0;
				signal_disconnect = 0;
				estado = 4;
			}
			else if(timer_started == 0)	//si no hay timer activo...
			{
				TimStart(0,40,SEG);
				timer_started = 1;
			}
			else if(TimEvent(0))		//si vencio timer reenvio el codigo maximo 3 veces...
			{
				Transmit_UART1(RED_IP_PORT,41);
				timer_started = 0;
				cont_intentos++;
			}
			else if(cont_intentos == MAX_INTENTOS_MODULO)	//si llega a la cant max de intentos...
			{
				timer_started = 0;
				cont_intentos = 0;
				estado = 0;
				signal_connect = 0;
				signal_disconnect = 1;
				config_fin = 0;
			}
			break;
		//4. Estado normal de MdEConectado
		case 4:
			if(signal_save == 1)
			{
				signal_save = 0;
				verifyData(stringrecibido);
				if(dataOk == 1)
				{
					f_open_SD(fil,"config.txt",FA_CREATE_ALWAYS| FA_WRITE | FA_READ);
					f_write(fil,stringrecibido,sizeof(stringrecibido),written);
					f_close_SD(fil);
					dataOk = 0;
				}
			}

			if(signal_disconnect == 1)
			{
				config_fin = 0;
				estado = 0;
				cont_intentos = 0;
				signal_connect = 0;

				TimStop(0);
				ClearMatrix();
				TimStart(0,2,SEG);
			}

			if(signal_test == 1)
			{
				signal_test = 0;
				verifyData(stringrecibido);
				if(dataOk == 1)
				{
					stringToData(stringrecibido);
					ClearMatrix();
					TimStop(0);
					TimStart(0,2,SEG);
					dataOk = 0;
					TransferToAllMAX7219(0x0A,bright);
				}
			}

			if(TimEvent(0))
			{
				ShiftMatrix();
				if(mode == 0)
				{
					if(vueltas < 3)
					{
						DisplayMatrix((uint8_t*)text,dataLen(text));
					}
					else
					{
						getTime(&sec,&min,&hora);
						horaToStr(hora,min);
						DisplayMatrix((uint8_t*)buff_hora,5);
						if(vueltas >= 4)
							vueltas = 0;
					}
				}
				else if(mode == 1)
				{
					getTime(&sec,&min,&hora);
					horaToStr(hora,min);
					DisplayMatrix((uint8_t*)buff_hora,5);
				}
				else if(mode == 2)
					DisplayMatrix((uint8_t*)text,dataLen(text));

				TimStart(0,velocity*50,MSEG);
				i++;
				i%=8;
			}

			key = GetTecla();
			switch(key)
			{
				case K0:
					config_fin = 0;
					estado = 0;
					cont_intentos = 0;
					signal_connect = 0;
					signal_disconnect = 1;

					TimStop(0);
					ClearMatrix();
					TimStart(0,2,SEG);
					break;
				case K1:
					break;
				case K2:
					break;
				case K3:
					break;
			}
			break;
		default:
			estado = 0;
	}
}

uint8_t Coneccion(void)
{
	/*
	static uint8_t nivel_actual = 1;
	static uint8_t nivel_anterior = 1;

	nivel_actual = GetPIN_(2,10);
	if(nivel_anterior != nivel_actual)
	{
		flag_estadoDeConeccion ^= (~GetPIN_(2,10))&0x01; //Suponiendo que manda un pulso de coneccion y desconeccion
		nivel_anterior = nivel_actual;
	}
*/

	return signal_connect;
}





