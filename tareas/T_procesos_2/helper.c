#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "helper.h"

int *reservar_memoria(){
	int *memoria;
	memoria = (int *)malloc( sizeof(int)*NDATOS );
	if( memoria == NULL ){
		perror("Error al reservar memoria.\n");
		exit(EXIT_FAILURE);
	}
	return memoria;
}

void llenar_arreglo( int *datos ){
	register int i;
	for( i = 0; i < NDATOS; i++ ){
		datos[i] = rand() % TOPE;
	}
}

void imprimir_arreglo( int *datos ){
	register int i;
	for( i = 0; i < NDATOS; i++ ){
		if( !( i%16 ) )
			printf("\n\t");
		printf("%3d ", datos[i] );
	}
	printf("\n");
}

