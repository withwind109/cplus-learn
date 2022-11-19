/*
 * @Author: cdtangchao
 * @Desc: 添加注释
 * @Date: 2022-11-18 16:41:53
 * @LastEditors: cdtangchao
 * @LastEditTime: 2022-11-18 16:47:46
 */
#include <iostream>
#include "SektClient.h"

int main(int, char**) {
    SektClient *client=new SektClient();
    client->createClient();
}
