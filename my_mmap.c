/**************************************************************************
	>file name:my_mmap.c
	>author:Comedly
	>create time:2016-8-6
**************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>

#define _PATH_NAME_ "./map"

int main()
{
	int fd = open(_PATH_NAME_,O_RDONLY);
	if(fd < 0)
	{
		perror("open()");
		return -1;
	}

	int len = lseek(fd,0,SEEK_END);
	char* ptr = mmap(NULL,len,PROT_READ,MAP_SHARED,fd,0);
	if(ptr < 0)
	{
		close(fd);
		printf("mmap error\n");
		return -2;
	}
	close(fd);
	printf("%s\n",ptr);
	return 0;
}
