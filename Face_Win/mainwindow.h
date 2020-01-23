#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"FaceRec.h"
//#include<qfiledevice.h>
#include <QMainWindow>
//#include <QPixmap>
#include<QTime>
#include<QPainter>

using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    /*
     * 用于初始时将图片区域空置
    */
    void V_Empty();

    /*
     * 1、从终端获取图片的方式，一个是利用nfs挂载直接图取
     * 2、利用TCP/UDP的方式将进行通信获取数据
     * 从终端获取图片，并存放在picture
    */

    void V_Capture(cv::Mat &picture);

    /*
     * 获取图片后进行识别（调用opencv中的相关函数）
     * 返回值，可能需要识别得到的结果信息,可构造结构体
    */
    void V_Chuli(cv::Mat &picture);

    /*
     * 得到的数据信息，显示到旁边的菜单栏中
     * 时间、人数
     * 并且做成曲线图（当有人数变化时进行记录）
     * 并存入数据库中
    */
    void V_Display(int a);
    /*将得到的数据表格显示出来,人数和时间*/
    void S_Chart();//初始花表格
    void V_Chart();
    /*脸部的检测*/
    void detectAndDisplay(cv::Mat &image);
    /*这里要作一个线程持续获取时间*/
    void V_showtime();
    //void onDateTime();
    /*
     *当数据发生变化时，折线图发生变化：
     *记录时间和对应的人数变化
    */
    //void V_Chart();
    Ui::MainWindow *getUI();
    bool getflag();
    bool *getA();
    ~MainWindow();

private slots:
    //开始读取的视频
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    cv::Mat image;
    bool flag;//这个变量来检测按钮的值，来打开按钮
    int peo_num;
    bool a[1];//用来取消对应线程时使用
    int count_p;//记录，总共的记录次数
};
#endif // MAINWINDOW_H
