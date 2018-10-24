#include <curses.h>
#define LEFTEDGE	10
#define RIGHTEDGE	30
#define	ROW			10

void main()
{
	char	message[]	= "Hello";
	char	blank[]		= "     ";
	int		dir			= +1;
	int		pos			= LEFTEDGE;
	int i;

	initscr();
	clear();

	while(1)
	{
		move(ROW, pos);
		addstr(message);				// draw string
		move(LINES - 1, COLS - 1);		// park the cursor
		refresh();						// show string
		usleep(100000);
		move(ROW, pos);	
		addstr(blank);					// erase string
		pos += dir;
		if (pos >= RIGHTEDGE)			// advance position
			dir = -1;					// check for bounce
		if (pos <= LEFTEDGE)
			dir = +1;
	}
}
