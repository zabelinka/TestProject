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
    timer -> start(int(1000 / fps));

}

void VideoObject::readFrame(){
    // get new frame
    capture >> frame;
    qDebug() << QThread::currentThreadId();
    connect(this, SIGNAL(updatedFrame(cv::Mat)), mainWidget, SLOT(getNewFrame(cv::Mat)), Qt::DirectConnection);

    // передача кадра в главный поток
    emit updatedFrame(frame);

}
