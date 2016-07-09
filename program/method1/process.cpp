#include "process.h"
#include <QString>
#include <QMessageBox>//! [0]
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

Process::Process()
{
}

Process::~Process()
{
    
}

bool Process::ValidFileName(string name)
{
	string last = "";
	int k = name.length();
	for(int i = k-3; i < k; i ++)
		last += name[i];
	if(last == "off")
		return true;
	else
		return false;
}

void Process::EliminatePreSpace(string &str)
{
	unsigned int i = 0;
	while (i < str.size())
	{
		if(str[i] == ' ' || str[i] == '\t')
		{
			str = str.substr(i + 1, str.size());
			i = 0; 
			continue;
		}
		else
			break;
	}
}

template <typename NumType>

void Process::ConvertString(string &str, NumType &number)
{
	EliminatePreSpace(str); //调用消除前置空格函数
	unsigned int i_len = 0;
	while (i_len < str.size())
	{
		if(str[i_len] == ' ' || str[i_len] == '\t')
			break;
		else
			i_len ++;
	}
	string num = "";
	for(unsigned int j = 0; j < i_len; j ++)
	{
		if(str[j]!=' ')
			num += str[j];
		else
			break;
	}
	if(i_len + 1 < str.size())
		str = str.substr(i_len+1 , str.size());
	const char *charnum = num.data();
	number = 0e-32;
	number = atof(charnum);
}

bool Process::GetFileContent(string fileName)
{
	long double sum_x;
	long double sum_y;
	long double sum_z;
	int size_;
	sum_x=0;
	sum_y=0;
	sum_z=0;
	PointSet.clear();
	order_xy.clear();
	vector<Point_3> TempSet;
	TempSet.clear();
	/*打开文件并且开始读取*/
	ifstream infile(fileName.c_str(), ios::in);
	if(!ValidFileName(fileName)) //判断是否合法
	{
		cout<<"Filename is not .off file!"<<endl;
		return false;
	}
	if(!infile)
	{
		cout<<"Could not open it!"<<endl;
		return false;
	}
	else//文件打开正确
	{
		string getString="";
		int i_line = 0;
		int first = 0;
		int vertices = 0, faces = 0;
		int i_vertex = 0;
		int i_face = 0;

		/*解析文件*/
		while (getline(infile, getString))
		{
			getString.erase(getString.end()-1);
			if(i_line == 0 && (getString == "OFF" || getString == "OFF "))
			{
				i_line ++;
				getString = "";
				continue;
			}
			else if(i_line == 0 && (getString != "OFF"|| getString != "OFF "))
			{
				cout<<"Not a valid off file!"<<endl;
				break;
			}
			if(getString!= "")
			{
				if(getString[0] == '#' || getString == " ")
				{
					i_line ++; 
					getString = "";
					continue;
				}
				else
				{
					if (first == 0)
					{
						ConvertString(getString, vertices);
						ConvertString(getString, faces);
						cout<<"Vertices:"<<vertices<<"\tFaces:"<<faces<<endl;
						first = 1;
						getString = "";
					}
					else
					{
						//处理点,获取里面的点
						if(i_vertex < vertices)
						{
						    long double x =0e-32,y=0e-32,z=0e-32;
						    ConvertString(getString, x);
						    ConvertString(getString, y);
						    ConvertString(getString, z);
                            //Point_3为点类 点类填充点对象p
						    Point_3 temp(x,y,z,i_vertex);
							sum_x = sum_x + x;
							sum_y = sum_y + y;
							sum_z = sum_z + z;
                            PointSet.push_back(temp);
							i_vertex ++;
							getString = "";
							continue;
						}
						
						
					}
				}
			}
			i_line ++;
		}
	}
	infile.close();
	size_ = PointSet.size();
	sum_x = sum_x/size_;
	sum_y = sum_y/size_;
	sum_z = sum_z/size_;
	if(size_>1000)
	{
		for(unsigned long i=0;i<PointSet.size();i=i+200)
		{
			TempSet.push_back(PointSet.at(i));
		}
		PointSet.clear();
		PointSet = TempSet;
	}
	for(unsigned long i=0;i<PointSet.size();i++)
	{
		PointSet.at(i).x = PointSet.at(i).x - sum_x;
		PointSet.at(i).y = PointSet.at(i).y - sum_y;
		PointSet.at(i).z = PointSet.at(i).z - sum_z;
	}
	cout<<"Reading data is completed!...."<<endl;
/*	for(int i=0;i<PointSet.size();i++)
	{
		cout<<PointSet[i].count <<PointSet[i].x <<PointSet[i].y <<PointSet[i].z <<endl;
	}
*/
	return true;
}

