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
	MyVector vet_;
	int size_;
	sum_x=0;
	sum_y=0;
	sum_z=0;
	PointSet.clear();
	order_xy.clear();
	FaceSet.clear();
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
						//处理面，把三角面的关联点存起来
						if(i_vertex == vertices && i_face < faces)
						{
							int n=0,a=0,b=0,c=0;
							ConvertString(getString,n);
							ConvertString(getString,a);
							ConvertString(getString,b);
							ConvertString(getString,c);
							MyRelation mtemp(a,b,c);
							FaceSet.push_back(mtemp);
							++ i_face;
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
	//去除杂质面的干扰
	for(unsigned long i=0;i<FaceSet.size();++i)
	{
		if(FaceSet.at(i).a >= size_ || FaceSet.at(i).b >= size_ || FaceSet.at(i).c >= size_)
		{
			FaceSet.erase(FaceSet.begin()+i);
			i--;
		}
	}
	sum_x = sum_x/size_;
	sum_y = sum_y/size_;
	sum_z = sum_z/size_;
	cout<<sum_x<<" "<<sum_y<<" "<<sum_z<<endl;
	if(size_>10000000)
	{
		for(unsigned long i=0;i<PointSet.size();i=i+200)
		{
			TempSet.push_back(PointSet.at(i));
		}
		PointSet.clear();
		PointSet = TempSet;
	}
/*	vet_ = ComU(PointSet,FaceSet);
	for(unsigned long i=0;i<PointSet.size();i++)
	{
		PointSet.at(i).x = PointSet.at(i).x - vet_.a;
		PointSet.at(i).y = PointSet.at(i).y - vet_.b;
		PointSet.at(i).z = PointSet.at(i).z - vet_.c;
	}*/
	if(size_<1000)
	for(unsigned long i=0;i<PointSet.size();i++)
	{
		PointSet.at(i).x = PointSet.at(i).x - sum_x;
		PointSet.at(i).y = PointSet.at(i).y - sum_y;
		PointSet.at(i).z = PointSet.at(i).z - sum_z;
	}
//	cout<<sum_x<<" "<<sum_y<<" "<<sum_z<<endl;
//		cout<<vet_.a<<" "<<vet_.b<<" "<<vet_.c<<endl;
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
	MyCube M, M1, obbM;
	long double x,y,z;
	Point_3 temp_;
	long double dx_,dy_,dz_;
	long double dx1_,dy1_,dz1_;
	c1_[2].x = -1;//-0.0003;//0.007;
	c1_[2].y = 0.0001;//0.8766;//0.4813;
	c1_[2].z = 0.0008;//-0.4813;//0.8766;
	c2_[2].x = 0.5510;//0.7962;//-0.2501;
	c2_[2].y = -0.7079;//0.6046;//0.3651;
	c2_[2].z = 0.4418;//-0.7079;//0.8968;
	c1_[1].x = -0.0003;//0.007;
	c1_[1].y = 0.8776;//0.4813;
	c1_[1].z = -0.4793;//0.8766;
	c2_[1].x = 0.7962;//-0.2501;
	c2_[1].y = 0.6045;//0.3651;
	c2_[1].z = -0.0243;//0.8968;
	c1_[0].x = 0.0007;
	c1_[0].y = 0.4793;
	c1_[0].z = 0.8776;
	c2_[0].x = -0.2499;
	c2_[0].y = 0.3652;
	c2_[0].z = 0.8968;

	c2_[1].x = -160.031+18.1125;//-161.126+18.1125;   //A
	c2_[1].y = 115.15-28.7139;//111.696-28.7139;
	c2_[1].z = -61.4471-31.7087;//-61.7108-31.7087;

	c1_[1].x = 181.239+0.619104;   //C
	c1_[1].y = 27857.5-27904.7;
	c1_[1].z = 4994.6-4966.39;
	
	c2_[2].x = 91.0369+18.1125;//80.9495+18.1125 ;   //B
	c2_[2].y = -93.6237-28.7139;//-95.9458-28.7139 ;
	c2_[2].z = 114.821-31.7087;//123.585-31.7087 ;
	
	c1_[2].x = -182+0.619104 ;     //D
	c1_[2].y = 27923-27904.7 ;
	c1_[2].z = 4956.16-4966.39 ;

		c2_[0].x = 39.5827+18.1125;   //E
		c2_[0].y = -143.06-28.7139;
		c2_[0].z = 98.589-31.7087;
	
		c1_[0].x = -181.293+0.619104;     //F
		c1_[0].y = 27857.5-27904.7;
		c1_[0].z = 4994.6-4966.39;

//	for(unsigned long i=0;i<3;++i)
		//for(unsigned long j=0;j<3;++j)
//		{
		M = RotateMet(c1_[2],c1_[1],c2_[2],c2_[1]);
//			M = RotateNew(c1_[2],c1_[1],c2_[2],c2_[1]);
		//	if(i!=2)
		//		M = RotateNew(c1_[i],c1_[i+1],c2_[i],c2_[i+1]);
	
		for(unsigned long j=0; j<3; j++)
		{
		x = c2_[j].x;
		y = c2_[j].y;
		z = c2_[j].z;
		c2_[j].x = M.a*x+M.d*y+M.g*z;//M.a*x + M.b*y + M.c*z;
        c2_[j].y = M.b*x+M.e*y+M.h*z;//M.d*x + M.e*y + M.f*z;
        c2_[j].z = M.c*x+M.f*y+M.i*z;//M.g*x + M.h*y + M.i*z;
//		cout<<c2_[j].x<<" "<<c2_[j].y<<" "<<c2_[j].z<<endl;
		}
		
        //c2_[1].x = c2_[1].x - dx_;

		dx_ = - c2_[1].x + c1_[1].x;
		dy_ = - c2_[1].y + c1_[1].y;
		dz_ = - c2_[1].z + c1_[1].z;
		c2_[1].x += dx_;
		c2_[1].y += dy_;
		c2_[1].z += dz_;
		c2_[2].x += dx_;
		c2_[2].y += dy_;
		c2_[2].z += dz_;
		c2_[0].x += dx_;
		c2_[0].y += dy_;
		c2_[0].z += dz_;

		cout<<c2_[1].x<<" "<<c2_[1].y<<" "<<c2_[1].z<<endl;
		cout<<c2_[2].x<<" "<<c2_[2].y<<" "<<c2_[2].z<<endl;
		cout<<c2_[0].x<<" "<<c2_[0].y<<" "<<c2_[0].z<<endl;

		cout<<c1_[1].x<<" "<<c1_[1].y<<" "<<c1_[1].z<<endl;
		cout<<c1_[2].x<<" "<<c1_[2].y<<" "<<c1_[2].z<<endl;
		cout<<c1_[0].x<<" "<<c1_[0].y<<" "<<c1_[0].z<<endl;


		M1 = RotateMeet(c2_[1],c2_[2],c2_[0],c1_[0]);
		for(unsigned long j=0; j<1; j++)
		{
		x = c2_[j].x;
		y = c2_[j].y;
		z = c2_[j].z;
		c2_[j].x = M1.a*x+M1.d*y+M1.g*z;//M.a*x + M.b*y + M.c*z;
        c2_[j].y = M1.b*x+M1.e*y+M1.h*z;//M.d*x + M.e*y + M.f*z;
        c2_[j].z = M1.c*x+M1.f*y+M1.i*z;//M.g*x + M.h*y + M.i*z;
//		cout<<c2_[j].x<<" "<<c2_[j].y<<" "<<c2_[j].z<<endl;
		}

/*		dx1_ = - c2_[1].x + c1_[1].x;
		dy1_ = - c2_[1].y + c1_[1].y;
		dz1_ = - c2_[1].z + c1_[1].z;
		c2_[1].x += dx1_;
		c2_[1].y += dy1_;
		c2_[1].z += dz1_;
		c2_[2].x += dx1_;
		c2_[2].y += dy1_;
		c2_[2].z += dz1_;
		c2_[0].x += dx1_;
		c2_[0].y += dy1_;
		c2_[0].z += dz1_;*/


/*			char fname[30];
    sprintf(fname,"./after/new7.off");
			ofstream outfile(fname);
	if(!outfile)
	{
		cout<<"can not creat the file"<<endl;
		//break;
	}else{
		cout<<"test.off is writting."<<endl;
		outfile<<"OFF "<<endl;
		outfile<<in.PointSet.size()<<" "<<in.PointSet.size()<<endl;
//		cout<<dx_<<" "<<dy_<<" "<<dz_<<endl;
		for(unsigned long j=0; j<in.PointSet.size(); j++)
		{
		x = in.PointSet.at(j).x;
		y = in.PointSet.at(j).y;
		z = in.PointSet.at(j).z;
		temp_.x = M.a*x+M.d*y+M.g*z ;//M.a*x + M.b*y + M.c*z;
        temp_.y = M.b*x+M.e*y+M.h*z ;//M.d*x + M.e*y + M.f*z;
        temp_.z = M.c*x+M.f*y+M.i*z ;//M.g*x + M.h*y + M.i*z;
		temp_.x += dx_;
		temp_.y += dy_;
		temp_.z += dz_;
		x = temp_.x;
		y = temp_.y;
		z = temp_.z;
		temp_.x = M1.a*x+M1.d*y+M1.g*z;//M.a*x + M.b*y + M.c*z;
        temp_.y = M1.b*x+M1.e*y+M1.h*z;//M.d*x + M.e*y + M.f*z;
        temp_.z = M1.c*x+M1.f*y+M1.i*z;//M.g*x + M.h*y + M.i*z;
		temp_.x += dx1_;
		temp_.y += dy1_;
		temp_.z += dz1_;
		outfile<<temp_.x<<" "<<temp_.y<<" "<<temp_.z<<endl;
		//outfile<<x<<" "<<y<<" "<<z<<endl;
		}
		cout<<"finish!"<<endl;
	}
	outfile.close();*/
	//	}
	//	obbM = OBBMet(PointSet,FaceSet);
//	M = OBBMet(in.PointSet,in.FaceSet);
/*	ofstream outfile("./after/test.off");
	if(!outfile)
	{
		cout<<"can not creat the file"<<endl;
		//break;
	}else{
		cout<<M.a<<M.b<<M.c<<endl;
		cout<<M.d<<M.e<<M.f<<endl;
		cout<<M.g<<M.h<<M.i<<endl;
		cout<<"test.off is writting."<<endl;
		outfile<<"OFF "<<endl;
		outfile<<in.PointSet.size()<<" "<<in.PointSet.size()<<endl;
		for(unsigned long j=0; j<in.PointSet.size(); j++)
		{
		x = in.PointSet.at(j).x;
		y = in.PointSet.at(j).y;
		z = in.PointSet.at(j).z;
		temp_.x = M.a*x+M.d*y+M.g*z;//M.a*x + M.b*y + M.c*z;
        temp_.y = M.b*x+M.e*y+M.h*z;//M.d*x + M.e*y + M.f*z;
        temp_.z = M.c*x+M.f*y+M.i*z;//M.g*x + M.h*y + M.i*z;
		outfile<<temp_.x<<" "<<temp_.y<<" "<<temp_.z<<endl;
		//outfile<<x<<" "<<y<<" "<<z<<endl;
		}
		cout<<"finish!"<<endl;
	}
	outfile.close();*/
//cout<<M.a<<" "<<M.b<<" "<<M.c<<endl;
//		cout<<M.d<<" "<<M.e<<" "<<M.f<<endl;
//		cout<<M.g<<" "<<M.h<<" "<<M.i<<endl;

}

