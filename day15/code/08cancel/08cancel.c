//线程的取消
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* task(void* p)
{
	//默认允许被取消，并且是延迟取消
	//设置该线程不允许被取消
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
	//pthread_setcancelstate(PTHREAD_CANCEL_ENABLE ,NULL);
	//pthread_setcanceltype( PTHREAD_CANCEL_ASYNCHRONOUS, NULL );
	while(1)
	{
		printf("I am SuperMan!\n");
		usleep(100000);
	}
}

void* task2(void* p)
{
	printf("开始取消线程\n");
	usleep(300000);
	//给线程一发送取消的请求
	// pthread_t* pt = p;
	// *pt;
	pthread_cancel(*(pthread_t*)p);
	printf("取消线程完毕\n");
}

int main(void)
{
	//1.启动一个线程，进行打印
	pthread_t tid;
	pthread_create(&tid,NULL,task,NULL);
	//2.启动一个线程，负责发送取消的请求
	pthread_t tid2;
	pthread_create(&tid2,NULL,task2,&tid);

	//3.主线程进入等待
	pthread_join(tid,NULL);
	pthread_join(tid2,NULL);
	return 0;
}



