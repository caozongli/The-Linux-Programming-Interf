#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 0X800000000 

int print_ntimes(char *str)
{
	sleep(1);
	int m = 1;
	while(m--)
		printf("%s", str);
	return 0;
}

void *th_fun(void *arg)
{
	int n = 3;
	while(n--)
		print_ntimes("hello xwp\n");
}


int main(void)
{
	pthread_t tid;
	int err, detachstate;
	pthread_attr_t attr;
	size_t stacksize;
	void *stackaddr;

	pthread_attr_init(&attr);

	pthread_attr_getstack(&attr, &stackaddr, &stacksize);
	printf("stackadd = %p\n", stackaddr);
	printf("stacksize = %x\n", (int)stacksize);

	pthread_attr_getdetachstate(&attr, &detachstate);
	if(detachstate == PTHREAD_CREATE_DETACHED)
		printf("thread detached\n");
	else if(detachstate == PTHREAD_CREATE_JOINABLE)
		printf("thread join\n");
	else
		printf("thread un known");
	//设置线程分离属性
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	int  i=1;
	while(1)
	{
		//申请内存，指定线程栈的起始地址和大小
		stackaddr = malloc(SIZE);
		if(stackaddr == NULL)
		{
			perror("malloc");
			exit(1);
		}
		stacksize = SIZE;
		pthread_attr_setstack(&attr, stackaddr, stacksize);

		err = pthread_create(&tid, &attr, th_fun, NULL);
		if(err != 0)
		{
			printf("%s\n", strerror(err));
			exit(1);
		}
		printf("%d\n", i++);
	}

	pthread_attr_destroy(&attr);
	
	return 0;
}


