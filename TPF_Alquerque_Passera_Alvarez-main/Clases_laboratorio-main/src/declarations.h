#define MAX_CARACTERES 21
#define CANT_MAX_OPERADORES 10

/**
 * lectura de entrada:
 * 	- muestra opciones de entrada de datos
 * 	- retorna una bandera que indica si se desea seguir leyendo o no (1 para continuar, 0 para finalizar el programa)
 * 	- el programa deberá volver a preguntar si continuar o finalizar: menú de opciones del programa
 * 	- recibe el buffer donde se almacenara la expresion leida
 */
char leerExpresion(char expresion[MAX_CARACTERES]);

/**
 * procesamiento de la entrada:
 * - debe recibir la cadena a evaluar, un buffer para almacenar operadores y un buffer para operandos
 * - procesar la cadena completa e identificar las operaciones a realizar
 * - Los caracteres de entrada permitidos son: [0-9,+,-,*,/].
 * - Se asume que la entrada es válida
 * - actualiza una lista de operadores y operandos
 */
void procesarExpresion(char expresion[MAX_CARACTERES], char operadores[CANT_MAX_OPERADORES], int operandos[CANT_MAX_OPERADORES+1]);

/**
 * resolver operaciones:
 * - recibe la lista de operandos y operadores
 * - realiza operaciones, no importa la precedencia de operadores
 * - retorna resultado de la operacion
 */
int calcularResultado(char operadores[CANT_MAX_OPERADORES], int operandos[CANT_MAX_OPERADORES+1]);

/**
 * - opciones para impresion en pantalla
 * - casos en que sea <= 10 (romanos) o > 10
 * - recibe el valor a imprimir
 */
void imprimirResultados(int resultado);

/**
 * cual es el numero romano correspondiente
 * - recibe el numero a transformar
 * - retorna la cadena que representa el numero
 */
const char* obtenerRomano(int numero);

/*
 * limpia buffer de entrada
 */
void limpiarBuffer();
