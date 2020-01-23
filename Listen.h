#pragma once
#ifndef LISTEN_H
#define LISTENT_H
#include"head.h"
//这个类负责监听套接字
class Listen{
public:
    //暂时看来就只有建立连接
    /*
     * 默认初始化
     * 默认初始化，则只进行相关连接的初始化操作
    */
    Listen();
    //Listen(in_port_t);//自行绑定对应的端口号
    /*
     * 这里等待连接，连接到达后，则返回一个通信套接字
    */
     struct Soc_info  accept_1();
     int getsoket(){return listenfd.sockfd;};//返回套接字
    /*
     * 释放资源
    */
    ~Listen();//析构
private:
     struct Soc_info listenfd;
};

#endif // LISTEN_H
