#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "defs.h"
#include "procesos.h"
#include "procesamiento.h"

float *muestras, *ventana, *producto, *resultado;

void proc_padre( ){	
	int estado, np, ini;
	int tam_bloque = MUESTRAS / NP;
	int pipesfd[NP][2];
	int edo_pipe;
	pid_t pid;

	register int i;
	for( i = 0; i < NP; i++ ){
		edo_pipe = pipe( pipesfd[i] );
		if( edo_pipe == -1){
			perror("Error al crear tuberia.\n");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if( pid == -1 ){
			perror("Error al crear proceso.\n");
			exit(EXIT_FAILURE);
		}

		if( !pid ){
			proc_hijo_producto( i, pipesfd[i] );
		}
	}

	for( i = 0; i < NP; i++ ){
		pid = wait( &estado );
		np = estado >> 8;
		printf("Proceso %d terminado.\n", np);
		ini = np * tam_bloque;
		read( pipesfd[np][0], producto+ini, sizeof(float)*tam_bloque );
	}

	for( i = 0; i < NP; i++ ){
		pid = fork();
		if( pid == -1 ){
			perror("Error al crear proceso.\n");
			exit(EXIT_FAILURE);
		} 
		if( !pid ){
			proc_hijo_autocorrelacion(i, pipesfd[i]);
		}
	}


	for( i = 0; i < NP; i++ ){
		pid = wait( &estado );
		np = estado >> 8;
		printf("Proceso %d terminado.\n", np);
		close( pipesfd[np][1] );
		ini = np * tam_bloque;
		read( pipesfd[np][0], resultado+ini, sizeof(float)*tam_bloque );
		close( pipesfd[np][0] );
	}
}

void proc_hijo_producto( int np, int *pipefd ){
	
	printf("Proceso %d ejecutando producto.\n", np);
	
	close( pipefd[0] );
	int tam_bloque = MUESTRAS / NP;
	int ini = np * tam_bloque;
	int fin = ini + tam_bloque;

	register int i;
	for( i = ini; i < fin; i++ )
		producto[i] = muestras[i] * ventana[i];

	write( pipefd[1], producto+ini, sizeof(float)*tam_bloque );
	close( pipefd[1] );
	exit( np );
}

void proc_hijo_autocorrelacion( int np, int *pipefd ){
	
	printf("Proceso %d ejecutando autocorrelacion.\n", np);
	close( pipefd[0] );
	int tam_bloque = MUESTRAS / NP;
	int ini = np * tam_bloque;
	int fin = ini + tam_bloque;
	float suma;

	register int i, j;
	for( i = ini; i < fin; i++ ){
		suma = 0;
		for( j = ini; j < MUESTRAS; j++ )
			suma += producto[j] * producto[j-i];

		resultado[i] = suma;
	}

	write( pipefd[1], resultado+ini, sizeof(float)*tam_bloque );
	close( pipefd[1] );
	exit( np );
}
