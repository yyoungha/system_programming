#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#define NUM 100

void *print_msg(void *);

void main()
{
	pthread_t t1, t2;

	pthread_create(&t1, NULL, print_msg, (void *) "hello");
	pthread_create(&t2, NULL, print_msg, (void *) "world\n");
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}

void *print_msg(void *m)
{
	int i;
	for ( i = 0; i < NUM; i++ )
	{
		printf("%s", m);
		fflush(stdout);
		sleep(1);
	}
}
