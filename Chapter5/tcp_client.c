#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling ( char * msg );

int main ( int argc, char * argv[] ) {

	int sock;
	struct sockaddr_in serv_adr;
	char buf [ BUF_SIZE - 5 ];
	char msg [ BUF_SIZE ];

	int msg_len, str_len, i;

	if ( argc != 3 ) {
		printf ( "Usage: %s <IP> <Port> \n", argv[0] );
		exit ( 1 );
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
		fputs ( "input message(Quit: q): ", stdout );
		fgets ( buf, sizeof ( buf ), stdin );

		if ( !strcmp ( buf, "q\n" ) || !strcmp ( buf, "Q\n" ) )
			break;


		str_len = strlen ( buf ) - 1;
		
		msg[0] = ( char ) str_len;
		&msg[4] = buf;

		

		write ( sock, msg, BUF_SIZE );


	}

	close ( sock );



	return 0;
}

void error_handling ( char * msg ) {

	fputs ( msg, stderr );
	fputc ( '\n', stderr );
	exit ( 1 );
}

