
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


#define TRUE 1
#define FALSE 0

#define SIN_ERROR 0
#define SIN_JUGADOR 1
#define ER_SINTAXIS 2 //mal escrito, faltan datos y cosas similares
#define ER_SEMANTICA 3 //bien escrito pero sin el significado correcto, como por ejemplo hacer un [10,1] en un juego

const char * bienvenidaJuego =
"                                                                                                               \n\n"
"    /$$ /$$$$$$$  /$$                                                    /$$       /$$     /$$$$$$     /$$       \n"
"   |__/| $$__  $$|__/                                                   |__/      | $$   /$$$__  $$$  | $$       \n"
"       | $$  \\ $$ /$$  /$$$$$$  /$$$$$$$  /$$    /$$  /$$$$$$  /$$$$$$$  /$$  /$$$$$$$  /$$_/  \\_  $$ | $$     \n"
"    /$$| $$$$$$$ | $$ /$$__  $$| $$__  $$|  $$  /$$/ /$$__  $$| $$__  $$| $$ /$$__  $$ /$$/ /$$$$$  $$| $$       \n"
"   | $$| $$__  $$| $$| $$$$$$$$| $$  \\ $$ \\  $$/$$/ | $$$$$$$$| $$  \\ $$| $$| $$  | $$| $$ /$$  $$| $$|__/    \n"
"   | $$| $$  \\ $$| $$| $$_____/| $$  | $$  \\  $$$/  | $$_____/| $$  | $$| $$| $$  | $$| $$| $$\\ $$| $$        \n"
"   | $$| $$$$$$$/| $$|  $$$$$$$| $$  | $$   \\  $/   |  $$$$$$$| $$  | $$| $$|  $$$$$$$| $$|  $$$$$$$$/ /$$      \n"
"   |__/|_______/ |__/ \\_______/|__/  |__/    \\_/     \\_______/|__/  |__/|__/ \\_______/|  $$\\________/ |__/  \n"
"                                                                                      \\  $$$   /$$$             \n"
"                                                                                        \\_  $$$$$$_/            \n"
"                                                                                          \\______/              \n";

//typedef struct string
//{
//	char* ptr;
//	size_t len;
//	size_t size;
//}
//string;

typedef struct player
{
	unsigned int juego[11][2];
	int puntaje;
	unsigned int error;
}
player;

int N = 0;
player jugador[10];

int dentroRangoInclusive(int num, int min, int max)
{
	if (num <= max && num >= min)
		return TRUE;
	else
		return FALSE;
}

void bienvenida()
{
	printf("%s\nSe calculara el ganador del Bowling. Ingrese los siguientes datos.\n\n", bienvenidaJuego);
	return;
}


//le meto la cadena "314 = 300 + 10 + 4
int stringToInt(char* cadena,int len)
{
	int resultado = 0;
	for(len--;len>=0;len--)
	{
	   resultado += (int)(*cadena - '0') * (int)pow(10,len);
	    cadena++;
	}

	return resultado;
}

