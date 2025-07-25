#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAMANO_MAXIMO 50
#define FALSE 0
#define TRUE 1
//esta funcion recorre el buffer hasta dejarlo limpio, PERO NO debe ingresarse en esta si el buffer ya no tiene nada
void cleanBuffer()
{
    char c;
    while((c = getchar())!='\n' && c!= EOF);
}

//cargamos una cadena Numerica la cual sera solicitada hasta cumplirse la condicion
int cargarNumeros(char mensaje[],char lista[])
{
    char aux[TAMANO_MAXIMO+1], c , esNumerica;
    aux[TAMANO_MAXIMO] = '\0'; //cadena auxiliar porque tengo miedo de tocar mi cadena
    int i,j;
    do{
        printf("%s",mensaje);
        for(i = 0; i<TAMANO_MAXIMO && (c=getchar())!='\n' && c!=EOF;++i)
            aux[i] = c;
        if(c!='\n')
            cleanBuffer();
        aux[i]='\0';
        esNumerica = TRUE;
        for(j = 0;j<i;j++){
            if(aux[j]<'0' || '9'<aux[j] ){ //verificamos si cada caracter esta en el rango establecido
                esNumerica = FALSE;
                puts("Error: La cadena no es numerica");
                break;
            }
        }
    }while(esNumerica==FALSE);
    strcpy(lista,aux); //cargamos la aux a lista
    return i; //retornamos el largor de la cadena resultado
}

char esPrimo(int numero){
    char respuesta = TRUE;
    for(int i = 2; i<numero;i++)
    {
        if(numero%i == 0){ //dividimos por todos los numeros anteriores a el y si sale multiplo no es primo
            // printf("Es divisible por: %i\n",i);
            respuesta = FALSE;
            break;
        }
    }
    return respuesta;
}

char esEspecial(char lista[],int numeroDeChars)
{
    char strAux[3];
    strAux[2] = '\0';
    int charIzquierdo = 0, charDerecho = numeroDeChars -1; //recorremos la cadena acercandonos al centro por ambos lados

    for(; charIzquierdo<=charDerecho;charIzquierdo++,charDerecho--){
        if(charIzquierdo != charDerecho) //creamos una subcadena con el numero a verificar si es primo o no
        {
            strAux[0] = lista[charIzquierdo];
            strAux[1] = lista[charDerecho];
        }else
        {
            strAux[0] = lista[charIzquierdo];
            strAux[1] = '\0';
        }
        // printf("NUMERO: %s\n",strAux);

        if (!esPrimo(atoi(strAux))) //si es primo salimos ya que ya es falso
        {
            return FALSE;
        }
    }
    return TRUE;
}


int main()
{
    char lista[TAMANO_MAXIMO+1];
    int numeroDeChars;
    lista[TAMANO_MAXIMO] = '\0';
    numeroDeChars = cargarNumeros("Ingrese una cadena de caracteres: ",lista);
    // printf("Cadena recibida: %s\nNumero de chars: %i\n",lista,numeroDeChars);
    printf("%s",esEspecial(lista,numeroDeChars)?"Es especial":"No es especial");
    // int a = 6;
    // printf("%i %s es primo",a,esPrimo(a)?"":"no");
}
