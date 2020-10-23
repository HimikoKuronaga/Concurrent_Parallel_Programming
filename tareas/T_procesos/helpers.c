

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defs.h"
#include "helpers.h"


int *reservar_memoria(){
	int *memoria = (int*) malloc(sizeof(int)*NDATOS);
	if(memoria == NULL){
		perror("Error al reservar memoria.\n");
		exit(EXIT_FAILURE);
	}
	return memoria;
}

void generar_datos( int *datos ){
	register int i;
	for( i = 0; i < NDATOS; i++){
		datos[i] = rand() % 256;
	}
}

void imprimir_datos( int *datos ){
	register int i;
	for( i = 0; i < NDATOS; i++){
		if( !( i % 16 ))
			printf("\n");

		printf( "%3d ", datos[i] );
	}
	printf("\n");
}
