/*	pipedemo2.c	*	Demonstrates: how to pipe is duplicated in fork()
 *				*	Parent continues to write and read pipe,   
 *				*	but child also writes to the pipe
 */

#include	<stdio.h>

#define		CHILD_MESS	"I want a cookie\n"
#define		PAR_MESS	"testing..\n"
#define		oops(m,x)	{ perror(m); exit(x); }


void main()
{
	int		pipefd[2];				// the pipe
	int		len;					// for write
	char	buf[BUFSIZ];			// for read
	int		read_len;

	/* get a pipe */
	if (pipe (pipefd) == -1)
		oops("cannot get a pipe", 1);

	switch( fork() ) {
		case -1:
			oops("cannot fork", 2);

		// child process writes to pipe every 5 seconds
		case 0:
			len = strlen(CHILD_MESS);
			while (1) {
				if ( write(pipefd[1], CHILD_MESS, len) != len )
					oops("write", 3);
				sleep(5);
			}

		// parent process reads from pipe and also writes to pipe 
		default:
			len = strlen( PAR_MESS );
			while (1) {
				if ( write( pipefd[1], PAR_MESS, len ) != len )
					oops("write", 4);
				sleep(1);
				read_len = read( pipefd[0], buf, BUFSIZ );
				if ( read_len <= 0 )
					break;
				write( 1, buf, read_len );
			}
	} // end of switch
}
