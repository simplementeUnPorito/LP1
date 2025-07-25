// INCLUSION DE LAS LIBRERIAS USADAS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <gtk/gtk.h>


// DEFINICION DE VARIABLES NUMERICAS Y BOOLEANAS
#define PC 0
#define PERSONA 1
#define SIN_VICTORIA 0
#define VICTORIA_BLANCAS 1
#define VICTORIA_NEGRAS 2
#define PLAY_AGAIN 1
#define TURNO_BLANCAS 0
#define TURNO_NEGRAS 1
#define FALSO 0
#define VERDADERO 1

// DEFINICION DE CHARS UTILIZADOS PARA LA IMPRESION DE LA TABLA EN EL PROGRAMA
#define CHAR_BLANCO '@'
#define CHAR_NEGRO  'O'
#define CHAR_VACIO  ' '

// DEFINICION DE LOS MENSAJES
#define PEDIR_MODO "Seleccione el modo de juego:\n[P]C vs PC\n[S]ingle Player\n[M]ultiplayer\nRespuesta: "
#define ASK_COLOUR "Elija el color con el que jugara:\n[B]lancas\n[N]egras\n\nRespuesta: "
#define ASK_ORDEN "Elija el orden de los turnos:\n[B]lancas primero\n[N]egras primero\n[R]andom\n\nRespuesta: "
#define ASK_PLAYAGAIN "Quiere jugar de nuevo?\n[S]i\n[N]o\n\nRespuesta: "

/* DECLARACION DE VARIABLES GLOBALES
 * 	jBLanco y jNegro 			 -> hacemos referencia a quién le toca las fichas blancas o negras. Ej.: jBlanco es la PC (0)
 * 	fichasBlancas y fichasNegras -> nro. de fichas en cada momento de cada jugador durante el juego
 * 	turno 						 -> hace referencia al jugardor a quien le toca jugar en ese momento
 * 	tablero[5][6]				 -> estructura de la tabla donde se juega
*/
unsigned char jBlanco, jNegro, fichasBlancas, fichasNegras, tablero[5][6], turno;

/* Limpia el buffer de teclado
 * Utilizado en la funcion: checkAnswer()
 * Parametros: nada
 * Return: nada (es void)
 */
void cleanBuffer()
{
 	char c;
	while ((c = getchar()) != '\n');
}

/* Se resetean los valores de tablero[5][6] (global)
 * Utilizadon en el main()
 * Parametros: nada
 * Return: nada (es void)
 */
void resetTablero()
{
	// Se resetean la posición de cada ficha en la tabla
	int j = 0,i = 0;
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5;j++)
		{
			if (i < 2)
				tablero[i][j] = CHAR_NEGRO;
			else if (i == 2)
			{
				if(j < 2)
					tablero[i][j] = CHAR_NEGRO;
				else if (j > 2)
					tablero[i][j] = CHAR_BLANCO;
				else
					tablero[i][j] = CHAR_VACIO;
			}
			else
				tablero[i][j] = CHAR_BLANCO;
		}
		tablero[i][j] = '\0'; // al final de cada fila (en la ultima columna) se pone el \0
	}
}

/* Se verifica si la respuesta ingresada por teclado forma parte de la cadena respuestasP[]
 * Esto se repite hasta que la respuesta sea igual a uno de los valores de respuestasP[]
 * Utilizado en las funciones: askPlayAgain() y chooseMode()
 * Parametros:
 * 	mensaje[]	  -> mensaje que se mostrara por pantalla antes de pedir la respuesta (ej.: PEDIR_MODO -> cadena global)
 * 	respuestasP[] -> contiene las respuestas validas
 * 	nRespuestas	  -> longitud de respuestasP[]
 * Return: tipo char
 * 	respuesta -> contiene uno de los elementos de respuestasP[]
 */
char checkAnswer(char mensaje[], char respuestasP[], int nRespuestas)
{
	
	// quedarse: actua como bandera del while
	// respuesta: almacenara el caracter introducido por teclado
	char respuesta, quedarse = VERDADERO;
	
	// Pide la respuesta a la persona hasta que su valor esté dentro de respuestaP[]"
	do
	{
		printf("%s", mensaje);
		respuesta = getchar();
		cleanBuffer();
		respuesta = toupper(respuesta);
		// Se recorre nRespuestas[] para verificar si el contenido de respuesta se encuentra dentro
		for(int i = 0; i < nRespuestas; i++)
		{
			if(respuesta == respuestasP[i] )
			{
				quedarse = FALSO; // Si "respuesta" está dentro de "nRespuestas[]", entonces se habilita la salida del while
				break;
			}
		}
		puts("");
	}
	while(quedarse);
	
	return respuesta; // Devuelve uno de los elementos de "respuestasP[]"
}
/* Pregunta si se quiere volver a jugar o no
 * Utilizado en la funcion: main()
 * Parametros: nada
 * Return: tipo char
 * 	 PLAY_AGAIN (1) -> si la funcion checkAnswer() retorna 'S'
 * 	!PLAY_AGAIN (0) -> si la funcion checkAnswer() retorna 'N'
 */
