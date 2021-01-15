#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define NP 4
#define ND 16

void proceso_padre( int pipefd[NP][2] );
void proceso_hijo( int np, int pipefd[] );

int *reservar_memoria();
void generar_datos( int *datos );
void imprimir_datos( int *datos );

int *a, *b, *c;

int main(){
	
	a = reservar_memoria();
	b = reservar_memoria();
	c = reservar_memoria();

	srand( getpid() );
	generar_datos( a );
	generar_datos( b );

	printf("Arreglo a:\n");
	imprimir_datos( a );
	printf("Arreglo b:\n");
	imprimir_datos( b );

	pid_t pid;
	int pipefd[NP][2], edo_pipe;

	printf("Probando procesos...\n");

	register int np;
	for( np = 0; np < NP; np++ )
	{
		edo_pipe = pipe( &pipefd[np][0] );
		if( edo_pipe == -1 )
		{
			perror("Error al crear la tuberia...\n");
			exit(EXIT_FAILURE);
		}

		pid = fork();
		if( pid == -1 )
		{
			perror("Error al crear el proceso...\n");
			exit(EXIT_FAILURE);
		}
		if( !pid )
		{
			proceso_hijo( np, &pipefd[np][0] );
		}
	}
	proceso_padre( pipefd );

	printf("\nArreglo c = a*b:\n");
	imprimir_datos( c );
	free( a );
	free( b );
	free( c );

	return 0;
}

void proceso_padre( int pipefd[NP][2] ){
	
	pid_t pid;
	
	int estado, numproc;
	int nelem = ND/NP;
	int ini;
	
	register int np;
	for( np = 0; np < NP; np++ ){
		pid = wait(&estado);
		numproc = estado >> 8;
	
		close( pipefd[numproc][1] );
		
		ini = numproc*nelem;	
		read( pipefd[numproc][0], c+ini, sizeof(int)*nelem );
		
		printf("Proceso %d terminado, con pid %d.\n", numproc, pid);
		close( pipefd[numproc][0] );
	}
}

void proceso_hijo( int np, int *pipefd ){

	int nelem = ND/NP;
	int ini = np*nelem;
	int fin = ini + nelem;

	close(pipefd[0]);
	register int i;
	for( i = ini; i < fin; i++)
		c[i] = a[i] * b[i];

	write( pipefd[1], c+ini, sizeof(int)*nelem );

	close( pipefd[1] );
	exit( np );
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

	register int i;
	for( i = 0; i < ND; i++){
		datos[i] = rand() % 256;
	}
}

void imprimir_datos(int *datos ){
	register int i;
	for( i = 0; i < ND; i++ ){
		if(!( i%16 ))
			printf("\n\t");
		printf("%3d ", datos[i]);
	}
	printf("\n\n");
}
