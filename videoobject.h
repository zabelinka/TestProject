#ifndef VIDEOTHREAD
#define VIDEOTHREAD

#include <QtCore>
#include <QString>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include "pip.h"

using namespace cv;

/* объект этого класса:
 * открывает видео  -- в конструкторе
 * устанавливает таймер по его fps  -- в конструкторе
 * connect таймер и функцию обновления  -- в конструкторе
 * передает очередной кадр главному потоку
*/

class VideoObject : public QObject{
    Q_OBJECT

private:
    VideoCapture capture;
    QTimer *timer;
    Mat frame;
    int fps;
    PiP* mainWidget;


public:
    // конструктор с параметрами - имя видеофайла и указатель на главный объект
    VideoObject(std::string fileName, PiP *widget);
    QSize getSize();

public slots:
    void process();
private slots:
    void readFrame();
signals:
    void updatedFrame(cv::Mat);
    void finished();

};



#endif // VIDEOTHREAD

