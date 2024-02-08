#include <getopt.h>
#include <limits.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <syslog.h>
#include <fcntl.h>

#include "common.h"

int dflag = 0; 

struct ThreadData {
    int connfd;
};

void daemonize(char *nombre_programa) {
    printf("Entrando en modo daemon...\n");
    int fd0, fd1, fd2;
    pid_t pid;

    if ((pid = fork()) < 0) {
        fprintf(stderr, "No es posible hacer un fork, error %s\n", strerror(errno));
        exit(1);
    } else if (pid != 0) {
        exit(0);
    }

    setsid();

    // Cerrar stdout, stdin y stderr
    close(0);
    close(1);
    close(2);

    // Abrir un log para este daemon en el sistema syslog
    openlog(nombre_programa, LOG_CONS, LOG_DAEMON);

    fd0 = open("/dev/null", O_RDWR);
    if (fd0 < 0) {
        syslog(LOG_ERR, "Error al abrir /dev/null");
        exit(1);
    }

    fd1 = dup(fd0);
    if (fd1 < 0) {
        syslog(LOG_ERR, "Error al duplicar el descriptor de archivo");
        exit(1);
    }

    fd2 = dup(fd0);
    if (fd2 < 0) {
        syslog(LOG_ERR, "Error al duplicar el descriptor de archivo");
        exit(1);
    }

    syslog(LOG_INFO, "Modo daemon habilitado");
}

void atender_cliente(int connfd);

void *atender_cliente_thread(void *arg) {
    struct ThreadData *threadData = (struct ThreadData *)arg;
    atender_cliente(threadData->connfd);
    close(threadData->connfd);
    free(threadData);
    return NULL;
}




void print_help(char *command) {
    printf("Servidor simple de ejecución remota de comandos.\n");
    printf("uso:\n %s <puerto>\n", command);
    printf(" %s -h\n", command);
    printf("Opciones:\n");
    printf(" -h\t\t\tAyuda, muestra este mensaje\n");
    printf(" -d\t\t\tModo daemon\n");
}

/**
 * FunciÃ³n que crea argv separando una cadena de caracteres en
 * "tokens" delimitados por la cadena de caracteres delim.
 *
 * @param linea Cadena de caracteres a separar en tokens.
 * @param delim Cadena de caracteres a usar como delimitador.
 *
 * @return Puntero a argv en el heap, es necesario liberar esto despuÃ©s de uso.
 *	Retorna NULL si linea estÃ¡ vacÃ­a.
 */
char **parse_comando(char *linea, char *delim)
{
	char *token;
	char *linea_copy;
	int i, num_tokens = 0;
	char **argv = NULL;

	linea_copy = (char *) malloc(strlen(linea) + 1);
	strcpy(linea_copy, linea);

	/* Obtiene un conteo del nÃºmero de argumentos */
	token = strtok(linea_copy, delim);
	/* recorre todos los tokens */
	while( token != NULL ) {
		token = strtok(NULL, delim);
		num_tokens++;
	}
	free(linea_copy);

	/* Crea argv en el heap, extrae y copia los argumentos */
	if(num_tokens > 0){

		/* Crea el arreglo argv */
		argv = (char **) malloc((num_tokens + 1) * sizeof(char **));

		/* obtiene el primer token */
		token = strtok(linea, delim);
		/* recorre todos los tokens */
		for(i = 0; i < num_tokens; i++){
			argv[i] = (char *) malloc(strlen(token)+1);
			strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
	}

	return argv;
}

/**
 * Recoge hijos zombies... (puede ser eliminado)
 */
void recoger_hijos(int signal) {
    while (waitpid(-1, 0, WNOHANG) > 0)
        ;
    return;
}

void salir(int signal) {
    printf("BYE\n");
    exit(0);
}




int main(int argc, char **argv) {
    int opt, index;

    // Sockets
    int listenfd, connfd;
    unsigned int clientlen;
    // Direcciones y puertos
    struct sockaddr_in clientaddr;
    char *port = NULL;

    while ((opt = getopt(argc, argv, "dh")) != -1) {
        switch (opt) {
        case 'h':
            print_help(argv[0]);
            return 0;
        case 'd':
            dflag = 1; // Establece la bandera para el modo daemon
            break;
        default:
            fprintf(stderr, "uso: %s <puerto>\n", argv[0]);
            fprintf(stderr, "     %s -h\n", argv[0]);
            return -1;
        }
    }

    /* Recorre argumentos que no son opción */
    for (index = optind; index < argc; index++) {
        port = argv[index];
    }

    if (port == NULL) {
        fprintf(stderr, "uso: %s <puerto>\n", argv[0]);
        fprintf(stderr, "     %s -h\n", argv[0]);
        return 1;
    }

    // Valida el puerto
    int port_n = atoi(port);
    if (port_n <= 0 || port_n > USHRT_MAX) {
        fprintf(stderr, "Puerto: %s invalido. Ingrese un número entre 1 y %d.\n", port, USHRT_MAX);
        return 1;
    }

    // Registra funcion para recoger hijos zombies (innecesario?)
    signal(SIGCHLD, recoger_hijos);

    // Registra funcion para señal SIGINT (Ctrl-C)
    // NO comentar ni eliminar esta linea!!!
    signal(SIGINT, salir);

    // Abre un socket de escucha en port
    listenfd = open_listenfd(port);

    if (listenfd < 0)
        connection_error(listenfd);

    // if dflag
    // daemonize(arg0)
    if (dflag) {
        daemonize(argv[0]); // Llama a la función de demonización si está en modo daemon
    }
    printf("server escuchando en puerto %s...\n", port);

    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);

        
        struct ThreadData *threadData = (struct ThreadData *)malloc(sizeof(struct ThreadData));
        threadData->connfd = connfd;

        
        pthread_t thread;
        pthread_create(&thread, NULL, atender_cliente_thread, (void *)threadData);

       
        pthread_detach(thread);
    }
}







void atender_cliente(int connfd)
{
	int n, status;
	char buf[MAXLINE] = {0};
	char **argv;
	pid_t pid;

	
	while(1){
		n = read(connfd, buf, MAXLINE);
		if(n <= 0)
			return;

		printf("Recibido: %s", buf);

		//Detecta "CHAO" y se desconecta del cliente
		if(strcmp(buf, "CHAO\n") == 0){
			write(connfd, "BYE\n", 5);
			return;
		}

		//Remueve el salto de linea antes de extraer los tokens
		buf[n - 1] = '\0';

	
		argv = parse_comando(buf, " ");

		if(argv){
			if((pid = fork()) == 0){
				dup2(connfd, 1); 
				dup2(connfd, 2); 
				if(execvp(argv[0], argv) < 0){
					fprintf(stderr, "Comando desconocido...\n");
					exit(1);
				}
			}

			
			waitpid(pid, &status, 0);

			if(!WIFEXITED(status))
				write(connfd, "ERROR\n",7);
			else
				write(connfd, "\0", 1); 

			
			for(int i = 0; argv[i]; i++)
				free(argv[i]);
			free(argv);

		}else{
			strcpy(buf, "Comando vacio...\n");
			write(connfd, buf, strlen(buf) + 1);
		}

		memset(buf, 0, MAXLINE); 
	}
}
