#ifndef EXTEND_H
#define EXTEND_H

#include <QDialog>
#include "ui_extend.h"
class ExtendDialog:public QDialog,public Ui::ExtendDialog
{
	Q_OBJECT
	public:
		ExtendDialog(QWidget *parent=0);
		
};

#endif

