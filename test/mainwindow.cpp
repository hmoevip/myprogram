#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "carve.h"
#define Amount 100

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showspeed = true;
    setupPlot(ui->plot1,0);
    setupPlot(ui->plot2,1);
    setupPlot(ui->plot3,2);
    setupPlot(ui->plot4,3);
    setupPlot(ui->plot5,4);
    setupPlot(ui->plot6,5);
    setupPlot(ui->plot7,6);
    setupPlot(ui->plot8,7);

    // configure scroll bars:
    // Since scroll bars only support integer values, we'll set a high default range of -500..500 and
    // divide scroll bar position values by 100 to provide a scroll range -5..5 in floating point
    // axis coordinates. if you want to dynamically grow the range accessible with the scroll bar,
    // just increase the the minimum/maximum values of the scroll bars as needed.
   // ui->horizontalScrollBar->setRange(0, 10000);
   // ui->verticalScrollBar->setRange(400, 500);

    // create connection between axes and scroll bars:
  //  connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
  //  connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)));
  //  connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
  //  connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));
    connect(ui->actionSpeed, SIGNAL(triggered()), this, SLOT(changeshow1()));
    connect(ui->actionPosition, SIGNAL(triggered()), this, SLOT(changeshow2()));
    // initialize axis range (and scroll bar positions via signals we just connected):
    //ui->plot->xAxis->setRange(0, 6, Qt::AlignCenter);
   // ui->plot->yAxis->setRange(0, 10, Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeshow1()
{
    showspeed = true;
    setupPlot(ui->plot1,0);
    //ui->plot1->replot();
    setupPlot(ui->plot2,1);
    setupPlot(ui->plot3,2);
    setupPlot(ui->plot4,3);
    setupPlot(ui->plot5,4);
    setupPlot(ui->plot6,5);
    setupPlot(ui->plot7,6);
    setupPlot(ui->plot8,7);
}

void MainWindow::changeshow2()
{
    showspeed = false;
    setupPlot(ui->plot1,0);
    //ui->plot1->replot();
    setupPlot(ui->plot2,1);
    setupPlot(ui->plot3,2);
    setupPlot(ui->plot4,3);
    setupPlot(ui->plot5,4);
    setupPlot(ui->plot6,5);
    setupPlot(ui->plot7,6);
    setupPlot(ui->plot8,7);
}

void MainWindow::setupPlot(QCustomPlot *customPlot, int i)
{
  // The following plot setup is mostly taken from the plot demos:
  customPlot->addGraph();
  customPlot->graph()->setPen(QPen(Qt::blue));
  customPlot->graph()->setBrush(QBrush(QColor(0, 0, 255, 20)));
  //ui->plot->addGraph();
  //ui->plot->graph()->setPen(QPen(Qt::red));

  QVector<double> time(Amount);
  QVector< QVector<double> > pos(8,QVector<double>(Amount,0));
  QVector< QVector<double> > vel(8,QVector<double>(Amount,0));
      //double vel[8][Amount];
  double vmax;
  vmax = 100.0;
      //XY缓存，系数矩阵缓存
  Mplace ori(0,0,10),tar(0,0,12);
      //Carve *m_carve;
      //m_carve->qube(0,ori,tar,0,0,10,Amount,(double **)ParaK,6);
  Carve mm(0,ori,tar,0,0,vmax,Amount,pos,vel,time,6);
  for(int j=0;j<Amount;++j)
      time[j] *= 20000;
  for(int i=0;i<8;++i)
  {
      double temp = pos[i][0];
      for(int j=0;j<Amount;++j)
      {
          pos[i][j] = (pos[i][j] - temp) * 20000;
          vel[i][j] = abs(vel[i][j]);
      }
  }
  if(showspeed)
  {
      customPlot->graph(0)->setData(time, vel[i]);
      customPlot->xAxis->setRange(time[0], time[Amount-1]);
      customPlot->yAxis->setRange(vel[i][0], vmax);
      customPlot->xAxis->setLabel("时间t，单位s");
      customPlot->yAxis->setLabel("速度v，单位脉冲／s");
  }else
  {
      customPlot->graph(0)->setData(time, pos[i]);
      customPlot->xAxis->setRange(time[0], time[Amount-1]);
      customPlot->yAxis->setRange(pos[i][0], pos[i][Amount-1]);
      customPlot->xAxis->setLabel("时间t，单位s");
      customPlot->yAxis->setLabel("位移s，单位脉冲");
  }
  customPlot->axisRect()->setupFullAxesBox(true);
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  customPlot->replot();
}