MyCube Process::RotateNew(Point_3 _i1, Point_3 _i2, Point_3 _j1, Point_3 _j2)
{
	MyVector v1_,v2_,v_;
	MyCube met_,met1_,met2_;
	float angle,temp;
	float x,y,z;
	v1_.a = _i1.x;
	v1_.b = _i1.y;
	v1_.c = _i1.z;
	v2_.a = _j1.x;
	v2_.b = _j1.y;
	v2_.c = _j1.z;
	temp = v1_.mod()*v2_.mod();
//	cout<<temp<<endl;
	if(temp != 0)
		angle = acos(v1_.dot(v2_)/temp);
	else
		angle = PI/2;
	v_ = (v1_.plus(v2_));
	v_.unit();
	met_.a = cos(angle) + v_.a*v_.a*(1-cos(angle));
	met_.b = v_.a*v_.b*(1-cos(angle))-v_.c*sin(angle);
	met_.c = v_.b*sin(angle)+v_.a*v_.c*(1-cos(angle));

	met_.d = v_.c*sin(angle) + v_.a*v_.b*(1-cos(angle));
	met_.e = cos(angle) + v_.b*v_.b*(1-cos(angle));
	met_.f = v_.b*v_.c*(1-cos(angle))-v_.a*sin(angle);

	met_.g = v_.a*v_.c*(1-cos(angle))-v_.b*sin(angle);
	met_.h = v_.a*sin(angle) + v_.b*v_.c*(1-cos(angle));
	met_.i = cos(angle) + v_.c*v_.c*(1-cos(angle));

	x = _j2.x;
	y = _j2.y;
	z = _j2.z;
	v2_.a = met_.a*x+met_.d*y+met_.g*z;//M.a*x + M.b*y + M.c*z;
    v2_.b = met_.b*x+met_.e*y+met_.h*z;//M.d*x + M.e*y + M.f*z;
    v2_.c = met_.c*x+met_.f*y+met_.i*z;
	v1_.a = _i2.x;
	v1_.b = _i2.y;
	v1_.c = _i2.z;
	temp = v1_.mod()*v2_.mod();
	if(temp != 0)
		angle = acos(v1_.dot(v2_)/temp);
	else
		angle = PI/2;
	v_ = (v1_.plus(v2_));
//	v_.a = _i1.x;//
//	v_.b = _i1.y;
//	v_.c = _i1.z;
	v_.unit();
    met1_.a = cos(angle) + v_.a*v_.a*(1-cos(angle));
	met1_.b = v_.a*v_.b*(1-cos(angle))-v_.c*sin(angle);
	met1_.c = v_.b*sin(angle)+v_.a*v_.c*(1-cos(angle));

	met1_.d = v_.c*sin(angle) + v_.a*v_.b*(1-cos(angle));
	met1_.e = cos(angle) + v_.b*v_.b*(1-cos(angle));
	met1_.f = v_.b*v_.c*(1-cos(angle))-v_.a*sin(angle);

	met1_.g = v_.a*v_.c*(1-cos(angle))-v_.b*sin(angle);
	met1_.h = v_.a*sin(angle) + v_.b*v_.c*(1-cos(angle));
	met1_.i = cos(angle) + v_.c*v_.c*(1-cos(angle));

/*	met2_.a = met1_.a*met_.a+met1_.b*met_.d+met1_.c*met_.g;
	met2_.b = met1_.a*met_.b+met1_.b*met_.e+met1_.c*met_.h;
	met2_.c = met1_.a*met_.c+met1_.b*met_.f+met1_.c*met_.i;

	met2_.d = met1_.d*met_.a+met1_.e*met_.d+met1_.f*met_.g;
	met2_.e = met1_.d*met_.b+met1_.e*met_.e+met1_.f*met_.h;
	met2_.f = met1_.d*met_.c+met1_.e*met_.f+met1_.f*met_.i;

	met2_.g = met1_.g*met_.a+met1_.h*met_.d+met1_.i*met_.g;
	met2_.h = met1_.g*met_.b+met1_.h*met_.e+met1_.i*met_.h;
	met2_.i = met1_.g*met_.c+met1_.h*met_.f+met1_.i*met_.i;
*/
	met2_.a = met_.a*met1_.a+met_.b*met1_.d+met_.c*met1_.g;
	met2_.b = met_.a*met1_.b+met_.b*met1_.e+met_.c*met1_.h;
	met2_.c = met_.a*met1_.c+met_.b*met1_.f+met_.c*met1_.i;

	met2_.d = met_.d*met1_.a+met_.e*met1_.d+met_.f*met1_.g;
	met2_.e = met_.d*met1_.b+met_.e*met1_.e+met_.f*met1_.h;
	met2_.f = met_.d*met1_.c+met_.e*met1_.f+met_.f*met1_.i;

	met2_.g = met_.g*met1_.a+met_.h*met1_.d+met_.i*met1_.g;
	met2_.h = met_.g*met1_.b+met_.h*met1_.e+met_.i*met1_.h;
	met2_.i = met_.g*met1_.c+met_.h*met1_.f+met_.i*met1_.i;


	return met2_;

}


