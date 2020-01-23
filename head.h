#pragma once
#ifndef HEAD_H
#define HEAD_H

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/objdetect.hpp"
#include <iostream>
/*Linux需要的文件*/
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <fcntl.h>
#include<pthread.h>
using namespace std;
using namespace cv;
struct Soc_info{
    int sockfd;
    struct sockaddr_in client;
    int flag;//用来显示相机是否打开(同样用来线程的控制)
    int camera_flag;//用来判定摄像头数据是否就绪
};

#endif //
