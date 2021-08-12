#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t mutex;	//定义一把互斥锁, 想象为一个int数, 本质是一个结构体

void *t_fun(void *arg)
{
	srand(time(NULL));
	
	while(1)
	{
		pthread_mutex_lock(&mutex); //加锁, 想象成减1

		printf("hello ");
		sleep(rand() % 2);
		printf("world\n");
		
		pthread_mutex_unlock(&mutex); //解锁, 想象成锁加1

		sleep(rand() % 2);
	}

	return NULL;
}

int main(void)
{
	pthread_t tid;

	srand(time(NULL));
	int ret;
	if((ret = pthread_mutex_init(&mutex, NULL)) != 0) // 初始化互斥锁, 可以认为锁的值为1
	{
		fprintf(stderr, "mutex init error:%s\n", strerror(ret));
		exit(1);
	}

	pthread_create(&tid, NULL, t_fun, NULL);
	while(1)
	{
		pthread_mutex_lock(&mutex); //枷锁

		printf("HELLO ");
		sleep(rand() % 2);
		printf("WORLD\n");

		pthread_mutex_unlock(&mutex); //解锁

		sleep(rand() % 2);

	}

	pthread_join(tid, NULL);

	pthread_mutex_destroy(&mutex); //销毁互斥锁

	return 0;
}
