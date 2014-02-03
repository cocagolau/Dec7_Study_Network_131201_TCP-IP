#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling (char *msg);

int main (int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char msg[BUF_SIZE] = {0,};
	int msg_idx = 0;
	int str_len, i;

	if (argc != 3)
	{
		printf ("Usage : %s <IP> <port>\n", argv[0]);
		exit (1);
	}

	while (1) {
		fputs ("If you want to quit - Press q/Q: ", stdout);
		fgets (msg, sizeof (msg), stdin);
		printf ("msg: %s", msg);

		sock = socket (PF_INET, SOCK_STREAM, 0);
		if (sock == -1)
			error_handling ("socket() error");

		memset (&serv_addr, 0, sizeof (serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = inet_addr (argv[1]);
		serv_addr.sin_port = htons (atoi (argv[2]));

		if (connect (sock, (struct sockaddr*) &serv_addr, sizeof (serv_addr)) == -1)
			error_handling ("connect() error!");
		else
			printf ("connected....... \n");

		str_len = write (sock, msg, BUF_SIZE);
		if (!strcmp (msg, "q\n") || !strcmp (msg, "Q\n"))
			break;

		for (i=0; i<str_len; i++) {
			msg[i] = 0;
		}

		str_len = read (sock, msg, BUF_SIZE);
		close (sock);

		for (i=0; i<str_len; i++) {
			msg[i] = 0;
		}
		
	}
	close (sock);
	return 0;
}

void error_handling (char *msg)
{
	fputs (msg, stderr);
	fputc ('\n', stderr);
	exit (1);
}