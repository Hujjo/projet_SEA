#ifndef STRUCT_USER_CHANNEL_H
#define STRUCT_USER_CHANNEL_H


#include "init.h"

/************************************
 *			   Structures			*
 ***********************************/

/* Structure user */
typedef struct user {
	int  *id;
	char nickname[9];
	char username[20];
	char *realname;
	int channel;
	char *password;
}user;

/* User in a linked list of users */
typedef struct tuser {
	user * users;
	struct tuser * next;
}tuser;

/* List of users */
typedef struct tlistU {
	tuser * first;
	tuser * last;
} tlistU;

/* Structure channel */
typedef struct channel {
	char * name ;
	tlistU * userlist;
}channel;

/* Channel in a linked list of channels */
typedef struct tchannel {
	channel * channel;
	struct tchannel * next;
}tchannel;


/* List of channels */
typedef struct tlistC {
	tchannel * first;
	tchannel * last;
}tlistC;

/* Struture regrouping all structures types which will be passed to thread */
typedef struct thread_args {
	user userinfos;
	int client_fd;
	tuser userinlist;
	tlistU lu;
	channel channelinfos;
	tchannel channelinlist;
	tlistC channellist;
} thread_args;
	

/************************************
 *    User manipulation methods		*
 ***********************************/
 /*******************************************************
 * To create an user				                    *
 * Return 	: int            	                    	*
 * Args 	: tlistU, tuser, user,char*,char*,char*		*
 ********************************************************/
 /*connecting user by checking first if the name exists, if not add him ( problem in searching)*/
int user_connexion(tlistU lu,tuser *L,user *c,char *msg_param1,char *msg_param2,char *msg_command);
/************************************
 * To create an user				*
 * Return 	: pointer on user		*
	                                *
 ***********************************/
user *create_user(char *msg_command,char *msg_param1 , char *msg_param2);

/****************************************
 * To delete an user					*
 * Return 	: 1 if deleting successfull	*
 * 			  0 if deleting fail		*
 * Args 	: int, id of user 			*
 ***************************************/
int delete_user(int);

/************************************************************
 * To update an user										*
 * Return 	: 1 if updating successfull						*
 * 			  0 if updating fail							*
 * Args 	: int, id of user								*
 * 			  int, id of channel							*
 * 			  char*, nickname,username,realname,password	*
 ***********************************************************/
int update_nickname_user(int , char*);
int update_username_user(int, char*);
int update_realname_user(int, char*);
int update_channel_user (int, int  );
int update_password_user(int, char*);

/************************************
 *   Channel manipulation methods	*
 ***********************************/

/************************************
 * To create a channel				*
 * Return 	: pointer on channel	*
 * Args 	: int, id of channel	*
 ***********************************/
channel create_channel(int);

/****************************************
 * To delete a channel					*
 * Return 	: 1 if deleting successfull	*
 * 			  0 if deleting fail		*
 * Args 	: int, id of channel		*
 ***************************************/
int delete_channel(int);

/********************************************
 * To update a channel						*
 * Return 	: 1 if updating successfull		*
 * 			  0 if updating fail			*
 * Args 	: int, id of channel			*
 * 			  int, public or private		*
 * 			  char*, name of channel		*
 * 			  tlistU, linked list of users	*
 ********************************************/
int update_name_channel(int, char*);
int update_userlist_channel(int, tlistU);
int update_view_channel(int, int);

/************************************
 * Linked List manipulation methods *
 ***********************************/

/* Insert an element in the linked list */
/*          Always at the end           */
void add_channel(tlistC * lc, channel 	* c);
void add_user(tlistU *lu, user * u,tuser *new);

/* Delete an element in the linked list */
void del_channel(tlistC * lc, channel 	* c);
void del_user	(tlistU * lu, user 		* u);

/* Search an element in the linked list */

channel search(channel * lc, channel * c); // or by the ID ?

/************************************************
 * Search an user in a list of user				*
 * If user does not exist, add it in the list	*
 * Return	TRUE if user exist					*
 * 			FALSE if user does not exist		*
 * Args		list of tuser						*
 * 			tuser								*
 * 			user								*
 ************************************************/
int search_user(tlistU * lu, tuser *L, user *u);

/* Sort the linked list by name or ID */


#endif // STRUCT_USER_CHANNEL_H_INCLUDED
