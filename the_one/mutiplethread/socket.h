/*************************************************************************
	> File Name: socket.h
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月03日 星期四 15时27分04秒
 ************************************************************************/
//将头文件加入
int listenfd_init(char* ip,char* port);
void handle_request(int fd_client);
