/*******************************************************************************	>file name:server.c
	>author:Comedly
	>create time:2016-8-5
*******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>

void colect_child(int sig)
{
	while(waitpid(-1,0,WNOHANG)>0){
		printf("colect child done....\n");
	}
}

void* handler_data(void *arg)
{
	int sock = (int)arg;
	printf("create a new thread....new socket:%d\n",sock);
	char buf[1024];
	while(1){
		ssize_t _s = read(sock,buf,sizeof(buf)-1);
		if(_s > 0){//read success
			buf[_s] = '\0';
			printf("client # %s\n",buf);

			write(sock,buf,strlen(buf));
		}else if(_s == 0){//client close
			printf("client is closed\n");
			break;
		}else{
			break;
		}
	}
	close(sock);
	pthread_exit((void*)0);
}

int main()
{
	int listen_sock = socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock < 0){
		perror("socket");
		exit(1);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(8080);
	local.sin_addr.s_addr = htonl(INADDR_ANY);//

	if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local)) < 0){
		perror("bind");
		exit(2);
	}

	if(listen(listen_sock,5) < 0){
		perror("listen");
		exit(3);
	}

	struct sockaddr_in peer;
	socklen_t len = sizeof(peer);

	signal(SIGCHLD,colect_child);

	while(1)
	{
		int new_fd = accept(listen_sock,(struct sockaddr*)&peer,&len);
		if(new_fd > 0){
			pthread_t id;
			pthread_create(&id,NULL,handler_data,(void*)new_fd);
			pthread_detach(id);
		}
	}
	return 0;
}
