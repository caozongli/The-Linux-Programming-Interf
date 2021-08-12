#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int counter;
pthread_rwlock_t rwlock;

void *th_write(void *arg)
{
	int t;
	int i = (int)arg;
	while(1)
	{
		pthread_rwlock_wrlock(&rwlock); //以写模式加锁
		t = counter;
		usleep(1000);
		printf("=========write %d: %lu: counter=%d ++counter=%d\n", i, pthread_self(), t, ++counter);
		pthread_rwlock_unlock(&rwlock);
		usleep(10000);
	}
	return NULL;
}

void *th_read(void *arg)
{
	int i = (int)arg;

	while(1)
	{
		pthread_rwlock_rdlock(&rwlock); //读线程间，读锁共享
		printf("---------------read %d: %lu: %d\n", i, pthread_self(), counter);
		pthread_rwlock_unlock(&rwlock);
		usleep(2000);
	}
	return NULL;
}

int main(void)
{
	int i;
	pthread_t tid[8];
	int res;

	if((res = pthread_rwlock_init(&rwlock, NULL)) != 0)
	{
		fprintf(stderr, "mutex init error:%s\n", strerror(res));
		exit(1);
	}

	for(i = 0; i < 3; i++)
		if(pthread_create(&tid[i], NULL, th_write, (void*)i) < 0)
		{
			perror("create pthread i=%d\n");
			exit(2);
		}

	for(i = 0; i < 3; i++)
		pthread_create(&tid[i+3], NULL, th_read, (void*)i);

	for(i = 0; i < 8; i++)
		pthread_join(tid[i], NULL);

	pthread_rwlock_destroy(&rwlock);

	return 0;
}

