#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void sys_err(char *str, int exitno)
{
	perror(str);
	exit(exitno);
}

int main(int argc, char *argv[])
{
	int fd;
	char buf[1024];

	if(argc < 2) 
	{
		printf("./a.out fifoname\n");
		exit(1);
	}

	//fd = open(argv[1], O_RDONLY);
	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		sys_err("open", 1);
	}
	
	int len = read(fd, buf, sizeof(buf));
	write(STDOUT_FILENO, buf, len);
	close(fd);
	return 0;
}
