#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	int fd = open("abd", O_RDWR);
	if(fd < 0)
	{
		printf("errno = %d\n", errno);
		printf("xwp %s\n", strerror(errno));
//perror("caozong");
	}
	printf("fd=%d\n", fd);
	return 0;
}
