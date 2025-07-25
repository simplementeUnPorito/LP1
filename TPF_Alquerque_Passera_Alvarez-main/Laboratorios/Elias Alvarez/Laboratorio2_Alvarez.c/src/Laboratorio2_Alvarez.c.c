#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20
#define TRUE 1
#define FALSE 0

void cleanBuffer(void)
{
    char c;
    while((c=getchar()) !='\n' && c != EOF);

}

float calculadoraSP(char expresion[]){
	int final = strlen(expresion),j;
	char subexpresion[MAX +1], operacion='+';
	subexpresion[MAX] = '\0';
	float resultado;
	resultado = 0;
	for(int i = 0;i<final;i++){
		for(j=0;isdigit(expresion[i]);i++,j++)
			subexpresion[j] = expresion[i];

		subexpresion[j] = '\0';

		if (operacion == '+')
			resultado += atof(subexpresion);
		else if(operacion == '-')
			resultado -= atof(subexpresion);
		else if(operacion == '*')
			resultado *= atof(subexpresion);
		else if(operacion == '/')
			resultado /= atof(subexpresion);
		else;

		//printf("\n\nOPERADOR:%c\t\tNUMERO:%f\t\tRESULTADO:%f\n",operacion,atof(subexpresion),resultado);

		operacion = expresion[i];
	}
	 return resultado;
}

void printNumNombre(float number){
    char isNegative = FALSE;
    if (number<0){
        isNegative = TRUE;
    }


    if ((number - (int)number == 0) && -10<=number && number<=10){
        switch (isNegative?-(int)number:(int)number){
            case 0:
                printf("Cero");
            case 1:
                printf("%sUno",isNegative?"Menos ":"");
                break;
            case 2:
                printf("%sDos",isNegative?"Menos ":"");
                break;
            case 3:
                printf("%sTres",isNegative?"Menos ":"");
                break;
            case 4:
                printf("%sCuatro",isNegative?"Menos ":"");
                break;
            case 5:
                printf("%sCinco",isNegative?"Menos ":"");
                break;
            case 6:
                printf("%sSeis",isNegative?"Menos ":"");
                break;
            case 7:
                printf("%sSiete",isNegative?"Menos ":"");
                break;
            case 8:
                printf("%sOcho",isNegative?"Menos ":"");
                break;
            case 9:
                printf("%sNueve",isNegative?"Menos ":"");
                break;
            case 10:
                printf("%sDiez",isNegative?"Menos ":"");
                break;
            default:
                printf("ERROR EN IMPRESION DE NUMERO");
                break;
        }
    }else printf("%.2f",number);

}


int main()
{
    char expresion[MAX+1];
    expresion[MAX] =  '\0';
    float resp;

    printf("Ingrese la formula: ");
    scanf("%20s",expresion);
    cleanBuffer();

	resp = calculadoraSP(expresion);
	printf("Resultado: ");
    printNumNombre(resp);

}
