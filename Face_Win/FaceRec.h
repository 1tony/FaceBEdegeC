#ifndef FACEREC_H
#define FACEREC_H
#include"head.h"

class FaceRecognition
{
private:
    cv::Mat img;
    cv::CascadeClassifier face_cascade;

public:
    FaceRecognition();
    ~FaceRecognition();
    void recognition(int &);
    void setImg(cv::Mat &mat);
};

#endif // FACEREC_H
