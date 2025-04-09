  edit 2
  /* I made an edit */ 

/* use this code to compare times using the standard library vs POSIX 

from: https://www.reddit.com/r/C_Programming/comments/ho8cxv/use_system_calls_or_standard_library_functions/

 */


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void do_syscall( size_t count, size_t size )
{
    char *buffer = malloc( size );
    for (int i=0;i!=size;i++)
        buffer[i] = i%256;
    
    int d = open( "data.raw", O_CREAT|O_WRONLY, 0666 );
    while (count--)
        write( d, buffer, size );
    
    close( d );
}

void do_stdlib( size_t count, size_t size )
{
    char *buffer = malloc( size );
    for (int i=0;i!=size;i++)
        buffer[i] = i%256;
    
    FILE *f = fopen( "data.raw", "wb" );
    while (count--)
        fwrite( buffer, size, 1, f );
    
    fclose( f );
}

int main( int argc, char **argv )
{
    if (argc!=4)
    {
        fprintf( stderr, "%s : count size y/n\n", argv[0] );
        return EXIT_FAILURE;
    }

    size_t count = atoi( argv[1] );
    size_t size = atoi( argv[2] );
    int use_syscall = (argv[3][0]=='y');

    if (use_syscall)
        do_syscall( count, size );
    else
        do_stdlib( count, size );
    return 0;
}