/***
// Se verifica si la cadena apuntada por jugada.ptr es valida o no
// Se modifica jugador[i].error si se detecta algun error de sintaxis o semantica en la cadena apuntada por jugada.ptr

void cargaYVerificacionError(string jugada, int i)
{
	char * cad_aux = jugada.ptr;

	// Vector en el que se almacenara cada juego de la cadena que se ingrese
	char aux_un_juego[6];
	aux_un_juego[6] = '\0';

	// Vector utilizado para almacenar un par de caracteres de aux_un_juego
	// Se utilizaran estos caracteres para verificar si la suma entre dos numeros
	char num_aux[2];
	num_aux[2] = '\0';

	int habilitar_once = FALSE;

	// Si el primer caracter de la cadena no es [, hay un error de sintaxis
	if(jugada.ptr[0] != '[')
	{
		jugador[i].error = ER_SINTAXIS;
	}
	else // El primer caracter de la cadena es [
	{
		// En la cadena ingresada (ahora apuntada por cad_aux), recorremos los 11 juegos que tiene
		for (int j = 0; j < 11; j++)
		{
			// Copiamos los primeros 6 caracteres de cad_aux a aux_un_juego
			strncpy(aux_un_juego, cad_aux, 6); // copiamos el juego (solo un conjunto de [..,..]) correspondiente de cad_aux a aux_un_juego

			// Cambia el caracter al que apunta cad_aux dependiendo de lo que contenga aux_un_juego[5]
			if (aux_un_juego[5] == '[')
				cad_aux += 5;
			else if (aux_un_juego[5] == ']' ||(j==10 && aux_un_juego[5] == '\n'))
				cad_aux += 6;
			else
				jugador[i].error = ER_SINTAXIS;

			// Recorremos aux_un_juego que contiene un juego de la forma: [1,0][, [0,10] o [10,0]
			// Se buscan errores de sintaxis y semantica
			for (int m = 1; m < 6; m++)
			{
				habilitar_once = FALSE;
				if (aux_un_juego[2] != ',' && aux_un_juego[3] != ',')
				{
					jugador[i].error = ER_SINTAXIS;
				}
				else if (aux_un_juego[2] == ',') // caso: aux_un_juego --> [1,0][ o [0,10]
				{
					if (aux_un_juego[5] == '[' && aux_un_juego[4] == ']') // [1,0][
					{
						if (isdigit(aux_un_juego[1]) && isdigit(aux_un_juego[3])) // Si ambos son numeros, se verfica su suma
						{
							if (j == 10) // en caso de que estemos en el ultimo juego (11): si el juego 10 no suma 10 puntos, el juego 11 debe sumar 0
							{
								if (habilitar_once)
								{
									if (((aux_un_juego[1]-'0') + (aux_un_juego[3]-'0')) > 10 || (aux_un_juego[1]-'0') + (aux_un_juego[3]-'0') < 0)
									{
										jugador[i].error = ER_SEMANTICA;
										break;
									}
								}
								else
								{
									if (((aux_un_juego[1]-'0') + (aux_un_juego[3]-'0')) != 0)
									{
										jugador[i].error = ER_SEMANTICA;
										break;
									}
								}
							}
							else if (j == 9)
							{
								// Si la suma de ambos numeros es ==10 en el juego 10, se habilita el juego 11
								if ((aux_un_juego[1]-'0') + (aux_un_juego[3]-'0') == 10)
								{
									habilitar_once = TRUE;
								}
								else
								{
									if ((aux_un_juego[1]-'0') + (aux_un_juego[3]-'0') > 10 || (aux_un_juego[1]-'0') + (aux_un_juego[3]-'0') < 0)
									{
										jugador[i].error = ER_SEMANTICA;
										break;
									}
								}
							}
							else
							{
								// Si la suma de ambos numeros es >10 o <0, hay error de semantica
								if ((aux_un_juego[1]-'0') + (aux_un_juego[3]-'0') > 10 || (aux_un_juego[1]-'0') + (aux_un_juego[3]-'0') < 0)
								{
									jugador[i].error = ER_SEMANTICA;
									break;
								}
							}
						}
						else // Si alguno no es un numero, se modifica error
						{
							jugador[i].error = ER_SINTAXIS;
							break;
						}
					}
					else if (aux_un_juego[5] == ']') // [0,10]
					{
						if (isdigit(aux_un_juego[1]) && isdigit(aux_un_juego[3]) && isdigit(aux_un_juego[4])) // Si todos son numeros, se verfica su suma
						{
							num_aux[0] = aux_un_juego[3];
							num_aux[1] = aux_un_juego[4];
							if (j == 10) // en caso de que estemos en el ultimo juego (11): si el juego 10 no suma 10 puntos, el juego 11 debe sumar 0
							{
								if (habilitar_once)
								{
									if ((aux_un_juego[1]-'0') + stringToInt(num_aux, 2) > 10 || (aux_un_juego[1]-'0') + stringToInt(num_aux, 2) < 0)
									{
										jugador[i].error = ER_SEMANTICA;
										break;
									}
								}
								else
								{
									if ((aux_un_juego[1]-'0') + stringToInt(num_aux, 2) != 0)
									{
										jugador[i].error = ER_SEMANTICA;
										break;
									}
								}
							}
							else if (j == 9)
							{
								// Si la suma de ambos numeros es ==10 en el juego 10, se habilita el juego 11
								if ((aux_un_juego[1]-'0') + stringToInt(num_aux, 2) == 10)
								{
									habilitar_once = TRUE;
								}
								else
								{
									if ((aux_un_juego[1]-'0') + stringToInt(num_aux, 2) > 10 || (aux_un_juego[1]-'0') + stringToInt(num_aux, 2) < 0)
									{
										jugador[i].error = ER_SEMANTICA;
										break;
									}
								}
							}
							else
							{
								// Si la suma de ambos numeros es >10 o <0, hay error de semantica
								if ((aux_un_juego[1]-'0') + stringToInt(num_aux, 2) > 10 || (aux_un_juego[1]-'0') + stringToInt(num_aux, 2) < 0)
								{
									jugador[i].error = ER_SEMANTICA;
									break;
								}
							}
						}
						else // Si alguno no es un numero, se modifica error
						{
							jugador[i].error = ER_SINTAXIS;
							break;
						}
					}
					else
					{
						jugador[i].error = ER_SINTAXIS;
						break;
					}
				}
				else if (aux_un_juego[3] == ',') // caso: aux_un_juego --> [10,0]
				{
					if (aux_un_juego[5] == ']')
					{
						if (isdigit(aux_un_juego[1]) && isdigit(aux_un_juego[2]) && isdigit(aux_un_juego[4])) // si alguno no es un numero, se modifica error
						{
							num_aux[0] = aux_un_juego[1];
							num_aux[1] = aux_un_juego[2];
							if (j == 10) // en caso de que estemos en el ultimo juego (11): si el juego 10 no suma 10 puntos, el juego 11 debe sumar 0
							{
								if (habilitar_once)
								{
									if ((aux_un_juego[3]-'0') + stringToInt(num_aux, 2) > 10 || (aux_un_juego[3]-'0') + stringToInt(num_aux, 2) < 0)
									{
										jugador[i].error = ER_SEMANTICA;
										break;
									}
								}
								else
								{
									if ((aux_un_juego[3]-'0') + stringToInt(num_aux, 2) != 0)
									{
										jugador[i].error = ER_SEMANTICA;
										break;
									}
								}
							}
							else if (j == 9)
							{
								// Si la suma de ambos numeros es ==10 en el juego 10, se habilita el juego 11
								if ((aux_un_juego[3]-'0') + stringToInt(num_aux, 2) == 10)
								{
									habilitar_once = TRUE;
								}
								else
								{
									if ((aux_un_juego[3]-'0') + stringToInt(num_aux, 2) > 10 || (aux_un_juego[3]-'0') + stringToInt(num_aux, 2) < 0)
									{
										jugador[i].error = ER_SEMANTICA;
										break;
									}
								}
							}
							else
							{
								// Si la suma de ambos numeros es >10 o <0, hay error de semantica
								if ((aux_un_juego[3]-'0') + stringToInt(num_aux, 2) > 10 || (aux_un_juego[3]-'0') + stringToInt(num_aux, 2) < 0)
								{
									jugador[i].error = ER_SEMANTICA;
									break;
								}
							}
						}
						else
						{
							jugador[i].error = ER_SINTAXIS;
							break;
						}
					}
				}
				else
				{
					jugador[i].error = ER_SINTAXIS;
					break;
				}
			}
		}
	}
}

***/

