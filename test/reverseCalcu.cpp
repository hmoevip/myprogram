#include "reverseCalcu.h"

double MyCalcu::distance(matrixly p,matrixly f)  
{  
    return sqrt((p.dataly[0][0]-f.dataly[0][0])*(p.dataly[0][0]-f.dataly[0][0])+(p.dataly[1][0]-f.dataly[1][0])*(p.dataly[1][0]-f.dataly[1][0])+(p.dataly[2][0]-f.dataly[2][0])*(p.dataly[2][0]-f.dataly[2][0]));  
}  

//最终返回长度集合
vector<double>MyCalcu::calculate( double X, double Y, double Z, double a, double b, double c)
{  
    //存储上下顶点集合
	vector<matrixly> v1;
    vector<matrixly> v2;
	
	//存储Bi点的集合
    vector<matrixly> v3;

	//杆长临时集合
	vector<double> temp_list; 
	
	//杆长变化集合
	vector<double> move_list;
	//视觉识别X,Y，Z 结构体
	matrixly CA;
	CA.dataly[0][0]=X;
    CA.dataly[1][0]=Y;
    CA.dataly[2][0]=Z+400;
	CA.rowly=3;
	CA.colly=1;

	//下平台点坐标
    matrixly C1;
	matrixly C2;
	matrixly C3;
	matrixly C4;
	matrixly C5;
	matrixly C6;
	matrixly C7;
	matrixly C8;
    
    double dataC1[3] ={-200,158,0}; 
	double dataC2[3] ={60,158,0};
	double dataC3[3] ={200,158,0};
	double dataC4[3] ={258,60,0}; 
	double dataC5[3] ={200,-158,0};
	double dataC6[3] ={-60,-158,0};
	double dataC7[3] ={-200,-158,0};
	double dataC8[3] ={-258,-60,0};
	
    
	for(int q=0;q<3;q++)
		{
			C1.dataly[q][0]=dataC1[q];
		    C2.dataly[q][0]=dataC2[q];
			C3.dataly[q][0]=dataC3[q];
			C4.dataly[q][0]=dataC4[q];
			C5.dataly[q][0]=dataC5[q];
			C6.dataly[q][0]=dataC6[q];
			C7.dataly[q][0]=dataC7[q];
			C8.dataly[q][0]=dataC8[q];

	}
		C1.rowly=3;
		C1.colly=1;
		C2.rowly=3;
		C2.colly=1;
		C3.rowly=3;
		C3.colly=1;
		C4.rowly=3;
		C4.colly=1;
		C5.rowly=3;
		C5.colly=1;
		C6.rowly=3;
		C6.colly=1;
		C7.rowly=3;
		C7.colly=1;
		C8.rowly=3;
		C8.colly=1;
		
	  v1.push_back( C1 );
	  v1.push_back( C2 );
	  v1.push_back( C3 );
	  v1.push_back( C4 );
	  v1.push_back( C5 );
	  v1.push_back( C6 );
	  v1.push_back( C7 );
	  v1.push_back( C8 );

	//上平台点坐标
    matrixly A1;
	matrixly A2;
	matrixly A3;
	matrixly A4;
	matrixly A5;
	matrixly A6;
	matrixly A7;
	matrixly A8;

	double dataA1[3] ={-200,158,0}; 
	double dataA2[3] ={-60,158,0};
	double dataA3[3] ={200,158,0};
	double dataA4[3] ={258,-60,0};
	double dataA5[3] ={200,-158,0}; 
	double dataA6[3] ={60,-158,0}; 
	double dataA7[3] ={-200,-158,0}; 
	double dataA8[3] ={-258,60,0}; 

		for(int p=0;p<3;p++)
		{
			A1.dataly[p][0]=dataA1[p];
			A2.dataly[p][0]=dataA2[p];
			A3.dataly[p][0]=dataA3[p];
			A4.dataly[p][0]=dataA4[p];
			A5.dataly[p][0]=dataA5[p];
			A6.dataly[p][0]=dataA6[p];
			A7.dataly[p][0]=dataA7[p];
			A8.dataly[p][0]=dataA8[p];
		}

        A1.rowly=3;
		A1.colly=1;
		A2.rowly=3;
		A2.colly=1;
		A3.rowly=3;
		A3.colly=1;
		A4.rowly=3;
		A4.colly=1;
		A5.rowly=3;
		A5.colly=1;
		A6.rowly=3;
		A6.colly=1;
		A7.rowly=3;
		A7.colly=1;
		A8.rowly=3;
		A8.colly=1;

	v2.push_back( A1 );	
	v2.push_back( A2 );	
	v2.push_back( A3 );	
	v2.push_back( A4 );	
	v2.push_back( A5 );	
	v2.push_back( A6 );	
	v2.push_back( A7 );	
	v2.push_back( A8 );	
         
	//A	
	double data1[3][3] ={1,0,0,0,cos(a),-sin(a),0,sin(a),cos(a)};
	//B
	double data2[3][3] ={cos(b),0,sin(b),0,1,0,-sin(b),0,cos(b)};
	//C
	double data3[3][3] ={cos(c),-sin(c),0,sin(c),cos(c),0,0,0,1};
	matrix A;
	A.col=3;
	A.row=3;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
           	A.data[i][j]=data1[i][j];
		}
		matrix B;
		B.col=3;
		B.row=3;
		for(int m=0;m<3;m++)
			for(int n=0;n<3;n++)
			{
				B.data[m][n]=data2[m][n];
			}
			matrix C;
			C.col=3;
			C.row=3;
			for(int o=0;o<3;o++)
				for(int p=0;p<3;p++)
				{
					C.data[o][p]=data3[o][p];
				}

				//show(A);
				//show(B);
				//show(C);
				//show(mult(C,B));
				//show(mult(mult(C,B),A));
				//showly(mult1(mult(mult(C,B),A), v2.at(1)));
				//showly(add(CA,mult1(mult(mult(C,B),A), v2.at(1))));

	           //进行8次求解Bi
				for(int count = 0; count<8;count++)
				{
				 //添加集合
                 v3.push_back(add(CA,mult1( mult(mult(C,B),A), v2.at(count))));
                
				}
				//清空数据
				temp_list.clear();
				//计算长度
				for(int countn=0;countn<8;countn++)
				{
                 temp_list.push_back(distance(v3.at(countn),v1.at(countn)));
				}
				return temp_list;		
};