Point_3 Process::FindSmallest(int flag)
{
	Point_3 smallpoint;
	smallpoint = PointSet[0];
	switch(flag)
	{
		case 0:
			for(unsigned long i=1;i<PointSet.size();i++)
			{
				if(PointSet[i].x<smallpoint.x)
					smallpoint = PointSet[i];
			}
			break;
		case 1:
			for(unsigned long i=1;i<PointSet.size();i++)
			{
				if(PointSet[i].y<smallpoint.y)
					smallpoint = PointSet[i];
			}
			break;
		case 2:
			for(unsigned long i=1;i<PointSet.size();i++)
			{
				if(PointSet[i].z<smallpoint.z)
					smallpoint = PointSet[i];
			}
			break;
		default:
			cout<<"flag does not exit!"<<endl;
	}
	return smallpoint;
}

long double Process::ComputeAngle(Point_3 start,Point_3 end, Point_3 newend,int flag)
{
	long double angle;
	angle = 0;
	long double a,b,c,d,e;
	if(start==newend||end==newend)
	{
		angle = 0;
		return angle;
	}
	switch(flag)
	{
		case 0:
			a = end.x-start.x;
			b = end.y-start.y;
		    c = newend.x-start.x;
			d = newend.y-start.y;
			e = sqrt(a*a+b*b)*sqrt(c*c+d*d);
			angle = acos((a*c+b*d)/e);
			break;
		case 1:
			a = end.x-start.x;
			b = end.z-start.z;
		    c = newend.x-start.x;
			d = newend.z-start.z;
			e = sqrt(a*a+b*b)*sqrt(c*c+d*d);
			angle = acos((a*c+b*d)/e);
			break;
		case 2:
			a = end.z-start.z;
			b = end.y-start.y;
		    c = newend.z-start.z;
			d = newend.y-start.y;
			e = sqrt(a*a+b*b)*sqrt(c*c+d*d);
			angle = acos((a*c+b*d)/e);
			break;
		default:
			e = 0;
			break;
	}
		if(e==0)
		angle = 0;
	return angle;
}

long double Process::ComputeAngleB(Point_3 start,Point_3 end, Point_3 newend,int flag)
{
	long double angle;
	angle = 0;
	long double a,b,c,d,e;
	if(start==newend||end==newend)
	{
		angle = 0;
		return angle;
	}
	switch(flag)
	{
		case 0:
			a = end.x-start.x;
			b = end.y-start.y;
		    c = newend.x-end.x;
			d = newend.y-end.y;
			e = sqrt(a*a+b*b)*sqrt(c*c+d*d);
			angle = acos((a*c+b*d)/e);
			break;
		case 1:
			a = end.x-start.x;
			b = end.z-start.z;
		    c = newend.x-end.x;
			d = newend.z-end.z;
			e = sqrt(a*a+b*b)*sqrt(c*c+d*d);
			angle = acos((a*c+b*d)/e);
			break;
		case 2:
			a = end.z-start.z;
			b = end.y-start.y;
		    c = newend.z-end.z;
			d = newend.y-end.y;
			e = sqrt(a*a+b*b)*sqrt(c*c+d*d);
			angle = acos((a*c+b*d)/e);
			break;
		default:
			e=0;
			break;
	}
	if(e==0)
		angle = 0;
	return angle;
}

