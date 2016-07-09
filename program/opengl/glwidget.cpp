#define _STDCALL_SUPPORTED
#define _M_IX86
#define GLUT_DISABLE_ATEXIT_HACK

#include "glwidget.h"
#include <GLUT/glut.h>
#include "qevent.h"
#include "stdio.h"
//! [0]

GLWidget::GLWidget(QWidget *parent)
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
    centerX = (int)(0.375*width());
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

GLWidget::~GLWidget()
{
    
}


QSize GLWidget::minimumSizeHint() const
{
    return QSize(800, 600);
}


QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}


void GLWidget::GetTransParameter(float *para)
{
    for(int i=0;i<6;i++)
    {
	    tr_par[i] = para[i];	    
    }
    emit RecordParameter(tr_par);
    MyTra.Init(tr_par,6);
    updateGL();
}
void GLWidget::GetExtendParameter(float *para)
{
    for(int i=0;i<5;i++)
    {
	    ex_par[i] = para[i];	    
    }
    MyTra.Init(ex_par,5);
    updateGL();
}
void GLWidget::GetRollParameter(float *para)
{
    for(int i=0;i<7;i++)
    {
	    ro_par[i] = para[i];	    
    }
    MyTra.Init(ro_par,7);
    updateGL();
}

void GLWidget::initializeGL()
{
    // ������Ӱƽ��
    glShadeModel( GL_SMOOTH );
    // ��ɫ����
    glClearColor( 1.0, 1.0, 1.0, 0.0 );
    // ������Ȼ���
    glClearDepth( 1.0 );
     // ������Ȳ���
    glEnable( GL_DEPTH_TEST );
    // ������Ȳ��Ե�����
    glDepthFunc( GL_LEQUAL );
    // ����ϵͳ��͸�ӽ�������
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}


void GLWidget::paintGL()
{
   // �����Ļ����Ȼ���
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    PaintPartLine();
    PaintMainViewport();
    PaintViewportX();
    PaintViewportY();
    PaintViewportZ();
    glFlush(); 
}


void GLWidget::resizeGL(int width, int height)
{
    // ��ֹ���ڴ�С��Ϊ0
    if ( height == 0 )
    {
        height = 1;
    }
    mywidth = width;
    myheight = height;
    centerX = (int)(0.375*width);
    centerY = height/2;
    r = centerX<centerY ? centerX:centerY;
    

}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		if(event->x()<(3*mywidth/4) && event->y()<myheight)
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


void GLWidget::mouseMoveEvent(QMouseEvent *event)
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


void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{

	if(event->button() == Qt::LeftButton)
	{
		flag_in = false;

	}
}
    
void GLWidget::wheelEvent(QWheelEvent *event)
{
	if(event->x()<(3*mywidth/4) && event->y()<myheight)
	{
		scale = scale +  0.05 * event->delta() / 120;
		if(scale<=0)
			scale = 0;
		updateGL();
	}
}

