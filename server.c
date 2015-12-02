#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "struct_user_channel.h"
#include "manip_chaines.h"

#define PORT 6667  //on definit le port sur lequel le cient il va se connecter au serveur
#define BACKLOG 10

int main(int argc, char *argv[])
{
	
	/*paramètre de connection au client */
    struct sockaddr_in server;
    struct sockaddr_in dest;
    int socket_fd, client_fd,num;
    socklen_t size;
    char buffer[10241];
    char buff[3000];
    
//  memset(buffer,0,sizeof(buffer));
    int yes =1;
    //char baf[13];

 
    //creation de socket 
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0))== -1) {
		//afficher ce mesage d'erreur en cas de failure 
        fprintf(stderr, "Socket failure!!\n");
        exit(1);
    }

    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    memset(&server, 0, sizeof(server));
    memset(&dest,0,sizeof(dest));
    // definir les paramètres de connection : port,host,ect ...
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    //faire le bind c'est à dire associcer la socket à notre adresse local 
    if ((bind(socket_fd, (struct sockaddr *)&server, sizeof(struct sockaddr )))== -1)    { //sizeof(struct sockaddr)
        fprintf(stderr, "Binding Failure\n");
        exit(1);
    }
    // faire le listen : genre ecouter tous les appels qui viennent des clients ( BACKLOG 10 donc on peut ecouter 10 appels à la fois)
    if ((listen(socket_fd, BACKLOG))== -1){
        fprintf(stderr, "Listening Failure\n");
        exit(1);
    }
   // dans le cas ou il ya des appels on attentes on passe pour les étapes suivantes
    while(1) {
		
        size = sizeof(struct sockaddr_in); 
         //on va accepter la connection de client ( client irssi ) 
        if ((client_fd = accept(socket_fd, (struct sockaddr *)&dest, &size))==-1) {
            //fprintf(stderr,"Accept Failure\n");
            perror("accept");
            exit(1);
        }
        
        // envoyer ça en buffer comme quoi la connexion est faite 
        printf("Server got connection from client %s\n", inet_ntoa(dest.sin_addr));
        
        
        //verifier la disponibilté de nickname il est pas utulisé
        
      while(1) {
	
        if ((num = recv(client_fd, buffer, 10240,0))== -1) {
            //fprintf(stderr,"Error in receiving message!!\n");
            perror("recv");
            exit(1);
        }  
        else if (num == 0) {
            printf("Connection closed\n");
            return 0;
        }else{
			            
       // if(send(client_fd,buff, strlen(buff),0)) {
		 //   buff="001"
        recv(client_fd,buffer, sizeof(buffer),50000);
         //buffer[num] = 'a';
         //printf("%s \n", buffer);
        
        // on fait l'appel à la fontction de manipulation de chaine pour récuperer les paramètre   
        //manip_chaines(buffer); <----- à modifer pour faire aapele de fonction 
        

		//create_user(message->command,message->param[0]);
	
	    irc_msg *message=NULL;
		message=(irc_msg*)malloc(sizeof(irc_msg));
		//msg_string[]=":nick!~hamza@server PRIVMSG #channelisty :apparament ça marche !";
		parse_message(buffer,message);
		
		 printf("\n command: %s \n, pram: %s \n",message->command,message->param[0]);
        

        strcpy(buff,"001");
        // on envoi 001 pour le client pour ---> mode +i l'utulisateur est reconnue que par les utulisateur de meme channel avec /who or 
        // whois
        send(client_fd,(char *)buff, sizeof(buff), 0);
        

      
	}
	
       }
        

     
    }
 
}
