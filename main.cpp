#include <QApplication>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoCapture cap("drop.avi");

    if(!cap.isOpened()){    // check if we succeeded
        std::cout << "Cannot open the video file" << std::endl;
        return -1;
    }

    Mat frame;
    namedWindow("video", 1);
    while ( cap.isOpened() )
    {
        cap >> frame;
        if(frame.empty()) break;

        imshow("video", frame);
        if(waitKey(30) >= 0) break;
    }

    return a.exec();
}
