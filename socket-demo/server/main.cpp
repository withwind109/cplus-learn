/*
 * @Author: cdtangchao
 * @Desc: 添加注释
 * @Date: 2022-11-18 16:37:02
 * @LastEditors: cdtangchao
 * @LastEditTime: 2022-11-18 16:40:58
 */
#include <iostream>
#include "SektServer.h"

int main(int, char**){
    SektServer *server=new SektServer();
    server->startServer();
}
