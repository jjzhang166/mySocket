修改的文件是my_socket.c文件中的一个函数
handle_request(int fd_client)这个函数
将刚开始处理的第一条语句recv(fd_client,msg.s_buf,msg.s_len,0)
这句话注释掉，将会造成后面的接收数据乱套啦
所以说在服务前的文件即便是有这个请求文件，也是无法打开，供客户端下载
的、
