#include "pip.h"
#include <QApplication>




int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    // в основном потоке создаем объект главного класса,
        // который будет формировать результирующую картинку и отображать ее в виджете
    PiP w;
    w.show();



    return a.exec();
}
