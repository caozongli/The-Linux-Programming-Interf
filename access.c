#include <stdio.h>

int main(void)
{
	if(access("abc", F_OK) < 0)
	{
		perror("avc");
		exit(1);
	}
	return 0;
}