long double Process::Distance(Point_3 start, Point_3 end,int flag)
{
	long double distance;
	switch(flag)
	{
		case 0:
			distance = sqrt((start.x-end.x)*(start.x-end.x)+(start.y-end.y)*(start.y-end.y));
			break;
		case 1:
			distance = sqrt((start.x-end.x)*(start.x-end.x)+(start.z-end.z)*(start.z-end.z));
            break;
		case 2:
			distance = sqrt((start.z-end.z)*(start.z-end.z)+(start.y-end.y)*(start.y-end.y));
            break;
		default:
			distance = 0;
			break;
	}
	return distance;
}

void Process::ComputeXYConvex()
{
	Point_3 start,temp_point,next_point,stop_flag;
	long double angle,temp_angle;
	unsigned long safe;
	long double distance_temp,same_temp,d_temp;
	int ff;
	ff=0;
	angle=PI;
	distance_temp=0;
	same_temp=0;
	safe = 0;
	start = FindSmallest(1);
	order_xy.push_back(start);
	temp_point = start;
	stop_flag = start;
    temp_point.x = start.x+0.001;
//	temp_point.y = start.y-0.001;
	for(unsigned long i=0;i<PointSet.size();i++)
	{
		temp_angle=ComputeAngle(start,temp_point,PointSet[i],0);
		//cout<<i<<" temp_angle: "<<temp_angle<<endl;
		if(temp_angle<0.0001)
		{
			d_temp = Distance(start,PointSet[i],0);
		//	cout<<d_temp<<" "<<distance_temp<<endl;
			if(d_temp>distance_temp)
			{
				angle = 0;
				distance_temp = d_temp;
				next_point = PointSet[i];
			}
		}else if(angle-temp_angle>0.001)
		{
			angle = temp_angle;
			next_point = PointSet[i];
		}
		//cout<<i<<" angle: "<<angle<<endl;
	}
    order_xy.push_back(next_point);
	temp_point = next_point;
	while(next_point!=stop_flag)
	{
		safe++;
		angle = PI;
		distance_temp = Distance(start,temp_point,0);
		for(unsigned long i=0;i<PointSet.size();i++)
		{
			temp_angle = ComputeAngleB(start,temp_point,PointSet[i],0);
			if(temp_angle==0)
			{
				d_temp = Distance(start,PointSet[i],0);
				if(d_temp>distance_temp)
				{	
					angle = 0;
					distance_temp = d_temp;
					next_point = PointSet[i];
					order_xy.pop_back();
					order_xy.push_back(next_point);
				}
			}else if(angle>temp_angle)
			{
				angle = temp_angle;
				next_point = PointSet[i];
			}
		}
		if(angle!=0)
		{
			order_xy.push_back(next_point);
		}
		start = order_xy[order_xy.size()-2];
		temp_point = order_xy.back();
		if(safe>PointSet.size())
			break;
	}
	order_xy.pop_back();
	//cout<<order_xy.size()<<endl;
}

