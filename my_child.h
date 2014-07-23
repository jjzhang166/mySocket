/*************************************************************************
	> File Name: my_child.h
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月03日 星期四 19时27分22秒
 ************************************************************************/
#ifndef __MY_CHILD_H__
#define __MY_CHILE_H__
#define S_BUSY 1
#define S_IDLE 0
tpyedef struct tat
{
	pid_t s_pid;
	int s_status;
	int s_read;
	int s_write;
	int s_cnt;//儿子处理了多少请求
}CHLD,*pCHLD;
//儿子与儿子通信是通过管道
//读写是相对于父亲的
void make_chld(pCHID arr,int cnt);
#endif

