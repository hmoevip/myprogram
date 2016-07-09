#include <QCoreApplication>
#include <QThread>
#include<QDebug>
#include "mycom.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyCom myThread;
    myThread.start();
   // QThread::sleep(10);
   // myThread.stop=true;
    return a.exec();
}
