//使用pthread_create函数启动新线程
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* task(void* task)
{
	int i = 0;
	for(i = 0; i < 100; i++)
	{
		printf("子线程中：i = %d\n",i);
	}
}

int main(void)
{
	pthread_t tid;
	//创建线程
	pthread_create(&tid,NULL,task,NULL);
	int i = 0;
	for(i = 0; i < 100; i++)
	{
		printf("主线程中：i = %d\n",i);
	}
	//当前系统中：pthread_t=>unsigned long int
	printf("tid = %lu\n",tid);//子线程
	printf("主线程的ID = %lu\n",pthread_self());
	return 0;
}



