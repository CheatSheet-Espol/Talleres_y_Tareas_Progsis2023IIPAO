#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

//TODO: declarar flags
//Flags del programa, cada flag representa una opcion del programa
bool cflag = false; 
bool fflag = false; 
int min_word_length = 0;
char *filename = NULL;

#define MAXWORD 20

int count_words(char *filename, int size){
	//Apertura del archivo, verificando que exista
    int count = 0;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error al abrir el archivo %s.\n", filename);
        exit(EXIT_FAILURE);
    }
	//Contar las palabras del archivo abierto.
    char word[MAXWORD];
    while (fscanf(file, "%s", word) != EOF) {
        if (strlen(word) >= min_word_length) {
            count++;
        }
    }
	//cerrar el archivo y retornar el conteo de palabras
    fclose(file);
    return count;
}

//imprimir el mensaje de ayuda.
void print_help(char *command){
    printf("Programa en C para contar palabras en un archivo según la longitud mínima especificada.\n");
    printf("Uso: %s [-c N] [-f filename]\n", command);
    printf("     %s -h\n", command);
    printf("Opciones:\n");
    printf("  -c N              Establecer la longitud mínima de las palabras a contar.\n");
    printf("  -f filename       Especificar el nombre del archivo.\n");
    printf("  -h                Mostrar esta ayuda.\n");
}

int main(int argc, char **argv){
	int opt;
	//Opciones c y f con parametros requeridos.
	//verifica todos los casos con un switch
    while ((opt = getopt(argc, argv, "c:f:h")) != -1) {
        switch (opt) {
            case 'c':
                cflag = true;
                min_word_length = atoi(optarg);
                break;
            case 'f':
                fflag = true;
                filename = optarg;
                break;
            case 'h':
                print_help(argv[0]);
                return 0;
            case '?':
            default:
                fprintf(stderr, "Uso: %s [-c N] [-f filename]\n", argv[0]);
                fprintf(stderr, "     %s -h\n", argv[0]);
                return -1;
		}
	}
	
	//validar que opciones con argumentos haya sido ingresados
	if (!cflag || !fflag) {
        fprintf(stderr, "Debe especificar tanto -c como -f.\n");
        return -1;
    }
	
	int count = count_words(filename, min_word_length);
    printf("The number of words with length>=%d in '%s' file is %d.\n", min_word_length, filename, count);


	/* El programa se invocó sin usar opciones o argurmentos */
	if(argc == 1)
		print_help(argv[0]);

	return 0;
}
