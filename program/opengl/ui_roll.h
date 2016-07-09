/********************************************************************************
** Form generated from reading ui file 'roll.ui'
**
** Created: Thu Apr 2 18:37:30 2015
**      by: Qt User Interface Compiler version 4.2.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ROLL_H
#define UI_ROLL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_RollDialog
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_8;
    QHBoxLayout *hboxLayout1;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_2;
    QLabel *label_9;
    QHBoxLayout *hboxLayout2;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_3;
    QLabel *label_10;
    QHBoxLayout *hboxLayout3;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox_4;
    QLabel *label_11;
    QHBoxLayout *hboxLayout4;
    QLabel *label_5;
    QLabel *label_14;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout5;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox_5;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_6;
    QLabel *label_13;
    QDoubleSpinBox *doubleSpinBox_7;
    QHBoxLayout *hboxLayout6;
    QSpacerItem *spacerItem1;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *RollDialog)
    {
    RollDialog->setObjectName(QString::fromUtf8("RollDialog"));
    groupBox = new QGroupBox(RollDialog);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(10, 10, 301, 221));
    layoutWidget = new QWidget(groupBox);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(10, 20, 282, 192));
    vboxLayout = new QVBoxLayout(layoutWidget);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    label = new QLabel(layoutWidget);
    label->setObjectName(QString::fromUtf8("label"));

    hboxLayout->addWidget(label);

    doubleSpinBox = new QDoubleSpinBox(layoutWidget);
    doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
    doubleSpinBox->setMaximum(10);
    doubleSpinBox->setMinimum(1);
    doubleSpinBox->setValue(1);

    hboxLayout->addWidget(doubleSpinBox);

    label_8 = new QLabel(layoutWidget);
    label_8->setObjectName(QString::fromUtf8("label_8"));

    hboxLayout->addWidget(label_8);


    vboxLayout->addLayout(hboxLayout);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    label_2 = new QLabel(layoutWidget);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    hboxLayout1->addWidget(label_2);

    doubleSpinBox_2 = new QDoubleSpinBox(layoutWidget);
    doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));
    doubleSpinBox_2->setMaximum(10);
    doubleSpinBox_2->setMinimum(0);
    doubleSpinBox_2->setValue(0);

    hboxLayout1->addWidget(doubleSpinBox_2);

    label_9 = new QLabel(layoutWidget);
    label_9->setObjectName(QString::fromUtf8("label_9"));

    hboxLayout1->addWidget(label_9);


    vboxLayout->addLayout(hboxLayout1);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    label_3 = new QLabel(layoutWidget);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    hboxLayout2->addWidget(label_3);

    doubleSpinBox_3 = new QDoubleSpinBox(layoutWidget);
    doubleSpinBox_3->setObjectName(QString::fromUtf8("doubleSpinBox_3"));
    doubleSpinBox_3->setMaximum(10);
    doubleSpinBox_3->setMinimum(1);
    doubleSpinBox_3->setValue(1);

    hboxLayout2->addWidget(doubleSpinBox_3);

    label_10 = new QLabel(layoutWidget);
    label_10->setObjectName(QString::fromUtf8("label_10"));

    hboxLayout2->addWidget(label_10);


    vboxLayout->addLayout(hboxLayout2);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    label_4 = new QLabel(layoutWidget);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    hboxLayout3->addWidget(label_4);

    doubleSpinBox_4 = new QDoubleSpinBox(layoutWidget);
    doubleSpinBox_4->setObjectName(QString::fromUtf8("doubleSpinBox_4"));
    doubleSpinBox_4->setMaximum(1);
    doubleSpinBox_4->setMinimum(0.01);
    doubleSpinBox_4->setSingleStep(0.1);
    doubleSpinBox_4->setValue(0.1);

    hboxLayout3->addWidget(doubleSpinBox_4);

    label_11 = new QLabel(layoutWidget);
    label_11->setObjectName(QString::fromUtf8("label_11"));

    hboxLayout3->addWidget(label_11);


    vboxLayout->addLayout(hboxLayout3);

    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setMargin(0);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    label_5 = new QLabel(layoutWidget);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    hboxLayout4->addWidget(label_5);

    label_14 = new QLabel(layoutWidget);
    label_14->setObjectName(QString::fromUtf8("label_14"));

    hboxLayout4->addWidget(label_14);

    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout4->addItem(spacerItem);


    vboxLayout->addLayout(hboxLayout4);

    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setSpacing(6);
    hboxLayout5->setMargin(0);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    label_6 = new QLabel(layoutWidget);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    hboxLayout5->addWidget(label_6);

    doubleSpinBox_5 = new QDoubleSpinBox(layoutWidget);
    doubleSpinBox_5->setObjectName(QString::fromUtf8("doubleSpinBox_5"));
    doubleSpinBox_5->setMaximum(89.99);

    hboxLayout5->addWidget(doubleSpinBox_5);

    label_7 = new QLabel(layoutWidget);
    label_7->setObjectName(QString::fromUtf8("label_7"));

    hboxLayout5->addWidget(label_7);

    doubleSpinBox_6 = new QDoubleSpinBox(layoutWidget);
    doubleSpinBox_6->setObjectName(QString::fromUtf8("doubleSpinBox_6"));
    doubleSpinBox_6->setEnabled(false);
    doubleSpinBox_6->setMaximum(89.99);

    hboxLayout5->addWidget(doubleSpinBox_6);

    label_13 = new QLabel(layoutWidget);
    label_13->setObjectName(QString::fromUtf8("label_13"));

    hboxLayout5->addWidget(label_13);

    doubleSpinBox_7 = new QDoubleSpinBox(layoutWidget);
    doubleSpinBox_7->setObjectName(QString::fromUtf8("doubleSpinBox_7"));
    doubleSpinBox_7->setEnabled(false);
    doubleSpinBox_7->setMaximum(89.99);

    hboxLayout5->addWidget(doubleSpinBox_7);


    vboxLayout->addLayout(hboxLayout5);

    hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setSpacing(6);
    hboxLayout6->setMargin(0);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    spacerItem1 = new QSpacerItem(101, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout6->addItem(spacerItem1);

    okButton = new QPushButton(layoutWidget);
    okButton->setObjectName(QString::fromUtf8("okButton"));

    hboxLayout6->addWidget(okButton);

    cancelButton = new QPushButton(layoutWidget);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

    hboxLayout6->addWidget(cancelButton);


    vboxLayout->addLayout(hboxLayout6);


    retranslateUi(RollDialog);

    QSize size(320, 239);
    size = size.expandedTo(RollDialog->minimumSizeHint());
    RollDialog->resize(size);


    QMetaObject::connectSlotsByName(RollDialog);
    } // setupUi

    void retranslateUi(QDialog *RollDialog)
    {
    RollDialog->setWindowTitle(QApplication::translate("RollDialog", "Dylinder Setting", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("RollDialog", "Rolling parameter input", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("RollDialog", "The small circle radius ", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("RollDialog", "(1~10)", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("RollDialog", "The difference of radius", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("RollDialog", "(0~10)", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("RollDialog", "The height of cylinder  ", 0, QApplication::UnicodeUTF8));
    label_10->setText(QApplication::translate("RollDialog", "(1~10)", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("RollDialog", "The accuracy of segmentation", 0, QApplication::UnicodeUTF8));
    label_11->setText(QApplication::translate("RollDialog", "(0.01~1)", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("RollDialog", "The rotate angle", 0, QApplication::UnicodeUTF8));
    label_14->setText(QApplication::translate("RollDialog", "(0~90)", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("RollDialog", "X:", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("RollDialog", "Y:", 0, QApplication::UnicodeUTF8));
    label_13->setText(QApplication::translate("RollDialog", "Z:", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("RollDialog", "Ok", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("RollDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(RollDialog);
    } // retranslateUi

};

namespace Ui {
    class RollDialog: public Ui_RollDialog {};
} // namespace Ui

#endif // UI_ROLL_H
