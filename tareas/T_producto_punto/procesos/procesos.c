#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#include "defs.h"
#include "procesos.h"

extern int *x, *y, producto;

void proc_padre( int pipesfd[NP][2] ){
	
	int estado, nproc;
	pid_t pid;
	
	int suma;
	producto = 0;
	register int i;
	for( i = 0; i < NP; i++ ){
		pid = wait( &estado );
		nproc = estado >> 8;
		close( pipesfd[nproc][1] );
		printf("Proceso hijo %d, con pid %d, terminado.\n",nproc, pid);
		read( pipesfd[nproc][0], &suma, sizeof(int) );
		producto += suma;
		close( pipesfd[nproc][0] );
	}
}

void proc_hijo( int np, int *pipefd ){
	
	printf("Proceso hijo %d, en ejecucion...\n", np);
	close( pipefd[0] );
	int suma = 0;
	register int i;
	for( i = np; i < ND; i += NP)
		suma += x[i] * y[i];

	write( pipefd[1], &suma, sizeof(int));
	close( pipefd[1] );
	exit( np );

}
