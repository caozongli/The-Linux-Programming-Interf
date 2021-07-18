#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int fd = open("abc", O_RDWR | O_CREAT);
	if(fd<0)
	{
		perror("failure open abc");
		exit(-1);
	}

	int ret = lseek(fd, 10*1024*1024-1, SEEK_SET);
	if(ret < 0)
	{
		perror("lseek error");
	}
	write(fd, "a", 1);
	close(fd);

	return 0;
}
