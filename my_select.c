/**************************************************************************
	>file name:my_select.c
	>author:Comedly
	>create time:2016-8-7
**************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int fds[64];
const int fds_nums = sizeof(fds)/sizeof(fds[0]);

static int startup(const char* ip,int port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket()");
		exit(2);
	}

	int opt = 1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);

	if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
	{
		perror("bind()");
		exit(3);
	}

	if(listen(sock,5) < 0)
	{
		perror("listen()");
		exit(4);
	}
	return sock;
}

static void usage(const char *proc)
{
	printf("%s [ip] [port]\n",proc);
}

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		exit(1);
	}

	int listen_sock = startup(argv[1],atoi(argv[2]));
	fd_set rset;
	int i = 0;
	FD_ZERO(&rset);
	FD_SET(listen_sock,&rset);
	//initial fds
	for(;i < fds_nums;i++)
	{
		fds[i] = -1;
	}
	fds[0] = listen_sock;
	int done = 0;
	while(!done)
	{
		int max_fd = -1;
		for(i = 0;i < fds_nums;i++)
		{
			if(fds[i]>0)
			{
				FD_SET(fds[i],&rset);
				max_fd = max_fd < fds[i]?fds[i]:max_fd;
			}
		}
		switch(select(max_fd+1,&rset,NULL,NULL,NULL))
		{
			case 0:
				printf("time out...\n");
				break;
			case -1:
				perror("select()");
				break;
			default:
				for(i = 0;i < fds_nums;i++)
				{
					if(i==0 && FD_ISSET(listen_sock,&rset))
					{
						//printf("there\n");
						struct sockaddr_in peer;
						socklen_t len = sizeof(peer);
						int newfd = accept(listen_sock,(struct sockaddr*)&peer,&len);
						if(newfd > 0)
						{
							printf("get a new client$ socket->%s:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
						}
						int j = 0;
						for(j;j<fds_nums;j++)
						{
							if(fds[j] == -1)
							{
								fds[j] = newfd;
								break;
							}
						}
						if(j == fds_nums)
						{
							close(newfd);
						}
					}
					else//normal accept_fd
					{
						if(FD_ISSET(fds[i],&rset))
						{
							char buf[1024];
							memset(buf,'\0',sizeof(buf));
							ssize_t _s = read(fds[i],buf,sizeof(buf)-1);
							if(_s > 0)
							{
								buf[_s-1] = '\0';
								printf("client$ %s\n",buf);
							}
							else if(_s == 0)
							{
								printf("%d is read done......\n",fds[i]);
								write(fds[i],"mn",2);
								sleep(10);
								close(fds[i]);
								fds[i] = -1;
							}
							else
							{
								perror("read()");
							}
						}

					}
				}
				break;
		}
	}
	return 0;
}
