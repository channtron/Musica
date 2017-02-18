/*
 * partituras.c
 *
 *  Created on: 16/12/2015
 *      Author: Manolo
 */
#include "partituras.h"

const unsigned int Nota[]={61156,57724,54480,51428,48540,45816,43244,40818,38528,36364,34336,32404,
		30578,28862,27240,25714,24270,22908,21622,20408,19264,18182,17168,16202,
		15289,14431,13620,12857,12135,11454,10811,10204,9632,9091,8584,8101,1
};

const char * Notas_N[]={"DO0  ", "REb0 ","RE0  ","MIb0 ", "MI0  ", "FA0  ","SOLb0","SOL0 ", "LAb0 ","LA0  ","SIb0 ", "SI0  ",
		"DO   ", "REb  ","RE   ","MIb  ", "MI   ", "FA   ","SOLb ","SOL  ", "LAb  ","LA   ","SIb  ", "SI   ",
		"DO1 ", "REb1","RE1 ","MIb1", "MI1 ", "FA1 ","SOLb1","SOL1 ", "LAb1","LA1 ","SIb1", "SI1 ", "-----"
};
/* PARTITURAS para el primer apartado */

const char COPLITA1[]={SOL-12, SOL-12, LA-12, SOL-12, DO,SI-12,
		SOL-12, SOL-12, LA-12, SOL-12,RE,DO,
		SOL-12, SOL-12,SOL,MI,DO,SI-12,LA-12,
             FA,FA,MI,DO,RE,DO,0};
const char COPLITA2[]={DO,RE,MI,FA,SOL,SOL,
		DO+12,DO+12,SI,SI,LA,SOL,
		SOL,LA,SOL,LA,SOL,FA,
		RE,MI,RE,MI,RE,DO,0};

const char COPLITA3[]={MI,MI,MI,FA,SOL,SOL,SOL,SOL,
		DO+12,DO+12,DO+12,DO+12,DO+12,DO+12,DO+12,DO+12,
		RE,RE,RE,MI,FA,FA,FA,FA,FA,FA,FA,FA,FA,FA,
		SOL,SOL,SOL,LA,SI,SI,SI,SI,
		FA+12,FA+12,FA+12,FA+12,
		FA+12,FA+12,FA+12,FA+12,
		LA,LA,LA,SI,DO+12,DO+12,DO+12,DO+12,
		RE+12,RE+12,RE+12,RE+12,MI+12,MI+12,MI+12,MI+12,
		MI,MI,MI,FA,SOL,SOL,SOL,SOL,
		DO+12,DO+12,DO+12,DO+12,DO+12,DO+12,DO+12,DO+12,
		RE+12,RE+12,RE+12,MI+12,
		FA+12,FA+12,FA+12,FA+12,
				FA+12,FA+12,FA+12,FA+12,
				FA+12,FA+12,FA+12,FA+12,
		SOL,SOL,SOL,SOL,
		MI+12,MI+12,MI+12,MI+12,
		RE+12,RE+12,RE+12,SOL,
		MI+12,MI+12,MI+12,MI+12,
		RE+12,RE+12,RE+12,SOL,
		MI+12,MI+12,MI+12,MI+12,
		RE+12,RE+12,RE+12,SI+12,
		DO+12,DO+12,DO+12,DO+12,DO+12,DO+12,DO+12,DO+12,
		DO+12,DO+12,DO+12,DO+12,0
};


/* PARTITURAS para el segundo apartado */


const char indiana[]={MI,3,FA,1,SOL,4,
		DO+12,8,
		RE,3,MI,1,FA,12,
		SOL,3,LA,1,SI,4,
		FA+12,8,
		LA,3,SI,1,DO+12,4,
		RE+12,4,MI+12,4,
		MI,3,FA,1,SOL,4,
		DO+12,8,
		RE+12,3,MI+12,1,
		FA+12,12,
		SOL,3,SOL,1,MI+12,4, RE+12,3,
		SOL,1,	MI+12,4,	RE+12,3,
		SOL,1,	FA+12,4,	MI+12,3,
		RE+12,1,DO+12,12,0
};

const char darthvader[]={
		SOL,3,SIL,1,SOL,3,SIL,1,SOL,3,SIL,1,MIb,3,SIb,1,
		SOL,4,MIb,3,SIb,1,SOL,8,
		RE+12,3,SIL,1,RE+12,3,SIL,1,RE+12,3,SIL,1,MIb+12,3,SIb,1,
		SOLb,4,MIb,3,SIb,1,SOL,8,
		SOL+12,4,SOL,2,SIL,1, SOL,1,SOL+12,4,SOLb+12,3,FA+12,1,
		MI+12,1,MIb+12,1,MI+12,1,SIL,2,LAb,2,REb+12,4,DO+12,3,SI,1,
		SIb,1,LA,1,SIb,2,SIL,2,MIb,2,SOLb,4,MIb,3,SOLb,1,
		SIb,4,SOL,3,SIb,1,RE+12,8,
		SOL+12,4,SOL,2,SIL,1, SOL,1,SOL+12,4,SOLb+12,3,FA+12,1,
		MI+12,1,MIb+12,1,MI+12,1,SIL,2,LAb,2,REb+12,4,DO+12,3,SI,1,
		SIb,1,LA,1,SIb,2,SIL,2,MIb,2,SOLb,4,MIb,3,SIb,1,
		SOL,4,MIb,3,SIb,1,SOL,7,SIL,1,

0};

