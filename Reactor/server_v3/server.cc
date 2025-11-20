#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/socket.h>

#define EPOLL_EVENT_SIZE 100

void perror_if(bool condition, const char * error_message){
    if(condition){
        perror(error_message);
        exit(1);
    }
}

int main(){
    //1.创建监听套接字
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    perror_if(listen_fd == -1, "socket");
    //2.设置ip地址可重用
    int on = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    //3.绑定ip和端口
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8000);
    
    int ret = bind(listen_fd, (struct sockaddr *)
                   &server_addr, sizeof(server_addr));

    perror_if(ret == -1, "bind");
    //4.设置监听
    ret = listen(listen_fd, 10);
    perror_if(ret == -1, "listen");
    //5.创建epoll实例
    int epfd = epoll_create1(0);
    perror_if(epfd < 0, "epoll_create1");
    //6.使用epoll监听listen_fd的读事件
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.data.fd = listen_fd;
    ev.events = EPOLLIN;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listen_fd, &ev);
    perror_if(ret < 0, "epoll_ctrl");
    struct epoll_event *pArr = (struct epoll_event *)calloc(sizeof(ev), EPOLL_EVENT_SIZE);
    //7.开启事件循环
    while(1){
        int nready = epoll_wait(epfd, pArr, EPOLL_EVENT_SIZE, 5000 );
        perror_if(nready < 0, "epoll_wait");
        if(nready == 0){
            printf("epoll time out \n");
        }
        //nready > 0, 就是有已经就绪的文件描述符
        //轮询所有就绪的文件描述符数组
        else{
            for(int i = 0; i < nready; ++i){
                int fd = pArr[i].data.fd;
                //8.如果有新连接进来，要对其进行处理
                if(fd ==listen_fd){
                    struct sockaddr_in client_addr;
                    memset(&client_addr, 0, sizeof(client_addr));
                    socklen_t len = sizeof(client_addr);
                    int netfd = accept(listen_fd, (struct sockaddr *)
                                       &client_addr, &len);
                 //8.1打印客户端信息
                 printf("conn %d client[%s:%d] has connected.\n",
                        netfd,inet_ntoa(client_addr.sin_addr),
                        ntohs(client_addr.sin_port));
                 //8.2对新连接进行监听
                 ev.data.fd = netfd;
                 ev.events = EPOLLIN;
                 epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &ev);
                }
                //9.对已经建立好的连接收到数据进行处理
                else{
                    char buf[100] = {0};
                    ret = recv(fd, buf, sizeof(buf), 0);
                    if(ret == 0){
                        ev.data.fd = fd;
                        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
                        printf("conn %d has closed.\n", fd);
                        close(fd);
                        continue;
                    }
                    printf(">> recv %d bytes,%s\n", ret, buf);
                    ret = send(fd, buf, strlen(buf), 0);
                    printf(">> send %d bytes.\n", ret);
                }
            }//end of for
        }
    }//end of while
    close(epfd);
    close(listen_fd);
    return 0;
}
