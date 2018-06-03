//基于socket的本地通信
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>

int main(void)
{
	int yes = 1;
	//1.创建socket,使用socket函数
	int sockfd = socket(AF_UNIX,SOCK_DGRAM,0);
	if(-1 == sockfd)
	{
		perror("socket"),exit(-1);
	}
	printf("创建socket成功\n");

	/* in case it already exists */
	unlink( "a.sock" );
	//2.准备通信地址,使用结构体类型
	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path,"a.sock");
	
	if( setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes ) == -1 ){
		perror( "setsockopt");
		exit(-1);
	}
	//3.绑定socket和通信地址,使用bind函数
	int res = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
	if(-1 == res)
	{
		perror("bind"),exit(-1);
	}
	printf("绑定成功\n");
	//4.进行通信,使用read/write函数
	char buf[100] = {0};
	res = read(sockfd,buf,sizeof(buf));
	if(-1 == res)
	{
		perror("read"),exit(-1);
	}
	printf("读取客户端发来的数据内容是：%s,数据大小是：%d\n",buf,res);
	//5.关闭socket,使用close函数
	close(sockfd);
	//练习：vi 02sockB.c文件，编写客户端代码，负责给服务器发送消息"hello"
	return 0;
}



