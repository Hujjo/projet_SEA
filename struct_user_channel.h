
/* 
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

#ifndef STRUCT_USER_CHANNEL_H_INCLUDED
#define STRUCT_USER_CHANNEL_H_INCLUDED

#include "init.h"

/************************************
 *			   Structures			*
 ***********************************/

/* Structure channel */
typedef struct channel {
	int id;
	char * name = NULL;
	tlistU * userlist;
	int view;
} channel;

/* Structure user */
typedef struct user {
	int id;
	char * nickname = NULL;
	char * username = NULL;
	char * realname = NULL;
	int channel;
	char * password = NULL;
} user;

/* Channel in a linked list of channels */
typedef struct tchannel {
	channel * channel;
	struct tchannel * next;
} tchanel;

/* User in a linked list of users */
typedef struct tuser {
	user * user;
	struct tuser * next;
} tuser;

/* List of channels */
typedef struct tlistC {
	tchannel * first;
	tchannel * last;
} tlistC;

/* List of users */
typedef struct tlistU {
	tuser * first;
	tuser * last;
} tlistU;

/************************************
 *    User manipulation methods		*
 ***********************************/

/************************************
 * To create an user				*
 * Return 	: pointer on user		*
 * Args 	: int, id of user		*
 ***********************************/
user * create_user(int);

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
channel * create_channel(int);

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
void add(tlistC * lc, channel * c);
void add(tlistU * lu, user    * u);

/* Delete an element in the linked list */
void del(tlistC * lc, channel * c);
void del(tlistU * lu, user    * u);

/* Search an element in the linked list */
channel search(channel * lc, channel * c); // or by the ID ?
user    search(user    * lu, user    * u); // or by the ID ?

/* Sort the linked list by name or ID */


#endif	// STRUCT_USER_CHANNEL_H_INCLUDED
