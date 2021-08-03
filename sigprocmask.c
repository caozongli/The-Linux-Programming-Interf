#include <signal.h>
#include <stdio.h>

void printsighset(const sigset_t *set)
{
	int i;
	for(i = 0; i < 32; i++)
	{
		if(sigismember(set, i) == 1)
			putchar('1');
		else
			putchar('0');
	}
	puts("");
}

int main(void)
{
	sigset_t s, p;
	sigemptyset(&s);
	sigaddset(&s, SIGINT);
	sigprocmask(SIG_BLOCK, &s, NULL);
	int n = 0;
	while(1)
	{
		n += 1;
		sigpending(&p);
		printsighset(&p);
		sleep(1);
		if(n == 10)
		{
			sigdelset(&s, SIGQUIT);
			sigprocmask(SIG_UNBLOCK, &s, NULL);
		}
	}
	return 0;
}
