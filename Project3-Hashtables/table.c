//Jonathan Sofer

//These functions will implement a hash table data structure for strings

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "set.h"

#define EMPTY 0
#define FILLED 1
#define DELETED 2

struct set
{
	int count;
	int length;
	char **elts;
	char *flags;
};

//Function to create a hash key for a string 
//Runtime 0(n)
unsigned hashString(char *s)
{
	unsigned hash = 0;

	while (*s != '\0')
		hash = 31 * hash + *s ++;

	return hash;
}

//Function to return the index of the element in the set, or -1 if not found
//Best case runtime 0(1) ; Worst case runtime 0(n)
int findElement(SET *sp, char *elt, bool *found)
{
	int i;
	unsigned hash = hashString(elt);
	unsigned index;
	int rememberslot = -1;
	int firstdeletedslot = 0;
	for (i = 0; i < sp-> length; i++)
	{
		index = (hash + i) % sp->length;
		if (sp->flags[index] == EMPTY)
		{
			*found = false;
			if(rememberslot == -1) //we did not previously pass a deleted slot, so we'll store our key here
				return index;
			else
				return rememberslot; //we previously passed a deleted slot, so we'll store our new key there
		}	
		else if (sp->flags[index] == DELETED)
		{
		   	if (firstdeletedslot == 0) //this is the first deleted slot we passed
			{
				rememberslot = index; //set rememberslot to that index
				firstdeletedslot = 1; //stop us from remembering the next deleted slot (if there is one)
			}
		}
		else if (sp->flags[index] == FILLED)
		{
			if (strcmp(elt, sp->elts[index]) == 0)
			{
				*found = true;
				return index; //we found our key
			}
		}
	}
	*found = false;
	return (-1); //we did not find the key; should've returned rememberslot
}

//Function to create a set
//Runtime O(n) 
SET *createSet(int maxElts)
{
	int i;

	SET *sp;
	sp = malloc(sizeof(SET));
	assert (sp != NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->elts = malloc(sizeof(char*)*maxElts);
	assert(sp->elts != NULL);
	sp->flags=malloc(sizeof(char)*maxElts);
	assert(sp->flags != NULL);

	for (i = 0; i < sp->length; i++)
	{
		sp->flags[i] = EMPTY; //init flags to empty
	}
	return sp;
}

//Function to destroy a set
//Runtime O(n)
void destroySet(SET *sp)
{
	int i;
	assert(sp != NULL);
	for (i = 0 ; i < sp -> count; i++) //count = length?
		if (sp -> flags[i] == FILLED)
			free(sp -> elts[i]);
	free (sp -> elts);
	free (sp -> flags);
	free (sp);
	return;	
}

//Function to count the number of strings in the set
//Runtime O(1)
int numElements(SET *sp)
{
	assert (sp != NULL);
	return (sp -> count);
}

//Function to check if an element is in the set
//Best case runtime 0(1) ; Worst case runtime 0(n)
bool hasElement(SET *sp, char *elt)
{
	bool found;
	assert (sp != NULL && elt != NULL);
	findElement(sp, elt, &found);
	return found;
}

//Function to add a word to the set
//Best case runtime 0(1) ; Worst case runtime 0(n)
bool addElement(SET *sp, char *elt)
{
	int i;
	int index;
	bool found;
	assert(sp != NULL && elt != NULL);
	elt = strdup(elt); //no need if not added
	index = findElement(sp, elt, &found);
	if (found == true)
		return false; //we are not adding the element to the array because it is already there
	if (sp->count >= sp->length)
		return false; //we are not adding the element to the array because it is full
	sp->elts[index] = elt;
	sp->flags[index] = FILLED;
	(sp->count)++;
	return true; //we have added the element to the array
}

//Function to remove a word from the set
//Best case runtime 0(1) ; Worst case runtime 0(n)
bool removeElement(SET *sp, char *elt)
{
	int i;
	int index;
	bool found;
	assert (sp != NULL && elt != NULL);
	if (sp->count == 0)
		return false; //there are no elements in the array
	index = findElement(sp, elt, &found);
	if (found == false)
		return false; //we are not removing the element because it is not in the array
	free(sp->elts[index]);
	sp->flags[index] = DELETED;
	(sp->count)--;
	return true; //we have removed the element from the array	
}

