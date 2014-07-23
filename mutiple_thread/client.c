/*************************************************************************
	> File Name: client.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月03日 星期四 10时37分13秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include"msg.h"
int main(int argc,char *argv[])
{
	MSG msg,rev_msg;
	if(argc!=4)
	{
		printf("usage:server_ip and port");
		exit(-1);
	}
	int fd_client,fd_file;
	struct sockaddr_in server_addr;
	if((fd_client=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket");
		exit(-1);
	}
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);
	int temp=connect(fd_client,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(temp==-1)
	{
		printf("conect error!");
		close(fd_client);
		exit(-1);
	}
	//客户端发送数据
	memset(&msg,0,sizeof(msg));
	printf("input:");
	scanf("%s",msg.s_buf);
	msg.s_len=strlen(msg.s_buf);//文件名的长度
	//将文件名封装成一个message发送给服务器
	//循环接受
	fd_file=open(argv[3],O_WRONLY|O_CREAT,0666);//在本地创建一个文件用于存储下载的数据

	//下面是客户端发送给服务器的第一个数据包
	send(fd_client,&msg,msg.s_len+MSG_LEN,0);//msg这个结构体用来传输文件名
	//注意send函数的前三个参数等同于read和write
	//send函数的第三个参数：nbytes：实际要改善的数据的字节数
	//至于第四个参数flags:一般设置为0
	while(1)
	{
		memset(&rev_msg,0,sizeof(MSG));
		recv(fd_client,&rev_msg,MSG_LEN,0);
		if(rev_msg.s_len>0)
		{
			printf("begin....\n");
			recv(fd_client,rev_msg.s_buf,rev_msg.s_len,0);
			write(fd_file,rev_msg.s_buf,rev_msg.s_len);
			printf("end.....\n");
		}
		else
		{
			printf("the rusult=%d\n",rev_msg.s_len);
			break;
		}
	}
	printf("abd\n");
	close(fd_file);
	close(fd_client);
}

