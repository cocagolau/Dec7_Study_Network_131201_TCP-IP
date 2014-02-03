#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling ( char *message );

int main ( int argc, char *argv[] ) {

	int sock;
	struct sockaddr_in serv_adr;
	char message[BUF_SIZE];
	int i;

	if (argc != 3) {
		printf ("Usage : %s <IP> <Port> \n", argv[0]);
		exit (1);
	}

	sock = socket ( PF_INET, SOCK_STREAM, 0 );
	if ( sock == -1 )
		error_handling ( "socket() error" );

	return 0;
}

void error_handling ( char *message ) {
	fputs ( message, stderr );
	fputc ( '\n', stderr );
	exit ( 1 );
}