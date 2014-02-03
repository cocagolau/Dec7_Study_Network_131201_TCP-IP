#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100
#define INSZ 4

void error_handling ( char *message );

int main ( int argc, char *argv[] ) {

	int sock;
	struct sockaddr_in serv_adr;
	char message[BUF_SIZE];
	// char operator_code;
	int str_len;
	int operand_num, result, i;

	if ( argc != 3 ) {
		printf ( "Usage : %s <IP> <Port> \n", argv[0] );
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

	// while ( 1 ) {
		fputs ( "input Number of Operand: ", stdout );
		scanf ( "%d", &operand_num );
		fputs ( "-----------------\n", stdout );

		message[0] = ( char ) operand_num;
		for ( i=0; i<operand_num; i++ ) {
			fputs ( "input operand: ", stdout );
			scanf ( "%d", ( int * ) &message[ ( INSZ * i ) + 1 ] );
		}
		fputs ( "-----------------\n", stdout );

		fgetc ( stdin ); // clearing stdin buffer
		fputs ( "input operator: ", stdout );
		scanf ( "%c", &message[ ( operand_num * INSZ ) + 1 ] );

		write ( sock, message, ( operand_num * INSZ ) + 2 );

		read ( sock, &result, INSZ );
		fputs ( "-----------------\n", stdout );
		printf ( "result: %d \n", result );
	// }


	close ( sock );

	return 0;
}

void error_handling ( char *message ) {
	fputs ( message, stderr );
	fputc ( '\n', stderr );
	exit ( 1 );
}
