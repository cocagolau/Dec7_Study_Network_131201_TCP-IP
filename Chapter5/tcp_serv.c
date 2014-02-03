#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling ( char *message );

int main ( int argc, char *argv[] ) {

	return 0;
}

void error_handling ( char *message ) {
	fputs ( message, stderr );
	fputc ( '\n', stderr );
	exit ( 1 );
}