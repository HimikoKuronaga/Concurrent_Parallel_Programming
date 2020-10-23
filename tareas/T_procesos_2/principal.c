
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "defs.h"
#include "helper.h"
#include "procesos.h"

int main(int argc, char **args){
	printf("\nLos datos originales son:\n");
	srand( getpid() );
	int *datos = reservar_memoria();
	llenar_arreglo( datos );
	imprimir_arreglo( datos );		

	int pipesfd[NPROC][2];
	int estado_pipe;

	printf("\nIniciando procesos.\n");

	pid_t pid;
	register int i;
	for( i = 0; i < NPROC; i++ ){		

		estado_pipe = pipe( pipesfd[i] );
		if( estado_pipe == -1 ){
			perror("Error al crear tuberia.\n");
			exit(EXIT_FAILURE);
		}

		pid = fork();
		if( pid == -1 ){
			perror("Error al crear proceso.\n");
			exit(EXIT_FAILURE);
		}

		if( !pid ){
			proceso_hijo( i, pipesfd[i], datos );
		}
	}
	proceso_padre( pipesfd, datos );
	return 0;
}
