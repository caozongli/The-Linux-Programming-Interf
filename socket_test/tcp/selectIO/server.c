#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "wrap.h"

#define MAXLINE 80
#define SERV_PORT 8000

int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr, cliaddr;
	char buf[MAXLINE];
	int i, n, sockfd, listenfd, maxfd, maxi, connfd;
	int nready, client[FD_SETSIZE];
	fd_set rset, allset;
	socklen_t cliaddr_len;
	char str[INET_ADDRSTRLEN];

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	Listen(listenfd, 20);

	maxfd = listenfd;
	maxi = -1;

	for( i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;

	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);

	for(; ;)
	{
		rset = allset;
		nready = select(maxfd+1, &rset, NULL, NULL, NULL);
		if(nready < 0)
			perr_exit("select error\n");

		if(FD_ISSET(listenfd, rset))
		{
			cliaddr_len = sizeof(cliaddr);
			connfd = Accept(listenfd, (struct  sockaddr*)&cliaddr, &cliaddr_len);

			printf("received from %s at PORT %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port)));

			for(i = 0; i < FD_SETSIZE; i++)
			{
				if(client[i] < 0)
				{
					client[i] = connfd;
					break;
				}
			}
			if(i == FD_SETSIZE)
			{
				fputs("too many clients\n", stderr);
				exit(1);
			}
			FD_SET(connfd, &allset);
			if(connfd > maxfd)
				maxfd = connfd;
			if(i > maxi) maxi = i;
			if(--nready == 0)
				continue;
		}

		for(i = 0; i <= maxi; i++)
		{
			if((sockfd = client[i]) < 0) continue;
			if(FD_ISSET(sockfd, &rset))
			{
				if((n = Read(sockfd, buf, MAXLINE)) == 0)
				{
					Close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i] = -1;
				}
			}
			else
			{
				int j;
				for( j = 0; j < n; j++)
					buf[i] = toupper(buf[i]);
				Write(sockfd, buf, n);
			}

			if(--nready == 0)
				break;
		}
	}

	return 0;
}
