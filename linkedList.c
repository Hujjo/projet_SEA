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

/************************************
 * Linked List manipulation methods *
 ************************************/

/* Insert an element in the linked list */
/*          Always at the end           */
void add(tlistC * lc, channel * c);
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
void add(tlistU * lu, user    * u);
{
	tuser * new = calloc(1, sizeof(tuser));
	new->user = u;

	if (lu->first == NULL) {
		lu->first = new;
		lu->last  = new;
	} else {
		lu->last->next = new;
		lu->last = new;
	}
}

/* Delete an element in the linked list */
void del(tlistC * lc, channel * c);
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
		if (cur->next->channel == ) {
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
void del(tlistU * lu, user    * u);
{
	/* lu is empty do nothing */
	if (lu->first == NULL) {
		return;
	}

	/* special case when u is the head of the list */
	if (l->first->user == u) {
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
		if (cur->next->user == u) {
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

/* Search an element in the linked list */
channel search(channel * lc, channel * c); // or by the ID ?
{

}
user    search(user    * lu, user    * u); // or by the ID ?
{

}

#endif	// LINKEDLIST_H_INCLUDE
