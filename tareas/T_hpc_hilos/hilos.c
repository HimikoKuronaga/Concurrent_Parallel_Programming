#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "defs.h"
#include "hilos.h"

extern float *pulso, *ventana, *producto;

void hilo_principal( pthread_t *tids ){

	int *nh;
	register int i;
	for( i = 0; i < NH; i++ ){	
		pthread_join( tids[i], (void**)&nh );
		printf("Hilo %d terminado.\n", *nh);
	}
}

void *func_hilo( void *arg ){
	int nh = *(int *)arg;

	printf("Hilo %d, en ejecucion.\n", nh);
		
	register int i;
	for( i = nh; i < MUESTRAS; i += NH )
		producto[i] = pulso[i] * ventana[i];	

	pthread_exit( arg );
}
