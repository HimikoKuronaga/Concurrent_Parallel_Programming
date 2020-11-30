#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "defs.h"
#include "hilos.h"
#include "procesamiento.h"

float *muestras, *ventana, *producto, *resultado;	
void hilo_principal( pthread_t *tids ){
	int *hilo;
	register int i;
	for( i = 0; i < NH; i++ ){
		pthread_join( tids[i], (void **)&hilo );		
	}
}

void *func_hilo( void *arg ){
	int nh = *(int *)arg;
	
	register int i;
	for( i = nh; i < MUESTRAS; i+=NH ){
		producto[i] = muestras[i] * ventana[i];	
	}

	pthread_exit( arg );
}
