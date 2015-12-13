#ifndef SERVER_FUNCTIONS_H_INCLUDED
#define SERVER_FUNCTIONS_H_INCLUDED

#include "init.h"

// Function to create and configure a socket
int createSocket(int,int,sockaddr_in,sockaddr_in);

// Function to bind, ie to associate the new socket to our local address
void doBind(int,sockaddr_in);

// Function to listen calling clients
void listenAConnection(int);

#endif	// SERVER_FUNCTIONS_H_INCLUDED
