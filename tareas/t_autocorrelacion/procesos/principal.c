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

	proc_padre();

	escribir_archivo( ventana, "ventana.dat" );
	escribir_archivo( producto, "producto.dat" );
	escribir_archivo( resultado, "resultado.dat" );

	free( muestras );
	free( ventana );
	free( producto );
	free( resultado );
	return 0;
}
