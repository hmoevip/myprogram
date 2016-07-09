#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mat_qimage.h>
#include <mprocess.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Mat moriginal;
    void mDraw(Mat mimage);
    void mPgs();
    void mColorRect();
private slots:
    int OpenFile();
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
