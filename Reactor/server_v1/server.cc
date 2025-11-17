#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(){
    //1.创建监听套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    if(listenfd == -1){
        perror("socket error");
        exit(1);
    }
    //2.初始化监听的ip和端口
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    //3.使用bind将socket与地址进行绑定
    int ret = bind(listenfd, (struct sockaddr *)&server_addr,
                   sizeof(server_addr));

    if(ret == -1){
        perror("bind error");
        exit(1);
    }

    //4.设置监听
    ret = listen(listenfd, 128);
    if(ret == -1){
        perror("listen");
        exit(1);
    }
    //5.建立连接
    char buf[512] = {0};
    while(1){
        int net_fd = accept(listenfd, NULL, NULL);
        const char *p = "welcome to server.\n";
        ret = send(net_fd, p, strlen(p), 0);
        printf("send %d byte(s)\n", ret);
        ret = recv(net_fd, buf, sizeof(buf), 0);
        printf("recv %d byte(s): %s\n", ret, buf);
    }
    return 0;
}


