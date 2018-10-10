/*	play_again1.c
 *		purpose	: ask if user wants another transaction
 *		method	: set tty into char-by-char mode, read char, return result
 *		returns	: 0 => yes, 1 => no
 *		better	: do no echo inappropriate input
 */

#include	<stdio.h>
#include	<termios.h>

#define	QUESTION	"Do you want another transaction"
int get_response( char * );
void set_crmode(void);
void tty_mode(int);

int main(void)
{
	int response;

	tty_mode(0);
	set_crmode();
	response = get_response(QUESTION);
	tty_mode(1);
	return response;
}

int get_response(char *question)
/*
 *	purpose	: ask a question and wait for a y/n answer
 *	method	: use getchar and ignore non y/n answers
 *	returns	: 0 => yes, 1 => no
 */
{
	int input;
	printf("%s (y/n)?", question);
	while(1)
		switch( input = getchar() )
		{
			case 'y':
			case 'Y':
				return 0;
			case 'n':
			case 'N':
			case EOF:
				return 1;
			default:
				printf("\ncannot understand %c, ", input);
				printf("Please type y or n\n");
		}
}

/* how == 0 => save current mode. how == 1 => restore mode */
void tty_mode(int how)
{
	static struct termios original_mode;
	if ( how == 0 )
		tcgetattr(0, &original_mode);
	else
		tcsetattr(0, TCSANOW, &original_mode);
}

void set_crmode(void)
/*
 *	purpose	: put file descriptor 0 (i.e. stdin) into char-by-char mode
 *	method	: use bits in termios
 */	
{
	struct termios ttystate;
	tcgetattr( 0, &ttystate );
	ttystate.c_lflag	&= ~ICANON;
	ttystate.c_cc[VMIN]	= 1;
	tcsetattr( 0, TCSANOW, &ttystate);
}
