#include<iostream>
#include<semaphore.h>
#include<vector>
#include<string>

class sem
{
	public:
		sem(int _val = 2)
		{
			sem_init(&_sem,0,_val);
		}

		~sem()
		{
			sem_destroy(&_sem);
		}

		void sem_p()
		{
			sem_wait(&_sem);
		}

		void sem_v()
		{
			sem_post(&_sem);
		}

	private:
		sem_t _sem;
};

const int size = 10;
std::vector<std::string>  vec_pool(size);

sem sem_product(size);
sem sem_consumer(0);

void* consumer(void *arg)
{
	pthread_detach(pthread_self());

	std::string box;
	int i = 0;
	while(1)
	{
		sem_consumer.sem_p();
		//consumer begin
		box = vec_pool[i];
		sem_product.sem_v();
		i = (i+1) % size;
		std::cout<<"consumer done,val is :"<<box<<std::endl;
		sleep(1);
	}
}

void* product(void *arg)
{
	pthread_detach(pthread_self());
	int i = 0;
	while(1)
	{
		std::string pro = "hello world";
		sem_product.sem_p();
		//product begin

		vec_pool[i] = pro;
		sem_consumer.sem_v();
		i = (i + 1) % size;
		std::cout<<"product is done,val is :"<<pro<<std::endl;
	}
}

int main()
{
	pthread_t id1,id2;
	pthread_create(&id1,NULL,product,NULL);
	pthread_create(&id2,NULL,consumer,NULL);

	sleep(100);
	return 0;
}
