//线程的分离
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* task(void* p)
{
	int i = 0;
	for(i = 1; i < 20; i++)
	{
		printf("子线程中：i = %d\n",i);
	}
}

int main(void)
{
	pthread_t tid;
	pthread_create(&tid,NULL,task,NULL);
	//设置线程为分离状态，则无法被等待
	pthread_detach(tid);
	//等待子线程结束，然后打印
	pthread_join(tid,NULL);
	int i = 0;
	for(i = 1; i < 20; i++)
	{
		printf("主线程中：i = %d\n",i);
	}
	return 0;
}
