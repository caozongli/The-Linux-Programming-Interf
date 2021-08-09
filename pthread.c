#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *th_fun(void *arg)
{
	int *p = (int*) arg;
	printf("pthread ID = %x\n", (unsigned int)pthread_self());
	printf("PID = %d\n", getpid());
	printf("*arg = %d\n", *p);
	sleep(1);
}


int main(void)
{
	pthread_t tid;
	int n = 10;

	pthread_create(&tid, NULL, th_fun, (void*)&n);//1.创建线程 2.线程号填写到tid 3.返回函数调用
	// 主线程里面的pthread_create返回值tid == 子线程里面的pthread_self()？
	printf("main thread ID = %x\n", (unsigned int)pthread_self());
	printf("main child pthread ID = %x\n", (unsigned int)tid);
	printf("PID = %d\n", getpid());
	sleep(2);
	return 0;
}