char askPlayAgain()
{
	char respuestasPosibles[] = {'S','N'};

	return checkAnswer(ASK_PLAYAGAIN, respuestasPosibles, 2) == 'S' ? PLAY_AGAIN : !PLAY_AGAIN;
}

/* Verificamos si llegamos o no a una victoria
 * Tres casos posibles: no ha ganado nadie, gano el jugador blanco o gano el jugador negro
 * Utilizado en la funcion: play()
 * Parametros: nada
 * Return: tipo char
 *	VICTORIA_NEGRAS  (2) -> si el jugador con fichas blancas se queda sin fichas, es decir, si fichasBlancas == 0
 *	VICTORIA_BLANCAS (1) -> si el jugador con fichas negras se queda sin fichas, es decir, si fichasNegras == 0
 *	SIN_VICTORIA	 (0) -> si todavia no hay jugador cuyo numero de fichas sea 0
 */

char askVictory()
{
	if (fichasBlancas == 0)
		return VICTORIA_NEGRAS;
	else if (fichasNegras == 0)
		return VICTORIA_BLANCAS;
	else
		return SIN_VICTORIA;
}

/* Se solicitar el modo de juego (PERSONA vs PC (Singleplayer), PC vs PC o PERSONA vs PERSONA (Multiplayer))
 * Utilizado en la funcion: main()
 * Tambien se elige que color de ficha empieza moviendo
 * Modificacion de globales: (una de las dos posibilidades dependiendo de lo que elija la persona)
 * 	jBlanco y jNegro -> PERSONA (1)
 * 					 -> PC (0)
 * 	turno -> TURNO_BLANCAS (0)
 * 		  -> TURNO_NEGRAS  (1)
 * Parametros: nada
 * Return: nada (es void)
 */
void chooseMode()
{
	char respuesta, respuestasModo[] = {'P','S','M'}, respuestasColor[]={'B','N'}, respuestasOrden[] = {'B','N','R'};

	// Preguntamos si se quiere jugar Singleplayer (PERSONA vs PC), PC vs PC o Multiplayer (PERSONA vs PERSONA)
	respuesta = checkAnswer(PEDIR_MODO, respuestasModo, 3);

	if (respuesta == 'P') // PC vs PC
		jBlanco = jNegro = PC;
	else if (respuesta == 'M') // Multiplayer
		jBlanco = jNegro = PERSONA;
	else // Singleplayer
	{
		// Si es Singleplayer, entonces se pregunta qué color de piezas se quiere ser y, dependiendo de la respuesta,
		// se asignan los valores a jBlanco y jNegro (a quien le toca cada ficha)

		respuesta = checkAnswer(ASK_COLOUR, respuestasColor, 2);

		if (respuesta == 'B')
		{
			jBlanco = PERSONA;
			jNegro = PC;
		}
		else
		{
			jBlanco = PC;
			jNegro = PERSONA;
		}
    }
	
	// Preguntamos quién empieza primero (negras, blancas o random) 
    respuesta = checkAnswer(ASK_ORDEN, respuestasOrden, 3);
    if (respuesta == 'B') {
		// El turno actual corresponde al jugador cuyas fichas son las blancas
        turno = TURNO_BLANCAS;
    } else if (respuesta == 'N') {
		// El turno actual corresponde al jugador cuyas fichas son las negras
    	turno = TURNO_NEGRAS;
    } else {
		// El turno actual corresponde a un jugador random
    	turno = rand()%2;
    }
    
}

/* Se imprime la tabla completa en su estado actual
 * Utilizado en la funcion: play()
 * Parametros: nada
 * Return: nada (es void)
 */
void printTable()
{
	// Matriz que muestras los caminos posibles para cada ficha dentro de la tabla
	// Será utilizada en una función para graficar la tabla entera
	const char caminosTablero[5][10] = {"|\\|/|\\|/|", "|/|\\|/|\\|", "|\\|/|\\|/|", "|/|\\|/|\\|"};

	// Se recorre tablero[5][6]
    printf("\n  0 1 2 3 4\n");
	for(int i = 0; i < 5; i++)
	{
        printf("%i ", i);
		for(int j = 0; j < 5; j++)
		{
			// Imprime CHAR_BLANCO, CHAR_NEGRO o CHAR_VACIO dependiendo del valor de tablero[i][j]
			printf("%c", tablero[i][j]);
			printf("%c", j < 4 ? '-' : '\n');
		}
		printf("  %s\n", caminosTablero[i]);
	}
	printf("Fichas Blancas: %i\tFichas Negras: %i\n\n",fichasBlancas,fichasNegras);
}

