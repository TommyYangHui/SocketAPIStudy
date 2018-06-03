//使用pthread_exit函数实现线程的终止
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* task(void* p)
{
	//static int i = 0;
	int i = 0;
	for(i = 1; i < 100; i++)
	{
		if(10 == i)
		{
			//终止当前线程
			//pthread_exit((void*)&i);
			//return (void*)&i;
			//exit(0);//终止当前进程
			pthread_exit((void*)i);
		}
		printf("子线程中 i = %d\n",i);
	}
}

int main(void)
{
	//1.启动一个新线程，打印
	pthread_t tid;
	pthread_create(&tid,NULL,task,NULL);
	//2.主线程等待子线程，并且获取退出状态
	//int* pi = NULL;
	//pthread_join(tid,(void**)&pi);
	//printf("*pi = %d\n",*pi); //10
	
	int num = 0;
	pthread_join(tid,(void**)&num);
	printf("主线程中：num = %d\n",num);
	return 0;
}



