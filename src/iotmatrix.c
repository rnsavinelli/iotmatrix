/*
===============================================================================
 Name        : iotmatrix.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include "bibliotecaInfoII.h"
#include "MdESistema.h"
#include <string.h>

#include "diskio.h"
#include "fatfs.h"
#include "ff.h"	  //funciones importantes
#include "ffconf.h"
#include "integer.h"
#include "rtc176x.h"


#include "prim_dataprocess.h"

#define TAM 10

uint8_t recibio=0;
extern uint8_t status_sd;

uint8_t velocity;
uint8_t orientation;
uint8_t mode;
uint8_t bright;
uint8_t text[64];

extern uint8_t dataOk;
extern uint8_t line[80]; //lo que lee de la sd


DWORD get_fattime (void)
{
	RTC rtc;

	/* Get local time */
	rtc_gettime(&rtc);

	/* Pack date and time into a DWORD variable */
	return	  ((DWORD)(rtc.year - 1980) << 25)
			| ((DWORD)rtc.month << 21)
			| ((DWORD)rtc.mday << 16)
			| ((DWORD)rtc.hour << 11)
			| ((DWORD)rtc.min << 5)
			| ((DWORD)rtc.sec >> 1);
}


int main(void)
{
	//Variables SD
	FIL fil;
	FATFS* fs;
	UINT* written;
	FRESULT res;

	//1. Inicializo el sistema
	InicializarPLL();
	InitMdESistema();

	//2. Monto la SD
	fs = malloc(sizeof (FATFS));          /* Get work area for the volume */
	res = f_mount_SD(fs,"", 1);           /* Mount the default drive */

	//3. Precargo los datos almacenados de la SD a las configuraciones
	res = f_open_SD(&fil,"config.txt",FA_OPEN_EXISTING | FA_READ);
	if(res == FR_OK)
	{
		f_gets_SD(line, sizeof(line),&fil);
		verifyData(line);
		if(dataOk)
		{
			stringToData(line);
			dataOk = 0;
		}
		else
		{
			velocity = 6;
			orientation = 1;
			mode = 2;
			bright = 1;
			strcpy(text,"NO CONFIGURATIONS");
		}
	}
	else
	{
		velocity = 6;
		orientation = 1;
		mode = 2;
		bright = 1;
		strcpy(text,"NO SD");
	}
	f_close_SD(&fil);
	TransferToAllMAX7219(0x0A,bright);

	//4. Comienzo maquina de estados del sistema
	while(1)
	{
		MdESistema(&fil,written);
	}

	f_mount_SD(0,"", 0);
    return 0 ;
}
