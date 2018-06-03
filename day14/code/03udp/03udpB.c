//实现基于UDP协议模型的客户端
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main( int argc, char *argv[] )
{
	if( argc != 2 ){
		printf( "stderr\r\n" );
	}
	//1.创建socket,使用socket函数
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(-1 == sockfd)
	{
		perror("socket"),exit(-1);
	}
	printf("创建socket成功\n");

	//2.准备通信地址，使用服务器的地址
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	//addr.sin_addr.s_addr = inet_addr("172.30.11.191");
	addr.sin_addr.s_addr = inet_addr( argv[1] );

	//3.进行通信，发送数据到服务器
	//int res = write(sockfd,"hello",6);
	int res = sendto(sockfd,"hello",6,0,(struct sockaddr*)&addr,sizeof(addr));
	if(-1 == res)
	{
		perror("sendto"),exit(-1);
	}
	printf("发送到服务器的数据大小是：%d\n",res);

	//接受服务器发来的数据
	char buf[100] = {0};
	res = recv(sockfd,buf,sizeof(buf),0);
	if(-1 == res)
	{
		perror("recv"),exit(-1);
	}
	printf("服务器发来的数据是：%s,数据大小是：%d\n",buf,res);
	//4.关闭socket,使用close函数
	close(sockfd);
	return 0;
}







