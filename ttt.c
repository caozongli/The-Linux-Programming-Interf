#include <string.h>

#define MAX_PATH 1024

void dirwalk(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH];
	struct dirent *dp; 	//目录项
	DIR *dfd;	
	if((dfd = opendir(dir)) == NULL)
	{
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}

	while((dp = readdir(dfd)) != NULL)
	{
		if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) continue;		//如果是self和parent跳过
		if(strlen(dir)+strlen(dp->d_name)+2 > sizeof(name))	// +2 /和\0
			fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->d_name);
		else
		{
			sprintf(name, "%s/%s", dir, dp->d_name);
			(*fcn)(name);

		}
	}
	closedir(dfd);
}



void fsize(char *naem)
{
	struct stat stbuf;
	if(stat(name, &stbuf) == -1) 	// 获取属性
	{
		fprintf(stderr, "fsize: can't access %s\n", name);
		return ;
	}
	if(stbuf.st_mode & S_IFMT == S_IFDIR) 	//判断是否为目录
		dirwalk(name, fsize); 	//回调函数：参数为函数指针
	printf("%8ld %s\n", stbuf.st_size, name);
}

int main(int argc, char **argc)
{
	if(argc == 1) /* default: current directory */
		fsize("."); 	//没有传参数，当前目录
	else
		while(--argv > 0)
			fsize(*++agv);
	return 0;
}
