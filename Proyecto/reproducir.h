/*
* reproducir.h
*
* Created on: 15/02/2017
*	Author: Chulani & Pelayo
*/

#ifndef PROYECTO_1617_REPRODUCIR_H_
#define PROYECTO_1617_REPRODUCIR_H_

//Los define y Nota[] se han cogido del fichero partituras.h aportado por el profesor para la realizacion de las practicas

#define 	DO 12
#define 	REb	13
#define		RE	14
#define		MIb	15
#define		MI	16
#define		FA	17
#define		SOLb	18
#define		SOL	19
#define		LAb	20
#define		LA	21
#define		SIb	22
#define		SI	23
#define 	SIL 36

extern char flagboton1;
extern char flagboton2;
extern unsigned int teclita;
extern const unsigned int Nota[];
extern const unsigned int NotaTec[];

extern const char ESCALA[];
extern const char ESCALA1[];
extern const char ESCALA2[];


/* Funciones para el manejo del reproductor*/
void asigna(char c);	//Asigna una frecuencia determinada segun la tecla pulsada en el teclado del ordenador
void asignajoy(unsigned long int x, unsigned long int y, const char escala[]);	//Asignacion de la nota y el volumen a reproducir segun la pos del joystick y la escala en la que se encuentra
int modfrec(unsigned long int l, unsigned long int lr);	//Valor para modificar la frecuencia de la nota dependiendo de la luz actual y la luz que tenga como referencia
void DibujaCirculos(int x, int y);	//Dibujar la pantalla del BP
int selectescala(int n, unsigned long int x, unsigned long int y);	//Elegir escala segun los botones del BP y llamada a la funcion asignajoy()

#endif	/*PROYECTO_1617_REPRODUCIR_H_ */
