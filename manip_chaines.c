#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "manip_chaines.h"
	int parse_message(char *msg_string, irc_msg *message)
    {
		/* if empty string was passed to the function */
		if(msg_string[0] == 0 || msg_string == NULL) return 0;
		/*Initialize message structure*/
		memset(message, 0, sizeof(*message));
  
		char *tmp, *prefix = NULL;
        char *ptr = strncpy(message->raw, msg_string, 512);
  
		/*****************************
		 *  prefix & command Parsing *
		 *****************************/
		/*replace the fist " " with "\0" */
		ptr = strtok(ptr, " ");
        if(*ptr != ':') message->command = ptr; // if we don't have prefix we parse command
        else {
			/*parse prefix which start after ":"*/
            prefix = ptr + 1;
            /*then parse command ( NULL takes the last string used*/
            message->command = strtok(NULL, " ");
        }
  
        /* check if there is a command */
        if(message->command == NULL) return 0; /* NO COMMAND, NOT OK! */
  
        /* trailing (last part) : optionnal */
        ptr = strtok(NULL, ""); /* \r\n ? */
        if(ptr != NULL)
        {
			/*if the first car in ptr is ":" = trailing*/
            if(*ptr == ':')
            {
                message->trailing = ptr + 1;
                ptr = NULL;
            }
            /*look for ":" and copy it in tmp*/
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
				/*save the name*/
                message->ident[name] = tmp; 
    
                tmp = strtok(NULL, "@");
                if(tmp != NULL)
                {

					/*we save the username*/
                    message->ident[user1] = tmp;
   
                    tmp = strtok(NULL, "");
                    /*we save the hostname*/
                    if(tmp != NULL) message->ident[host] = tmp;
                }
            }
            else message->ident[host] = prefix;
        }
 
        return 1; /* OK */
    }

	int manip_chaines(char * msg_string){
		irc_msg *message=NULL;
		message=(irc_msg*)malloc(sizeof(irc_msg));
		parse_message(msg_string,message);
		printf("prefix:%s  \n ident_name : %s , ident_user: %s ident_host:%s \n command: %s \n, pram: %s \n, nparam: %d \n trailing: %s",message->prefix,message->ident[name],message->ident[user1],message->ident[host],message->command,message->param[0],message->nparams,message->trailing );

	return 0;
	}
