#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define _SEM_PRO_ 10
#define _SEM_CON_ 0

sem_t sem_product;
sem_t sem_consume;

int blank[_SEM_PRO_];

void* consumer(void *_val)
{
	int c = 0;
	while(1)
	{
		sem_wait(&sem_consume);
		int data = blank[c];
		printf("consume done....val is: %d\n",data);
		sem_post(&sem_product);
		c = (c+1)%_SEM_PRO_;
		sleep(rand()%2);
	}
}

void* product(void *_val)
{
	int p = 0;
	while(1)
	{
		sem_wait(&sem_product);
		int data = rand()%1000;
		blank[p] = data;
		printf("product done ... val is ：%d\n",data);
		sem_post(&sem_consume);
		p = (p+1)%_SEM_PRO_;
		sleep(rand()%2);
	}
}

void run_product_consume()
{
	pthread_t tid_consumer;
	pthread_t tid_producter;

	pthread_create(&tid_consumer,NULL,consumer,NULL);
	pthread_create(&tid_producter,NULL,product,NULL);

	pthread_join(tid_consumer,NULL);
	pthread_join(tid_producter,NULL);
}

void destroy_all_sem(int val)
{
	printf("process done......\n");
	sem_destroy(&sem_consume);
	sem_destroy(&sem_product);
	exit(0);
}
void init_all_sem()
{
	signal(2,destroy_all_sem);
	int blank[_SEM_PRO_];
	int _num = sizeof(blank)/sizeof(blank[0]);
	int i = 0;
	for(;i < _num;i++)
	{
		blank[i] = 0;
	}
	sem_init(&sem_product,0,_SEM_PRO_);
	sem_init(&sem_consume,0,_SEM_CON_);
}
int main()
{
	init_all_sem();
	run_product_consume();
	destroy_all_sem(0);
	return 0;
}
