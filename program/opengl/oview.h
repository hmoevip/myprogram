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
    //������Ⱦ����
    void initializeGL();
    //���ƴ���
    void paintGL();
    //��Ӧ���ڵĴ�С�仯
    void resizeGL( int width, int height );
    //����϶���ת��
    void mouseOperate();
    //����Ŀ������
    void MyPaint();
    //��굥���¼�
    void mousePressEvent(QMouseEvent *event);
    //����ƶ��¼�
    void mouseMoveEvent(QMouseEvent *event);
    //����ͷ��¼�
    void mouseReleaseEvent(QMouseEvent *event);
    //�������¼�
    void wheelEvent(QWheelEvent *event);
//! [2]


//! [3]

private:
    //��xyz�����ת����
    float xRot;
    float yRot;
    float zRot;
    //��������
    float scale;
    //�������ӿڵĿ�͸�
    int mywidth;
    int myheight;
    //�ж�����Ƿ�����������ӿ�
    bool flag_in;
    //����ӿڵ�����λ��
    int centerX;
    int centerY;
    //ģ����뾶
    int r;
    //��¼��ת����
    MyPoint vet;
    //��Ԫ������ת��
    MyPoint q;
    float qc;
    //��ת���ۼӣ���Ԫ���ĳ˷�����
    void Quaternion(MyPoint v,float a);
    //������λ��
    MyPoint Normal(MyPoint in);
    float tr_par[6];
    Morphing MyTra;
    
    float ex_par[5];
    float ro_par[7];
    
};
//! [3]


#endif

