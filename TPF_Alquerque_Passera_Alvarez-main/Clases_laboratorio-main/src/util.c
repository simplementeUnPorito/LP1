#include <stdio.h>
#include "declarations.h"
/*
 * limpia buffer de entrada
 */
void limpiarBuffer(){
	char a;
	while((a=getchar())!= EOF && a != '\n');
}

/**
 * cual es el numero romano correspondiente
 * - recibe el numero a transformar
 * - retorna la cadena que representa el numero
 */
const char* obtenerRomano(int numero){

	switch(numero){
	case 1:
		return "I";
	case 2:
		return "II";
	case 3:
		return "III";
	case 4:
		return "IV";
	case 5:
		return "V";
	case 6:
		return "VI";
	case 7:
		return "VII";
	case 8:
		return "VIII";
	case 9:
		return "IX";
	case 10:
		return "X";
	}

	return "invalid";
}
