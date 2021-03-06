#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void sys_err(int n, char *str)
{
	perror(str);
	exit(n);
}

void daemonize()
{
	pid_t pid;

	/*
	 * 成为一个新会话的首进程，失去控制终端
	 */
	if((pid = fork()) < 0)
		sys_err(1, "frok");
	if(pid != 0)
		exit(0);

	/*
	 * 创建新的会话
	 */
	setsid();
	/*
	 * 改变当前工作目录到/目录下
	 */
	if(chdir("/") < 0)
		sys_err(1, "chdir");
	
	/*
	 * 设置umask为0
	 */
	umask(0);

	/*
	 * 重定向0,1,2文件描述符到/dev/null，因为已经失去控制端，再操作0,1,2没有意义
	 */
	close(0);
	open("/dev/null", O_RDWR);
	dup2(0, 1);
	dup2(0, 2);

}

int main(void)
{
	daemonize();
	while(1);	/*在此循环中可以实现守护进程的核心工作*/
	return 0;
}
