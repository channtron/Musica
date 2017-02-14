#include <msp430.h> 
#include "grlib.h"
#include "partituras.h"
#include "Crystalfontz128x128_ST7735.h"
#include "HAL_MSP430G2_Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include "MSP430_TMP_OPT.h"

/*
 * main.c
 */
char estado;
char flagBot;

Graphics_Context g_sContext;

int lee_ch(char canal){
	ADC10CTL0 &= ~ENC;					//deshabilita el ADC
	ADC10CTL1&=(0x0fff);				//Borra canal anterior
	ADC10CTL1|=canal<<12;				//selecciona nuevo canal
	ADC10CTL0|= ENC;					//Habilita el ADC
	ADC10CTL0|=ADC10SC;					//Empieza la conversión
	LPM0;								//Espera fin en modo LPM0
	return(ADC10MEM);					//Devuelve valor leido
	}

void inicia_ADC(char canales){
	ADC10CTL0 &= ~ENC;		//deshabilita ADC
    ADC10CTL0 = ADC10ON | ADC10SHT_3 | SREF_0|ADC10IE; //enciende ADC, S/H lento, REF:VCC, con INT
    ADC10CTL1 = CONSEQ_0 | ADC10SSEL_0 | ADC10DIV_0 | SHS_0 | INCH_0;
    //Modo simple, reloj ADC, sin subdivision, Disparo soft, Canal 0
    ADC10AE0 = canales; //habilita los canales indicados
    ADC10CTL0 |= ENC; //Habilita el ADC
}

void pantalla_inicial(void){
	while(P2IN&BIT5){ //No pasas a inicio hasta que sueltas el botón del joystick
		LPM0;
	}
	//P1.1 y P1.2 de entrada y salida
	P1SEL&=~(BIT1|BIT2);
	P1SEL2&=~(BIT1|BIT2);
	P1REN|=(BIT1|BIT2);
	P1OUT|=(BIT1|BIT2);
	Graphics_clearDisplay(&g_sContext);
	Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
	Graphics_drawString(&g_sContext,"Elige modo:",30,10,10,OPAQUE_TEXT);
	Graphics_drawString(&g_sContext,"Up.- Reproducir",30,10,40,OPAQUE_TEXT);
	Graphics_drawString(&g_sContext,"Dw.- Componer",30,10,70,OPAQUE_TEXT);
	if (!(P1IN&BIT1)) estado=1; //Pasamos a Reproducir
	if (!(P1IN&BIT2)) estado=2; //Pasamos a Componer
}

void reproducir(void){
	while(P1IN&BIT1) LPM0;
}

void componer(void){
	while(P1IN&BIT2) LPM0;
	inicia_ADC(BIT0); //Eje x del joystick
	inicia_ADC(BIT3); //Eje y del joystick

	//Inicialización y leer I2C
	CS_HIGH;			//Deshabilita la pantalla
	guarda_conf();		//Almacena la config. de la USCI (para la pantalla)
	OPT3001_init();		//Configura el I2C apuntando al OPT3001
	DeviceID=Lee_OPT3001(DEVICEID_REG);
	Luz=OPT3001_getLux();	//Lee la luminosidad
	restaura_conf();	//Vuelve a modo SPI (pantalla)
	CS_LOW;				//Habilita la pantalla
	Graphics_clearDisplay(&g_sContext);
	Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
	Graphics_drawString(&g_sContext,"Elige forma:",30,10,10,OPAQUE_TEXT);
	Graphics_drawString(&g_sContext,"Up.- Teclado",30,10,40,OPAQUE_TEXT);
	Graphics_drawString(&g_sContext,"Dw.- Joycom",30,10,70,OPAQUE_TEXT);
	if (!(P1IN&BIT1)) estado=3; //Usamos Teclado
	if (!(P1IN&BIT2)) estado=4; //Usamos Joystick
}

void joystick(void){

}

void teclado(void){

}

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


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	conf_reloj(16);

	//Configuracion boton joystick
	P2SEL&=~BIT5;
	P2SEL2&=~BIT5;
	P2REN|=BIT5;
	P2OUT|=BIT5;

	//PWN en el Pin 2.6
	P2DIR|=BIT6;
	P2SEL|=BIT6;
	P2SEL2&=~BIT6;
	P2SEL&=~BIT7;
	P2SEL2&=~BIT7;

	//Timer A0 para el PWM;
	TA0CCTL1=OUTMOD_7;
	TA0CTL=TASSEL_2 | MC_1;
	TA0CCR0=15999;
	TA0CCR1=1;

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
	Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
	Graphics_setFont(&g_sContext, &g_sFontCm16b);

	//UARTinit(); Inicializar el UCB0 para UART a 9600
	//inicia_ADC(BIT0);	//Eje x
	//inicia_ADC(BIT3);	//Eje y
	__bis_SR_register(GIE); //Habilitar interrupciones

	estado=0;
	while(1){
		LPM0;
		switch(estado){
		case 0:
			pantalla_inicial(); //Función

		case 1:
			reproducir(); //Función

		case 2:
			componer(); //Función

		case 3:
			teclado(); //Función

		case 4:
			joystick(); //Función
		}
	}
	return 0;
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
