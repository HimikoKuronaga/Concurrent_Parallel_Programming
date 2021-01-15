#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NPROC 2
#define NDATOS 32

/*FUNCIONES PADRE E HIJOS*/
void proceso_padre();
void proceso_hijo( int np, int *datos );

/*FUNCIONES PARA CREAR ARREGLO DE DATOS*/
int *reservarMemoria();
void llenarArreglo( int *datos );
void imprimirArreglo( int *datos );

/*FUNCIONES PARA MANIPULAR ARREGLO*/
int encontrar_mayor( int *datos );
int encontrar_menor( int *datos );


int main(){
	
	pid_t pid;
	int *datos = reservarMemoria();
	llenarArreglo( datos );
	imprimirArreglo( datos );

	register int i;
	for( i = 0; i < NPROC; i++){
		pid = fork();
		if(pid == -1){
			perror("Error al crear proceso.\n");
			exit(EXIT_FAILURE);
		}

		if(!pid){
			proceso_hijo( i, datos );
		}
	}

	proceso_padre();
	return 0;
}


int *reservarMemoria(){
	int *memoria;
	memoria = (int *)malloc(sizeof(int)*NDATOS);
	if(!memoria){
		perror("Error al reservar memoria. \n");
		exit(EXIT_FAILURE);
	}
	return memoria;
}

void llenarArreglo( int *datos ){
	register int i;
	srand();
	for( i = 0; i < NDATOS; i++){
		datos[i] = rand()%256;
	}
}

void imprimirArreglo( int *datos ){
	register int i;
	for( i = 0; i < NDATOS; i++){
		if(!i%16)
			printf("\n");

		printf("%3d ", datos[i]);
	}
}

int encontrar_mayor(int *datos){

	int mayor = datos[0];

	register int i;
	for( i = 0; i < NDATOS; i++){
		if(datos[i] > mayor)
			mayor = datos[i];
	}

	return mayor;
}

int encontrar_menor(int *datos){
	int menor = datos[0];

	register int i;
	for( i = 0; i < NDATOS; i++){
		if(datos[i] < menor)
			menor = datos[i];
	}

	return menor;

}

void proceso_hijo( int np, int *datos ){
	
	printf("\n\nProceso hijo %d ejecutado con pid: %d\n\n", np, getpid());
	int mayor, menor;
	if(np == 0){
		mayor = encontrar_mayor(datos);
		exit(mayor);
	}else if( np == 1){
		menor = encontrar_menor(datos);
		exit(menor);
	}

	exit(np);
}

void proceso_padre(){
	int estado;
	pid_t pid;

	register int i;
	for( i = 0; i < NPROC; i++ ){
		pid = wait(&estado);
		printf("\n\nProceso: %d, terminado con:  %d\n\n", pid, estado>>8);
	}
}


