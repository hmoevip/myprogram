#-------------------------------------------------
#
# Project created by QtCreator 2016-05-27T08:52:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hell
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mat_qimage.cpp \
    mprocess.cpp

HEADERS  += mainwindow.h \
    mat_qimage.h \
    mycvheader.h \
    mprocess.h

FORMS    += mainwindow.ui



#QT       -= gui
#CONFIG   += c++11
#CONFIG   -= app_bundle
#CONFIG -= qt
#CONFIG += libstdc++
#libc++ -lstdc++
#CONFIG += $(pkg-config --cflags --libs opencv)
# -stdlib=libc++
#-stdlib libc++
#TEMPLATE = app


#QMAKE_CXXFLAGS += -lstdc++
#CMAKE_CXXFLAGS += -std=c++11
#CXXFLAGS += -std=c++11
QMAKE_LFLAGS += `pkg-config opencv --cflags --libs`
#QMAKE_CXXFLAGS = $$QMAKE_CFLAGS
#QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
#SOURCES += main.cpp
#QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
INCLUDEPATH += /usr/local/include /usr/local/include/opencv /usr/local/include/opencv2

LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_calib3d -lopencv_highgui
