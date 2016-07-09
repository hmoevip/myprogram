#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionOpen->setShortcut(tr("Ctrl+P"));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(OpenFile()));
    OpenFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::OpenFile()
{
/*    QString filename = QFileDialog::getOpenFileName(0, "Open File", "", "*.jpg *.png *.bmp", 0);
    if (filename.isNull()) {
        return -1;
    }*/
    QString filename = "/Users/admin/myprogram/hell/Cam1_075608.bmp";
    moriginal = imread(filename.toAscii().data(), 1);
    //mPgs();
    mColorRect();
    return 0;
}
void MainWindow::mColorRect()
{
    Mat mgrey,mc,img_trans,qq,mthr;
    MProcess mp;
    int a[3]={150,150,250};
    mp.chooseBlue(moriginal,mc,a);
    qq = mp.findRect(moriginal,mc,img_trans);
    cvtColor(img_trans,mgrey, CV_BGR2GRAY);
    mgrey = mp.selectColor(img_trans);
//    mgrey = mp.drawHist(mgrey);
    mDraw(img_trans);
}
void MainWindow::mPgs()
{
    MProcess mp;
    Mat mblue;
    Mat img_trans,qq;
    //int a[3]={190,150,150};
    int a[3]={0,150,70};
    mp.chooseBlue(moriginal,mblue,a);
    qq = mp.findRect(moriginal,mblue,img_trans);

    Mat mc,mgrey;
    cvtColor(img_trans,mgrey, CV_BGR2GRAY);
    Canny(mgrey,mc,50,150,3);
    mc = mp.detectLine(mc);
    mDraw(mc);
}

void MainWindow::mDraw(Mat mimage)
{
    //绘制
    QImage image = Mat_Qimage::cvMat2QImage(mimage);
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(scene);
    //ui->graphicsView->resize(image.width() + 10, image.height() + 10);
    ui->graphicsView->show();
}
