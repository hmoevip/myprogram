#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupPlot(QCustomPlot *customPlot, int i);

private slots:
  //  void horzScrollBarChanged(int value);
  //  void vertScrollBarChanged(int value);
  //  void xAxisChanged(QCPRange range);
  //  void yAxisChanged(QCPRange range);
    void changeshow1();
    void changeshow2();
private:
    Ui::MainWindow *ui;
    void setupQuadraticDemo(QCustomPlot *customPlot);
    bool showspeed;
};

#endif // MAINWINDOW_H
