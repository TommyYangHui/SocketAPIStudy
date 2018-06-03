//实现基于TCP一对多模型的客户端
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	//2.准备通信地址，服务器端的地址
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
	//4.不断地和服务器进行通信,使用read/write
	while(1)
	{
		char buf[100] = {0};
		printf("请输入要发送的数据内容：\n");
		//scanf("%s",buf);
		scanf( "%[^\n]", buf );  //以换行符作为字符串输入的结束
		//一次性发送100个字节,无论数据是否有效
		//res = write(sockfd,buf,sizeof(buf));
		//使用strlen发送时，只会发送有效字符
		//不包括 '\0'
		res = write(sockfd,buf,strlen(buf));
		if(-1 == res)
		{
			perror("write"),exit(-1);
		}
		//判断客户端是否下线
		if(!strcmp(buf,"bye"))
		{
			break;//跳出无限循环
		}
		char buf2[100] = {0};
		res = read(sockfd,buf2,sizeof(buf2));
		if(-1 == res)
		{
			perror("read"),exit(-1);
		}
		printf("服务器发来的消息是：%s,消息大小是：%d\n",buf2,res);
	}
	//5.关闭socket,使用close函数
	close(sockfd);
	return 0;
}





