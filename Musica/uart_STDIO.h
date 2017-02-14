/*
 * lcd_uart.h
 *
 *  Created on: 15/12/2014
 *      Author: Manolo
 */

#ifndef EJEMPLO9_1516_LCD_UART_H_
#define EJEMPLO9_1516_LCD_UART_H_


/* Funciones para el manejo de la consola a través de la UART*/

void UARTinit(void);					// Inicializa el UCB0 para uart a 9600
void UARTprintc(char c);				// manda un caracter
void UARTprint(const char * frase);		//manda una cadena de caracteres
void UARTprintCR(const char *frase);	//Manda una cadena, acabada en CR+LF
void UARTgets( char *BuffRx, int TMAX);	//Lee una cadena (acabada en CR+LF)
char UARTgetc(void);					//Lee un caracter
int  UARTgetint(void);					//Lee una cadena y devuelve su valor entero
void UARTnum(int Num);


#endif /* EJEMPLO9_1516_LCD_UART_H_ */
