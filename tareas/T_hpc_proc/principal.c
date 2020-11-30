#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "defs.h"
#include "helpers.h"
#include "archivos.h"
#include "procesamiento.h"
#include "procesos.h"

float *pulso, *ventana, *producto;
int main(){

	printf("\nTarea procesos.\n");
	pulso = reservar_memoria();
	ventana = reservar_memoria();
	producto = reservar_memoria();
	leer_datos( pulso );
	generar_ventana( ventana );
	guardar_datos( ventana, "ventana.dat" );

	int pipesfd[NP][2];
	int edo_pipe;
	pid_t pid;
	register int i;
	for( i = 0; i < NP; i++ ){
		edo_pipe = pipe( pipesfd[i] );
		if( edo_pipe == -1){
			perror("Error al crear tuberias.\n");
			exit(EXIT_FAILURE);
		}

		pid = fork();
		if( pid == -1 ){
			perror("Error al crear proceso.\n");
			exit(EXIT_FAILURE);
		}
		if( !pid ){
			proc_hijo( i, pipesfd[i] );
		}
	}
	proc_padre( pipesfd );
	guardar_datos( producto, "producto.dat" );

	free( pulso );
	free( ventana );
	free( producto );

	return 0;
}
