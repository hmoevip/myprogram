#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui/QMainWindow>
#include <QKeyEvent>
#include "glwidget.h"
#include "original.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    bool fullscreen;
    //处理键盘事件
    void keyPressEvent( QKeyEvent *e );
    void createMenus();
    void createActions();
    void closeEvent(QCloseEvent *e);
private slots:
    void TranslateSettings();
    void OriginalSettings();
    void RollSettings();
    void ExtendSettings();
    void ResetTranslate(float *para);
signals:
    void SetTransParameter(float *para);
    void SetExtendParameter(float *para);
    void SetRollParameter(float *para);
private:
    QMenu *fileMenu;
    QAction *Translate;
    QAction *Extend;
    QAction *Roll;
    QAction *Original;
    GLWidget *glWidget ;
    float para_t[6];
    float para_e[5];
    float para_r[7];
    bool flag_t;
    OriginalDialog *odialog;
};
#endif // MAINWINDOW_H

