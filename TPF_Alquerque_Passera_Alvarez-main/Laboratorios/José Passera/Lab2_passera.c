#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

void cleanBuffer () 
{
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

void print_vec_Float(char mensaje[], float *numeros)
{
    printf("%s", mensaje);
    for (int i = 0; numeros[i] != '\0'; i++)
    {   
        printf(" %f", numeros[i]);
    }
}

int len_vec_Float(float *numeros)
{
    int len_numeros = 0;

    for (int i = 0; numeros[i] != '\0'; i++, len_numeros++);

    return len_numeros;
}

// Se pide una cadena intercalada entre numeros y signos (solo los permitidos, ver condiciones de ifs) 
// La cadena debe comenzar con un numero obligatoriamente
// Si la cadena termina con un signo, se pone NULL (\0) en su ubicacion dentro de la cadena
// Si no se cumple alguna condicion, entonces se vuelve a pedir la cadena hasta que se cumplan todas
char * pedir_cadena ()
{
    char c, *cadena;
    int i, len_cadena = 0, cantidad_signos = 0, cantidad_numeros = 0;

    do 
    {
        len_cadena = cantidad_signos = cantidad_numeros = 0;
        cadena = (char *)malloc(1*sizeof(char));
        
        printf("\nIngrese la operacion a evaluar (caracteres permitidos: 0-9, +, -, * y /).\nSi la cadena termina con un signo, se omitira el signo.\nCadena: ");

        for (i = 0; (c = getchar()) != EOF && c != '\n'; i++)
        {
            if (c >= '0' && c <= '9')
            {
                cadena[len_cadena] = c;
                cadena = (char *)realloc(cadena, (len_cadena+1)*sizeof(char));
                len_cadena++;
                cantidad_numeros++;
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/')
            {
                if (cantidad_numeros != 0) 
                {
                    cadena[len_cadena] = c;
                    cadena = (char *)realloc(cadena, (len_cadena+1)*sizeof(char));
                    len_cadena++;
                    cantidad_signos++;
                }
                else
                {
                    printf("\nError! La cadena no puede empezar con un signo de operacion!\n\n");
                    cleanBuffer();
                    free(cadena);
                    break;
                }
            }
            else 
            {
                printf("\nError! La cadena solo puede contener los caracteres validos!\n\n");
                cleanBuffer();
                free(cadena);
                break;
            }
        }

        if ((c == '\n' || c == EOF) && (cantidad_numeros == 0 || cantidad_signos == 0 || i == 0)) // el i == 0 quiere decir que se ingreso nada, solo un enter
        {
            printf("\nError! La cadena debe contener como minimo una operacion permitida entre dos de los numeros permitidos.\n\n");
            cleanBuffer();
            free(cadena);
        }
        else
        {
            if (c == '\n' || c == EOF)
            {
                // Se revisa si la cadena termina con un signo o no
                // En ambos casos, se agrega +0 al final de la cadena porque o si no no se convierte el ultimo numero a float (no sé por qué :/)
                if (cadena[len_cadena-1] == '+' || cadena[len_cadena-1] == '-' || cadena[len_cadena-1] == '*' || cadena[len_cadena-1] == '/') 
                {
                    cadena[len_cadena] = '0';
                    cadena = (char *)realloc(cadena, (len_cadena+1)*sizeof(char));
                    cadena[len_cadena+1] = '\0';
                }
                else
                {
                    cadena[len_cadena] = '+';
                    cadena = (char *)realloc(cadena, (len_cadena+2)*sizeof(char));
                    cadena[len_cadena+1] = '0';
                    cadena[len_cadena+2] = '\0';   
                }
            
                // len_cadena = strlen(cadena);
                // printf("\nCadena ingresada: %s\nLongitud de cadena ingresada: %d\n", cadena, len_cadena);

                return cadena;
            }
        }
    }
    while (TRUE);
}

// Covierte los numeros de la cadena de caracteres en numeros floats (se considera un punto hata un signo de operacion) y los alamacena en un vector de floats (numeros)
float * convertir_numeros (char * cadena, int len_cadena)
{
    float * numeros = (float *)malloc(1*sizeof(float));
    char aux[len_cadena];
    int c, n, a;

    // c: indice para la cadena de caracetes            (cadena)
    // n: indice para la cadena de numeros              (numeros)
    // a: indice para la cadena auxiliar de caracteres  (aux)
    for (c = 0, a = 0, n = 0; cadena[c] != '\0'; c++) 
    {
        if (cadena[c] >= '0' && cadena[c] <= '9')
        {  
            aux[a] = cadena[c];
            // printf("\n%s", aux);
            a++;
        }
        else
        {
            aux[a] = '\0';
            numeros[n] = atof(aux);
            a = 0; // reseteamos para empezar desde 0 en la cadena aux y asi evitamos que los numeros se encimen
            n++;
            numeros = (float *)realloc(numeros, (n+1)*sizeof(float));
        }
    }   
    numeros[n] = '\0';
    // print_vec_Float("\nCadena de numeros floats:", numeros);
    return numeros;
}

// Se ubican los signos de la cadena de caracteres en un vector de caracteres (signos)
char * obtener_signos (char * cadena, int len_cadena)
{
    char * signos = (char *)malloc(1*sizeof(char));
    int c, s;

    // c: indice para la cadena de caracetes    (cadena)
    // s: indice para la cadena de signos       (signos)
    for (c = 0, s = 0; cadena[c] != '\0'; c++) 
        if (cadena[c] == '+' || cadena[c] == '-' || cadena[c] == '*' || cadena[c] == '/')
        {  
            signos[s] = cadena[c];
            s++;
            signos = (char *)realloc(signos, (s+1)*sizeof(char));
        }  
    signos[s] = '\0';

    return signos;
}

float calculo_operacion (float * numeros, int len_numeros, char * signos, int len_signos)
{
    float valorFinal = numeros[0];
    
    printf("\n\nOperaciones: ");

    for (int s = 0, n = 1; s < len_signos; s++, n++)
    {
        switch (signos[s])
        {
            case '+':
                printf("\n%f + ", valorFinal);
                valorFinal += numeros[n]; 
                printf("%f = %f", numeros[n], valorFinal);  
                break;
            case '-':
                printf("\n%f - ", valorFinal);
                valorFinal -= numeros[n]; 
                printf("%f = %f", numeros[n], valorFinal);
                break;
            case '*':
                printf("\n%f * ", valorFinal);
                valorFinal *= numeros[n];
                printf("%f = %f", numeros[n], valorFinal);
                break;
            case '/':
                if (numeros[n] != 0) 
                {
                    printf("\n%f / ", valorFinal);
                    valorFinal /= numeros[n];
                    printf("%f = %f", numeros[n], valorFinal); 
                }
                else
                    printf("\n\nNo se puede dividir un numero entre 0.\nSe realizo el calculo de las operaciones anteriores a la division entre 0.");
                break;
            default: 
                break;
        }
        if (numeros[n] == 0 && signos[s] == '/')
            break;
    }
    return valorFinal;
}

int main()
{
    char *cadena, *signos; 
    float *numeros;
    int len_numeros, len_cadena, len_signos;

    cadena = pedir_cadena();
    len_cadena = strlen(cadena);
    numeros = convertir_numeros(cadena, len_cadena);
    len_numeros = len_vec_Float(numeros);
    signos = obtener_signos(cadena, len_cadena);
    len_signos = strlen(signos);

    printf("\nCadena ingresada: %s\nLongitud de cadena ingresada: %d", cadena, len_cadena);
    print_vec_Float("\nCadena de numeros floats:", numeros);
    printf("\nLongitud de cadena de numeros floats: %d\n", len_numeros);
    printf("Cadena de signos: %s\nLongitud de cadena de signos: %d", signos, len_signos);
    printf("\n\nResultado de la operacion: %f\n", calculo_operacion(numeros, len_numeros, signos, len_signos));

    return 0;
}
