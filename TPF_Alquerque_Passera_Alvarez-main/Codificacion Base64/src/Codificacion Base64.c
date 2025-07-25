/*
 ============================================================================
 Name        : Codificacion.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <string.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0

void crearBase64(char*base64){
	char charACargar,i;
	for(i = 0,charACargar = 'A'; i<'Z'-'A';i++,charACargar++)
		base64[i] = charACargar;

	for(charACargar = 'a'; i<'z' - 'a'; i++,charACargar++)
		base64[i] = charACargar;
	for(charACargar = '0'; i<'9' - '0'; i++,charACargar++)
			base64[i] = charACargar;
	base64[i++] = '+';
	base64[i] = '/';
}


char* codificarBase64(char* entrada){



	int lenEntrada = strlen(entrada);

	char* respuesta;
	size_t lenRespuesta = 1;
	respuesta = malloc(lenRespuesta);

	int iRespuesta = 0;
	int iEntrada = 0;
	char auxChar[3], resultadoACargar[4],iACargar[4];
	while(TRUE)
	{
		lenEntrada -=3;
		if(lenEntrada>=0){
			auxChar[0] = entrada[iEntrada++];
			auxChar[1] = entrada[iEntrada++];
			auxChar[2] = entrada[iEntrada++];

			iACargar[0] = auxChar[0]>>2;
			iACargar[1] = ((auxChar[0]<<4)&0x30)|((auxChar[1]>>4)&0x0F);
			iACargar[2] = ((auxChar[1]<<2)&0x3C)|((auxChar[2]>>6)&0x03);
			iACargar[3] = (auxChar[2]&0x3F);

			for(int i = 0;i<4;i++)
				resultadoACargar[i] = base64[iACargar[i]];


			lenRespuesta += 4;
			respuesta = realloc(respuesta,lenRespuesta);


			for(int i = 0;i<4;i++,iRespuesta++){
				respuesta[iRespuesta] = resultadoACargar[i];
			}



	}



	return respuesta;
}


	char base64[64];
int main(void) {

	crearBase64(base64);

	codificarBase64("ABC");


}
