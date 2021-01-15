#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#include "defs.h"
#include "hilos.h"

extern unsigned char *imgGRAY, *imgFiltrada;
extern uint32_t width, height;

void *filtroGausiano( void *arg ){
	int nhilo = *(int *)arg;
	printf( "Hilo %d en ejecucion.\n", nhilo );

	int mascara[DIMASK*DIMASK] = {
		1, 4, 7, 4, 1,
		4, 20, 33, 20, 4,
		7, 33, 54, 33, 7,	
		4, 20, 33, 20, 4,
		1, 4, 7, 4, 1
	};

	int factor = 330;
	int tamBloque = height / NH;
	int iniBloque = nhilo * tamBloque;
	int finBloque = nhilo == NH-1? height-DIMASK: iniBloque + tamBloque;

	int indicei, indicem, conv;
	register int y, x, ym, xm;
	for( y = iniBloque; y < finBloque; y++ ){
		for( x = 0; x < width-DIMASK; x++ ){
			indicem = 0;
			conv = 0;
			for( ym = 0; ym < DIMASK; ym++ ){
				for( xm = 0; xm < DIMASK; xm++ ){
					indicei = (y+ym)*width + (x+xm);
					conv += imgGRAY[indicei] * mascara[indicem++];
				}
			}

			conv /= factor;
			indicei = (y+2)*width + (x+2);
			imgFiltrada[indicei] = conv;
		}
	}

	pthread_exit( arg );
}
