#! [0]
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = arrowpad
TEMPLATE = app

HEADERS      = arrowpad.h \
               mainwindow.h
SOURCES      = arrowpad.cpp \
               main.cpp \
               mainwindow.cpp
#! [0] #! [1]
#TRANSLATIONS = arrowpad_fr.ts \
 #              arrowpad_nl.ts
#! [1]

FORMS    += m_move.ui
# install
target.path = $$[QT_INSTALL_EXAMPLES]/linguist/arrowpad
sources.files = $$SOURCES $$HEADERS *.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/linguist/arrowpad
INSTALLS += target sources

symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
maemo5: include($$QT_SOURCE_TREE/examples/maemo5pkgrules.pri)

symbian: warning(This example might not fully work on Symbian platform)
maemo5: warning(This example might not fully work on Maemo platform)
simulator: warning(This example might not fully work on Simulator platform)

RESOURCES += m_res.qrc
