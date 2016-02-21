#include <QApplication>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <stdio.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cv::VideoCapture cap("drop.avi");

    cv::Mat frame;
    cv::namedWindow("video", 1);
    while ( cap.isOpened() )
    {
        cap >> frame;
        if(frame.empty()) break;

        imshow("video", frame);
        if(cv::waitKey(30) >= 0) break;
    }

    return a.exec();
}
