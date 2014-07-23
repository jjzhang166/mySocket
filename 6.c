/*************************************************************************
	> File Name: pool_client.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年07月05日 星期六 23时45分29秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
int main(int argc,char *argv[])
{
 if(3 != argc)
 {
 printf("EXE IP PORT\n");
 exit(-1);
 }

int fd_server;
fd_server = socket(AF_INET ,SOCK_DGRAM ,0);

struct sockaddr_in server_addr;


char buf[8192]="";
int addr_len=sizeof(struct sockaddr_in);
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = inet_addr(argv[1]);
server_addr.sin_port = htons(atoi(argv[2]));
while(bzero(buf,8192) ,fgets(buf,8192,stdin)!=NULL)
{

printf("%s %d \n",inet_ntoa(server_addr.sin_addr),ntohs(server_addr.sin_port));
sendto(fd_server ,buf ,8192 ,0 ,(const struct sockaddr*)&server_addr,addr_len);
bzero(buf,8192);
recvfrom(fd_server,buf,8192,0,NULL,NULL);
puts(buf);
}
/*while(1)
{
bzero(buf,8192);
recvfrom(fd_server,buf,8192,0,( struct sockaddr*)&server_addr,&addr_len);
puts(buf);
}
*/
return 0;
}
