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

	int str_len, i;

	if (argc != 3) {
		printf ("Usage : %s <IP> <Port> \n", argv[0]);
		exit (1);
	}

	sock = socket ( PF_INET, SOCK_STREAM, 0 );
	if ( sock == -1 )
		error_handling ( "socket() error" );

	memset ( &serv_adr, 0, sizeof ( serv_adr ) );
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr ( argv[1] );
	serv_adr.sin_port = htons ( atoi ( argv[2] ) );

	if ( connect ( sock, ( struct sockaddr* ) &serv_adr, sizeof ( serv_adr ) ) == -1 )
		error_handling ( "connect() error" );

	while ( 1 ) {
		fputs ( "input message: ", stdout );
		fgets ( message, BUF_SIZE, stdin);

		if ( !strcmp ( message, "q\n") || !strcmp ( message, "Q\n") )
			break;

		printf ( "confirm message: %s \n", message );
		write ( sock, message, strlen ( message ) );
	}

	close ( sock );

	return 0;
}

void error_handling ( char *message ) {
	fputs ( message, stderr );
	fputc ( '\n', stderr );
	exit ( 1 );
} 