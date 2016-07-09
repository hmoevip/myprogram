/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

//#include <QtGui>

//#include "arrowpad.h"
#include "mainwindow.h"
#include "ui_m_move.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setStyleSheet("MainWindow{border-image:url(:/mres/img/background.png);}");
    ui->upArrow->setStyleSheet("QPushButton{border-image: url(:/mres/img/up.png);}"
                                   "QPushButton:hover{border-image: url(:/mres/img/uon.png);}"
                                   "QPushButton:pressed{border-image: url(:/mres/img/upress.png);}");
    ui->downArrow->setStyleSheet("QPushButton{border-image: url(:/mres/img/down.png);}"
                                   "QPushButton:hover{border-image: url(:/mres/img/don.png);}"
                                   "QPushButton:pressed{border-image: url(:/mres/img/dpress.png);}");
    ui->leftArrow->setStyleSheet("QPushButton{border-image: url(:/mres/img/left.png);}"
                                   "QPushButton:hover{border-image: url(:/mres/img/lon.png);}"
                                   "QPushButton:pressed{border-image: url(:/mres/img/lpress.png);}");
    ui->rightArrow->setStyleSheet("QPushButton{border-image: url(:/mres/img/right.png);}"
                                   "QPushButton:hover{border-image: url(:/mres/img/ron.png);}"
                                   "QPushButton:pressed{border-image: url(:/mres/img/rpress.png);}");
    ui->leftup->setStyleSheet("QPushButton{border-image: url(:/mres/img/leftup.png);}"
                                   "QPushButton:hover{border-image: url(:/mres/img/luon.png);}"
                                   "QPushButton:pressed{border-image: url(:/mres/img/lupress.png);}");
    ui->rightup->setStyleSheet("QPushButton{border-image: url(:/mres/img/rightup.png);}"
                                   "QPushButton:hover{border-image: url(:/mres/img/ruon.png);}"
                                   "QPushButton:pressed{border-image: url(:/mres/img/rupress.png);}");
    ui->leftdown->setStyleSheet("QPushButton{border-image: url(:/mres/img/leftdown.png);}"
                                   "QPushButton:hover{border-image: url(:/mres/img/ldon.png);}"
                                   "QPushButton:pressed{border-image: url(:/mres/img/ldpress.png);}");
    ui->rightdown->setStyleSheet("QPushButton{border-image: url(:/mres/img/rightdown.png);}"
                                   "QPushButton:hover{border-image: url(:/mres/img/rdon.png);}"
                                   "QPushButton:pressed{border-image: url(:/mres/img/rdpress.png);}");
    ui->leftrotate->setStyleSheet("QPushButton{border-image: url(:/mres/img/left_rotate.png);}"
                                   "QPushButton:hover{border-image: url(:/mres/img/lon_rotate.png);}"
                                   "QPushButton:pressed{border-image: url(:/mres/img/lpress_rotate.png);}");
    ui->rightrotate->setStyleSheet("QPushButton{border-image: url(:/mres/img/right_rotate.png);}"
                                   "QPushButton:hover{border-image: url(:/mres/img/ron_rotate.png);}"
                                   "QPushButton:pressed{border-image: url(:/mres/img/rpress_rotate.png);}");

//! [0]
/*    arrowPad = new ArrowPad;
    i=0;
//! [0]
    setCentralWidget(arrowPad);
    connect(arrowPad->upButton, SIGNAL(pressed()), this, SLOT(mplus()));
    connect(arrowPad->upButton, SIGNAL(released()), this, SLOT(mmunes()));
//! [1]
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
//! [1]

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAct);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mplus()
{
    i++;
}

void MainWindow::mmunes()
{
    i--;
}
