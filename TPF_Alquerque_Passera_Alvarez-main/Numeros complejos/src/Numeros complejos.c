/*
 ============================================================================
 Name        : Numeros.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct complex{
	double real;
	double imaginario;
}complex;

complex suma(complex n1,complex n2){
	complex result;
	result.real = n1.real+n2.real;
	result.imaginario = n1.imaginario + n2.imaginario;
	return result;
}

complex resta(complex n1,complex n2){
	complex result;
	result.real = n1.real-n2.real;
	result.imaginario = n1.imaginario - n2.imaginario;
	return result;
}

complex multiplicar(complex n1, complex n2){
	complex result = {n1.real * n2.real - n1.imaginario * n2.imaginario , n1.real * n2.imaginario + n2.real * n1.imaginario};
	return result;
}

complex dividir(complex n1, complex n2){
	complex result = {(n1.real * n2.real + n1.imaginario * n2.imaginario)/(pow(n2.real,2)+ pow(n2.imaginario,2) ), (n1.imaginario * n2.real - n1.real * n2.imaginario)/(pow(n2.real,2)+ pow(n2.imaginario,2) )};
	return result;
}

complex conjugado(complex n1){
	complex result = {n1.real , -1 * n1.imaginario};
	return result;
}


int main(void) {
	complex a = {1,2} , b = {4,5};
	a = conjugado(a);
}
