/*************************************************************************
	> File Name: getsockaopt.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月03日 星期四 09时21分42秒
 ************************************************************************/

#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
int main()
{
	int sockfd;
	int revc_size,snd_size;
	int len_recv,snd_recv;
	int my_recv_buf,my_snd_buf;
	getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&recv_size,&len_recv);
	setsockopt(sock_fd,SOL_SOCKET,SO_RCVBUF,&MY_RCV,SIZEOF(INT));//设置缓冲区大小
}
