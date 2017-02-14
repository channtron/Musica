/*
 * partituras.h
 *
 *  Created on: 14/01/2014
 *      Author: Manolo
 */

#ifndef PRACTICA11_1516_3_PARTITURAS_H_
#define PRACTICA11_1516_3_PARTITURAS_H_

/*
#define 	DO	30578
#define 	REb	28862
#define		RE	27240
#define		MIb	25714
#define		MI	24270
#define		FA	22908
#define		SOLb	21622
#define		SOL	20408
#define		LAb	19264
#define		LA	18182
#define		SIb	17168
#define		SI	16202
#define 	SIL 1
*/
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


extern const unsigned int Nota[];
extern const char * Notas_N[];

extern const char COPLITA1[];
extern const char COPLITA2[];
extern const char COPLITA3[];
extern const char indiana[];
extern const char darthvader[];
extern const char hobbit[];
extern const char Simps[];
extern const char Tetris[];
extern const char ESCALA[];
extern const char nochedepaz[];



typedef  struct Cancion{
	const char *notas;		// Vector de notas y duraciones
	char *nombre;			// Nombre de la cancion
	unsigned int tempo;		// tempo recomendado
}Cancion;

extern const Cancion IndianaJones;
extern const Cancion DarthVader;
extern const Cancion TheShire;
extern const Cancion TheSimpsons;
extern const Cancion TetrisTheme;
extern const Cancion GameOfThrones;





#endif /* PRACTICA11_1516_3_PARTITURAS_H_ */
