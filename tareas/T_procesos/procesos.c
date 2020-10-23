
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "defs.h"
#include "procesos.h"
#include "procesamiento.h"

void proceso_padre(){

	pid_t pid;
	int estado;

	register int i;
	for( i = 0; i < NPROC; i++){
		pid = wait(&estado);
		printf("Proceso con pid: %d terminado, resultado: %d\n", pid, estado>>8);
	}
}

void proceso_hijo( int np, int *datos ){
	
	printf("\nProceso %d ejecutando...con pid: %d\n", np, getpid());
	int mayor, menor, n_pares, prom;

	if( np == 0 ){
		mayor = encontrar_mayor( datos );
		exit(mayor);
	}else if( np == 1 ){
		menor = encontrar_menor( datos );
		exit(menor);
	}else if( np == 2){
		prom = promedio( datos );
		exit(prom);
	}else if( np == 3){
		n_pares = numero_pares( datos );
		exit(n_pares);
	}

	exit(0);
}
