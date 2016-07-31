#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

void create_daemon(void)
{
	int i;
	int fd0;
	pid_t pid;
	struct sigaction sa;

	umask(0);//设置文件掩码为0

	if((pid = fork()) < 0){
	}else if(pid != 0){
		exit(0);//终止父进程
	}

	setsid();//设置新会话

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if(sigaction(SIGCHLD,&sa,NULL) < 0){//注册子进程退出忽略信号
		return ;
	}

	if((pid = fork()) < 0){//再次fork，终止进程，保持子进程不是话首进程，从而保证后续不会再和其他终端关联
		printf("fork error !\n");
		return ;
	}else if(pid != 0){
	exit(0);
	}

	if(chdir("/")<0){//更改工作目录到根
		printf("child dir error\n");
		return ;
	}
	close(0);
	fd0 = open("/dev/null",O_RDWR);//关闭标准输入，重定向所有标准（输入输出错误）到/dev/null
	dup2(fd0,1);
	dup2(fd0,2);
}

int main()
{
	create_daemon();
	while(1)
	{
		sleep(1);
	}
	return 0;
}
