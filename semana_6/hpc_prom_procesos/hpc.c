#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NP 4 
#define ND 16

void proceso_padre( int pipesfd[NP][2] );
void proceso_hijo( int np, int *pipefd );
int *reservar_memoria();
void generar_datos();
void imprimir_datos();


int *a, promedio;

int main(){

	printf("Promedio de datos con procesos.\nDatos:\n");

	a = reservar_memoria();
	generar_datos( a );
	imprimir_datos( a );
	promedio = 0;

	int pipesfd[NP][2];
	int edo_pipe;
	pid_t pid;
	register int i;
	for( i = 0; i < NP; i++ ){
		edo_pipe = pipe( pipesfd[i] );
		if( edo_pipe < 0 ){
			perror("Error al crear tuberia.\n");
			exit(EXIT_FAILURE);
		}

		pid = fork();
		if( pid < 0 ){
			perror("Error al crear proceso.\n");
			exit(EXIT_FAILURE);
		}

		if( !pid ){
			proceso_hijo( i, pipesfd[i] );
		}
	}
	proceso_padre( pipesfd );
	printf("EL promedio de los datos es: %d\n", promedio);

	return 0;
}

void proceso_padre( int pipesfd[NP][2] ){
	int suma_parcial = 0;
	int estado, np;
	pid_t pid;
	register int i;
	for( i = 0; i < NP; i++ ){
		pid = wait( &estado );
		np = estado >> 8;
		printf("Proceso %d terminado.\n", np);
		close( pipesfd[np][1] );
		read( pipesfd[np][0], &suma_parcial, sizeof(int) );
		promedio += suma_parcial;
	}
	promedio = promedio >> 4;
}

void proceso_hijo( int np, int *pipefd ){

	printf("Proceso %d en ejecucion.\n", np);
	int suma = 0;
	close( pipefd[0] );

	register int i;
	for( i = np; i < ND; i+= NP )
		suma+=a[i];

	write( pipefd[1], &suma, sizeof( int ));
	close( pipefd[1] );
	exit( np );
}

int *reservar_memoria(){
	int *memoria = (int*)malloc(sizeof(int)*ND);
	if(memoria == NULL){
		perror("Error al reservar memoria.\n");
		exit(EXIT_FAILURE);
	}
	return memoria;
}

void generar_datos( int *datos ){
	register int i;
	for( i = 0; i < ND; i++ ){
		datos[i] = rand() % 256;
	}
}

void imprimir_datos( int *datos ){
	register int i;
	for( i = 0; i < ND; i++ ){
		if( !( i%16 ))
			printf("\n\t");
		printf("%3d ", datos[i]);
	}
	printf("\n\n");
}