void Process::ComputeXZConvex()
{
	Point_3 start,temp_point,next_point,stop_flag;
	long double angle,temp_angle;
	unsigned long safe;
	long double distance_temp,same_temp,d_temp;
	angle=PI;
	distance_temp=0;
	same_temp=0;
	safe = 0;
	start = FindSmallest(2);
	order_xz.push_back(start);
	temp_point = start;
	stop_flag = start;
    temp_point.x = start.x+0.001;
//	temp_point.y = start.y-0.001;
	for(unsigned long i=0;i<PointSet.size();i++)
	{
		temp_angle=ComputeAngle(start,temp_point,PointSet[i],1);
		//cout<<i<<" temp_angle: "<<temp_angle<<endl;
		if(temp_angle<0.0001)
		{
			d_temp = Distance(start,PointSet[i],1);
		//	cout<<d_temp<<" "<<distance_temp<<endl;
			if(d_temp>distance_temp)
			{
				angle = 0;
				distance_temp = d_temp;
				next_point = PointSet[i];
			}
		}else if(angle-temp_angle>0.001)
		{
			angle = temp_angle;
			next_point = PointSet[i];
		}
		//cout<<i<<" angle: "<<angle<<endl;
	}
    order_xz.push_back(next_point);
	temp_point = next_point;
	while(next_point!=stop_flag)
	{
		safe++;
		angle = PI;
		distance_temp = Distance(start,temp_point,1);
		for(unsigned long i=0;i<PointSet.size();i++)
		{
			temp_angle = ComputeAngleB(start,temp_point,PointSet[i],1);
			if(temp_angle==0)
			{
				d_temp = Distance(start,PointSet[i],1);
				if(d_temp>distance_temp)
				{	
					angle = 0;
					distance_temp = d_temp;
					next_point = PointSet[i];
					order_xz.pop_back();
					order_xz.push_back(next_point);
				}
			}else if(angle>temp_angle)
			{
				angle = temp_angle;
				next_point = PointSet[i];
			}
		}
		if(angle!=0)
		{
			order_xz.push_back(next_point);
		}
		start = order_xz[order_xz.size()-2];
		temp_point = order_xz.back();
		if(safe>PointSet.size())
			break;
	}
	order_xz.pop_back();
	//cout<<order_xz.size()<<endl;
}

void Process::ComputeConvex()
{
	ComputeXYConvex();
	ComputeXZConvex();
	ComputeYZConvex();

}
void Process::ComputeYZConvex()
{
	Point_3 start,temp_point,next_point,stop_flag;
	long double angle,temp_angle;
	unsigned long safe;
	long double distance_temp,same_temp,d_temp;
	int ff;
	ff=0;
	angle=PI;
	distance_temp=0;
	same_temp=0;
	safe = 0;
	start = FindSmallest(2);
	order_yz.push_back(start);
	temp_point = start;
	stop_flag = start;
    temp_point.y = start.y+0.001;
//	temp_point.y = start.y-0.001;
	for(unsigned long i=0;i<PointSet.size();i++)
	{
		temp_angle=ComputeAngle(start,temp_point,PointSet[i],2);
		//cout<<i<<" temp_angle: "<<temp_angle<<endl;
		if(temp_angle<0.0001)
		{
			d_temp = Distance(start,PointSet[i],2);
		//	cout<<d_temp<<" "<<distance_temp<<endl;
			if(d_temp>distance_temp)
			{
				angle = 0;
				distance_temp = d_temp;
				next_point = PointSet[i];
			}
		}else if(angle-temp_angle>0.001)
		{
			angle = temp_angle;
			next_point = PointSet[i];
		}
		//cout<<i<<" angle: "<<angle<<endl;
	}
    order_yz.push_back(next_point);
	temp_point = next_point;
	while(next_point!=stop_flag)
	{
		safe++;
		angle = PI;
		distance_temp = Distance(start,temp_point,2);
		for(unsigned long i=0;i<PointSet.size();i++)
		{
			temp_angle = ComputeAngleB(start,temp_point,PointSet[i],2);
			if(temp_angle==0)
			{
				d_temp = Distance(start,PointSet[i],2);
				if(d_temp>distance_temp)
				{	
					angle = 0;
					distance_temp = d_temp;
					next_point = PointSet[i];
					order_yz.pop_back();
					order_yz.push_back(next_point);
				}
			}else if(angle>temp_angle)
			{
				angle = temp_angle;
				next_point = PointSet[i];
			}
		}
		if(angle!=0)
		{
			order_yz.push_back(next_point);
		}
		start = order_yz[order_yz.size()-2];
		temp_point = order_yz.back();
		if(safe>PointSet.size())
			break;
	}
	order_yz.pop_back();
//	cout<<order_yz.size()<<endl;
}

