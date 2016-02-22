#include <QApplication>
#include <QDebug>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <stdio.h>
#include <iostream>

using namespace cv;

// converts from cv::Mat to QImage
inline QImage  cvMatToQImage( const Mat &inMat )
{
    switch ( inMat.type() )
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );

        return image;
    }

        // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );

        return image.rgbSwapped();
    }
    default:
        qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}

// converts from cv::Mat to Qpixmap using QImage
inline QPixmap cvMatToQPixmap( const cv::Mat &inMat )
{
    return QPixmap::fromImage( cvMatToQImage( inMat ) );
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);




    VideoCapture cap("drop.avi");

    if(!cap.isOpened()){    // check if we succeeded
        std::cout << "Cannot open the video file" << std::endl;
        return -1;
    }

    Mat frame;
    cap >> frame;

    QPixmap image = cvMatToQPixmap(frame);

    QLabel *lbl = new QLabel();
    lbl->setPixmap( image );
    lbl->show();

    return a.exec();
}
