//使用pthread_join等待线程并且获取返回值
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* task(void* p)
{
	int i = 0;
	// 使用static修饰的局部变量 全局区/数据区
	static int sum = 0;
	for(i = 0; i <= 100; i++)
	{
		sum += i;
	}
	return &sum;
}

int main(void)
{
	//1.启动线程，线程处理函数中计算1~100的和
	pthread_t tid;
	pthread_create(&tid,NULL,task,NULL);
	//2.等待线程结束，并且获取返回值
	int* pi = NULL;
	pthread_join(tid,(void**)&pi);
	printf("线程处理函数的结果是：%d\n",*pi);
	return 0;
}


