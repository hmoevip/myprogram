#include "form.h"
#include "ui_form.h"
#include "qcustomplot.h"
#include <QTime>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    x.clear();
    y.clear();
    thread = new QThread();
    task = new MyThread();
    task->DoSetup(*thread);
    task->moveToThread(thread);
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(stop()));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(goon()));
 //   connect(task, SIGNAL(draw(int,double)), this, SLOT(draw(int,double)));
    draw();

}

Form::~Form()
{
    delete ui;
}

void Form::stop()
{
    task->iswait = true;
}

void Form::goon()
{
    task->iswait = false;
}

void Form::draw()
{
   /* QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);*/
    ui->widget->addGraph(); // blue line
    ui->widget->graph(0)->setPen(QPen(Qt::blue));
    ui->widget->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    ui->widget->graph(0)->setAntialiasedFill(false);
 //   customPlot->addGraph(); // red line
 //   customPlot->graph(1)->setPen(QPen(Qt::red));
 //   customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));

 //   ui->widget->addGraph(); // blue dot
 //   ui->widget->graph(2)->setPen(QPen(Qt::blue));
 //   ui->widget->graph(2)->setLineStyle(QCPGraph::lsNone);
 //   ui->widget->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
//    customPlot->addGraph(); // red dot
//    customPlot->graph(3)->setPen(QPen(Qt::red));
//    customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
//    customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->widget->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->widget->xAxis->setDateTimeFormat("mm:ss");
    ui->widget->xAxis->setAutoTickStep(false);
    ui->widget->xAxis->setTickStep(0.5);
    ui->widget->axisRect()->setupFullAxesBox();
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(task, SIGNAL(draw(int,double)), this, SLOT(realtimeDataSlot(int,double)));
    thread->start();


/*
    ui->widget->addGraph();
    ui->widget->graph()->setPen(QPen(Qt::blue));
    //ui->widget->graph()->setBrush(QBrush(QColor(0, 0, 255, 20)));
    //ui->plot->addGraph();
    //ui->plot->graph()->setPen(QPen(Qt::red));
    x.push_back(num*0.2);

    y.push_back(ynum);

    ui->widget->graph(0)->setData(x, y);
    if(num*0.2<10)
        ui->widget->xAxis->setRange(0,10);
    else
        ui->widget->xAxis->setRange(0, num*0.2);
    ui->widget->yAxis->setRange(-100, 100);
    ui->widget->xAxis->setLabel("时间t，单位s");
    ui->widget->yAxis->setLabel("速度v，单位脉冲／s");
    ui->widget->axisRect()->setupFullAxesBox(true);
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->widget->replot();
    num++;*/
}

void Form::realtimeDataSlot(int num, double value0)
{
  // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  double key = 0;
#else
  double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif
  static double lastPointKey = 0;
  if (key-lastPointKey > 0.01) // at most add point every 10 ms
  {
    //double value0 = qSin(key); //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
    //double value1 = qCos(key); //qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
    // add data to lines:
    ui->widget->graph(0)->addData(key, value0);
   // ui->customPlot->graph(1)->addData(key, value1);
    // set data of dots:
 //   ui->widget->graph(2)->clearData();
 //   ui->widget->graph(2)->addData(key, value0);
 //   ui->customPlot->graph(3)->clearData();
 //   ui->customPlot->graph(3)->addData(key, value1);
    // remove data of lines that's outside visible range:
    ui->widget->graph(0)->removeDataBefore(key-8);
//    ui->customPlot->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->widget->graph(0)->rescaleValueAxis();
 //   ui->customPlot->graph(1)->rescaleValueAxis(true);
    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->widget->xAxis->setRange(key, 1, Qt::AlignRight);
  ui->widget->replot();

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
 /*   ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(ui->widget->graph(0)->data()->count()+ui->widget->graph(1)->data()->count())
          , 0);*/
    lastFpsKey = key;
    frameCount = 0;
  }
}
