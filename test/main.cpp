//#include "stdafx.h"
#include <QtGui>
#include <QApplication>
#include "mainwindow.h"
#include "form.h"
/***********************************************************************************
测试main函数
数据组数：20
阶数：5
***********************************************************************************/
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");

    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    MainWindow w;
    w.show();

    Form kk;
    kk.show();
    a.exec();
}
