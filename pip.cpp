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

    VideoObject* video1 = new VideoObject("Sample.mp4", this);
    VideoObject* video2 = new VideoObject("drop.avi", this);

    mainImageSize = video1->getSize();
    minorImageSize = video2->getSize();

    // изменяем размер окна и label по размеру главного видео
    this->resize(mainImageSize);
    ui->label->resize(mainImageSize);

    // создаем пустое финальное изображение по размеру главного видео
    finalImage = new QImage(mainImageSize.width(), mainImageSize.height(), QImage::Format_RGB888);

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


    qDebug() << frame.cols;

    QRgb color;
/*
    if(frame.cols == 256){

        QImage littleImage = QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        for(int x = 0; x < frame.cols; x++){
            for(int y = 0; y < frame.rows; y++){
                color = littleImage.pixel(x, y);
                finalImage.setPixel(x, y, color);
            }
        }
    }

    if(frame.cols == 1280){
        QImage littleImage = QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        for(int x = 256; x < frame.cols; x++){
            for(int y = 0; y < 240; y++){
                color = littleImage.pixel(x, y);
                finalImage.setPixel(x, y, color);
            }
        }
        for(int x = 0; x < 256; x++){
            for(int y = 240; y < frame.rows; y++){
                color = littleImage.pixel(x, y);
                finalImage.setPixel(x, y, color);
            }
        }
        for(int x = 256; x < frame.cols; x++){
            for(int y = 240; y < frame.rows; y++){
                color = littleImage.pixel(x, y);
                finalImage.setPixel(x, y, color);
            }
        }
    }
*/
    // QImage img= QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);


    //QPixmap pix = QPixmap::fromImage(img);
 //    QPixmap pix = QPixmap::fromImage(finalImage);

//   ui->label->setPixmap(pix);


}


