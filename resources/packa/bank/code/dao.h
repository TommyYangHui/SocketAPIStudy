//进行文件操作函数的声明
#ifndef DAO_H
#define DAO_H
#include "bank.h"

//生成帐号的函数
int generator_id(void);
//保存帐户信息的函数
int createUser(struct Account acc);

#endif
