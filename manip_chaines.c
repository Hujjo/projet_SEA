#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "manip_chaines.h"
	

	int manip_chaines(char * msg_string){
		irc_msg *message=NULL;
		message=(irc_msg*)malloc(sizeof(irc_msg));
		//msg_string[]=":nick!~hamza@server PRIVMSG #channelisty :apparament ça marche !";
		parse_message(msg_string,message);
		printf("prefix:%s  \n ident_name : %s , ident_user: %s ident_host:%s \n command: %s \n, pram: %s \n, nparam: %d \n trailing: %s",message->prefix,message->ident[name],message->ident[user1],message->ident[host],message->command,message->param[0],message->nparams,message->trailing );
		
	
		
		
	return 0;
	}
