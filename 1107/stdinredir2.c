/* stdinredir2.c
 *		shows two more methods for redirecting standard input
 *		use #define to set one or the other
 */

#include	<unistd.h>
#include	<stdio.h>
#include	<fcntl.h>
#include	<stdlib.h>

const int flag = 1;

void main()
{
	int fd;
	int newfd;
	char line[100];
	
	// ead and print three lines
	// fgets uses stdin (file descripter 0) for input

	fgets(line, 100, stdin); printf("%s", line);
	fgets(line, 100, stdin); printf("%s", line);
	fgets(line, 100, stdin); printf("%s", line);

	// redirect input

	fd = open("/etc/passwd", O_RDONLY);

	if ( flag ) {
		close(0);
		newfd = dup(fd);
		printf("newfd is %d\n", newfd);
	} else {
		newfd = dup2(fd, 0);
	}

	if ( newfd != 0 ) {
		fprintf(stderr, "Could not duplicate fd to 0\n");
		exit(1);
	}

	close(fd);

	// read and print three lines

	fgets(line, 100, stdin); printf("%s", line);
	fgets(line, 100, stdin); printf("%s", line);
	fgets(line, 100, stdin); printf("%s", line);
}
