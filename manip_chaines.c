#include "manip_chaines.h"


int parse_message(char *msg_string, irc_msg *message)
{
	/* if empty string was passed to the function */
	if(msg_string[0] == 0 || msg_string == NULL) return 0;

	memset(message, 0, sizeof(*message));

	char *tmp, *prefix = NULL;
	char *ptr = strncpy(message->raw, msg_string, 512);
 
	/* prefix & command */
	ptr = strtok(ptr, " ");
	if(*ptr != ':') message->command = ptr; // if we don't have prefix we parse command
	else {
		prefix = ptr + 1; // we parse prefix which start after ":"
		message->command = strtok(NULL, " ");
    }
 
	/* check if there is a command */
	if(message->command == NULL) return 0; /* NO COMMAND, NOT OK! */

	/* trailing */
	ptr = strtok(NULL, ""); /* \r\n ? */
	if(ptr != NULL)
	{
		if(*ptr == ':')
		{
			message->trailing = ptr + 1;
			ptr = NULL;
		}
		else
		{
			tmp = strstr(ptr, " :");
			if(tmp != NULL)
			{
				*tmp = 0;
				message->trailing = tmp + 2;
			}
		}

		/* params */
		message->param[0] = strtok(ptr, " "); /* \r\n ? */
		if(message->param[0] != NULL)
		{
			int i;
			for(i = 1; i < MAX_PARAMS; ++i)
			{
				ptr = strtok(NULL, " ");
				if(ptr == NULL) break;
					message->param[i] = ptr;
			}
			message->nparams = i;
		}
	}

	/* explode the prefix in smaller items */
	if(prefix != NULL)
	{
		tmp = strtok(prefix, "!");
		if(tmp != NULL)
		{
			message->ident[name] = tmp;

			tmp = strtok(NULL, "@");
			if(tmp != NULL)
			{
				message->ident[user1] = tmp;

				tmp = strtok(NULL, "");
				if(tmp != NULL) message->ident[host] = tmp;
			}
		}
		else message->ident[host] = prefix;
	}

	return 1; /* OK */
}

void affiche_parsed_message( irc_msg* message)
{
			printf("prefix:%s  \n ident_name : %s , ident_user: %s ident_host:%s \n command: %s \n, pram: %s \n, nparam: %d \n trailing: %s",message->prefix,message->ident[name],message->ident[user1],message->ident[host],message->command,message->param[0],message->nparams,message->trailing );

}

/*int main (void){
	irc_msg *message = NULL;
	message = (irc_msg*) malloc(sizeof(irc_msg));
	char msg_string[]=":nick!~hamza@server PRIVMSG #channelisty :apparament ça marche !";

	parse_message(msg_string,message);

	printf("prefix:%s  \n ident_name : %s , ident_user: %s ident_host:%s \n command: %s \n, pram: %s \n, nparam: %d \n trailing: %s",message->prefix,message->ident[name],message->ident[user1],message->ident[host],message->command,message->param[0],message->nparams,message->trailing );

	return 0;
}*/
