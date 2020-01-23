#include"Soc.h"
#include"Listen.h"
//对于socket的连接，一定要改进到select上

struct Socc{
    struct Soc_info *tt;//存放套接字的相关数据
    bool flag;
};



Soc::Soc()
{

}

Soc::Soc(struct Soc_info &cli)
{
    SockF = cli;//显示的初始化
    SockF.flag = false;
    cli.camera_flag = false;
}
/*****************************************************************/
bool Network_client(struct Soc_info *temp)
{
    //默认构造就是按我的默认网络进行初始化
    socklen_t len;
    struct Soc_info sld;
    //先初始化一个套接字
    sld.sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sld.sockfd<0){
        cerr<<"listened failed"<<endl;
    }else cout<<"套接字初始化成功"<<endl;
    bzero(&sld.client,sizeof(sld.client));
    sld.client.sin_family = AF_INET;
    sld.client.sin_port = htons(9999);
    sld.client.sin_addr.s_addr = htonl(INADDR_ANY);//这里监听所有的网卡
    len = sizeof (struct sockaddr);
    //进行监听
    if(bind(sld.sockfd,(struct sockaddr*)&sld.client,len)<0){
        cerr<<"bind failed"<<endl;
    }else cout<<"绑定成功"<<endl;
    listen(sld.sockfd,5);//这里设置监听的相关设置
    temp->sockfd = accept(sld.sockfd,(struct sockaddr*)&temp->client,&len);
    if(temp->sockfd<0)
    {
        perror("accept erro:");
    }
    return true;
}
/*
 * 将图片存放入数据中
 * 图像数据的接收，我们这里另外建立一条连接，主线程的连接用来通信，这里的线程的连接用来传输数据
*/
void *Proc_picture(void *arg)
{
    /*********1.21****************************/
    /*这里应该使用现有的Soc类来建立连接，应该可以吧*/
    //获取套接字就可以了
    char bb1;
    //有时候，是用开辟内存还是直接变量的方式要斟酌，因为两者的存储地址是不同的
    struct Soc_info *temp;//用来存放接受的数据信息
    temp = new struct Soc_info();
    Network_client(temp);
    //这里用类传递端口号，出现空值，所以没没有调用类
    if(temp->sockfd<0){
        cout<<"连接建立失败"<<endl;
    }
    //连接建立后，认为应该做一些交互，以确认对方是边缘端
    bb1 = 'b';
    if(write(temp->sockfd,&bb1,sizeof(bb1))<0)
    {
        cout<<"数据发送失败"<<endl;
    }
    //对方接收到信息后，就会向该套接字发送图片，所以后面就直接读取套接字的内容即可
    /****************************************************/
    char buf1[921654];
    char bb;
    cout<<"进入Proc_picture"<<endl;
    struct Soc_info *pic = (struct Soc_info*)arg;
    //这里应该将数据转存为另一张图片
    string pic_name= "/home/wlm/code/video/1.bmp";
    string pic_name1= "/home/wlm/code/video/2.bmp";
    /*图片转储时使用*/
    std::vector<int>param;
    param.push_back(CV_IMWRITE_PXM_BINARY);
    //int fld=open(pic_name.c_str(),O_RDWR);
    cout<<"Socc:"<<temp->sockfd<<endl;
    //当外部控制信息将flag置位，然后将套接字空闲出来
    //退出循环表示监控结束，则应该向外部发送退出的连接
    int fld=open(pic_name.c_str(),O_RDWR);
    if(fld<0)
    {
        perror("fld failed:");
    }
    ssize_t byte;
    while(pic->flag){
        byte = recv(temp->sockfd,buf1,sizeof(buf1),MSG_WAITALL);
        //byte=read(temp->sockfd,buf1,sizeof(buf1));
        if(byte<=0)//-----------------接收数据信息
        {
            perror("read :");
        }
        cout<<"byte:"<<byte<<endl;
        lseek(fld,0,SEEK_SET);//将指针指向首位
        if(write(fld,&buf1,sizeof(buf1))<=0)//将数据写入文件中
        {
            perror("write file");
        }
        /*****************1.22*************************/
        //这里因为图像质量不高，所以将文件关闭，然后再开启（重复的系统调用，可能会有些耗时间）
        //close(fld);//将文件关闭
        /*********************************************/
        waitKey(15);
        Mat image = imread(pic_name);
        if(image.empty())
        {
            cout<<"空"<<endl;
            continue;
        }
        //imshow("test",image);
        //这里要再将图片存入
        pic->camera_flag = true;
        //因为传输中，数据斌不是那么完美，筛选出完整的image将其存储
        cv::imwrite("/home/wlm/code/video/2.bmp",image,param);
        //waitKey(10);
    }
    //结束，向对方发一个空的字符。表示连接的结束
    pic->camera_flag = false;
    write(temp->sockfd,&bb,sizeof(bb));
    delete temp;

}
/*
 * 这里用的线程来当代数据的读入，后面可以更换成select
*/
void *Proce(void *arg)
{
    cout<<"进入处理函数，开始处理"<<endl;
    int file_client;//存放要传递给客户端的文件描述符
    //对控制信息，和数据信息分别用不同的变量存储，那么交流的顺序必须要一直
    char buf;//控制信息
    struct Soc_info *cli = (struct Soc_info*)arg;//格式进行转换
    //这边要对信号进行相关的注册
    int err;
    err = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
    if(err < 0){
        cerr<<"setstate failed"<<endl;
    }
    err = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);//退出后立即取消
    if(err<0){
        cerr<<"settype failed"<<endl;
    }
    pthread_t tld;
    cli->flag = true;
     //我感觉这里不需要死循环处理，因为这里进行简单的信息交互即可
    //这里做一个while循环，想要是处理多种的信息，，但好像没必要，建立一次的连接即可
    //还有就是，这里的read对应套机字和图像接收的套接字是相同的，我担心这样两个read是否会产生问题
        /*
         * 信息通信的流程：
         * 接收buf（控制信号）->发送buf（控制信号）->接收buf1（数据信息）
         *
        */
      read(cli->sockfd,&buf,sizeof(buf));//
      //buf为1说明，说明这是摄像头的进程
     if(buf=='1'){//表示就绪------控制信号
         buf = 'a';
         int t;
         t = write(cli->sockfd,&buf,sizeof(buf));//收到消息，给对方回一个消息，a表示客户端准备好图像-------发送控制信号
         if(t<=0){
             cerr<<"write failed:"<<endl;
         }
         //用脚本传输，然后一行搞定
         system("expect /home/wlm/code/test.sh");
        /**********************************************************/
        /***********************************************************/
         //上面进行通信后，这里就应该返回相关信息。
        //其实只需要一个标志信息，即图像准备完毕数据处理如果是图像，就需要再开线程处理
         err = pthread_create(&tld,NULL,Proc_picture,cli);
         if(err<0){
             cerr<<"pthread failed:"<<endl;
         }
        pthread_join(tld,NULL);
        close(tld);
    }
     //这边就是客户端的信息，客户端的信息就是简单的控制
    //else if(){};


}
/*
 * 这里对信息进行处理，，需要持续监控是否有信息进来
*/

