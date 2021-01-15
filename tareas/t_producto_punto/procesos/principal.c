#include <stdio.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#include "defs.h"
#include "helpers.h"
#include "procesos.h"

int *x, *y, producto;

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
	
	int pipesfd[NP][2];
	int edopipe;
	pid_t pid;

	register int i;
	for( i = 0; i < NP; i++ ){
		edopipe = pipe( pipesfd[i] );
		if( edopipe == -1 ){
			perror("Error al crear tuberias.\n");
			exit(EXIT_FAILURE);
		}

		pid = fork();
		if( pid == -1 ){
			perror("Error al crear la tuberia.\n");
			exit(EXIT_FAILURE);
		}

		if(!pid){
			proc_hijo( i, pipesfd[i] );
		}
	}

	proc_padre( pipesfd );
	printf("\nEl producto punto entre x e y es: %d\n", producto);

	free( x );
	free( y );
	return 0;
}