void GLWidget::mouseOperate()
{
	glRotatef(-zRot*180/PI,0,0,1);
	glRotatef(yRot*180/PI,0,1,0);
	glRotatef(-xRot*180/PI,1,0,0);
	glScalef(scale,scale,scale);
	QString text = "Rotation Angle  x:"+(QString::number(-xRot*180/PI,'f',4)).rightJustified(9,' ')+
		"  y:"+(QString::number(yRot*180/PI,'f',4)).rightJustified(9,' ')+
		"  z:"+(QString::number(-zRot*180/PI,'f',4)).rightJustified(9,' ')+
		"  scale:"+(QString::number(scale,'f',2)).rightJustified(5,' ');
	emit RotationChangedText(text);
	
	
}
void GLWidget::MyPaint()
{
	mouseOperate();
    
    //����һ��������
    for (int i=0;i<MyTra.Targface.size();i++)
    {
	if(MyTra.Targface.at(i).type==0)
	{
		glColor3ub( 100.0, 100.0, 100.0 );
	}else if(MyTra.Targface.at(i).type==1)
	{
		glColor3ub( 150.0, 150.0, 150.0 );
	}
	else if(MyTra.Targface.at(i).type==2)
	{
		glColor3ub( 200.0, 200.0, 200.0 );
	}else if(MyTra.Targface.at(i).type==3)
	{
		glColor3ub( 125.0, 125.0, 125.0 );
	}else{
		glColor3ub( 175.0, 175.0, 175.0 );
	}
	
	
    	glBegin(GL_POLYGON);							// ����������
	for (int j=0;j<MyTra.Targface.at(i).side.size();j++)
	{
		glVertex3f(MyTra.Targface.at(i).side.at(j).Mybegin.x,
				MyTra.Targface.at(i).side.at(j).Mybegin.y,
				MyTra.Targface.at(i).side.at(j).Mybegin.z);
	}
	glEnd();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINES);							// ����������
	for (int j=0;j<MyTra.Targface.at(i).side.size();j++)
	{
		glVertex3f(MyTra.Targface.at(i).side.at(j).Mybegin.x,
				MyTra.Targface.at(i).side.at(j).Mybegin.y,
				MyTra.Targface.at(i).side.at(j).Mybegin.z);
		glVertex3f(MyTra.Targface.at(i).side.at(j).Myend.x,
				MyTra.Targface.at(i).side.at(j).Myend.y,
				MyTra.Targface.at(i).side.at(j).Myend.z);
	}
	glEnd();
    }
    glColor3ub(225,225,225);
    glBegin(GL_POLYGON);
	for (int i=0;i<720;i++)
		glVertex3f(MyTra.aup.at(i).x,MyTra.aup.at(i).y,MyTra.aup.at(i).z);
    glEnd();
    glColor3ub(225,225,225);
    glBegin(GL_POLYGON);
	for (int i=0;i<720;i++)
		glVertex3f(MyTra.down.at(i).x,MyTra.down.at(i).y,MyTra.down.at(i).z);
    glEnd();
}

