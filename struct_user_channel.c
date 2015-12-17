

/************************************
 * Linked List manipulation methods *
 ************************************/

/* Insert an element in the linked list */
/*          Always at the end           */
/* 
 *
 *
 */
#include "struct_user_channel.h"
#include "manip_chaines.h"

user *create_user(char *msg_command,char *msg_param1 , char *msg_param2)
{
	
	user *nouvutilisateur = malloc(sizeof(nouvutilisateur));

	if(strcmp(msg_command,"NICK") == 0){
			   
		strcpy(nouvutilisateur->nickname,msg_param1);	
		strcpy(nouvutilisateur->username,msg_param2);
       
	}
      
	return  nouvutilisateur;
}
   
/************************************
 * Linked List manipulation methods *
 ************************************/

/* Insert an element in the linked list */
/*          Always at the end           */
void add_channel(tlistC * lc, channel * c)
{
	tchannel * new = calloc(1, sizeof(tchannel));
	new->channel = c; 

	if (lc->first == NULL) {
		lc->first = new;
		lc->last  = new;
	} else {
		lc->last->next = new;
		lc->last = new;
	}
}

/*Add a new user to a list*/

void add_user(tlistU *lu, user * u,tuser *new)
{
	
	  tuser *nouveau = NULL;
	  nouveau=(tuser*)malloc(sizeof(tuser));
	  nouveau->users=malloc(sizeof(*u));

	  if (lu == NULL || nouveau == NULL)
      {
        exit(EXIT_FAILURE);
      }
	  strcpy(nouveau->users->nickname,u->nickname);
	  nouveau->next=lu->first;
	  lu->first=nouveau;
     
	
}


/* Delete an element in the linked list */
void del_channel(tlistC * lc, channel * c)
{
	/* lc is empty do nothing */
	if (lc->first == NULL) {
		return;
	}

	/* special case when c is the head of the list */
	if (lc->first->channel == c) {
		tchannel * succesor = lc->first->next;
		free(lc->first);
		lc->first = succesor;
		return;
	} 

	tchannel * cur = lc->first;
	while (1) {
		/* c was not found, return */
		if (cur->next == NULL) {
			return;
		} 

		/* c is found, remove it, and reconnect the list */
		if (cur->next->channel ) {
			/* special case when c is the tail of the list */
			if (cur->next == lc->last) {
				lc->last = cur;
			}
			tchannel * succesor = cur->next->next;
			free(cur->next);
			cur->next = succesor;
			return;
		}
		cur = cur->next;
	}
}
void del_user(tlistU * lu, user * u)
{
	/* lu is empty do nothing */
	if (lu->first == NULL) {
		return;
	}

	/* special case when u is the head of the list */
	if (lu->first->users == u) {
		tuser * succesor = lu->first->next;
		free(lu->first);
		lu->first = succesor;
		return;
	} 

	tuser * cur = lu->first;
	while (1) {
		/* u was not found, return */
		if (cur->next == NULL) {
			return;
		} 

		/* u is found, remove it, and reconnect the list */
		if (cur->next->users == u) {
			/* special case when u is the tail of the list */
			if (cur->next == lu->last) {
				lu->last = cur;
			}
			tuser * succesor = cur->next->next;
			free(cur->next);
			cur->next = succesor;
			return;
		}
		cur = cur->next;
	}
}

int search1(tlistU *lu,tuser *L,user *c,char *identifiant,char *msg_command) // or by the ID ?
{
   
    tlistU *tmp=calloc(1, sizeof(tlistU));   
    tmp=lu;
    int k;

 
    char* valeur="NICK";
   
    char* str1 =(char *) malloc(100);
    char* str2 =(char *) malloc(100);
   //identifiant = "sami";


	if(strcmp(msg_command,valeur) == 0 )
    {

		while(tmp->first!=NULL)
		{
			 printf("%s",lu->first->users->nickname);
			  strcpy(str2,identifiant);
			  strcpy(str1,tmp->first->users->nickname);
			  k = strcmp(tmp->first->users->nickname,identifiant);

			if (k == 0)
			   {

				 return 1; 

			   }
			else
			{
				/*parcourir la liste des users*/
				if (tmp->first->next != NULL ) {
					tmp->first = tmp->first->next;
			
				}
				else
					return 0 ;
				 
			}
		 } 
   }	
   return 0;
}

int user_connexion(tlistU lu,tuser *L,user *c,char *msg_param1,char *msg_param2,char *msg_command){
	 
	tuser *new = calloc(1, sizeof(tuser));
	user  * utu1 = malloc(sizeof(*utu1));

	/*if ( search1(lu,L,c,msg_param1,msg_command) == 1 ) 
	{
		printf("l'identifant %s existe  \n",msg_param1);
		return 0;
	} */

	utu1 = create_user(msg_command, msg_param1,msg_param2);		 
	add_user(&lu,utu1,new);
	return 1;

}
     
void ini_tlistU(tlistU *lu) {
	
	      
	user  * utu1 = malloc(sizeof(*utu1));
	tuser * new  = malloc(sizeof(*new));     

	char *mess =malloc(sizeof(*mess));
	mess ="USER0";
	strcpy(utu1->nickname,mess);

	new->users = utu1;                 
	new->next=NULL;
	lu->first =new;

	} 
 
/* Search an element in the linked list */
/*channel search(channel * lc, channel * c) // or by the ID ?
{

}
* */



