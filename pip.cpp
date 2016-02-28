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

    // создаем пустое финальное изображение по размеру главного видео + ширина маленького видео
    finalImage = new QImage(mainImageSize.width() + minorImageSize.width(), mainImageSize.height(), QImage::Format_RGB888);

    // изменяем размер окна и label по размеру главного видео
    this->resize(finalImage->size() );
    ui->label->resize(finalImage->size());

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
    delete finalImage;
}

void PiP::getNewFrame(cv::Mat frame){

    QImage* current = new QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    QRgb color;


    // если полученный кадр из ГЛАВНОГО изображения, то перерисовываем его часть
    if(current->width() == mainImageSize.width()){
        for(int x = 0; x < current->width(); x++){
            for(int y = 0; y < current->height(); y++){
                color = current->pixel(x, y);                                   // взять цвет у кадра
                finalImage->setPixel(x + minorImageSize.width(), y, color);     // закрасить этим цветом соответствующий пиксель
            }
        }
    }

    if(current->width() == minorImageSize.width()){
        for(int x = 0; x < current->width(); x++){
            for(int y = 0; y < current->height(); y++){
                color = current->pixel(x, y);                                   // взять цвет у кадра
                finalImage->setPixel(x, y, color);     // закрасить этим цветом соответствующий пиксель
            }
        }
    }


    // qDebug() << frame.cols;




    //QPixmap pix = QPixmap::fromImage(img);
    QPixmap pix = QPixmap::fromImage(*finalImage);
    ui->label->setPixmap(pix);

    delete current;

}


