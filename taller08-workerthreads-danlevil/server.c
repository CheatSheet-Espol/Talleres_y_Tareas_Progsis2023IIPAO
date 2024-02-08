#include <getopt.h>
#include <limits.h>
#include <sys/wait.h>
#include <pthread.h>
#include <syslog.h>
#include <fcntl.h>

#include "common.h"

// TODO: Define and initialize the buffer
sbuf_t buffer; 

void atender_cliente(int connfd);

void print_help(char *command)
{
    printf("Servidor simple de ejecución remota de comandos.\n");
    printf("uso:\n %s [-d] <puerto>\n", command);
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
	char *saveptr = NULL;

	linea_copy = (char *) malloc(strlen(linea) + 1);
	strcpy(linea_copy, linea);

	/* Obtiene un conteo del nÃºmero de argumentos */
	token = strtok_r(linea_copy, delim, &saveptr);
	/* recorre todos los tokens */
	while( token != NULL ) {
		token = strtok_r(NULL, delim, &saveptr);
		num_tokens++;
	}
	free(linea_copy);

	/* Crea argv en el heap, extrae y copia los argumentos */
	if(num_tokens > 0){

		/* Crea el arreglo argv */
		argv = (char **) malloc((num_tokens + 1) * sizeof(char **));

		/* obtiene el primer token */
		token = strtok_r(linea, delim, &saveptr);
		/* recorre todos los tokens */
		for(i = 0; i < num_tokens; i++){
			argv[i] = (char *) malloc(strlen(token)+1);
			strcpy(argv[i], token);
			token = strtok_r(NULL, delim, &saveptr);
		}
		argv[i] = NULL;
	}

	return argv;
}

/**
 * Recibe SIGINT, termina ejecuciÃ³n. NO eliminar esta funciÃ³n
 */
void salir(int signal){
	printf("BYE\n");
	exit(0);
}

void *thread(void *vargp);

bool dflag = false; //OpciÃ³n -d, El programa es Daemon

void daemonize(char *nombre_programa)
{
	printf("Entrando modo daemon...\n");

	int fd0, fd1, fd2;
	pid_t pid;
	
	if ((pid = fork()) < 0){
		fprintf(stderr, "No es posible hacer un fork, error %s\n", strerror(errno));
		exit(1);
	}else if (pid != 0)
		exit(0);

	setsid();

	//Cerrar solamente stdout, stdin y stderr
	close(0);
	close(1);
	close(2);

	//se deben abrir otra vez, por que se podrÃ­a abrir un archivo al stdout, stdin o stderr
	//y los printf van a enviar a ese archivo
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(fd0);
	fd2 = dup(fd0);

	//Abrir un log para este daemon en el sistema syslog
	openlog(nombre_programa, LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d",
		fd0, fd1, fd2);
		exit(1);
	}
}


int main(int argc, char **argv)
{
    int opt, index;

    int listenfd;
    unsigned int clientlen;
    struct sockaddr_in clientaddr;
    char *port;
    int nthreads = 1;

    while ((opt = getopt(argc, argv, "hdj:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            print_help(argv[0]);
            return 0;
        case 'd':
            dflag = true;
            break;
        case 'j':
            nthreads = atoi(optarg);
            break;
        default:
            fprintf(stderr, "uso: %s [-d] <puerto>\n", argv[0]);
            fprintf(stderr, " %s -h\n", argv[0]);
            return 1;
        }
    }

    for (index = optind; index < argc; index++)
        port = argv[index];

    if (argv == NULL)
    {
        fprintf(stderr, "uso: %s [-d] <puerto>\n", argv[0]);
        fprintf(stderr, " %s -h\n", argv[0]);
        return 1;
    }

    int port_n = atoi(port);
    if (port_n <= 0 || port_n > USHRT_MAX)
    {
        fprintf(stderr, "Puerto: %s invalido. Ingrese un número entre 1 y %d.\n", port, USHRT_MAX);
        return 1;
    }

    signal(SIGINT, salir);

    listenfd = open_listenfd(port);

    if (listenfd < 0)
        connection_error(listenfd);

    printf("server escuchando en puerto %s...\n", port);

    if (dflag)
        daemonize(argv[0]);

   
    pthread_t tid;

    sbuf_init(&buffer, nthreads + 1);

   
    for (int i = 0; i < nthreads; i++)
    {
        pthread_create(&tid, NULL, thread, NULL);
    }

    while (1)
    {
        int *connfd_ptr;
        clientlen = sizeof(clientaddr);
        connfd_ptr = (int *)malloc(sizeof(int));
        *connfd_ptr = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
        sbuf_insert(&buffer, *connfd_ptr);
        pthread_create(&tid, NULL, thread, connfd_ptr);
    }
}

/*
 * thread - En un nuevo hilo atiende al cliente. 
 */

void *thread(void *vargp)
{
   
    free(vargp);

    pthread_detach(pthread_self());

    while (1)
    {
        int connfd = sbuf_remove(&buffer);
        atender_cliente(connfd);
        close(connfd);
    }

    return NULL;
}

void atender_cliente(int connfd)
{
	int n, status;
	char buf[MAXLINE] = {0};
	char **argv;
	pid_t pid;

	//ComunicaciÃ³n con cliente es delimitada con '\0'
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

		//Crea argv con los argumentos en buf, asume separaciÃ³n por espacio
		argv = parse_comando(buf, " ");

		if(argv){
			if((pid = fork()) == 0){
				dup2(connfd, 1); //Redirecciona STDOUT al socket
				dup2(connfd, 2); //Redirecciona STDERR al socket
				if(execvp(argv[0], argv) < 0){
					fprintf(stderr, "Comando desconocido...\n");
					exit(1);
				}
			}

			//Espera a que el proceso hijo termine su ejecuciÃ³n
			waitpid(pid, &status, 0);

			if(!WIFEXITED(status))
				write(connfd, "ERROR\n",7);
			else
				write(connfd, "\0", 1); //Envia caracter null para notificar fin

			/*Libera argv y su contenido
			para evitar fugas de memoria */
			for(int i = 0; argv[i]; i++)
				free(argv[i]);
			free(argv);

		}else{
			strcpy(buf, "Comando vacÃ­o...\n");
			write(connfd, buf, strlen(buf) + 1);
		}

		memset(buf, 0, MAXLINE); //Encera el buffer
	}
}