//基于tcp协议通信模型的服务器
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
	int yes = 1;
	//1.创建socket,使用socket函数
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == sockfd)
	{
		perror("socket"),exit(-1);
	}
	printf("创建socket成功\n");
	if( setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes ) == -1 ){
		perror( "setsockopt");
		exit(-1);
	}
	
	//2.准备通信地址，使用结构体类型
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	//addr.sin_addr.s_addr = inet_addr("172.30.11.191");
	addr.sin_addr.s_addr = htonl( INADDR_ANY );

	//3.绑定socket和通信地址，使用bind函数
	int res = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
	if(-1 == res)
	{
		perror("bind"),exit(-1);
	}
	printf("绑定成功\n");
	//4.监听,使用listen函数
	res = listen(sockfd,100);
	if(-1 == res)
	{
		perror("listen"),exit(-1);
	}
	printf("监听成功\n");
	//5.响应客户端的连接请求,使用accept函数
	struct sockaddr_in rcv_addr;
	socklen_t len = sizeof(rcv_addr);
	int fd = accept(sockfd,(struct sockaddr*)&rcv_addr,&len);
	if(-1 == fd)
	{
		perror("accept"),exit(-1);
	}
	//6.进行通信,使用read/write函数
	char buf[100] = {0};
	res = read(fd,buf,sizeof(buf));
	if(-1 == res)
	{
		perror("read"),exit(-1);
	}
	printf("客户端发来的消息是：%s,消息大小是：%d\n",buf,res);
	res = write(fd,"I received!",12);
	if(-1 == res)
	{
		perror("write"),exit(-1);
	}
	printf("发送给客户端数据大小是:%d\n",res);
	//7.关闭socket,使用close函数
	close(fd);
	close(sockfd);
	//练习：vi 01tcpB.c文件，编写客户端的代码
	return 0;
}






