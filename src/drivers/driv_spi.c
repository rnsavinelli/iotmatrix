/*
 * driv_spi.c
 *
 *  Created on: Oct 11, 2019
 *      Author: User
 */
#include "driv_spi.h"
#include "driv_uart.h"
#include "driv_gpio.h"

void InitSPI(void)
{
	/*Se utiliza SSP0 en lugar de SPI*/

	//1. Alimento a SSP1
	PCONP |= 0x01<<21;	//
	//2. Selecciono clock CCLK/4
	PCLKSEL1 &= ~(0x03 << 20);
	//3. Configuro la funcion de los pines para la SPI
	SetPINSEL_(0,6,2);	//SSEL1 (Si pongo 0x00: GPIO para controlarlo a gusto)
	SetPINSEL_(0,7,2);	//SCK1
	SetPINSEL_(0,8,2);	//MISO 1
	SetPINSEL_(0,9,2); 	//MOSI 1

	/*SSP0CR0 Register*/
	//4. DDS, Data size: 8bit transfer
	SSP0CR0 &= ~(0x0F);
	SSP0CR0 |= 0x07;
	//5. FRF, Frame format: SPI
	SSP0CR0 &= ~(0x03 << 4);
	//6. CPOL, Clock polarity: low between frames
	SSP0CR0 &= ~(0x01 << 6);
	//7. CPHA, Clock phase: captures serial data on first clock
	SSP0CR0 &= ~(0x01 << 7);
	//8. SCR, Serial clock rate
	SSP0CR0 &= ~(0xFF << 8);

	/*SSP0CR1 Register*/
	//8. LBM, Loop Back Mode: 0
	SSP0CR1 &= ~(0x01 << 0);
	//9. SSE, SSP enable: true
	SSP0CR1 |= (0x01 << 1);
	//10. MS, Master/slave mode: act as master
	SSP0CR1 &= ~(0x01 << 2);


	/*CONGIRUACION DEL CLOK
	Vamos a usar los siguientes registros: PCLKSEL0 para PCLk , SSP1CPSR para CPSDVSR y
	 SSP1CR0 para el SCR (serial clok rate).
	SIGUE LA SIGUIENTE ECUACION :

	fclk = PCLK/ CPSDVSR*(SCR + 1)
	*/

	//CPSDVSR : numero que elejimos entre 2 y 254. en este ejemplo 200 -> 11001000
	SSP0CPSR &= ~(0x01 << 0);
	SSP0CPSR &= ~(0x01 << 1);
	SSP0CPSR &= ~(0x01 << 2);
	SSP0CPSR |= (0x01 << 3);
	SSP0CPSR &= ~(0x01 << 4);
	SSP0CPSR &= ~(0x01 << 5);
	SSP0CPSR |= (0x01 << 6);
	SSP0CPSR |= (0x01 << 7);




	//REGISTRO DE DATOS // de este registro es donde se va a leer y escribir.
	// HAY DOS REGISTROS PERO ESTO SUPONGO QUE ES SI QUEREMOS HACER TODAS LAS PRIMITIVAS
	// VER COMO USAR BIBLIOTECA PERO SE SUPONE QUE ESTO ES PARA EL SPI
}

