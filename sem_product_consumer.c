/*信号量实现生产者-消费者问题*/
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

void sys_error(int ret, char *str)
{
	if(ret != 0)
	{
		fprintf(stderr, "%s:%s\n", str, strerror(ret));
		pthread_exit(NULL);
	}

}

#define NUM 5

int queue[NUM];
sem_t blank_number, product_number;

void *producer(void *arg)
{
	int i = 0;

	while(1)
	{
		sem_wait(&blank_number);
		queue[i] = rand() % 1000 + 1;
		printf("------Produce-------%d\n", queue[i]);
		sem_post(&product_number);

		i = (i + 1) % NUM;

		sleep(rand() % 1);
	}
}

void *consumer(void *arg)
{
	int i = 0;

	while(1)
	{
		sem_wait(&product_number);
		printf("---Consume---%d\n", queue[i]);
		queue[i] = 0;
		sem_post(&blank_number);

		i = (i+1) % NUM;
		sleep(rand() % 2);
	}
}

int main(void)
{
	pthread_t pid, cid;
	int ret;
	
	sem_init(&blank_number, 0, NUM);	
	sem_init(&product_number, 0, 0);
	
	if((ret = pthread_create(&pid, NULL, producer, NULL)) != 0)
		sys_error(ret, "producer create error");
	if((ret = pthread_create(&cid, NULL, consumer, NULL)) != 0)
		sys_error(ret, "consumer create error");

	pthread_join(pid, NULL);
	pthread_join(cid, NULL);

	sem_destroy(&blank_number);
	sem_destroy(&product_number);
	

	return 0;
}
