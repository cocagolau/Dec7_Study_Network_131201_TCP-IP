#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling ( char * msg );

int main ( int argc, char * argv[] ) {

	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_size;

	char msg [ BUF_SIZE ];
	char buf [ BUF_SIZE ];
	int str_len, msg_len, i, recv_len = 0, curr_len;

	if ( argc != 2 ) {
		printf ( "Usage: %s <IP> \n", argv[0] );
		exit ( 1 );
	}

	serv_sock = socket ( PF_INET, SOCK_STREAM, 0 );
	if ( serv_sock == -1 )
		error_handling ( "socket() error" );

	memset ( &serv_adr, 0, sizeof ( serv_adr ) );
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl ( INADDR_ANY );
	serv_adr.sin_port = htons ( atoi ( argv[1] ) );

	if ( bind ( serv_sock, ( struct sockaddr* ) &serv_adr, sizeof ( serv_adr ) ) == -1 )
		error_handling ( "bind() error" );

	if ( listen ( serv_sock, 5 ) == -1 ) 
		error_handling ( "listen() error" );

	clnt_adr_size = sizeof ( clnt_adr );
	for ( i=0; i<3; i++ ) {
		clnt_sock = accept ( serv_sock, ( struct sockaddr* ) &clnt_adr, &clnt_adr_size );

		while  ( str_len = read ( clnt_sock, buf, 4 ) ) {
			if ( str_len == -1 ) {
				close ( clnt_sock );
				break;
			}

			msg_len = ( int ) buf[0];

			printf ( "msg_len: %d \n", msg_len );
		}
	}

	close ( serv_sock );
	return 0;
}

void error_handling ( char * msg ) {

	fputs ( msg, stderr );
	fputc ( '\n', stderr );
	exit ( 1 );
}
