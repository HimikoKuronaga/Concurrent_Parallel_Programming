#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NPROC 4

void proceso_padre( int *pipefd );
void proceso_hijo( int np, int *pipefd );


int main(){

	int pipefd[2], edo_pipe;
	pid_t pid;

	edo_pipe = pipe( pipefd );
	if( edo_pipe == -1){
		printf("Error al crear tuberia. \n");
		exit(EXIT_FAILURE);
	}
	
	register int i;
	for( i = 0; i < NPROC; i++ ){

		pid = fork();
		if( pid == -1 ){
			perror("Error al crear proceso. \n");
			exit(EXIT_FAILURE);
		}	

		if( !pid )
			proceso_hijo( i, pipefd );
	}

	proceso_padre( pipefd );

	return 0;
}

void proceso_padre( int *pipefd ){
	
	int resultado, estado, np;
	pid_t pid;

	close( pipefd[1] ); 
	register int i;
	for( i = 0; i < NPROC; i++ ){

		pid = wait( &estado );
		np = estado >> 8;

		if( np == 0){
			read( pipefd[0], &resultado, sizeof(int) );
			printf("Proceso %d con pid: %d, la suma es: %d\n\n", np, pid, resultado);
		}if( np == 1){
			read( pipefd[0], &resultado, sizeof(int) );
			printf("Proceso %d con pid: %d, la resta es: %d\n\n", np, pid, resultado);
		}if( np == 2){
			read( pipefd[0], &resultado, sizeof(int) );
			printf("Proceso %d con pid: %d, la multiplicacion es: %d\n\n", np, pid, resultado);
		}else if( np == 3){
			read( pipefd[0], &resultado, sizeof(int) );
			printf("Proceso %d con pid: %d, la division es: %d\n\n", np, pid, resultado);
		}
	}

	close( pipefd[0] );
}

void proceso_hijo( int np, int *pipefd ){
	int num1 = 20, num2 = 4;
	int suma, resta, multi, divi;

	close( pipefd[0] );
	//printf("Proceso hijo %d ejecutando, con pid: %d\n", np, getpid());
	if( np == 0)
	{
		suma = num1 + num2;
		write( pipefd[1], &suma, sizeof(int) );
	}
	else if( np == 2 )
	{
		resta = num1 - num2;
		write( pipefd[1], &resta, sizeof(int) );
	}
	else if( np == 3)
	{
		multi = num1 * num2;
		write( pipefd[1], &multi, sizeof(int) );
	}
	else if( np == 4)
	{
		divi = num1 / num2;
		write( pipefd[1], &divi, sizeof(int) );
	}
	exit(np);
}
