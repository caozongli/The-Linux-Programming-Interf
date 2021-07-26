#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("abc", O_CREAT, 0777);
	printf("%d\n", getuid()); 	//获取实际用户ID
	printf("%d\n", geteuid());	//获取有效用户ID

	close(fd);
	return 0;
}	
