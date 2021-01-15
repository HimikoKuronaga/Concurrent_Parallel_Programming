#include <stdio.h>
#include <stdlib.h>
#include "imagen.h"
#include "helpers.h"

void rgbToGray( unsigned char *imgRGB, unsigned char *imgGRAY ,uint32_t width, uint32_t height );
void grayToRgb( unsigned char *imgGRAY, unsigned char *imgRGB, uint32_t width, uint32_t height );

int main( int argc, char **args ){

	if( argc < 3){
		perror("Especifica los nombres de archivo de entrada y salida.\n");	
		exit(EXIT_FAILURE);
	}

	bmpInfoHeader info;
	unsigned char *imgRGB = abrirBMP( args[1], &info );
	unsigned char *imgGRAY = reservar_memoria( info.width, info.height );

	rgbToGray( imgRGB, imgGRAY, info.width, info.height );
	grayToRgb( imgGRAY, imgRGB, info.width, info.height );
	guardarBMP( args[2], &info, imgRGB );

	free( imgRGB );
	free( imgGRAY );
	return 0;
}

/*
	METODO 1.

void rgbToGray( unsigned char *imgRGB, unsigned char *imgGRAY ,uint32_t width, uint32_t height ){

	unsigned char nivel;
	int indiceRGB, indiceGRAY;

	register int i, j;
	for( j = 0; j < height; j++  ){
		for( i = 0; i < width; i++ ){
			indiceGRAY = j*width + i; 
			indiceRGB =  indiceGRAY * 3;
			nivel = ( imgRGB[indiceRGB] + imgRGB[indiceRGB + 1] + imgRGB[indiceRGB + 2] ) / 3;
			imgGRAY[indiceGRAY] = nivel;	
		}
	}
}
*/

/*
   METODO 2.
void rgbToGray( unsigned char *imgRGB, unsigned char *imgGRAY ,uint32_t width, uint32_t height ){

	unsigned char nivel;
	int indiceRGB, indiceGRAY;

	register int i, j;
	for( j = 0; j < height; j++  ){
		for( i = 0; i < width; i++ ){
			indiceGRAY = j*width + i; 
			indiceRGB =  indiceGRAY * 3;
			nivel = ( 30*imgRGB[indiceRGB] + 59*imgRGB[indiceRGB + 1] +11*imgRGB[indiceRGB + 2] ) / 100;
			imgGRAY[indiceGRAY] = nivel;	
		}
	}
}
*/

/*METODO 2 VERSION 2*/
void rgbToGray( unsigned char *imgRGB, unsigned char *imgGRAY ,uint32_t width, uint32_t height ){
	unsigned char nivel;
	register int indiceRGB, indiceGRAY;
	for( indiceRGB = 0, indiceGRAY = 0; indiceGRAY < width*height; indiceGRAY++, indiceRGB+=3  ){
		nivel = ( 30*imgRGB[indiceRGB] + 59*imgRGB[indiceRGB + 1] +11*imgRGB[indiceRGB + 2] ) / 100;
		imgGRAY[indiceGRAY] = nivel;	
	}
}

void grayToRgb( unsigned char *imgGRAY, unsigned char *imgRGB, uint32_t width, uint32_t height ){
	register int indiceRGB, indiceGRAY;
	for( indiceRGB = 0, indiceGRAY = 0; indiceGRAY < width*height; indiceGRAY++, indiceRGB+=3  ){
		imgRGB[indiceRGB] = imgGRAY[indiceGRAY];	
		imgRGB[indiceRGB + 1] = imgGRAY[indiceGRAY];	
		imgRGB[indiceRGB + 2] = imgGRAY[indiceGRAY];	
	}
}

/*
void grayToRgb( unsigned char *imgGRAY, unsigned char *imgRGB, uint32_t width, uint32_t height ){

	int indiceRGB, indiceGRAY;
	register int i, j;
	for( j = 0; j < height; j++  ){
		for( i = 0; i < width; i++ ){
			indiceGRAY = j*width + i; 
			indiceRGB =  indiceGRAY * 3;

			imgRGB[indiceRGB] = imgGRAY[indiceGRAY];	
			imgRGB[indiceRGB + 1] = imgGRAY[indiceGRAY];	
			imgRGB[indiceRGB + 2] = imgGRAY[indiceGRAY];	
		}
	}
}
*/
