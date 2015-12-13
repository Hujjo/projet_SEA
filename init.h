#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

#define PUBLIC 1
#define PRIVATE 0

#define PORT 6667	// port of connection by client
#define BACKLOG 10	// number of simultanous connection for one socket

// todo : define a new type : boolean

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

#endif //INIT_H_INCLUDED
