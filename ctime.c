#include <stdio.h>
#include <time.h>

int main(void)
{
	char buf[1024];
	time_t t;

	time(&t);				//距离1970.1.1 00:00:00的秒数
	ctime_r(&t, buf);		//把秒数转化成当前时间
	printf("%s\n", buf);

	return 0;
}
