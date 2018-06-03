//线程的创建
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* task(void* p)
{
	while(1)
	{
		printf("我是新线程\n");
	}
}

int main(void)
{
	//typedef unsigned long int pthread_t;
	pthread_t tid;
	//创建一个新的线程
	pthread_create(&tid,NULL,task,NULL);
	usleep(100000);
	printf("tid = %lu\n",tid);
	return 0;
}



