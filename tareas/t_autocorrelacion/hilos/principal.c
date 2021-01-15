#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "helpers.h"
#include "procesamiento.h"
#include "hilos.h"
#include "archivos.h"

float *muestras, *ventana, *producto, *resultado;

int main(){
	muestras = reservar_memoria();
	ventana = reservar_memoria();
	producto = reservar_memoria();
	resultado = reservar_memoria();

	leer_archivo( muestras );
	generar_ventana( ventana );

	hilo_principal( );

	escribir_archivo( ventana, "ventana.dat" );
	escribir_archivo( producto, "producto.dat" );
	escribir_archivo( resultado, "resultado.dat" );

	free( muestras );
	free( ventana );
	free( producto );
	free( resultado );
	return 0;
}
