#include"SocKet.h"


//客户端有两个进程，client是用于外部访问所用，client_edge用于对边缘设备与服务器之间的连接
/*
 * 边缘端的任务：
 * 1、与服务器建立连接
*/
int main()
{
    SocKet *sockFd = NULL;
    sockFd = new SocKet();//执行默认初始化，建立连接
    sockFd->Soc_write('1');//窗口打开，我们先发送一个数据,表示已经就绪
    //cout<<"已发送"<<endl;
    char buf;
    /*
     * 服务器在建立连接后，服务器会向客户端发送控制信息
    */
    buf = sockFd->Soc_read();//这里要根据获取的信息，做相关处理
    cout<<"窗口进入"<<endl;
    /*客户端接受到信息后，进行相应的处理*/
//    if(buf == 'a'){//这里表示相机未打开
//        sockFd->Soc_write('b');
//    }
    //根据获取的数据进行相关处理
    sockFd->Soc_proc(buf);
    //这里应该阻塞，当对方传送结束的信息，才将信息释放
    sleep(100000000);//无线等待
    delete sockFd;
    return 0;
}
