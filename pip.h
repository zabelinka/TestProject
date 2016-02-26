#ifndef PIP_H
#define PIP_H

#include <QMainWindow>
#include <QtCore>

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

