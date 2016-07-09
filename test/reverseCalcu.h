#include "stdio.h"
#include<iomanip>
#include<iostream>
#include<math.h>
#include <vector>
#include <list>
using namespace std;

//矩阵
class matrix
{
 public:
	double data[3][3];
	int row;
	int col;
};

class matrixly
{    
 public:
     double dataly[3][1];
	 int rowly;
	 int colly;
};

class MyCalcu
{
public:
	vector<double> calculate(double a, double b, double c, double X, double Y, double Z);

	matrix mult(matrix a, matrix b);

	matrixly mult1(matrix a,matrixly b);

	matrixly add(matrixly a,matrixly b);
	//移动量
	vector<double> move1(double a, double b, double c, double X, double Y, double Z,double aa, double bb, double cc, double XX, double YY, double ZZ);
	vector<double> move(vector<double> a,vector<double> b);

	void show(matrix a);

	void showly(matrixly a);

	//求两点距离函数
	double distance(matrixly p,matrixly q);  

};