/* Revisa si cada caracter de la cadena es un numero
 * Utilizado en la funcion: revisar_Syntax_Cad()
 * Parametros:
 * 	&str -> direccion que contiene la cadena donde esta la jugada ingresada
 * Return: tipo int
 * 	FALSO (0) 	  -> si no todos los caracteres son numeros o no hay numeros
 * 	VERDADERO (1) -> si todos los caracteres son numeros
 */
int isNumeric(char* str)
{
    // printf("%s",str);
    while(VERDADERO)
    {
        // printf("%c\n",*str);
        if(*str == '\0')
        	break;

        if(isdigit(*str) == FALSO)
            return FALSO;

        str++;
    }

    // printf("Es numerico\n\n");
    return VERDADERO;

}

/* Se revisa si la posicion esta dentro del rango, si no esta, se retorna FALSO
 * Utilizado en la funcion: revisar_Syntax_Cad()
 * Parametros:
 * 	int num -> numero a ser analizado
 * 	int min -> valor minimo del intervalo cerrado
 * 	int max -> valor maximo del intervalo cerrado
 * Return: tipo int
 * 	FALSO (0) -> si num no forma parte del intervalo cerrado [min, max]
 * 	VERDADERO (1) -> si num forma parte del intervalo cerrado [min, max]
 */
int dentroRangoInclusive(int num, int min, int max)
{
	if (num <= max && num >= min)
		return VERDADERO;
	else
		return FALSO;
}

/* Revisa si el movimiento en diagonal es valido
 * Utilizado en la funcion: revisar_Semantica_Y_Carga()
 * Parametros:
 * 	aux[5][6] 			-> matriz auxiliar donde se realizan las pruebas de movimiento
 * 	coord_actual[3] 	-> contiene la posicion de la ficha que se quiere mover
 * 	char coord_sgte[3] 	-> contiene la posicion a la que se quiere llegar
 * 	coord_comido[3]		-> incialmente vacio; se modifica si hay alguna ficha entre coord_actual y coord_sgte
 * Return:
 * 	FALSO 		-> si la ficha no puede realizar el movimiento diagonal
 * 	VERDADERO   -> si la ficha puede realizar el movimiento diagonal
 */
int mov_diagonal_cuadrantes(unsigned char aux[5][6], char coord_actual[3], char coord_sgte[3], char coord_comido[3])
{
	// Movimiento hacia el 2do cuadrante
	if ((coord_sgte[0] == coord_actual[0] - 2 && coord_sgte[1] == coord_actual[1] - 2))
	{
		if (turno == TURNO_BLANCAS)
		{
			if (aux[coord_sgte[0] - '0' + 1][coord_sgte[1] - '0' + 1] != CHAR_NEGRO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_sgte[0]  + 1;
				coord_comido[1] =  coord_sgte[1] - '0' + 1;
			}
		}
		else if (aux[coord_sgte[0] - '0' + 1][coord_sgte[1] - '0' + 1] != CHAR_BLANCO)
		{
			return FALSO;
		}
		else
		{
			coord_comido[0] = coord_sgte[0] + 1;
			coord_comido[1] =  coord_sgte[1]  + 1;
		}
	}
	// Movimiento hacia el 1er cuadrante
	else if ((coord_sgte[0] == coord_actual[0] + 2 && coord_sgte[1] == coord_actual[1] - 2))
	{
		if (turno == TURNO_BLANCAS)
		{
			if (aux[coord_sgte[0] - '0' - 1][coord_sgte[1] - '0' + 1] != CHAR_NEGRO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_sgte[0] - 1;
				coord_comido[1] =  coord_sgte[1] + 1;
			}
		}
		else
		{
			if (aux[coord_sgte[0] - '0' - 1][coord_sgte[1] - '0' + 1] != CHAR_BLANCO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_sgte[0] - 1;
				coord_comido[1] =  coord_sgte[1] + 1;
			}
		}

	}
	// Movimiento hacia el 3er cuadrante
	else if ((coord_sgte[0] == coord_actual[0] - 2 && coord_sgte[1] == coord_actual[1] + 2))
	{
		if (turno == TURNO_BLANCAS)
		{
			if (aux[coord_sgte[0] - '0' + 1][coord_sgte[1] - '0' - 1] != CHAR_NEGRO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_sgte[0]  + 1;
				coord_comido[1] =  coord_sgte[1] - 1;
			}
		}
		else
		{
			if (aux[coord_sgte[0] - '0' + 1][coord_sgte[1] - '0' - 1] != CHAR_BLANCO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_sgte[0] + 1;
				coord_comido[1] =  coord_sgte[1] - 1;
			}
		}
	}
	// Movimiento hacia el 4to cuadrante
	else if ((coord_sgte[0] == coord_actual[0] + 2 && coord_sgte[1] == coord_actual[1] + 2))
	{
		if (turno == TURNO_BLANCAS)
		{
			if (aux[coord_sgte[0] - '0' - 1][coord_sgte[1] - '0' - 1] != CHAR_NEGRO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_sgte[0]  - 1;
				coord_comido[1] =  coord_sgte[1]  - 1;
			}
		}
		else if (aux[coord_sgte[0] - '0' - 1][coord_sgte[1] - '0' - 1] != CHAR_BLANCO)
		{
			return FALSO;
		}
		else
		{
			coord_comido[0] = coord_sgte[0]  - 1;
			coord_comido[1] =  coord_sgte[1]  - 1;
		}
	}

	return VERDADERO; // El movimiento en diagonal es valido
}