MyCube Process::RotateMet(Point_3 _i1, Point_3 _i2, Point_3 _j1, Point_3 _j2)
{
	MyVector v1_,v2_,v_;
	MyCube met_;
	float angle,temp;
	v1_.a = _i1.x-_i2.x;
	v1_.b = _i1.y-_i2.y;
	v1_.c = _i1.z-_i2.z;
	v2_.a = _j1.x-_j2.x;
	v2_.b = _j1.y-_j2.y;
	v2_.c = _j1.z-_j2.z;
	temp = v1_.mod()*v2_.mod();
	if(temp != 0)
		angle = acos(v1_.dot(v2_)/temp);
	else
		angle = PI/2;
	v_ = (v1_.plus(v2_));
	v_.unit();
	met_.a = cos(angle) + v_.a*v_.a*(1-cos(angle));
	met_.b = v_.a*v_.b*(1-cos(angle))-v_.c*sin(angle);
	met_.c = v_.b*sin(angle)+v_.a*v_.c*(1-cos(angle));

	met_.d = v_.c*sin(angle) + v_.a*v_.b*(1-cos(angle));
	met_.e = cos(angle) + v_.b*v_.b*(1-cos(angle));
	met_.f = v_.b*v_.c*(1-cos(angle))-v_.a*sin(angle);

	met_.g = v_.a*v_.c*(1-cos(angle))-v_.b*sin(angle);
	met_.h = v_.a*sin(angle) + v_.b*v_.c*(1-cos(angle));
	met_.i = cos(angle) + v_.c*v_.c*(1-cos(angle));

	return met_;

}

