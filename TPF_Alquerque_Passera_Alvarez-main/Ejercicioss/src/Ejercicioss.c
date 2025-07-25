#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *nombreFile;
	char *nombreCompleto;
	char *data;
	size_t bufsize = 0;
	size_t chars_nombreFile, chars_data;
	nombreFile = (char *)malloc(bufsize * sizeof(char));
	data = (char *)malloc(bufsize * sizeof(char));

	if(nombreFile == NULL || data == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}

	FILE *file;
	printf("Nombre del archivo: ");
	chars_nombreFile = getline(&nombreFile, &bufsize, stdin);
	nombreFile[chars_nombreFile-1] = '\0';
	nombreCompleto = strcat(nombreFile, ".txt");

	bufsize = 0;

	// Cargamos los datos ingresados por teclado en el archivo creado cuyo nombre es el ingresado
	file = fopen(nombreCompleto, "w");
	printf("\nDatos: ");
//	chars_data = getline(&data, &bufsize, stdin);
//	data[chars_data] = '\0';
//	data[chars_data-1] = '\0';
//	fwrite(data, strlen(data)*sizeof(char), 1, file);

	char c;
	while ((c = getchar()) != EOF)
	{
//		fwrite(&c, sizeof(char), 1, file);
		putc(c, file);
	}
	fclose(file);

	return EXIT_SUCCESS;
}
