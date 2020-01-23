#ifndef Soc_H
#define Soc_H
#include<head.h>

//这里是通信套接字类，负责处理信息
//一个连接分配一个套接字类(主要在服务端上使用)
/*
 * 类的简单介绍：
 * 1、得到相关连接的信息
 * 2、设定客户端传递的信息是单字节的，所以用一个字符即可
 * 3、我们根据这个字符来选择对应的函数来进行处理，处理则要利用线程进行处理
 * 4、得到一个线程的标识符，用于后面的类对该线程的控制
*/
class Soc{
public:
    Soc();//默认初始化，我认为就没什么事做了
    Soc(struct Soc_info&);//显示的初始化
    int set_Socinfo(struct Soc_info );
    /*
     *这个类就是得到新的类，则对它信息进行相关实现
     * 暂时的功能就是用摄像头，我考虑可以做成抽象类，根据得到的消息内容，分配不同的类去处理，暂时一个类足够了
     * 监听那边会返回一个结构体，得到之后，就进行处理
     */
    void Soc_Proce();
    void Soc_Camera();//这个函数就是用来打开相机的
    ~Soc();
private:
    //这里存放该类的通信套接字和信息
    struct Soc_info SockF;
    char buf;//一个buf获取信息
    pthread_t tld;//这里线程就与客户端进行交互
    pthread_t camera;
};

#endif // Soc_H
