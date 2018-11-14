#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <time.h> 
#include <string.h>

#define		oops(msg)	{ perror(msg); exit(1); }

int main(int ac, char *av[])
{
	struct	sockaddr_in	saddr;
	struct	hostent		*hp;
	int		sock_id, sock_fd;
	char	message[BUFSIZ];
	int		messlen;

	// Step 1. 
	sock_id = socket( AF_INET, SOCK_STREAM, 0 );
	if ( sock_id == -1 )
		oops("socket");

	// Step 2. connect to server
	bzero( (void *)&saddr, sizeof(saddr) );

	hp = gethostbyname( av[1] );
	if ( hp == NULL )
		oops(av[1]);

	bcopy( (void *)hp->h_addr, (struct sockaddr *)&saddr.sin_addr, hp->h_length);
	saddr.sin_port = htons(atoi(av[2]));
	saddr.sin_family = AF_INET;

	if ( connect(sock_id, (struct sockaddr *)&saddr, sizeof(saddr)) != 0 )
		oops("connect");

	// Step 3. transfer data from server, then hangup
	messlen = read(sock_id, message, BUFSIZ);
	if ( messlen == -1 )
		oops("read");
	if ( write ( 1, message, messlen ) != messlen )
		oops("write");
	close( sock_id );
}
