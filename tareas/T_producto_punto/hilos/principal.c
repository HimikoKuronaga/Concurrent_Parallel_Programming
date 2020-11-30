#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include "defs.h"
#include "helpers.h"
#include "hilos.h"

int *x, *y, producto;
pthread_mutex_t bloqueo;
pthread_t hilos[NH];

int main(){

	printf("\nTarea: version procesos.\n");
	x = reservar_memoria();
	y = reservar_memoria();
	
//	srand( getpid() );
	generar_datos( x );
	generar_datos( y );

	printf("Arreglo x:\n");
	imprimir_datos( x );
	printf("Arreglo y:\n");
	imprimir_datos( y );

	pthread_mutex_init( &bloqueo, NULL );
	
	int nh[NH];
	register int i;
	for( i = 0; i < NH; i++ ){
		nh[i] = i;
		pthread_create( &hilos[i], NULL, func_hilo, (void *)&nh[i] );
	}

	hilo_principal( );
	printf("\nProducto punto entre x e y: %d\n", producto);

	free( x );
	free( y );
	pthread_mutex_destroy( &bloqueo );
	return 0;
}
