#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "defs.h"
#include "helpers.h"
#include "archivos.h"
#include "procesamiento.h"
#include "hilos.h"

float *pulso, *ventana, *producto;

int main(){

	printf("\nTarea: version de hilos.\n");
	pulso = reservar_memoria();
	ventana = reservar_memoria();
	producto = reservar_memoria();
	leer_datos( pulso );
	generar_ventana( ventana );
	guardar_datos( ventana, "ventana.dat" );
	
	pthread_t tids[NH];
	int nh[NH];

	register int i;
	for( i = 0; i < NH; i++ ){
			nh[i] = i;
			pthread_create( tids+i, NULL, func_hilo, nh+i );
	}

	hilo_principal( tids );
	guardar_datos( producto, "producto.dat" );

	free( pulso );
	free( ventana );
	free( producto );
	return 0;
}