/* Verifica si la ficha seleccionada (mediante la posicion) es del color del jugador cuyo turno corresponde
 * Utilizado en la funcion: revisar_Semantica_Y_Carga()
 * Parametros:
 * 	aux[5][6] 			-> matriz auxiliar donde se realizan las pruebas de movimiento
 * 	coord_actual[3] 	-> contiene la posicion de la ficha que se quiere revisar
 * Return:
 * 	FALSO 		-> si la ficha no concuerda con el turno
 * 	VERDADERO   -> si la ficha concuerda con el turno
 */
int coincide_ficha_turno(unsigned char aux[5][6], char coord_actual[3])
{
	if (turno == TURNO_BLANCAS && aux[coord_actual[0]-'0'][coord_actual[1]-'0'] != CHAR_BLANCO)
		return FALSO;

	if(turno == TURNO_NEGRAS && aux[coord_actual[0]-'0'][coord_actual[1]-'0'] != CHAR_NEGRO)
		return FALSO;

	return VERDADERO;
}

/* Verifica si el movimiento VERTICAL es valido
 * Utilizado en la funcion: revisar_Semantica_Y_Carga()
 * Parametros:
 *	aux[5][6] 			-> matriz auxiliar donde se realizan las pruebas de movimiento
 * 	coord_actual[3] 	-> contiene la posicion de la ficha que se quiere mover
 * 	char coord_sgte[3] 	-> contiene la posicion a la que se quiere llegar
 * 	coord_comido[3]		-> incialmente vacio; se modifica si hay alguna ficha entre coord_actual y coord_sgte
 * 	&mov_doble			-> 	FALSO 	  -> la cadena debe ser unicamente de 1 movimiento
 * 			  				VERDADERO -> la cadena es de +1 movimiento
 * Return:
 * 	FALSO 		-> si la ficha no puede realizar el movimiento sobre el eje y
 * 	VERDADERO   -> si la ficha puede realizar el movimiento sobre el eje y
 */
int mov_eje_Y(unsigned char aux[5][6], char coord_sgte[3], char coord_comido[3], char coord_actual[3], int *mov_doble)
{
	if(abs(coord_actual[0] - coord_sgte[0]) == 1) // Se movio 1 paso hacia arriba o abajo
	{
		if (*mov_doble)
			return FALSO;
	}
	else if ((coord_actual[0] - coord_sgte[0]) == 2) // Se movio 2 pasos hacia arriba
	{
		*mov_doble = VERDADERO;

		if (turno == TURNO_BLANCAS)
		{
			if (aux[coord_actual[0] - '0' - 1][coord_actual[1] - '0'] != CHAR_NEGRO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_actual[0] - 1;
				coord_comido[1] =  coord_actual[1];
			}
		}
		else
		{
			if (aux[coord_actual[0] - '0' - 1][coord_actual[1] - '0'] != CHAR_BLANCO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_actual[0]  - 1;
				coord_comido[1] =  coord_actual[1] ;
			}
		}
	}
	else if ((coord_actual[0] - coord_sgte[0]) == -2) // Se movio 2 pasos hacia abajo
	{
		*mov_doble = VERDADERO;

		if (turno == TURNO_BLANCAS)
		{
			if (aux[coord_actual[0] - '0' + 1][coord_actual[1] - '0'] != CHAR_NEGRO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_actual[0]  + 1;
				coord_comido[1] = coord_actual[1] ;
			}
		}
		else
		{
			if (aux[coord_actual[0] - '0' + 1][coord_actual[1] - '0'] != CHAR_BLANCO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_actual[0]+1;
				coord_comido[1] =  coord_actual[1];
			}
		}
	}
	else // Si se mueve una distancia mayor entonces está mal
	{
		return FALSO;
	}

	return VERDADERO;
}

/* Verifica si el movimiento HORIZONTAL es valido
 * Utilizado en la funcion: revisar_Semantica_Y_Carga()
 * Parametros:
 *	aux[5][6] 			-> matriz auxiliar donde se realizan las pruebas de movimiento
 * 	coord_actual[3] 	-> contiene la posicion de la ficha que se quiere mover
 * 	char coord_sgte[3] 	-> contiene la posicion a la que se quiere llegar
 * 	coord_comido[3]		-> incialmente vacio; se modifica si hay alguna ficha entre coord_actual y coord_sgte
 * 	&mov_doble			-> 	FALSO 	  -> la cadena debe ser unicamente de 1 movimiento
 * 			  				VERDADERO -> la cadena es de +1 movimiento
 * Return:
 * 	FALSO 		-> si la ficha no puede realizar el movimiento sobre el eje x
 * 	VERDADERO   -> si la ficha puede realizar el movimiento sobre el eje x
 */
