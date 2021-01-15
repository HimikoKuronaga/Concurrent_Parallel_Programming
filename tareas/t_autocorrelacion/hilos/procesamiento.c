#include <math.h>

#include "defs.h"
#include "procesamiento.h"

void generar_ventana( float *datos ){
	
	float a = 0.5, b = 0.5;

	register int i;
	for ( i = 0; i < MUESTRAS; i++ ){
		datos[i] = a - (b*cosf( 2*M_PI*i/( MUESTRAS-1 )));
	}
}

void autocorrelacion( float *datos ){

}
