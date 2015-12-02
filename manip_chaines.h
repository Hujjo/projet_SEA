#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MANIP_CHAINES_H
#define MANIP_CHAINES_H
#define MAX_PARAMS 15

#include "struct_user_channel.h"

//FONCTION
int manip_chaines(char * msg_string);

	enum PREFIX_ITEMS
	{
      name = 0,
      user1 = 1,
      host = 2
	};
	

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
#endif
