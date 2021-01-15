#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "defs.h"
#include "procesos.h"

extern float *pulso, *ventana, *producto;

void proc_padre( int pipesfd[NP][2] ){

	int estado, np;
	int tam_bloque = MUESTRAS / NP;
	int ini;
	
	pid_t pid;
	register int i;
	for( i = 0; i < NP; i++ ){
		pid = wait( &estado );
		np = estado >> 8;
		close( pipesfd[i][1] );
		ini = np * tam_bloque;
		read( pipesfd[np][0], producto+ini, sizeof(int)*tam_bloque );
		close( pipesfd[np][0] );

		printf("Proceso %d con pid %d, terminado.\n", np, pid);
	}
}

void proc_hijo( int np, int *pipefd ){

	printf("Proceso %d, en ejecucion...\n", np);

	int tam_bloque = MUESTRAS / NP;
	int ini = np * tam_bloque;
	int fin =  ini + tam_bloque;

	close( pipefd[0] );
	register int i;
	for( i = ini; i < fin; i++ )
		producto[i] = pulso[i] * ventana[i];

	write( pipefd[1], producto+ini, sizeof(float)*tam_bloque);
	close( pipefd[1]);
	exit( np );
}
