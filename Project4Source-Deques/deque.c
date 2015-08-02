//Jonathan Sofer

//These funcitons will implement a deque using a doubly-linked list with a dummy node

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "deque.h"

#define DUMMY dp->head

typedef struct node
{
	int data;
	struct node *next;
	struct node *prev;
}NODE;

struct deque
{
	int count;
	NODE *head;
};

//Function to create a deque
//Runtime O(1)
DEQUE *createDeque(void)
{
	DEQUE *dp;
	dp = malloc(sizeof(DEQUE));
	assert (dp != NULL);
	dp->count = 0;
	dp->head = malloc(sizeof(NODE));
	assert (dp->head != NULL);
	DUMMY->next = DUMMY;
	DUMMY->prev = DUMMY;
	return dp;
}

//Function to destroy a deque
//Runtime O(n)
void destroyDeque(DEQUE *dp)
{
	assert (dp != NULL);
	NODE *p, *q;
	p = q = DUMMY->next;
	while (p != DUMMY)
	{
		q = p;
		p = p->next;
		free(q);
	}
	free(DUMMY);
	free(dp);
}

//Function to count the number of items in the deque
//Runtime O(1)
int numItems(DEQUE *dp)
{
	assert (dp != NULL);
	return (dp->count);
}

//Function to add element x to the start of the deque
//Runtime O(1)
void addFirst(DEQUE *dp, int x)
{
	assert (dp != NULL);
	NODE *temp;
	temp = malloc(sizeof(NODE));
	temp->data = x;
	temp->prev = DUMMY;
	temp->next = DUMMY->next;
	temp->next->prev = temp;
	DUMMY->next = temp;	
	(dp->count)++;

}

//Function to add element x to the end of the deque
//Runtime O(1)
void addLast(DEQUE *dp, int x)
{
	assert (dp != NULL);
	NODE *temp;
	temp = malloc(sizeof(NODE));
	temp->data = x;
	temp->next = DUMMY;
	temp->prev = DUMMY->prev;
	DUMMY->prev->next = temp;
	DUMMY->prev = temp;
	(dp->count)++;
}

//Function to remove the first item in the deque (given the deque is not empty)
//Runtime O(1)
int removeFirst(DEQUE *dp)
{
	assert (dp != NULL);
	if (dp->count == 0)
		return -1;

	int x;
	NODE *temp, *np;
	temp = DUMMY;
	np = temp->next;
	temp->next = np->next;
	np->next->prev = temp;
	x = np->data; //save the data before we delete its node
	free (np);
	(dp->count)--;
	return x;
}

//Function to remove the last item in the deque (given the deque is not empty)
//Runtime O(1)
int removeLast(DEQUE *dp)
{
	assert (dp != NULL);
	if (dp->count == 0)
		return -1;

	int x;
	NODE *temp, *np;
	temp = DUMMY;
	np = temp-> prev;
	np->prev->next = temp;
	temp->prev = np->prev;
	x = np->data; //save the data before we delete its node
	free(np);
	(dp->count)--;
	return x;
}

//Function to return the first item in the deque
//Runtime O(1)
int getFirst(DEQUE *dp)
{
	assert (dp != NULL);
	if (dp->count == 0)
		return -1;

	return DUMMY->next->data;
}

//Function to return the last item in the deque
//Runtime O(1)
int getLast(DEQUE *dp)
{
	assert (dp != NULL);
	if (dp->count == 0)
	   return -1;

	return DUMMY->prev->data;	
}
