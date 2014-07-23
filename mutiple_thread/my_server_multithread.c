/*************************************************************************
	> File Name: my_server_multithread.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月03日 星期四 18时59分27秒
 ************************************************************************/

#include"my_socket.h"
#include<pthread.h>
void* thread_handle(void* arg);
int main(int argc,char* argv[])
{
	signal(13,SIG_IGN);
	if(argc!=3)
	{
		printf("add ip and port");
		exit(-1);
	}
	int fd_server,fd_client;
	struct sockaddr_in client_addr;
	int addrlen=sizeof(client_addr);

	fd_server=listenfd_init(argv[1],argv[2]);
	
	while(fd_client=accept(fd_server,(struct sockaddr*)&client_addr,&addrlen))
	{
		printf("a client connect:%s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		pthread_t tid;
		pthread_create(&tid,NULL,thread_handle,(void*)fd_client);
	}
}
void* thread_handle(void* arg)
{
	int fd_client=(int)arg;
	pthread_detach(pthread_self());
	handle_request(fd_client);
}

