#include "mainwindow.h"
#include <QStatusBar>
#include <QLabel>
#include "translate.h"
#include "extend.h"
#include "roll.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    glWidget = new GLWidget();
    fullscreen = true;
    odialog = new OriginalDialog();
    odialog->show();
    odialog->accept();
    setGeometry(100,100,800,600);
    setWindowTitle(tr("Common View Framework"));
    setCentralWidget(glWidget);
    createActions();
    createMenus();
    QLabel *rototionangle = new QLabel( tr("Rotation Angle") );
    rototionangle->setMinimumSize( rototionangle->sizeHint() );
    QStatusBar *statusBar = this->statusBar();
    statusBar->addWidget( rototionangle );
    statusBar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    connect(glWidget, SIGNAL(RotationChangedText(QString)), rototionangle,
		    SLOT(setText(QString)));
    connect(this,SIGNAL(SetTransParameter(float *)),glWidget,SLOT(GetTransParameter(float *)));
    connect(this,SIGNAL(SetExtendParameter(float *)),glWidget,SLOT(GetExtendParameter(float *)));
    connect(this,SIGNAL(SetRollParameter(float *)),glWidget,SLOT(GetRollParameter(float *)));

    connect(this,SIGNAL(SetTransParameter(float *)),odialog,SLOT(TrTransParameter(float *)));
    connect(this,SIGNAL(SetExtendParameter(float *)),odialog,SLOT(TrExtendParameter(float *)));
    connect(this,SIGNAL(SetRollParameter(float *)),odialog,SLOT(TrRollParameter(float *)));

    connect(glWidget,SIGNAL(RecordParameter(float *)),this,SLOT(ResetTranslate(float *)));
    flag_t = false;
    para_e[0] = 1;
    para_e[1] = 0;
    para_e[2] = 1;
    para_e[3] = 0.1;
    para_e[4] = 0;
    para_r[0] = 1;
    para_r[1] = 0;
    para_r[2] = 1;
    para_r[3] = 0.1;
    para_r[4] = 0;
    para_r[5] = 0;
    para_r[6] = 0;

}
MainWindow::~MainWindow()
{

}
void MainWindow::closeEvent(QCloseEvent *e)
{
	if(odialog)
	{
		odialog->accept();
	}
}
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch ( e->key() )
      {
      case Qt::Key_F2:
        fullscreen = !fullscreen;
        if ( fullscreen )
        {
          showFullScreen();
        }
        else
        {
          showNormal();
        }
      glWidget->updateGL();
        break;
      case Qt::Key_Escape:
       close();
        break;
     }
}
void MainWindow::createActions()
{
	Translate = new QAction(tr("&Translate"), this);
	Translate->setShortcut(tr("Ctrl+T"));
	Translate->setStatusTip(tr("Set the parameter of transformation"));
	connect(Translate, SIGNAL(triggered()), this, SLOT(TranslateSettings()));
	Extend = new QAction(tr("&Extend"),this);
	Extend->setShortcut(tr("Ctrl+E"));
	Extend->setStatusTip(tr("Set the parameter of extending"));
	connect(Extend,SIGNAL(triggered()),this,SLOT(ExtendSettings()));
	Roll = new QAction(tr("&Roll"),this);
	Roll->setShortcut(tr("Ctrl+R"));
	Roll->setStatusTip(tr("Set the patameter of rolling"));
	connect(Roll,SIGNAL(triggered()),this,SLOT(RollSettings()));
	Original = new QAction(tr("&Original"),this);
	Original->setShortcut(tr("Ctrl+O"));
	Original->setStatusTip(tr("Show the orignal shap"));
	connect(Original,SIGNAL(triggered()),this,SLOT(OriginalSettings()));
}
void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&Operate"));
	fileMenu->addAction(Translate);
	fileMenu->addAction(Extend);
	fileMenu->addAction(Roll);
	fileMenu->addAction(Original);
	fileMenu->setStatusTip(tr("Operations"));
}

void MainWindow::OriginalSettings()
{
	if(!odialog)
	{
		odialog = new OriginalDialog(this);
	}
	odialog->show();
//	odialog->raise();
//	odialog->activateWindow();
}

void MainWindow::RollSettings()
{
	RollDialog dialog(this);
	    dialog.doubleSpinBox->setValue(para_r[0]);
    	    dialog.doubleSpinBox_2->setValue(para_r[1]);
    	    dialog.doubleSpinBox_3->setValue(para_r[2]);
    	    dialog.doubleSpinBox_4->setValue(para_r[3]);
    	    dialog.doubleSpinBox_5->setValue(para_r[4]);
	    dialog.doubleSpinBox_6->setValue(para_r[5]);
    	    dialog.doubleSpinBox_7->setValue(para_r[6]);
    if (dialog.exec()) {
	    para_r[0] = dialog.doubleSpinBox->value();
	    para_r[1] = dialog.doubleSpinBox_2->value();
	    para_r[2] = dialog.doubleSpinBox_3->value();
	    para_r[3] = dialog.doubleSpinBox_4->value();
	    para_r[4] = dialog.doubleSpinBox_5->value();
	    para_r[5] = dialog.doubleSpinBox_6->value();
	    para_r[6] = dialog.doubleSpinBox_7->value();
	    emit SetRollParameter(para_r); 
    }
}
void MainWindow::TranslateSettings()
{
    TranslateDialog dialog(this);
    if(flag_t)
    {
    	dialog.doubleSpinBox->setValue(para_t[0]);
    	dialog.doubleSpinBox_2->setValue(para_t[1]);
    	dialog.doubleSpinBox_3->setValue(para_t[2]);
    	dialog.doubleSpinBox_4->setValue(para_t[3]);
    	dialog.doubleSpinBox_5->setValue(para_t[4]);
    	dialog.doubleSpinBox_6->setValue(para_t[5]);
    }
    if (dialog.exec()) {
	   float para[6];
	    para[0] = dialog.doubleSpinBox->value();
	    para[1] = dialog.doubleSpinBox_2->value();
	    para[2] = dialog.doubleSpinBox_3->value();
	    para[3] = dialog.doubleSpinBox_4->value();
	    para[4] = dialog.doubleSpinBox_5->value();
	    para[5] = dialog.doubleSpinBox_6->value();
	    emit SetTransParameter(para); 
    }
}

void MainWindow::ExtendSettings()
{
    ExtendDialog dialog(this);    
	    dialog.doubleSpinBox->setValue(para_e[0]);
    	    dialog.doubleSpinBox_2->setValue(para_e[1]);
    	    dialog.doubleSpinBox_3->setValue(para_e[2]);
    	    dialog.doubleSpinBox_4->setValue(para_e[3]);
    	    dialog.doubleSpinBox_5->setValue(para_e[4]);
    if (dialog.exec()) {
	    para_e[0] = dialog.doubleSpinBox->value();
	    para_e[1] = dialog.doubleSpinBox_2->value();
	    para_e[2] = dialog.doubleSpinBox_3->value();
	    para_e[3] = dialog.doubleSpinBox_4->value();
	    para_e[4] = dialog.doubleSpinBox_5->value();
	    emit SetExtendParameter(para_e); 
    }
}

void MainWindow::ResetTranslate(float *para)
{
	flag_t = true;
	for(int i=0;i<6;i++)
	{
		para_t[i]=para[i];
	}
}


