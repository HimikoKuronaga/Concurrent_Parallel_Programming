#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "defs.h"
#include "helpers.h"
#include "hilos.h"

float *muestras, *ventana, *producto, *resultado;

int main(){
	muestras = reservar_memoria();
	ventana = reservar_memoria();
	producto = reservar_memoria();
	resultado = reservar_memoria();

	leer_archivo( muestras );
	generar_ventana( ventana );

	int nh[NH];
	pthread_t tids[NH];

	register int i;
	for( i = 0; i < NH; i++ ){
		nh[i] = i;
		pthread_create( tids+i, NULL, func_hilo, (void *)&nh[i] );
	}
	hilo_principal( tids );

	escribir_archivo( ventana, "ventana.dat" );
	escribir_archivo( producto, "producto.dat" );
	escribir_archivo( resultado, "resultado.dat" );

	free( muestras );
	free( ventana );
	free( producto );
	free( resultado );
	return 0;
}
