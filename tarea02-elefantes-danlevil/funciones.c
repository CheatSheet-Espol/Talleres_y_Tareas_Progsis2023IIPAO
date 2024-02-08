
    //CalcularPromedio
    //La unica funcion del programa
    //Es utilizada en el main.

#include "funciones.h"
#include <stdio.h>

double calcularPromedioPeso() {
    char *nombreArchivo = "elephants.txt";
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo");
        return 1;
    }

    double suma = 0.0;
    int contador = 0;
    double peso;

    while (fscanf(archivo, "%lf", &peso) == 1) {
        suma += peso;
        contador++;
    }

    fclose(archivo);

    if (contador == 0) {
        fprintf(stderr, "El archivo está vacío o no contiene números.\n");
        return 1;
    }

    return suma / contador;
}
