#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#include "defs.h"
#include "hilos.h"
#include "helpers.h"

int prom, num_pares, num_primos;
int *datos;
pthread_mutex_t bloqueo;

int main(){
	
	printf("Tarea hilos.\nLos datos originales son.\n");
	srand( getpid() );
	datos = reservar_memoria();
	generar_datos ( datos );
	imprimir_datos( datos );

	pthread_mutex_init( &bloqueo, NULL );
	pthread_t ids[NH];
	int nhilo[NH];
	
	register int i;
	for( i = 0; i < NH; i++ ){
		nhilo[i] = i;
		pthread_create( &ids[i], NULL, fun_hilo, &nhilo[i] );
	}
	
	int *hilo;
	for( i = 0; i < NH; i++ ){
		pthread_join( ids[i], (void **)&hilo );
		printf("\nHilo %d, concluido.\n", *hilo);
		if( *hilo == 0){
			printf("Los datos ordenados: \n");
			imprimir_datos( datos );
		}else if( *hilo == 1 ){
			printf( "El promedio es: %d\n", prom );
		}else if( *hilo == 2 ){
			printf( "La cantidad de pares es: %d\n", num_pares );
		}else if( *hilo == 3 ){		
			printf( "La cantidad de primos es: %d\n", num_primos );
		}
	}
	free( datos );
	pthread_mutex_destroy( &bloqueo );
	return 0;
}

