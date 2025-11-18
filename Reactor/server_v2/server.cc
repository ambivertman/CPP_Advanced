#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <thread>
using std::thread;

void perror_if(bool condition, const char * error_message){
    if(condition){
        perror(error_message);
        exit(1);
    }
}

void task(int client_fd){
    char buf[512];
    int ret = 0;
    const char * pstr = "hello, this is server\n";
    memset(buf, 0 , sizeof(buf));
    ret = send(client_fd, pstr, strlen(pstr), 0);
    printf("send %d byte(s)\n", ret);
    ret = recv(client_fd, buf, sizeof(buf), 0);
    if(ret > 0){
        printf("recv %d byte(s):%s\n", ret, buf);
        ret = send(client_fd, buf, strlen(buf), 0);
        printf("echo send %d byte(s)\n", ret);
    }
    else if(ret == 0){
        printf("client disconnected...");
    }
    else{
        printf("send error\n");
    }
    close(client_fd);
}


int main(){
    //1.创建监听套接字
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    perror_if(listen_fd == -1, "socket");

    //2.绑定ip和端口
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8000);

    int ret = bind(listen_fd, (struct sockaddr *)
                   &server_addr, sizeof(server_addr));
    perror_if(ret == -1, "bind");

    //3.设置监听
    ret = listen(listen_fd, 10);
    perror_if(ret == -1, "listen");

    //4.建立连接
    while(1){
        int net_fd = accept(listen_fd, NULL, NULL);
        thread t(task,net_fd);
        t.detach();
    }

    return 0;
}
