#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NH 4
#define ND 16

int *reservar_memoria();
void generar_datos( int *datos );
void imprimir_datos( int *datos );
void *fun_hilo(void *arg);

int *a,*b,*c;

int main(){

}

int *reservar_memoria(){
	int *memoria = (int *)malloc(sizeof(int)*ND);
	if( memoria == NULL){
		perror("Error al reservar memoria");
		exit(EXIT_FAILURE);
	}
	return memoria;
}

void generar_datos( int *datos ){
	srand( getpid() );
	register int i;
	for( i = 0; i < ND; i++){
		datos[i] = rand() % 256;
	}
}

void imprimir_datos(int *datos ){
	register int i;
	for( i = 0; i < n; i++ ){
		if(!( i%16 ))
			printf("\n\t");
		printf("%3d ", datos[i]);
	}
	printf("\n\n");
}
