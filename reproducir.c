/*
* reproducir.c
*
* Created on: 15/02/2017
*	Author: Chulani
*/

#include <msp430.h> 
#include "grlib.h"
#include "partituras.h"
#include "Crystalfontz128x128_ST7735.h"
#include "HAL_MSP430G2_Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include "uart_STDIO.h"

Graphics_Context g_sContext;

unsigned long int color;
unsigned int i,duracion,t;
Cancion songs[7];
char caracter;
char estado;

void inicia_Rep(void){

	//Inicializar songs
	songs[0]=IndianaJones;
 	songs[1]=DarthVader;
	songs[2]=TheShire;
    	songs[3]=TheSimpsons;
    	songs[4]=TetrisTheme;
    	songs[5]=GameOfThrones;
    	songs[6]=NocheDePaz;

	//Timer A1 para interrupción según el tempo de la canción
    	TA1CCTL0=CCIE;
    	TA1CCTL1=OUTMOD_0;
    	TA1CTL=TASSEL_1 | MC_1;

	t=0;
    	duracion=0;
    	i=0;
	caracter=10;
    	__bis_SR_register(GIE);		//Habilitar interrupciones
    	UARTinit();		//Inicializa el UCB0 para uart a 9600
}

char menu_elige(void){
	while(caracter>6){
	TA0CCR1=1;	//Silenciar para que no haya ruido en la selección de la canción
    	//Escribir en el terminal el menú de canciones mediante puerto serie
    	UARTprintCR("Elige una nueva cancion:");
        UARTprintCR("0.Indiana Jones");
        UARTprintCR("1.Darth Vader");
        UARTprintCR("2.The Shire");
        UARTprintCR("3.The Simpsons");
        UARTprintCR("4.Tetris");
        UARTprintCR("5.Game of Thrones");
        UARTprintCR("6.Noche de Paz");
	caracter=UARTgect()-'0'; //Guardar tecla recibida por puerto serie y restar '0' para convertirlo en numeric
	if (carcarter>6) UARTprintCR("Elige un número entre el 0 y el 6");
	}

	return(caracter);
}

void una_cancion(char c){

	TA1CCR0=songs[c].tempo;		//Tempo de la canción elegida
    	if(songs[c].notas[i]==SIL)	//Nota es un silencio
    		{
    		TA0CCR1=1;			//Silenciar
    		i++;
    		duracion=songs[c].notas[i];		//Duración de cada nota
    		t=0;
    		LPM0;
    		Graphics_drawString(&g_sContext,"SIL",15,12,60,OPAQUE_TEXT);	//SIL en pantalla del Launchpad
    		}
       	else	//Nota diferente de silencio
    	   	{
    		TA0CCR0=Nota[songs[c].notas[i]];	//Tipo de nota
    		TA0CCR1=TA0CCR0>>4;
    		i++;
    		duracion=songs[c].notas[i];
    		t=0;
    		LPM0;
        	Graphics_drawString(&g_sContext,Notas_N[songs[c].notas[i]],15,12,60,OPAQUE_TEXT);	//Nombre nota en pantalla Launchpad
	    	}
  	Graphics_drawString(&g_sContext,songs[c].nombre,15,12,30,OPAQUE_TEXT);	//Título canción en pantalla Launchpad
    	i++;
    	if(songs[c].notas[i]==0){
       	i=0;
    	return 0; 	//Ha terminado la canción
    		}
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR_HOOK(void)
{
	t++;
	if(t>=duracion)LPM0_EXIT;   //Sale cuando termina el tiempo de la nota que suena
}