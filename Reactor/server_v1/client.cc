#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     
#include <sys/socket.h> 
#include <arpa/inet.h>  

int main(){
    //1.简历客户端套接字
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    //2.设置服务器地址
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8000);
    //3.进行连接
    connect(client_fd, (const struct sockaddr *)
            &server_addr, sizeof(server_addr));

    //4.进行数据收发
    char buf[512] = {0};

    int ret = recv(client_fd, buf, sizeof(buf), 0);
    printf("recv %d byte(s):%s", ret, buf);
    const char *pstr = "hello, sever\n";
    ret = send(client_fd, pstr, strlen(pstr), 0);
    close(client_fd);
        
    return 0;
}

