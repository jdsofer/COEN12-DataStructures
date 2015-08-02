//Jonathan Sofer

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 30

//This program will be reading words into a buffer and outputing the total amount of words read in
int main (int argc, char *argv[])
{
	
	int counter = 0;
	char buffer[MAX_WORD_LENGTH];
	FILE *fp;

	//Check to see that both arguments into main are recieved
	if (argc == 1)
	{
		printf("The file you wish to count is missing.\n");
		return 1;
	}	
	
	//Check to see that the text file can be opened
	fp = fopen(argv[1], "r");
    if (fp == NULL)
	{
		printf("Unable to open file for reading.\n");
		return 1;
	}

	//Reading in words into a buffer and counting how may words are read in	
	while (fscanf(fp, "%s", buffer) > 0)
	{
		counter++;
	}
	fclose(fp);

	printf("%d total words\n", counter);

}
