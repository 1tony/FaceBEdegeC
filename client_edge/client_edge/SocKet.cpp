#include"SocKet.h"
SocKet::SocKet()
{
    //向服务器发起通信，并发送控制字符
    //先查询状态，后续再发相关信息处理
    sld.sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sld.sockfd<0)
    {
        cerr<<"socket error"<<endl;
    }
    bzero(&sld.server,sizeof(sld.server));
    sld.server.sin_family = AF_INET;
    //这里设置本机为地址
    //sld.server.sin_addr.s_addr = inet_addr("127.0.0.1");
    //测试1.0
    //将地址设为服务器的地址
    sld.server.sin_addr.s_addr = inet_addr("192.168.1.105");
    sld.server.sin_port = htons(8888);
    //这里与服务建立连接
    if(connect(sld.sockfd,(struct sockaddr*)&sld.server,sizeof(sld.server))<0)
    {
        cerr<<"connect erro"<<endl;
    }
    cout<<"客户端与服务器已建立连接"<<endl;
    flag = true;
}

void SocKet::Soc_proc(char x)
{
    pthread_t car_;//用来执行另一个carema的程序
    switch(x)
    {
        case 'a'://收到控制信号a后就发送图片
            if(fork() == 0)
            {
                sleep(5);//这里应该做个延时，等待那边配置
                //上面将程序接收后，就另外执行
                //这里就是一个新的进程,这里进程的任务就是与服务端建立连接，然后传送图片数据
                cout<<"进入子进程，开辟"<<endl;
                execl("/home/zx/code/carema",(char*)0);
            }
            /*************************************************/
            //Soc_proc_picture();
            //pthread_join(car_,NULL);
            break;
            }
}
/***********************************************************************************************/
/**********************************Soc_write***************************************************/
void SocKet::Soc_write(char buf)
{
    int bytes;
    //cout<<"客户端已发送"<<endl;
    bytes = write(sld.sockfd,&buf,sizeof(buf));
    if(bytes < 0){
        cerr<<"write failed"<<endl;
    }
}

void SocKet::Soc_write()
{
    //这个函数将数据图像发送
    int bytes;
    char picture[921654];//1.bmp图片的大小
    bytes = write(sld.sockfd,picture,sizeof(picture));
    if(bytes < 0){
        cerr<<"write failed"<<endl;
    }
}

char SocKet::Soc_read()
{
    int bytes;
    char buf;
    cout<<"等待信息接"<<endl;
    bytes = read(sld.sockfd,&buf,1);
    if(bytes<0){
        cerr<<"read failed"<<endl;
    }
    cout<<"消息："<<buf<<endl;
    return buf;
}
SocKet::~SocKet()
{
    /*清理相关资源*/
    close(sld.sockfd);
    close(tld);
    flag = false;
    //这里要对Proc进行资源释放，将值传入，将flage进行修改
}
