#include "pip.h"
#include "ui_pip.h"

PiP::PiP(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PiP)
{
    ui->setupUi(this);          // create the widget
    capture.open("drop.avi");   //open video
    int fps = capture.get(CV_CAP_PROP_FPS);         // frame per second

// --- !!! --- изменить размер окошка под размер видео
// ui->label->resize(capture.get(CV_CAP_PROP_FRAME_HEIGHT), capture.get(CV_CAP_PROP_FRAME_WIDTH));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(displayFrame()));      // connect the timer to the widget and to the method
    timer -> start(int(1000 / fps));


}

PiP::~PiP()
{
    delete ui;
}

// after each refresh
void PiP::displayFrame(){

    capture >> frame;       // get new frame

    // create QPixmap from Mat
    QImage img= QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    QPixmap pix = QPixmap::fromImage(img);

    ui->label->setPixmap(pix);          // display the pixmap on the label
}


