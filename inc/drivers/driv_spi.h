/*
 * driv_spi.h
 *
 *  Created on: Oct 11, 2019
 *      Author: R. Nicolás Savinelli, Tomás Arbia, Kevin Chon, Juan Ignacio Piccardi
 */

#ifndef DRIV_SPI_H_
#define DRIV_SPI_H_

#define SSP0CR0  	*( ( __RW uint32_t * ) 0x40088000 )
#define SSP0CR1  	*( ( __RW uint32_t * ) 0x40088004 )
#define SSP0DR  	*( ( __RW uint32_t * ) 0x40088008 )
#define SSP0SR  	*( ( __RW uint32_t * ) 0x4008800C )
#define SSP0CPSR 	*( ( __RW uint32_t * ) 0x40088010 )

#define PCLKSEL1 *( ( __RW uint32_t * ) 0x400FC1AC )

void InitSPI(void);


#endif /* DRIV_SPI_H_ */
