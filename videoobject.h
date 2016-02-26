#ifndef VIDEOTHREAD
#define VIDEOTHREAD

#include <QtCore>
#include <QString>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>

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

public:
    // конструктор с параметром - имя видеофайла
    VideoObject(std::string fileName);
public slots:
    void process();
private slots:
    void readFrame();
signals:
    void finished();
};



#endif // VIDEOTHREAD

