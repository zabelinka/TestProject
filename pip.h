#ifndef PIP_H
#define PIP_H

#include <QMainWindow>
#include <QtCore>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/core/core.hpp"
#include <opencv2/videoio.hpp>

using namespace cv;

namespace Ui {
class PiP;
}

class PiP : public QMainWindow
{
    Q_OBJECT

public:
    explicit PiP(QWidget *parent = 0);
    ~PiP();



private:
    Ui::PiP *ui;
    QTimer *timer;
    VideoCapture capture;
    Mat frame;
private slots:
    void displayFrame();
};



#endif // PIP_H

