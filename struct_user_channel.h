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
	user * user;
	struct tuser * next;
}tuser;

/* List of users */
typedef struct tlistU {
	tuser * first;
	tuser * last;
} tlistU;

/* Structure channel */
typedef struct channel {
	int id;
	char * name ;
	tlistU * userlist;
	int view;
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

/************************************
 *    User manipulation methods		*
 ***********************************/

/************************************
 * To create an user				*
 * Return 	: pointer on user		*
 * Args 	: int, id of user		*
 ***********************************/
user create_user(char *msg_command,char *msg_param);

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
int update_nickname_user(int, char*);
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
void add_user	(tlistU * lu, user 		* u);

/* Delete an element in the linked list */
void del_channel(tlistC * lc, channel 	* c);
void del_user	(tlistU * lu, user 		* u);

/* Search an element in the linked list */
channel search_channel	(channel * lc, channel * c); // or by the ID ?
user    search_user		(user    * lu, user    * u); // or by the ID ?

/* Sort the linked list by name or ID */


#endif	// STRUCT_USER_CHANNEL_H_INCLUDED
