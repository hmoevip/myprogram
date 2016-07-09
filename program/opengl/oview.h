#ifndef OVIEW_H
#define OVIEW_H

#include <QGLWidget>
#include <QtGui>
#include <QtOpenGL>

#include "morphing.h"

//! [0]

class OView : public QGLWidget
{
    Q_OBJECT

public:
    OView(QWidget *parent = 0);
    ~OView();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
//! [0]


//! [1]

public slots:
    void GetTransParameter(float *para);
    void GetExtendParameter(float *para);
    void GetRollParameter(float *para);

//! [1]


//! [2]

protected:
    //设置渲染环境
    void initializeGL();
    //绘制窗口
    void paintGL();
    //响应窗口的大小变化
    void resizeGL( int width, int height );
    //鼠标拖动旋转量
    void mouseOperate();
    //绘制目标主体
    void MyPaint();
    //鼠标单击事件
    void mousePressEvent(QMouseEvent *event);
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event);
    //鼠标滚轮事件
    void wheelEvent(QWheelEvent *event);
//! [2]


//! [3]

private:
    //绕xyz轴的旋转弧度
    float xRot;
    float yRot;
    float zRot;
    //放缩比例
    float scale;
    //定义总视口的宽和高
    int mywidth;
    int myheight;
    //判断鼠标是否点击在了左侧视口
    bool flag_in;
    //左侧视口的中心位置
    int centerX;
    int centerY;
    //模拟球半径
    int r;
    //记录旋转向量
    MyPoint vet;
    //四元数和旋转量
    MyPoint q;
    float qc;
    //旋转的累加，四元数的乘法运算
    void Quaternion(MyPoint v,float a);
    //向量单位化
    MyPoint Normal(MyPoint in);
    float tr_par[6];
    Morphing MyTra;
    
    float ex_par[5];
    float ro_par[7];
    
};
//! [3]


#endif

