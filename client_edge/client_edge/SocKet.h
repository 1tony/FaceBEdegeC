#ifndef SOCKET_H
#define SOCKET_H
#include"head.h"
//这个类用来进行相关网络通信
class SocKet{
public:
    //默认初始化，建立连接，获取相关套接字
    SocKet();
    ~SocKet();
    //下面则是相关功能
    void Soc_proc(char x);//这里是数据进行处理的地方
    void Soc_proc_picture();//将图片进行处理
    void Soc_write();//写信息
    void Soc_write(char a);//重载函数
    char Soc_read();//读到信息，要向上返回，然后交给窗口进行处理
    //获取私有变量
    struct Soc_info *get_Socinfo(){return &sld;};
    bool get_flag(){return flag;};


private:
    struct Soc_info sld;
    bool flag;
    pthread_t tld;
};

#endif // SOCKET_H
