#include "server_functions.h"

/* Function to create a socket.
 * Return	integer, the file_descriptor of the socket.
 * Params	socket_fd, the file_descriptor of the socket.
 */ 
int createSocket(int socket_fd, int yes, sockaddr_in server, sockaddr_in dest) {
	// To create the socket
	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0))== -1)
	{
		/* show this message if failure */
		fprintf(stderr, "Socket failure!!\n");
		exit(1);
	}
	// To configure the socket
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}
	memset(&server, 0, sizeof(server));
	memset(&dest,0,sizeof(dest));
	
	return socket_fd;
}

/* Function to bind, ie to associate the new socket to our local address
 * Return	none
 * Params	socket_fd, the file_descriptor of the socket
 * 			server, in address of the socket
 */
void doBind(int socket_fd, sockaddr_in server) {
	if ((bind(socket_fd, (sockaddr *)&server, sizeof(sockaddr)))== -1)
	{	//sizeof(struct sockaddr)
		fprintf(stderr, "Binding Failure\n");
		exit(1);
	}
}

/* Function to listen calling clients. Backlog is equal to 10, 
 * therefore we can't listen more of 10 clients.
 * Return	none
 * Params	socket_fd, file descriptor of the socket
 */
void listenAConnection(int socket_fd){
	if ((listen(socket_fd, BACKLOG))== -1){
		fprintf(stderr, "Listening Failure\n");
		exit(1);
	}
}

void acceptAConnection(int 
