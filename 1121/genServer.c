#include <stdlib.h>

const int port = 23123;

void main(int ac, char* av[])
{
	int sock, fd;
	sock = make_server_socket(port);
	if ( sock == -1 )
		exit(1);

	while(1) 
	{
		fd = accept(sock, NULL, NULL);
		if ( fd == -1 )
			break;
		process_request(fd);
		close(fd);
	}
}

void process_request(int fd)
{
	/*
	time_t now;
	char *cp;
	time(&now);
	cp = ctime(&now);
	write(fd, cp, strlen(cp));
*/
	int pid = fork();

	switch(pid) {
		case -1:
			return;
		case 0:
			dup2(fd, 1);
			close(fd);
			execl("/bin/date", "date", NULL);
			perror("execlp");
		default:
			wait(NULL);
	}
	
}
