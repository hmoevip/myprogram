#ifndef ORIGINAL_H
#define ORIGINAL_H

#include <QDialog>
#include "oview.h"
//#include "ui_original.h"
class OriginalDialog : public QDialog
{
	Q_OBJECT
	public:
		OriginalDialog(QWidget *parent=0);
public slots:
	void TrTransParameter(float *para);
    	void TrExtendParameter(float *para);
    	void TrRollParameter(float *para);
signals:
    void SetTransParameter(float *para);
    void SetExtendParameter(float *para);
    void SetRollParameter(float *para);
	private:
		OView *oview ;	
};

#endif

