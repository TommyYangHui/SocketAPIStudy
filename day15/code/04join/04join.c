//使用pthread_join函数等待线程并且获取退出码
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* task(void* p)
{
	// pc 指向 只读常量区
	// pc 本身 在栈区
	char* pc = "hello";
	// 返回 "hello"字符串的首地址
	return pc;

	// ps 指向栈区  ps本身在栈区
	//char ps[] = "hello";
	// 返回 栈区空间的地址
	//return ps; 返回该地址没有意义
}

int main(void)
{
	//1.启动一个线程
	pthread_t tid;
	pthread_create(&tid,NULL,task,NULL);
	//2.等待线程结束，并且获取退出信息
	char* pc = NULL;
	pthread_join(tid,(void**)&pc);
	printf("线程处理函数的返回值是：%s\n",pc);
	return 0;
}




