/*
 * prim_dataprocess.c
 *
 *  Created on: Dec 13, 2019
 *      Author: User
 */

#include <stdio.h>
#include <string.h>
//si esto anda quedaria mas prolijo implemetarlo dsps con una estructura. Lo hacemos el viernes si hay tiempo

#define TAM_BUFF_TEXTO 64
#define TAM_BUFF_TEXTO_Y_PROPIEDADES 72 //64 +8 de propiedades y coma

typedef char uint8_t; //BORRAR EN MCU

uint8_t dataOk = 0;   //pongo en 1 cuando esta ok.poner en cero en inicializar

extern uint8_t velocity;
extern uint8_t orientation;
extern uint8_t bright;
extern uint8_t mode;
extern uint8_t text[TAM_BUFF_TEXTO];

uint8_t data[TAM_BUFF_TEXTO_Y_PROPIEDADES];

void stringToData (uint8_t* data)
{
    char* aux;
    char aux2[72];

    strcpy(aux2,data);

    aux = strtok(data,",");
    mode=aux[0]-48;
    aux = strtok(NULL,",");
    bright=aux[0]-48;
    aux = strtok(NULL,",");
    velocity=aux[0]-48;
    aux = strtok(NULL,",");
    orientation=aux[0]-48;
    aux = strtok(NULL,"\0");
    strcpy(text,aux);

    strcpy(data,aux2);

    return;
}

void dataToString (uint8_t mode, uint8_t bright, uint8_t velocity, uint8_t orientation,uint8_t* texto)
{
    uint8_t i=0;

    data[0]=mode+48;
    data[1]=',';

    data[2]=bright+48;
    data[3]=',';

    data[4]=velocity+48;
    data[5]=',';

    data[6]=orientation+48;
    data[7]=',';

    while(*(texto+i) != '\0')
    {
        data[i+8]= *(texto+i);
        i++;
    }

    return;
}
void verifyData (uint8_t* data)
{
    char* aux;
    char aux2[74];

    strcpy(aux2,data);

    aux = strtok(data,",");
    if ( *aux<(0+48) || *aux>(2+48) || strlen(aux)>1 )  //si tiene mas de dos caracteres entonces es un numero mas de 0a9 -> error
        return;
    aux = strtok(NULL,",");
    if ( *aux<(0+48) || *aux>(9+48) || strlen(aux)>1 )
        return;
    aux = strtok(NULL,",");
    if ( *aux<(0+48) || *aux>(9+48) || strlen(aux)>1 )
        return;
    aux = strtok(NULL,",");
    if ( *aux<(0+48) || *aux>(1+48) || strlen(aux)>1 )
        return;
    aux = strtok(NULL,"\n");
    if (strlen(aux)>TAM_BUFF_TEXTO)
        return;

    dataOk = 1;
    strcpy(data,aux2);

    return;
}

uint8_t dataLen (uint8_t* data)
{
    uint8_t i=0;

    while(*(data+i) != '\0')    //nos da el tamano de propiedad hasta el ultimo caracter.
        i++;
    return i;
}

