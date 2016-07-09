#define _STDCALL_SUPPORTED
#define _M_IX86
#define GLUT_DISABLE_ATEXIT_HACK

#include "oview.h"
#include <GLUT/glut.h>
#include "qevent.h"
#include "stdio.h"
//! [0]

OView::OView(QWidget *parent)
    : QGLWidget(parent)
{
    //*vet = new MyPoint;
    //*rot = new MyPoint;
    q.x = 0.0;
    q.y = 0.0;
    q.z = 0.0;
    xRot = 0;
    yRot = 0;
    zRot = 0;
    mywidth = width();
    myheight = height();
    flag_in = false;
    centerX = width()/2;
    centerY = height()/2;
    r = centerX<centerY ? centerX:centerY;
    //qDebug( "my window handle = %d,%d,%d", centerX,centerY,r );
    qc = 1.0;
    scale = 1;
    tr_par[0]=1;
    tr_par[1]=0;
    tr_par[2]=1;
    tr_par[3]=0.1;
    tr_par[4]=0;
    tr_par[5]=0;
    ex_par[0]=1;
    ex_par[1]=0;
    ex_par[2]=1;
    ex_par[3]=0.1;
    ex_par[4]=0;
    MyTra.Init(tr_par,6);
}

OView::~OView()
{
    
}


QSize OView::minimumSizeHint() const
{
    return QSize(1000, 1000);
}


QSize OView::sizeHint() const
{
    return QSize(1000, 1000);
}


void OView::GetTransParameter(float *para)
{
    for(int i=0;i<6;i++)
    {
	    tr_par[i] = para[i];	    
    }
    MyTra.Init(tr_par,6);
    updateGL();
}
void OView::GetExtendParameter(float *para)
{
    for(int i=0;i<5;i++)
    {
	    ex_par[i] = para[i];	    
    }
    MyTra.Init(ex_par,5);
    updateGL();
}
void OView::GetRollParameter(float *para)
{
    for(int i=0;i<7;i++)
    {
	    ro_par[i] = para[i];	    
    }
    MyTra.Init(ro_par,7);
    updateGL();
}

void OView::initializeGL()
{
    // 启用阴影平滑
    glShadeModel( GL_SMOOTH );
    // 黑色背景
    glClearColor( 1.0, 1.0, 1.0, 0.0 );
    // 设置深度缓存
    glClearDepth( 1.0 );
     // 启用深度测试
    glEnable( GL_DEPTH_TEST );
    // 所作深度测试的类型
    glDepthFunc( GL_LEQUAL );
    // 告诉系统对透视进行修正
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}


void OView::paintGL()
{
   // 清除屏幕和深度缓存
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //glLoadIdentity();
    glPushMatrix();
    MyPaint();
    glPopMatrix();
}


void OView::resizeGL(int width, int height)
{
    // 防止窗口大小变为0
    if ( height == 0 )
    {
        height = 1;
    }
    mywidth = width;
    myheight = height;
    centerX = width/2;
    centerY = height/2;
    r = centerX<centerY ? centerX:centerY;
    //设置视口为左侧主视口  
    glViewport(0, 0, width, height);      
    //设置观察点在Z轴的正方向  
    gluLookAt(0,0,5,0,0,0,0,1,0);
    //设置投影矩阵  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //设置投影区域，数字选择参照红书，第二项比例为左侧主视口的比例  
    gluPerspective(60, (GLfloat)width/(GLfloat)height,0.1,10.0);  
    glMatrixMode(GL_MODELVIEW); 
    
    //glLoadIdentity();
}


void OView::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		if(event->x()<(mywidth) && event->y()<myheight)
			flag_in = true;
		if(flag_in)
		{
		    int a = event->x()-centerX;
		    int b = event->y()-centerY;
		    int c = a*a+b*b;
		    if(c>=r*r)
		       {
                           vet.x = a*r/sqrt(c);
			   vet.y = b*r/sqrt(c);
			   vet.z = 0;
		       }else if(c<r*r)
		       {
			   vet.x = a;
			   vet.y = b;
			   vet.z = sqrt(r*r-c);
		       }
		vet = Normal(vet);  
		//qDebug( "my window handle = %f,%f,%f", vet.x,vet.y,vet.z );
		}		
	}    
}


void OView::mouseMoveEvent(QMouseEvent *event)
{
	if(flag_in)
	{
		MyPoint new_vet;
		MyPoint new_rot;
		float temp;
		double temp1,temp2,temp3;
    		int a = event->x()-centerX;
		int b = event->y()-centerY;
		int c = a*a+b*b;
		if(c>=r*r)
		{
                   new_vet.x = a*r/sqrt(c);
		   new_vet.y = b*r/sqrt(c);
		   new_vet.z = 0;
		}else if(c<r*r)
		{
		   new_vet.x = a;
		   new_vet.y = b;
		   new_vet.z = sqrt(r*r-c);
		}
		new_vet = Normal(new_vet);
		
		temp1 = (new_vet.x-vet.x)*(new_vet.x-vet.x);
		temp2 = (new_vet.y-vet.y)*(new_vet.y-vet.y);
		temp3 = (new_vet.z-vet.z)*(new_vet.z-vet.z);
		temp = sqrt(temp1+temp2+temp3);
		
		
		new_rot.x = vet.y*new_vet.z-new_vet.y*vet.z;
		new_rot.y = vet.z*new_vet.x-new_vet.z*vet.x;
		new_rot.z = vet.x*new_vet.y-new_vet.x*vet.y;
		
		vet = new_vet;

    		if (event->buttons() & Qt::LeftButton) {
			Quaternion(new_rot,temp); 
			updateGL();
   		}
	}
}


