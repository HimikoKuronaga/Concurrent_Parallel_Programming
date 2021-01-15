#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>

#include "defs.h"
#include "helpers.h"
#include "imagen.h"
#include "hilos.h"

unsigned char *imgRGB, *imgGRAY, *imgSeg;
uint32_t width, height;

int main( int argc, char **argv ){
	
	bmpInfoHeader info;
	imgRGB = abrirBMP( argv[1], &info );
	width = info.width;
	height = info.height;

	imgGRAY = reservar_memoria( width, height );
	imgSeg = reservar_memoria( width, height );
	memset( imgSeg, 0, width*height);

	rgbToGray( imgRGB, imgGRAY, width, height );

	pthread_t tids[NH];
	int hilo[NH];
	register int i;
	for( i = 0; i < NH; i++ ){
		hilo[i] = i;
		pthread_create( &tids[i], NULL, sobel, &hilo[i] );
	}

	int *nhilo;
	for( i = 0; i < NH; i++ ){
		pthread_join( tids[i], (void**)&nhilo );
		printf("Hilo %d terminado.\n", *nhilo );
	}

	grayToRgb( imgRGB, imgSeg, width, height );
	guardarBMP( argv[2], &info, imgRGB );
	free( imgRGB );
	free( imgGRAY );
	free( imgSeg );
	return 0;
}
