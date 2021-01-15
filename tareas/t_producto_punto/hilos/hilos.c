#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

#include "defs.h"
#include "hilos.h"

extern int *x, *y, producto;
extern pthread_t hilos[NH];
extern pthread_mutex_t bloqueo;

void hilo_principal(){
	int *hilo;
	register int i;
	for( i = 0 ; i < NH; i++ ){
		pthread_join( hilos[i], (void **)&hilo );
		printf("Hilo %d terminado.\n",*hilo);
	}
}

void *func_hilo( void *arg ){

	int nh = *(int *)arg;

	printf("Hilo %d en ejecucion...\n", nh);
	int tambloque = ND / NH;
	int ini = nh * tambloque;
	int fin = ini + tambloque;

	int suma = 0;
	register int i;
	for( i = ini; i < fin; i++ )
		suma += x[i] * y[i];

	pthread_mutex_lock( &bloqueo );
	producto += suma;
	pthread_mutex_unlock( &bloqueo );

	pthread_exit( arg );
}
