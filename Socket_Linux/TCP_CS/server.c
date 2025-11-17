#include "socket_header.h"
#include <stdio.h>      // for printf, perror
#include <string.h>     // for memset

int main()
{   
    //1.创建监听socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    //2.设置服务器的地址
    //为了防止服务器重启之后进入time_wait可以通过setsocketopt
    //设置ip地址可以重用
    int reuse = 1;
    int ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    struct sockaddr_in server_addr;
    memset(&server_addr, 0 , sizeof(server_addr)); 
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8080);

    //3.将listenfd 与地址进行绑定
    ret = bind(listenfd, 
               (struct sockaddr *) &server_addr,
               sizeof(server_addr));
    if(ret < 0){

    }
    //4.通过listen将listenfd对应的socket对象的输入输出缓冲区
    //释放,并维护半连接队列和全连接队列
    ret = listen(listenfd, 10);

    while(1){
        int net_fd = accept(listenfd, NULL, NULL);
        const char * pstr = "welcome to server \n";
        ret = send(net_fd, pstr, strlen(pstr), 0);
        char buf[100] = {0};

        ret = recv(net_fd, buf, sizeof(buf), 0);
        printf("\n>> recv %d bytes : %s\n", ret, buf);
        ret = send(net_fd, buf, strlen(buf), 0);
    }

    return 0;
}

