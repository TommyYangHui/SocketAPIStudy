//基于socket的网络通信
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
	//1.创建socket,使用socket函数
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(-1 == sockfd)
	{
		perror("socket"),exit(-1);
	}
	printf("创建socket成功\n");
	//2.准备通信地址，使用结构体类型
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);//端口号
	//addr.sin_addr.s_addr = inet_addr("172.30.11.191");
	//addr.sin_addr.s_addr = inet_addr("192.168.0.122");
	addr.sin_addr.s_addr = htonl( INADDR_ANY );

	//3.绑定socket和通信地址，使用bind函数
	int res = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
	if(-1 == res)
	{
		perror("bind"),exit(-1);
	}
	printf("绑定成功\n");
	//printf( "ip=%s\r\n", ntohl( addr.sin_addr.s_addr) );
	//TODO:Why the ip is what the ifconfig get:
	printf( "ip=%s\r\n", addr.sin_addr.s_addr );
	//4.进行通信，使用read/write函数
	char buf[100] = {0};
	res = read(sockfd,buf,sizeof(buf));
	if(-1 == res)
	{
		perror("read"),exit(-1);
	}
	printf("读取客户端发来的消息内容是：%s,消息大小是：%d\n",buf,res);
	//5.关闭socket,使用close函数
	close(sockfd);
	return 0;
}




