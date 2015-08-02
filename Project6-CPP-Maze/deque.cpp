//Jonathan Sofer

//These funcitons will implement a deque using a doubly-linked list with a dummy node in C++

#include <cassert>
#include "deque.h"
#define DUMMY head

class Node
{
	public:
	int data;
	class Node *next;
	class Node *prev;
};

//Function to create a deque
//Runtime O(1)
Deque::Deque()
{
	count = 0;
	head = new Node;
	DUMMY->next = DUMMY;
	DUMMY->prev = DUMMY;
}

//Function to destroy a deque
//Runtime O(n)
Deque::~Deque()
{
	Node *p, *q;
	p = q = DUMMY->next;
	while (p != DUMMY)
	{
		q = p;
		p = p->next;
		delete q;
	}
	delete DUMMY;
}

//Function to count the number of items in the deque
//Runtime O(1)
int Deque::size()
{
	return count;
}

//Function to add element x to the start of the deque
//Runtime O(1)
void Deque::addFirst(int x)
{
	Node *temp;
	temp = new Node;
	temp->data = x;
	temp->prev = DUMMY;
	temp->next = DUMMY->next;
	temp->next->prev = temp;
	DUMMY->next = temp;	
	count++;
}

//Function to add element x to the end of the deque
//Runtime O(1)
void Deque::addLast(int x)
{
	Node *temp;
	temp = new Node;
	temp->data = x;
	temp->next = DUMMY;
	temp->prev = DUMMY->prev;
	DUMMY->prev->next = temp;
	DUMMY->prev = temp;
	count++;
}

//Function to remove the first item in the deque (given the deque is not empty)
//Runtime O(1)
int Deque::removeFirst()
{
	assert (count != 0);

	int x;
	Node *temp, *np;
	temp = DUMMY;
	np = temp->next;
	temp->next = np->next;
	np->next->prev = temp;
	x = np->data; //save the data before we delete its node
	delete np;
	count--;
	return x;
}

//Function to remove the last item in the deque (given the deque is not empty)
//Runtime O(1)
int Deque::removeLast()
{
	assert (count != 0);

	int x;
	Node *temp, *np;
	temp = DUMMY;
	np = temp-> prev;
	np->prev->next = temp;
	temp->prev = np->prev;
	x = np->data; //save the data before we delete its node
	delete np;
	count--;
	return x;
}

//Function to return the first item in the deque
//Runtime O(1)
int Deque::getFirst()
{
	assert (count != 0);
	return DUMMY->next->data;
}

//Function to return the last item in the deque
//Runtime O(1)
int Deque::getLast()
{
	assert (count != 0);
	return DUMMY->prev->data;	
}