int mov_eje_X(unsigned char aux[5][6], char coord_sgte[3], char coord_comido[3], char coord_actual[3], int *mov_doble)
{
	if(abs(coord_actual[1] - coord_sgte[1]) == 1) // Se movio 1 paso hacia la izquierda o derecha
	{
		if (*mov_doble)
			return FALSO;
	}
	else if ((coord_actual[1] - coord_sgte[1]) == 2) // Se movio 2 pasos hacia la izquierda
	{
		*mov_doble = VERDADERO;

		if (turno == TURNO_BLANCAS)
		{
			if (aux[coord_actual[0] - '0'][coord_actual[1] - '0' - 1] != CHAR_NEGRO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_actual[0];
				coord_comido[1] =  coord_actual[1]-1;
			}
		}
		else
		{
			if (aux[coord_actual[0] - '0'][coord_actual[1] - '0' - 1] != CHAR_BLANCO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_actual[0];
				coord_comido[1] =  coord_actual[1]-1;
			}
		}
	}
	else if ((coord_actual[1] - coord_sgte[1]) == -2) // Se movio 2 pasos hacia la derecha
	{
		*mov_doble = VERDADERO;

		if (turno == TURNO_BLANCAS)
		{
			if (aux[coord_actual[0] - '0'][coord_actual[1] - '0' + 1] != CHAR_NEGRO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_actual[0];
				coord_comido[1] =  coord_actual[1]+1;
			}
		}
		else
		{
			if (aux[coord_actual[0] - '0'][coord_actual[1] - '0' + 1] != CHAR_BLANCO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_actual[0];
				coord_comido[1] =  coord_actual[1]+1;
			}
		}
	}
	else // Si se mueve una distancia mayor entonces está mal
	{
		return FALSO;
	}

	return VERDADERO;
}

/* Se copia en aux[5][6] el movimiento realizado
 * Utilizado en la funcion: revisar_Semantica_Y_Carga()
 * Parametros:
 *	aux[5][6] 			-> matriz auxiliar donde se realizan las pruebas de movimiento
 * 	coord_actual[3] 	-> contiene la posicion de la ficha que se quiere mover
 * 	char coord_sgte[3] 	-> contiene la posicion a la que se quiere llegar
 * 	coord_comido[3]		-> incialmente vacio (\0); se modifica si hay alguna ficha entre coord_actual y coord_sgte
 * 	&mov_doble			-> 	FALSO 	  -> la cadena debe ser unicamente de 1 movimiento
 * 			  				VERDADERO -> la cadena es de +1 movimiento
 * Return: nada (void)
 */
void cargar_movEn_aux(unsigned char aux[5][6], char coord_sgte[3], char coord_comido[3], char coord_actual[3], int *mov_doble,int *aux_fichasBlancas,int *aux_fichasNegras)
{
	aux[coord_actual[0] - '0'][coord_actual[1] - '0'] = CHAR_VACIO;

	if (turno == TURNO_BLANCAS)
		aux[coord_sgte[0] - '0'][coord_sgte[1] - '0'] = CHAR_BLANCO;
	else
		aux[coord_sgte[0] - '0'][coord_sgte[1] - '0'] = CHAR_NEGRO;

	if (*mov_doble && coord_comido[0] != '\0' && coord_comido[1] != '\0')
	{
		aux[coord_comido[0] - '0'][coord_comido[1] - '0'] = CHAR_VACIO;
		if(turno == TURNO_BLANCAS)
			(*aux_fichasNegras)--;
		else
			(*aux_fichasBlancas)--;
	}
}

/* Si llegamos al final de la cadena str_respuesta, se copia en tablero[5][6] tdo el contenido de aux[5][6]
 * Utilizado en la funcion: revisar_Semantica_Y_Carga()
 * Parametros:
 *	aux[5][6] 			-> matriz auxiliar donde se realizan las pruebas de movimiento
 * 	&str_respuesta		-> direccion de str_respuesta (cadena con la jugada entera)
 * Return:
 * 	FALSO: si todavia no se llego al final de la cadena str_respuesta
 * 	VERDADERO: si ya se llego al final de la cadena str_respuesta. Se utiliza para salir del while de revisar_Semantica_Y_Carga()
 */
int cargar_auxEn_tablero(unsigned char aux[5][6], char *str_respuesta)
{
	if(*str_respuesta == '\n')
	{

		for(int i = 0; i < 5; i++)
			strncpy(tablero[i], aux[i], 5);

		// Si llegamos hasta aca y no dio FALSO en ningun lugar, entonces tdo esta correcto y
		// mandamos VERDADERO para que salga del while
		return VERDADERO;
	}
	else
		return FALSO; // Todavia no se llego al final de la cadena str_respuesta
}