void cleanBuffer()
{
    char c;
    while ((c = getchar()) != '\n');
}

void pedirJugadas()
{
	int i = 0, retScanf;
//	string jugada;
//	jugada.ptr = NULL;
//	jugada.size = 1;
//	jugada.len = 0;
	//Recibir cada jugada realizada y filtrarla en caso de fallo
	for( ; i < N; i++)
	{
		jugador[i].error = SIN_ERROR;
		printf("Ingrese los puntos obtenidos por el jugador %i: ", i+1);

		retScanf = scanf("[%i,%i][%i,%i][%i,%i][%i,%i][%i,%i][%i,%i][%i,%i][%i,%i][%i,%i][%i,%i][%i,%i]",&jugador[i].juego[0][0],&jugador[i].juego[0][1],&jugador[i].juego[1][0],
				&jugador[i].juego[1][1],&jugador[i].juego[2][0],&jugador[i].juego[2][1],&jugador[i].juego[3][0],&jugador[i].juego[3][1],&jugador[i].juego[4][0],&jugador[i].juego[4][1],
				&jugador[i].juego[5][0],&jugador[i].juego[5][1],&jugador[i].juego[6][0],&jugador[i].juego[6][1],&jugador[i].juego[7][0],&jugador[i].juego[7][1],&jugador[i].juego[8][0],
				&jugador[i].juego[8][1],&jugador[i].juego[9][0],&jugador[i].juego[9][1],&jugador[i].juego[10][0],&jugador[i].juego[10][1],&jugador[i].juego[11][0],&jugador[i].juego[11][1]);

		cleanBuffer();

		if(retScanf != 22)
			jugador[i].error = ER_SINTAXIS;
		else
		{
			for(int m = 0; m < 10; m++)
			{
				if (jugador[i].juego[m][0] < 0 || jugador[i].juego[m][1] < 0 || jugador[i].juego[m][0] > 10 || jugador[i].juego[m][1] > 10 || (jugador[i].juego[m][0] + jugador[i].juego[m][1] > 10))
				{
					jugador[i].error = ER_SEMANTICA;
					break;
				}
			}
			// Si hay chuza en el decimo lanzamiento, revisamos si son validos los valores del decimoprimer lanzamiento
			if (jugador[i].juego[9][0] == 10)
			{
				if((jugador[i].juego[10][0] < 0 || jugador[i].juego[10][1] < 0) || (jugador[i].juego[10][0] > 10 || jugador[i].juego[10][1] > 10) || (jugador[i].juego[10][0] + jugador[i].juego[10][1] > 10))
				{
					jugador[i].error = ER_SEMANTICA;
					continue;
				}

			}
			else if (jugador[i].juego[9][0] + jugador[i].juego[9][1] == 10)
			{
				if (jugador[i].juego[10][0] < 0 || jugador[i].juego[10][0] > 10 || jugador[i].juego[10][1] != 0)
				{
					jugador[i].error = ER_SEMANTICA;
					continue;
				}
			}
			else
			{
				if (jugador[i].juego[10][0] != 0 || jugador[i].juego[10][1] != 0)
				{
					jugador[i].error = ER_SEMANTICA;
					continue;
				}
			}
		}
	}
	//Asignar a cada todo elemento del vector que no sea necesario como "SIN JUGADOR"
	for( ; i < 10; i++)
		jugador[i].error = SIN_JUGADOR;
}

