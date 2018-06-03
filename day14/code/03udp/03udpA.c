//实现基于UDP通信模型的服务器
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

	//解决重新启动程序时地址被占用的问题
	int reuseaddr = 1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuseaddr,sizeof(reuseaddr));

	//2.准备通信地址，使用结构体类型
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	//addr.sin_addr.s_addr = inet_addr("172.30.11.191");
	addr.sin_addr.s_addr = htonl( INADDR_ANY );

	//3.绑定socket和通信地址,使用bind函数
	int res = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
	if(-1 == res)
	{
		perror("bind"),exit(-1);
	}
	printf("绑定成功\n");
	//4.进行通信，使用函数读取客户端信息
	char buf[100] = {0};
	//res = read(sockfd,buf,sizeof(buf));
	//准备结构体变量
	struct sockaddr_in recv_addr;
	socklen_t len = sizeof(recv_addr);
	res = recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&recv_addr,&len);
	if(-1 == res)
	{
		perror("recvfrom"),exit(-1);
	}
	printf("客户端发来的消息内容是：%s,消息大小是：%d\n",buf,res);
	//向客户端回发消息
	res = sendto(sockfd,"I received!",12,0,(struct sockaddr*)&recv_addr,len);
	if(-1 == res)
	{
		perror("sendto"),exit(-1);
	}
	printf("发送给客户端的数据大小是：%d\n",res);

	//5.关闭socket,使用close函数
	close(sockfd);
	return 0;
}




