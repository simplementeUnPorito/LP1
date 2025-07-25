#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_MAX 51 // longitud maxima de la cadena de carateres
#define TRUE 1
#define FALSE 0

void cleanBuffer()
{
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

char * pedir_cadena()
{   
    int len_cadena, i;
    char c, *cadena;

    do 
    {
        cadena = (char *)malloc(1*sizeof(char));
        len_cadena = 0;
        printf("Ingrese la cadena que desea verificar (solo numeros): ");

        for (i = 0; i < 51 && (c = getchar()) != EOF && c != '\n'; i++)
        {
            if (c >= '0' && c <= '9')
            {
                cadena[i] = c;
                cadena = (char *)realloc(cadena, (len_cadena+1)*sizeof(char)); 
                len_cadena++; 
            }
            else 
            {
                printf("\nError! La cadena debe contener unicamente numeros\n");
                free(cadena);
                cleanBuffer();
                break;
            }
        }

        if ((c == '\n' || c == EOF) && i == 0) 
        {
            printf("\nError! La cadena debe contener unicamente numeros\n");
            free(cadena);
            cleanBuffer();
        }
        else
        {
            if ((c == '\n' || c == EOF) && i != 0) 
            {
                cadena[len_cadena] = '\0';
                return cadena;
            }
        }
    } 
    while (TRUE); 
}

void print_vec_Int(char mensaje[], int *numeros)
{
    printf("%s", mensaje);
    for (int i = 0; numeros[i] != '\0'; i++)
    {   
        printf(" %i", numeros[i]);
    }
}

int * char_to_int_especial(char *cadena, int len_cadena)
{
    // int len_numeros = (len_cadena % 2) == 0 ? len_cadena/2 : (len_cadena/2)+1; // se calcula la longitud que se necesita reservar para numeros

    int *numeros = (int *)malloc(1*sizeof(int)), len_numeros = 1; 

    char aux[3];
    aux[2] = '\0';

    for (int i = 0, j = len_cadena-1; i <= j; i++, j--)
    {
        if (i < j)
        {
            aux[0] = cadena[i];
            aux[1] = cadena[j];
            numeros[i] = atoi(aux);
        }
        else
        {
            aux[0] = cadena[i];
            aux[1] = '\0';
            numeros[i] = atoi(aux);
        }    
        // printf("%s\n", aux);
        // printf("%i\n", numeros[i]);

        numeros = (int *)realloc(numeros, (len_numeros+1)*sizeof(int));
        len_numeros++;
    }
    numeros[len_numeros-1] = '\0';
    
    // printf("\nCadena de chars: %s\nLongitud de cadena: %d", cadena, len_cadena);
    // printf("\nCadena de numeros:");
    // print_vec_Int(numeros);
    // printf("\nLongitud de numeros: %d\n", len_numeros-1);

    return numeros;
}

// numero de elementos de un vector de enteros
int len_vec_int(int *numeros)
{
    int len_numeros = 0;

    for (int i = 0; numeros[i] != '\0'; i++, len_numeros++);

    return len_numeros;
}

// ordena cadena de caracteres de numeros
void ordenar_cadena(char *cadena) 
{
    char aux; 

    for (int i = 0; cadena[i] != '\0'; i++) 
        for (int j = 0; cadena[j] != '\0'; j++) 
            if ((cadena[j+1] != '\0') && ((cadena[j] - '0') > (cadena[j+1] - '0')))
            {
                aux = cadena[j+1];
                cadena[j+1] = cadena[j];
                cadena[j] = aux;
            }
    
    // printf("\nCadena de chars ordenado: %s\n", cadena);
}

// especial si todos los valores de numeros son primos, no especial si no todos sus valores son primos
int verificar_Especial(int *numeros)
{
    for (int i = 0; numeros[i] != '\0'; i++)
        for (int j = 2; j < numeros[i]; j++)
            if (numeros[i] % j == 0)
                return FALSE; // no es especial
    return TRUE; // si es especial
}

int main()
{   
    int *numeros, len_cadena, len_numeros, especial;
    char *cadena;

    cadena = pedir_cadena(); // retorna la direccion de la cadena (solo de nros) creada
    len_cadena = strlen(cadena); // retorna la longitud de la cadena 
    ordenar_cadena(cadena); // se ordenan los numero de la cadena
    numeros = char_to_int_especial(cadena, len_cadena); // retorna la direccion de la cadena de enteros listos para analizar si son especiales
    len_numeros = len_vec_int(numeros); // retorna la longitud de la cadena de enteros
    especial = verificar_Especial(numeros); // retorna TRUE si la cadena de numeros es especial y FALSE si no lo es

    printf("\nCadena de chars ordenado: %s\nLongitud de cadena: %d", cadena, len_cadena);
    print_vec_Int("\nCadena de numeros", numeros);
    printf("\nLongitud de numeros: %d\n", len_numeros);
    printf("\nLa cadena de numeros %s es especial.\n", especial ? "SI" : "NO");

    free(cadena);
    free(numeros);

    return 0;
}
