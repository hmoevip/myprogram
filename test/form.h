#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "mythread.h"
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
private slots:
    void stop();
    void goon();
    void realtimeDataSlot(int num, double value0);
private:
    Ui::Form *ui;
    QVector<double> x,y;
    QThread *thread;
    MyThread *task;
    void draw();
};

#endif // FORM_H
