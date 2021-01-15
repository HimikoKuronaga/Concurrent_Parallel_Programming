#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "helpers.h"

unsigned char *reservar_memoria( uint32_t width, uint32_t height ){
	unsigned char *memoria = (unsigned char *)malloc( width * height * sizeof( unsigned char ));
	if(memoria == NULL ){
		perror( "Error al reservar memoria.\n" );
		exit( EXIT_FAILURE );
	}
	return memoria;
}
