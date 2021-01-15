#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NH 4

void *fun_hilo( void *arg );

int contador;
pthread_mutex_t bloqueo;
int main(){
	
	printf("Probando hilos.\n");
	int *hilo;
	int nhs[NH];
	pthread_t tids[NH];
	pthread_mutex_init( &bloqueo, NULL);

	contador = 0;
	register int i;
	for( i = 0; i < NH; i++ ){
		nhs[i] = i;
		pthread_create( &tids[i], NULL, fun_hilo, &nhs[i] );
	}

	for( i = 0; i < NH; i++ ){
		pthread_join( tids[i], (void**)&hilo );
		printf("Hilo %d terminado.\n", *hilo);
	}
	printf("COntador =  %d", contador);
	return 0;
}

void *fun_hilo(void *arg){

	int nh = *(int*)arg;
	register int i = 0;

	pthread_mutex_lock( &bloqueo );

	contador++;
	printf("Hilo %d en ejecucion, contador = %d\n", nh, contador);

	while(--i)

	contador++;
	printf("Hilo %d en ejecucion, contador = %d\n", nh, contador);
	
	pthread_mutex_unlock( &bloqueo );

	pthread_exit(arg);
}
