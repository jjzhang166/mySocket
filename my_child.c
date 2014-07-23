/*************************************************************************
	> File Name: my_child.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月03日 星期四 19时38分25秒
 ************************************************************************/

#include<stdio.h>
#include"my_child.h"
void make_chl(pCHLD arr ,int cnt)
{
	int index;
	for(index=0;index<cnt;index++)
	{
		//创建管子
		pid_t pid;
		int fds1[2],fds2[2];//fds1 父亲读 fds2父亲写
		pipe(fds1);
		pipe(fds2);
		pid=fork();
		if(pid==0)//儿子进程
		{
			//另外两个管子用不到
			close(fds1[0]);
			close(fds2[1]);
			//儿子
			dup2(fds1[1],1);//向父亲写，涉及到标准输入的，都是网fds1[1]这个管子里写
			dup2[fds2[0],0];//儿子读
			//重定向以后可以关管子啦
			close(fds1[1]);
			close(fds2[0]);
			child_main();//child_main（）是个死循环
		}
		else
		{
			//那两个管子父亲用不到
			close(fds[1]);
			close(fds[2]);
			arr[index].s_pid=pid;
			arr[index].s_status=S_IDLE;
			arr[index].s_read=fds1[0];
			arr[index].s_write=fds2[1];
			arr[index].s_cnt=0;
		}
	}
}

void child_main()
{
	int fd_client;
	int flag=1;
	//从标准输入读一个整数
	while(scanf("%d",&fd_client)==1)
	{
		handle_request(fd_client);
		printf("%d\n",flag);
	}
}
