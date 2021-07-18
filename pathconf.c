#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("%ld\n", fpathconf(STDOUT_FILENO, _PC_NAME_MAX));
	return 0;
}

