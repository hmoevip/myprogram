#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QObject>
#include <QDateTime>
#define AXSI   4
class MyThread: public QObject
{
    Q_OBJECT
public:
    MyThread(QObject *parent=0);
    void DoSetup(QThread &thread);
    bool iswait;
signals:
    void draw(int num,double ynum);
public slots:
    void DoWork();
private:
    void sleep(int msec);
};

#endif // MYTHREAD_H
