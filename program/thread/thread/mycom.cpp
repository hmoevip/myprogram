#include "mycom.h"
#include <QtCore>
#include <QDebug>

MyCom::MyCom()
{
   // struct PortSettings myComSetting = {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
    //定义一个结构体，用来存放串口各个参数
    myCom = new Posix_QextSerialPort("com1",QextSerialBase::EventDriven);
    //定义串口对象，并传递参数，在构造函数里对其进行初始化
    myCom ->open(QIODevice::ReadWrite);
    //以可读写方式打开串口
    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
    //信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作

}

void MyCom::run()
{
    qDebug()<<"running"<<endl;
}

void MyCom::readMyCom()
{
    QByteArray temp = myCom->readAll();
    //读取串口缓冲区的所有数据给临时变量temp
}
