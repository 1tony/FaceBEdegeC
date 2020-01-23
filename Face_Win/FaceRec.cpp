#include"FaceRec.h"

FaceRecognition::FaceRecognition(){}

FaceRecognition::~FaceRecognition()
{
    //delete face_cascade_name;
}

void FaceRecognition::setImg(cv::Mat &mat)
{
    this->img = mat;
}

void FaceRecognition::recognition(int &face_number)
{
    //-- 1. Load the cascades
    if (!face_cascade.load("/home/wlm/Opencv/opencv-3.4.0/data/haarcascades"
                           "/haarcascade_frontalface_alt.xml")){ printf("--(!)Error loading face cascade\n"); return ; };
    std::vector<cv::Rect> faces;
    cv::Mat img_gray;

    cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(img_gray, img_gray);

    //-- 2. Detect faces
    face_cascade.detectMultiScale(img_gray, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
    for (int i = 0; i < faces.size(); i++)
        {
            cv::Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
            ellipse(img, center, cv::Size(faces[i].width / 2, faces[i].height / 2),
                    0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
    }
    face_number=faces.size();
}
