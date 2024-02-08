#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

void separar_tokens(char *linea, char *delim) {
    char *token;
    int i = 0;

    printf("Separacion en tokens:\n");

    token = strtok(linea, delim);

    while( token != NULL ) {
        printf( "%d. %s\n", ++i, token);
        token = strtok(NULL, delim);
    }
}
void print_help() {
    printf("Uso: ./nombre_del_programa\n");
    printf("Este programa ejecuta comandos ingresados por el usuario.\n");
    printf("Ejemplos de comandos:\n");
    printf("  - ls\n");
    printf("  - pwd\n");
    printf("  - echo Bienvenido a Alexa\n");
    printf("Para salir, ingrese QUIT.\n");
}

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        printf(">> ");
        fgets(input, MAX_INPUT_SIZE, stdin);

        
        input[strcspn(input, "\n")] = 0;

        
        if (strcmp(input, "QUIT") == 0) {
            printf("BYE!\n");
            break;
        }
        if (strcmp(input, "-h") == 0) {
            print_help();
            continue;
        }

       
        pid_t pid = fork();

        if (pid == -1) {
            perror("Error en el fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
           
            char *delim = " ";
            char *token = strtok(input, delim);
            char *args[MAX_INPUT_SIZE];
            int i = 0;

            while (token != NULL) {
                args[i++] = token;
                token = strtok(NULL, delim);
            }

            args[i] = NULL; 
            
            if (execvp(args[0], args) == -1) {
                perror("Error al ejecutar el programa");
                exit(EXIT_FAILURE);
            }
        } else {
            
            wait(NULL);
        }
    }

    return 0;
}