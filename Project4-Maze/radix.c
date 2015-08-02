//Jonathan Sofer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#include "deque.h"

#define R 10

int main()
{
	int i, j;
	int input;
	int temp;
	int max = 0;
	int digits;
	int Bucket;
	int exp = 1;

	DEQUE *MainDeque;
	MainDeque = createDeque(); //Creating our main deque
	DEQUE *RDeque[10];
	for (i = 0 ; i < R ; i++)
	{
		RDeque[i] = createDeque(); //Creating our temporary decks for radix sorting
	}
		
	printf("Please enter non-negative integers to be sorted.\n");
	while (scanf("%d", &input) == 1)
	{
		if(input >= 0)
		{
			addLast(MainDeque , input);//Add the number to the main deque
			if (input > max)
			{
				max = input; //We need to keep track of the max integer
			}
		}
		else //User tried to input a negative number
		{
			printf("Sorry, radix sort does not work on negative numbers.\n");
			return 0;
		}
	}

	digits = ceil(log(max+1)/log(R)); //digits will tell us how many times to loop through our algorithm

	//Radix sort algorithm using our MainDeque and an array of R deques
	for (i = 0 ; i < digits ; i++) //Main for loop that will go "digits" amount of times
	{
		while (numItems(MainDeque) > 0) //Keep going while MainDeque has values
		{
			temp  = removeFirst(MainDeque); 
			Bucket = (temp/exp) % 10; //Bucket is equal to the (value / (R^i)) mod R
			addLast(RDeque[Bucket], temp); 
		}
		for (j = 0 ; j < R ; j++) //Loop to put back each value from the buckets into the MainDeque
			while(numItems(RDeque[j]) > 0) 
				addLast(MainDeque, removeFirst(RDeque[j]));
		exp *=10;
	}	

	while(numItems(MainDeque) > 0) //Print to the screen each item in MainDeque 
	{
		temp = removeFirst(MainDeque);
		printf("%d\t", temp);
	}

	return 0;
}
