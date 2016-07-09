/********************************************************************************
** Form generated from reading UI file 'm_move.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_M_MOVE_H
#define UI_M_MOVE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *rightrotate;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *leftup;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *leftArrow;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *leftdown;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_6;
    QPushButton *upArrow;
    QSpacerItem *verticalSpacer;
    QPushButton *downArrow;
    QSpacerItem *verticalSpacer_7;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *rightup;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *rightArrow;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *rightdown;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *leftrotate;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(683, 475);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(100, 100));
        MainWindow->setStyleSheet(QString::fromUtf8("border-image: url(:/mres/img/background.png);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 20, 641, 392));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        rightrotate = new QPushButton(widget);
        rightrotate->setObjectName(QString::fromUtf8("rightrotate"));
        sizePolicy.setHeightForWidth(rightrotate->sizePolicy().hasHeightForWidth());
        rightrotate->setSizePolicy(sizePolicy);
        rightrotate->setMinimumSize(QSize(100, 100));
        rightrotate->setStyleSheet(QString::fromUtf8("border-image:url(:/mres/img/ron_rotate.png);\n"
"border-image: url(:/mres/img/right_rotate.png);\n"
"border-image: url(:/mres/img/rpress_rotate.png);\n"
""));

        horizontalLayout->addWidget(rightrotate);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        leftup = new QPushButton(widget);
        leftup->setObjectName(QString::fromUtf8("leftup"));
        sizePolicy.setHeightForWidth(leftup->sizePolicy().hasHeightForWidth());
        leftup->setSizePolicy(sizePolicy);
        leftup->setMinimumSize(QSize(100, 100));
        leftup->setStyleSheet(QString::fromUtf8("border-image: url(:/mres/img/luon.png);\n"
"border-image: url(:/mres/img/leftup.png);\n"
"border-image: url(:/mres/img/lupress.png);\n"
""));
        leftup->setShortcut(QString::fromUtf8(""));
        leftup->setAutoDefault(false);
        leftup->setDefault(false);
        leftup->setFlat(false);

        horizontalLayout_2->addWidget(leftup);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        leftArrow = new QPushButton(widget);
        leftArrow->setObjectName(QString::fromUtf8("leftArrow"));
        sizePolicy.setHeightForWidth(leftArrow->sizePolicy().hasHeightForWidth());
        leftArrow->setSizePolicy(sizePolicy);
        leftArrow->setMinimumSize(QSize(100, 100));
        leftArrow->setSizeIncrement(QSize(100, 100));
        leftArrow->setBaseSize(QSize(100, 100));
        leftArrow->setStyleSheet(QString::fromUtf8("border-image: url(:/mres/img/lon.png);\n"
"border-image: url(:/mres/img/left.png);\n"
"border-image: url(:/mres/img/lpress.png);\n"
""));
        leftArrow->setIconSize(QSize(100, 100));

        horizontalLayout_3->addWidget(leftArrow);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        leftdown = new QPushButton(widget);
        leftdown->setObjectName(QString::fromUtf8("leftdown"));
        sizePolicy.setHeightForWidth(leftdown->sizePolicy().hasHeightForWidth());
        leftdown->setSizePolicy(sizePolicy);
        leftdown->setMinimumSize(QSize(100, 100));
        leftdown->setStyleSheet(QString::fromUtf8("border-image:url(:/mres/img/ldon.png);\n"
"border-image: url(:/mres/img/leftdown.png);\n"
"border-image: url(:/mres/img/ldpress.png);\n"
""));

        horizontalLayout_4->addWidget(leftdown);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        upArrow = new QPushButton(widget);
        upArrow->setObjectName(QString::fromUtf8("upArrow"));
        sizePolicy.setHeightForWidth(upArrow->sizePolicy().hasHeightForWidth());
        upArrow->setSizePolicy(sizePolicy);
        upArrow->setMinimumSize(QSize(100, 100));
        upArrow->setContextMenuPolicy(Qt::DefaultContextMenu);
        upArrow->setStyleSheet(QString::fromUtf8("border-image: url(:/mres/img/uon.png);\n"
"border-image: url(:/mres/img/up.png);\n"
"border-image: url(:/mres/img/upress.png);\n"
""));
        upArrow->setIconSize(QSize(48, 48));
        upArrow->setShortcut(QString::fromUtf8(""));
        upArrow->setAutoRepeat(true);
        upArrow->setAutoRepeatInterval(99);
        upArrow->setAutoDefault(true);
        upArrow->setDefault(true);
        upArrow->setFlat(true);

        verticalLayout->addWidget(upArrow);

        verticalSpacer = new QSpacerItem(20, 80, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        downArrow = new QPushButton(widget);
        downArrow->setObjectName(QString::fromUtf8("downArrow"));
        downArrow->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(100);
        sizePolicy1.setVerticalStretch(100);
        sizePolicy1.setHeightForWidth(downArrow->sizePolicy().hasHeightForWidth());
        downArrow->setSizePolicy(sizePolicy1);
        downArrow->setMinimumSize(QSize(100, 100));
        downArrow->setStyleSheet(QString::fromUtf8("border-image:url(:/mres/img/don.png);\n"
"border-image: url(:/mres/img/down.png);\n"
"border-image: url(:/mres/img/dpress.png);\n"
""));
        downArrow->setIconSize(QSize(100, 100));

        verticalLayout->addWidget(downArrow);

        verticalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_7);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        rightup = new QPushButton(widget);
        rightup->setObjectName(QString::fromUtf8("rightup"));
        sizePolicy.setHeightForWidth(rightup->sizePolicy().hasHeightForWidth());
        rightup->setSizePolicy(sizePolicy);
        rightup->setMinimumSize(QSize(100, 100));
        rightup->setStyleSheet(QString::fromUtf8("border-image: url(:/mres/img/ruon.png);\n"
"border-image: url(:/mres/img/rightup.png);\n"
"border-image: url(:/mres/img/rupress.png);\n"
""));

        horizontalLayout_5->addWidget(rightup);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        rightArrow = new QPushButton(widget);
        rightArrow->setObjectName(QString::fromUtf8("rightArrow"));
        sizePolicy.setHeightForWidth(rightArrow->sizePolicy().hasHeightForWidth());
        rightArrow->setSizePolicy(sizePolicy);
        rightArrow->setMinimumSize(QSize(100, 100));
        rightArrow->setStyleSheet(QString::fromUtf8("border-image:url(:/mres/img/ron.png);\n"
"border-image: url(:/mres/img/right.png);\n"
"border-image: url(:/mres/img/rpress.png);\n"
""));

        horizontalLayout_6->addWidget(rightArrow);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);


        verticalLayout_3->addLayout(horizontalLayout_6);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);

        rightdown = new QPushButton(widget);
        rightdown->setObjectName(QString::fromUtf8("rightdown"));
        sizePolicy.setHeightForWidth(rightdown->sizePolicy().hasHeightForWidth());
        rightdown->setSizePolicy(sizePolicy);
        rightdown->setMinimumSize(QSize(100, 100));
        rightdown->setStyleSheet(QString::fromUtf8("border-image:url(:/mres/img/rdon.png);\n"
"border-image: url(:/mres/img/rightdown.png);\n"
"border-image: url(:/mres/img/rdpress.png);\n"
""));

        horizontalLayout_7->addWidget(rightdown);


        verticalLayout_3->addLayout(horizontalLayout_7);


        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        leftrotate = new QPushButton(widget);
        leftrotate->setObjectName(QString::fromUtf8("leftrotate"));
        sizePolicy.setHeightForWidth(leftrotate->sizePolicy().hasHeightForWidth());
        leftrotate->setSizePolicy(sizePolicy);
        leftrotate->setMinimumSize(QSize(100, 100));
        leftrotate->setStyleSheet(QString::fromUtf8("border-image:url(:/mres/img/lon_rotate.png);\n"
"border-image: url(:/mres/img/left_rotate.png);\n"
"border-image: url(:/mres/img/lpress_rotate.png);\n"
""));

        horizontalLayout->addWidget(leftrotate);

        MainWindow->setCentralWidget(centralwidget);
        upArrow->raise();
        leftArrow->raise();
        rightArrow->raise();
        downArrow->raise();
        rightup->raise();
        leftdown->raise();
        rightdown->raise();
        leftup->raise();
        leftup->raise();
        leftArrow->raise();
        leftdown->raise();
        rightup->raise();
        rightArrow->raise();
        rightdown->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 683, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        rightrotate->setText(QString());
        leftup->setText(QString());
        leftArrow->setText(QString());
        leftdown->setText(QString());
        upArrow->setText(QString());
        downArrow->setText(QString());
        rightup->setText(QString());
        rightArrow->setText(QString());
        rightdown->setText(QString());
        leftrotate->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_M_MOVE_H
