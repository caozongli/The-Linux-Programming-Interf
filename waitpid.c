#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sys_err(char *str)
{
	perror(str);
	exit(1);
}

void do_sig_child(int signo)
{
	/*
	while(!(waitpid(0, NULL, WNOHANG) == -1));
	*/
	int status;
	pid_t pid;
	while((pid = waitpid(0, &status, WNOHANG)) > 0)
	{
		if(WIFEXITED(status))
			printf("child %d exit %d\n", pid, WEXITSTATUS(status));
		else if(WIFSIGNALED(status))
			printf("child %d cancel signal %d \n", pid ,WTERMSIG(status));

	}
}

int main(void)
{
	pid_t pid;
	int i;
	//阻塞SIGCHLD
	for(i=0; i<10; i++)
	{
		if((pid = fork()) == 0)
			break;
		else if(pid < 0)
			sys_err("fork");
	}

	if(pid == 0)
	{
		int n = 8;
		while(n--)
		{
			printf("chid ID %d\n", getpid());
			sleep(1);
		}
	}
	else if(pid > 0)
	{
		// 先设置捕捉
		// 再解除对SIGCHLD的阻塞

		struct sigaction act;
		act.sa_handler = do_sig_child;
		act.sa_flags = 0;
		sigaction(SIGCHLD, &act, NULL);

		while(1)
		{
			printf("parrent ID %d\n", getpid());
			sleep(1);
		}
	}

	return 0;
}
