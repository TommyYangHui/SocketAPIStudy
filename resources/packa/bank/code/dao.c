//实现我们想要的功能
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "dao.h"

//保存帐号的文件
const char* ID_FILE = "id.dat";

//生成帐号的函数实现
int generator_id(void)
{
	//初始帐号
   	int idUser = 100000;
	//检查文件是否存在
	if(-1 == access(ID_FILE,F_OK))
	{
		//文件不存在，创建文件
		int fd = open(ID_FILE,O_CREAT|O_EXCL|O_WRONLY,0666);
       	if(-1 == fd)
		{
			perror("文件创建失败");
			exit(-1);
		}
		printf("文件创建成功\n");
       	//保存帐号
		if(-1 == write(fd,&idUser,sizeof(idUser)))
		{
			perror("写入文件失败");
			exit(-1);
		}
		//关闭文件
		close(fd);
		//返回当前帐号
		return idUser;
	}
	//处理除第一个用户之外其他用户的开户
	int fd = open(ID_FILE,O_RDWR,0666);
	if(-1 == fd)
	{
		perror("打开文件失败");
		exit(-1);
	}
   	printf("成功打开文件\n");
   	//读出文件中的帐号
	read(fd,&idUser,sizeof(idUser));
   	//对帐号加一
	idUser++;
	//将读写位置移动到文件的开头
   	lseek(fd,0,SEEK_SET);
	//把新帐号写入文件
   	write(fd,&idUser,sizeof(idUser));
	//关闭文件
	close(fd);
	//返回当前帐号
	return idUser;
}

//保存帐户信息的函数实现
int createUser(Account acc)
{
	char filename[20] = {0};
	//把帐号按照%d的格式写入filename
	sprintf(filename,"%d.dat",acc.id);
	//创建名为filename的文件
    int fd = open(filename,O_CREAT|O_EXCL|O_WRONLY,0666);
	if(-1 == fd)
	{
		perror("创建文件失败");
		//exit(-1);
		return -1;
	}
	printf("成功创建文件\n");
	//将帐户信息写入文件
    if(-1 == write(fd,&acc,sizeof(acc)))
	{
		perror("写入文件失败");
		return -1;
	}
	//关闭文件
	close(fd);
	return 0;
}
