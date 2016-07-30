#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
//单生产者单消费者模型

typedef struct my_list
{
	int data;
    struct my_list* next;
}product_list;

product_list *head = NULL;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t need_product = PTHREAD_COND_INITIALIZER;

void InitList(product_list *list)
{
	if(NULL != head)
	{
		list->next = NULL;
		list->data = 0;
	}
}

void* consumer(void *_val)
{
	product_list *p = NULL;
	while(1)
	{
		pthread_mutex_lock(&lock);
		while(head == NULL)
		{
			pthread_cond_wait(&need_product,&lock);
		}
		p = head;
		head = head->next;
		p->next = NULL;
		pthread_mutex_unlock(&lock);
		printf("consum success,val is :%d\n",p->data);
		p = NULL;
	}
	return NULL;
}

void* product(void *_val)
{
	while(1)
	{
		sleep(1);
		product_list *p = malloc(sizeof(product_list));
		pthread_mutex_lock(&lock);
		InitList(p);
		p->data = rand()%1000;
		p->next = head;
		head = p;
		pthread_mutex_unlock(&lock);
		printf("call consumer!product succsee,val is:%d\n",p->data);
		pthread_cond_signal(&need_product);
	}
}

int main()
{
	pthread_t t_product;
	pthread_t t_consumer;
	pthread_create(&t_product,NULL,product,NULL);
	pthread_create(&t_consumer,NULL,consumer,NULL);

	pthread_join(t_product,NULL);
	pthread_join(t_consumer,NULL);
	return 0;
}


//product_list* alloc_Node(int x)
//{
//	product_list* newNode = (product_list*)malloc(sizeof(product_list));
//	newNode->data = x;
//	newNode->next = NULL;
//	return newNode;
//}
//
//int isempty()
//{
//	return (_head->next != NULL)?1:0;
//}
//
//void PushFront(product_list* head,int d)
//{
//	product_list* newNode = alloc_Node(d);
//	if(head->next == NULL)
//	{
//		head->next = newNode;
//		newNode->next = NULL;
//	}
//	else
//	{
//		newNode->next = head->next;
//		head->next = newNode;
//	}
//}
//
//void PopFront(product_list* head)
//{
//	if(head->next == NULL)
//	{
//		return;
//	}
//	else
//	{
//		product_list* del = head->next;
//		head->next = head->next->next;
//		free(del);
//	}
//}
//
//void print()
//{
//	if(isempty() == 1)
//	{
//		product_list* list = _head;
//		while(list)
//		{
//			printf("%d ",list->data);
//			list = list->next;
//		}
//		printf("\n");
//	}
//
//}

//int main()
//{
//	product_list* list;
//	InitList(&list);
//	int i =0;
//	for(;i < 10;i++)
//	{
//		PushFront(list,i);
//		print(list);
//	}
//
//
//	return 0;
//}
