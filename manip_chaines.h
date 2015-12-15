#ifndef MANIP_CHAINES_H
#define MANIP_CHAINES_H

#include "init.h"

#define MAX_PARAMS 15

enum PREFIX_ITEMS
{
	name = 0,
	user1 = 1,
	host = 2
};
typedef struct 
{
	char    raw[512];       /* raw copy of the original message           */
	char    *prefix;        /* pointer to prefix                          */
	char    *ident[3];      /* arrays devided prefix (name, user, host)   */
	char    *command;       /* pointer to command                         */
	char    *param[15];     /* array of pointer to parsed params          */
	int     nparams;        /* numnber of params                          */
	char    *trailing;      /* pointer to trialing                        */
} irc_msg;
int parse_message(char *msg_string, irc_msg *message);
void affiche_parsed_message( irc_msg* message);
#endif
