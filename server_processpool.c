/*************************************************************************
	> File Name: server_processpool.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月03日 星期四 19时26分33秒
 ************************************************************************/

#include<stdio.h>
#include"my_socket.h"
int main(int argc,char* argv[])
{
	char buf[1024];
	//传递4个参数  exe  ip   port  child_cnt
	if(argc!=4)
	{
		printf("input the string!\n");
	}
	int fd_server;
	pCHLD my_chlds=(pCHLD)calloc(atoi(argv[3]),sizeof(CHLD));
	//写个创建儿子的函数
	make_chld(my_chlds,atoi(argv[3]));
	fd_set read_set,ready_set;


	fd_server=lisenfd_init(argv[1],argv[2]);//初始化
	FD_ZERO(&read_set);
	FD_SET(fd_server,&read_set);
	for(index=0;index<atoi(argv[3]);index++)
	{
		FD_SET(my_chlds[index].s_read,&read_set);
	}
	struct timeval tm;
	while(1)
	{
		tm.tv_usec=1000;
		tm.tv_sec=0;
		ready_set=read_set;
		select(1024,&ready_set,NULL,NULL,&tm);
		//如果有活动请求，
		//如果是客户端发的，则从fd_server中读连接
		if(FD_ISSET(fd_server,&ready_set))
		{
			int fd_client=accept(fd_server,NULL,NULL);//accept可以得到一些信息[对方的结构体中放在这另个null中里]
			//描述符对应一个socket
			//找一个空闲的儿子，让任务非配给儿子,
			//find_child_handle();具体如何找到
			for(index=0;index<atoi(argv[3]);index++)
			{
				if(my_chlds[index].s_status==S_IDLE)
					break;
			}
			//找到my_chlds[index];write
			//write(fds2[0],buf,1024)
			write(my_chlds[index].s_write,buf,1024);
			my_chlds[index].s_status=BUSY;
			
			
		}
		for(index=0;index<atoi(argv[3]);index++)
		{
			//查看儿子是否有发请求
			if(FD_ISSET(my_chlds[index].s_read,&ready_set))
			{
				//read_from_fd();//能否理解为处理完后需要做的工作嘛
				my_chlds[index].s_status=S_IDLE;
			}
		}
	}

}
