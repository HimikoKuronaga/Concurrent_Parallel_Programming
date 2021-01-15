#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "defs.h"
#include "procesos.h"
#include "procesamiento.h"
#include "helper.h"

void proceso_padre( int pipesfd[NPROC][2], int *datos ){

	int estado, proceso, resultado;
	pid_t pid;
	
	register int i;
	for( i = 0; i < NPROC; i++ ){
		close( pipesfd[i][1] );
		pid = wait( &estado );
		proceso = estado >> 8;

		if( proceso == 0 ){
			read( pipesfd[proceso][0], datos, NDATOS*sizeof(int) );
			printf("Proceso %d, con pid: %d terminado. Los datos ordenados son:\n", proceso, pid);
			imprimir_arreglo( datos );
			printf("\n");
		}else if( proceso  == 1){		     
			read( pipesfd[proceso][0], &resultado, sizeof(int) );
			printf("Proceso %d, con pid: %d terminado, el promedio es: %d\n", proceso, pid, resultado );
		}else if( proceso == 2){		       
			read( pipesfd[proceso][0], &resultado, sizeof(int) );
			printf("Proceso %d, con pid: %d terminado, la cantidad de pares es: %d\n", proceso, pid, resultado );
		}else if( proceso == 3){
			read( pipesfd[proceso][0], datos, NDATOS*sizeof(int) );
			printf("Proceso %d, con pid: %d terminado. Los datos multiplicados son:\n", proceso, pid);
			imprimir_arreglo( datos );
			printf("\n");
		}
		close(pipesfd[proceso][0]);
	}	
	free(datos);
}

void proceso_hijo( int np, int *pipefd, int *datos ){
	printf("\nProceso hijo: %d ejecutando, con pid: %d\n", np, getpid());
	close(pipefd[0]);
	if( np == 0 ){
		ordenar( datos );
		write( pipefd[1], datos, sizeof(int)*NDATOS );
		free(datos);
	}else if( np == 1 ){
		int prom = promedio( datos );
		write( pipefd[1], &prom, sizeof(int) );
	}else if( np == 2 ){
		int n_pares = pares( datos );
		write( pipefd[1], &n_pares, sizeof(int) );
	}else if( np == 3 ){
		multiplicar( datos );
		write( pipefd[1], datos, sizeof(int)*NDATOS );
		free(datos);
	}
	exit( np );
}
