/** @brief archivos.c, este programa
 * 	guarda un arreglo de datos en el archivo.
 * */

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

void guarda_datos( float *datos ){
	
	FILE *fp = fopen("seno.dat", "w");
	
	if(fp == NULL){
		perror("Error al abrir archivo.\n");
		exit(EXIT_FAILURE);
	}

	register int n;
	for(n = 0; n < MUESTRAS; n++){
		fprintf(fp, "%f \n", datos[n]);
	}

	fclose(fp);
}
