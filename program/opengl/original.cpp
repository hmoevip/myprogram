#include <QtGui>
#include "original.h"


OriginalDialog::OriginalDialog(QWidget *parent):QDialog(parent)
{
	setGeometry(900,100,400,400);
	setWindowTitle(tr("Original View"));
	
	//setupUi(this);
	//QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
	//lineEdit->setValidator(new QRegExpValidator(regExp,this));
	oview = new OView();
	QHBoxLayout *mainLayout = new QHBoxLayout;
    	mainLayout->addWidget(oview);
    	setLayout(mainLayout);
	connect(this,SIGNAL(SetTransParameter(float *)),oview,SLOT(GetTransParameter(float *)));
    	connect(this,SIGNAL(SetExtendParameter(float *)),oview,SLOT(GetExtendParameter(float *)));
    	connect(this,SIGNAL(SetRollParameter(float *)),oview,SLOT(GetRollParameter(float *)));
	//setCentralWidget(glWidget);
	//setAttribute(Qt::WA_DeleteOnClose);
}

void OriginalDialog::TrTransParameter(float *para)
{
    	emit SetTransParameter(para);
}
void OriginalDialog::TrExtendParameter(float *para)
{
	emit SetExtendParameter(para);
}
void OriginalDialog::TrRollParameter(float *para)
{
	emit SetRollParameter(para);
}