MyCube Process::RotateMeet(Point_3 _A, Point_3 _B, Point_3 _C, Point_3 _D)
{
	MyVector axis;
	MyCube met_;
	MyVector ac,bc,ad,bd;
	float angle,temp;
	axis.a = _A.x - _B.x;
	axis.b = _A.y - _B.y;
	axis.c = _A.z - _B.z;
	axis.unit();
//	cout<<axis.a<<" "<<axis.b<<" "<<axis.c<<endl;
	ac.a = _C.x - _A.x;
	ac.b = _C.y - _A.y;
	ac.c = _C.z - _A.z;
	
	bc.a = _C.x - _B.x;
	bc.b = _C.y - _B.y;
	bc.c = _C.z - _B.z;

	ad.a = _D.x - _A.x;
	ad.b = _D.y - _A.y;
	ad.c = _D.z - _A.z;

	bd.a = _D.x - _B.x;
	bd.b = _D.y - _B.y;
	bd.c = _D.z - _B.z;

	temp = (ac.plus(bc)).mod()*(ad.plus(bd)).mod();
	if(temp == 0)
	{
		angle = 0;
	}else{
	angle = acos(((ac.plus(bc)).dot(ad.plus(bd)))/temp);
	}
	
	met_.a = cos(angle) + axis.a*axis.a*(1-cos(angle));
	met_.b = axis.a*axis.b*(1-cos(angle))-axis.c*sin(angle);
	met_.c = axis.b*sin(angle)+axis.a*axis.c*(1-cos(angle));

	met_.d = axis.c*sin(angle) + axis.a*axis.b*(1-cos(angle));
	met_.e = cos(angle) + axis.b*axis.b*(1-cos(angle));
	met_.f = axis.b*axis.c*(1-cos(angle))-axis.a*sin(angle);

	met_.g = axis.a*axis.c*(1-cos(angle))-axis.b*sin(angle);
	met_.h = axis.a*sin(angle) + axis.b*axis.c*(1-cos(angle));
	met_.i = cos(angle) + axis.c*axis.c*(1-cos(angle));

	return met_;

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

MyVector Process::ComU(vector<Point_3> point, vector<MyRelation> face)
{
	MyVector vet_;
	int faceNum;
	int pointNum;
	int p_,q_,r_;
	float x_,y_,z_;
	x_=y_=z_=0;
	faceNum = face.size();
	pointNum = point.size();
	//cout<<faceNum<<endl;
	for(int i=0;i<faceNum;++i)
	{
		p_ = face.at(i).a;
		q_ = face.at(i).b;
		r_ = face.at(i).c;
		x_ = x_ + point.at(p_).x+point.at(q_).x+point.at(r_).x;
		y_ = y_ + point.at(p_).y+point.at(q_).y+point.at(r_).y;
		z_ = z_ + point.at(p_).z+point.at(q_).z+point.at(r_).z;
	}
	vet_.a = x_ / (3*faceNum);
	vet_.b = y_ / (3*faceNum);
	vet_.c = z_ / (3*faceNum);
	return vet_;

}
MyCube Process::OBBMet(vector<Point_3> point, vector<MyRelation> face)
{
	MyCube mCMet(0,0,0,0,0,0,0,0,0);
	int faceNum;
	int pointNum;
	int p_,q_,r_;
	faceNum = face.size();
	pointNum = point.size();
	//cout<<faceNum<<endl;
	for(int i=0;i<faceNum;++i)
	{
		p_ = face.at(i).a;
		q_ = face.at(i).b;
		r_ = face.at(i).c;
		cout<<i<<": "<<p_<<" "<<q_<<" "<<r_<<" "<<faceNum<<endl;
		mCMet.a = mCMet.a + point.at(p_).x*point.at(p_).x + point.at(q_).x*point.at(q_).x + point.at(r_).x*point.at(r_).x;
		mCMet.b = mCMet.b + point.at(p_).x*point.at(p_).y + point.at(q_).x*point.at(q_).y + point.at(r_).x*point.at(r_).y;
		mCMet.c = mCMet.c + point.at(p_).x*point.at(p_).z + point.at(q_).x*point.at(q_).z + point.at(r_).x*point.at(r_).z;
		mCMet.e = mCMet.e + point.at(p_).y*point.at(p_).y + point.at(q_).y*point.at(q_).y + point.at(r_).y*point.at(r_).y;
        mCMet.f = mCMet.f + point.at(p_).y*point.at(p_).z + point.at(q_).y*point.at(q_).z + point.at(r_).y*point.at(r_).z;
		mCMet.i = mCMet.i + point.at(p_).z*point.at(p_).z + point.at(q_).z*point.at(q_).z + point.at(r_).z*point.at(r_).z;
	}
	mCMet.a = mCMet.a/(3*faceNum);
	mCMet.b = mCMet.b/(3*faceNum);
	mCMet.c = mCMet.c/(3*faceNum);
	mCMet.d = mCMet.b;
	mCMet.e = mCMet.e/(3*faceNum);
	mCMet.f = mCMet.f/(3*faceNum);
	mCMet.g = mCMet.c;
	mCMet.h = mCMet.f;
	mCMet.i = mCMet.i/(3*faceNum);

	return mCMet;
}



