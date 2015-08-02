//Jonathan Sofer

//This program will use Huffman coding to compress a text file

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#include "tree.h"
#include "pack.h"

//Declarations for three global arrays
int CountArray[257]; //Holds the count for each ASCII character
struct tree *LeavesArray[257]; //The array that holds the leaf for each ASCII character
struct tree *Heap[257]; //The heap we will use to create our huffman tree

//Function to traverse a tree recursively and assign 1's and 0's to its path
void printEncoding(struct tree *leaf)
{
	if (getParent(leaf) == NULL )
		return;
	if ((getLeft(getParent(leaf))) == leaf) //I'm the left child
	{
		printEncoding(getParent(leaf));
		printf("0");
	}	
	if ((getRight(getParent(leaf))) == leaf) //I'm the right child
	{
		printEncoding(getParent(leaf));
		printf("1");
	}
}

//Function that returns the parent's index of a node in the array
int ParentIndex(int i)
{
	return (floor((i-1)/2));
}

//Function that returns the left child of a node in the array
int LeftChild(int i)
{
	return ((2*i) + 1);
}

//Function that returns the right child of a node in the array
int RightChild(int i)
{
	return ((2*i) + 2);
}

//Function to insert a new node into a binary heap
void insert(struct tree *new, int i)
{
	//i is our array index
	//This loop will mantain heap order before we insert our new node into the heap
	while (i > 0 && getData(Heap[ParentIndex(i)]) > getData(new))
	{
		Heap[i] = Heap[ParentIndex(i)]; //Copy parent's data into index's slot (if parent's data > index's) 
		i = ParentIndex(i);
	}
	Heap[i] = new;	
}

//Function to return the minimum value (i.e., the first value) in a binary heap
struct tree *deleteMin(int Counter)
{
	int i;
	int Child;
	struct tree *minLeaf;
	struct tree *temp;
	minLeaf = Heap[0];
	temp = Heap[Counter-1];

	i = 0;
	//This loop will maintain heap order after deleting the first node in the heap
	while (LeftChild(i) < Counter-1)
	{
		Child = LeftChild(i); //Assume smallest child is the left child
		if (RightChild(i) < Counter-1 && getData(Heap[LeftChild(i)]) > getData(Heap[RightChild(i)]))
		{
			Child = RightChild(i); //Assign if smallest child is actually the right child
		}
		if (getData(Heap[Child]) < getData(temp)) //Check to see that our child is smaller than the last node
		{
			Heap[i] = Heap[Child]; //Replace node by its smallest child
			i = Child; //Repeat process for the child
		}
		else
			break;
	}
	Heap[i] = temp;
	return minLeaf;
}

//Function to create the initial binary heap of leaves using the data in LeavesArray
void create()
{
	int i, j;
	j = 0;
	for (i = 0; i < 257 ; i++)
	{
		if (LeavesArray[i] != NULL)
		{
			insert(LeavesArray[i], j);
			j++;
		}
	}
	return;
}

//Function to read in a file and insert each ASCII character's count into the CountArray
void read_file (char *myfile)
{
	int c;
	FILE *fp;
	fp = fopen(myfile, "rb");
	if (fp == NULL)
	{
		printf("File Not Found.\n");
		return;
	}
	while ((c = getc(fp)) != EOF) //read in characters until the End of File (EOF)
	{
		CountArray[c]++; //increment that character's count
	}
	fclose(fp);
	return;
}

int main (int argc, char *argv[])
{	
	struct tree *left;
	struct tree *right;
	struct tree *new;
	int Counter = 0;
	int i;
	for (i = 0; i < 257 ; i++)
	{
		CountArray[i] = 0;
		LeavesArray[i] = NULL;
	}

	if (argc != 3)
	{
		printf("The input and/or output file is missing.\n");
		return 1;
	}

	//read in file
	read_file(argv[1]);
	
	//We are creating an array of tree nodes with the count for each character as that node's data
	//Each tree node will be placed in the array index corresponding to its ASCII value 
	for (i = 0; i < 257 ; i++)
	{
		if(CountArray[i] != 0)
		{
			LeavesArray[i] = createTree(CountArray[i], NULL, NULL);
			Counter++;
		}
	}
	LeavesArray[256] = createTree(0, NULL, NULL); //create tree for EOF marker
	Counter++;

	//create the initial binary heap
	create();
	
	//While there is more than one node in the tree we will repeatedly remove the two minimum nodes in the array to create a new tree
	//This process will continue until there is only one tree left; this will be our huffman tree at Heap[0]
	while (Counter > 1)
	{
		//Get the two minimum values in the heap; one will be the left child and one will be the right child of our new tree
		//Decrement the Counter twice 
		left = deleteMin(Counter);
		Counter--;
		right = deleteMin(Counter);
		Counter--;
		
		//Create a new tree with the data from our above trees
		//Increment the Counter once
		new = createTree(getData(left)+getData(right), left, right); //new points to left and right as its parent
		setLeft(new, left); //left points to new as new's left child
		setRight(new, right); //right points to new as new's right child
		insert(new, Counter);
		Counter++;
	}
	
	//Print the ASCII value of each leaf, along with the character's count and its encoding using the huffman tree
	for (i = 0; i < 257 ; i++)
	{
		if (LeavesArray[i] != NULL)
		{
			if (isprint(i)) 
				printf("'%c': ", i);
			else
				printf("%o : ", i);
			printf("%d ", getData(LeavesArray[i]));
			printEncoding(LeavesArray[i]);
			printf("\n");
		}
	}
	
	//Pass our LeavesArray to pack
	pack(argv[1], argv[2], LeavesArray);

	return 1;
}
