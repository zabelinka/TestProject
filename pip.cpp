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

    VideoObject* video1 = new VideoObject("drop.avi");
    VideoObject* video2 = new VideoObject("Sample.mp4");

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






/*
 * открытие видеоФайла, чтение его fps, присоединение его к таймеру и функции
 *
    capture.open("drop.avi");   //open video
    int fps = capture.get(CV_CAP_PROP_FPS);         // frame per second



    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(displayFrame()));      // connect the timer to the widget and to the method
    timer->start(int(1000 / fps));
*/
