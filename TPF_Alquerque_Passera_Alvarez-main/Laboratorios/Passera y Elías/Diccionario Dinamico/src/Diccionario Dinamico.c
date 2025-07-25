/*
 ============================================================================
 Name        : Diccionario.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct termino{
	char *palabra;
	char *definicion;
}termino;

typedef struct diccionario{
	termino* vecTerminos; //vector de structs que contiene cada palabra con su definicion
	size_t numTerminos; //
}diccionario;




diccionario cargarDiccionario(diccionario libro){
	termino aux;
	size_t charsAux[2] = {0,0};
	size_t lenAux[2] = {0,0};

	do{
		printf("Ingrese la palabra a definir (enter sin nada para finalizar): ");
		lenAux[0] = getline(&(aux.palabra),&(charsAux[0]),stdin);

		if(strcmp(aux.palabra,"\n") == 0)
			break;
		(aux.palabra)[lenAux[0]-1] = '\0';

		printf("Ingrese la definicion: ");
		lenAux[1] = getline(&(aux.definicion),&(charsAux[1]),stdin);
		(aux.definicion)[lenAux[1]-1] = '\0';

		(libro.numTerminos)++;
		libro.vecTerminos = (termino*)realloc(libro.vecTerminos,libro.numTerminos * sizeof(termino));

		libro.vecTerminos[libro.numTerminos-1].palabra = (char*)malloc(sizeof(char)*lenAux[0]);
		(libro.vecTerminos+(libro.numTerminos-1))->definicion = (char*)malloc(sizeof(char)*lenAux[1]);

		strcpy((libro.vecTerminos[libro.numTerminos-1].palabra),aux.palabra);
		strcpy(libro.vecTerminos[libro.numTerminos-1].definicion,aux.definicion);



	}while(1);

	return libro;
}


diccionario ordenarDiccionario(diccionario libro){
	termino aux;
	for(int i = 0; i<libro.numTerminos; i++){

		for(int j = 0; j<libro.numTerminos -1 ; j++){

			if(strcmp(libro.vecTerminos[j].palabra,libro.vecTerminos[j+1].palabra)>0){
				aux.palabra = libro.vecTerminos[j].palabra;
				aux.definicion = libro.vecTerminos[j].definicion;

				libro.vecTerminos[j].palabra=libro.vecTerminos[j+1].palabra;
				libro.vecTerminos[j].definicion=libro.vecTerminos[j+1].definicion;

				libro.vecTerminos[j+1].palabra = aux.palabra;
				libro.vecTerminos[j+1].definicion = aux.definicion;

			}
		}
	}
	return libro;
}

void printDiccionario(diccionario libro){
	for(int i = 0; i<libro.numTerminos; i++)
		printf("%s: %s\n",libro.vecTerminos[i].palabra, libro.vecTerminos[i].definicion);

}

void printOrdenadoDiccionario(diccionario libro){
	libro = ordenarDiccionario(libro);
	printDiccionario(libro);

}

int main(void) {
	diccionario libro;
	libro.numTerminos = 0;
	libro.vecTerminos = (termino*)malloc(1 * sizeof(termino));
	libro = cargarDiccionario(libro);

	printOrdenadoDiccionario(libro);


}