void OView::mouseReleaseEvent(QMouseEvent *event)
{

	if(event->button() == Qt::LeftButton)
	{
		flag_in = false;

	}
}
    
void OView::wheelEvent(QWheelEvent *event)
{
	if(event->x()<(mywidth) && event->y()<myheight)
	{
		scale = scale +  0.05 * event->delta() / 120;
		if(scale<=0)
			scale = 0;
		updateGL();
	}
}

void OView::mouseOperate()
{
	glRotatef(-zRot*180/PI,0,0,1);
	glRotatef(yRot*180/PI,0,1,0);
	glRotatef(-xRot*180/PI,1,0,0);
	glScalef(scale,scale,scale);
}
void OView::MyPaint()
{
	mouseOperate();
    
    //绘制一个正方形
    for (int i=0;i<MyTra.Origface.size();i++)
    {
	if(MyTra.Origface.at(i).type==0)
	{
		glColor3ub(100,100,100);
	}else if(MyTra.Origface.at(i).type==1)
	{
		glColor3ub(150,150,150);
	}
	else if(MyTra.Origface.at(i).type==2)
	{
		glColor3ub(200,200,200);
	}else if(MyTra.Origface.at(i).type==3)
	{
		glColor3ub(125,125,125);
	}else if(MyTra.Origface.at(i).type==4)
	{
		glColor3ub(175,175,175);
	}else{
		glColor3ub( 1.0, 1.0, 1.0 );
	}
	
	
    	glBegin(GL_POLYGON);							// 绘制三角形
	for (int j=0;j<MyTra.Origface.at(i).side.size();j++)
	{
		glVertex3f(MyTra.Origface.at(i).side.at(j).Mybegin.x,
				MyTra.Origface.at(i).side.at(j).Mybegin.y,
				MyTra.Origface.at(i).side.at(j).Mybegin.z);
	}
	glEnd();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINES);							// 绘制三角形
	for (int j=0;j<MyTra.Origface.at(i).side.size();j++)
	{
		glVertex3f(MyTra.Origface.at(i).side.at(j).Mybegin.x,
				MyTra.Origface.at(i).side.at(j).Mybegin.y,
				MyTra.Origface.at(i).side.at(j).Mybegin.z);
		glVertex3f(MyTra.Origface.at(i).side.at(j).Myend.x,
				MyTra.Origface.at(i).side.at(j).Myend.y,
				MyTra.Origface.at(i).side.at(j).Myend.z);
	}
	glEnd();
    }
    glColor3ub(225,225,225);
    glBegin(GL_POLYGON);
	for (int i=0;i<720;i++)
		glVertex3f(MyTra.bup.at(i).x,MyTra.bup.at(i).y,MyTra.bup.at(i).z);
    glEnd();
    glColor3ub(225,225,225);
    glBegin(GL_POLYGON);
	for (int i=0;i<720;i++)
		glVertex3f(MyTra.down.at(i).x,MyTra.down.at(i).y,MyTra.down.at(i).z);
    glEnd();
}

void OView::Quaternion(MyPoint v,float a)
{
	//float norm;
	MyPoint u;
	float b,t;
	u = q;
	b = qc;
	t = cos(a/2);
        v = Normal(v);	
	
	v.x = v.x*sin(a/2);
	v.y = v.y*sin(a/2);
	v.z = v.z*sin(a/2);

	qc = b*t-v.x*u.x-v.y*u.y-v.z*u.z;
	q.x = t*u.x+b*v.x-u.y*v.z+v.y*u.z;
	q.y = t*u.y+b*v.y-u.z*v.x+v.z*u.x;
	q.z = t*u.z+b*v.z-u.x*v.y+v.x*u.y;

	xRot = atan2(2*(qc*q.x+q.y*q.z),1-2*(q.x*q.x+q.y*q.y));
	yRot = asin(2*(qc*q.y-q.x*q.z));
	zRot = atan2(2*(qc*q.z+q.x*q.y),1-2*(q.y*q.y+q.z*q.z));


}

MyPoint OView::Normal(MyPoint in)
{
	float norm;
	MyPoint v;
	v = in;
	norm = sqrt((v.x)*(v.x)+(v.y)*(v.y)+(v.z)*(v.z));
	if(norm>0)
	{
		v.x = v.x/norm;
		v.y = v.y/norm;
		v.z = v.z/norm;
	}
	return v;
}


