///*
// ============================================================================
// Name        : Ejercicio.c
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
// ============================================================================
// */
//
//#include <stdio.h>
//#include <stdlib.h>
//
//#define TRUE 1
//#define FALSE 0
//int filtroCabeceraJPG(FILE *ptrArchivo, char c){
//	if(c == 0xFF){
//		if((c= fgetc(ptrArchivo)) == 0xD8){
//			if((c= fgetc(ptrArchivo))==0xFF){
//				if((c= fgetc(ptrArchivo)) == 0xE0 || c == 0xE1){
//					return TRUE;
//				}else{
//					return FALSE;
//				}
//			}else{
//				return FALSE;
//			}
//		}else{
//			return FALSE;
//		}
//	}
//	else{
//
//		return FALSE;
//	}
//}
//
//
//char *crearNombre (int i){
//	static char cadena[100];
//	sprintf(cadena,"foto%d",i);
//	return cadena;
//}
//
//void recuperarFotos(char* archivoNombre){
//	FILE *ptrArchivo;
//	FILE *ptrFotoAux;
//	char nFotos = 0;
//
//	if((ptrArchivo = fopen(archivoNombre, "r")) == NULL){
//		perror("Recuperar fotos JPG");
//		return;
//	}
//
//	unsigned char c;
//	fseek(ptrArchivo,0,SEEK_SET);
//	while(TRUE){
//		if((c = fgetc(ptrArchivo)) == EOF)
//			break;
//		else{
//			if(!filtroCabeceraJPG(ptrArchivo, c))
//				fseek(ptrArchivo,511,SEEK_CUR);
//			else{
//				ptrFotoAux = fopen(crearNombre(nFotos++),"w");
//
//				do{
//					fputc(c,ptrFotoAux);
//					for(int i = 0; i<511;i++)
//						fputc(c = fgetc(ptrArchivo),ptrFotoAux);
//				}while((c = fgetc(ptrArchivo)) != EOF && !filtroCabeceraJPG(ptrArchivo, c));
//				fclose(ptrFotoAux);
//			}
//
//
//		}
//	}
//}
//
//int main(void) {
//	recuperarFotos("/home/lp1-2022/eclipse-workspace/GitProjects/TPF_Alquerque_Passera_Alvarez/Ejercicio Recuperar fotos JPG/Fotos.raw");
//	return EXIT_SUCCESS;
//}


/*
 ============================================================================
 Name        : fotos_jpg.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_SECTOR	512
unsigned char sector[TAM_SECTOR];
unsigned char firma[2][4] = {{0xff, 0xd8, 0xff, 0xe0}, {0xff, 0xd8, 0xff, 0xe1}};

/*
 * Crea un nombre de archivo para la foto. El nombre tiene la forma
 * foto<número>.jpg.
 * Parámetros:
 * 	i -> el número de foto
 * Retorno:
 * 	Dirección de la cadena con el nombre adecuado.
 */
char *creaNombre (int i) {
	static char cadena[100];

	sprintf (cadena, "foto%d.jpg", i);

	return cadena;
}

int main(void) {
	FILE *a, *d = NULL;
	int i, primeraFoto, tamanho, tamTotal = 0;
	char *nombre = "/home/lp1-2022/eclipse-workspace/GitProjects/TPF_Alquerque_Passera_Alvarez/Ejercicio Recuperar fotos JPG/Fotos.raw";
	if ((a = fopen(nombre, "r")) == NULL) {
		printf ("No encuentro el archivo fotos.raw\n");
		return -1;
	}

	for (i = 0, primeraFoto = 1, tamTotal = 0; fread (sector, 1, TAM_SECTOR, a) == TAM_SECTOR;) {
		// si encontramos una nueva foto, abrimos un archivo destino y cerramos el anterior
		if (memcmp(sector, firma[0], 4lu) == 0 || memcmp(sector, firma[1], 4lu) == 0){
			if (d != NULL) {
				fclose (d);	// cerramos archivo anterior
				// mostramos el tamaño del archivo anterior
				printf ("foto%d.jpg = %d bytes\n", i-1, tamanho);
			}
			if ((d = fopen(creaNombre(i), "w")) == NULL) {
				printf ("Error al intentar crear el archivo foto%d.jpg\nTerminamos", i);
				return -1;
			}
			// siguiente foto
			i++;
			tamanho = 0;
			primeraFoto = 0;
		}
		if (!primeraFoto) {
			// guardamos los datos
			fwrite (sector, 1, TAM_SECTOR, d);
			tamanho += TAM_SECTOR;
			tamTotal += TAM_SECTOR;
		}
	}
	// mostramos el tamaño de la última foto
	printf ("foto%d.jpg = %d bytes\n", i-1, tamanho);

	printf ("\nFueron recuperadas %d fotos\n", i);
	printf ("\nTamaño total = %d bytes\n", tamTotal);
	fclose (d);
	fclose (a);

	return EXIT_SUCCESS;
}


