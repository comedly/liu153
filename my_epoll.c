/**************************************************************************
	>file name:my_epoll.c
	>author:Comedly
	>create time:2016-8-9
**************************************************************************/

#include<stdio.h>
#include<sys/epoll.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>

//static void my_read(int epfd,int fd,char *buf,int len)
//{
//	int rs = 1;
//	while(rs)
//	{
//		ssize_t size = recv(fd,buf,len,0);
//		if(size < 0)
//		{
//			if(errno = EAGAIN)
//			{
//				break;
//			}
//			else
//			{
//				perror("recv");
//				return 9;
//			}
//		}
//		else if(size == 0)
//		{
//			//表示对端的sock已经正常关闭
//			printf("client close....\n");
//			struct epoll_event ev;
//			epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
//			close(fd);
//			break;
//		}
//		else
//		{
//			buf[size - 1] = '\0';
//			printf("client # %s\n",buf);
//			if(size == len)
//			{
//				rs = 1;
//			}
//			else
//			{
//				rs = 0;
//			}
//		}
//	}
//}

//static void my_write(int fd,char *buf,int len)
//{
//	int ws = 1;
//	while(ws)
//	{
//		ssize_t size = send(fd,buf,len,0);
//		if(size < 0)
//		{
//			//缓冲区已满，延时重试
//			if(errno == EAGAIN)
//			{
//				usleep(1000);
//				continue;
//			}
//			if(errno == EINTR)
//			{
//				return -1;
//			}
//		}
//		if(size == len)
//		{
//			continue;
//		}
//		len -= size;
//		buf += size;
//	}
//}

ssize_t my_read(int fd,char buf[])
{
	int ret = 0;
	int total = 0;
	while((ret = read(fd,buf+total,sizeof(buf)-total)) && errno != EAGAIN)
	{
		total +=ret;
	}
	buf[total] = '\0';
	return total;
}

static void set_no_block(int fd)
{
	//先得到之前的状态，在之前的状态上加入新状态，将其设置为非阻塞。
	int before = fcntl(fd,F_GETFL);
	fcntl(fd,F_SETFL,before|O_NONBLOCK);
}

static int startup(const char *ip,int port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0 )
	{
		perror("socket");
		return 2;
	}

	int opt = 1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);

	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind");
		return 3;
	}
	if(listen(sock,5) < 0)
	{
		perror("listen");
		return 4;
	}
	return sock;
}

static void usage(const char* proc)
{
	printf("%s [ip][port]\n",proc);
}

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}
	int listen_sock = startup(argv[1],atoi(argv[2]));
	int epfd = epoll_create(128);
	if(epfd < 0)
	{
		perror("epoll_create");
		return 5;
	}
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = listen_sock;
	if(epoll_ctl(epfd,EPOLL_CTL_ADD,listen_sock,&ev) < 0)
	{
		perror("epoll_ctl");
		return 6;
	}
	struct epoll_event evs[128];
	int len = sizeof(evs)/sizeof(evs[0]);
	int ready = 0;
	int timeout = -1;
	while(1)
	{
		switch(ready = epoll_wait(epfd,evs,len,timeout))
		{
			case 0:
				printf("timeout..\n");
				break;
			case -1:
				printf("epoll_wait");
				break;
			default:
				{
					int i = 0;
					for(;i < ready;i++)
					{
						int fd = evs[i].data.fd;
						if(i == 0 && fd == listen_sock && evs[i].events&EPOLLIN)
						{
							struct sockaddr_in peer;
							socklen_t len = sizeof(peer);
							int new_sock = accept(listen_sock,(struct sockaddr*)&peer,&len);
							if(new_sock < 0)
							{
								perror("accept");
								return 8;
							}
							else
							{
								//在epoll_wait之后改变其文件状态，为非阻塞，ET工作
								set_no_block(new_sock);
								printf("get new client:ip %s:port %d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
								ev.events = EPOLLIN|EPOLLET;
								ev.data.fd=new_sock;
								if(epoll_ctl(epfd,EPOLL_CTL_ADD,new_sock,&ev)<0)
								{
									perror("epoll_ctl");
									return 9;
								}
							}
						}
						else
						{
							//read
							if(evs[i].events&EPOLLIN)
							{
								char buf[1024];
								ssize_t _s = my_read(fd,buf);
								//ssize_t _s = recv(fd,buf,sizeof(buf)-1,0);
								if(_s > 0)
								{
									buf[_s] = '\0';
									printf("client # %s\n",buf);

									ev.data.fd = fd;
									ev.events = EPOLLOUT |EPOLLET;
									epoll_ctl(epfd,EPOLL_CTL_MOD,fd,&ev);
								}
								else if(_s == 0)
								{
									//client close
									printf("client close...\n");
									epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
									close(fd);
								}
								else
								{
									perror("my_read");
									return 10;
								}
							}
							else if(evs[i].events&EPOLLOUT)
							{
								char *msg = "HTTP/1.1 200 ok\r\n\r\n<html><h1>hello Comedly</h1></html>\r\n";
								//send(fd,msg,sizeof(msg)-1);
								//send(fd,msg,strlen(msg),0);
								write(fd,msg,strlen(msg));
								epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
								close(fd);
							}
							else
							{
								continue;
							}
						}
					}
				}
				break;
		}
	}
	return 0;
}
