#include"Listen.h"
//#include"head.h"
#define MAX 10
//Listen::Listen()
//{
//    /**********1..21********/
//    //将8888作为默认的端口
//    Listen(8888);
//    /***********************/
//}//u_int16_t port
Listen::Listen()
 {
     //默认构造就是按我的默认网络进行初始化
     socklen_t len;
     //先初始化一个套接字
     this->listenfd.sockfd = socket(AF_INET,SOCK_STREAM,0);
     if(this->listenfd.sockfd<0){
         cerr<<"listened failed"<<endl;
     }else cout<<"套接字初始化成功"<<endl;
     bzero(&listenfd.client,sizeof(listenfd.client));
     listenfd.client.sin_family = AF_INET;
     listenfd.client.sin_port = htons(8888);
     listenfd.client.sin_addr.s_addr = htonl(INADDR_ANY);//这里监听所有的网卡
     len = sizeof (struct sockaddr);
     //进行监听
     if(bind(this->listenfd.sockfd,(struct sockaddr*)&listenfd.client,len)<0){
         cerr<<"bind fail"<<endl;
     }else cout<<"绑定成功"<<endl;
     listen(this->listenfd.sockfd,MAX);//这里设置监听的相关设置
 }
/*设置监听*/
 struct Soc_info Listen::accept_1()
 {
     struct Soc_info info;
     socklen_t len;
     len = sizeof(struct sockaddr);
     cout<<"等待新的连接"<<endl;
     //注意这里accept是阻塞的,返回一个通信套接字
     info.sockfd = accept(this->listenfd.sockfd,(struct sockaddr*)&info.client,&len);
     if(info.sockfd<0)
     {
         perror("accept erro:");
     }
     return info;
 }


Listen::~Listen()
 {
     //空
 }
