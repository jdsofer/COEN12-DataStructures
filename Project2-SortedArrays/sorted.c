//Jonathan Sofer

//These functions will implement a sorted array data structure for strings, using a set

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

//Function to return the index of the element in the set, or where the element should go if not found using a binary search
//Runtime O(log n)
int findElement(SET *sp, char *elt, bool *found)
{
	int lo, hi, mid, diff;
	lo = 0;
	hi = (sp->count) - 1;
	while (lo <= hi)
	{
		mid = (lo + hi)/2;
		diff = strcmp(elt, sp->elts[mid]);
		if (diff < 0)
			hi = mid-1; //element is in the first half of our current range (if there)
		else if (diff > 0)
			lo = mid+1; //element is in the second half of our current range (if there)
		else
		{
			*found = true; //word found
			return mid;
		}
	}
	*found = false;
	return lo;
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
//Runtime O(log n)
bool hasElement(SET *sp, char *elt)
{
	bool found;
	assert (sp != NULL && elt != NULL);
	findElement(sp, elt, &found);
	return found;
}

//Function to add a word to the set
//Runtime O(n)
bool addElement(SET *sp, char *elt)
{
	int i,x;
	bool found;
	assert(sp != NULL && elt != NULL);
	elt = strdup(elt);
	x = findElement(sp, elt, &found);
	if (found == true)
		return false; //we are not adding the element to the array because it is already there
	if (sp->count >= sp->length)
		return false; //we are not adding the element to the array because it is full
	for (i = sp->count ; i > x ; i--)
		sp->elts[i] = sp->elts[i-1]; //shifting all values after x to the right
	sp->elts[x] = elt;
	(sp->count)++;
	return true; //we have added the element to the array
}

//Function to remove a word from the set
//Runtime O(n)
bool removeElement(SET *sp, char *elt)
{
	int i,x;
	bool found;
	assert (sp != NULL && elt != NULL);
	if (sp->count == 0)
		return false; //there are no elements in the array
	x = findElement(sp, elt, &found);
	if (found == false)
		return false; //we are not removing the element because it is not in the array
	for (i = x+1; i < sp->count ; i++)
		sp->elts[i-1] = sp->elts[i]; //shifting all values starting at the value after x to the left
	(sp->count)--;
	return true; //we have removed the element from the array	
}