const char hobbit[]={DO,2,RE,2,MI,4,SOL,4,MI,2,RE,2,
		DO,8,MI,2,SOL,2,
		LA,6,DO+12,2,SI,2,SOL,2,MI,6,
		FA,1,MI,1,RE,4,DO,2,RE,2,MI,4,SOL,4,
		RE,2,MI,2,DO,8,
		MI,2,SOL,2,LA,4,SOL,4,MI,4,
		RE,8,0};

const char Simps[]={DO,8,SOLb,8,SOL,16,
		DO+12,6,MI+12,4,SOLb+12,4,LA+12,2,
		SOL+12,6,MI+12,4,DO+12,4,LA,2,
		SOLb,1,SIL,1,SOLb,1,SIL,1,SOLb,1,SIL,1,SOL,8,SIL,2,
		SIL,2,SOLb,1,SIL,1,SOLb,1,SIL,1,SOLb,1,SIL,1,SOL,2,SIb,6,
		SI,8,SIL,8,
		DO+12,6,MI+12,4,SOLb+12,4,LA+12,2,
		SOL+12,6,MI+12,4,DO+12,4,LA,2,
		SIL,8,SOLb+12,1,SIL,1,SOLb+12,1,SIL,1,SOLb+12,1,SIL,1,SOL+12,2,
		SIL,2,SOLb,1,SIL,1,SOLb,1,SIL,1,SOLb,1,SIL,1,SOL,2,SIb,6,
		DO+12,1,SIL,1,DO+12,1,SIL,1,DO+12,1,SIL,1,DO+12,6,SIL,4,
0};

const char Tetris[]={LA,2,MI,1,FA,1,SOL,2,FA,1,MI,1,
		RE,1,SIL,1,RE,1,FA,1,LA,2,SOL,1,FA,1,
		MI,1,SIL,1,MI,1,FA,1,SOL,2,LA,2,
		FA,2,RE,1,SIL,1,RE,4,
		SIL,1,SOL,2,SIb,1,
		RE+12,2,DO+12,1,SIb,1,LA,3,FA,1,
		LA,2,SOL,1,FA,1,MI,1,SIL,1,MI,1,FA,1,
		SOL,2,LA,2,FA,2,RE,1,SIL,1,RE,4,
0};

const char nochedepaz[]={ SOL,3,LA,1,SOL,2,MI,6,
						 SOL,3,LA,1,SOL,2,MI,6,
						 RE+12,3,SIL,1,RE+12,2,SI,6,
						 DO+12,3,SIL,1,DO+12,2,SOL,6,
						 LA,3,SIL,1,LA,2,DO+12,3,SI,1,LA,2,
						 SOL,3,LA,1,SOL,2,MI,6,
						 LA,3,SIL,1,LA,2,DO+12,3,SI,1,LA,2,
						 SOL,3,LA,1,SOL,2,MI,6,
						 RE+12,3,SIL,1,RE+12,2,FA+12,3,RE+12,1,SI,2,
						 DO+12,6,MI+12,6,
						 DO+12,3,SOL,1,MI,2,
						 SOL,3,FA,1,RE,2,
						 DO,6,
						 SIL,6,
						 0
};

const char GoT[]={LA,6,RE,6,FA,1,SOL,1,LA,4,RE,4,FA,1,SOL,1,MI,2,
		LA,2,DO+12,1,RE+12,1,MI+12,2,LA,2,DO+12,1,RE+12,1,MI+12,2,LA,2,DO+12,1,RE+12,1,MI+12,2,
		LA,2,DO+12,2,
		SOL,6,DO,6,FA,1,MI,1,SOL,4,DO,6,FA,1,MI,1,RE,2,
		SIb,1,DO+12,1,RE+12,2,LA,2,SIb,1,DO+12,1,RE+12,2,LA,2,
		SIb,1,DO+12,1,RE+12,2,LA,2,SIb,1,DO+12,1,0

};
const Cancion IndianaJones={
		indiana,
		"Indiana Jones",
		1000
};

const Cancion DarthVader={
		darthvader,
		"Marcha Imperial",
		2000
};

const Cancion TheShire={
		hobbit,
		"La Comarca",
		3000
};

const Cancion TheSimpsons={
		Simps,
		"The Simpsons",
		1000
};

const Cancion TetrisTheme={
		Tetris,
		"Tetris Theme",
		1000
};

const Cancion GameOfThrones={
		GoT,
		"Juego de Tronos",
		1800
};

const Cancion NocheDePaz={
		nochedepaz,
		"Noche de Paz",
		2500
};




/* ESCALA para usar en el tercer apartado */

const char ESCALA[]={DO,REb,RE,MIb,MI,FA,SOLb,SOL,LAb,LA,SIb,SI,DO+12};
const char ESCALA1[]={DO,RE,FA,SOL,SIb};//ejemplo de 5 notas para joystick (primera parte little green bag

