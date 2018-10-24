/*
 * play_again4.c
 * purpose: ask if user wants another transaction
 * method:  set tty into char-by-char mode, no-echo mode
			set tty into no-delay mode
			read char, return result
			reset terminal modes on SIGINT, ignores SIGQUIT
   returns: 0=>yes, 1=>no, 2=> timeout
   better: reset terminal mode on Interrupt
*/

#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#define ASK			"Do you want another transaction"
#define TRIES		3				// max tries
#define SLEEPTIME	2				// time per try
#define BEEP		putchar('\a')	// alert user


int 		get_ok_char()
{
	int c;
	while ( ( c = getchar() ) != EOF && strchr("yYnN", c) == NULL)
		return c;
}

int     get_response(char *q, int maxtries){
/*
 purpose: ask a question and wait for a y/n answer or maxtries
 method: use getchar and complain about non y/n input
 returns:0=>yes, 1=>no, 2=> timeout
*/
	int input;

    printf("%s (y/n)?", q);						// ask
	fflush(stdout);								// force output
    while(1) 
	{
		sleep(SLEEPTIME);						// wait a little bit
		input = tolower(get_ok_char());			// get next char

		if ( input == 'y' || input == 'Y' )
			return 0;
		if ( input == 'n' || input == 'N' )
			return 1;
		if ( maxtries-- == 0 )					// out of time?
			return 2;
		BEEP;
    }
}

void set_cr_noecho_mode(void)
{
	struct termios ttystate;

	tcgetattr(0, &ttystate);
	ttystate.c_lflag	&= ~ICANON;
	ttystate.c_lflag	&= ~ECHO;
	ttystate.c_cc[VMIN]	=	1;
	tcsetattr(0, TCSANOW, &ttystate);
}

int			set_nodelay_mode()
/*
 * purpose: put file descripter 0 into no-delay mode
 * method:	use fcntl to set bits
 * notes:	tcsetattr() will do something similar, but it is complicated
 */
{
	int termflags;
	termflags = fcntl(0, F_GETFL);
	termflags |= O_NDELAY;
	fcntl(0, F_SETFL, termflags);
}

void ctrl_c_handler(int signum)
{
	tty_mode(1);
	exit(1);
}

int     tty_mode(int how){
/*
 * how == 0->save current mode, 1-> restore mode
 */
        static struct termios   original_mode;
		static int				original_flags;
		static int				stored = 0;
	if(how == 0) {
		tcgetattr(0, &original_mode);
		original_flags = fcntl(0, F_GETFL);
		stored = 1;
	} else if (stored) {
		tcsetattr(0, TCSANOW, &original_mode);
		fcntl(0, F_SETFL, original_flags);
	}
}

int     main()
{
        int     response;
		void	ctrl_c_handler(int);

        tty_mode(0); /* save tty mode */
		set_cr_noecho_mode();
		set_nodelay_mode();
		//signal(SIGINT, ctrl_c_handler);	
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
        response = get_response(ASK, TRIES);/* get some answer */
        tty_mode(1); /* restore tty mode */
        return response;
}
