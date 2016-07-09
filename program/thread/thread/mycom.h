#ifndef COM
#define COM

#define _TTY_POSIX_
#include <QtCore>
#include "posix_qextserialport.h"
class MyCom : public QThread
{
public:
    MyCom();
    void run();
private:
    Posix_QextSerialPort *myCom;
private slots:
    void readMyCom();
};

#endif // COM

