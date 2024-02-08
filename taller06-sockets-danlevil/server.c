#include <getopt.h>
#include <limits.h>

#include "common.h"
// TO-DO: sha256 header
#include "sha256.h"
void atender_cliente(int connfd);

void print_help(char *command)
{
	printf("Servidor simple de descarga de archivos.\n");
	printf("uso:\n %s <puerto>\n", command);
	printf(" %s -h\n", command);
	printf("Opciones:\n");
	printf(" -h\t\t\tAyuda, muestra este mensaje\n");
}

// TO-DO: sprint_hex function
void sprint_hex(char *output, const unsigned char* input, size_t size)
{
int i;
	for(i = 0; i < size; ++i)	
		sprintf(output + 2*i, "%02x", input[i]);
		sprintf(output + 2*i, "\n");
}

bool seguir = true;

int main(int argc, char **argv)
{
	int opt;

	//Sockets
	int listenfd, connfd;
	unsigned int clientlen;
	//Direcciones y puertos
	struct sockaddr_in clientaddr;
	struct hostent *hp;
	char *haddrp, *port;

	while ((opt = getopt (argc, argv, "h")) != -1){
		switch(opt)
		{
			case 'h':
				print_help(argv[0]);
				return 0;
			default:
				fprintf(stderr, "uso: %s <puerto>\n", argv[0]);
				fprintf(stderr, "     %s -h\n", argv[0]);
				return 1;
		}
	}

	if(argc != 2){
		fprintf(stderr, "uso: %s <puerto>\n", argv[0]);
		fprintf(stderr, "     %s -h\n", argv[0]);
		return 1;
	}else
		port = argv[1];

	//Valida el puerto
	int port_n = atoi(port);
	if(port_n <= 0 || port_n > USHRT_MAX){
		fprintf(stderr, "Puerto: %s invalido. Ingrese un número entre 1 y %d.\n", port, USHRT_MAX);
		return 1;
	}

	//Abre un socket de escucha en port
	listenfd = open_listenfd(port);

	if(listenfd < 0)
		connection_error(listenfd);

	printf("server escuchando en puerto %s...\n", port);

	while (seguir) {
		clientlen = sizeof(clientaddr);
		connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);

		/* Determine the domain name and IP address of the client */
		hp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
					sizeof(clientaddr.sin_addr.s_addr), AF_INET);
		haddrp = inet_ntoa(clientaddr.sin_addr);

		printf("server conectado a %s (%s)\n", hp->h_name, haddrp);
		atender_cliente(connfd);
		printf("server desconectando a %s (%s)\n", hp->h_name, haddrp);

		close(connfd);
	}
}

void atender_cliente(int connfd)
{
	int n;
	char buf[MAXLINE] = {0};
	// buf_out
	// TO-DO: sha256 variables
	char buf_out[MAXLINE] ={};
	char *sha_out[SHA256_BLOCK_SIZE];
	SHA256_CTX ctx;
	while(1){
		n = read(connfd, buf, MAXLINE);
		if(n <= 0)
			return;

		printf("Recibido: %s", buf);

		//Detecta "CHAO" y se desconecta del cliente
		if(strcmp(buf, "CHAO\n") == 0){
			write(connfd, "BYE\n", 4);
			return;
		}

		//Detecta "KILL", se desconecta del cliente y termina
		if(strcmp(buf, "KILL\n") == 0){
			write(connfd, "BYE\n", 4);
			seguir = false;
			return;
		}
		
		// TO-DO: sha256 gen (init/update/final)
		sha256_init(&ctx);
		sha256_update(&ctx,buf,strlen(buf)-1);
		sha256_final(&ctx,sha_out);
		
	
		// TO-DO: sprint_hex
		 sprint_hex(buf_out,sha_out, SHA256_BLOCK_SIZE);		
		
		//Reenvía el mensaje al cliente 
		n = write(connfd, buf_out, strlen(buf_out));  //TO-DO
		if(n <= 0)
			return;

		memset(buf, 0, MAXLINE); //Encera el buffer
	}
}
