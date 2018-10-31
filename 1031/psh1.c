/*	prompting shell version 1
 *		Prompts for the command and its arguments.
 *		builds the argument vector for the call to execvp.
 *		Uses execvp(), and never returns.
 */

#include	<stdio.h>
#include	<signal.h>
#include	<string.h>
#include	<stdlib.h>

#define MAXARGS	20
#define	ARGLEN	100

char* makestring(char*);			// cmdline args
int execute(char* []);				// token length

int main()
{
	char	*arglist[MAXARGS+1];	// an array of ptrs for arg
	int		numargs = 0;			// index into array
	char	argbuf[ARGLEN];			// read stuff here

	while ( numargs < MAXARGS )
	{
		printf("arg[%d]? ", numargs);
		if ( fgets(argbuf, ARGLEN, stdin) && * argbuf != '\n' )	// first char not equals to '\0'
			arglist[numargs++] = makestring(argbuf);
		else
			if ( numargs > 0 )				// any args?
			{
				arglist[numargs] = NULL;	// close list
				execute( arglist );			// do it
				numargs = 0;				// and reset
			}
	}

	return 0;
}

int execute( char *arglist[] )
{
	execvp(arglist[0], arglist);
	perror("execvp failed");
	exit(1);
}

char *makestring( char *buf )
{
	char	*cp;

	buf[strlen(buf) - 1] = '\0';		// trim newline
	cp = malloc( strlen(buf) + 1 );		// get memory
	if ( cp == NULL )					// or die
	{
		fprintf(stderr, "no memory\n");
		exit(1);
	}

	strcpy(cp, buf);	// copy chars
	return cp;			// return char ptr
}
