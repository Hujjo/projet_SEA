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

#define PORT 5000  //on definit le port sur lequel le cient il va se connecter au serveur
#define BACKLOG 10

int main(int argc, char *argv[])
{
	/*paramètre de connection au client */
    struct sockaddr_in server;
    struct sockaddr_in dest;
    int socket_fd, client_fd,num;
    socklen_t size;
    //taille de buffer
    char buffer[10241];
    char *buff;
//  memset(buffer,0,sizeof(buffer));
    int yes =1;

 
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
        printf("Server got connection from client %s\n", inet_ntoa(dest.sin_addr));
        //buffer = "Hello World!! I am networking!!\n";

        while(1) {
			/*on recoit le buffer du client tous ce qui est peut etre envoyé par client et on l'affiche aprés
		     par example dans le cas de irssi on recoit dés la connection on va recevoir :
		       * nick_name 
		       * real_name
		       */
        if ((num = recv(client_fd, buffer, 10240,0))== -1) {
            //fprintf(stderr,"Error in receiving message!!\n");
            perror("recv");
            exit(1);
        }  
        else if (num == 0) {
            printf("Connection closed\n");
            return 0;
        }
    //  num = recv(client_fd, buffer, sizeof(buffer),0);
        buffer[num] = '\0';
        printf("Message received: %s\n", buffer);
        }

    buff = "I am communicating with the client!!\n";
        // envoyer un message de server vers le client ( on recoit message de client et on le transmet selon les channels) 
        if ((send(client_fd,buff, strlen(buff),0))== -1) {
        fprintf(stderr, "Failure Sending Message\n");
        close(client_fd);
        exit(1);
    }
    else {
        printf("Message being sent: %s\nNumber of bytes sent:\n",buff);
    }

        close(client_fd);  
        close(socket_fd);  
        //return 0;
    }
    //close(client_fd);
    return 0;
}
