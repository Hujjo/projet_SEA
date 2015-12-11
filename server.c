#include "init.h"
#include "server_functions.h"
#include "struct_user_channel.h"
#include "manip_chaines.h"

int main( int argc, const char* argv[] )
	/*paramètre de connection au client */
	sockaddr_in server;
    sockaddr_in dest;
    int socket_fd, client_fd,num;
    socklen_t size;
    char buffer[10241];
    char buff[3000];
       
    tlistU  *lu;
    tuser *L;
    
    //memset(buffer,0,sizeof(buffer));
    int yes =1;
    //char baf[13];

	socket_fd = createScocket(socket_fd,yes,server,dest);
 
    // definir les paramètres de connection : port,host,ect ...
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    //faire le bind c'est à dire associcer la socket à notre adresse local 
    doBind(socket_fd,server);

    // faire le listen : genre ecouter tous les appels qui viennent des clients ( BACKLOG 10 donc on peut ecouter 10 appels à la fois)
    listenAConnection(socket_fd);
    
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
        

	    irc_msg *message=NULL;
		message=(irc_msg*)malloc(sizeof(irc_msg));
		//msg_string[]=":nick!~hamza@server PRIVMSG #channelisty :apparament ça marche !";
		parse_message(buffer,message);
		
		printf("prefix:%s  \n ident_name : %s , ident_user: %s ident_host:%s \n command: %s \n, pram: %s \n, nparam: %d \n trailing: %s",message->prefix,message->ident[name],message->ident[user1],message->ident[host],message->command,message->param[0],message->nparams,message->trailing );
		
		search1(lu,L,message->param[0]);
		//create_user(message->command,message->param[0]);
		
		
        strcpy(buff,"001");
        // on envoi 001 pour le client pour ---> mode +i l'utulisateur est reconnue que par les utulisateur de meme channel avec /who or 
        // whois
        send(client_fd,(char *)buff, sizeof(buff), 0);

	//memset(buffer,0,sizeof(buffer));
	int yes =1;
    
	// Create and configure the socket
	socket_fd = createSocket(socket_fd, yes, server, dest);
      
	/*definir les paramètres de connection : port,host,ect ...*/
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = INADDR_ANY;
	
	// Do the bind
	doBind(socket_fd, server);	

	// Listen calling clients
	listenAConnection(socket_fd);
	
	/*dans le cas ou il y a des appels en attente on passe aux étapes suivantes*/
	while(1) {
		size = sizeof(sockaddr_in); 
		
		/*on va accepter la connexion du client ( client irssi ) */
		if ((client_fd = accept(socket_fd, (sockaddr *)&dest, &size))==-1) {
			//fprintf(stderr,"Accept Failure\n");
			perror("accept");
			exit(1);
		}		
		printf("Server got connection from client %s\n", inet_ntoa(dest.sin_addr));
		
		/* Check the unicity of the nickname choose */
		while(1) {
		// reçoit un message sur la socket
		// échec
		if ((num = recv(client_fd, buffer, 10240,0))== -1) {
			//printf(stderr,"Error in receiving message!!\n");
			perror("recv");
			exit(1);
		} 
		// message de taille nul ou clôture d'une parti de l'échange de flux
		else if (num == 0) {
			printf("Connection closed\n");
			return 0;
		}
		// nombre d'octets reçus
		else{
			// if(send(client_fd,buff, strlen(buff),0)) {
				//buff="001"
			recv(client_fd,buffer, sizeof(buffer),50000);
			//buffer[num] = 'a';
			//printf("%s \n", buffer);

			/*on fait l'appel à la fontction de manipulation de chaine pour récuperer les paramètre*/   
			//manip_chaines(buffer); <----- à modifer pour faire aapele de fonction 

			//create_user(message->command,message->param[0]);
            irc_msg *message=NULL;
			message=(irc_msg*)malloc(sizeof(irc_msg));
			//msg_string[]=":nick!~hamza@server PRIVMSG #channelisty :apparament ça marche !";
			parse_message(buffer,message);
			affiche_parsed_message ( message);
			strcpy(buff,"001");
			
			// on envoi 001 pour le client pour ---> mode +i l'utulisateur est reconnue que par les utulisateur de meme channel avec /who or 
			// whois
			send(client_fd,(char *)buff, sizeof(buff), 0);
		}
	}
	
return 0;
}
