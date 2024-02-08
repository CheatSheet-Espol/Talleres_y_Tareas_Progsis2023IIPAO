#include <getopt.h>
#include <limits.h>

#include "common.h"

void print_help(char *command)
{
	printf("Cliente simple envío de comandos.\n");
	printf("uso:\n %s <hostname> <puerto>\n", command);
	printf(" %s -h\n", command);
	printf("Opciones:\n");
	printf(" -h\t\t\tAyuda, muestra este mensaje\n");
}

int main(int argc, char **argv)
{
	int opt;

	//Socket
	int clientfd;
	//Direcciones y puertos
	char *hostname, *port;

	//Lectura desde consola
	char *linea_consola;
	char read_buffer[MAXLINE + 1] = {0};
	size_t max = MAXLINE;
	ssize_t n, l = 0;

	while ((opt = getopt (argc, argv, "h")) != -1){
		switch(opt)
		{
			case 'h':
				print_help(argv[0]);
				return 0;
			default:
				fprintf(stderr, "uso: %s <hostname> <puerto>\n", argv[0]);
				fprintf(stderr, "     %s -h\n", argv[0]);
				return -1;
		}
	}

	if(argc != 3){
		fprintf(stderr, "uso: %s <hostname> <puerto>\n", argv[0]);
		fprintf(stderr, "     %s -h\n", argv[0]);
		return -1;
	}else{
		hostname = argv[1];
		port = argv[2];
	}

	//Valida el puerto
	int port_n = atoi(port);
	if(port_n <= 0 || port_n > USHRT_MAX){
		fprintf(stderr, "Puerto: %s invalido. Ingrese un número entre 1 y %d.\n", port, USHRT_MAX);
		return -1;
	}

	//Se conecta al servidor retornando un socket conectado
	clientfd = open_clientfd(hostname, port);

	if(clientfd < 0)
		connection_error(clientfd);

	printf("Conectado exitosamente a %s en el puerto %s.\n", hostname, port);

	linea_consola = (char *) calloc(1, MAXLINE);
	printf("Ingrese comando para enviar al servidor, escriba CHAO para terminar...\n");
	printf("> ");
	l = getline(&linea_consola, &max, stdin); //lee desde consola
	while(l > 0){
		n = write(clientfd, linea_consola, l); //Envia al servidor
		if(n<=0)
			break;

		/* Obtiene respuesta del servidor
		 * Insiste hasta vaciar el socket
		*/
		bool continuar = false;
		do{
			//Usa recv con MSG_DONTWAIT para no bloquear al leer el socket
			n = recv(clientfd, read_buffer, MAXLINE, MSG_DONTWAIT);

			if(n < 0){
				if(errno == EAGAIN) //Vuelve a intentar
					continuar = true;
				else
					continuar = false;
			}else if(n == MAXLINE) //Socket lleno, volver a leer
				continuar = true;
			else if(n == 0)
				continuar = false;
			else{ //n < MAXLINE, se asume que son los últimos caracteres en el socket
				char c = read_buffer[n - 1]; //Busca '\0' para detectar fin
				if(c == '\0')
					continuar = false;
				else
					continuar = true;
			}

			printf("%s", read_buffer);
			memset(read_buffer,0,MAXLINE + 1); //Encerar el buffer
		}while(continuar);

		//Volver a leer desde consola
		printf("> ");
		l = getline(&linea_consola, &max, stdin);
	}


	printf("Desconectando...\n");
	free(linea_consola);
	close(clientfd);
}