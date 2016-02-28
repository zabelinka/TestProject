#ifndef PIP_H
#define PIP_H

#include <QMainWindow>
#include <QtCore>
#include <opencv2/opencv.hpp>

/* объект основного класса PiP
 * создает виджет
 * запускает два потока для различных видео
 * получает от разных потоков в разное(?) время разные картинки
 * формирует результирующее изображение
 * отображает его в виджете
 */

namespace Ui {
class PiP;
}

class PiP : public QMainWindow
{
    Q_OBJECT

public:
    explicit PiP(QWidget *parent = 0);
    ~PiP();
    void display();     // запускает дочерние потоки, отображает картинку

private:
    Ui::PiP *ui;
    QImage *finalImage;
    QSize mainImageSize;
    QSize minorImageSize;

public slots:
    void getNewFrame(cv::Mat);

};

#endif // PIP_H

