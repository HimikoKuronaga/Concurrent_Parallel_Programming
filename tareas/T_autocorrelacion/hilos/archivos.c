#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

void leer_archivo( float *datos ){
	FILE *fp = fopen("pulso.dat", "r");

	if( fp == NULL ){
		perror("Error al abrir archivo");
		exit(EXIT_FAILURE);
	}

	register int i;
	for( i = 0; i < MUESTRAS; i++ ){
		fscanf( fp, "%f", datos+i);
		datos[i] -= 2200;
	}

	fclose( fp );
}

void escribir_archivo( float *datos, char *nombre_archivo ){
	FILE *fp = fopen(nombre_archivo, "w");

	if( fp == NULL ){
		perror("Error al abrir archivo");
		exit(EXIT_FAILURE);
	}

	register int i;
	for( i = 0; i < MUESTRAS; i++ ){
		fprintf( fp, "%.3f\n", datos[i]);
	}
	
	fclose(fp);
}