void Process::aaaaa(vector<Point_3> in)
{
	Point_3 a,b,c;
	MyVector ba,bc;
	long double ang;
	float dis;
	bool flag;
	flag = true;
	float delta;
	delta = 10;
	myQ.clear();
	cout<<"分割值为："<<delta<<endl;
	for(unsigned long i=0; i<in.size();i++)
	{
		if(i<in.size()-2)
		{
			a = in.at(i);
			b = in.at(i+1);
			c = in.at(i+2);
		}
		if(i==in.size()-2)
		{
			a = in.at(i);
			b = in.at(i+1);
			c = in.at(0);
		}
		if(i==in.size()-1)
		{
			a = in.at(i);
			b = in.at(0);
			c = in.at(1);
		}
		ba.a = a.x-b.x; 
		ba.b = a.y-b.y; 
		ba.c = a.z-b.z;
		bc.a = c.x-b.x; 
		bc.b = c.y-b.y; 
		bc.c = c.z-b.z;
		dis = bc.mod();
		ang = acos((ba.a*bc.a+ba.b*bc.b+ba.c*bc.c)/(ba.mod()*bc.mod()))*180/PI;
		if(ang<120 || dis>delta)
		{
			myQ.push_back(b);
			cout<<"("<<ang<<", "<<dis<<")"<<endl;
		/*	if(flag)
			{
				midQ.clear();
				midQ.push_back(b);
				Q.push_back(midQ);
				midQ.clear();
				cout<<"("<<ang<<", "<<dis<<")"<<endl;
			}else
			{
				Q.push_back(midQ);
				cout<<endl;
				midQ.clear();
				midQ.push_back(b);
				Q.push_back(midQ);
				midQ.clear();
				cout<<"("<<ang<<", "<<dis<<")"<<endl;
				flag = true;
			}*/
		}else if(ang>120 && dis<delta)
		{
		//	midQ.push_back(b);
		//	cout<<"("<<ang<<", "<<dis<<"); ";
		//	flag = false;
		}
	}
}
void Process::Compute(Process in)
{
	Point_3 p1,p2,p3,q1,q2,q3;
	Point_3 temp;
	vector<Point_3> after;
	vector<Point_3> changone;
	vector<Point_3> changtwo;
	long double x,y,z;
	Process mid;
	MyCube M;
	this->aaaaa(order_xy);
	changone = myQ;
	this->aaaaa(in.order_xy);
	changtwo = myQ;
	after.clear();
	for(unsigned long j=0; j<changone.size();j++)
	{
		if(j<changone.size()-2)
		{
			p1 = changone.at(j);
			p2 = changone.at(j+1);
			p3 = changone.at(j+2);
		}
		if(j==changone.size()-2)
		{
			p1 = changone.at(j);
			p2 = changone.at(j+1);
			p3 = changone.at(0);
		}
		if(j==changone.size()-1)
		{
			p1 = changone.at(j);
			p2 = changone.at(0);
			p3 = changone.at(1);
		}
	//inner
		for(unsigned long i=0; i<changtwo.size();i++)
	{
		if(i<changtwo.size()-2)
		{
			q1 = changtwo.at(i);
			q2 = changtwo.at(i+1);
			q3 = changtwo.at(i+2);
		}
		if(i==changtwo.size()-2)
		{
			q1 = changtwo.at(i);
			q2 = changtwo.at(i+1);
			q3 = changtwo.at(0);
		}
		if(i==changtwo.size()-1)
		{
			q1 = changtwo.at(i);
			q2 = changtwo.at(0);
			q3 = changtwo.at(1);
		}


		
 M.a = (q3.x*(p1.y*p2.z - p2.y*p1.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) - (q2.x*(p1.y*p3.z - p3.y*p1.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) + (q1.x*(p2.y*p3.z - p3.y*p2.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z);
 M.b = (q2.x*(p1.x*p3.z - p3.x*p1.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) - (q3.x*(p1.x*p2.z - p2.x*p1.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) - (q1.x*(p2.x*p3.z - p3.x*p2.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z);
 M.c = (q3.x*(p1.x*p2.y - p2.x*p1.y))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) - (q2.x*(p1.x*p3.y - p3.x*p1.y))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) + (q1.x*(p2.x*p3.y - p3.x*p2.y))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z);
M.d = (q3.y*(p1.y*p2.z - p2.y*p1.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) - (q2.y*(p1.y*p3.z - p3.y*p1.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) + (q1.y*(p2.y*p3.z - p3.y*p2.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z); 
M.e = (q2.y*(p1.x*p3.z - p3.x*p1.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) - (q3.y*(p1.x*p2.z - p2.x*p1.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) - (q1.y*(p2.x*p3.z - p3.x*p2.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z);
M.f = (q3.y*(p1.x*p2.y - p2.x*p1.y))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) - (q2.y*(p1.x*p3.y - p3.x*p1.y))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) + (q1.y*(p2.x*p3.y - p3.x*p2.y))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z);
M.g = (q3.z*(p1.y*p2.z - p2.y*p1.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) - (q2.z*(p1.y*p3.z - p3.y*p1.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) + (q1.z*(p2.y*p3.z - p3.y*p2.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z);
M.h = (q2.z*(p1.x*p3.z - p3.x*p1.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) - (q3.z*(p1.x*p2.z - p2.x*p1.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) - (q1.z*(p2.x*p3.z - p3.x*p2.z))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z);
M.i = (q3.z*(p1.x*p2.y - p2.x*p1.y))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) - (q2.z*(p1.x*p3.y - p3.x*p1.y))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z) + (q1.z*(p2.x*p3.y - p3.x*p2.y))/(p1.x*p2.y*p3.z - p1.x*p3.y*p2.z - p2.x*p1.y*p3.z + p2.x*p3.y*p1.z + p3.x*p1.y*p2.z - p3.x*p2.y*p1.z);

//	Met.push_back(M);
	char fname[20];
    sprintf(fname,"./after/%d%d.off",j,i);
	//fname = "./after"+std::to_string(i)+".txt";
	ofstream outfile(fname);
	if(!outfile)
	{
		cout<<"can not creat the file"<<fname<<endl;
		//break;
	}else{
		cout<<M.a<<M.b<<M.c<<endl;
		cout<<M.d<<M.e<<M.f<<endl;
		cout<<M.g<<M.h<<M.i<<endl;
		cout<<fname<<" is writting."<<endl;
		outfile<<"OFF "<<endl;
		outfile<<in.PointSet.size()<<" "<<in.PointSet.size()<<endl;
		for(unsigned long j=0; j<in.PointSet.size(); j++)
	{
		x = in.PointSet.at(j).x;
		y = in.PointSet.at(j).y;
		z = in.PointSet.at(j).z;
		temp.x = M.a*x+M.d*y+M.g*z;//M.a*x + M.b*y + M.c*z;
        temp.y = M.b*x+M.e*y+M.h*z;//M.d*x + M.e*y + M.f*z;
        temp.z = M.c*x+M.f*y+M.i*z;//M.g*x + M.h*y + M.i*z;
		outfile<<temp.x<<" "<<temp.y<<" "<<temp.z<<endl;
		//outfile<<x<<" "<<y<<" "<<z<<endl;
	}
		cout<<"finish!"<<endl;
	}
	outfile.close();

//	mid.PointSet = after;
//	mid.ComputeConvex();
//	mid.Output("旋转后的。。。",mid.order_xy);

	}}


}

void Process::Output(string str, vector<Point_3> in)
{
	cout<<str<<endl;
	cout<<"num: "<<in.size()<<endl;
	for(unsigned long i=0;i<in.size();i++)
	{
		cout<<"x: "<<in.at(i).x<<" y: "<<in.at(i).y<<" z: "<<in.at(i).z<<endl;
	}
	cout<<""<<endl;
}

