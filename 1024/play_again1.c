/*
 * play_again1.c
 * purpose: ask if user wants another transaction
 * method: set tty into char-by-char mode, read char,
           return results
   returns: 0=>yes, 1=>no
   better: do no echo inappropriate input
*/
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>

#define QUESTION        "Do you want another transaction" 

int     get_response(char *q){
/*
 purpose: ask a question and wait for a y/n answer
 method: use getchar and complain about non y/n answera
 returns:0=>yes, 1=>no
*/
	int input;
        printf("%s (y/n)?", q);
        while(1) {
                switch(getchar()) {
                        case 'y':
                        case 'Y': return 0;
                        case 'n':
                        case 'N':
                        case EOF: return 1;
                        default:
				printf("\ncannot understand: %c, ", input);
				printf("Please type y or no\n");
                }
        }
}

int     set_crmode(){
/*
 * purpose: put file descriptor 0 (i.e. stdin) into char-by-char mode
 * method: use bits in termios
 */
        struct termios  ttystate;
        tcgetattr(0, &ttystate); /* read curr. setting */
        ttystate.c_lflag &= ~ICANON;/* no buffering */
        ttystate.c_cc[VMIN] = 1;/* get 1 char at a time */
        tcsetattr(0, TCSANOW, &ttystate);/* install settings */
}

int     tty_mode(int how){
/*
 * how == 0->save current mode, 1-> restore mode 
 */
        static struct termios   original_mode;
        if(how == 0) {
                return tcgetattr(0, &original_mode);
	}
        else{
        	return tcsetattr(0, TCSANOW, &original_mode);
	}
}

int     main()
{
        int     response;
        tty_mode(0); /* save tty mode */
        set_crmode();/* set char-by-char mode */
        response = get_response(QUESTION);/* get some answer */
        tty_mode(1); /* restore tty mode */
        return response;
}



