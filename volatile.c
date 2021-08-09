#include <stdio.h>

void do_sig(int n)
{
	n = 0;
}

volatile int n = 5;
int main(void)
{
	while(n)
	{
		printf("hello");
	}
	return 0;
}
