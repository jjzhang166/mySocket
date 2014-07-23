/*************************************************************************
	> File Name: server.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月03日 星期四 10时03分31秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char* argv[])
{
	int fd_server,fd_client;
	int reuse=1;
	struct sockaddr_in server_addr ,client_addr;
	int addrlen=sizeof(client_addr);

	char file_name[128]="";
	MSG send_msg,msg;
	if((fd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket");
		exit(-1);
	}
	if(0!=setsockopt(fd_server,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int)))
	{
		perror("setscok");
		close(fd_server);
		exit(-1);
	}
	memset(&server_addr,0,sizeof(server_addr));//bzero传递两个参数
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);
	if(-1==bin(fd_server,(struct sockaddr*)&server_addr,sizeof(server_addr)))
	{
		perror("bind");
	}
	if(-1==listen(fd_server,5))
	{
		perror("listen");
		close(fd_server);
		exit(-1);
	}
	while(fd_client=accept(fd_server,(struct sockaddr*)&client_addr,&addrlen))
	{
		printf("a client connect:%s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		//收个文件名
		memset(&msg,0,sizeof(msg));
		recv(fd_client,&msg,MSG_ELN,128,0);
		recv(fd_client,&msg.s_buf,msg.slen,0);
		printf("recv msg:&s\n",msg.buf);
		fd_file=open(msg.buf,O_RDONLY);
		while(memset(&send_msg,0,sizeof(send_msg)),(read_n=read(fd_file,snd_msg.s_buf,MAG_SIZE))>0)
		{
			//封装成message法，是通过长度控制的。。。。
			snd_msg.s_len=read_n;
			send(fd_client,&snd_msg,read_n+MSG_LEN);
		}
		close(fd_file);
		close(fd_client);
	}
}
