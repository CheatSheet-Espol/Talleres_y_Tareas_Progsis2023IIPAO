#include "common.h"


//TO-DO:buffer functions implementations (sbuf_init, sbuf_remove, sbuf_insert)
//use: sem_init, sem_wait, sem_post (instead P or V)
#include "common.h"


//TO-DO:buffer functions implementations (sbuf_init, sbuf_remove, sbuf_insert)

void sbuf_init(sbuf_t *sp, int n) {
    sp->buf = (int *)malloc(n * sizeof(int));
    sp->n = n;
    sp->front = sp->rear = 0;
    sem_init(&sp->mutex, 0, 1);
    sem_init(&sp->slots, 0, n);
    sem_init(&sp->items, 0, 0);
}

void sbuf_insert(sbuf_t *sp, int item) {
    sem_wait(&sp->slots);
    sem_wait(&sp->mutex);
    sp->buf[(++sp->rear) % (sp->n)] = item;
    sem_post(&sp->mutex);
    sem_post(&sp->items);
}

int sbuf_remove(sbuf_t *sp) {
    int item;
    sem_wait(&sp->items);
    sem_wait(&sp->mutex);
    item = sp->buf[(++sp->front) % (sp->n)];
    sem_post(&sp->mutex);
    sem_post(&sp->slots);
    return item;
}

//use: sem_init, sem_wait, sem_post (instead P or V)


int open_listenfd(char *port) 
{
    struct addrinfo hints, *listp, *p;
    int listenfd, optval=1;

    /* Get a list of potential server addresses */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;  /* Accept TCP connections */
    hints.ai_flags = AI_PASSIVE;      /* ... on any IP address */
    hints.ai_flags |= AI_NUMERICSERV; /* ... using a numeric port arg. */
    hints.ai_flags |= AI_ADDRCONFIG;  /* Recommended for connections */
    getaddrinfo(NULL, port, &hints, &listp);

    /* Walk the list for one that we can bind to */
    for (p = listp; p; p = p->ai_next) {

        /* Create a socket descriptor */
        if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) 
            continue;  /* Socket failed, try the next */

        /* Eliminates "Address already in use" error from bind */
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, 
                   (const void *)&optval , sizeof(int));

        /* Bind the descriptor to the address */
        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
            break; /* Success */
        close(listenfd); /* Bind failed, try the next */
    }

    /* Clean up */
    freeaddrinfo(listp);
    if (!p) /* No address worked */
        return -1;

    /* Make it a listening socket ready to accept connection requests */
    if (listen(listenfd, 1024) < 0)
		return -1;
    return listenfd;
}


int open_clientfd(char *hostname, char *port) {
    int clientfd;
    struct addrinfo hints, *listp, *p;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;  
    hints.ai_flags = AI_NUMERICSERV; 
    hints.ai_flags |= AI_ADDRCONFIG; 
    getaddrinfo(hostname, port, &hints, &listp);
  
    for (p = listp; p; p = p->ai_next) {

        if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) 
            continue; 
        if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1) 
            break; 
        close(clientfd); 
    } 

    freeaddrinfo(listp);
    if (!p) 
        return -1;
    else   
        return clientfd;
}

void connection_error(int connfd)
{
	fprintf(stderr, "Error de conexión: %s\n", strerror(errno));
	close(connfd);
	exit(-1);
}