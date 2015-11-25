	
	#include "manip_chaines.h"
	
	int main (void){
		irc_msg *message=NULL;
		message=(irc_msg*)malloc(sizeof(irc_msg));
		char msg_string[]=":nick!~hamza@server PRIVMSG #channelisty :apparament ça marche !";
		parse_message(msg_string,message);
		printf("prefix:%s  \n ident_name : %s , ident_user: %s ident_host:%s \n command: %s \n, pram: %s \n, nparam: %d \n trailing: %s",message->prefix,message->ident[name],message->ident[user],message->ident[host],message->command,message->param[0],message->nparams,message->trailing );
		
	
		
		
	return 0;
	}
