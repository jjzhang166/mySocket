/*************************************************************************
	> File Name: my_socket.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月03日 星期四 16时33分51秒
 ************************************************************************/
#include"my_socket.h"
#include"msg.h"
int listenfd_init(char *ip,char *port)
{
	int fd_server;
	int temp;
	struct sockaddr_in server_addr;
	int reuse=1;
	fd_server=socket(AF_INET,SOCK_STREAM,0);
	if(fd_server==-1)
	{
		perror("socket");
		exit(-1);
	}
	//设置setsockopt
	temp=setsockopt(fd_server,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
	if(temp!=0)
	{
		perror("setsockopt");
		close(fd_server);
		exit(-1);
	}
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(port));
	server_addr.sin_addr.s_addr=inet_addr(ip);
	//bangding
	temp=bind(fd_server,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(temp==-1)
	{
		perror("bind error");
		close(fd_server);
		exit(-1);
	}
	temp=listen(fd_server,5);
	if(temp==-1)
	{
		perror("listen");
		close(fd_server);
		exit(-1);
	}
	return fd_server;
}
void handle_request(int fd_client)
{
	int fd_file;
	int read_n;
	MSG msg,snd_msg;
	memset(&msg,0,sizeof(msg));
	/*经过测试可得，如果将recv(fd_client,&msg,MSG_LEN,0)注释掉的话，无法
	 * 从服务下下载东西
	 * */
	//为什么刚开始要收到一个长度
	//
	//recv(fd_client,&msg,MSG_LEN,0);//测试一下这个语句是否对后续的接收数据造成影响
	//
	recv(fd_client,msg.s_buf,msg.s_len,0);
	printf("recv msg:%s\n",msg.s_buf);
	fd_file=open(msg.s_buf,O_RDONLY);
	//测试一下是否因为字节接收顺序不对造成的文件无法打开
	if(fd_file==-1)
	{
		printf("cannot find the file!\n");
	}

	//在服务器的运行程序的当前目录下打开客户端请求的文件
	while(memset(&snd_msg,0,sizeof(snd_msg)),(read_n=read(fd_file,snd_msg.s_buf,MSG_SIZE))>0)
	{
		snd_msg.s_len=read_n;
		send(fd_client,&snd_msg,snd_msg.s_len+MSG_LEN,0);
	}
	//最后发送的一个包长度为0
	snd_msg.s_len=0;
	send(fd_client,&snd_msg,snd_msg.s_len+MSG_LEN,0);
	close(fd_file);
	close(fd_client);
}

