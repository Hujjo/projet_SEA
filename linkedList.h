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

#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

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
typedef struct {
	tchannel * first;
	tchannel * last;
} tlistC;

/* List of users */
typedef struct {
	tuser * first;
	tuser * last;
} tlistU;

/************************************
 * Linked List manipulation methods *
 ************************************/

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

#endif	// LINKEDLIST_H_INCLUDE
