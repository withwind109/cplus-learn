/*
 * @Author: cdtangchao
 * @Desc: 添加注释
 * @Date: 2022-11-17 17:02:21
 * @LastEditors: cdtangchao
 * @LastEditTime: 2022-11-18 17:24:04
 */
class SektServer
{
private:
    int connfd;
    static void stopServer(int p);
public:
    void startServer();
};