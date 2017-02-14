/*
 * lcd_uart.c
 *
 *  Created on: 15/12/2014
 *      Author: Manolo
 */





#include "uart_STDIO.h"

#include <msp430.h>


void UARTinit(void){
	 	 P1SEL2|= BIT1 | BIT2;	//P1.1, P1.2 para la UART
	 	 P1SEL|= BIT1 | BIT2;

	 	 UCA0CTL1 |= UCSWRST;			// Reset uart para configurar
	 	 UCA0CTL1 = UCSSEL_2 | UCSWRST;	// Conf. como asincrono
 	     UCA0MCTL = UCBRF_0 | UCBRS_1;	// Modulacion
 	    if( BCSCTL1 == CALBC1_16MHZ )
 	    	{
 	    	UCA0BR0 = 130;
 	    	UCA0BR1 = 6;
 	    	}	// 16MHz/(6*256+130)=9603bps
 	    else
 	    	{
 	    	UCB0BR0 = 104; // 1MHz/104=9615,38..
 	    	}
 	     UCA0CTL1 &= ~UCSWRST;			// Quitar Reset
 	     IFG2 &= ~(UCA0RXIFG);			// Borrar flag
	 	 IE2 &=~ (UCA0RXIE+UCA0TXIE);	// Deshabilitar las ints.
}

void UARTprintc(char c){
	while (!(IFG2 & UCA0TXIFG)); 	//espera a Tx libre
			    	UCA0TXBUF = c;
}

void UARTprint(const char * frase){
	while(*frase)UARTprintc(*frase++);
}

void UARTprintCR(const char *frase){
	while(*frase)UARTprintc(*frase++);
	UARTprintc(10);
	UARTprintc(13);

}

char UARTgetc( void){
	char caracter;
	while(!(IFG2&UCA0RXIFG));
		caracter=UCA0RXBUF;
		UARTprintc(caracter);
	return(caracter);
}
void UARTgets( char *BuffRx, int TMAX){
	int indice=0;
	char caracter;
	do{
		while(!(IFG2&UCA0RXIFG));
		caracter=UCA0RXBUF;
		UARTprintc(caracter);
		if((caracter!=10)&&(caracter!=13)){BuffRx[indice]=caracter;
		indice++;}
	}while((caracter!=13)&&(indice<TMAX));

	if(indice==TMAX)indice--;
	BuffRx[indice]=0;
}


int UARTgetint(void){
		char caracter;
		char Err=0;
		unsigned long num=0;
		unsigned int Num;
		do{
				while(!(IFG2&UCA0RXIFG));
				caracter=UCA0RXBUF;
				if(caracter<'0' || caracter>'9' ) {if ((caracter!=10)&&(caracter!=13)){Err=1;}}
					else{
					num*=10;
					num+=(caracter-'0');
					if(num>0xffff) {num-=caracter-'0'; num/=10; Err=2;}}
				UARTprintc(caracter);
			}while((caracter!=13)&&(Err==0));
		if(Err==1) { Num=0xffff;}
		else {Num=(int)num;}


	return(Num);
}


void UARTnum(int Num){
	char nch[]="0000";
		nch[0]+=Num/1000;
		Num=Num-1000*(Num/1000);
		nch[1]+=Num/100;
		Num=Num-100*(Num/100);
		nch[2]+=Num/10;
			Num=Num-10*(Num/10);
			nch[3]+=Num;
			UARTprint(nch);
}



