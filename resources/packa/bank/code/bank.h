//定义消息结构 帐户的结构
#ifndef BANK_H
#define BANK_H

//定义key
extern const int key1;
extern const int key2;

//消息的类型
#define M_OPEN 1 //开户
#define M_DESTROY 2  //销户
#define M_SAVE 3 //存钱
#define M_TAKE 4 //取钱
#define M_QUERY 5 //查询
#define M_TRANSF 6 //转帐
#define M_SUCESS 7 //处理成功
#define M_FAILED 8 //处理失败

//帐户结构体
typedef struct Account
{
	 int id;//代表帐号
	 char username[20]; //帐户名称
	 char password[6]; //帐户密码
	 double balance; //帐户的余额
}Account;

//消息结构
typedef struct Msg
{
	 long mtype;//代表消息的类型
	 Account acc;//帐户信息
}Msg;

#endif
