
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
CONFIG += c++11

TARGET = test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    reverseCalcu.cpp \
    qcustomplot.cpp \
    mainwindow.cpp \
    carve.cpp \
    form.cpp \
    mythread.cpp

HEADERS  += \
    reverseCalcu.h \
    fit.h \
    qcustomplot.h \
    mainwindow.h \
    carve.h \
    form.h \
    mythread.h \
    gts.h

FORMS += \
    mainwindow.ui \
    form.ui

#LIBS += -L/Users/admin/myprogram/test/ -lgts
