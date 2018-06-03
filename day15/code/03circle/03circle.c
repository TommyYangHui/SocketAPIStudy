//根据圆形半径计算圆形的周长和面积
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define PI 3.14
void* task(void* p)
{
	int r = *(int*)p;
	printf("圆形的周长是：%lf,面积是：%lf\n",2*PI*r,PI*r*r);
}

int main(void)
{
	int* pi = (int*)malloc(sizeof(int));
	printf("请输入圆形的半径：\n");
	scanf("%d",pi);
	//启动子线程进行计算
	pthread_t tid;
	pthread_create(&tid,NULL,task,(void*)pi);
	//sleep(1);
	//usleep(100000);
	//等待线程tid终止，不接受退出状态信息
	pthread_join(tid,NULL);
	//释放动态内存
	free(pi);
	pi = NULL;
	return 0;
}



