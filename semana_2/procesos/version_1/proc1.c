#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	
	float num1 = 45, num2 = 13, suma, resta;
	pid_t pid;
	int estado;
	printf("Probando procesos\n");
	
	pid = fork();
	/*A partir de este punto se crea el proceso hijo y desde aqui se ejecuta el codigo del proceso hijo*/
	if(pid == -1){
		perror("Error al crear proceso...\n");
		exit(EXIT_FAILURE);
	}

	/*SI pid == 0 se esta ejecutando el proceso hijo*/
	if(!pid){
		printf("Proceso hijo ejecutando con pid: %d\n", getpid());
		suma = num1 + num2;
		printf("La suma es: %f\n", suma);
		exit(0);
	}else{
		/*Si no, se encuentra en el proceso padre*/
		printf("Proceso padre con pid: %d\n", getpid());
		resta = num1 - num2;
		printf("La resta es: %f \n",resta );
		pid = wait( &estado );
		printf("Proceso terminado con pid: %d y estado: %d\n", pid, estado);
	}
	return 0;
}
