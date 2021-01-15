
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NH 4

void *fun_hilo( void *arg );

int contador;
pthread_mutex_t bloqueo;
int main(){
	
	int nhs[NH];

	pthread_t tids[NH];
	pthread_mutex_init( &bloqueo, NULL);

	contador = 0;
	register int i;
	for( i = 0; i < NH; i++ ){
		nhs[i] = i;
		pthread_create( &tids[i], NULL, fun_hilo, (void *)&nhs[i] );
	}

	int *hilo;
	for( i = 0; i < NH; i++ ){
		pthread_join( tids[i], (void**)&hilo );
		printf("Hilo %d terminado.\n", *hilo);
		free(hilo);
	}
	
	pthread_mutex_destroy( &bloqueo );
	return 0;
}

void *fun_hilo(void *arg){

	int nh = *(int*)arg;
	register int i;

	pthread_mutex_lock( &bloqueo );

	contador++;
	printf("Hilo %d en ejecucion, contador = %d\n", nh, contador);

	i = 0;
	while(--i)

	contador++;
	printf("Hilo %d en ejecucion, contador = %d\n", nh, contador);

	pthread_mutex_unlock( &bloqueo );

	pthread_exit(arg);
}
