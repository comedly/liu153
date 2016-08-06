/**************************************************************************
	>file name:dup.c
	>author:Comedly
	>create time:2016-8-6
**************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	int fd = open("./log",O_CREAT |O_RDWR,0644);
	if(fd < 0)
	{
		perror("open()");
		return fd;
	}

	close(1);//关闭想要重定向的fd
//	int new_fd = dup(fd);//重定向标准输出到打开文件
//	if(new_fd == -1)
//	{
//		perror("dup()");
//		return -1;
//	}
//	close(fd);

	int ret = dup2(fd,1);

	char buf[1024];
	while(1)
	{
		memset(buf,'\0',sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
		if(strncmp("quit",buf,4) == 0)
		{
			break;
		}
		printf("%s\n",buf);//直接打印到标准输出，即可写入文件
		fflush(stdout);
	}
	//close(new_fd);
	close(fd);
}