/* Busca si existe algun movimiento invalido dentro de la cadena que contiene la jugada (lo que apunta str_respuesta)
 * Si el movimiento analizado es valido, entonces carga a la matriz auxiliar la jugada
 * Si no es posible, entonces no carga nada a la matriz y devuelve FALSO
 * Si se llega sin problemas al final de la cadena que contiene la jugada, entonces se copian todos los elementos de la matriz
 * auxiliar a tablero[5][6] (global) mediante la funcion cargar_movEn_tablero()
 * Parametros:
 *  char *str_respuesta -> contiene la cadena con la jugada ingresada
 * Return: tipo int
 * 	FALSO (0) -> si se encuentra algun movimiento invalido dentro de lo que apunta str_respuesta
 * 	VERDADERO (1) -> si todos los movimientos dentro de lo que apunta str_respuesta son validos
 */
int revisar_Semantica_Y_Carga(char *str_respuesta)
{
	// Matriz auxiliar que contendra el tablero con sus ultimos cambios
    unsigned char aux[5][6];
    
    int aux_fichasNegras = 0, aux_fichasBlancas = 0;

    /* mov_doble: FALSO -> la cadena debe ser unicamente de 1 movimiento
     * 			  VERDADERO -> la cadena es de +1 movimiento
     * diagonalPitagoras: 2 -> movimiento de un solo paso
     * 					  8 -> movimiento de doble paso
     * mov_diag_habilitado: FALSO -> la ficha en coord_actual no puede moverse en diagonal
     * 						VERDADERO -> la ficha en coord_actual puede moverse en diagonal
     */
    int mov_diag_habilitado = FALSO, mov_doble = FALSO, diagonalPitagoras;

    /* Con respecto a la matriz aux[5][6] y la cadena a la que apunta str_respuesta:
     * 	coord_actual[3]: cadena de 3 elementos que contendra la posicion actual de la cadena que apunta str_respuesta
     * 	coord_sgte[3]: cadena de 3 elementos que contendra la posicion del primer/unico movimiento de la cadena que apunta str_respuesta
     * 	coord_comido[3]: cadena de 3 elementos que contendra la posicion de la ficha que ha sido comida
	 */
    char coord_actual[3], coord_sgte[3], coord_comido[3];
    coord_actual[2] = coord_sgte[2] = coord_comido[2] = '\0';

    // Copiamos el contenido de cada fila de tablero a las filas de aux
	for (int i = 0; i < 5; i++)
		strncpy(aux[i], tablero[i], 6);

	// Se almacena en coord_actual la posicion actual de la ficha
    strncpy(coord_actual, str_respuesta, 2*sizeof(char));

    // Cambiamos donde apunta str_respuesta a donde empieza el 1er movimiento
    str_respuesta += 3;

    // Se almacena en coord_sgte el primer/unico movimiento de str_respuesta
    strncpy(coord_sgte, str_respuesta, 2);

    // Se analiza cada movimiento de la cadena apuntada por str_respuesta
    // Apenas se encuentra un movimiento invalido y sale de la funcion devolviendo FALSO
    while (VERDADERO)
    {
    	// Reseteo de variables
        mov_diag_habilitado = FALSO;
        coord_comido[0] = coord_comido[1] = '\0';

        // Verifica si la ficha seleccionada (mediante la posicion) es del color del jugador cuyo turno corresponde
        if ( !(coincide_ficha_turno(aux, coord_actual)) )
        	return FALSO;

        // Verificamos si existe movimiento, es decir, si es que el primer movimiento es distinto a la posicion actual
        if (coord_actual[0] == coord_sgte[0] && coord_actual[1] == coord_sgte[1])
            return FALSO;

        // Verificamos si el espacio al que se quiere mover esta vacio
        if (aux[coord_sgte[0] - '0'][coord_sgte[1] - '0'] != ' ')
            return FALSO;

        /* Verificamos si la ficha actual se encuentra en la diagonal principal, secundaria o en uno de los puntos
         * medios de los lados. Si se cumple una de las condiciones, tiene habilitado para moverse en todas las direcciones
         * Si ninguno se cumple, entonces la ficha solo se puede mover horizontal y verticalmente.
         */
        if (coord_actual[0] == coord_actual[1] || (coord_actual[0]-'0' + coord_actual[1] - '0') == 4 ||
        		(coord_actual[0] == '0' && coord_actual[1] == '2') || (coord_actual[0] == '2' && coord_actual[1] == '0') ||
						(coord_actual[0] == '2' && coord_actual[1] == '4') || (coord_actual[0] == '4' && coord_actual[1] == '2'))
            mov_diag_habilitado = VERDADERO;

        // Se verifica si el movimiento es diagonal
        if (coord_actual[0] != coord_sgte[0] && coord_actual[1] != coord_sgte[1])
            if (!mov_diag_habilitado)
                return FALSO;
            else // Para lo sgte. damos por hecho de que la ficha actual puede realizar un movimiento en diagonal en su posicion actual
            {
                // Si la diagonal por pitagoras da 2 significa que son catetos de lado 1, si da 8 son catetos de lado 2,
            	// cualquier otro numero es invalido
                diagonalPitagoras = (int) (pow(coord_sgte[0]- coord_actual[0] , 2) + pow(coord_sgte[1] - coord_actual[1], 2));

                // Si el sgte movimiento es de un solo paso y el movimiento anterior fue de doble paso, entonces la jugada es invalida
                if(diagonalPitagoras == 2) // Movimiento de un solo paso (si el cuadrado de la distancia es un 2)
                {
                	if (mov_doble) // Si anteriormente ya se hizo un movimiento doble
                		return FALSO;
                }
                else if (diagonalPitagoras == 8) // Movimiento de doble paso (si el cuadrado de la distancia es un 8)
                {
                    mov_doble = VERDADERO;

                    // Se buscan movimientos diagonales INVALIDOS
                    // Como diagonalPitagoras == 8, sabemos que entre coord_sgte y coord_actual hay una ficha

                    if ( !(mov_diagonal_cuadrantes(aux, coord_actual, coord_sgte,coord_comido)) )
                    	return FALSO;

                }
                else
                	return FALSO;
            }
        // Se verifica si el movimiento es sobre el eje x o y
        else if (coord_actual[0] != coord_sgte[0]) // Movimiento sobre el eje Y
        {
            if ( !(mov_eje_Y(aux, coord_sgte, coord_comido, coord_actual, &mov_doble)) )
            	return FALSO;
        }
        else // Movimiento sobre el eje X
        {
        	if ( !(mov_eje_X(aux, coord_sgte, coord_comido, coord_actual, &mov_doble)) )
        		return FALSO;
        }

        

        // Al llegar hasta aqui, sabemos que el movimiento es valido
        // Por lo tanto, cargamos el movimiento en aux
        cargar_movEn_aux(aux, coord_sgte, coord_comido, coord_actual, &mov_doble, &aux_fichasBlancas, &aux_fichasNegras);

        // Nos movemos 2 caraceteres por delante, el cual puede ser una, o un enter
        str_respuesta += 2;

        // En el caso de que mov_doble sea falso, significa que no puede existir otro movimiento
        // Despues del primero, por lo que si el siguiente caracter es una coma en lugar de
        // un enter, directamente la jugada es inválida
        if(*str_respuesta == ',' && mov_doble == FALSO)
            return FALSO;

        // Si llegamos al final de la cadena, salimos del while; caso contrario, se continua analizando la sgte. jugada
        // Se carga a la matriz trablero (original) la jugada entera
        if (cargar_auxEn_tablero(aux, str_respuesta)){
        	fichasNegras += aux_fichasNegras;
        	fichasBlancas += aux_fichasBlancas;
        	break;
        }


        // Copiamos el valor del siguiente en el actual, ya que es ahi
        // donde se encuentra actualmente nuestra ficha
        strcpy(coord_actual, coord_sgte);

        // Verificamos que el siguiente termino, el cual debe ser o una coma o un enter
        str_respuesta++;

        // Cargamos la sgte posicion de str_respuesta a coord_sgte
        strncpy(coord_sgte, str_respuesta, 2);
    }
    return VERDADERO;
}