void Soc::Soc_Proce()
{
    int err;
    if(SockF.sockfd<0){//进行检错
        cerr<<"初始化套接字失败"<<endl;
    }
    //这边建立连接后，得到消息
    //开辟新的线程，来处理得到的消息
    err = pthread_create(&tld,NULL,Proce,&SockF);
    if(err < 0){
        cerr<<"pthread_create failed"<<endl;
    }
    Soc_Camera();//然后等待调用图像处理程序
}
/************************************************************************/
void *Proc_Camera(void *arg)
{
    bool camera_flag = (bool)arg;
    while(!camera_flag){}//这里就是持续等待其变成1；
    //然后调用图像处理程序
    cout<<"进入图像处理程序"<<endl;
    //这里要再开辟一个进程，那么就要注意进程空间的开辟
    if(fork() == 0){
        execl("/home/wlm/code/My_Video/first",(char*)0);
    }
    else return (void*)0;
}
/*
 * 同样是开辟线程
 * 检测摄像头是否打开，如果打开，就调用处理程序
 *
*/
void Soc::Soc_Camera()
{
    //为了不阻塞整个程序的运行，也只有开辟线程
    int err;
    err = pthread_create(&camera,NULL,Proc_Camera,&this->SockF.camera_flag);
    if(err < 0){
        cerr<<"pthread_create failed"<<endl;
    }
    cout<<"Soc_Camera"<<endl;
}
/***********************************************************************/
Soc::~Soc()
{
    //析构函数，将相关资源释放
    //套接字、开辟的关联进程都要利用信号的方式将其杀死
    int cval;
    close(SockF.sockfd);
    cval = pthread_cancel(tld);
    close(camera);
    if(cval < 0){
        cerr<<"cancel thread failed"<<endl;
    }
    cout<<"退出"<<endl;
}
