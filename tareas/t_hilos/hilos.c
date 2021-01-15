#include <stdio.h>
#include <pthread.h>

#include "hilos.h"
#include "procesamiento.h"

extern int *datos;
extern int prom, num_pares, num_primos;
extern pthread_mutex_t bloqueo;

void *fun_hilo( void *arg ){

	int nh = *(int *)arg;
	printf("Hilo %d, ejecutandose...\n", nh);		
	
	pthread_mutex_lock( &bloqueo );
	
	if( nh == 0 ){
		ordenar( datos );
	}else if( nh == 1 ){
		prom = promedio( datos );
	}else if( nh == 2 ){
		num_pares = n_pares( datos );
	}else if( nh == 3 ){	
		num_primos = n_primos( datos );
	}

	pthread_mutex_unlock( &bloqueo );

	pthread_exit( arg );
}
