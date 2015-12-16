	#include "init.h"
	#include "struct_user_channel.h"
	#include "manip_chaines.h"
	#include "server_functions.h"

	void *connection_plusieurs(void *client_fd);

	int main( int argc, const char* argv[] )
	{
		/*Connection parameters variables */
		struct sockaddr_in server;
		struct sockaddr_in dest;
		int socket_fd=0;int client_fd=0;
		socklen_t size;
		pthread_t thread_id;
		int yes =1; 

		/*Socket creation*/ 
		socket_fd = createSocket(socket_fd, yes, server, dest);

		/* define connexion parameters : port,host,ect ... */
		server.sin_family = AF_INET;
		server.sin_port = htons(PORT);
		server.sin_addr.s_addr = INADDR_ANY;
		
		/*bind socket c'est à dire associcer la socket à notre adresse local*/
		doBind(socket_fd, server);	

		/* Listen :*/
		listenAConnection(socket_fd);
		
		/* If we have listener*/
		size = sizeof(struct sockaddr_in); 
			
		while((client_fd = accept(socket_fd, (struct sockaddr *)&dest, (socklen_t*)&size))) {
		/*Accept connexion*/ 
			if (client_fd==-1) {
				perror("not accept");
				exit(1);
			}
			/* Send acceptation message */
			
			printf("Server got connection from client %s\n", inet_ntoa(dest.sin_addr));
			if( pthread_create( &thread_id , NULL ,  connection_plusieurs , (void*) &client_fd) < 0)
			{
				perror("could not create thread");
				return 1;
			}
		}	
		
	return 0;
	}
	void *connection_plusieurs(void *client_filedesc)
		{
		
		char buffer[10241];
		char buff[3000];
		int num =0;
		int client_fd = *(int*)client_filedesc;
		num= recv(client_fd, buffer, 10240,0);
		if (num == -1) {
			perror("recv");
			exit(1);
		}  
		else if (num == 0) {
			printf("Connection closed\n");
			return 0;
		}
		else{
						
		recv(client_fd,buffer, sizeof(buffer),50000);
		
		irc_msg *message=NULL;
		message=(irc_msg*)malloc(sizeof(irc_msg));
		parse_message(buffer,message);
		affiche_parsed_message ( message);
		if (strcmp(message->command,"NICK")==0)
			strcpy(buff,"001\n");
		/* on envoi 001 pour le client pour ---> mode +i l'utulisateur est reconnue que par les utilisateurs de meme channel avec /who or whois*/
		send(client_fd,(char *)buff, sizeof(buff), 0);
		}
		return 0;
	}
			
