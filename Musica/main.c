#include <msp430.h> 
#include "grlib.h"
#include "partituras.h"
#include "Crystalfontz128x128_ST7735.h"
#include "HAL_MSP430G2_Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include "MSP430_TMP_OPT.h"
#include "reproducir.h"
#include "uart_STDIO.h"
/*
 * main.c
 */
char estado;
char carac; //Para elegir la canción
char flagboton=0; //para controlar las pulsaciones
char flagRep; //Para saber si estamos reproduciendo, para el timer
char tec;  //Tecla introducida por uart
unsigned int t,duracion;
const unsigned int NotaTec[]={30578,28862,27240,25714,24270,22908,21622,20408,19264,18182,17168,16202,1};
unsigned int teclita;
int ejex, ejey;
int DeviceID;
unsigned long int Luz;
int circle1[]={35,35};//coordenadas centrales de los circulos{X,Y}
int circle2[]={120,110};
int circle3[]={40,100};
int circle4[]={80,40};
int circle5[]={50,50};


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

void pantalla_inicial(void){
	if(P2IN&BIT5){//No pasas a inicio hasta que sueltas el botón del joystick
		flagboton=0;
		LPM0;
	}
	if(flagboton==0){
		//P1.1 y P1.2 de entrada y salida
		P1SEL&=~(BIT1|BIT2);
		P1SEL2&=~(BIT1|BIT2);
		P1REN|=(BIT1|BIT2);
		P1OUT|=(BIT1|BIT2);
		Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
		Graphics_drawString(&g_sContext,"Elige modo:",30,10,10,OPAQUE_TEXT);
		Graphics_drawString(&g_sContext,"Up.- Reproducir",30,10,40,OPAQUE_TEXT);
		Graphics_drawString(&g_sContext,"Dw.- Componer",30,10,70,OPAQUE_TEXT);
		if (!(P1IN&BIT1)){
			estado=1; //Pasamos a Reproducir
			flagboton=1;
			Graphics_clearDisplay(&g_sContext);
		}
		if (!(P1IN&BIT2)){
			estado=2; //Pasamos a Componer
			flagboton=1;
			Graphics_clearDisplay(&g_sContext);
		}
	}
}

void reproducir(void){
	if(P1IN&BIT1){//No pasas a inicio hasta que sueltas el botón del joystick
			flagboton=0;
			LPM0;
		}
	if(flagboton==0){
		inicia_Rep();
		flagRep=1;
		carac=menu_elige();
		una_cancion(carac);
		flagRep=0;
		if (!(P2IN&BIT5)){
			estado=0;
			flagboton=1;
		}
	}
}

void componer(void){
	if(P1IN&BIT2){//No pasas a inicio hasta que sueltas el botón del joystick
			flagboton=0;
			LPM0;
		}
	if(flagboton==0){
		inicia_ADC(BIT0); //Eje x del joystick
		inicia_ADC(BIT3); //Eje y del joystick
		Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
		Graphics_drawString(&g_sContext,"Elige forma:",30,10,10,OPAQUE_TEXT);
		Graphics_drawString(&g_sContext,"Up.- Teclado",30,10,40,OPAQUE_TEXT);
		Graphics_drawString(&g_sContext,"Dw.- Joycom",30,10,70,OPAQUE_TEXT);
		if (!(P1IN&BIT1)){
			estado=3; //Usamos Teclado
			flagboton=1;
			Graphics_clearDisplay(&g_sContext);
		}
		else if (!(P1IN&BIT2)){
			estado=4; //Usamos Joystick
			flagboton=1;
			Graphics_clearDisplay(&g_sContext);
		}
		else if (!(P2IN&BIT5)){
			estado=0;
			flagboton=1;
		}
	}
}

void joystick(void){
	if(P1IN&BIT2){//No pasas a inicio hasta que sueltas el botón del joystick
		flagboton=0;
		LPM0;
	}
	if(flagboton==0){
		ejex=lee_ch(0);
		ejey=1024-lee_ch(3);

		Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);//borrar circulo antio, esto sería recomendable antes de leer los ejes(podemos dibujar primero las bolas y despues cambiar el sonido
		Graphics_fillCircle(&g_sContext,circle1[0]+8,circle1[1]+8,30 );// MAS 8 ES LA POSICION CENTRAL
		Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);//dibujar nuevo circulo
		Graphics_fillCircle(&g_sContext,circle1[0]+(ejex>>6),circle1[1]+(ejey>>6),20 );

		if (!(P2IN&BIT5)){
					estado=0;
					flagboton=1;
		}
	}
}

void teclado(void){
	if(P1IN&BIT1){//No pasas a inicio hasta que sueltas el botón del joystick
		flagboton=0;
		LPM0;
	}
	if(flagboton==0){
		UARTinit();
		tec=UARTgetc();
		asigna(tec);
		ejey=lee_ch(3);
		if (ejey<205) teclita=teclita<<2;
		else if (ejey<410) teclita=teclita<<1;
		else if (ejey<615) teclita=teclita;
		else if (ejey<820) teclita=teclita>>1;
		else teclita=teclita>>2;
		//Inicialización y leer I2C
		CS_HIGH;			//Deshabilita la pantalla
		guarda_conf();		//Almacena la config. de la USCI (para la pantalla)
		OPT3001_init();		//Configura el I2C apuntando al OPT3001
		DeviceID=Lee_OPT3001(DEVICEID_REG);
		Luz=OPT3001_getLux();	//Lee la luminosidad
		restaura_conf();	//Vuelve a modo SPI (pantalla)
		CS_LOW;				//Habilita la pantalla

		//Timer para reproducir la nota
		TA0CCR0=teclita;
		TA0CCR1=TA0CCR0>>4;

		//Pantalla

		if (!(P2IN&BIT5)){
					estado=0;
					flagboton=1;
		}
	}
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
	Graphics_clearDisplay(&g_sContext);

	__bis_SR_register(GIE); //Habilitar interrupciones

	estado=0;
	while(1){
		LPM0;
		switch(estado){
		case 0:
			pantalla_inicial(); //Función
		break;
		case 1:
			reproducir(); //Función
		break;
		case 2:
			componer(); //Función
		break;
		case 3:
			teclado(); //Función
		break;
		case 4:
			joystick(); //Función
		break;
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
	if (flagRep==0)LPM0_EXIT;	//Despierta al micro cada 100ms
	else {						//Despierta al micro dependiendo de la duración de la nota
		t++;
		if(t>=duracion)LPM0_EXIT;   //Sale cuando termina el tiempo de la nota que suena
	}
}
