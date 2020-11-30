#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int promedio;

int main(){

}

int *reservar_memoria(){

}

void generar_datos( int *datos ){
	register int i;
	for( i = 0; i < ND; i++ ){
		datos[i] = rand() % 256;
	}
}

void imprimir_datos( int *datos ){

}
