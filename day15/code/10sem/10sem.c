//线程的同步问题
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

//准备共享资源
char* buf[5]; //字符指针数组
int pos; //记录数组的下标
//1.定义互斥量
//pthread_mutex_t mutex;
//1.定义信号量
sem_t sem;

void* task(void* p)
{
	//3.进行加锁
	//pthread_mutex_lock(&mutex);
	//3.获取信号量
	sem_wait(&sem);

	buf[pos] = p;
	sleep(1);
	pos++;

	//4.进行解锁
	//pthread_mutex_unlock(&mutex);
	//4.释放信号量
	sem_post(&sem);
}

int main(void)
{
	//2.初始化互斥量
	//pthread_mutex_init(&mutex,NULL);
	//2.初始化信号量
	sem_init(&sem,0,1);

	//1.启动一个线程，负责向数组存放数据
	pthread_t tid;
	pthread_create(&tid,NULL,task,"zhangfei");
	//再启动一个线程，负责向数组存储数据
	pthread_t tid2;
	pthread_create(&tid2,NULL,task,"guanyu");
	//2.主线程等待
	pthread_join(tid,NULL);
	pthread_join(tid2,NULL);
	
	//5.销毁互斥量
	//pthread_mutex_destroy(&mutex);
	//5.销毁信号量
	sem_destroy(&sem);

	//3.打印字符指针数组中的内容
	printf("字符指针数组中的内容是：");
	int i = 0;
	for(i = 0; i < pos; i++)
	{
		printf("%s ",buf[i]);
	}
	printf("\n");
	return 0;
}



