#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/stat.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h> // Include pthread library for multithreading
#include <semaphore.h> // Include semaphore library for synchronization

//TODO: include semaphore

#define MAXLINE 1024

///////////////////////////////////////
/* Funciones de gestión de conexión */

/**
 * Open and return a listening socket on port. This function is reentrant and protocol-independent.
 *
 * @param port Character array with TCP port, decimal.
 *
 * @return A listening socker. On error, returns -1 and sets errno.
 */
 //TODO:struct buffer (sbuf_t)
typedef struct {
    int *buf;      /* Buffer array */
    int n;         /* Maximum number of slots */
    int front;     /* buf[(front+1)%n] is the first item */
    int rear;      /* buf[rear%n] is the last item */
    sem_t mutex;   /* Protects accesses to buf */
    sem_t slots;   /* Counts available slots */
    sem_t items;   /* Counts available items */
} sbuf_t;


//TODO:buffer functions definitions (sbuf_init, sbuf_remove, sbuf_insert)
void sbuf_init(sbuf_t *sp, int n);
void sbuf_insert(sbuf_t *sp, int item);
int sbuf_remove(sbuf_t *sp);



int open_listenfd(char *port);


/**
 * Open connection to server at <hostname, port> and 
 * return a socket descriptor ready for reading and writing. This
 * function is reentrant and protocol-independent.
 *
 * @param hostname Character array with IP address or hostname.
 * @param port Character array with TCP port, decimal.
 *
 * @return Socket file descriptor. On error, returns -1 and sets errno.
 */
int open_clientfd(char *hostname, char *port);

/**
 * Closes the socket, prints error on STDERR and exits.
 *
 * @param connfd Socket file descriptor.
 */
void connection_error(int connfd);

#endif /* COMMON_H */




//implementations goes in common.c