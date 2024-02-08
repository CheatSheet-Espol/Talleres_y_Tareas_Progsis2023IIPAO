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
#include <fcntl.h>

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

/**
 * Function for internal tests.
 *
 * @param test_str Test string.
 * @param clientfd Socket file descriptor.
 */
void test(char *test_str, int clientfd);

#endif /* COMMON_H */