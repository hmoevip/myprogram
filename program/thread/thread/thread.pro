QT += core
QT -= gui

TARGET = thread
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mycom.cpp \
    posix_qextserialport.cpp \
    qextserialbase.cpp \
    qextserialport.cpp

HEADERS += \
    mycom.h \
    posix_qextserialport.h \
    qextserialbase.h \
    qextserialport.h

