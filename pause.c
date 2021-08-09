#include <stdio.h>
#include <signal.h>


void do_sig(int n)
{}

int mysleep(int n)
{
	signal(SIGALRM, do_sig);
	//1.阻塞SIGARM
	alarm(n); // 1秒
	//2.解出阻塞SIGALRM

	pause;
}

int main(void)
{
	struct sigaction act;

	act.sa_handler = do_sig;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	
	sigaction(SIGUSR1, &act, NULL);

	pause();
	printf("after pause\n");

	return 0;
}
