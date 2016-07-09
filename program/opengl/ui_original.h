/********************************************************************************
** Form generated from reading ui file 'original.ui'
**
** Created: Fri Apr 3 14:30:54 2015
**      by: Qt User Interface Compiler version 4.2.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ORIGINAL_H
#define UI_ORIGINAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QMainWindow>
#include <QtGui/QWidget>

class Ui_OriginalWindow
{
public:
    QWidget *centralwidget;

    void setupUi(QMainWindow *OriginalWindow)
    {
    OriginalWindow->setObjectName(QString::fromUtf8("OriginalWindow"));
    centralwidget = new QWidget(OriginalWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    OriginalWindow->setCentralWidget(centralwidget);

    retranslateUi(OriginalWindow);

    QSize size(590, 428);
    size = size.expandedTo(OriginalWindow->minimumSizeHint());
    OriginalWindow->resize(size);


    QMetaObject::connectSlotsByName(OriginalWindow);
    } // setupUi

    void retranslateUi(QMainWindow *OriginalWindow)
    {
    OriginalWindow->setWindowTitle(QApplication::translate("OriginalWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(OriginalWindow);
    } // retranslateUi

};

namespace Ui {
    class OriginalWindow: public Ui_OriginalWindow {};
} // namespace Ui

#endif // UI_ORIGINAL_H
