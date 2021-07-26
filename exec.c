#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("hello\n");
	execl("/bin/ls", "ls", "-l", NULL);
	printf("hello\n");	
	return 0;
}
