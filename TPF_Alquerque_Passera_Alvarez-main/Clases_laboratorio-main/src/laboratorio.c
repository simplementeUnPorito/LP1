#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"

#define CANT_VAL_1D 10

/**
 * lectura de entrada:
 * 	- muestra opciones de entrada de datos
 * 	- retorna una bandera que indica si se desea seguir leyendo o no (1 para continuar, 0 para finalizar el programa)
 * 	- el programa deberá volver a preguntar si continuar o finalizar: menú de opciones del programa
 * 	- recibe el buffer donde se almacenara la expresion leida
 */
char leerExpresion(char expresion[MAX_CARACTERES]){
	char opcion;

	// mensajes de bienvenida
    printf("Bienvenido! Desea evaluar una expresion? (y/n)\n");
    scanf("%c", &opcion);
    limpiarBuffer();

    switch(opcion){
    case 'y':
    	printf("Ingrese la expresion a evaluar (max 20 caracteres).\n");
    	strcpy(expresion,"");	// limpiamos buffer de expresion
    	scanf("%20[0-9+-*/]s", expresion);
    	limpiarBuffer();
    	break;
    case 'n':
    	printf("Gracias por usar la calculadora. Hasta luego.\n");
    	return 0;
    default:
    	printf("Opcion incorrecta.\n");
    	return 0;
    }

    return 1;
}


/**
 * procesamiento de la entrada:
 * - debe recibir la cadena a evaluar, un buffer para almacenar operadores y un buffer para operandos
 * - procesar la cadena completa e identificar las operaciones a realizar
 * - Los caracteres de entrada permitidos son: [0-9,+,-,*,/].
 * - Se asume que la entrada es válida
 * - actualiza una lista de operadores y operandos
 */
void procesarExpresion(char expresion[MAX_CARACTERES], char operadores[CANT_MAX_OPERADORES], int operandos[CANT_MAX_OPERADORES+1]){
	int i; // para el recorrido
	int i_operador = 0, i_operando = 0;

	char operando[MAX_CARACTERES] = ""; // se guarda la ultima cadena de caracteres leida (operando)
	int t_op = 0; // para ir almacenando temporalmente el operando

	// recorrer toda la cadena de expresion: caracter por caracter se va leyendo, al encontrar un operador corta la lectura de cada operando
	for(i=0; i<MAX_CARACTERES; i++){
		if(expresion[i] == '+' || expresion[i] == '-' || expresion[i] == '*' || expresion[i] == '/'){
			t_op = 0;
			operandos[i_operando++] = atoi(operando);
			operadores[i_operador++] = expresion[i];
			operadores[i_operador] = '\0';
		}else{
			operando[t_op++] = expresion[i];
			operando[t_op] = '\0';	//cada vez que agregamos un nuevo caracter, agregamos un caracter nulo para finalizar la cadena (si el numero tiene varios digitos, el caracter nulo se sobreescribira
		}
	}
	operandos[i_operando] = atoi(operando); // para el ultimo operando
}

/**
 * resolver operaciones:
 * - recibe la lista de operandos y operadores
 * - realiza operaciones, no importa la precedencia de operadores
 * - retorna resultado de la operacion
 */
int calcularResultado(char operadores[CANT_MAX_OPERADORES], int operandos[CANT_MAX_OPERADORES+1]){
	int i;
	int resultado = operandos[0];
	for(i = 0; operadores[i]; i++){
		switch(operadores[i]){
		case '+':
			resultado += operandos[i+1];
			break;
		case '-':
			resultado -= operandos[i+1];
			break;
		case '*':
			resultado *= operandos[i+1];
			break;
		case '/':
			resultado /= operandos[i+1];
			break;
		}
	}

	return resultado;
}

/**
 * - opciones para impresion en pantalla
 * - casos en que sea <= 10 (romanos) o > 10
 * - recibe el valor a imprimir
 */
void imprimirResultados(int resultado){
	if(resultado <= 10)
		printf("El resultado es %d y en romanos %s\n", resultado, obtenerRomano(resultado));
	else
		printf("El resultado es: %d\n", resultado);
}

void mostrarTrivia(int resultado){
	int cantdig[10];
	// pedir datos al usuario
	char respuestaUsuario;
	printf("Cual es el valor que aparece mas veces?");
	int lecturaCorrecta = scanf("%[0-9]c", &respuestaUsuario);
	limpiarBuffer();

	if(lecturaCorrecta){
		char stringResultado[MAX_CARACTERES];
		char c;
		int i;

		// comparar con el valor que aparece mas veces
		sprintf(stringResultado, "%d", resultado);
		// ceramos el array
		for(i=0;i<10;i++){
			*(cantdig+i) = 0; // cantdig[i]=0
		}


		for(i=0; c = *(stringResultado+i); i++){
			int digito = c - '0';
			*(cantdig + digito) += 1;
		}

		int mayor = *cantdig;
		int indMayor = 0;
		for(i=1;i<10;i++){
			if(*(cantdig+i) > mayor){
				mayor = *(cantdig+i);
				indMayor = i;
			}
		}

		// imprimir respuesta final: lo ingresado es correcto o no
		int valorUsuario = respuestaUsuario-'0';
		if(valorUsuario == indMayor)
			printf("\nEs correcto. El valor %d aparece %d veces.\n\n", indMayor, mayor);
		else
			printf("\nEs incorrecto. El valor %d aparece %d veces. El mayor es %d y aparece %d veces.\n\n", valorUsuario, *(cantdig+valorUsuario), indMayor, mayor);
	}

}



int main(void) {
	char expresion[MAX_CARACTERES],
		operadores[CANT_MAX_OPERADORES];
	int operandos[CANT_MAX_OPERADORES + 1];

	// se leera y procesara una nueva expresion hasta que el usuario finalice
	while(leerExpresion(expresion)){
		// se procesa expresion para obtener operadores y operandos
		procesarExpresion(expresion, operadores, operandos);
		int resultado = calcularResultado(operadores, operandos);
		mostrarTrivia(resultado);
		imprimirResultados(resultado);
	}
}