/* Revisa si la sintaxis de la cadena ingresada es correcta
 * Ej. de cadena valida: 33:21,20,11,05
 * Utilizada en la funcion: pedirJugada()
 * Parametros:
 * 	char* str -> apunta a la cadena ingresada cuya sintaxis se quiere revisar
 * Return: tipo int
 * 	FALSO (0) -> si hay un error en la estructura de la cadena ingresada
 * 	VERDADERO (1) -> si la estructura de la cadena es completamente valida
 */
int revisar_Syntax_Cad(char* str)
{
    if(strlen(str) < 5) // El minimo es de 5 posiciones en la cadena apuntada por str. Debe haber al menos 1 movimiento
        return FALSO;

    char tempStr[3];
    tempStr[2] = '\0';

    /* Se recorre la cadena enterar (hasta \0) verificando si todos los caracteres != ',', != '\n' y != ':'
     * sean numeros y si estos estan entre 0 y 4 inclusive
     * Se utiliza aritmetica de punteros (str++) para recorres la cadena hasta el \0
     */
    do
    {
        strncpy(tempStr, str, 2);

        // Se revisa si los dos caracteres de tempStr son numeros.
        // Si esto no se cumple, la cadena es invalida y se retorna FALSO
        if(isNumeric(tempStr) == FALSO)
            return FALSO;

        // Se revisa si cada caracter/numero de tempStr estan dentro del rango establecido
        // Si no se cumple, la cadena es invalida y se retorna FALSO
        if(dentroRangoInclusive( (int)(*str++ - '0'), 0, 4) == FALSO || dentroRangoInclusive((int)(*str++ - '0'), 0, 4) == FALSO)
            return FALSO;

        if(*str != ',' && *str != '\n' && *str != ':')
            return FALSO;

        str++;
    }
    while(*str != '\0');

    return VERDADERO;
}

