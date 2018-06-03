//实现基于TCP一对多模型的服务器
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//定义全局变量，保存socket描述符
int sockfd;

void fa(int signo)
{
	printf("正在关闭服务器，请稍后...\n");
	sleep(2);
	close(sockfd);
	printf("关闭服务器成功\n");
	exit(0);//终止进程
}

int main(void)
{
	//1.创建socket,使用socket函数
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == sockfd)
	{
		perror("socket"),exit(-1);
	}
	printf("创建socket成功\n");
	//2.准备通信地址，使用结构体类型
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	//addr.sin_addr.s_addr = inet_addr("172.30.11.191");
	addr.sin_addr.s_addr = htonl( INADDR_ANY );

	//解决重新启动程序时地址被占用的问题
	int reuseaddr = 1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuseaddr,sizeof(reuseaddr));
	
	//3.绑定socket和通信地址,使用bind函数
	int res = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
	if(-1 == res)
	{
		perror("bind"),exit(-1);
	}
	printf("绑定成功\n");
	//4.监听，使用listen函数
	res = listen(sockfd,100);
	if(-1 == res)
	{
		perror("listen"),exit(-1);
	}
	printf("监听成功\n");
	//8.采用信号2来关闭服务器
	printf("关闭服务器，请按ctrl+c...\n");
	signal(SIGINT,fa);
	//5.不断地响应客户端的连接请求,accept函数
	while(1)
	{
		struct sockaddr_in recv_addr;
		socklen_t len = sizeof(recv_addr);
		int fd = accept(sockfd,(struct sockaddr*)&recv_addr,&len);
		if(-1 == fd)
		{
			perror("accept"),exit(-1);
		}
		char* ip = inet_ntoa(recv_addr.sin_addr);
		printf("客户端%s连接成功...\n",ip);

		//6.针对每一个连接上来的客户端，创建子进程处理，使用fork函数
		pid_t pid = fork();
		if(-1 == pid)
		{
			perror("fork"),exit(-1);
		}
		//子进程
		if(0 == pid)
		{
			//7.针对每一个客户端进行不断通信,使用read/write函数
			while(1)
			{
				char buf[100] = {0};
				res = read(fd,buf,sizeof(buf));
				if(-1 == res)
				{
					perror("read"),exit(-1);
				}
				//printf("客户端%s发来的消息是：%s,消息大小是：%d\n",ip,buf,res);
				printf("客户端%s发来的消息是：%s\n",ip,buf);
				//判断客户端是否下线
				if(!strcmp(buf,"bye"))
				{
					printf("客户端%s已下线...\n",ip);
					break;
					//close(fd);
					//exit(0);
				}
				res = write(fd,"I received!",12);
				if(-1 == res)
				{
					perror("write"),exit(-1);
				}
			}
            close(fd);//关闭描述符
			exit(0);//结束子进程
		}
	}
	//练习：vi 02tcpB.c文件,每次发送的数据由用户输入
	return 0;
}




