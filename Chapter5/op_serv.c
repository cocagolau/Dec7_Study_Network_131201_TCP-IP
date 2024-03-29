#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100
#define INSZ 4

void error_handling ( char *message );
int calculate ( char operator_code, int operand[], int opnum );
int main ( int argc, char *argv[] ) {

	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;

	int operand_num, result=0, i, str_len;
	int operand[BUF_SIZE];
	char message[BUF_SIZE];
	char operator_code;

	if ( argc != 2 ) {
		printf ( "Usage : %s <port>\n", argv[0] );
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

	clnt_adr_sz = sizeof ( clnt_adr );
	
		clnt_sock = accept ( serv_sock, ( struct sockaddr* ) &clnt_adr, &clnt_adr_sz );
		if ( clnt_sock == -1 )
			error_handling ( "accept() error" );

		read ( clnt_sock, message, 1 );
		

		operand_num = ( int ) message[0];
		// printf ( "operand_num: %d \n", operand_num );

		for ( i=0; i<operand_num; i++ ) {
			read ( clnt_sock, &operand[i], INSZ );
			// printf ( "operand(%d): %d \n", i+1, operand[i] );
		}

		read ( clnt_sock, &operator_code, 10 );
		printf ( "operator: %c \n", operator_code );
//--------------------------------------
		read ( clnt_sock, &operator_code, 10 );
		result = calculate ( operator_code, operand, operand_num );
		write ( clnt_sock, &result, INSZ );

		close ( clnt_sock );
	
	close ( serv_sock );



	return 0;
}

void error_handling ( char *message ) {
	fputs ( message, stderr );
	fputc ( '\n', stderr );
	exit ( 1 );
}

int calculate ( char operator_code, int operand[], int opnum ) {
	int result = operand[0], i;

	switch ( operator_code ) {
		case '+' :
			for ( i=1; i<opnum; i++ )
				result += operand[i];
			break;

		case '-' :
			for ( i=1; i<opnum; i++ )
				result -= operand[i];
		break;

		case '*' :
			for ( i=1; i<opnum; i++ )
				result *= operand[i];
		break;
	}

	return result;
}