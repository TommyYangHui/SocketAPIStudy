//接受消息，并进行相应的处理
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include "bank.h"
#include "dao.h"

int main(void)
{
	//获取消息队列
	int msgid1 = msgget(key1,0);
	if(-1 == msgid1)
	{
		perror("获取消息队列一失败");
		exit(-1);
	}
	printf("成功获取消息队列一的消息\n");
	int msgid2 = msgget(key2,0);
	if(-1 == msgid2)
	{
		perror("获取消息队列二失败");
		exit(-1);
	}
	printf("成功获取消息队列二的消息\n");
	//接受消息
   	while(1)
	{
    	Msg msg;
		//接受消息失败，重新接受
	    if(msgrcv(msgid1,&msg,sizeof(msg.acc),M_OPEN,0) <= 0)
		{
			 continue;
		}
      	//实现开户的功能
		if(msg.mtype == M_OPEN)
		{
			//自动生成帐号
			int idTemp = generator_id();
			//将生成的帐号赋值给接受过来的帐户
			msg.acc.id = idTemp;
			//保存帐户信息
          	if(-1 == createUser(msg.acc))
			{
				printf("创建帐户失败\n");
				msg.mtype = M_FAILED;
			}					
			else
			{
				printf("创建帐户成功\n");
				msg.mtype = M_SUCESS;
			}
          	//给客户端发送消息
			msgsnd(msgid2,&msg,sizeof(msg.acc),0);
		}
   	}
	return 0;
}
