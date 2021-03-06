/*************************************************************************
	> File Name: server.c
	> Author: Comst
	> Mail:750145240@qq.com 
	> Created Time: Thu 03 Jul 2014 10:02:48 AM CST
 ************************************************************************/
#include "my_socket.h"
#include <pthread.h>
void* thread_handle(void* arg);
int main(int argc , char* argv[])//exe ip port
{
	signal(13,SIG_IGN);
	if(argc != 3)
	{
		printf("usge : exe ip port");
		exit(-1);
	}
	int fd_server ,fd_client;
	struct sockaddr_in client_addr ;
	int addrlen = sizeof(client_addr);
	fd_server = listenfd_init(argv[1],argv[2]);
	while(fd_client = accept(fd_server,(struct sockaddr*)&client_addr,&addrlen))
	{
		printf("a client connect :%s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		pthread_t tid ;
		pthread_create(&tid,NULL,thread_handle,(void*)fd_client);
	
	}

}
void* thread_handle(void* arg)
{
	int fd_client = (int)arg ;
	pthread_detach(pthread_self());
	handle_request(fd_client);
}
