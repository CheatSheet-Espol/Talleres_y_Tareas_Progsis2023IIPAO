#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

typedef struct nodo {
	short mes;
	short dia;
	short hora;
	float temperatura;
	struct nodo* siguiente;
} nodo_t;

//Variable globale que determina si la opción -c está siendo usada
bool cflag = false; //Opción -c, ignora la línea de cabecera

void recorrer_lista(nodo_t *cabecera);

int main (int argc, char *argv[])
{
	int opt, index;
	char *nombre_archivo = NULL;
	FILE *fp;
	nodo_t *cabecera, *nodo_actual, *nodo_anterior;

	while ((opt = getopt (argc, argv, "ch")) != -1){
		switch(opt)
		{
			case 'c':
				cflag = true;
				break;
			case 'h':
				printf("Lee un archivo tabulado con datos de temperatura.\nUso:\n");
				printf("%s [-c] archivo\n", argv[0]);
				printf("%s -h\n", argv[0]);
				printf("Opciones:\n");
				printf(" -h\tAyuda, muestra este mensaje\n");
				printf(" -c\tArchivo contiene línea cabecera\n");
				return 0;
			case '?':
			default:
				fprintf(stderr, "uso:\t%s [-c] [-h] archivo\n", argv[0]);
				fprintf(stderr, "\t%s -h\n", argv[0]);
				return 1;
		}
	}

	/* Asume que el último argumento sin opción es el nombre de archivo */
	for (index = optind; index < argc; index++)
		nombre_archivo = argv[index];

	if(nombre_archivo == NULL){
		fprintf(stderr, "uso:\t%s [-c] [-h] archivo\n", argv[0]);
		fprintf(stderr, "\t%s -h\n", argv[0]);
		return 1;
	}

	printf("Abriendo el archivo %s",nombre_archivo);
	if(cflag)
		printf(" y asumiendo que tiene cabecera.\n");
	else
		printf(".\n");

	fp = fopen(nombre_archivo,"r");

	/* Valida si pudo abrir el archivo, usa errno para mostrar el error */
	if(fp == NULL){
		fprintf(stderr, "Error al abrir %s: %s\n", nombre_archivo, strerror(errno));
		return 1;
	}

	if(cflag)
		fscanf(fp, "%*[^\n]\n"); //para ignorar la primera línea...

	int n;
	short mes,dia,hora;
	float temperatura;
	nodo_anterior=NULL;		
	//TODO: nodo xyz = null
	do{
		n = fscanf(fp,"%hd\t%hd\t%hd\t%f",&mes,&dia,&hora,&temperatura);
		
		if(n == 4){
			nodo_actual = (nodo_t *) malloc(sizeof(nodo_t));
			nodo_actual->mes = mes;
			nodo_actual->dia = dia;
			nodo_actual->hora = hora;
			nodo_actual->temperatura = temperatura;
			nodo_actual->siguiente = nodo_anterior;
			cabecera = nodo_actual;
			nodo_anterior= nodo_actual;
		}if(n==0){
			fprintf(stderr, "Error al leer datos_con_cabecera.txt",nombre_archivo);
		}
		//TODO: else if 0 fprintf/return1

	}while(n > 0);

	recorrer_lista(cabecera);
}

void recorrer_lista(nodo_t *cabecera)
{
	nodo_t *ptr;
	ptr = cabecera;

	while(ptr != NULL) {
		printf("%hd\t%hd\t%hd\t%.2f\n",ptr->mes,ptr->dia,ptr->hora,ptr->temperatura);
		ptr = ptr->siguiente;
	}
}
