#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define BUF_SIZE 100

void error_handling (char *message);

int main (void)
{

	int fd_read;
	int fd_write;
	int str_len;

	// char buf[BUF_SIZE] = "";
	char buf[BUF_SIZE] = {0,};
	// char buf[BUF_SIZE];

	fd_read = open ("data.txt", O_RDONLY);
	if (fd_read == -1)
		error_handling ("open() error!");

	if (read (fd_read, buf, sizeof (buf)) == -1)
		error_handling ("read() error!");

	close (fd_read);
	printf ("read data.txt: %s", buf);

	fd_write = open ("data_copy.txt", O_CREAT|O_WRONLY|O_TRUNC);
	if (fd_write == -1)
		error_handling("open() error!");

	printf ("buf: %s", buf);
	str_len = strlen (buf);

	if (write (fd_write, buf, str_len) == -1)
		error_handling("write() error!");

	printf ("after buf: %s", buf);

	close (fd_write);
	return 0;
}

void error_handling (char *message)
{
	fputs (message, stderr);
	fputc ('\n', stderr);
	exit (1);
}