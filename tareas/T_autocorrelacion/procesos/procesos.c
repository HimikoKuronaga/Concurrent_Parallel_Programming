#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "defs.h"
#include "procesos.h"
#include "procesamiento.h"

float *muestras, *ventana, *producto, *resultado;
void proc_padre( int pipesfd[NP][2] ){
	int estado;
	int np;
	pid_t pid;

	int tam_bloque = MUESTRAS / NP;
	int ini;

	register int i;
	for( i = 0; i < NP; i++ ){
		pid = wait( &estado );
		np = np >> 8;
		printf("Proceso %d terminado con pid %d.\n", np, pid);
		close( pipesfd[np][1] );
		ini = np * tam_bloque;
		read( pipesfd[np][0], producto+ini, sizeof(int)*tam_bloque );		
		close( pipesfd[np][0] );
	}
}

void proc_hijo( int np, int *pipefd ){
	printf("Proceso %d en ejecucion.\n", np);
	close( pipefd[0] );
	int tam_bloque = MUESTRAS / NP;
	int ini = np * tam_bloque;
	int fin = ini + tam_bloque;

	register int i;
	for( i = ini; i < fin; i++ ){
		producto[i] = muestras[i] * ventana[i];
		write( pipefd[1], resultado+i, sizeof(int)*tam_bloque );
	}

	close( pipefd[1] );
	exit( np );
}
