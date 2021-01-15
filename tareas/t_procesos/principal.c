
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "defs.h"
#include "helpers.h"
#include "procesos.h"


int main( int argc, char **args ){
	pid_t pid;

	srand( getpid() );
	int *datos = reservar_memoria();
	generar_datos( datos );
	imprimir_datos( datos );

	printf("\nProbando procesos.\n");
	register int i;
	for( i = 0; i < NPROC; i++ ){
		pid = fork();
		if(pid == -1){
			perror("Error al crear proceso. \n");
			exit(EXIT_FAILURE);
		}

		if(!pid){
			proceso_hijo( i, datos );
		}
	}
	proceso_padre();
	free( datos );

	return 0;
}
