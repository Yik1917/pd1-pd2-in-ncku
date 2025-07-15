#include <stdio.h>
#include <string.h>
#include "hw7-2.h"
extern char command[51][21];
char *getUserInput()
{
	fgets(command[50], 21, stdin);
	command[50][strcspn(command[50], "\n")] = '\0';
	return command[50];
}

void printAllInput(char C[][21], int n)
{
	for (int i = 0; i < n; i++)
		printf("%s\n", C[i]);
}
