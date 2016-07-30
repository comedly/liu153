#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define NLOOP 5000

static int g_count = 0;
pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;
void* read_write_mem(void *_val) 
{
	int val = 0;
	int i = 0;
	for(;i < NLOOP;i++)
	{
		pthread_mutex_lock(&mutex_lock);
		val = g_count;
		printf("pthread id is:%x,count is :%d\n",(unsigned long)pthread_self(),g_count);
		g_count = val + 1;
		pthread_mutex_unlock(&mutex_lock);
	}
	return NULL;
}

int main()
{
	pthread_t pt1,pt2;
	pthread_create(&pt1,NULL,read_write_mem,NULL);
	pthread_create(&pt2,NULL,read_write_mem,NULL);
	pthread_join(pt1,NULL);
	pthread_join(pt2,NULL);
	printf("count final val is:%d\n",g_count);
	return 0;
}
