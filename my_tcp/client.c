/***************************************************************************
	>file name:client.c
	>author:Comedly
	>create time:2016-8-5
***************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<signal.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>

void usage(const char* proc)
{
	printf("%s [ip] [port]\n",proc);
}

int main(int argc,char* argv[])
{
	if(argc != 3){
		usage(argv[0]);
		return 3;
	}

	int comn = socket(AF_INET,SOCK_STREAM,0);
	if(comn < 0)
	{
		perror("socket");
		return 1;
	}

	struct sockaddr_in remote;
	remote.sin_family = AF_INET;
	remote.sin_port = htons(atoi(argv[2]));
	remote.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(comn,(struct sockaddr*)&remote,sizeof(remote))<0){
		perror("connect");
		return 2;
	}

	char buf[1024];
	while(1)
	{
		ssize_t _s = read(0,buf,sizeof(buf)-1);
		if(_s > 0){
			buf[_s] = '\0';
			write(comn,buf,strlen(buf));

			read(comn,buf,sizeof(buf)-1);
			printf("server echo:%s\n",buf);
		}
	}
	return 0;
}
