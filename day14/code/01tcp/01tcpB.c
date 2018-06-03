//基于TCP协议通信的客户端
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
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
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

	//3.连接socket和通信地址,使用connect函数
	int res = connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
	if(-1 == res)
	{
		perror("connect"),exit(-1);
	}
	printf("连接服务器成功\n");
	//4.进行通信,使用read/write函数
	res = write(sockfd,"hello",6);
	if(-1 == res)
	{
		perror("write"),exit(-1);
	}
	printf("发送给服务器的数据大小是：%d\n",res);
	char buf[100] = {0};
	res = read(sockfd,buf,sizeof(buf));
	if(-1 == res)
	{
		perror("read"),exit(-1);
	}
	printf("服务器发来的消息是：%s,消息大小是：%d\n",buf,res);
	//5.关闭socket,使用close函数
	close(sockfd);
	return 0;
}





