#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <pthread.h>

#include "defs.h"
#include "hilos.h"

extern unsigned char *imgGRAY, *imgSeg;
extern uint32_t width, height;

void *sobel( void *arg ){
	int nhilo = *(int *)arg;
	printf( "Hilo %d en ejecucion.\n", nhilo );

	int tamBloque = height / NH;
	int iniBloque = nhilo * tamBloque;
	int finBloque = nhilo == NH-1? height-DIMASK: iniBloque + tamBloque;

	int kernelFila[] = { 1, 0, -1, 2, 0, -2, 1, 0, -1 };
	int kernelColumna[] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

	int indicei, indicem, convFila, convCol;
	register int y, x, ym, xm;
	for( y = iniBloque; y < finBloque; y++ ){
		for( x = 0; x < width-DIMASK; x++ ){
			indicem = 0;
			convFila = 0;
			convCol = 0;
			for( ym = 0; ym < DIMASK; ym++ ){
				for( xm = 0; xm < DIMASK; xm++ ){
					indicei = (y+ym)*width + (x+xm);
					convFila += imgGRAY[indicei] * kernelFila[indicem];
					convCol += imgGRAY[indicei] * kernelColumna[indicem++];
				}
			}

			convFila = convFila >> 2;
			convCol = convCol >> 2;
			indicei = (y+1)*width + (x+1);
			imgSeg[indicei] =  (unsigned char)sqrt( convFila * convFila + convCol*convCol );
		}
	}

	pthread_exit( arg );
}
