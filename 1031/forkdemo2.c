/* forkdemo2.c - shows how child processes pick up at the return
 *				from fork() and can execute any code thy like.
 * 				even fork(). Predict number of lines of output.
 */

#include	<stdio.h>
#include	<unistd.h>

void main()
{
	static int count = 0;
	printf("my pid is %d\n", getpid() ); count++;
	fork();
	fork();
	fork();
	printf("my pid is %d\n", getpid() ); count++;
	printf("count is %d\n", count);
}
