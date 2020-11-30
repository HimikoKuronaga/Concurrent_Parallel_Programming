#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

float *reservar_memoria(){
	float *memoria = (float *)malloc(sizeof(float)*MUESTRAS);
	if( memoria == NULL){
		perror("Error al reservar memoria.\n");
		exit(EXIT_FAILURE);
	}
}

void imprimir_arreglo( float *datos ){
	register int i;
	for(i = 0; i < MUESTRAS; i++ ){
		if( !( i%16 ))
			printf("\n\t");

		printf("%.3f", datos[i]);
	}
	printf("\n\n");
}
