#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#define MAX_PATH 1024

int main(void)
{
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;

	if((dfd = opendir(".")) == NULL)
	{
		fprintf(stderr, "can't open origin\n");
		return 0;
	}
	
	struct stat stbuf;
	while((dp = readdir(dfd)) != NULL)
	{
		if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) continue;
		if(strlen(dp->d_name) + 2 > sizeof(name))
			fprintf(stderr, "name %s too long\n", dp->d_name);
		else
		{
			if(stat(dp->d_name, &stbuf) == -1)
			{
				fprintf(stderr, "can't access %s\n", dp->d_name);
			}
			printf("=======%8ld=====%s====%d\n======", stbuf.st_size, dp->d_name, stbuf.st_mode);
		}
	}


	return 0;
}
