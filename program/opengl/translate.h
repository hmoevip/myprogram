#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <QDialog>
#include "ui_translate.h"
class TranslateDialog:public QDialog,public Ui::TranslateDialog
{
	Q_OBJECT
	public:
		TranslateDialog(QWidget *parent=0);
		
};

#endif

