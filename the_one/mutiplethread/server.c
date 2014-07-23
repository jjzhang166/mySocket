/*************************************************************************
	> File Name: server.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月03日 星期四 15时32分05秒
 ************************************************************************/

#include<stdio.h>
#include"socket.h"
int main(int argc,char* argv[])
{
	signal(13,SIG_IGN);//将某个信号给屏蔽掉
	return 0;
}
