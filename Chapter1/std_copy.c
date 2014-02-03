#include <stdio.h>
#include <stdlib.h>

void error_handling (char *message);

int main (void)
{
	FILE *stream1;
	FILE *stream2;
	int input = 0;

	stream1 = fopen ("data.txt", "r");
	stream2 = fopen ("data_std_copy.txt", "w");
	if (stream1 == NULL || stream2 == NULL)
		error_handling ("fopen() error!");

	while (input != EOF)
	{
		input = fgetc (stream1);
		fputc (input, stream2);
	}

	fclose (stream1);
	fclose (stream2);

	return 0;
}

void error_handling (char *message)
{
	fputs (message, stderr);
	fputc ('\n', stderr);
	exit (1);
}