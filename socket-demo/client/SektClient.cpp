/*
 * @Author: cdtangchao
 * @Desc: 添加注释
 * @Date: 2022-11-17 17:02:13
 * @LastEditors: cdtangchao
 * @LastEditTime: 2022-11-18 16:33:41
 */
#include "SektClient.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFSIZE 2048
#define SERVER_IP "10.254.170.75"
#define SERVER_PORT 16555

int csockfd;

void SektClient::createClient()
{
    struct sockaddr_in servaddr;
    char buff[BUFFSIZE];

    csockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (csockfd == -1)
    {
        printf("create socket error(%d):%s\n", errno, strerror(errno));
        return;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &servaddr.sin_addr);
    servaddr.sin_port = htons(SERVER_PORT);
    if (connect(csockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        printf("connect error(%d):%s\n", errno, strerror(errno));
        return;
    }

    printf("please input:");
    scanf("%s", buff);
    send(csockfd, buff, strlen(buff), 0);
    bzero(buff, sizeof(buff));
    recv(csockfd, buff, BUFFSIZE - 1, 0);
    printf("recv:%s\n", buff);

    close(csockfd);
}