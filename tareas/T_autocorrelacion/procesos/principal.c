#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "defs.h"
#include "helpers.h"
#include "archivos.h"
#include "procesamiento.h"
#include "procesos.h"

float *muestras, *ventana, *producto, *resultado;

int main(){
	muestras = reservar_memoria();
	ventana = reservar_memoria();
	producto = reservar_memoria();
	resultado = reservar_memoria();

	leer_archivo( muestras );
	generar_ventana( ventana );

	int pipesfd[NP][2];
	int edo_pipe;
	pid_t pid;

	register int i;
	for( i = 0; i < NH; i++ ){
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
			proc_hijo( i, pipesfd[i] );
		}
	}
	proc_padre( pipesfd );

	escribir_archivo( ventana, "ventana.dat" );
	escribir_archivo( producto, "producto.dat" );
	escribir_archivo( resultado, "resultado.dat" );

	free( muestras );
	free( ventana );
	free( producto );
	free( resultado );
	return 0;
}
