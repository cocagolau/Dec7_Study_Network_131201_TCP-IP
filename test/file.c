#include <stdio.h>
#include <fcntl.h>
                   
int main( void)
{
    int     fd;
    FILE   *fp;
    size_t n_size = 1024;
    char buf[1024] = "abc";
        
    fd  = open( "main.txt", O_CREAT|O_WRONLY|O_TRUNC);
    fp  = fdopen( fd, "w");
    
    fwrite ( buf, 1, n_size, fp );
    
    fclose( fp);
}