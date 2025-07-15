#include <stdio.h>
#include <string.h>
#include "hw7-1.h"

int GameStart()
{
	char input[100];
	puts("Welcome to the game A = B, please select the level");
	fgets(input, sizeof(input), stdin);
	input[strcspn(input, "\n")] = '\0';
	if (strlen(input) > 1)
		return -1;
	if (input[0] == '1')
		return 1;
	if (input[0] == '2')
		return 2;
	return -1;
}
