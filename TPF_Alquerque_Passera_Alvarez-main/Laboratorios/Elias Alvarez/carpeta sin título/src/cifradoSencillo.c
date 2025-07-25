#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

char* quitarChar(char *str, size_t *lenChar, char charQuitar)
{
	int i,j;
	for(i=j=0; str[i]!='\0';i++)
		if(str[i] != charQuitar)
			str[j++] = str[i];
	str[j] = '\0';
	*lenChar = j;
	return str;
}



void cifrar(char* str, size_t *strChars,size_t strLen){
	int piso = floor(*strChars);
	int techo = ceil(*strChars);
	char **matrixAux, **matrix;

	matrix = matrixAux= (char**)malloc(piso*sizeof(char*));
	if(matrixAux == NULL)
		exit (1);
	while(piso--){
		*matrixAux = (char *)malloc(techo*sizeof(char));
		if(*matrixAux == NULL)
			exit (1);
		matrixAux++;
	}


	return;
}


int main(void) {
	char *entrada = NULL;
	size_t largorEntrada = 0;
	int cantidadChars = 0;
	printf("Ingrese su cadena: ");
	cantidadChars = getline(&entrada,&largorEntrada,stdin)-1;
	entrada[cantidadChars] = '\0';
	char modo;
	modo = 'c';
	switch (modo)
	{
		case 'c':
			entrada = quitarChar(entrada,&cantidadChars,' ');
			entrada = cifrar(entrada, &cantidadChars,largorEntrada);
			break;
		case 'd':

			break;
		default:
			puts("ERROR: Modo de ejecucion no valido");
			break;
	}



	return EXIT_SUCCESS;
}