void GLWidget::PaintMainViewport()
{
    //�������ӿ����������ɫ
    glColor3f(1,0,0);
    //�н���һ�ӿڵĹ۲����  
    glLoadIdentity();
    //���ù۲����Z���������  
    gluLookAt(0,-5,5,0,0,0,0,1,0);
    //����ͶӰ����  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //����ͶӰ��������ѡ����պ��飬�ڶ������Ϊ������ӿڵı���  
    gluPerspective(60, (GLfloat)mywidth*0.75/(GLfloat)myheight,0.1,10.0);  
    glMatrixMode(GL_MODELVIEW);  
    //�����ӿ�Ϊ������ӿ�  
    glViewport(0, 0, 3*mywidth/4, myheight);  
    //�����ƽ�����������һʱ������һʱ�̵�λ��
    glPushMatrix();
    
    //����ʵ��
    MyPaint();
    glPopMatrix();
}
void GLWidget::PaintViewportX()
{
    //���������ӿ����������ɫ
    glColor3f(1,0,0);
    //�н���һ�ӿڵĹ۲����  
    glLoadIdentity();
    //���ù۲����X���������  
    gluLookAt(5,0,0,0,0,0,0,0,1);
    //����ͶӰ����  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //����ͶӰ��������ѡ����պ��飬�ڶ������Ϊ�����ӿڵı���  
    gluPerspective(60, (GLfloat)mywidth*0.75/(GLfloat)myheight,0.1,10.0);  
    glMatrixMode(GL_MODELVIEW);  
    //�����ӿ�Ϊ�����ӿڣ�ǰ�������������λ�ã������������ǿ�͸�  
    glViewport(3*mywidth/4, 0, mywidth/4, myheight/3);  
    //�����ƽ�����������һʱ������һʱ�̵�λ��
    glPushMatrix();
    //����ʵ��
    MyPaint();
    glPopMatrix();
}
void GLWidget::PaintViewportY()
{
    //���������ӿ����������ɫ
    glColor3f(1,0,0);
    //�н���һ�ӿڵĹ۲����  
    glLoadIdentity();
    //���ù۲����Y���������  
    gluLookAt(0,5,0,0,0,0,1,0,0);
    //����ͶӰ����  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //����ͶӰ��������ѡ����պ��飬�ڶ������Ϊ�����ӿڵı���  
    gluPerspective(60, (GLfloat)mywidth*0.75/(GLfloat)myheight,0.1,10.0);      
    glMatrixMode(GL_MODELVIEW);  
    //�����ӿ�Ϊ�����ӿ�  
    glViewport(3*mywidth/4, myheight/3, mywidth/4, myheight/3);  
    //�����ƽ�����������һʱ������һʱ�̵�λ��
    glPushMatrix();
    //����ʵ��
    MyPaint();
    glPopMatrix();
}
void GLWidget::PaintViewportZ()
{
    //���������ӿ����������ɫ
    glColor3f(1,0,0);
    //�н���һ�ӿڵĹ۲����  
    glLoadIdentity();
    //���ù۲����Z���������  
    gluLookAt(0,0,5,0,0,0,0,1,0);
    //����ͶӰ����  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //����ͶӰ��������ѡ����պ��飬�ڶ������Ϊ�����ӿڵı���  
    gluPerspective(60, (GLfloat)mywidth*0.75/(GLfloat)myheight,0.1,10.0);  
    glMatrixMode(GL_MODELVIEW);  
    //�����ӿ�Ϊ�����ӿ�  
    glViewport(3*mywidth/4, 2*myheight/3, mywidth/4, myheight/3);  
    //�����ƽ�����������һʱ������һʱ�̵�λ��
    glPushMatrix();
    //����ʵ��
    MyPaint();
    glPopMatrix();
}
void GLWidget::PaintPartLine()
{
    //���û��Ʒָ��ߵ���ɫΪ��ɫ	
    glColor3f(1,1,1);
    //�н�����һ�ӿڻ��ƵĹ۲����
    glLoadIdentity();
    //ѡ��ͶӰ����   
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //�������ӿڽ�ȡΪ���ճ���Ĵ�С
    gluOrtho2D( 0.0, mywidth, 0.0, myheight );
    // ѡ��ģ�͹۲����Ϊ��һ�ӿڻ������½ӿ�
    glMatrixMode( GL_MODELVIEW );
    
    //�����ĸ��ӿڵķָ��ߣ�һ������
    glViewport( 0, 0, mywidth, myheight);
    glBegin(GL_LINES);
    glVertex2f(0.75*mywidth,0.0);
    glVertex2f(0.75*mywidth,myheight);
    glVertex2f(0.75*mywidth,myheight/3);
    glVertex2f(mywidth,myheight/3);
    glVertex2f(0.75*mywidth,2*myheight/3);
    glVertex2f(mywidth,2*myheight/3);
    glEnd();
    //������������ϵ
    glBegin(GL_LINES);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/60,myheight/60);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/24,myheight/12);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/12,myheight/24);
    glEnd();
    glRasterPos2f(0.75*mywidth+3,3);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');
    glRasterPos2f(0.75*mywidth+myheight/24-4,myheight/12+4);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'z');
    glRasterPos2f(0.75*mywidth+myheight/12+1,myheight/24-4);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'y');
    //������������ϵ
    glTranslatef(0.0,myheight/3,0.0);
    glBegin(GL_LINES);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/60,myheight/60);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/24,myheight/12);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/12,myheight/24);
    glEnd();
    glRasterPos2f(0.75*mywidth+3,3);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'y');
    glRasterPos2f(0.75*mywidth+myheight/24-4,myheight/12+4);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');
    glRasterPos2f(0.75*mywidth+myheight/12+1,myheight/24-4);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'z');
    //������������ϵ
    glTranslatef(0.0,myheight/3,0.0);
    glBegin(GL_LINES);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/60,myheight/60);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/24,myheight/12);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/12,myheight/24);
    glEnd();
    glRasterPos2f(0.75*mywidth+3,3);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'z');
    glRasterPos2f(0.75*mywidth+myheight/24-4,myheight/12+4);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'y');
    glRasterPos2f(0.75*mywidth+myheight/12+1,myheight/24-4);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');
}

void PaintOriginalViewport()
{}

void GLWidget::Quaternion(MyPoint v,float a)
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

MyPoint GLWidget::Normal(MyPoint in)
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


