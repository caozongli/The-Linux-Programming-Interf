#include <stdio.h>

int main(void)
{
	int a = 0;
	char *str = "hello";
	while(1);
	*str = 'H';				//段错误， 11：SIGSEGV		非法操作内存
	printf("%d\n", 3/a);	//浮点数例外，8：SIGFPE		CPU错误
	return 0;
}
