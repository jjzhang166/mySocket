/*************************************************************************
	> File Name: msg.h
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月03日 星期四 09时58分26秒
 ************************************************************************/


#ifndef _MSG_H_
#define _MSG_H_
#define MSG_SIZE 8188
#define MSG_LEN 4
typedef struct tag
{
	int s_len;
	char s_buf[MSG_SIZE];
}MSG;
#endif
