#ifndef MYCLASS_H
#define MYCLASS_H
#include <QVector>
#define PI 3.1415926
#include <math.h>

class MyVector
{
public:
	double a;
	double b;
	double c;
	bool operator ==(MyVector s){
		if ((int)((s.a-a)*10000000)==0&&(int)((s.b-b)*10000000)==0&&(int)((s.c-c)*10000000)==0)
		{
			return true;
		}
		return false;
	}
	MyVector plus(MyVector s)
	{
		MyVector vet;
		vet.a = b*s.c-s.b*c;
		vet.b = c*s.a-s.c*a;
		vet.c = a*s.b-s.a*b;
		return vet;
	}
	float dot(MyVector s)
	{
		return s.a*a+s.b*b+s.c*c;
	}
	float mod()
	{
		return sqrt(a*a+b*b+c*c);
	}	
};

class MyPoint
{
public:
	float x;
	float y;
	float z;
	//用于比较两个点是否相同;
	bool operator ==(MyPoint s){
		if ((int)((s.x-x)*10000000)==0&&(int)((s.y-y)*10000000)==0&&(int)((s.z-z)*10000000)==0)
		{
			return true;
		}
		return false;
	}
	bool operator !=(MyPoint s){
		if ((int)((s.x-x)*10000000)!=0||(int)((s.y-y)*10000000)!=0||(int)((s.z-z)*10000000)!=0)
		{
			return true;
		}
		return false;
	}
	float dis(MyPoint s)
	{
		return sqrt((s.x-x)*(s.x-x)+(s.y-y)*(s.y-y)+(s.z-z)*(s.z-z));
	}
       	MyVector vet(MyPoint s)
	{
		MyVector vet;
		vet.a = s.x-x;
		vet.b = s.y-y;
		vet.c = s.z-z;
		return vet;
	}
	MyPoint mus(MyPoint s)
	{
		MyPoint v;
		v.x = x-s.x;
		v.y = y-s.y;
		v.z = z-s.z;
		return v;
	}
	MyPoint add(MyPoint s)
	{
		MyPoint v;
		v.x = x+s.x;
		v.y = y+s.y;
		v.z = z+s.z;
		return v;
	}
};



class MySide
{
public:
	MyPoint Mybegin;
	MyPoint Myend;
	bool operator ==(MySide s){
		if (s.Mybegin==Mybegin &&s.Myend==Myend)
		{
			return true;
		}
		return false;
	}
	bool operator !=(MySide s){
		if (s.Mybegin==Myend &&s.Myend==Mybegin)
		{
			return true;
		}
		return false;
	}
};

//面的定义，存三条边，加一条向量;
class MyFace
{
public:
	QVector <MySide> side;
	//Myvector v;
	int type;
};

#endif


