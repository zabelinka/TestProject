#include "videoobject.h"

VideoObject::VideoObject(std::string fileName, PiP *widget){
    capture.open(fileName);
    fps = capture.get(CV_CAP_PROP_FPS);         // frame per second
    timer = new QTimer(this);
    mainWidget = widget;
}

void VideoObject::process(){
    qDebug("I launch the timer ");
    // по срабатыванию таймера читается следующий кадр
    connect(timer, SIGNAL(timeout()), this, SLOT(readFrame()));      // connect the timer to the widget and to the method
    connect(this, SIGNAL(updatedFrame(cv::Mat)), mainWidget, SLOT(getNewFrame(cv::Mat)), Qt::DirectConnection);
    timer -> start(int(1000 / fps) );        // int(1000 / fps)

}

void VideoObject::readFrame(){
    // get new frame
    capture >> frame;

    // передача кадра в главный поток, если он есть
    if (frame.data) {
        emit updatedFrame(frame);
    }
    else {
        emit finished();
    }


}
