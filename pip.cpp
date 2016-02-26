#include "pip.h"
#include "ui_pip.h"
#include "videothread.h"

/* объект основного класса PiP
 * создает виджет
 * запускает два потока для различных видео
 * получает от разных потоков в разное(?) время разные картинки
 * формирует результирующее изображение
 * отображает его в виджете
 */

PiP::PiP(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PiP)
{
    ui->setupUi(this);          // создаем виджет с label
    VideoThread vthread("drop.avi");   // создаем поток, который откроет видео "drop.avi"



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

// --- !!! --- изменить размер окошка под размер видео
// ui->label->resize(capture.get(CV_CAP_PROP_FRAME_HEIGHT), capture.get(CV_CAP_PROP_FRAME_WIDTH));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(displayFrame()));      // connect the timer to the widget and to the method
    timer->start(int(1000 / fps));
*/
