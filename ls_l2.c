#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATH 1024

int main(int argc, char **argv)
{
	char name[MAX_PATH];
	
	if(argc == 1) strcpy(name, ".");
	else
		while(--argc > 0)
			strcpy(name, *++argv);
	printf("%ld\n", strlen(name));		

	struct dirent *dp;
	DIR *dfd;

	if((dfd = opendir(name)) == NULL)
	{
		fprintf(stderr, "can't open %s\n", name);
		return -1;
	}
	
	struct stat stbuf;
	int fdUid = open("/etc/passwd", O_RDONLY);
	if(fdUid == -1) 
	{
		perror("can't open /etc/passwd\n");
		exit(-1);
	}
	int fdGid = open("/etc/group", O_RDONLY);
	if(fdGid == -1)
	{
		perror("can't open /etc/group\n");
		exit(-1);		
	}

	while((dp = readdir(dfd)) != NULL)
	{
		if(!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) continue;
		if(strlen(name)+strlen(dp->d_name)+2 > MAX_PATH)
			fprintf(stderr, "name %s %s too long\n", name, dp->d_name);
		else
		{
			if(stat(name, &stbuf) == -1)
			{
				fprintf(stderr, "can't access %s\n", name);
				close(fdUid);
				close(fdGid);
				return -1;
			}
			int uid = stbuf.st_uid;
			int gid = stbuf.st_gid;
			printf("name:%s  uid:%d  gid:%d\n", dp->d_name, uid, gid);
		}
	}
	close(fdUid);
	close(fdGid);


	return 0;
}
