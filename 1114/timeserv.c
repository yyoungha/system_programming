/* timeserv.c - a socket-based time of day server
   */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <time.h> 
#include <string.h>

#define		PORTNUM	23000
#define		HOSTLEN	256
#define		oops(msg)	{ perror(msg); exit(1); }

int main(int ac, char *av[])
{
	struct	sockaddr_in	saddr;	// build our address here
	struct	hostent		*hp;	// this is part of our address
	char	hostname[HOSTLEN];
	int		sock_id, sock_fd;	// line id, file descriptor
	FILE	*sock_fp;			// use socket as stream
	char	*ctime();			// convert secs to string
	time_t	thetime;			// the time we report

	// Step 1. ask kernel for a socket
	sock_id = socket( PF_INET, SOCK_STREAM, 0 );
	if ( sock_id == -1 )
		oops("socket");

	// Step 2. erase the data bzero(startpoint, numofbytes) and bind address to socket.
	bzero( (void *)&saddr, sizeof(saddr) );

	gethostname( hostname, HOSTLEN );
	hp = gethostbyname( hostname );

	bcopy( (void *)hp->h_addr, (void *)&saddr.sin_addr, hp->h_length);
	saddr.sin_port = htons(PORTNUM);
	saddr.sin_family = AF_INET;

	// Step 3. allow incoming calls with Qsize=1 on socket
	if ( listen(sock_id, 1) != 0 )
		oops("listen");

	// main loop
	while (1) {
		sock_fd = accept(sock_id, NULL, NULL);
		printf("Wow! got a call!\n");
		if ( sock_fd == -1 )
			oops("accept");

		sock_fp = fdopen(sock_fd, "w");
		if ( sock_fp == NULL )
			oops("fdopen");

		thetime = time(NULL);

		fprintf( sock_fp, "The time here is ..." );
		fprintf( sock_fp, "%s", ctime(&thetime) );
		fclose( sock_fp );
	}
}
