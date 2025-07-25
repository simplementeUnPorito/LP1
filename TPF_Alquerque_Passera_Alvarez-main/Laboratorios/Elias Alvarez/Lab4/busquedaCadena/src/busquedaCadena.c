#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

int strncmpLP1(const char *str1, const char *str2, size_t n){
    size_t i =0;
    while(i++ < n && *str1 != '\0' && *str2 != '\0' && *str1++ == *str2++);
    *str1--;
    *str2--;
    // printf("c1:%c\tc2:%c\n",*str1,*str2);
    return (int)((*str2)-(*str1));
}

int strlenLP1(char* str){
    char* temp = str;
    while(*str++ != '\0');
    return str - temp - 1;
}


int isStr(char* buscar, char* dondeBuscar)
{
    char* temp = dondeBuscar;
    // printf("LenBuscar: %i",n);
    // printf("Buscar: %s\nDondeBuscar: %s\n\n",buscar, dondeBuscar);
   while(strlenLP1(buscar)<=strlenLP1(dondeBuscar)){
    //   printf("Buscar: %s\tDondeBuscar: %s\t%s\n\n",buscar, dondeBuscar,strncmpLP1(dondeBuscar,buscar,strlenLP1(buscar)) == 0? "SI":"NO");
        if(strncmpLP1(dondeBuscar,buscar,strlenLP1(buscar)) == 0){
            return dondeBuscar - temp +1;
        }
        dondeBuscar++;
    }
    return -1;
}



int* busquedaPP(char* buscar, char*dondeBuscar)
{
    int n = ceil(strlenLP1(dondeBuscar)/strlenLP1(buscar))+1;
    int* temp = (int*)malloc(n*sizeof(int));
    int* respuesta = temp;
    int placeHolder = 0,posicionActual = 0,posicionAnterior = 0;
    while(TRUE){
        posicionActual = isStr(buscar,dondeBuscar);
        if(posicionActual == -1)
            break;
        placeHolder = posicionActual+posicionAnterior;
        *temp++ = placeHolder;

        dondeBuscar+=posicionActual;
        posicionAnterior += posicionActual;
//        printf("AUX: %i\nPOSICION: %i\nM:%i\nDondeBuscar:%s\n\n",aux,*temp,m,dondeBuscar);


    }
    *temp = -1;
//
//     while(TRUE)
//         {
//         	if(*respuesta != -1)
//     			printf("%i ",*respuesta);
//     		else break;
//         	respuesta++;
//         }
     return respuesta;
}

int main()
{
    char buscar[] = "a", dondeBuscar[] = "raratirara";
    int* respuesta = busquedaPP(buscar,dondeBuscar);
    // printf("|%s| se encuentra en la posicion %i en |%s|",buscar,isStr(buscar,dondeBuscar),dondeBuscar);
    printf("Se encontro |%s| en |%s| en las siguientes posiciones: [",buscar,dondeBuscar);

    while(TRUE)
    {
    	if(*respuesta != -1)
			printf("%i",*respuesta);
		else break;
    	respuesta++;
    	if(*respuesta != -1)
    		printf(",");
    }


    printf("]\n");
    return 0;
}
