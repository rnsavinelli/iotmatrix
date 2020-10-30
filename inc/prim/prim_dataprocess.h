/*
 * prim_dataprocess.h
 *
 *  Created on: Dec 13, 2019
 *      Author: R. Nicolás Savinelli, Tomás Arbia, Kevin Chon, Juan Ignacio Piccardi
 */

#ifndef PRIM_DATAPROCESS_H_
#define PRIM_DATAPROCESS_H_

void stringToData (uint8_t* data);
void dataToString (uint8_t mode, uint8_t bright, uint8_t speed, uint8_t orientation,uint8_t* texto);
void verifyData (uint8_t* data);
uint8_t dataLen (uint8_t* data);


#endif /* PRIM_DATAPROCESS_H_ */
