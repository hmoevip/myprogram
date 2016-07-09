#include "mythread.h"
#include "gts.h"

MyThread::MyThread(QObject *parent) :
    QObject(parent)
{
    iswait = false;
    qsrand(time(NULL));
}

void MyThread::DoSetup(QThread &thread)
{
    connect(&thread, SIGNAL(started()), this, SLOT(DoWork()) );
}

void MyThread::DoWork()
{
    int i = 0;
    double pValue = 50;
    while(1)
    {
        pValue = (qrand()%100);
        int m = (qrand()%100);
        if(m%2 == 0)
            pValue = -pValue;
        //GT_GetEncPos(AXSI,&pValue,1,NULL);
        sleep(10);
        if(!iswait)
            emit draw(i,pValue);
        ++i;
    }
}

void MyThread::sleep(int msec)//自定义Qt延时函数,单位毫秒
{
    QDateTime last = QDateTime::currentDateTime();
    QDateTime now;
    while (1)
    {
        now = QDateTime::currentDateTime();
        if (last.msecsTo(now) >= msec)
        {
            break;
        }
    }
}
