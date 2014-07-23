/*************************************************************************
	> File Name: client.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年07月03日 星期四 11时03分35秒
 ************************************************************************/

#include <stdio.h>
#include "msg.h"
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int argc,char *argv[])
{
if(argc!=3)
{
printf("argu not wnough\n");
exit(-1);
}

int fd_client,fd_file;
if((fd_client=socket(AF_INET,SOCK_STREAM,0))==-1)
{
perror("socket\n");
exit(-1);
}
MSG msg,rcv_msg;
struct sockaddr_in server_addr;
memset(&server_addr,0,sizeof(server_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_addr.s_addr=inet_addr(argv[1]);
server_addr.sin_port=htons(atoi(argv[2]));
if(connect(fd_client,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
{
perror("connect");
close(fd_client);
exit(-1);
}
printf("conecting!\n");

//传输数据
memset(&msg,0,sizeof(msg));
printf("input:");
scanf("%s",msg.s_buf);
fd_file=open("1.xv",O_WRONLY|O_CREAT,0666);
msg.s_len=strlen(msg.s_buf);
send(fd_client,&msg,msg.s_len+MSG_LEN,0);
float total=0;
//printf("%d %s\n",msg.s_len,msg.s_buf);
while(1)
{
memset(&rcv_msg,0,sizeof(MSG));
printf("begin \n");
recv(fd_client,&rcv_msg,MSG_LEN,0);
printf("begin1 \n");
total+=rcv_msg.s_len;
system("clear");
printf("downloading... %.2fkb\n",(double)total/1024);
if(rcv_msg.s_len>0)
{
recv(fd_client,&rcv_msg.s_buf,rcv_msg.s_len,0);
write(fd_file,rcv_msg.s_buf,rcv_msg.s_len);
}else
{
break;
}
}
close(fd_file);
close(fd_client);
return 0;
}









