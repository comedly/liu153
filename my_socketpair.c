#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>

int main()
{
	int fd[2];
	int ret = socketpair(PF_LOCAL,SOCK_STREAM,0,fd);
	if(ret != 0)
	{
		perror("socketpair()");
		return ret;
	}

	pid_t id = fork();
	if(id < 0)
	{
		perror("fork()");
		return id;
	}
	else if(id == 0)
	{
		//child
		close(fd[0]);
		char buf[512];
		while(1)
		{
			memset(buf,0,sizeof(buf));
			strcpy(buf,"i am child");
			write(fd[1],buf,sizeof(buf));
			read(fd[1],buf,sizeof(buf));
			sleep(1);
			printf("%s\n",buf);
		}
	}
	else if(id >0)
	{
		//father
		close(fd[1]);
		char buf[512];
		while(1)
		{
			memset(buf,0,sizeof(buf));
			read(fd[0],buf,sizeof(buf));
			printf("%s\n",buf);
			strcpy(buf,"i am father");
			write(fd[0],buf,sizeof(buf));
		}
	}
	else
	{ }
	return 0;
}
