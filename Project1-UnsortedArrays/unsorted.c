//Jonathan Sofer

//These functions will implement an unsorted array data structure for strings, using a set

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "set.h"

struct set
{
	int count;
	int length;
	char **elts;
};

//Function to return the index of the element in the set, or -1 if not found, using sequnetial search
//Runtime O(n)
int findElement(SET *sp, char *elt, bool *found)
{
	int i;
	for (i = 0; i < (sp->count); i++)
	{
		if(strcmp(sp->elts[i],elt) == 0)
		{
			return i;
		}
	}
	return -1;
}

//Function to create a set
//Runtime O(1) 
SET *createSet(int maxElts)
{
	SET *sp;
	sp = malloc(sizeof(SET));
	assert (sp != NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->elts = malloc(sizeof(char*)*maxElts);
	assert(sp->elts != NULL);
	return sp;
}

//Function to destroy a set
//Runtime O(n)
void destroySet(SET *sp)
{
	int i;
	assert(sp != NULL);
	for (i = 0 ; i < sp -> count; i++)
		free(sp -> elts[i]);
	free (sp -> elts);
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
//Runtime O(n)
bool hasElement(SET *sp, char *elt)
{
	bool found;
	assert (sp != NULL && elt != NULL);
	if (findElement(sp, elt, &found) > -1)
		return true;
	return false;
}

//Function to add a word to the set
//Runtime O(n)
bool addElement(SET *sp, char *elt)
{
	bool found;
	assert(sp != NULL && elt != NULL);
	elt = strdup(elt);
	if (findElement(sp, elt, &found) > -1)
		return false; //we are not adding the word to the set because it is already there
	sp->elts[sp->count] = elt;
	(sp->count)++;
	return true; //we are adding the word to the set at the end of the array
}

//Function to remove a word from the set
//Runtime O(n)
bool removeElement(SET *sp, char *elt)
{
	bool found;
	int x;
	assert (sp != NULL && elt != NULL);
	x = findElement(sp, elt, &found);
	if (x != -1)
	{
		sp->elts[x] = sp->elts[(sp->count)-1];
		(sp->count)--;
		return true; //we are removing the word from the set by replacing it with the word at the end of the array, then decrementing the counter
	}
	return false; //we are not removing the word from the set because it isn't there
}

