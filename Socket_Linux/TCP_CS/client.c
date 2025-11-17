#include "socket_header.h"
#include <string.h>
#include <stdio.h>

int main(void){
    //1.建立客户端套件字
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    //2.设置服务器地址
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8080);

    //3.进行连接
    connect(clientfd, (const struct sockaddr *)
            &server_addr, sizeof(server_addr));
    //4.进行数据收发
    char buf[100] = {0};

    int ret = recv(clientfd, buf, sizeof(buf), 0);
    printf(">>recv %d bytes: %s", ret, buf);

    const char * pstr = "hello server";
    ret = send(clientfd, pstr, strlen(pstr), 0);
    
    close(clientfd);

    return 0;
}



