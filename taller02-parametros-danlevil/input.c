#include <stdio.h>
#include <stdbool.h>

//Variable global definida en main.c
extern bool eflag;

int get_from_console(char **line)
{
	*line = NULL; //Importante inicializar en NULL 
	size_t n = 0; //Obliga a getline a usar malloc()
	ssize_t l = 0; //Número de caracteres ingresados, incluye '\n'

	if(eflag)
		printf("Input text: ");
	else
		printf("Ingrese texto: ");

	l = getline(line, &n, stdin); //getline llama a malloc internamente

	if(l > 0)
		(*line)[l-1] = '\0'; //Sobreescribe el salto de línea
	else
		return l;

	return l-1;
}
