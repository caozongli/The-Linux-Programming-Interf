#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pid, pid_c;
	//调用1次返回2次，在父进程返回子进程的PID，在子进程返回0
	pid = fork();

	if(pid > 0)
	{
		while(1)
		{
			printf("I am parent %d\n", getpid());
			pid_c = wait(NULL);
			printf("wait for child %d \n", pid_c);
			sleep(1);
		}
	}
	else if(pid == 0)
	{
		printf("I am child %d\n", getpid());
		sleep(3);
	}
	else
	{
		perror("create failure\n");
		exit(-1);
	}
	return 0;
}