matrixly MyCalcu::add(matrixly a,matrixly b) 
{ 
	
	int i,j;
	matrixly c; 
	c.rowly=a.rowly; 
	c.colly=a.colly; 
	for(i=0;i<a.rowly;i++) 
	{ 
		for(j=0;j<a.colly;j++) 
		{ 
			c.dataly[i][j]=a.dataly[i][j]+b.dataly[i][j]; 
		} 
	} 
	return c; 
}


//3*3运算
matrix MyCalcu::mult(matrix a,matrix b)
{
	int i,j,k; 
	matrix c; 
	c.row=c.col=0;
	if(a.col!=b.row) 
	{ 
		return c; 
	}
	c.row=a.row;  
	c.col=b.col;
	for(i=0;i<a.row;i++)
	{   
		for(j=0;j<b.col;j++)  
		{   
			c.data[i][j]=0;  
			for(k=0;k<a.col;k++)  
			{   
				c.data[i][j]+=a.data[i][k]*b.data[k][j];   
			}  
		} 
	} 
	return c;
}

//3*1运算
matrixly MyCalcu::mult1(matrix a,matrixly b)
{
	int i,j,k; 
	matrixly c; 
	c.rowly=c.colly=0;
	c.rowly=a.row;  
	c.colly=b.colly;
	for(i=0;i<a.row;i++)
	{   
		for(j=0;j<b.colly;j++)  
		{   
			c.dataly[i][j]=0;  
			for(k=0;k<a.col;k++)  
			{   
				c.dataly[i][j]+=a.data[i][k]*b.dataly[k][j];   
			}  
		} 
	} 
	return c;
}

//show
void MyCalcu::show(matrix a)
{
	int i,j;
	for(i=0;i<a.row;i++)
	{
		for(j=0;j<a.col;j++)
		{
			cout<<setw(20)<<a.data[i][j];
		}
		cout<<endl;
	}
}
//showly
void MyCalcu::showly(matrixly a)
{
	int i,j;
	for(i=0;i<a.rowly;i++)
	{
		for(j=0;j<a.colly;j++)
		{
			cout<<setw(20)<<a.dataly[i][j];
		}
		cout<<endl;
	}
}
//杆长变化
vector<double> MyCalcu::move(vector<double> a,vector<double> b)
{ 
     vector<double> c; 
	 for(int iu=0;iu<8;iu++)
	 {
		 c.push_back(a.at(iu)-b.at(iu));
	 }
    
	 return c;
}
