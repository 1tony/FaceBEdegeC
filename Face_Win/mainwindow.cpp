#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"pthread.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("border-image:url(/home/wlm/code/1.jpg);");
    flag=false;
    peo_num=0;
    count_p=-1;
    S_Chart();
    this->V_Empty();
    /*
     * 在窗口打开则计算时间，这个时间需要被窗口类共享
     * 时间的获取利用线程来持续的获取
    */
   a[0]=true;
   V_showtime();

}

Ui::MainWindow *MainWindow::getUI()
{
    return this->ui;
}
bool MainWindow::getflag()
{
    return flag;
}
bool *MainWindow::getA()
{
    return a;
}
MainWindow::~MainWindow()
{
    delete ui;
    /*让线程取消*/
    a[0]=0;

}
void MainWindow::S_Chart()
{
    QTableWidgetItem *Item;
    QStringList Text;
    Text<<"时间"<<"人数";
    ui->Tongji->setColumnCount(Text.count());
    for(int i=0;i<ui->Tongji->columnCount();++i)
    {
        Item=new QTableWidgetItem(Text.at(i)); //获取字符
        QFont font=Item->font();//获取原有字体设置
        font.setBold(false);//设置为粗体
        font.setPointSize(12);//字体大小
        Item->setTextColor(Qt::white);//字体颜色
        Item->setFont(font);//设置字体
        ui->Tongji->setHorizontalHeaderItem(i,Item);
    }
}
/**************************获取时间，显示******************************/

void *onTime(void *arg)
{
    MainWindow *u=(MainWindow *)arg;
    /*
     * 利用linux自带的系统调用多线程，将整个窗体类进行调用
     */
    while(u->getA()[0])
    {
       QDateTime Time = QDateTime::currentDateTime();
       QString s_t = QString::number(Time.date().month())+"月"+":"
                      ""+QString::number(Time.date().day())+"日"+""
                      ""+"  "+QString::number(Time.time().hour())+":"
                      ""+QString::number(Time.time().minute())+":"
                      ""+QString::number(Time.time().second())+"";
        u->getUI()->label_3->setText(s_t);
    }
    cout<<"退出"<<endl;
}
void MainWindow::V_showtime()
{

    int err;
    pthread_t t_time;
    int a=0;
    cout<<"ui的地址"<<this<<endl;
    err = pthread_create(&t_time,NULL,onTime,this);
}
/*********************************************************/

void MainWindow::V_Empty()
{
    Mat picture(100,100,CV_32F,Scalar(0,0,0));
    QImage temp = QImage((const unsigned char*)(picture.data),
                        picture.cols, picture.rows, QImage::Format_RGB888);
    temp = temp.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                    ui->label->setPixmap(QPixmap::fromImage(temp));

    this->ui->peo_number->setText("0");
}
/****************************开启摄像头，开始识别*******************/
void *C_pic(void *arg){
    /*这里开启摄像头进行捕捉*/
    bool flag=(bool)arg;
    cv::VideoCapture capture;
    capture.open(0);
    if(!capture.isOpened()){
        cout<<"摄像头打开失败"<<endl;
        return (void *)-1;
    }
    Mat frame;
    cout<<"vvv"<<endl;
    std::vector<int>param;
    param.push_back(CV_IMWRITE_PXM_BINARY);
    while(flag){
        capture>>frame;
        if(frame.empty())
        {
            cerr<<"frame failed"<<endl;
        }
        //imshow("pic",frame);
      cv::imwrite("/home/wlm/code/video/1.bmp",frame,param);
        //waitKey(100);
    }
}
void MainWindow::on_pushButton_clicked()
{
    /*
     * 进来这里开辟线程，如果需要将摄像头打开并录取视频
     * （！如果是移植到树莓派上，则就是检测改文件是否存在，进行代码修改）
    */
    flag=!flag;
    //pthread_t tld;
    string pic_name= "/home/wlm/code/video/2.bmp";
    this->ui->pushButton->setText("关闭");//进入后按钮则要变换内容
    while(flag)
    {
        Mat image = imread(pic_name);
        //这里需要做一次的检测，因为图片实现时，图片还未完全生成
        //这种情况下，利用continue进行跳过
        if(image.empty())
        {
            cerr<<"read erro"<<endl;
            continue;
        }
        //imshow("first",image);
        detectAndDisplay(image);

        QImage img = QImage((const unsigned char*)(image.data),
                            image.cols, image.rows, QImage::Format_RGB888);
        img = img.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                        ui->label->setPixmap(QPixmap::fromImage(img));
        if(waitKey(25) >= 0)
            break;
    }
    this->V_Empty();
    this->ui->pushButton->setText("开启");
}


/*利用级联分类器实现对目标的检测（面部）*/
void MainWindow::detectAndDisplay(Mat &image)
{
    FaceRecognition FR;
    int p_num=0;//存放此次数据
    FR.setImg(image);
    FR.recognition(p_num);
    if(p_num!=peo_num)//如果不相同，则更新数据
    {
        /*数据发生更改，则要进行记录*/
        count_p=count_p+1;
        peo_num=p_num;
        V_Chart();
    }
    this->ui->peo_number->setText(QString::number(p_num));
}
/**************************将人数时间获取，可以做好表格，显示，初始化时，则可以从数据库中读取(暂时读本地缓存)**********/
void MainWindow::V_Chart()
{
    QDateTime Time = QDateTime::currentDateTime();
    //ui->Tongji->resizeRowsToContents();//根据内容变换行
    ui->Tongji->insertRow(0);
    QString s_t = QString::number(Time.time().hour())+":"
                  ""+QString::number(Time.time().minute())+":"
                  ""+QString::number(Time.time().second())+"";
    QTableWidgetItem *I= new QTableWidgetItem(s_t);
    cout<<"人数"<<count_p<<endl;
    ui->Tongji->setItem(0,0,I);
    QTableWidgetItem *II= new QTableWidgetItem(QString::number(peo_num));
    ui->Tongji->setItem(0,1,II);
}



