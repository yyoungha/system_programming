/* who2.c	- read /var/adm/utmp and list info therein
			- suppresses empty records
			- formats time nicely
   */
#include	<stdio.h>
#include	<unistd.h>
#include	<utmp.h>
#include	<fcntl.h>
#include	<time.h>
#include	<stdlib.h>

void showtime(long);
void show_info(struct utmp * );

int main()
{
	struct utmp		utbuf;	/* read info into here */
	int				utmpfd;	/* read from this descriptor */

	if ( ( utmpfd = open(UTMP_FILE, O_RDONLY) ) == -1 )
	{
		perror(UTMP_FILE);
		exit(1);
	}

	while ( read ( utmpfd, &utbuf, sizeof(utbuf) ) == sizeof(utbuf) )
		show_info( &utbuf );

	close(utmpfd);
	return 0;
}

/* show_info()	- displays the contents of the utmp struct
				- in human readable form
				- displays nothing if record has no user name
   */

void show_info( struct utmp *utbufp )
{
	if (utbufp->ut_type != USER_PROCESS )
		return;

	printf("%-8.8s", utbufp->ut_name);	/* the log name */
	printf(" ");
	printf("%-8.8s", utbufp->ut_line);	/* the tty */
	printf(" ");
	showtime( utbufp->ut_time );		/* display time */

#ifndef SHOWHOST
	if( utbufp->ut_host[0] != '\0' )
		printf(" (%s)", utbufp->ut_host);
#endif
	printf("\n");
}

/* showtime()	- displays time in a format fit for human consumption
				- uses ctime to build a string then picks parts out of it
				* NOTE : %12.12s prints a string 12 chars wide and LIMITS it to 12 chars.
   */
void showtime( long timeval )
{
	char *cp;
	cp = ctime(&timeval);
	printf("%12.12s", cp+4);
}
