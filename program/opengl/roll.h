#ifndef ROLL_H
#define ROLL_H

#include <QDialog>
#include "ui_roll.h"
class RollDialog:public QDialog,public Ui::RollDialog
{
	Q_OBJECT
	public:
		RollDialog(QWidget *parent=0);
		
};

#endif

