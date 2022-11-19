/*
 * @Author: cdtangchao
 * @Desc: 添加注释
 * @Date: 2022-11-17 17:02:05
 * @LastEditors: cdtangchao
 * @LastEditTime: 2022-11-18 17:23:23
 */
#include "SektServer.h"
#include <iostream>
#include <stdlib.h>

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>

#define BUFFSIZE 2048
#define DEFAULT_PROT 16555 //默认端口号
#define MAXLINK 2048       //最大链接数

int sockfd; //设置成全局，避免静态成员函数的stopServer访问不了

void SektServer::stopServer(int p)
{
    close(sockfd);
    printf("close server\n");
    exit(0);
};

void SektServer::startServer()
{
    struct sockaddr_in servaddr;
    char buff[BUFFSIZE];

    // AF_INET:TCP/IP – IPv4
    // SOCK_STREAM:TCP流
    //"protocol"一般设置为0
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // 创建失败 成功返回0
    if (sockfd == -1)
    {
        printf("create socket error(%d):%s\n", errno, strerror(errno));
        return;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(DEFAULT_PROT);
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)))
    {
        printf("bind error(%d):%s\n", errno, strerror(errno));
        return;
    }

    // int sockfd 套接字描述符
    // int input_queue_size 套接字使用的队列长度，置顶在请求队列中最大请求数
    if (listen(sockfd, MAXLINK) == -1)
    {
        printf("listen error(%d):%s\n", errno, strerror(errno));
        return;
    }

    printf("listening ...\n");

    //注册一个ctrl+c中断的信号监听
    signal(SIGINT, stopServer);

    while (true)
    {
        // int sock(套接字描述符), struct sockaddr *addr(网络通信的地址结构体), socklen_t *addrlen（套接字的数据类型）
        connfd = accept(sockfd, NULL, NULL);
        if (connfd == -1)
        {
            printf("accpet error(%d):%s\n", errno, strerror(errno));
        }

        //将buff清零
        bzero(buff, BUFFSIZE);

        recv(connfd, buff, BUFFSIZE - 1, 0);

        printf("recv:%s\n", buff);
        send(connfd, buff, strlen(buff), 0);
        close(connfd);
    }
};
