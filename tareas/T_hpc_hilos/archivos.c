
#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "archivos.h"

void leer_datos( float *datos ){
	FILE *fp = fopen("pulso.dat", "r");

	if( fp == NULL){
		perror("Error al escribir archivo.\n");
		exit(EXIT_FAILURE);
	}
	
	register int i;
	for( i = 0; i < MUESTRAS; i++ ){
		fscanf(fp, "%f ", datos+i);		
		datos[i] -= 2200;
	}
	fclose(fp);
}

void guardar_datos( float *datos, char *nombre ){
	FILE *fp = fopen(nombre, "w");

	if( fp == NULL){
		perror("Error al escribir archivo.\n");
		exit(EXIT_FAILURE);
	}

	register int i;
	for( i = 0; i < MUESTRAS; i++){
		fprintf( fp, "%f \n", datos[i] );
	}

	fclose( fp );
}
