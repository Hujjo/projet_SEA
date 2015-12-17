
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
		message->param[0] = strtok(ptr," "); /* \r\n ? */
		if(message->param[0] != NULL)
		{
			int i;
			for(i = 1; i < 2; ++i)
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
	printf("Prefix:%s  \n************* \n",message->prefix);
	printf("	ident_name : %s\n************* \n" , message->ident[name]);
	printf("	ident_user: %s\n************* \n", message->ident[user1]);
	printf("	ident_host:%s \n************* \n", message->ident[host]);
	printf("Command: %s \n************* \n",message->command);
	printf("	First Parameter: %s\n************* \n", message->param[0]);
	printf("	Number of parameters: %d \n************* \n",message->nparams);
	printf("	trailing: %s\n************* \n", message->trailing );
}

	
	
	


