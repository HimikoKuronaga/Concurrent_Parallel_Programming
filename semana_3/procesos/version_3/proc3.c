#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NPROC 4 

void proceso_padre( int *pipefd );
void proceso_hijo( int *pipefd, int np );

int main(){
	
	pid_t pid;
	register int i;
	int pipefd[2], edo_pipe;

	edo_pipe = pipe( pipefd );
	
	if(edo_pipe == -1 ){
		perror("Error al crear tuberia. \n");
		exit(EXIT_FAILURE);
	}

	for( i = 0; i < NPROC; i++ ){
		pid = fork();

		if( pid == -1 ){
			perror("Error al crear proceso.\n");
			exit(EXIT_FAILURE);
		}

		if(pid == 0)
			proceso_hijo( pipefd, i );
	}

	proceso_padre( pipefd );

	return 0;
}


void proceso_padre( int *pipefd ){

	pid_t pid;
	int estado, np, resultado;	
	
	close( pipefd[1] );

	register int i;
	for( i = 0; i < NPROC; i++ ){
		pid = wait( &estado );
		read( pipefd[0], &resultado, sizeof(int) );
		np = estado >> 8;
	
		if( np == 0){
			printf("Proceso: %d terminado, con pid: %d, la suma es: %d\n", np, pid, resultado);
		}else if( np == 1){
			printf("Proceso: %d terminado, con pid: %d, la resta es: %d\n", np, pid, resultado);
		} else if( np == 2){
			printf("Proceso: %d terminado, con pid: %d, la multiplicacion es: %d\n", np, pid, resultado);
		}else if( np == 3){
			printf("Proceso: %d terminado, con pid: %d, la division es: %d\n", np, pid, resultado);
		}
	}

	close( pipefd[0] );
}

void proceso_hijo( int *pipefd, int np ){
	
	int num1 = 10, num2 = 100;
	int suma, resta, multi, divi;

	close( pipefd[0] );
		
	if( np == 0){
		suma = num1 + num2;
		write( pipefd[1], &suma, sizeof(int));
	}else if( np == 1 ){
		resta = num1  - num2;
		write( pipefd[1], &resta, sizeof(int));

	}else if( np == 2 ){
		multi = num1 * num2;
		write( pipefd[1], &multi, sizeof(int));

	}else if( np == 3 ){
		divi = num2 / num1;
		write( pipefd[1], &divi, sizeof(int));

	}

	exit(np);
}

