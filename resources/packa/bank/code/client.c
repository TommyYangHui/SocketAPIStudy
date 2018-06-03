//客户端的实现
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include "bank.h"

//定义消息队列ID
static int msgid1;
static int msgid2;

//获取消息队列
void getId(void)
{
	//获取消息队列一
	msgid1 = msgget(key1,0);
	if(-1 == msgid1)
	{
		perror("获取消息队列一失败");
		exit(-1);
	}
	printf("成功获取消息队列一\n");
	//消息队列二
	msgid2 = msgget(key2,0);
	if(-1 == msgid2)
	{
		perror("获取消息队列二失败");
		exit(-1);
	}
	printf("成功获取消息队列二\n");
}

//开户
void createUser(void)
{
	Account acc;
	printf("请输入用户名：\n");
	scanf("%s",acc.username);
	printf("请输入密码：\n");
	scanf("%s",acc.password);
	printf("请输入要存入的金额\n");
	scanf("%lf",&acc.balance);
	Msg msg = {M_OPEN,acc};
   	getId();
   	if(-1 == msgsnd(msgid1,&msg,sizeof(msg.acc),0))
	{
    	perror("发送到消息队列一的消息发送失败");
		exit(-1);
	}
   	printf("成功发送消息到消息队列一\n");	
   	//接受服务器端的消息
	msgrcv(msgid2,&msg,sizeof(msg),0,0);
	if(msg.mtype == M_SUCESS)
	{
		printf("恭喜您开户成功,您的帐号为：%d,账户名称为：%s,账户密码为：%s,账户余额为：%lf\n",msg.acc.id,msg.acc.username,msg.acc.password,msg.acc.balance);
	}
	else
	{
		printf("开户失败\n");
	} 
}

//绘制界面
void mainPage(void)
{
	 while(1)
	 {
	    printf("     欢迎使用迷你ATM机\n");
	    printf("--------------------------\n");
	    printf(" [1] 开户");
	    printf("    [2] 销户\n");
	    printf(" [3] 存钱");
	    printf("    [4] 取钱\n");
	    printf(" [5] 查询");
	    printf("    [6] 转帐\n");
	    printf(" [0] 退出\n");
	    printf("------------------------\n");
	    printf("请选择：\n");
	    int choose = 0;
	    scanf("%d",&choose);
	    switch(choose)
	    {
			case 1://printf("正在开户\n");
				createUser();break;
			case 2:printf("正在销户\n");
				break;
			case 3:printf("正在存钱\n");
				break;
			case 4:printf("正在取钱\n");
				break;
			case 5:printf("正在查询\n");
				break;
			case 6:printf("正在转帐\n");
				break;
			case 0:printf("谢谢使用，下次再见\n");
				return;
			default:printf("输入错误\n");
	   	}
		printf("\n\n");
	}
}

int main(void)
{
	 mainPage();
	 return 0;
}
