	#include "init.h"
	#include "struct_user_channel.h"
	#include "manip_chaines.h"
	

	#define PORT 6667  //Port number
	#define BACKLOG 10


	void *connection_handler(void *client_fd);

	int main( int argc, const char* argv[] )
	{
		
		/*Connection parameters variables */
		struct sockaddr_in server;
		struct sockaddr_in dest;
		int socket_fd, client_fd;
		socklen_t size;
		pthread_t thread_id;

		
		int yes =1; 
		/*Socket creation*/ 
		if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0))== -1) {
			/*in case of failure*/ 
			fprintf(stderr, "Socket failure!!\n");
			exit(1);
		}

		if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}
		memset(&server, 0, sizeof(server));
		memset(&dest,0,sizeof(dest));
		
		/* define connexion parameters : port,host,ect ... */
		
		server.sin_family = AF_INET;
		server.sin_port = htons(PORT);
		server.sin_addr.s_addr = INADDR_ANY;
		
		/*bind socket c'est à dire associcer la socket à notre adresse local*/
		 
		if ((bind(socket_fd, (struct sockaddr *)&server, sizeof(struct sockaddr )))== -1)    { //sizeof(struct sockaddr)
			fprintf(stderr, "Binding Failure\n");
			exit(1);
		}
		/* Listen :*/
		
		if ((listen(socket_fd, BACKLOG))== -1){
			fprintf(stderr, "Listening Failure\n");
			exit(1);
		}
		
		/* If we have listener*/
		size = sizeof(struct sockaddr_in); 
		/*Accept connexion*/ 
			
		 
			
		while((client_fd = accept(socket_fd, (struct sockaddr *)&dest, (socklen_t*)&size))) {
			
			if (client_fd==-1) {
				perror("not accept");
				exit(1);
			}
			/* Send acceptation message */
			
			printf("Server got connection from client %s\n", inet_ntoa(dest.sin_addr));
			 
		   /***************************************************************************
			* 																		*
			* Once connexion done we will use threads to maintain multiple connexions *
			*																			*
			* 																		*
			***************************************************************************/
				
					
			while(1) {
			if( pthread_create( &thread_id , NULL ,  connection_plusieurs , (void*) &client_fd) < 0)
			{
				perror("could not create thread");
				return 1;
			}
				}	
			

	}
	return 0;
	}
	void *connection_handler(void *client_filedesc)
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

		strcpy(buff,"001");
		/* on envoi 001 pour le client pour ---> mode +i l'utulisateur est reconnue que par les utilisateurs de meme channel avec /who or whois*/
		send(client_fd,(char *)buff, sizeof(buff), 0);
		}
		return 0;
	}
			
