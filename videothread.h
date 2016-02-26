#ifndef VIDEOTHREAD
#define VIDEOTHREAD

#include <QThread>
#include <QtCore>
#include <QString>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/core/core.hpp"
#include <opencv2/videoio.hpp>

using namespace cv;

/* объект этого класса:
 * открывает видео  -- в конструкторе
 * устанавливает таймер по его fps  -- в конструкторе
 * connect таймер и функцию обновления  -- в конструкторе
 * передает очередной кадр главному потоку
*/

class VideoThread : public QThread{
    Q_OBJECT
private:
    VideoCapture capture;
    QTimer *timer;
    Mat frame;

public:
    VideoThread();      // конструктор
    // конструктор с параметром - имя видеофайла
    VideoThread(QString fileName){
        capture.open(fileName);   //open video
        int fps = capture.get(CV_CAP_PROP_FPS);         // frame per second
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(displayFrame()));      // connect the timer to the widget and to the method
        timer->start(int(1000 / fps));

    }
private slots:
    // обновление картинки
    void displayFrame(){

        capture >> frame;       // get new frame

        // --- !!!!!!!! В ОСНОВНОМ ПОТОКЕ !!!!!!!!!!!!

        // create QPixmap from Mat
        /*
         * QImage img= QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
         * QPixmap pix = QPixmap::fromImage(img);
         *
         * // --- !!! --- изменить размер окошка под размер видео
         *
         * ui->label->setPixmap(pix);          // display the pixmap on the label
        */
    }


};



#endif // VIDEOTHREAD

