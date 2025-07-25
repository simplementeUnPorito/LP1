#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

void cleanBuffer()
{
    char c;
    while((c = getchar()) != '\n');
}

int isStr(char *buscar, char *dondeBuscar)
{
    int posic = 0, posic_aux, posicion;


    printf("Cadena: %s\nSe busca: %s\n\n", dondeBuscar, buscar);

    while (1)
    {
    	char *aux = (char *)malloc(1*sizeof(char));
        for (posic_aux = 0; dondeBuscar[posic] != '\0'; posic++)
        {
            if (buscar[0] == dondeBuscar[posic])
            {
                for (posic_aux = 0; buscar[posic_aux] != '\0'; posic_aux++, posic++)
                {
                    aux[posic_aux] = dondeBuscar[posic];
                    aux = (char *)realloc(aux, (posic_aux+2)*sizeof(char));
                }
                aux[posic_aux+1] = '\0';
                break;
            }
        }

        if (strncmp(aux, buscar, strlen(buscar)) == 0)
        {
			posicion = posic - strlen(buscar) + 1;
			printf("Posicion: %d\n", posicion);
			// printf("\n\naux: %s", aux);

			if (posic == strlen(dondeBuscar))
				break;
        }
        else
        	if (posic == strlen(dondeBuscar))
        		break;
        free(aux);

    }
    return posic;
}

int main()
{
    char buscar[10] = "hoy", dondeBuscar[100] = "Buenos dias, hoy me encontre hoy con Juanjo el bueno hoy";

    // strcpy(buscar, "Bueno");
    // strcpy(buscar, "Buenos dias, hoy me encontre con Juanjo");

    // printf("Cadena: %s\nSe busca: %s", dondeBuscar, buscar);

    isStr(buscar, dondeBuscar);

    return 0;
}

