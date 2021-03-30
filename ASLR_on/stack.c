/* stack.c */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int bof(char *str)
{
	char buffer[400];
	/* The following statement has a buffer overflow problem */

	strcpy(buffer, str);
	printf("Buffer now: %s",buffer);
	return 1;
}

int main(int argc, char **argv)
{
	for(int i=0;i<20;i++)
		printf("New process created\n");
	char str[517];
	FILE *badfile;
	badfile = fopen("badfile", "r");
	fread(str, sizeof(char), 517, badfile);
	bof(str);
	printf("Returned Properly\n");
	return 1;
}

