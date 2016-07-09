#ifndef PROCESS_H
#define PROCESS_H

#include "MyClass.h"
#include "stdio.h"
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;
//! [0]

class Process
{
public:
    Process();
    ~Process();
	vector<Point_3> order_xy;
	vector<Point_3> order_xz;
	vector<Point_3> order_yz;
	vector<Point_3> PointSet;
	vector<MyRelation> FaceSet;
	vector< vector<Point_3> > Q;
	vector<Point_3> midQ;
	vector<Point_3> myQ;
	vector<MyCube> Met;
	//����͹����
	void ComputeConvex();
	Point_3 *c1_ = new Point_3[3];
	Point_3 *c2_ = new Point_3[3];

	//��ȡ�ļ�����
    bool GetFileContent(string fileName);
	void Compute(Process in);
	void Output(string str, vector<Point_3> in);
	void aaaaa(vector<Point_3> in);
protected:
	//�ļ����Ƿ�Ϸ�
    bool ValidFileName(string name);
	//����ǰ�ÿո�
	void EliminatePreSpace(string &str);
    //���ַ�ת����
	template <typename NumType>
    void ConvertString(string &str,NumType &number);
	//Ѱ����С��
	Point_3 FindSmallest(int flag);
	//�����������н�
	long double ComputeAngle(Point_3 start, Point_3 end, Point_3 newend,int flag);
	long double ComputeAngleB(Point_3 start, Point_3 end, Point_3 newend,int flag);
	//������������
	long double Distance(Point_3 start,Point_3 end,int flag);
	void ComputeXYConvex();
	void ComputeXZConvex();	
	void ComputeYZConvex();
	MyCube RotateMet(Point_3 _i1, Point_3 _i2, Point_3 _j1, Point_3 _j2);
	MyCube OBBMet(vector<Point_3> point, vector<MyRelation> face);
	MyCube RotateNew(Point_3 _i1, Point_3 _i2, Point_3 _j1, Point_3 _j2);
	MyCube RotateMeet(Point_3 _A, Point_3 _B, Point_3 _C, Point_3 _D);
	MyVector ComU(vector<Point_3> point, vector<MyRelation> face);

private:
	string InName;
};
//! [3]


#endif

