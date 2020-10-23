#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NPROC 4 

void proceso_padre( int pipefd[NPROC][2] );
void proceso_hijo( int *pipefd, int np );

int main(){
	
	pid_t pid;
	register int i;
	int pipefd[NPROC][2], edo_pipe;

	for( i = 0; i < NPROC; i++ ){

		edo_pipe = pipe( pipefd[i] );
		if(edo_pipe == -1 ){
			perror("Error al crear tuberia. \n");
			exit(EXIT_FAILURE);
		}
	
		pid = fork();

		if( pid == -1 ){
			perror("Error al crear proceso.\n");
			exit(EXIT_FAILURE);
		}

		if(pid == 0)
			proceso_hijo( pipefd[i], i );
	}

	proceso_padre( pipefd );

	return 0;
}



void proceso_padre( int pipefd[NPROC][2] ){

	pid_t pid;
	int estado, np, resultado;	
	
	register int i;
	for( i = 0; i < NPROC; i++ ){
	
		close( pipefd[i][1] );
	
		pid = wait( &estado );
		np = estado >> 8;
		read( pipefd[np][0], &resultado, sizeof(int) );
	
		if( np == 0){
			printf("Proceso: %d terminado, con pid: %d, la suma es: %d\n", np, pid, resultado);
		}else if( np == 1){
			printf("Proceso: %d terminado, con pid: %d, la resta es: %d\n", np, pid, resultado);
		} else if( np == 2){
			printf("Proceso: %d terminado, con pid: %d, la multiplicacion es: %d\n", np, pid, resultado);
		}else if( np == 3){
			printf("Proceso: %d terminado, con pid: %d, la division es: %d\n", np, pid, resultado);
		}
		
		close( pipefd[np][0] );
	}
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

