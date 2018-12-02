#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define NUM 10

int counter = 0;
void *print_count(void *);
void main()
{
	pthread_t t1;
	int i;

	pthread_create(&t1, NULL, print_count, NULL);
	for(i = 0; i < NUM; i++) {
		counter++;
		sleep(1);
	}

	pthread_join(t1, NULL);
	return 0;
}

void *print_count(void *m) {
	int i;
	for(i = 0;i < NUM; i++) {
		printf("count = %d\n", counter);
		sleep(2);
	}
	return NULL;
}
