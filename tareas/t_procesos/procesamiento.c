#include "defs.h"
#include "procesamiento.h"

int encontrar_mayor( int *datos ){
	int mayor = datos[0];

	register int i;
	for( i = 0; i < NDATOS; i++){
		if( datos[i] > mayor )
			mayor = datos[i];
	}
	return mayor;
}

int encontrar_menor( int *datos ){
	int menor = datos[0];

	register int i;
	for( i = 0; i < NDATOS; i++){
		if( datos[i] < menor )
			menor = datos[i];
	}	
	return menor;
}

int promedio( int *datos ){
	int suma = 0;

	register int i;
	for( i = 0; i < NDATOS; i++){
		suma += datos[i];
	}
	return (suma/NDATOS);
}

int numero_pares( int *datos ){
	int contador = 0;
	register int i;

	for( i = 0; i < NDATOS; i++){
		if( !( datos[i] % 2) )
			++contador;
	}
	return contador;
}
