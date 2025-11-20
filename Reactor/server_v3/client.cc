#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/socket.h>

void perror_if(bool condition, const char * error_message){
    if(condition){
        perror(error_message);
        exit(1);
    }
}

int main(){
    //1.创建客户端套接字
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    perror_if(clientfd < 0, "socket");

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8000);
    server_addr.sin_addr.s_addr = INADDR_ANY;   

    //2.建立连接
    int ret = connect(clientfd, (const struct sockaddr *)
                      &server_addr, sizeof(server_addr));
    perror_if(ret != 0, "connect");
    printf("connect success!\n");

    //3.使用select监听clientfd和标准输入
    fd_set readfds;
    while(1){
        FD_ZERO(&readfds);
        FD_SET(clientfd, &readfds);
        FD_SET(STDIN_FILENO, &readfds);

        select(clientfd + 1, &readfds,
               NULL, NULL, NULL);
        char buf[100] = {0};
        memset(buf, 0, sizeof(buf));
        if(FD_ISSET(STDIN_FILENO, &readfds)){
            ret = read(STDIN_FILENO, buf, sizeof(buf));
            printf(">> read %d bytes.\n", ret);
            ret = send(clientfd, buf, strlen(buf), 0);
            printf(">> send %d bytes.\n", ret);
        }

        if(FD_ISSET(clientfd, &readfds)){
            ret = recv(clientfd, buf, sizeof(buf), 0);
            if(ret == 0){
                break;
            }
            printf(">> recv %d bytes from server:%s", ret, buf);
        }
    }
    close(clientfd);
    return 0;
}
