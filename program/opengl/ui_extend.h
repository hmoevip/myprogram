/********************************************************************************
** Form generated from reading ui file 'extend.ui'
**
** Created: Thu Apr 2 18:31:53 2015
**      by: Qt User Interface Compiler version 4.2.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_EXTEND_H
#define UI_EXTEND_H

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

class Ui_ExtendDialog
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
    QDoubleSpinBox *doubleSpinBox_5;
    QLabel *label_14;
    QHBoxLayout *hboxLayout5;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *ExtendDialog)
    {
    ExtendDialog->setObjectName(QString::fromUtf8("ExtendDialog"));
    groupBox = new QGroupBox(ExtendDialog);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(10, 10, 301, 201));
    layoutWidget = new QWidget(groupBox);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(10, 22, 282, 164));
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

    doubleSpinBox_5 = new QDoubleSpinBox(layoutWidget);
    doubleSpinBox_5->setObjectName(QString::fromUtf8("doubleSpinBox_5"));
    doubleSpinBox_5->setMaximum(10);

    hboxLayout4->addWidget(doubleSpinBox_5);

    label_14 = new QLabel(layoutWidget);
    label_14->setObjectName(QString::fromUtf8("label_14"));

    hboxLayout4->addWidget(label_14);


    vboxLayout->addLayout(hboxLayout4);

    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setSpacing(6);
    hboxLayout5->setMargin(0);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    spacerItem = new QSpacerItem(101, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout5->addItem(spacerItem);

    okButton = new QPushButton(layoutWidget);
    okButton->setObjectName(QString::fromUtf8("okButton"));

    hboxLayout5->addWidget(okButton);

    cancelButton = new QPushButton(layoutWidget);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

    hboxLayout5->addWidget(cancelButton);


    vboxLayout->addLayout(hboxLayout5);


    retranslateUi(ExtendDialog);

    QSize size(320, 219);
    size = size.expandedTo(ExtendDialog->minimumSizeHint());
    ExtendDialog->resize(size);


    QMetaObject::connectSlotsByName(ExtendDialog);
    } // setupUi

    void retranslateUi(QDialog *ExtendDialog)
    {
    ExtendDialog->setWindowTitle(QApplication::translate("ExtendDialog", "Dylinder Setting", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("ExtendDialog", "Stretch parameter input", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("ExtendDialog", "The small circle radius ", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("ExtendDialog", "(1~10)", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("ExtendDialog", "The difference of radius", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("ExtendDialog", "(0~10)", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("ExtendDialog", "The height of cylinder  ", 0, QApplication::UnicodeUTF8));
    label_10->setText(QApplication::translate("ExtendDialog", "(1~10)", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("ExtendDialog", "The accuracy of segmentation", 0, QApplication::UnicodeUTF8));
    label_11->setText(QApplication::translate("ExtendDialog", "(0.01~1)", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("ExtendDialog", "The stretch height      ", 0, QApplication::UnicodeUTF8));
    label_14->setText(QApplication::translate("ExtendDialog", "(0~10)", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("ExtendDialog", "Ok", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("ExtendDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ExtendDialog);
    } // retranslateUi

};

namespace Ui {
    class ExtendDialog: public Ui_ExtendDialog {};
} // namespace Ui

#endif // UI_EXTEND_H
