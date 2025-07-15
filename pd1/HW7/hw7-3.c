#include <stdio.h>
#include "hw7-3.h"

void ParsingData(char *command, char *string1, char *string2)
{
	sscanf(command, "%s = %s", string1, string2);
}
