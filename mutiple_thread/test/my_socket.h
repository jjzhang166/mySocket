/*************************************************************************
	> File Name: my_socket.h
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月03日 星期四 16时18分49秒
 ************************************************************************/
#ifndef __MY_SOCKET_H__
#define __MY_SOCKET_H__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<signal.h>
int listenfd_init(char *ip,char* port);
void handle_request(int fd_client);
#endif




