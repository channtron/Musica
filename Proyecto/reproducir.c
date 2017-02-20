/*
* reproducir.c
*
* Created on: 15/02/2017
*	Author: Chulani & Pelayo
*/

#include <msp430.h> 
#include "grlib.h"
#include "Crystalfontz128x128_ST7735.h"
#include "HAL_MSP430G2_Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include "uart_STDIO.h"
#include "reproducir.h"
Graphics_Context g_sContext;

const unsigned int Nota[]={61156,57724,54480,51428,48540,45816,43244,40818,38528,36364,34336,32404,
		30578,28862,27240,25714,24270,22908,21622,20408,19264,18182,17168,16202,
		15289,14431,13620,12857,12135,11454,10811,10204,9632,9091,8584,8101,1};

const char ESCALA[]={RE-12,SOL-12,LA-12,FA,SOL}; //Come Together
const char ESCALA1[]={DO,RE,FA,SOL,SIb};//Little Green Bag
const char ESCALA2[]={FA+12,LA+12,DO+12,RE+12,MIb+12}; //Rock 'n Roll

unsigned int teclita;
const unsigned int NotaTec[]={30578,28862,27240,25714,24270,22908,21622,20408,19264,18182,17168,16202,1};

void asigna(char c){
	switch(c){
	case 83: teclita=NotaTec[0];
	break;

	case 69: teclita=NotaTec[1];
	break;

	case 68: teclita=NotaTec[2];
	break;

	case 82: teclita=NotaTec[3];
	break;

	case 70: teclita=NotaTec[4];
	break;

	case 71: teclita=NotaTec[5];
	break;

	case 89: teclita=NotaTec[6];
	break;

	case 72: teclita=NotaTec[7];
	break;

	case 85: teclita=NotaTec[8];
	break;

	case 74: teclita=NotaTec[9];
	break;

	case 73: teclita=NotaTec[10];
	break;

	case 75: teclita=NotaTec[11];
	break;

	case 76: teclita=NotaTec[0]>>1;
	break;

	case 32: teclita=NotaTec[12];
	break;
	}
}

void asignajoy(unsigned long int x, unsigned long int y, const char escala[]){
	//Asignacion nota
	if(x<100) TA0CCR0=Nota[escala[0]];

	else if(x<460) TA0CCR0=Nota[escala[1]];

	else if(x<560) TA0CCR0=Nota[escala[2]];

	else if(x<900) TA0CCR0=Nota[escala[3]];

	else TA0CCR0=Nota[escala[4]];

	//Asignacion volumen
	if(y<160)	TA0CCR1=1;	//Silencio

	else TA0CCR1=TA0CCR0/20-9;	//Forma lineal de aumentar el volumen con el eje y del joystick
}

int modfrec(unsigned long int l, unsigned long int lr){
	int ret;	//Valor que va a modificar la frecuencia
	if(l>lr) ret=l*5000/(5000-lr);
	else	ret=5000*l/lr-5000;
	return ret;
}

//Coordenadas centrales de los circulos{X,Y}
int circle1[]={30,45};
int circle2[]={40,100};
int circle3[]={80,40};
int yrep, xrep;

void DibujaCirculos(int x, int y){
	Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_SNOW-13107*x);	//Color de fondo que cambia con el eje x del joystick
	yrep=1024-y;	//Como los valores de y en la pantalla crecen hacia abajo, es necesario para que los circulos se muevan en el mismo sentido que el eje y del joystick
	xrep=1024-x;	//Para que los circulos se muevan en sentido contrario al eje x del joystick

	Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_SNOW-13107*x);	//Color del circulo exterior
	Graphics_fillCircle(&g_sContext,circle1[0]+(xrep>>8),circle1[1]+(y>>8),18);	//Circulo que se mueve al contrario de la posicion del joystick
	Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE+100*x+50*y);	//Color del circulo interior
	Graphics_fillCircle(&g_sContext,circle1[0]+(x>>8),circle1[1]+(yrep>>8),10);	//Circulo que se mueve mismo sentido que posicion del joystick

	Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_SNOW-13107*x);	//Color del circulo exterior
	Graphics_fillCircle(&g_sContext,circle2[0]+(xrep>>6),circle2[1]+(y>>6),36);	//Circulo que se mueve al contrario de la posicion del joystick
	Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_GREEN+88*x+275*y);	//Color del circulo interior
	Graphics_fillCircle(&g_sContext,circle2[0]+(x>>6),circle2[1]+(yrep>>6),25);	//Circulo que se mueve mismo sentido que posicion del joystick

	Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_SNOW-13107*x);	//Color del circulo exterior
	Graphics_fillCircle(&g_sContext,circle3[0]+(xrep>>7),circle3[1]+(y>>7),32);	//Circulo que se mueve al contrario de la posicion del joystick
	Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_PERU+10*x+165*y);	//Color del circulo interior
	Graphics_fillCircle(&g_sContext,circle3[0]+(x>>7),circle3[1]+(yrep>>7),20);	//Circulo que se mueve mismo sentido que posicion del joystick
}

char flagboton1=0;	//Flag para el boton de abajo del BP
char flagboton2=0;	//Flag para el boton de arriba del BP

int selectescala(int n, unsigned long int x, unsigned long int y){
	if (!(P1IN&BIT2)){	//Se pulsa el boton de abajo del BP
		flagboton1=1;
	}
	else if ((P1IN&BIT2)&&flagboton1){
		flagboton1=0;
		n++;
	}
	if (!(P1IN&BIT1)){	//Se pulsa el boton de arriba del BP
		flagboton2=1;
	}
	else if ((P1IN&BIT1)&&flagboton2){
		flagboton2=0;
		n--;
	}
	if(n<0) n=2;
	else if(n>2) n=0;
	Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
	Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);

	//Asignacion de notas segun la escala y posicion del joystick
	switch(n){
	case 0:
		Graphics_drawString(&g_sContext,"CT ",25,95,5,OPAQUE_TEXT);
		asignajoy(x,y,ESCALA);
	break;
	case 1:
		Graphics_drawString(&g_sContext,"LGB",25,95,5,OPAQUE_TEXT);
		asignajoy(x,y,ESCALA1);
	break;
	case 2:
		Graphics_drawString(&g_sContext,"RnR",25,95,5,OPAQUE_TEXT);
		asignajoy(x,y,ESCALA2);
	break;
	}
	return n;
}
