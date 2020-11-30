#include <math.h>

#include "defs.h"
#include "procesamiento.h"

void generar_ventana( float *ventana ){
	float a0 = 0.5, a1 = 0.5;
	register int i;
	for( i = 0; i < MUESTRAS; i++ ){
		ventana[i] =  a0 - a1 * cosf( 2 * M_PI * i / (MUESTRAS-1) );
	}
}

void generar_seno( float *seno ){
	float f = 1000, fs = 45000;
	register int i;
	for( i = 0; i < MUESTRAS; i++ ){
		seno[i] = sinf( 2 * M_PI * f * i / fs );
	}
}