void recibirNroJugadores()
{
	int returnScanf, nValidado = FALSE;
	//Solicitar N para saber cuantas personas han jugado
	do
	{
		printf("Numero de jugadores: ");
		returnScanf = scanf("%i",&N);
		cleanBuffer();

		if(returnScanf == 1 && dentroRangoInclusive(N,2,10))
			nValidado = TRUE;
		else if(returnScanf != 1)
			printf("\nERROR: INGRESE UN NUMERO ENTERO\n\n");
		else
			printf("\nERROR: INGRESE UN NUMERO ENTRE 2 Y 10\n\n");

	}
	while(!nValidado);
}

void calcularPuntajes()
{
	//Recorremos cada jugador para calcular su puntaje
	for(int i = 0; i<N;i++)
	{
		if(jugador[i].error != SIN_ERROR)
			continue;
		//Recorremos cada juego del jugador para calcular su puntaje
		for(int j = 0;j<10;j++)
		{

			jugador[i].puntaje += (jugador[i].juego[j][0] + jugador[i].juego[j][1]); //sumamos lo que sea que haya conseguido
																					//en la jugada j
			//verificamos que sea chuza
			if(jugador[i].juego[j][0] == 10)
			{
				//Si la jugada es anterior al decimo juego
				if(j < 9)
				{
					if(jugador[i].juego[j+1][0] != 10)
						jugador[i].puntaje += (jugador[i].juego[j+1][0] + jugador[i].juego[j+1][1]);
					else
						jugador[i].puntaje += (jugador[i].juego[j+1][0] + jugador[i].juego[j+2][0]);
				}
				//si es el decimo tiro
				else if(j == 9)
				{
					jugador[i].puntaje +=(jugador[i].juego[10][0] + jugador[i].juego[10][1]);
				}
			}
			//verificamos que sea semi chuza
			else if(jugador[i].juego[j][0] + jugador[i].juego[j][1] == 10)
				jugador[i].puntaje += jugador[i].juego[j+1][0];
		}
	}
}

void printDatos()
{
	int ganadorIndice[11];
	int indice = 0;
	int puntajeMayor = -1;
	puts("");
	for(int i = 0; i < N; i++)
	{
		printf("Jugador %i -> ", i+1);
		switch(jugador[i].error)
		{
			case SIN_ERROR:
				printf("Puntaje: %i\n", jugador[i].puntaje);
				if(jugador[i].puntaje > puntajeMayor)
				{
					indice = 0;
					ganadorIndice[0] = i;
					puntajeMayor = jugador[i].puntaje;
				}
				else if(puntajeMayor == jugador[i].puntaje)
				{
					indice++;
					ganadorIndice[indice] = i;
				}
				break;
			case SIN_JUGADOR:
				break;
			case ER_SINTAXIS:
				puts("ERROR: SINTAXIS INVALIDA");
				break;
			case ER_SEMANTICA:
				puts("ERROR: DATOS NO VALIDOS");
				break;
			default:
				puts("ERROR SIN IDENTIFICAR");
		}
	}
	if (puntajeMayor == -1){
		printf("\n\nNo se ha encontrado ningun jugador con datos valicos, por lo que no se ha podido definir un ganador.");
	}
	else if(indice == 0)
		printf("\n\nFelicidades! El jugador %i ha ganado con %i puntos!", ganadorIndice[0]+1, puntajeMayor);
	else
	{
		printf("\n\nLos jugadores ");
		for(int i = 0;i<=indice; i++)
			printf("%i%s",ganadorIndice[i]+1,i==indice? " ": i == (indice-1) ? " y " : ", ");
		printf("han empatado con %i puntos!",puntajeMayor);
	}
}

int main(void)
{
	bienvenida();
	recibirNroJugadores();
	pedirJugadas();
	calcularPuntajes();
	printDatos();
}
