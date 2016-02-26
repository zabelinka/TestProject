#ifndef PIP_H
#define PIP_H

#include <QMainWindow>
#include <QtCore>

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

private:
    Ui::PiP *ui;

};

#endif // PIP_H

