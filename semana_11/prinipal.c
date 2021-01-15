#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "imagen.h"
#include "helpers.h"

void rgbToGray( unsigned char *imgRGB, unsigned char *imgGRAY ,uint32_t width, uint32_t height );
void grayToRgb( unsigned char *imgGRAY, unsigned char *imgRGB, uint32_t width, uint32_t height );
void filtroPB( unsigned char *img, unsigned char *imgFiltrada, uint32_t width, uint32_t height );

int main( int argc, char **args ){

	if( argc < 3){
		perror("Especifica los nombres de archivo de entrada y salida.\n");	
		exit(EXIT_FAILURE);
	}

	bmpInfoHeader info;
	unsigned char *imgRGB = abrirBMP( args[1], &info );
	unsigned char *imgGRAY = reservar_memoria( info.width, info.height );
	unsigned char *imgFiltrada = reservar_memoria( info.width, info.height );

	memset( imgFiltrada, 0, info.width*info.height );

	rgbToGray( imgRGB, imgGRAY, info.width, info.height );
	filtroPB( imgGRAY, imgFiltrada, info.width, info.height );
	grayToRgb( imgFiltrada, imgRGB, info.width, info.height );

	guardarBMP( args[2], &info, imgRGB );

	free( imgRGB );
	free( imgGRAY );
	free( imgFiltrada );
	return 0;
}


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

void filtroPB( unsigned char *img, unsigned char *imgFiltrada, uint32_t width, uint32_t height ){
	
	int mascara[DIMASK*DIMASK] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	int indicei, indicem;
	int conv = 0;
	
	register int y, x, ym, xm;
	for( y = 0; y < height-DIMASK; y++ ){
		for( x = 0; x < width-DIMASK; x++ ){
			conv = 0;
			indicem = 0;
			for( ym= 0; ym < DIMASK; ym++ ){
				for( xm = 0; xm < DIMASK; xm++ ){
					indicei = (y + ym) * width + ( x + xm);
					conv += img[indicei] * mascara[indicem++];	
				}
			}
			conv /= 9;
			indicei = (y+1)*width + (x+1);
			imgFiltrada[indicei] = conv;
		} 
	} 
}
