#include <getopt.h>
#include <limits.h>

#include "common.h"

void print_help(char *command)
{
	printf("Cliente simple de descarga de archivos.\n");
	printf("uso:\n %s <hostname> <puerto>\n", command);
	printf(" %s -h\n", command);
	printf("Opciones:\n");
	printf(" -h\t\t\tAyuda, muestra este mensaje\n");
}

bool tflag = false;

int main(int argc, char **argv)
{
	int opt;

	//Socket
	int clientfd;
	//Direcciones y puertos
	char *hostname, *port;

	//Lectura desde consola
	char *linea_consola;
	char read_buffer[MAXLINE] = {0};
	size_t max = MAXLINE;
	ssize_t n, l = 0;
	char *test_str = NULL;

	while ((opt = getopt (argc, argv, "ht:")) != -1){
		switch(opt)
		{
			case 'h':
				print_help(argv[0]);
				return 0;
			case 't':
				tflag = true;
				test_str = optarg;
				break;
			default:
				fprintf(stderr, "uso: %s <hostname> <puerto>\n", argv[0]);
				fprintf(stderr, "     %s -h\n", argv[0]);
				return 1;
		}
	}

	int contador = 0;
	int index = 0;
	for (index = optind; index < argc; index++)
		contador++;

	if(contador != 2){
		fprintf(stderr, "uso: %s <hostname> <puerto>\n", argv[0]);
		fprintf(stderr, "     %s -h\n", argv[0]);
		return 1;
	}else{
		hostname = argv[optind];
		port = argv[optind + 1];
	}

	//Valida el puerto
	int port_n = atoi(port);
	if(port_n <= 0 || port_n > USHRT_MAX){
		fprintf(stderr, "Puerto: %s invalido. Ingrese un número entre 1 y %d.\n", port, USHRT_MAX);
		return 1;
	}

	//Se conecta al servidor retornando un socket conectado
	clientfd = open_clientfd(hostname, port);

	if(clientfd < 0)
		connection_error(clientfd);

	printf("Conectado exitosamente a %s en el puerto %s.\n", hostname, port);

	/* Código para testing automatico, no remover */
	/*********************************************/
	if(tflag) test(test_str, clientfd);
	/*********************************************/

	linea_consola = (char *) calloc(1, MAXLINE);
	printf("Ingrese texto para enviar al servidor, escriba CHAO para terminar...\n");
	printf("> ");
	l = getline(&linea_consola, &max, stdin); //lee desde consola
	while(l > 0){
		n = write(clientfd, linea_consola, l); //Envia al servidor
		if(n<=0)
			break;

		n = read(clientfd, read_buffer, MAXLINE); //Lee respuesta del servidor
		if(n<=0)
			break;

		printf("Recibido: %s", read_buffer);
		memset(read_buffer,0,MAXLINE); //Encerar el buffer

		//Volver a leer desde consola
		printf("> ");
		l = getline(&linea_consola, &max, stdin);
	}


	printf("Desconectando...\n");
	free(linea_consola);
	close(clientfd);

	return 0;
}