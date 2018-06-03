//线程共享所在进程中的内存资源
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 

void* task(void* p)
{
	// void* p = &num;
	// int* pi = p = &num;
	// *pi = *(&num) = num;
	int* pi = p;
	*pi = 200;
}

int main(void)
{
	int num = 118;//局部变量,栈区
	//启动一个新线程，负责修改num变量的值
	pthread_t tid;
	pthread_create(&tid,NULL,task,(void*)&num);
	//主线程等待子线程结束后，打印num的值
	sleep(1);
	printf("子线程修改之后:num = %d\n",num);
	return 0;
}






