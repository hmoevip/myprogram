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
	vector< vector<Point_3> > Q;
	vector<Point_3> midQ;
	vector<Point_3> myQ;
	vector<MyCube> Met;
	Point_3 c1_,c2_;
	//计算凸包点
	void ComputeConvex();
	//读取文件内容
    bool GetFileContent(string fileName);
	void Compute(Process in);
	void Output(string str, vector<Point_3> in);
	void aaaaa(vector<Point_3> in);
protected:
	//文件名是否合法
    bool ValidFileName(string name);
	//消除前置空格
	void EliminatePreSpace(string &str);
    //将字符转数字
	template <typename NumType>
    void ConvertString(string &str,NumType &number);
	//寻找最小点
	Point_3 FindSmallest(int flag);
	//计算两向量夹脚
	long double ComputeAngle(Point_3 start, Point_3 end, Point_3 newend,int flag);
	long double ComputeAngleB(Point_3 start, Point_3 end, Point_3 newend,int flag);
	//计算两点间距离
	long double Distance(Point_3 start,Point_3 end,int flag);
	void ComputeXYConvex();
	void ComputeXZConvex();	
	void ComputeYZConvex();
	MyCube RotateMet(Point_3 _i1, Point_3 _i2);

private:
	string InName;
};
//! [3]


#endif

