#include"head.h"

struct Soc_info{
    int sockfd;
    struct sockaddr_in server;
};

struct Soc_info sld;
bool Network_client();//进行与服务器之间的连接

int main()
{
    Network_client();

    cv::VideoCapture capture;
    char picture[921654];//1.bmp图片的大小
    int bytes;
    capture.open(0);
    if(!capture.isOpened()){
        cout<<"摄像头打开失败"<<endl;
        return -1;
    }
    Mat frame;
    std::vector<int>param;
    param.push_back(CV_IMWRITE_PXM_BINARY);
    int fld=open("/home/zx/code/video/1.bmp",O_RDWR | O_CREAT,0777);
    if(fld<0){
        cerr<<"file failed"<<endl;
    }
    int fld1=open("/home/zx/code/video/2.bmp",O_RDWR | O_CREAT,0777);
    if(fld1<0){
        cerr<<"file failed"<<endl;
    }
    while(true){
        capture>>frame;
        //cout<<"c"<<endl;
        if(frame.empty())
        {
            cerr<<"frame failed"<<endl;
        }
        //这里先将数据转换成图片，然后再传
      cv::imwrite("/home/zx/code/video/1.bmp",frame,param);
      lseek(fld,0,SEEK_SET);//将指针指向首位
      //将数据传送
      /************读取数据这里应该是阻塞的吧，为什么会出现只读取到了部分数据*******/
      bytes = read(fld,picture,sizeof(picture));
      if(bytes < 0){
          cerr<<"read failed"<<endl;
      }
      if(bytes==0) break;//当未发送信息，就退出循环
      //cout<<"读取的图片大小："<<sizeof(picture)<<":"<<bytes<<endl;
      //可以整体的传输，但是在server端接收出现了问题

      bytes = write(sld.sockfd,picture,sizeof(picture));
      if(bytes < 0){
          //cerr<<"write failed"<<endl;
          perror("write:");

      }
      //cout<<"bytes:"<<bytes<<endl;
      /********************1.22测试用*********************/

      /****************************************/
        //waitKey(10);
    }
}
bool Network_client()
{
    sld.sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sld.sockfd<0)
    {
        cerr<<"socket error"<<endl;
    }
    bzero(&sld.server,sizeof(sld.server));
    sld.server.sin_family = AF_INET;
    sld.server.sin_addr.s_addr = inet_addr("192.168.1.105");
    sld.server.sin_port = htons(9999);
    //这里与服务建立连接
    if(connect(sld.sockfd,(struct sockaddr*)&sld.server,sizeof(sld.server))<0)
    {
        cerr<<"connect erro"<<endl;
    }
    else{
        cout<<"套接字："<<sld.sockfd<<endl;
        cout<<"客户端与服务器相机已建立连接"<<endl;
    }
    return true;
}
