#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "defs.h"
#include "hilos.h"
#include "procesamiento.h"

float *muestras, *ventana, *producto, *resultado;	

void hilo_principal( ){

	int *hilo;
	int nh[NH];
	pthread_t tids[NH];

	register int i;
	for( i = 0; i < NH; i++ ){
		nh[i] = i;
		pthread_create( tids+i, NULL, func_hilo_producto, (void *)&nh[i] );
	}
	
	for( i = 0; i < NH; i++ ){
		pthread_join( tids[i], (void **)&hilo );
		printf("Hilo %d terminado.\n", *hilo);		
	}

	for( i = 0; i < NH; i++ ){
		nh[i] = i;
		pthread_create(tids+i,NULL,func_hilo_autocorrelacion,(void *)&nh[i]);
	}
	
	for( i = 0; i < NH; i++ ){
		pthread_join( tids[i], (void **)&hilo );		
		printf("Hilo %d terminado.\n", *hilo);
	}
}

void *func_hilo_producto( void *arg ){
	int nh = *(int *)arg;
	printf("Hilo %d ejecutando producto.\n", nh);
	register int i;
	for( i = nh; i < MUESTRAS; i+=NH ){
		producto[i] = muestras[i] * ventana[i];	
	}
	
	pthread_exit( arg );
}

void *func_hilo_autocorrelacion( void *arg ){
	int nh = *(int *)arg;
	printf("Hilo %d ejecutando autocorrelacion.\n", nh);
	float suma;
	register int i,j;
	for( i = nh; i < MUESTRAS; i+=NH ){
		suma = 0;
		for( j = i; j < MUESTRAS; j++)
			suma += producto[j]*producto[j-i];

		resultado[i] = suma;
	}

	pthread_exit( arg );
}
