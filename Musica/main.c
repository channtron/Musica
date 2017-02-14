#include <msp430.h> 
#include "grlib.h"
#include "partituras.h"
#include "Crystalfontz128x128_ST7735.h"
#include "HAL_MSP430G2_Crystalfontz128x128_ST7735.h"
#include <stdio.h>

/*
 * main.c
 */

int lee_ch(char canal){
	ADC10CTL0 &= ~ENC;					//deshabilita el ADC
	ADC10CTL1&=(0x0fff);				//Borra canal anterior
	ADC10CTL1|=canal<<12;				//selecciona nuevo canal
	ADC10CTL0|= ENC;					//Habilita el ADC
	ADC10CTL0|=ADC10SC;					//Empieza la conversión
	LPM0;								//Espera fin en modo LPM0
	return(ADC10MEM);					//Devuelve valor leido
	}

------------------------------------------------------------------
void inicia_ADC(char canales){
	ADC10CTL0 &= ~ENC;		//deshabilita ADC
    ADC10CTL0 = ADC10ON | ADC10SHT_3 | SREF_0|ADC10IE; //enciende ADC, S/H lento, REF:VCC, con INT
    ADC10CTL1 = CONSEQ_0 | ADC10SSEL_0 | ADC10DIV_0 | SHS_0 | INCH_0;
    //Modo simple, reloj ADC, sin subdivision, Disparo soft, Canal 0
    ADC10AE0 = canales; //habilita los canales indicados
    ADC10CTL0 |= ENC; //Habilita el ADC
}
------
void inicia_ADC(void){
	ADC10CTL0 &= ~ENC; // deshabilita ADC
	/*Habilitar int, Encender ADC,   Conv. Multiple,    S/H:x64,    V+=Vcc V-=gnd*/
	ADC10CTL0 = ADC10IE | ADC10ON | MSC | ADC10SHT_3 | SREF_0;
	/*varios canales,    reloj ADC10OSC, sin preescalado, Disparo en T0, canal 4(primero a leer)*/
	ADC10CTL1 = CONSEQ_1 | ADC10SSEL_0 | ADC10DIV_0 | SHS_2 | INCH_4;
	ADC10AE0 = 0x19; // 0x19=00011111: activar entradas 4, 3, 2, 1, 0
	ADC10DTC0 = ADC10CT; // transferencia Continua: se resetea solo cuando acaba
	ADC10DTC1 = 5; // Numero de transferencias a hacer
	ADC10SA = (unsigned int)BufferADC; // Direccion de comienzo de la transferencia
	ADC10CTL0 |= ENC; // habilita ADC
}
-----------------------------------------------------------------------------------------------------


void conf_reloj(char VEL){
	BCSCTL2 = SELM_0 | DIVM_0 | DIVS_0;
	switch(VEL){
	case 1:
		if (CALBC1_1MHZ != 0xFF) {
			DCOCTL = 0x00;
			BCSCTL1 = CALBC1_1MHZ;      /* Set DCO to 1MHz */
			DCOCTL = CALDCO_1MHZ;
		}
		break;
	case 8:

		if (CALBC1_8MHZ != 0xFF) {
			__delay_cycles(100000);
			DCOCTL = 0x00;
			BCSCTL1 = CALBC1_8MHZ;      /* Set DCO to 8MHz */
			DCOCTL = CALDCO_8MHZ;
		}
		break;
	case 12:
		if (CALBC1_12MHZ != 0xFF) {
			__delay_cycles(100000);
			DCOCTL = 0x00;
			BCSCTL1 = CALBC1_12MHZ;     /* Set DCO to 12MHz */
			DCOCTL = CALDCO_12MHZ;
		}
		break;
	case 16:
		if (CALBC1_16MHZ != 0xFF) {
			__delay_cycles(100000);
			DCOCTL = 0x00;
			BCSCTL1 = CALBC1_16MHZ;     /* Set DCO to 16MHz */
			DCOCTL = CALDCO_16MHZ;
		}
		break;
	default:
		if (CALBC1_1MHZ != 0xFF) {
			DCOCTL = 0x00;
			BCSCTL1 = CALBC1_1MHZ;      /* Set DCO to 1MHz */
			DCOCTL = CALDCO_1MHZ;
		}
		break;

	}
	BCSCTL1 |= XT2OFF | DIVA_0;
	BCSCTL3 = XT2S_0 | LFXT1S_2 | XCAP_1;

}


Graphics_Context g_sContext;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	conf_reloj(16);
	
	//Timer A1 para interrupción de 100ms
	TA1CCTL0=CCIE;
	TA1CCTL1=OUTMOD_0;
	TA1CTL=TASSEL_1 | MC_1;
	TA1CCR0=1199;   //PERIODO=100ms

	Crystalfontz128x128_Init();

	/* Set default screen orientation */
	Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

	/* Initializes graphics context */
	Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128);

	UARTinit();	//Inicializar el UCB0 para UART a 9600
	//inicia_ADC(BIT4); inicia_ADC(BIT1); ó inicia_ADC();
	__bis_SR_register(GIE); //Habilitar interrupciones

	while(1){
		LPM0;
	}
	return 0;s
}

#pragma vector=ADC10_VECTOR
__interrupt void ConvertidorAD(void)
{
    LPM0_EXIT;	//Despierta al micro al final de la conversión
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR_HOOK(void)
{
	LPM0_EXIT;	//Despierta al micro cada 100ms
}