/* Pide al jugador una cadena que contenga su posicion actual y su jugada
 * Se debe respetar la estructura de la cadena jugada. Ej. de cadena correcta: 41:13,11,43 (termina con enter)
 * Utilizada en la funcion: play()
 * Parametros: nada
 * Return: tipo *char
 * 	 str_respuesta -> cadena cuya estructura es valida
 */
char *pedirJugada()
{
    int esInvalido = VERDADERO; // Bandera para el do-while
    char * str_respuesta = NULL; // Para almacenar la cadena ingredasa por teclado
    size_t str_size = 0; // Tamaño de str_respuesta. Solo se utilizada como parametro de getline()

    do
    {
        printf("Jugada fichas %s: ", turno == TURNO_BLANCAS ? "blancas" : "negras");
        getline(&str_respuesta, &str_size, stdin);

        // Si ambos son verdaderos, entonces la cadena es completamente valida y se puede realiza la jugada;
        // caso contrario, se vuelve a solicitar la cadena
        if (revisar_Syntax_Cad(str_respuesta) == VERDADERO)
        {
            if(revisar_Semantica_Y_Carga(str_respuesta) == VERDADERO)
                esInvalido = FALSO;
            else
                puts("\nERROR: Jugada invalida.\n");
        }
        else
            puts("\nERROR: Sintaxis invalida.\n");
    }
    while(esInvalido);

    return str_respuesta;
}

/* Se genera la cadena que contiene la jugada de la PC
 * Parametros: nada
 * Return:
 * 	direccion de char * str_cad_pc
 */
void generarJugadaPC()
{
//	char  str_cad_pc[7], coord_sgte[3], coord_actual[3];
//
//
//	str_cad_pc[2] = ':';
//	str_cad_pc[6] = coord_sgte[2] = coord_actual[2] = '\0';
//	str_cad_pc[5] = '\n';
//
//	do
//	{
//		coord_actual[0] = rand () % 5; // 0 a 4
//		coord_actual[1] = rand () % 5;
//
//		// Para filas y columnas -> entre M: coord_actual[0] - '0' - 2
//		//							y	  N: coord_actual[0] - '0' + 2
//		coord_sgte[0] = coord_actual[0] + (rand () % 2 ? 1 : -1) * rand () % 3;
//		coord_sgte[1] = coord_actual[1] + (rand () % 2 ? 1 : -1) * rand () % 3;
//
//		strncpy(str_cad_pc, coord_actual, 2*sizeof(char));
//		str_cad_pc[3] = coord_sgte[0];
//		str_cad_pc[4] = coord_sgte[1];
//
//
//		if (revisar_Syntax_Cad(str_cad_pc) && revisar_Semantica_Y_Carga(str_cad_pc))
//			break;
//	}
//	while (VERDADERO);

	char jugadaRandom[7];
	do{
		jugadaRandom[0] = '0' + rand()%5;
		jugadaRandom[1] = '0' + rand()%5;

		jugadaRandom[2] = ':';

		jugadaRandom[3] = '0' + rand()%5;
		jugadaRandom[4] = '0' + rand()%5;
		jugadaRandom[5] = '\n';
		jugadaRandom[6] = '\0';
		if(revisar_Semantica_Y_Carga(jugadaRandom))
			break;
	}while(VERDADERO);
	printf("Jugada de la pc con las fichas %s: %s",turno == TURNO_BLANCAS? "blancas":"negras", jugadaRandom);

}

/* Se empieza a jugar. Se dan los turno de cada jugador
 * Utilizado en la funcion: main()
 * Parametros: nada
 * Return: nada (es void)
 */
void play()
{
    // fichasBlancas y fichasNegras: numero de turnos para cada jugador
	// victoria: bandera para el do-while
	fichasBlancas = 12, fichasNegras = 12;
	char victoria = SIN_VICTORIA;

	// Se repetira el proceso hasta que se acabe la cantidad de fichas de uno de los jugadores
	printTable();
	do
	{


		// Turno de la PC
        if ((turno == TURNO_BLANCAS && jBlanco == PC) || (turno == TURNO_NEGRAS && jNegro == PC))
        {
        	generarJugadaPC();
        }
        else // Turno de la persona (si es multiplayer, se utiliza para ambas personas)
        {
        	pedirJugada();
        }
        printTable();
		turno = !turno; // Invertimos el valor de turno para que el sgte. jugador juegue
	}
	while ((victoria = askVictory()) == SIN_VICTORIA);

	printf("\nHa ganado el jugador con fichas %s!!!\n", victoria == VICTORIA_BLANCAS ? "blancas" : "negras");
}

int main(void)
{
	srand(time(NULL));
	do
	{
		resetTablero();
		chooseMode();
		play();
	}
	while (askPlayAgain() == PLAY_AGAIN);
}
