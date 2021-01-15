#include "defs.h"
#include "procesamiento.h"

void ordenar( int *datos ){
	register int i, j;
	for( i = 0; i < NDATOS - 1; i++ ){
		for( j = 0; j < NDATOS - i - 1; j++ ){
			if( datos[j] > datos[j+1] ){
				int tmp= datos[j];
				datos[j]= datos[j+1];
				datos[j+1]= tmp;
			}
		}
	}
}

int promedio( int *datos ){
	int suma = 0;
	register int i;
	for( i = 0; i < NDATOS; i++ ){
		suma += datos[i];
	}
	return (suma/NDATOS);
}

int pares( int *datos ){
	int npares = 0;
	register int i;
	for( i = 0; i < NDATOS; i++ ){
		if( !(datos[i]%2) )
			npares++;
	}
	return npares;
}

void multiplicar( int *datos ){
	register int i;
	for( i = 0; i < NDATOS; i++ ){
		datos[i] *= CONST; 
	}
}
