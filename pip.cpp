#include "pip.h"
#include "ui_pip.h"
#include "videoobject.h"

PiP::PiP(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PiP)
{
    ui->setupUi(this);          // создаем виджет с label

    // создаем два потока и два соотвествующих ВидеоОбъекта
    QThread* thread1 = new QThread();
    QThread* thread2 = new QThread();

    VideoObject* video1 = new VideoObject("drop.avi", this);
    VideoObject* video2 = new VideoObject("Sample.mp4", this);

    // видеоОбъекты по потокам
    video1->moveToThread(thread1);
    video2->moveToThread(thread2);

    // по запуску потока начинает выполняться process()
    connect(thread1, SIGNAL(started()), video1, SLOT(process()));
    connect(thread2, SIGNAL(started()), video2, SLOT(process()));

    // по окончании видео завершается работа потока
    connect(video1, SIGNAL(finished()), thread1, SLOT(quit()));
    connect(video2, SIGNAL(finished()), thread2, SLOT(quit()));


    thread1->start();
    thread2->start();


}


PiP::~PiP()
{
    delete ui;
}


void PiP::getNewFrame(cv::Mat frame){
    qDebug() << "I display frame " << frame.data;

    QImage img= QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    QPixmap pix = QPixmap::fromImage(img);

    ui->label->setPixmap(pix);
}


