#include "morphing.h"

Morphing::Morphing()
{
	
}

Morphing::~Morphing()
{
}

void Morphing::Init(float *a,int fn)
{
	Origface.clear();
	Targface.clear();
	r = a[0];
	R = a[0]+a[1];
	diff = a[1];
	h = a[2];
	int temp =(int)(a[3]*10);
	ComK(temp);	
	if(fn == 6)
	{
		x = a[4];
		y = a[5];
		ext = 0;
		roll = 0;
		SetLocation();
		if(diff == 0)
		{
			DrawOne();
		}else
		{
			DrawTwo();
		}
	}else if(fn == 5)
	{
		x = 0;
		y = 0;
		ext = a[4];
		roll = 0;
		SetLocation();
		DrawThr();
	}else if(fn == 7)
	{
		roll = a[4]*PI/180;
		RollLocation();
		DrawFor();
		//TestDraw();
	}
	Bottom(fn);

}

void Morphing::ComK(int b)
{
	if(b==0)
	{
		k = 4;
	}else if(b==7){
		k=72;
	}else{
		k = 10*b;
	}
}

void Morphing::RollLocation()
{
	MyPoint temp;
	bup.clear();
	aup.clear();
	down.clear();
	for(int i=0;i<=k;i++)
	{
		float arc;
		arc = 2*PI/k;
		temp.x = r*cos(arc*i);
		temp.y = r*sin(arc*i);
		temp.z = h/2;
		bup.append(temp);
		temp.x = r*cos(arc*i)*cos(roll);
		temp.y = r*sin(arc*i);		
		temp.z = h/2-r*cos(arc*i)*sin(roll);
		aup.append(temp);
		temp.x = R*cos(arc*i);
		temp.y = R*sin(arc*i);
		temp.z = -h/2;
		down.append(temp);
	}
}

void Morphing::SetLocation()
{
	MyPoint temp;
	bup.clear();
	aup.clear();
	down.clear();
	for(int i=0;i<=k;i++)
	{
		float arc;
		arc = 2*PI/k;
		temp.x = r*cos(arc*i);
		temp.y = r*sin(arc*i);
		temp.z = h/2;
		bup.append(temp);
		temp.x = r*cos(arc*i)+x;
		temp.y = r*sin(arc*i)+y;
		temp.z = h/2+ext;
		aup.append(temp);
		temp.x = R*cos(arc*i);
		temp.y = R*sin(arc*i);
		temp.z = -h/2;
		down.append(temp);
	}
}

void Morphing::TestDraw()
{
	MyFace temp_face;
	MySide side;
	Targface.clear();
	for(int i=0;i<k;i++)
	{	
		side.Mybegin = aup.at(i);
		side.Myend = aup.at(i+1);
		temp_face.side.append(side);
		side.Mybegin = aup.at(i+1);
		side.Myend = down.at(i+1);
		temp_face.side.append(side);
		side.Mybegin = down.at(i+1);
		side.Myend = down.at(i);
		temp_face.side.append(side);
		side.Mybegin = down.at(i);
		side.Myend = aup.at(i);
		temp_face.side.append(side);
		temp_face.type = 8;
		Targface.append(temp_face);
		temp_face.side.clear();
	}
}

void Morphing::DrawOne()
{
	float d;
	MyFace temp_face;
	MySide side;
	Origface.clear();
	Targface.clear();
	//上边两点C,D
	MyPoint point_c;
	MyPoint point_d;
	//下边两点A,B
	MyPoint point_a;
	MyPoint point_b;
	//上边移动后两点E',F'
	MyPoint point_e;
	MyPoint point_f;
	//存储计算出的M,M1,M2,N,N1,N2
	MyPoint M[6];
	MyPoint OM,ON,OC,OD;
	//角MAB的弧度
	float angle_mab;
	//AB,AM,BN,AM1，AM2，BN1，BN2,AE'边长度
	float l_ab,l_am,l_bn,l_am1,l_am2,l_bn2,l_bn1,l_ae;
	//用于计算M,M1,M2,N,N1,N2点坐标的比例值,例如AM/AE'
	float v[3],u[3],ov,ou;
	//判断移动方向和侧边AB向量的方向
	float dir;
	for(int i=0;i<k;i++)
	{
		point_c = bup.at(i);
		point_d = bup.at(i+1);
		point_a = down.at(i);
		point_b = down.at(i+1);
		point_e = aup.at(i);
		point_f = aup.at(i+1);
		dir = x*(point_b.x-point_a.x)+y*(point_b.y-point_a.y);
		//平移后边E'F'与原边CD之间的距离
		d = ((point_d.x-point_c.x)*y-(point_d.y-point_c.y)*x)
			/sqrt((point_d.x-point_c.x)*(point_d.x-point_c.x)
				+(point_d.y-point_c.y)*(point_d.y-point_c.y));
		angle_mab = PI/2-atan2(sqrt(x*x+y*y-d*d),sqrt(h*h+d*d));
		l_ab = point_a.dis(point_b);
		l_ae = point_a.dis(point_e);
	if(dir>=0)
	{
		l_am = l_ab*cos(angle_mab);
		v[0] = l_am/l_ae;
		l_bn = sqrt(x*x+y*y+h*h)-l_am;
		u[0] = l_bn/l_ae;
		l_am1 = l_am+(l_bn-h)/2;
		v[1] = l_am1/l_ae;
		l_am2 = l_am+(l_bn+h)/2;
		v[2] = l_am2/l_ae;
		l_bn2 = (l_bn-h)/2;
		u[2] = l_bn2/l_ae;
		l_bn1 = (l_bn+h)/2;
		u[1] = l_bn1/l_ae;
		if(l_bn-h>0)
		{
					
			for(int i=0;i<3;i++)
			{
				M[i].x = v[i]*(point_e.x-point_a.x)+point_a.x;
				M[i].y = v[i]*(point_e.y-point_a.y)+point_a.y;
				M[i].z = v[i]*(point_e.z-point_a.z)+point_a.z;
				M[i+3].x = u[i]*(point_f.x-point_b.x)+point_b.x;
				M[i+3].y = u[i]*(point_f.y-point_b.y)+point_b.y;
				M[i+3].z = u[i]*(point_f.z-point_b.z)+point_b.z;
			}
			//面ABM
			side.Mybegin = point_a;
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = M[0];
			temp_face.side.append(side);
			side.Mybegin = M[0];
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 1;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面MBN2M1
			side.Mybegin = M[0];
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = M[5];
			temp_face.side.append(side);
			side.Mybegin = M[5];
			side.Myend = M[1];
			temp_face.side.append(side);
			side.Mybegin = M[1];
			side.Myend = M[0];
			temp_face.side.append(side);
			temp_face.type = 2;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面M1N2N1M2
			side.Mybegin = M[1];
			side.Myend = M[5];
			temp_face.side.append(side);
			side.Mybegin = M[5];
			side.Myend = M[4];
			temp_face.side.append(side);
			side.Mybegin = M[4];
			side.Myend = M[2];
			temp_face.side.append(side);
			side.Mybegin = M[2];
			side.Myend = M[1];
			temp_face.side.append(side);
			temp_face.type = 0;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面M2N1NE'
			side.Mybegin = M[2];
			side.Myend = M[4];
			temp_face.side.append(side);
			side.Mybegin = M[4];
			side.Myend = M[3];
			temp_face.side.append(side);
			side.Mybegin = M[3];
			side.Myend = point_e;
			temp_face.side.append(side);
			side.Mybegin = point_e;
			side.Myend = M[2];
			temp_face.side.append(side);
			temp_face.type = 2;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面EN3F
			side.Mybegin = point_e;
			side.Myend = M[3];
			temp_face.side.append(side);
			side.Mybegin = M[3];
			side.Myend = point_f;
			temp_face.side.append(side);
			side.Mybegin = point_f;
			side.Myend = point_e;
			temp_face.side.append(side);
			temp_face.type = 1;
			Targface.append(temp_face);
			temp_face.side.clear();
			//////////////////////////////////////////////////////////
			ov = (l_ab*sin(angle_mab))/l_ab;
			OM.x = ov*(point_b.x-point_a.x)+point_a.x;
			OM.y = ov*(point_b.y-point_a.y)+point_a.y;
			OM.z = ov*(point_b.z-point_a.z)+point_a.z;
			ON.x = ov*(point_d.x-point_c.x)+point_c.x;
			ON.y = ov*(point_d.y-point_c.y)+point_c.y;
			ON.z = ov*(point_d.z-point_c.z)+point_c.z;
			//面AOMONC
			side.Mybegin = point_a;
			side.Myend = OM;
			temp_face.side.append(side);
			side.Mybegin = OM;
			side.Myend = ON;
			temp_face.side.append(side);
			side.Mybegin = ON;
			side.Myend = point_c;
			temp_face.side.append(side);
			side.Mybegin = point_c;
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 0;
			Origface.append(temp_face);
			temp_face.side.clear();
			//面ONOMBD
			side.Mybegin = ON;
			side.Myend = OM;
			temp_face.side.append(side);
			side.Mybegin = OM;
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = point_d;
			temp_face.side.append(side);
			side.Mybegin = point_d;
			side.Myend = ON;
			temp_face.side.append(side);
			temp_face.type = 4;
			Origface.append(temp_face);
			temp_face.side.clear();
			//////////////////////////////////////////////////////////
		}else
		{
			M[0].x = v[0]*(point_e.x-point_a.x)+point_a.x;
			M[0].y = v[0]*(point_e.y-point_a.y)+point_a.y;
			M[0].z = v[0]*(point_e.z-point_a.z)+point_a.z;
			M[3].x = u[0]*(point_f.x-point_b.x)+point_b.x;
			M[3].y = u[0]*(point_f.y-point_b.y)+point_b.y;
			M[3].z = u[0]*(point_f.z-point_b.z)+point_b.z;
			//面ABM
			side.Mybegin = point_a;
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = M[0];
			temp_face.side.append(side);
			side.Mybegin = M[0];
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 1;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面MBNE'
			side.Mybegin = M[0];
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = M[3];
			temp_face.side.append(side);
			side.Mybegin = M[3];
			side.Myend = point_e;
			temp_face.side.append(side);
			side.Mybegin = point_e;
			side.Myend = M[0];
			temp_face.side.append(side);
			temp_face.type = 0;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面EN3F
			side.Mybegin = point_e;
			side.Myend = M[3];
			temp_face.side.append(side);
			side.Mybegin = M[3];
			side.Myend = point_f;
			temp_face.side.append(side);
			side.Mybegin = point_f;
			side.Myend = point_e;
			temp_face.side.append(side);
			temp_face.type = 1;
			Targface.append(temp_face);
			temp_face.side.clear();
			//////////////////////////////////////////////////////////
			ov = (l_ab*sin(angle_mab))/l_ab;
			OM.x = ov*(point_b.x-point_a.x)+point_a.x;
			OM.y = ov*(point_b.y-point_a.y)+point_a.y;
			OM.z = ov*(point_b.z-point_a.z)+point_a.z;
			ON.x = ov*(point_d.x-point_c.x)+point_c.x;
			ON.y = ov*(point_d.y-point_c.y)+point_c.y;
			ON.z = ov*(point_d.z-point_c.z)+point_c.z;
			ou = M[0].dis(point_e)/h;
			OC.x = ou*(point_c.x-point_a.x)+point_a.x;
			OC.y = ou*(point_c.y-point_a.y)+point_a.y;
			OC.z = ou*(point_c.z-point_a.z)+point_a.z;
			OD.x = ou*(point_d.x-point_b.x)+point_b.x;
			OD.y = ou*(point_d.y-point_b.y)+point_b.y;
			OD.z = ou*(point_d.z-point_b.z)+point_b.z;
			MyPoint aaa;
			aaa.x = ov*(OD.x-OC.x)+OC.x;
			aaa.y = ov*(OD.y-OC.y)+OC.y;
			aaa.z = ov*(OD.z-OC.z)+OC.z;
			//面AOMaaaOC
			side.Mybegin = point_a;
			side.Myend = OM;
			temp_face.side.append(side);
			side.Mybegin = OM;
			side.Myend = aaa;
			temp_face.side.append(side);
			side.Mybegin = aaa;
			side.Myend = OC;
			temp_face.side.append(side);
			side.Mybegin = OC;
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 0;
			Origface.append(temp_face);
			temp_face.side.clear();
			//面OCaaaONC
			side.Mybegin = OC;
			side.Myend = aaa;
			temp_face.side.append(side);
			side.Mybegin = aaa;
			side.Myend = ON;
			temp_face.side.append(side);
			side.Mybegin = ON;
			side.Myend = point_c;
			temp_face.side.append(side);
			side.Mybegin = point_c;
			side.Myend = OC;
			temp_face.side.append(side);
			temp_face.type = 4;
			Origface.append(temp_face);
			temp_face.side.clear();
			//面ONOMBD
			side.Mybegin = ON;
			side.Myend = OM;
			temp_face.side.append(side);
			side.Mybegin = OM;
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = point_d;
			temp_face.side.append(side);
			side.Mybegin = point_d;
			side.Myend = ON;
			temp_face.side.append(side);
			temp_face.type = 4;
			Origface.append(temp_face);
			temp_face.side.clear();
			//////////////////////////////////////////////////////////
		}
	}else{
		l_bn = l_ab*cos(angle_mab);
		u[0] = l_bn/l_ae;
		l_am = sqrt(x*x+y*y+h*h)-l_bn;
		v[0] = l_am/l_ae;
		l_am1 = (l_am+h)/2;
		v[1] = l_am1/l_ae;
		l_am2 = (l_am-h)/2;
		v[2] = l_am2/l_ae;
		l_bn2 = l_bn+(l_am+h)/2;
		u[2] = l_bn2/l_ae;
		l_bn1 = l_bn+(l_am-h)/2;
		u[1] = l_bn1/l_ae;
		if(l_am-h>0)
		{
					
			for(int i=0;i<3;i++)
			{
				M[i].x = v[i]*(point_e.x-point_a.x)+point_a.x;
				M[i].y = v[i]*(point_e.y-point_a.y)+point_a.y;
				M[i].z = v[i]*(point_e.z-point_a.z)+point_a.z;
				M[i+3].x = u[i]*(point_f.x-point_b.x)+point_b.x;
				M[i+3].y = u[i]*(point_f.y-point_b.y)+point_b.y;
				M[i+3].z = u[i]*(point_f.z-point_b.z)+point_b.z;
			}
			//面ABN
			side.Mybegin = point_a;
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = M[3];
			temp_face.side.append(side);
			side.Mybegin = M[3];
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 1;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面ANN1M2
			side.Mybegin = point_a;
			side.Myend = M[3];
			temp_face.side.append(side);
			side.Mybegin = M[3];
			side.Myend = M[4];
			temp_face.side.append(side);
			side.Mybegin = M[4];
			side.Myend = M[2];
			temp_face.side.append(side);
			side.Mybegin = M[2];
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 2;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面M2N1N2M1
			side.Mybegin = M[2];
			side.Myend = M[4];
			temp_face.side.append(side);
			side.Mybegin = M[4];
			side.Myend = M[5];
			temp_face.side.append(side);
			side.Mybegin = M[5];
			side.Myend = M[1];
			temp_face.side.append(side);
			side.Mybegin = M[1];
			side.Myend = M[2];
			temp_face.side.append(side);
			temp_face.type = 0;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面M1N2F'M
			side.Mybegin = M[1];
			side.Myend = M[5];
			temp_face.side.append(side);
			side.Mybegin = M[5];
			side.Myend = point_f;
			temp_face.side.append(side);
			side.Mybegin = point_f;
			side.Myend = M[0];
			temp_face.side.append(side);
			side.Mybegin = M[0];
			side.Myend = M[1];
			temp_face.side.append(side);
			temp_face.type = 2;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面MF'E'
			side.Mybegin = M[0];
			side.Myend = point_f;
			temp_face.side.append(side);
			side.Mybegin = point_f;
			side.Myend = point_e;
			temp_face.side.append(side);
			side.Mybegin = point_e;
			side.Myend = point_f;
			temp_face.side.append(side);
			temp_face.type = 1;
			Targface.append(temp_face);
			temp_face.side.clear();
			//////////////////////////////////////////////////////////
			ov = (l_ab*sin(angle_mab))/l_ab;
			OM.x = ov*(point_b.x-point_a.x)+point_a.x;
			OM.y = ov*(point_b.y-point_a.y)+point_a.y;
			OM.z = ov*(point_b.z-point_a.z)+point_a.z;
			ON.x = ov*(point_d.x-point_c.x)+point_c.x;
			ON.y = ov*(point_d.y-point_c.y)+point_c.y;
			ON.z = ov*(point_d.z-point_c.z)+point_c.z;
			//面AOMONC
			side.Mybegin = point_a;
			side.Myend = OM;
			temp_face.side.append(side);
			side.Mybegin = OM;
			side.Myend = ON;
			temp_face.side.append(side);
			side.Mybegin = ON;
			side.Myend = point_c;
			temp_face.side.append(side);
			side.Mybegin = point_c;
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 0;
			Origface.append(temp_face);
			temp_face.side.clear();
			//面ONOMBD
			side.Mybegin = ON;
			side.Myend = OM;
			temp_face.side.append(side);
			side.Mybegin = OM;
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = point_d;
			temp_face.side.append(side);
			side.Mybegin = point_d;
			side.Myend = ON;
			temp_face.side.append(side);
			temp_face.type = 4;
			Origface.append(temp_face);
			temp_face.side.clear();
			//////////////////////////////////////////////////////////
		}else
		{
			M[0].x = v[0]*(point_e.x-point_a.x)+point_a.x;
			M[0].y = v[0]*(point_e.y-point_a.y)+point_a.y;
			M[0].z = v[0]*(point_e.z-point_a.z)+point_a.z;
			M[3].x = u[0]*(point_f.x-point_b.x)+point_b.x;
			M[3].y = u[0]*(point_f.y-point_b.y)+point_b.y;
			M[3].z = u[0]*(point_f.z-point_b.z)+point_b.z;
			//面ABN
			side.Mybegin = point_a;
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = M[3];
			temp_face.side.append(side);
			side.Mybegin = M[3];
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 1;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面ANF'M
			side.Mybegin = point_a;
			side.Myend = M[3];
			temp_face.side.append(side);
			side.Mybegin = M[3];
			side.Myend = point_f;
			temp_face.side.append(side);
			side.Mybegin = point_f;
			side.Myend = M[0];
			temp_face.side.append(side);
			side.Mybegin = M[0];
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 0;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面MF'E'
			side.Mybegin = M[0];
			side.Myend = point_f;
			temp_face.side.append(side);
			side.Mybegin = point_f;
			side.Myend = point_e;
			temp_face.side.append(side);
			side.Mybegin = point_e;
			side.Myend = M[0];
			temp_face.side.append(side);
			temp_face.type = 1;
			Targface.append(temp_face);
			temp_face.side.clear();
			//////////////////////////////////////////////////////////
			ov = (l_ab*sin(angle_mab))/l_ab;
			OM.x = ov*(point_b.x-point_a.x)+point_a.x;
			OM.y = ov*(point_b.y-point_a.y)+point_a.y;
			OM.z = ov*(point_b.z-point_a.z)+point_a.z;
			ON.x = ov*(point_d.x-point_c.x)+point_c.x;
			ON.y = ov*(point_d.y-point_c.y)+point_c.y;
			ON.z = ov*(point_d.z-point_c.z)+point_c.z;
			ou = M[3].dis(point_f)/h;
			OC.x = ou*(point_c.x-point_a.x)+point_a.x;
			OC.y = ou*(point_c.y-point_a.y)+point_a.y;
			OC.z = ou*(point_c.z-point_a.z)+point_a.z;
			OD.x = ou*(point_d.x-point_b.x)+point_b.x;
			OD.y = ou*(point_d.y-point_b.y)+point_b.y;
			OD.z = ou*(point_d.z-point_b.z)+point_b.z;
			MyPoint aaa;
			aaa.x = ov*(OD.x-OC.x)+OC.x;
			aaa.y = ov*(OD.y-OC.y)+OC.y;
			aaa.z = ov*(OD.z-OC.z)+OC.z;
			//面AOMaaaOC
			side.Mybegin = point_a;
			side.Myend = OM;
			temp_face.side.append(side);
			side.Mybegin = OM;
			side.Myend = aaa;
			temp_face.side.append(side);
			side.Mybegin = aaa;
			side.Myend = OC;
			temp_face.side.append(side);
			side.Mybegin = OC;
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 0;
			Origface.append(temp_face);
			temp_face.side.clear();
			//面OCaaaONC
			side.Mybegin = OC;
			side.Myend = aaa;
			temp_face.side.append(side);
			side.Mybegin = aaa;
			side.Myend = ON;
			temp_face.side.append(side);
			side.Mybegin = ON;
			side.Myend = point_c;
			temp_face.side.append(side);
			side.Mybegin = point_c;
			side.Myend = OC;
			temp_face.side.append(side);
			temp_face.type = 4;
			Origface.append(temp_face);
			temp_face.side.clear();
			//面ONOMBD
			side.Mybegin = ON;
			side.Myend = OM;
			temp_face.side.append(side);
			side.Mybegin = OM;
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = point_d;
			temp_face.side.append(side);
			side.Mybegin = point_d;
			side.Myend = ON;
			temp_face.side.append(side);
			temp_face.type = 4;
			Origface.append(temp_face);
			temp_face.side.clear();
			//////////////////////////////////////////////////////////
		}
	}

	}
}

void Morphing::DrawTwo()
{
	float d;
	MyFace temp_face;
	MySide side;
	Targface.clear();
	Origface.clear();
	//上边两点C,D
	MyPoint point_c;
	MyPoint point_d;
	//下边两点A,B
	MyPoint point_a;
	MyPoint point_b;
	//上边移动后两点E',F'
	MyPoint point_e;
	MyPoint point_f;
	//存储计算出的M,M1,M2,N,N1,N2
	MyPoint M[6];
	//角MAB的弧度
	float ang_1,ang_2,ang_3,ang_4,ang_5,ang_6;
	//AB,AM,BN,AM1，AM2，BN1，BN2,AE'边长度
	float l_ab,l_ef,l_am,l_bn,l_am1,l_am2,l_bn2,l_bn1,l_ae,l_bf,l_pp,l_fn;
	//用于计算M,M1,M2,N,N1,N2点坐标的比例值,例如AM/AE'
	float v[3],u[3];
	//判断移动方向和侧边AB向量的方向
	float dir;
	//母线长度
	float t;
	//直线AB与EF间距离
	float new_t;
	//用于计算new_t的中间量
	float com_temp;
	MyVector vet;
	MyPoint temp_on;
	for(int i=0;i<k;i++)
	{
		point_c = bup.at(i);
		point_d = bup.at(i+1);
		point_a = down.at(i);
		point_b = down.at(i+1);
		point_e = aup.at(i);
		point_f = aup.at(i+1);
		dir = x*(point_b.x-point_a.x)+y*(point_b.y-point_a.y);
		//平移后边E'F'与原边CD之间的距离
		d = ((point_d.x-point_c.x)*y-(point_d.y-point_c.y)*x)
			/sqrt((point_d.x-point_c.x)*(point_d.x-point_c.x)
				+(point_d.y-point_c.y)*(point_d.y-point_c.y));
		t = sqrt(diff*diff+h*h);
		//外翻和内翻将导致new_t的值变换太大，所以这里不用以下算法
		//new_t = sqrt(h*h+(d+sqrt(t*t-h*h))*(d+sqrt(t*t-h*h)));
		//使用如下算法：直接计算两直线的距离，即计算点E到直线AB的距离，中间点on，线Eon垂直AB
		vet.a = point_b.x-point_a.x;
		vet.b = point_b.y-point_a.y;
		vet.c = point_b.z-point_a.z;
		com_temp = (vet.a*(point_e.x-point_a.x)
				+vet.b*(point_e.y-point_a.y)
				+vet.c*(point_e.z-point_a.z))
			/(vet.a*vet.a+vet.b*vet.b+vet.c*vet.c);
		temp_on.x = vet.a*com_temp+point_a.x;
		temp_on.y = vet.b*com_temp+point_a.y;
		temp_on.z = vet.c*com_temp+point_a.z;
		new_t = temp_on.dis(point_e);
		//到此算法结束
		l_ab = point_a.dis(point_b);
		l_ef = point_e.dis(point_f);
		ang_2 = atan2(new_t,(sqrt(x*x+y*y-d*d)-(l_ab-l_ef)/2));
		ang_6 = atan2(new_t,(sqrt(x*x+y*y-d*d)+(l_ab-l_ef)/2));
		ang_1 = (PI-ang_2-ang_6)/2;
		ang_4 = ang_6+ang_1;
		ang_5 = ang_1+ang_2;
		ang_3 = PI/2-ang_4;
		l_ae = point_a.dis(point_e);		
		l_bf = point_b.dis(point_f);
	if(dir>=0)
	{		
		l_am = l_ab*sin(ang_1)/sin(ang_5);
		l_fn = l_ef*sin(ang_1)/sin(ang_4);
		l_pp = l_bf*cos(ang_3)-l_ef*sin(ang_1);
		l_bn = l_bf-l_fn;
		v[0] = l_am/l_ae;
		u[0] = l_bn/l_bf;
		if(l_pp>=t)
		{			
			l_am1 = l_am+((l_pp-t)*(l_ae-l_am))/(2*l_pp);
			l_am2 = l_ae-((l_pp-t)*(l_ae-l_am))/(2*l_pp);
			l_bn1 = (l_bn*(l_pp+t))/(2*l_pp);
			l_bn2 = (l_bn*(l_pp-t))/(2*l_pp);
			v[1] = l_am1/l_ae;
			v[2] = l_am2/l_ae;
			u[1] = l_bn1/l_bf;
			u[2] = l_bn2/l_bf;
			for(int i=0;i<3;i++)
			{
				M[i].x = v[i]*(point_e.x-point_a.x)+point_a.x;
				M[i].y = v[i]*(point_e.y-point_a.y)+point_a.y;
				M[i].z = v[i]*(point_e.z-point_a.z)+point_a.z;
				M[i+3].x = u[i]*(point_f.x-point_b.x)+point_b.x;
				M[i+3].y = u[i]*(point_f.y-point_b.y)+point_b.y;
				M[i+3].z = u[i]*(point_f.z-point_b.z)+point_b.z;
			}
			//面ABM
			side.Mybegin = point_a;
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = M[0];
			temp_face.side.append(side);
			side.Mybegin = M[0];
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 1;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面MBN2M1
			side.Mybegin = M[0];
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = M[5];
			temp_face.side.append(side);
			side.Mybegin = M[5];
			side.Myend = M[1];
			temp_face.side.append(side);
			side.Mybegin = M[1];
			side.Myend = M[0];
			temp_face.side.append(side);
			temp_face.type = 2;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面M1N2N1M2
			side.Mybegin = M[1];
			side.Myend = M[5];
			temp_face.side.append(side);
			side.Mybegin = M[5];
			side.Myend = M[4];
			temp_face.side.append(side);
			side.Mybegin = M[4];
			side.Myend = M[2];
			temp_face.side.append(side);
			side.Mybegin = M[2];
			side.Myend = M[1];
			temp_face.side.append(side);
			temp_face.type = 0;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面M2N1NE'
			side.Mybegin = M[2];
			side.Myend = M[4];
			temp_face.side.append(side);
			side.Mybegin = M[4];
			side.Myend = M[3];
			temp_face.side.append(side);
			side.Mybegin = M[3];
			side.Myend = point_e;
			temp_face.side.append(side);
			side.Mybegin = point_e;
			side.Myend = M[2];
			temp_face.side.append(side);
			temp_face.type = 2;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面EN3F
			side.Mybegin = point_e;
			side.Myend = M[3];
			temp_face.side.append(side);
			side.Mybegin = M[3];
			side.Myend = point_f;
			temp_face.side.append(side);
			side.Mybegin = point_f;
			side.Myend = point_e;
			temp_face.side.append(side);
			temp_face.type = 1;
			Targface.append(temp_face);
			temp_face.side.clear();
			////////////////////////////////////////////////
			float mu,mv,dd;
			MyPoint OM,ON,OC,OD;
			dd = ((t/l_pp)*l_ef*sin(ang_2)/sin(ang_4)+((l_pp-t)/l_pp)*l_ab*sin(ang_6)/sin(ang_5));
			if(dd<=point_c.dis(point_d))
			{
			mu = (point_c.dis(point_d)-dd)/(2*point_c.dis(point_d));
			mv = (1-sin(ang_6)/sin(ang_5))/2;
			OM.x = mv*(point_b.x-point_a.x)+point_a.x;
			OM.y = mv*(point_b.y-point_a.y)+point_a.y;
			OM.z = mv*(point_b.z-point_a.z)+point_a.z;
			ON.x = mv*(point_a.x-point_b.x)+point_b.x;
			ON.y = mv*(point_a.y-point_b.y)+point_b.y;
			ON.z = mv*(point_a.z-point_b.z)+point_b.z;
			OC.x = mu*(point_d.x-point_c.x)+point_c.x;
			OC.y = mu*(point_d.y-point_c.y)+point_c.y;
			OC.z = mu*(point_d.z-point_c.z)+point_c.z;
			OD.x = mu*(point_c.x-point_d.x)+point_d.x;
			OD.y = mu*(point_c.y-point_d.y)+point_d.y;
			OD.z = mu*(point_c.z-point_d.z)+point_d.z;
			//面AOMOCC
			side.Mybegin = point_a;
			side.Myend = OM;
			temp_face.side.append(side);
			side.Mybegin = OM;
			side.Myend = OC;
			temp_face.side.append(side);
			side.Mybegin = OC;
			side.Myend = point_c;
			temp_face.side.append(side);
			side.Mybegin = point_c;
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 4;
			Origface.append(temp_face);
			temp_face.side.clear();
			//面OMONODOC
			side.Mybegin = OM;
			side.Myend = ON;
			temp_face.side.append(side);
			side.Mybegin = ON;
			side.Myend = OD;
			temp_face.side.append(side);
			side.Mybegin = OD;
			side.Myend = OC;
			temp_face.side.append(side);
			side.Mybegin = OC;
			side.Myend = OM;
			temp_face.side.append(side);
			temp_face.type = 0;
			Origface.append(temp_face);
			temp_face.side.clear();
			//面ONBDOD
			side.Mybegin = ON;
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = point_d;
			temp_face.side.append(side);
			side.Mybegin = point_d;
			side.Myend = OD;
			temp_face.side.append(side);
			side.Mybegin = OD;
			side.Myend = ON;
			temp_face.side.append(side);
			temp_face.type = 4;
			Origface.append(temp_face);
			temp_face.side.clear();
			}else{
				float angdd;
				angdd = atan2(2*t,l_ab-point_c.dis(point_d));
				mv = (1-sin(ang_6)/sin(ang_5))/2;
				mu = mv*l_ab*sin(ang_4)/(sin(ang_4-angdd)*point_a.dis(point_c));
				OC.x = mu*(point_c.x-point_a.x)+point_a.x;
				OC.y = mu*(point_c.y-point_a.y)+point_a.y;
				OC.z = mu*(point_c.z-point_a.z)+point_a.z;
				OD.x = mu*(point_d.x-point_b.x)+point_b.x;
				OD.y = mu*(point_d.y-point_b.y)+point_b.y;
				OD.z = mu*(point_d.z-point_b.z)+point_b.z;
				
				OM.x = mv*(point_b.x-point_a.x)+point_a.x;
				OM.y = mv*(point_b.y-point_a.y)+point_a.y;
				OM.z = mv*(point_b.z-point_a.z)+point_a.z;
				ON.x = mv*(point_a.x-point_b.x)+point_b.x;
				ON.y = mv*(point_a.y-point_b.y)+point_b.y;
				ON.z = mv*(point_a.z-point_b.z)+point_b.z;
				//面AOMOC
				side.Mybegin = point_a;
				side.Myend = OM;
				temp_face.side.append(side);
				side.Mybegin = OM;
				side.Myend = OC;
				temp_face.side.append(side);
				side.Mybegin = OC;
				side.Myend = point_a;
				temp_face.side.append(side);
				temp_face.type = 4;
				Origface.append(temp_face);
				temp_face.side.clear();
				//面OMONODDCOC
				side.Mybegin = OM;
				side.Myend = ON;
				temp_face.side.append(side);
				side.Mybegin = ON;
				side.Myend = OD;
				temp_face.side.append(side);
				side.Mybegin = OD;
				side.Myend = point_d;
				temp_face.side.append(side);
				side.Mybegin = point_d;
				side.Myend = point_c;
				temp_face.side.append(side);
				side.Mybegin = point_c;
				side.Myend = OC;
				temp_face.side.append(side);
				side.Mybegin = OC;
				side.Myend = OM;
				temp_face.side.append(side);
				temp_face.type = 0;
				Origface.append(temp_face);
				temp_face.side.clear();
				//面ONBOD
				side.Mybegin = ON;
				side.Myend = point_b;
				temp_face.side.append(side);
				side.Mybegin = point_b;
				side.Myend = OD;
				temp_face.side.append(side);
				side.Mybegin = OD;
				side.Myend = ON;
				temp_face.side.append(side);
				temp_face.type = 4;
				Origface.append(temp_face);
				temp_face.side.clear();
			}
			////////////////////////////////////////////////
		}else
		{
			M[0].x = v[0]*(point_e.x-point_a.x)+point_a.x;
			M[0].y = v[0]*(point_e.y-point_a.y)+point_a.y;
			M[0].z = v[0]*(point_e.z-point_a.z)+point_a.z;
			M[3].x = u[0]*(point_f.x-point_b.x)+point_b.x;
			M[3].y = u[0]*(point_f.y-point_b.y)+point_b.y;
			M[3].z = u[0]*(point_f.z-point_b.z)+point_b.z;
			//面ABM
			side.Mybegin = point_a;
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = M[0];
			temp_face.side.append(side);
			side.Mybegin = M[0];
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 1;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面MBNE'
			side.Mybegin = M[0];
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = M[3];
			temp_face.side.append(side);
			side.Mybegin = M[3];
			side.Myend = point_e;
			temp_face.side.append(side);
			side.Mybegin = point_e;
			side.Myend = M[0];
			temp_face.side.append(side);
			temp_face.type = 0;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面EN3F
			side.Mybegin = point_e;
			side.Myend = M[3];
			temp_face.side.append(side);
			side.Mybegin = M[3];
			side.Myend = point_f;
			temp_face.side.append(side);
			side.Mybegin = point_f;
			side.Myend = point_e;
			temp_face.side.append(side);
			temp_face.type = 1;
			Targface.append(temp_face);
			temp_face.side.clear();
			////////////////////////////////////////////////
			float mu,mv,vvv;
			MyPoint OM,TT,OC,OD,RR,ON;
			vvv = l_pp/t;
			TT.x = vvv*(point_c.x-point_a.x)+point_a.x;
			TT.y = vvv*(point_c.y-point_a.y)+point_a.y;
			TT.z = vvv*(point_c.z-point_a.z)+point_a.z;
			RR.x = vvv*(point_d.x-point_b.x)+point_b.x;
			RR.y = vvv*(point_d.y-point_b.y)+point_b.y;
			RR.z = vvv*(point_d.z-point_b.z)+point_b.z;
			mu = (TT.dis(RR) - l_ef*sin(ang_2)/sin(ang_4))/(2*TT.dis(RR));
			mv = (l_ab-l_ab*sin(ang_6)/sin(ang_5))/(2*l_ab);
			OM.x = mv*(point_b.x-point_a.x)+point_a.x;
			OM.y = mv*(point_b.y-point_a.y)+point_a.y;
			OM.z = mv*(point_b.z-point_a.z)+point_a.z;
			ON.x = mv*(point_a.x-point_b.x)+point_b.x;
			ON.y = mv*(point_a.y-point_b.y)+point_b.y;
			ON.z = mv*(point_a.z-point_b.z)+point_b.z;
			OC.x = mu*(RR.x-TT.x)+TT.x;
			OC.y = mu*(RR.y-TT.y)+TT.y;
			OC.z = mu*(RR.z-TT.z)+TT.z;
			OD.x = mu*(TT.x-RR.x)+RR.x;
			OD.y = mu*(TT.y-RR.y)+RR.y;
			OD.z = mu*(TT.z-RR.z)+RR.z;
			//面OMOCODON
			side.Mybegin = OM;
			side.Myend = OC;
			temp_face.side.append(side);
			side.Mybegin = OC;
			side.Myend = OD;
			temp_face.side.append(side);
			side.Mybegin = OD;
			side.Myend = ON;
			temp_face.side.append(side);
			side.Mybegin = ON;
			side.Myend = OM;
			temp_face.side.append(side);
			temp_face.type = 0;
			Origface.append(temp_face);
			temp_face.side.clear();
			//面AOMOCC
			side.Mybegin = point_a;
			side.Myend = OM;
			temp_face.side.append(side);
			side.Mybegin = OM;
			side.Myend = OC;
			temp_face.side.append(side);
			side.Mybegin = OC;
			side.Myend = point_c;
			temp_face.side.append(side);
			side.Mybegin = point_c;
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 4;
			Origface.append(temp_face);
			temp_face.side.clear();
			//面ODOCCD
			side.Mybegin = OD;
			side.Myend = OC;
			temp_face.side.append(side);
			side.Mybegin = OC;
			side.Myend = point_c;
			temp_face.side.append(side);
			side.Mybegin = point_c;
			side.Myend = point_d;
			temp_face.side.append(side);
			side.Mybegin = point_d;
			side.Myend = OD;
			temp_face.side.append(side);
			temp_face.type = 4;
			Origface.append(temp_face);
			temp_face.side.clear();
			//面ONODDB
			side.Mybegin = ON;
			side.Myend = OD;
			temp_face.side.append(side);
			side.Mybegin = OD;
			side.Myend = point_d;
			temp_face.side.append(side);
			side.Mybegin = point_d;
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = ON;
			temp_face.side.append(side);
			temp_face.type = 4;
			Origface.append(temp_face);
			temp_face.side.clear();
			////////////////////////////////////////////////
		}
	}else{

		l_am = l_ae-l_ef*sin(ang_1)/sin(ang_4);
		l_bn = l_ab*sin(ang_1)/sin(ang_5);
		l_pp = l_ae*cos(ang_3)-l_ef*sin(ang_1);
		v[0] = l_am/l_ae;
		u[0] = l_bn/l_bf;
		if(l_pp>=t)
		{			
			l_am1 = (l_am*(l_pp+t))/(2*l_pp);
			l_am2 = (l_am*(l_pp-t))/(2*l_pp);
			l_bn1 = l_bn+((l_bf-l_bn)*(l_pp-t))/(2*l_pp);
			l_bn2 = l_bf-((l_bf-l_bn)*(l_pp-t))/(2*l_pp);
			v[1] = l_am1/l_ae;
			v[2] = l_am2/l_ae;
			u[1] = l_bn1/l_bf;
			u[2] = l_bn2/l_bf;
			for(int i=0;i<3;i++)
			{
				M[i].x = v[i]*(point_e.x-point_a.x)+point_a.x;
				M[i].y = v[i]*(point_e.y-point_a.y)+point_a.y;
				M[i].z = v[i]*(point_e.z-point_a.z)+point_a.z;
				M[i+3].x = u[i]*(point_f.x-point_b.x)+point_b.x;
				M[i+3].y = u[i]*(point_f.y-point_b.y)+point_b.y;
				M[i+3].z = u[i]*(point_f.z-point_b.z)+point_b.z;
			}
			//面ABN
			side.Mybegin = point_a;
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = M[3];
			temp_face.side.append(side);
			side.Mybegin = M[3];
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 1;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面ANN1M2
			side.Mybegin = point_a;
			side.Myend = M[3];
			temp_face.side.append(side);
			side.Mybegin = M[3];
			side.Myend = M[4];
			temp_face.side.append(side);
			side.Mybegin = M[4];
			side.Myend = M[2];
			temp_face.side.append(side);
			side.Mybegin = M[2];
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 2;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面M2N1N2M1
			side.Mybegin = M[2];
			side.Myend = M[4];
			temp_face.side.append(side);
			side.Mybegin = M[4];
			side.Myend = M[5];
			temp_face.side.append(side);
			side.Mybegin = M[5];
			side.Myend = M[1];
			temp_face.side.append(side);
			side.Mybegin = M[1];
			side.Myend = M[2];
			temp_face.side.append(side);
			temp_face.type = 0;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面M1N2F'M
			side.Mybegin = M[1];
			side.Myend = M[5];
			temp_face.side.append(side);
			side.Mybegin = M[5];
			side.Myend = point_f;
			temp_face.side.append(side);
			side.Mybegin = point_f;
			side.Myend = M[0];
			temp_face.side.append(side);
			side.Mybegin = M[0];
			side.Myend = M[1];
			temp_face.side.append(side);
			temp_face.type = 2;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面MF'E'
			side.Mybegin = M[0];
			side.Myend = point_f;
			temp_face.side.append(side);
			side.Mybegin = point_f;
			side.Myend = point_e;
			temp_face.side.append(side);
			side.Mybegin = point_e;
			side.Myend = point_f;
			temp_face.side.append(side);
			temp_face.type = 1;
			Targface.append(temp_face);
			temp_face.side.clear();
			////////////////////////////////////////////////
			float mu,mv,dd;
			MyPoint OM,ON,OC,OD;
			dd = ((t/l_pp)*l_ef*sin(ang_2)/sin(ang_4)+((l_pp-t)/l_pp)*l_ab*sin(ang_6)/sin(ang_5));
			if(dd<=point_c.dis(point_d))
			{
			mu = (point_c.dis(point_d)-dd)/(2*point_c.dis(point_d));
			mv = (1-sin(ang_6)/sin(ang_5))/2;
			OM.x = mv*(point_b.x-point_a.x)+point_a.x;
			OM.y = mv*(point_b.y-point_a.y)+point_a.y;
			OM.z = mv*(point_b.z-point_a.z)+point_a.z;
			ON.x = mv*(point_a.x-point_b.x)+point_b.x;
			ON.y = mv*(point_a.y-point_b.y)+point_b.y;
			ON.z = mv*(point_a.z-point_b.z)+point_b.z;
			OC.x = mu*(point_d.x-point_c.x)+point_c.x;
			OC.y = mu*(point_d.y-point_c.y)+point_c.y;
			OC.z = mu*(point_d.z-point_c.z)+point_c.z;
			OD.x = mu*(point_c.x-point_d.x)+point_d.x;
			OD.y = mu*(point_c.y-point_d.y)+point_d.y;
			OD.z = mu*(point_c.z-point_d.z)+point_d.z;
			//面AOMOCC
			side.Mybegin = point_a;
			side.Myend = OM;
			temp_face.side.append(side);
			side.Mybegin = OM;
			side.Myend = OC;
			temp_face.side.append(side);
			side.Mybegin = OC;
			side.Myend = point_c;
			temp_face.side.append(side);
			side.Mybegin = point_c;
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 1;
			Origface.append(temp_face);
			temp_face.side.clear();
			//面OMONODOC
			side.Mybegin = OM;
			side.Myend = ON;
			temp_face.side.append(side);
			side.Mybegin = ON;
			side.Myend = OD;
			temp_face.side.append(side);
			side.Mybegin = OD;
			side.Myend = OC;
			temp_face.side.append(side);
			side.Mybegin = OC;
			side.Myend = OM;
			temp_face.side.append(side);
			temp_face.type = 0;
			Origface.append(temp_face);
			temp_face.side.clear();
			//面ONBDOD
			side.Mybegin = ON;
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = point_d;
			temp_face.side.append(side);
			side.Mybegin = point_d;
			side.Myend = OD;
			temp_face.side.append(side);
			side.Mybegin = OD;
			side.Myend = ON;
			temp_face.side.append(side);
			temp_face.type = 4;
			Origface.append(temp_face);
			temp_face.side.clear();
			}else{
				float angdd;
				angdd = atan2(2*t,l_ab-point_c.dis(point_d));
				mv = (1-sin(ang_6)/sin(ang_5))/2;
				mu = mv*l_ab*sin(ang_4)/(sin(ang_4-angdd)*point_a.dis(point_c));
				OC.x = mu*(point_c.x-point_a.x)+point_a.x;
				OC.y = mu*(point_c.y-point_a.y)+point_a.y;
				OC.z = mu*(point_c.z-point_a.z)+point_a.z;
				OD.x = mu*(point_d.x-point_b.x)+point_b.x;
				OD.y = mu*(point_d.y-point_b.y)+point_b.y;
				OD.z = mu*(point_d.z-point_b.z)+point_b.z;
				
				OM.x = mv*(point_b.x-point_a.x)+point_a.x;
				OM.y = mv*(point_b.y-point_a.y)+point_a.y;
				OM.z = mv*(point_b.z-point_a.z)+point_a.z;
				ON.x = mv*(point_a.x-point_b.x)+point_b.x;
				ON.y = mv*(point_a.y-point_b.y)+point_b.y;
				ON.z = mv*(point_a.z-point_b.z)+point_b.z;
				//面AOMOC
				side.Mybegin = point_a;
				side.Myend = OM;
				temp_face.side.append(side);
				side.Mybegin = OM;
				side.Myend = OC;
				temp_face.side.append(side);
				side.Mybegin = OC;
				side.Myend = point_a;
				temp_face.side.append(side);
				temp_face.type = 4;
				Origface.append(temp_face);
				temp_face.side.clear();
				//面OMONODDCOC
				side.Mybegin = OM;
				side.Myend = ON;
				temp_face.side.append(side);
				side.Mybegin = ON;
				side.Myend = OD;
				temp_face.side.append(side);
				side.Mybegin = OD;
				side.Myend = point_d;
				temp_face.side.append(side);
				side.Mybegin = point_d;
				side.Myend = point_c;
				temp_face.side.append(side);
				side.Mybegin = point_c;
				side.Myend = OC;
				temp_face.side.append(side);
				side.Mybegin = OC;
				side.Myend = OM;
				temp_face.side.append(side);
				temp_face.type = 0;
				Origface.append(temp_face);
				temp_face.side.clear();
				//面ONBOD
				side.Mybegin = ON;
				side.Myend = point_b;
				temp_face.side.append(side);
				side.Mybegin = point_b;
				side.Myend = OD;
				temp_face.side.append(side);
				side.Mybegin = OD;
				side.Myend = ON;
				temp_face.side.append(side);
				temp_face.type = 4;
				Origface.append(temp_face);
				temp_face.side.clear();
			}
			////////////////////////////////////////////////
		}else
		{
			M[0].x = v[0]*(point_e.x-point_a.x)+point_a.x;
			M[0].y = v[0]*(point_e.y-point_a.y)+point_a.y;
			M[0].z = v[0]*(point_e.z-point_a.z)+point_a.z;
			M[3].x = u[0]*(point_f.x-point_b.x)+point_b.x;
			M[3].y = u[0]*(point_f.y-point_b.y)+point_b.y;
			M[3].z = u[0]*(point_f.z-point_b.z)+point_b.z;
			//面ABN
			side.Mybegin = point_a;
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = M[3];
			temp_face.side.append(side);
			side.Mybegin = M[3];
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 1;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面ANF'M
			side.Mybegin = point_a;
			side.Myend = M[3];
			temp_face.side.append(side);
			side.Mybegin = M[3];
			side.Myend = point_f;
			temp_face.side.append(side);
			side.Mybegin = point_f;
			side.Myend = M[0];
			temp_face.side.append(side);
			side.Mybegin = M[0];
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 0;
			Targface.append(temp_face);
			temp_face.side.clear();
			//面MF'E'
			side.Mybegin = M[0];
			side.Myend = point_f;
			temp_face.side.append(side);
			side.Mybegin = point_f;
			side.Myend = point_e;
			temp_face.side.append(side);
			side.Mybegin = point_e;
			side.Myend = M[0];
			temp_face.side.append(side);
			temp_face.type = 1;
			Targface.append(temp_face);
			temp_face.side.clear();
			////////////////////////////////////////////////
			float mu,mv,vvv;
			MyPoint OM,TT,OC,OD,RR,ON;
			vvv = l_pp/t;
			TT.x = vvv*(point_c.x-point_a.x)+point_a.x;
			TT.y = vvv*(point_c.y-point_a.y)+point_a.y;
			TT.z = vvv*(point_c.z-point_a.z)+point_a.z;
			RR.x = vvv*(point_d.x-point_b.x)+point_b.x;
			RR.y = vvv*(point_d.y-point_b.y)+point_b.y;
			RR.z = vvv*(point_d.z-point_b.z)+point_b.z;
			mu = (TT.dis(RR) - l_ef*sin(ang_2)/sin(ang_4))/(2*TT.dis(RR));
			mv = (l_ab-l_ab*sin(ang_6)/sin(ang_5))/(2*l_ab);
			OM.x = mv*(point_b.x-point_a.x)+point_a.x;
			OM.y = mv*(point_b.y-point_a.y)+point_a.y;
			OM.z = mv*(point_b.z-point_a.z)+point_a.z;
			ON.x = mv*(point_a.x-point_b.x)+point_b.x;
			ON.y = mv*(point_a.y-point_b.y)+point_b.y;
			ON.z = mv*(point_a.z-point_b.z)+point_b.z;
			OC.x = mu*(RR.x-TT.x)+TT.x;
			OC.y = mu*(RR.y-TT.y)+TT.y;
			OC.z = mu*(RR.z-TT.z)+TT.z;
			OD.x = mu*(TT.x-RR.x)+RR.x;
			OD.y = mu*(TT.y-RR.y)+RR.y;
			OD.z = mu*(TT.z-RR.z)+RR.z;
			//面OMOCODON
			side.Mybegin = OM;
			side.Myend = OC;
			temp_face.side.append(side);
			side.Mybegin = OC;
			side.Myend = OD;
			temp_face.side.append(side);
			side.Mybegin = OD;
			side.Myend = ON;
			temp_face.side.append(side);
			side.Mybegin = ON;
			side.Myend = OM;
			temp_face.side.append(side);
			temp_face.type = 0;
			Origface.append(temp_face);
			temp_face.side.clear();
			//面AOMOCC
			side.Mybegin = point_a;
			side.Myend = OM;
			temp_face.side.append(side);
			side.Mybegin = OM;
			side.Myend = OC;
			temp_face.side.append(side);
			side.Mybegin = OC;
			side.Myend = point_c;
			temp_face.side.append(side);
			side.Mybegin = point_c;
			side.Myend = point_a;
			temp_face.side.append(side);
			temp_face.type = 4;
			Origface.append(temp_face);
			temp_face.side.clear();
			//面ODOCCD
			side.Mybegin = OD;
			side.Myend = OC;
			temp_face.side.append(side);
			side.Mybegin = OC;
			side.Myend = point_c;
			temp_face.side.append(side);
			side.Mybegin = point_c;
			side.Myend = point_d;
			temp_face.side.append(side);
			side.Mybegin = point_d;
			side.Myend = OD;
			temp_face.side.append(side);
			temp_face.type = 4;
			Origface.append(temp_face);
			temp_face.side.clear();
			//面ONODDB
			side.Mybegin = ON;
			side.Myend = OD;
			temp_face.side.append(side);
			side.Mybegin = OD;
			side.Myend = point_d;
			temp_face.side.append(side);
			side.Mybegin = point_d;
			side.Myend = point_b;
			temp_face.side.append(side);
			side.Mybegin = point_b;
			side.Myend = ON;
			temp_face.side.append(side);
			temp_face.type = 4;
			Origface.append(temp_face);
			temp_face.side.clear();
			////////////////////////////////////////////////
		}
	}		
	}
}

void Morphing::DrawThr()
{
	MyFace temp_face;
	MySide side;
	Targface.clear();
	Origface.clear();
	//上边两点C,D
	MyPoint point_c;
	MyPoint point_d;
	//下边两点A,B
	MyPoint point_a;
	MyPoint point_b;
	//上边移动后两点E',F'
	MyPoint point_e;
	MyPoint point_f;
	MyPoint point_o;
	MyPoint M[2];
	MyVector vet;
	float com_temp;
	float v;
	for(int i=0;i<k;i++)
	{
		point_c = bup.at(i);
		point_d = bup.at(i+1);
		point_a = down.at(i);
		point_b = down.at(i+1);
		point_e = aup.at(i);
		point_f = aup.at(i+1);
		v = sqrt(h*h+diff*diff)/sqrt((h+ext)*(h+ext)+diff*diff);
		vet.a = point_b.x-point_a.x;
		vet.b = point_b.y-point_a.y;
		vet.c = point_b.z-point_a.z;
		//计算点C,E在直线AB上的垂足
		com_temp = (vet.a*(point_e.x-point_a.x)
				+vet.b*(point_e.y-point_a.y)
				+vet.c*(point_e.z-point_a.z))
			/(vet.a*vet.a+vet.b*vet.b+vet.c*vet.c);
		point_o.x = vet.a*com_temp+point_a.x;
		point_o.y = vet.b*com_temp+point_a.y;
		point_o.z = vet.c*com_temp+point_a.z;		
		M[0].x = v*(point_e.x-point_o.x)+point_o.x;
		M[0].y = v*(point_e.y-point_o.y)+point_o.y;
		M[0].z = v*(point_e.z-point_o.z)+point_o.z;
		//计算点D,F在直线AB上的垂足
		com_temp = (vet.a*(point_f.x-point_a.x)
				+vet.b*(point_f.y-point_a.y)
				+vet.c*(point_f.z-point_a.z))
			/(vet.a*vet.a+vet.b*vet.b+vet.c*vet.c);
		point_o.x = vet.a*com_temp+point_a.x;
		point_o.y = vet.b*com_temp+point_a.y;
		point_o.z = vet.c*com_temp+point_a.z;		
		M[1].x = v*(point_f.x-point_o.x)+point_o.x;
		M[1].y = v*(point_f.y-point_o.y)+point_o.y;
		M[1].z = v*(point_f.z-point_o.z)+point_o.z;
		//面ABM1M0
		side.Mybegin = point_a;
		side.Myend = point_b;
		temp_face.side.append(side);
		side.Mybegin = point_b;
		side.Myend = M[1];
		temp_face.side.append(side);
		side.Mybegin = M[1];
		side.Myend = M[0];
		temp_face.side.append(side);
		side.Mybegin = M[0];
		side.Myend = point_a;
		temp_face.side.append(side);
		temp_face.type = 0;
		Targface.append(temp_face);
		temp_face.side.clear();
		//面AEM0
		side.Mybegin = point_a;
		side.Myend = point_e;
		temp_face.side.append(side);
		side.Mybegin = point_e;
		side.Myend = M[0];
		temp_face.side.append(side);
		side.Mybegin = M[0];
		side.Myend = point_a;
		temp_face.side.append(side);
		temp_face.type = 3;
		Targface.append(temp_face);
		temp_face.side.clear();
		//面M0M1FE
		side.Mybegin = M[0];
		side.Myend = M[1];
		temp_face.side.append(side);
		side.Mybegin = M[1];
		side.Myend = point_f;
		temp_face.side.append(side);
		side.Mybegin = point_f;
		side.Myend = point_e;
		temp_face.side.append(side);
		side.Mybegin = point_e;
		side.Myend = M[0];
		temp_face.side.append(side);
		temp_face.type = 2;
		Targface.append(temp_face);
		temp_face.side.clear();
		//面FBM1
		side.Mybegin = point_f;
		side.Myend = point_b;
		temp_face.side.append(side);
		side.Mybegin = point_b;
		side.Myend = M[1];
		temp_face.side.append(side);
		side.Mybegin = M[1];
		side.Myend = point_f;
		temp_face.side.append(side);
		temp_face.type = 3;
		Targface.append(temp_face);
		temp_face.side.clear();
		//面ABCD
		side.Mybegin = point_a;
		side.Myend = point_b;
		temp_face.side.append(side);
		side.Mybegin = point_b;
		side.Myend = point_d;
		temp_face.side.append(side);
		side.Mybegin = point_d;
		side.Myend = point_c;
		temp_face.side.append(side);
		side.Mybegin = point_c;
		side.Myend = point_a;
		temp_face.side.append(side);
		temp_face.type = 0;
		Origface.append(temp_face);
		temp_face.side.clear();
	}
}

void Morphing::DrawFor()
{
	MyFace temp_face;
	MySide side;
	Targface.clear();
	Origface.clear();
	//上边两点C,D
	MyPoint point_c;
	MyPoint point_d;
	//下边两点A,B
	MyPoint point_a;
	MyPoint point_b;
	//上边移动后两点E',F'
	MyPoint point_e;
	MyPoint point_f;
	MyPoint new_c;
	MyPoint temp;
	MyPoint O;
	MyVector v_a,v_b,v_c;
	MyVector axc,axb;
	float C,S;
	double u;
	for(int i=0;i<k;i++)
	{
		point_c = bup.at(i);
		point_d = bup.at(i+1);
		point_a = down.at(i);
		point_b = down.at(i+1);
		point_e = aup.at(i);
		point_f = aup.at(i+1);
		v_a = point_a.vet(point_b);
		v_b = point_b.vet(point_c);
		v_c = point_b.vet(point_e);
		axc = v_a.plus(v_c);
		axb = v_a.plus(v_b);
		if(v_b.plus(v_c).dot(v_a)<0)
		{
			C = axb.dot(axc)/(axb.mod()*axc.mod());
			if(C>=1)
				C=1;
			S = sin(acos(C));			
		}else if(v_b.plus(v_c).dot(v_a)>0){
			C = axb.dot(axc)/(axb.mod()*axc.mod());
			if(C>=1)
				C=1;
			S = -sin(acos(C));
		}else
		{
			C = 1;
			S = 0;
		}
		v_a = normal(v_a);
		temp = point_c.mus(point_a);
		new_c.x = temp.x*(C - v_a.a*v_a.a*(C - 1))
		       	+ temp.y*(S*v_a.c - v_a.a*v_a.b*(C - 1))
		       	- temp.z*(S*v_a.b + v_a.a*v_a.c*(C - 1));
		new_c.y = temp.y*(C - v_a.b*v_a.b*(C - 1))
		       	- temp.x*(S*v_a.c + v_a.a*v_a.b*(C - 1))
		       	+ temp.z*(S*v_a.a - v_a.b*v_a.c*(C - 1));
		new_c.z = temp.z*(C - v_a.c*v_a.c*(C - 1)) 
			+ temp.x*(S*v_a.b - v_a.a*v_a.c*(C - 1)) 
			- temp.y*(S*v_a.a + v_a.b*v_a.c*(C - 1));
		new_c = new_c.add(point_a);
		if(samedir(point_a,point_b,new_c,point_e))
		{
			if(samedir(point_b,point_a,new_c,point_e))
			{
				//E2
				//面ACB，原始面
				side.Mybegin = point_a;
				side.Myend = point_b;
				temp_face.side.append(side);
				side.Mybegin = point_b;
				side.Myend = new_c;
				temp_face.side.append(side);
				side.Mybegin = new_c;
				side.Myend = point_a;
				temp_face.side.append(side);
				temp_face.type = 0;
				Targface.append(temp_face);
				temp_face.side.clear();
				//面ACE，补面
				side.Mybegin = point_a;
				side.Myend = new_c;
				temp_face.side.append(side);
				side.Mybegin = new_c;
				side.Myend = point_e;
				temp_face.side.append(side);
				side.Mybegin = point_e;
				side.Myend = point_a;
				temp_face.side.append(side);
				temp_face.type = 2;
				Targface.append(temp_face);
				temp_face.side.clear();
				//面BEC，补面
				side.Mybegin = point_b;
				side.Myend = point_e;
				temp_face.side.append(side);
				side.Mybegin = point_e;
				side.Myend = new_c;
				temp_face.side.append(side);
				side.Mybegin = new_c;
				side.Myend = point_b;
				temp_face.side.append(side);
				temp_face.type = 2;
				Targface.append(temp_face);
				temp_face.side.clear();
				//面ABC
				side.Mybegin = point_b;
				side.Myend = point_a;
				temp_face.side.append(side);
				side.Mybegin = point_a;
				side.Myend = point_c;
				temp_face.side.append(side);
				side.Mybegin = point_c;
				side.Myend = point_b;
				temp_face.side.append(side);
				temp_face.type = 0;
				Origface.append(temp_face);
				temp_face.side.clear();
			}else{
				//E3
				float eee,fff,ggg;
				eee = acos((point_e.dis(point_b)*point_e.dis(point_b)
							+point_b.dis(point_a)*point_b.dis(point_a)
							-point_e.dis(point_a)*point_e.dis(point_a))
						/(2*point_e.dis(point_b)*point_b.dis(point_a)));
				fff = acos((new_c.dis(point_a)*new_c.dis(point_a)
							+point_b.dis(point_a)*point_b.dis(point_a)
							-point_b.dis(new_c)*point_b.dis(new_c))
						/(2*new_c.dis(point_a)*point_b.dis(point_a)));
				ggg = (point_a.dis(point_b)*sin(fff))/(sin(eee+fff));
				u = ggg/point_b.dis(point_e);
				O.x = u*(point_e.x-point_b.x)+point_b.x;
				O.y = u*(point_e.y-point_b.y)+point_b.y;
				O.z = u*(point_e.z-point_b.z)+point_b.z;
				v_a = normal(v_a);
				temp = O.mus(point_a);
				S = -S;
				new_c.x = temp.x*(C - v_a.a*v_a.a*(C - 1))
			       		+ temp.y*(S*v_a.c - v_a.a*v_a.b*(C - 1))
			     	  	- temp.z*(S*v_a.b + v_a.a*v_a.c*(C - 1));
				new_c.y = temp.y*(C - v_a.b*v_a.b*(C - 1))
				       	- temp.x*(S*v_a.c + v_a.a*v_a.b*(C - 1))
				       	+ temp.z*(S*v_a.a - v_a.b*v_a.c*(C - 1));
				new_c.z = temp.z*(C - v_a.c*v_a.c*(C - 1)) 
					+ temp.x*(S*v_a.b - v_a.a*v_a.c*(C - 1)) 
					- temp.y*(S*v_a.a + v_a.b*v_a.c*(C - 1));
				new_c = new_c.add(point_a);
				//面ABO，原始面
				side.Mybegin = point_a;
				side.Myend = point_b;
				temp_face.side.append(side);
				side.Mybegin = point_b;
				side.Myend = O;
				temp_face.side.append(side);
				side.Mybegin = O;
				side.Myend = point_a;
				temp_face.side.append(side);
				temp_face.type = 0;
				Targface.append(temp_face);
				temp_face.side.clear();
				//面AOE，补面
				side.Mybegin = point_a;
				side.Myend = O;
				temp_face.side.append(side);
				side.Mybegin = O;
				side.Myend = point_e;
				temp_face.side.append(side);
				side.Mybegin = point_e;
				side.Myend = point_a;
				temp_face.side.append(side);
				temp_face.type = 2;
				Targface.append(temp_face);
				temp_face.side.clear();
				//面ABO，原始面
				side.Mybegin = point_a;
				side.Myend = point_b;
				temp_face.side.append(side);
				side.Mybegin = point_b;
				side.Myend = new_c;
				temp_face.side.append(side);
				side.Mybegin = new_c;
				side.Myend = point_a;
				temp_face.side.append(side);
				temp_face.type = 0;
				Origface.append(temp_face);
				temp_face.side.clear();
				//面BOE，补面
				side.Mybegin = point_b;
				side.Myend = new_c;
				temp_face.side.append(side);
				side.Mybegin = new_c;
				side.Myend = point_c;
				temp_face.side.append(side);
				side.Mybegin = point_c;
				side.Myend = point_b;
				temp_face.side.append(side);
				temp_face.type = 4;
				Origface.append(temp_face);
				temp_face.side.clear();				
			}
		}else{
			if(samedir(point_b,point_a,new_c,point_e))
			{
				//E1
				float eee,fff,ggg;
				eee = acos((point_e.dis(point_a)*point_e.dis(point_a)
							+point_b.dis(point_a)*point_b.dis(point_a)
							-point_e.dis(point_b)*point_e.dis(point_b))
						/(2*point_e.dis(point_a)*point_b.dis(point_a)));
				fff = acos((new_c.dis(point_b)*new_c.dis(point_b)
							+point_b.dis(point_a)*point_b.dis(point_a)
							-point_a.dis(new_c)*point_a.dis(new_c))
						/(2*new_c.dis(point_b)*point_b.dis(point_a)));
				ggg = (point_a.dis(point_b)*sin(eee))/(sin(eee+fff));
				u = ggg/point_b.dis(new_c);
				O.x = u*(new_c.x-point_b.x)+point_b.x;
				O.y = u*(new_c.y-point_b.y)+point_b.y;
				O.z = u*(new_c.z-point_b.z)+point_b.z;
				v_a = normal(v_a);
				temp = O.mus(point_a);
				S = -S;
				new_c.x = temp.x*(C - v_a.a*v_a.a*(C - 1))
			       		+ temp.y*(S*v_a.c - v_a.a*v_a.b*(C - 1))
			     	  	- temp.z*(S*v_a.b + v_a.a*v_a.c*(C - 1));
				new_c.y = temp.y*(C - v_a.b*v_a.b*(C - 1))
				       	- temp.x*(S*v_a.c + v_a.a*v_a.b*(C - 1))
				       	+ temp.z*(S*v_a.a - v_a.b*v_a.c*(C - 1));
				new_c.z = temp.z*(C - v_a.c*v_a.c*(C - 1)) 
					+ temp.x*(S*v_a.b - v_a.a*v_a.c*(C - 1)) 
					- temp.y*(S*v_a.a + v_a.b*v_a.c*(C - 1));
				new_c = new_c.add(point_a);				
				//面ABO，原始面
				side.Mybegin = point_a;
				side.Myend = point_b;
				temp_face.side.append(side);
				side.Mybegin = point_b;
				side.Myend = O;
				temp_face.side.append(side);
				side.Mybegin = O;
				side.Myend = point_a;
				temp_face.side.append(side);
				temp_face.type = 0;
				Targface.append(temp_face);
				temp_face.side.clear();
				//面BOE，补面
				side.Mybegin = point_b;
				side.Myend = O;
				temp_face.side.append(side);
				side.Mybegin = O;
				side.Myend = point_e;
				temp_face.side.append(side);
				side.Mybegin = point_e;
				side.Myend = point_b;
				temp_face.side.append(side);
				temp_face.type = 2;
				Targface.append(temp_face);
				temp_face.side.clear();
				//面ABO，原始面
				side.Mybegin = point_a;
				side.Myend = point_b;
				temp_face.side.append(side);
				side.Mybegin = point_b;
				side.Myend = new_c;
				temp_face.side.append(side);
				side.Mybegin = new_c;
				side.Myend = point_a;
				temp_face.side.append(side);
				temp_face.type = 0;
				Origface.append(temp_face);
				temp_face.side.clear();
				//面BOE，补面
				side.Mybegin = point_a;
				side.Myend = new_c;
				temp_face.side.append(side);
				side.Mybegin = new_c;
				side.Myend = point_c;
				temp_face.side.append(side);
				side.Mybegin = point_c;
				side.Myend = point_a;
				temp_face.side.append(side);
				temp_face.type = 4;
				Origface.append(temp_face);
				temp_face.side.clear();					
			}else{
				//E4
				//面ABE
				side.Mybegin = point_a;
				side.Myend = point_b;
				temp_face.side.append(side);
				side.Mybegin = point_b;
				side.Myend = point_e;
				temp_face.side.append(side);
				side.Mybegin = point_e;
				side.Myend = point_a;
				temp_face.side.append(side);
				temp_face.type = 0;
				Targface.append(temp_face);
				temp_face.side.clear();
				//将e点转回去
				v_a = normal(v_a);
				temp = point_e.mus(point_a);
				S = -S;
				new_c.x = temp.x*(C - v_a.a*v_a.a*(C - 1))
				       	+ temp.y*(S*v_a.c - v_a.a*v_a.b*(C - 1))
				       	- temp.z*(S*v_a.b + v_a.a*v_a.c*(C - 1));
				new_c.y = temp.y*(C - v_a.b*v_a.b*(C - 1))
				       	- temp.x*(S*v_a.c + v_a.a*v_a.b*(C - 1))
				       	+ temp.z*(S*v_a.a - v_a.b*v_a.c*(C - 1));
				new_c.z = temp.z*(C - v_a.c*v_a.c*(C - 1)) 
					+ temp.x*(S*v_a.b - v_a.a*v_a.c*(C - 1)) 
					- temp.y*(S*v_a.a + v_a.b*v_a.c*(C - 1));
				new_c = new_c.add(point_a);
				//面ACB，原始面
				side.Mybegin = point_a;
				side.Myend = point_b;
				temp_face.side.append(side);
				side.Mybegin = point_b;
				side.Myend = new_c;
				temp_face.side.append(side);
				side.Mybegin = new_c;
				side.Myend = point_a;
				temp_face.side.append(side);
				temp_face.type = 0;
				Origface.append(temp_face);
				temp_face.side.clear();
				//面ACE，补面
				side.Mybegin = point_a;
				side.Myend = new_c;
				temp_face.side.append(side);
				side.Mybegin = new_c;
				side.Myend = point_c;
				temp_face.side.append(side);
				side.Mybegin = point_c;
				side.Myend = point_a;
				temp_face.side.append(side);
				temp_face.type = 4;
				Origface.append(temp_face);
				temp_face.side.clear();
				//面BEC，补面
				side.Mybegin = point_b;
				side.Myend = point_c;
				temp_face.side.append(side);
				side.Mybegin = point_c;
				side.Myend = new_c;
				temp_face.side.append(side);
				side.Mybegin = new_c;
				side.Myend = point_b;
				temp_face.side.append(side);
				temp_face.type = 4;
				Origface.append(temp_face);
				temp_face.side.clear();
			}
		}
		//边长CD=EF=l1，BE=l2，BF=l3，BC=l4，BD=l5
		float l1,l2,l3,l4,l5,l_bo;
		//角度的余弦值EBO=CBD=abt，FEB=afn，BCD=ath，FBE=alp，
		float abt,afn,ath,alp;
		float v,w,g;
		MyPoint H,P,G;
		l1 = point_c.dis(point_d);
		l2 = point_b.dis(point_e);
		l3 = point_b.dis(point_f);
		l4 = point_b.dis(point_c);
		l5 = point_b.dis(point_d);
		abt = acos((l4*l4+l5*l5-l1*l1)/(2*l4*l5));
		afn = acos((l1*l1+l2*l2-l3*l3)/(2*l1*l2));
		ath = acos((l1*l1+l4*l4-l5*l5)/(2*l1*l4));
		alp = acos((l2*l2+l3*l3-l1*l1)/(2*l2*l3));
		if(l2<l4)
		{
			if(alp<=abt)
			{
				//面BEF
				side.Mybegin = point_e;
				side.Myend = point_b;
				temp_face.side.append(side);
				side.Mybegin = point_b;
				side.Myend = point_f;
				temp_face.side.append(side);
				side.Mybegin = point_f;
				side.Myend = point_e;
				temp_face.side.append(side);
				temp_face.type = 0;
				Targface.append(temp_face);
				temp_face.side.clear();
				/////////////////////////////////////////////
				if(alp==abt)
				{
					v = l2/l4;
					w = l3/l5;
					H.x = v*(point_c.x-point_b.x)+point_b.x;
					H.y = v*(point_c.y-point_b.y)+point_b.y;
					H.z = v*(point_c.z-point_b.z)+point_b.z;
					P.x = w*(point_d.x-point_b.x)+point_b.x;
					P.y = w*(point_d.y-point_b.y)+point_b.y;
					P.z = w*(point_d.z-point_b.z)+point_b.z;
					//面BEF，补面
					side.Mybegin = point_b;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = P;
					temp_face.side.append(side);
					side.Mybegin = P;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Origface.append(temp_face);
					temp_face.side.clear();
					//面EFDC，补面
					side.Mybegin = H;
					side.Myend = P;
					temp_face.side.append(side);
					side.Mybegin = P;
					side.Myend = point_d;
					temp_face.side.append(side);
					side.Mybegin = point_d;
					side.Myend = point_c;
					temp_face.side.append(side);
					side.Mybegin = point_c;
					side.Myend = H;
					temp_face.side.append(side);
					temp_face.type = 4;
					Origface.append(temp_face);
					temp_face.side.clear();
				}else{
					v = l2/l4;
					H.x = v*(point_c.x-point_b.x)+point_b.x;
					H.y = v*(point_c.y-point_b.y)+point_b.y;
					H.z = v*(point_c.z-point_b.z)+point_b.z;
					w = (l4*sin(alp))/(l1*sin(alp+ath));
					P.x = w*(point_d.x-point_c.x)+point_c.x;
					P.y = w*(point_d.y-point_c.y)+point_c.y;
					P.z = w*(point_d.z-point_c.z)+point_c.z;
					l_bo = P.dis(point_b);
					g = (l2*sin(afn))/(l_bo*sin(alp+afn));
					G.x = g*(P.x-point_b.x)+point_b.x;
					G.y = g*(P.y-point_b.y)+point_b.y;
					G.z = g*(P.z-point_b.z)+point_b.z;
					//面BEF，补面
					side.Mybegin = point_b;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = G;
					temp_face.side.append(side);
					side.Mybegin = G;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Origface.append(temp_face);
					temp_face.side.clear();
					//面ECPF，补面
					side.Mybegin = H;
					side.Myend = point_c;
					temp_face.side.append(side);
					side.Mybegin = point_c;
					side.Myend = P;
					temp_face.side.append(side);
					side.Mybegin = P;
					side.Myend = G;
					temp_face.side.append(side);
					side.Mybegin = G;
					side.Myend = H;
					temp_face.side.append(side);
					temp_face.type = 4;
					Origface.append(temp_face);
					temp_face.side.clear();
					//面BPD，补面
					side.Mybegin = point_b;
					side.Myend = P;
					temp_face.side.append(side);
					side.Mybegin = P;
					side.Myend = point_d;
					temp_face.side.append(side);
					side.Mybegin = point_d;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 4;
					Origface.append(temp_face);
					temp_face.side.clear();
				}
				/////////////////////////////////////////////
			}else{
				l_bo = (sin(afn)*l2)/sin(afn+abt);
				if(l_bo<=l5)
				{
					v = (l2*sin(abt))/(l1*sin(abt+afn));
					H.x = v*(point_f.x-point_e.x)+point_e.x;
					H.y = v*(point_f.y-point_e.y)+point_e.y;
					H.z = v*(point_f.z-point_e.z)+point_e.z;
					//面BEH
					side.Mybegin = point_b;
					side.Myend = point_e;
					temp_face.side.append(side);
					side.Mybegin = point_e;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Targface.append(temp_face);
					temp_face.side.clear();
					//面BHF
					side.Mybegin = point_b;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_f;
					temp_face.side.append(side);
					side.Mybegin = point_f;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 2;
					Targface.append(temp_face);
					temp_face.side.clear();
					/////////////////////////////////////////////////
					if(l_bo==l5)
					{
						v = l2/l4;
						H.x = v*(point_c.x-point_b.x)+point_b.x;
						H.y = v*(point_c.y-point_b.y)+point_b.y;
						H.z = v*(point_c.z-point_b.z)+point_b.z;
						//面BEF，补面
						side.Mybegin = point_b;
						side.Myend = H;
						temp_face.side.append(side);
						side.Mybegin = H;
						side.Myend = point_d;
						temp_face.side.append(side);
						side.Mybegin = point_d;
						side.Myend = point_b;
						temp_face.side.append(side);
						temp_face.type = 0;
						Origface.append(temp_face);
						temp_face.side.clear();
						//面ECD，补面
						side.Mybegin = H;
						side.Myend = point_c;
						temp_face.side.append(side);
						side.Mybegin = point_c;
						side.Myend = point_d;
						temp_face.side.append(side);
						side.Mybegin = point_d;
						side.Myend = H;
						temp_face.side.append(side);
						temp_face.type = 4;
						Origface.append(temp_face);
						temp_face.side.clear();
					}else{
						v = l2/l4;
						H.x = v*(point_c.x-point_b.x)+point_b.x;
						H.y = v*(point_c.y-point_b.y)+point_b.y;
						H.z = v*(point_c.z-point_b.z)+point_b.z;
						w = l_bo/l5;
						P.x = w*(point_d.x-point_b.x)+point_b.x;
						P.y = w*(point_d.y-point_b.y)+point_b.y;
						P.z = w*(point_d.z-point_b.z)+point_b.z;
						//面BHP，补面
						side.Mybegin = point_b;
						side.Myend = H;
						temp_face.side.append(side);
						side.Mybegin = H;
						side.Myend = P;
						temp_face.side.append(side);
						side.Mybegin = P;
						side.Myend = point_b;
						temp_face.side.append(side);
						temp_face.type = 0;
						Origface.append(temp_face);
						temp_face.side.clear();
						//面HCDP，补面
						side.Mybegin = H;
						side.Myend = point_c;
						temp_face.side.append(side);
						side.Mybegin = point_c;
						side.Myend = point_d;
						temp_face.side.append(side);
						side.Mybegin = point_d;
						side.Myend = P;
						temp_face.side.append(side);
						side.Mybegin = P;
						side.Myend = H;
						temp_face.side.append(side);
						temp_face.type = 4;
						Origface.append(temp_face);
						temp_face.side.clear();
					}
					/////////////////////////////////////////////////
				}else{
					v = ((l4-l2)*sin(ath))/(l1*sin(afn-ath));
					H.x = v*(point_f.x-point_e.x)+point_e.x;
					H.y = v*(point_f.y-point_e.y)+point_e.y;
					H.z = v*(point_f.z-point_e.z)+point_e.z;
					w = (sin(abt)*l2)/(l1*sin(afn+abt));
					P.x = w*(point_f.x-point_e.x)+point_e.x;
					P.y = w*(point_f.y-point_e.y)+point_e.y;
					P.z = w*(point_f.z-point_e.z)+point_e.z;
					g = l5/l_bo;
					G.x = g*(P.x-point_b.x)+point_b.x;
					G.y = g*(P.y-point_b.y)+point_b.y;
					G.z = g*(P.z-point_b.z)+point_b.z;
					//面BEH
					side.Mybegin = point_b;
					side.Myend = point_e;
					temp_face.side.append(side);
					side.Mybegin = point_e;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Targface.append(temp_face);
					temp_face.side.clear();
					//面BHG
					side.Mybegin = point_b;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = G;
					temp_face.side.append(side);
					side.Mybegin = G;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Targface.append(temp_face);
					temp_face.side.clear();
					//面GHF
					side.Mybegin = G;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_f;
					temp_face.side.append(side);
					side.Mybegin = point_f;
					side.Myend = G;
					temp_face.side.append(side);
					temp_face.type = 2;
					Targface.append(temp_face);
					temp_face.side.clear();
					//面BGF
					side.Mybegin = point_b;
					side.Myend = G;
					temp_face.side.append(side);
					side.Mybegin = G;
					side.Myend = point_f;
					temp_face.side.append(side);
					side.Mybegin = point_f;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 2;
					Targface.append(temp_face);
					temp_face.side.clear();
					//////////////////////////////////////////
					v = l2/l4;
					H.x = v*(point_c.x-point_b.x)+point_b.x;
					H.y = v*(point_c.y-point_b.y)+point_b.y;
					H.z = v*(point_c.z-point_b.z)+point_b.z;
					w = ((l4-l2)*sin(afn))/(l1*sin(afn-ath));
					P.x = w*(point_d.x-point_c.x)+point_c.x;
					P.y = w*(point_d.y-point_c.y)+point_c.y;
					P.z = w*(point_d.z-point_c.z)+point_c.z;
					//面BHPD
					side.Mybegin = point_b;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = P;
					temp_face.side.append(side);
					side.Mybegin = P;
					side.Myend = point_d;
					temp_face.side.append(side);
					side.Mybegin = point_d;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Origface.append(temp_face);
					temp_face.side.clear();
					//面HCP
					side.Mybegin = H;
					side.Myend = point_c;
					temp_face.side.append(side);
					side.Mybegin = point_c;
					side.Myend = P;
					temp_face.side.append(side);
					side.Mybegin = P;
					side.Myend = H;
					temp_face.side.append(side);
					temp_face.type = 4;
					Origface.append(temp_face);
					temp_face.side.clear();
					//////////////////////////////////////////
				}				
			}
		}else if(l2>l4)
		{
			if(alp>abt)
			{
				v = (l2*sin(abt))/(l1*sin(afn+abt));
				H.x = v*(point_f.x-point_e.x)+point_e.x;
				H.y = v*(point_f.y-point_e.y)+point_e.y;
				H.z = v*(point_f.z-point_e.z)+point_e.z;
				l_bo = H.dis(point_b);				
				g = l5/l_bo;
				G.x = g*(H.x-point_b.x)+point_b.x;
				G.y = g*(H.y-point_b.y)+point_b.y;
				G.z = g*(H.z-point_b.z)+point_b.z;
				w = l4/l2;
				P.x = g*(point_e.x-point_b.x)+point_b.x;
				P.y = g*(point_e.y-point_b.y)+point_b.y;
				P.z = g*(point_e.z-point_b.z)+point_b.z;
				//面BPG
				side.Mybegin = point_b;
				side.Myend = P;
				temp_face.side.append(side);
				side.Mybegin = P;
				side.Myend = G;
				temp_face.side.append(side);
				side.Mybegin = G;
				side.Myend = point_b;
				temp_face.side.append(side);
				temp_face.type = 0;
				Targface.append(temp_face);
				temp_face.side.clear();
				//面PEFG
				side.Mybegin = P;
				side.Myend = point_e;
				temp_face.side.append(side);
				side.Mybegin = point_e;
				side.Myend = point_f;
				temp_face.side.append(side);
				side.Mybegin = point_f;
				side.Myend = G;
				temp_face.side.append(side);
				side.Mybegin = G;
				side.Myend = P;
				temp_face.side.append(side);
				temp_face.type = 2;
				Targface.append(temp_face);
				temp_face.side.clear();
				//面BGF
				side.Mybegin = point_b;
				side.Myend = G;
				temp_face.side.append(side);
				side.Mybegin = G;
				side.Myend = point_f;
				temp_face.side.append(side);
				side.Mybegin = point_f;
				side.Myend = point_b;
				temp_face.side.append(side);
				temp_face.type = 2;
				Targface.append(temp_face);
				temp_face.side.clear();
				////////////////////////////////////////////////
				//面HCP
				side.Mybegin = point_b;
				side.Myend = point_c;
				temp_face.side.append(side);
				side.Mybegin = point_c;
				side.Myend = point_d;
				temp_face.side.append(side);
				side.Mybegin = point_d;
				side.Myend = point_b;
				temp_face.side.append(side);
				temp_face.type = 0;
				Origface.append(temp_face);
				temp_face.side.clear();
				////////////////////////////////////////////////
			}else{
				l_bo = (l4*sin(ath))/sin(ath+alp);
				if(l_bo>l3)
				{
					v = ((l2-l4)*sin(ath))/(l1*sin(ath-afn));
					H.x = v*(point_f.x-point_e.x)+point_e.x;
					H.y = v*(point_f.y-point_e.y)+point_e.y;
					H.z = v*(point_f.z-point_e.z)+point_e.z;
					w = l4/l2;
					P.x = w*(point_e.x-point_b.x)+point_b.x;
					P.y = w*(point_e.y-point_b.y)+point_b.y;
					P.z = w*(point_e.z-point_b.z)+point_b.z;
					//面BPHF
					side.Mybegin = point_b;
					side.Myend = P;
					temp_face.side.append(side);
					side.Mybegin = P;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_f;
					temp_face.side.append(side);
					side.Mybegin = point_f;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Targface.append(temp_face);
					temp_face.side.clear();
					//面PEH
					side.Mybegin = P;
					side.Myend = point_e;
					temp_face.side.append(side);
					side.Mybegin = point_e;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = P;
					temp_face.side.append(side);
					temp_face.type = 2;
					Targface.append(temp_face);
					temp_face.side.clear();
					////////////////////////////////////////////////
					v = ((l2-l4)*sin(afn))/(l1*sin(ath-afn));
					H.x = v*(point_d.x-point_c.x)+point_c.x;
					H.y = v*(point_d.y-point_c.y)+point_c.y;
					H.z = v*(point_d.z-point_c.z)+point_c.z;
					w = (l4*sin(alp))/(l1*sin(ath+alp));
					P.x = w*(point_d.x-point_c.x)+point_c.x;
					P.y = w*(point_d.y-point_c.y)+point_c.y;
					P.z = w*(point_d.z-point_c.z)+point_c.z;
					g = (l2*sin(afn))/(l_bo*sin(alp+afn));
					G.x = g*(P.x-point_b.x)+point_b.x;
					G.y = g*(P.y-point_b.y)+point_b.y;
					G.z = g*(P.z-point_b.z)+point_b.z;
					//面BCHG
					side.Mybegin = point_b;
					side.Myend = point_c;
					temp_face.side.append(side);
					side.Mybegin = point_c;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = G;
					temp_face.side.append(side);
					side.Mybegin = G;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Origface.append(temp_face);
					temp_face.side.clear();
					//面BGD
					side.Mybegin = point_b;
					side.Myend = G;
					temp_face.side.append(side);
					side.Mybegin = G;
					side.Myend = point_d;
					temp_face.side.append(side);
					side.Mybegin = point_d;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 4;
					Origface.append(temp_face);
					temp_face.side.clear();
					//面DGH
					side.Mybegin = point_d;
					side.Myend = G;
					temp_face.side.append(side);
					side.Mybegin = G;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_d;
					temp_face.side.append(side);
					temp_face.type = 4;
					Origface.append(temp_face);
					temp_face.side.clear();
					////////////////////////////////////////////////
				}else if(l_bo==l3)
				{
					w = l4/l2;
					P.x = w*(point_e.x-point_b.x)+point_b.x;
					P.y = w*(point_e.y-point_b.y)+point_b.y;
					P.z = w*(point_e.z-point_b.z)+point_b.z;
					//面PEF
					side.Mybegin = P;
					side.Myend = point_e;
					temp_face.side.append(side);
					side.Mybegin = point_e;
					side.Myend = point_f;
					temp_face.side.append(side);
					side.Mybegin = point_f;
					side.Myend = P;
					temp_face.side.append(side);
					temp_face.type = 2;
					Targface.append(temp_face);
					temp_face.side.clear();
					//面BPF
					side.Mybegin = point_b;
					side.Myend = P;
					temp_face.side.append(side);
					side.Mybegin = P;
					side.Myend = point_f;
					temp_face.side.append(side);
					side.Mybegin = point_f;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Targface.append(temp_face);
					temp_face.side.clear();
					//////////////////////////////////////////////
					v = ((l2-l4)*sin(afn))/(l1*sin(ath-afn));
					H.x = v*(point_d.x-point_c.x)+point_c.x;
					H.y = v*(point_d.y-point_c.y)+point_c.y;
					H.z = v*(point_d.z-point_c.z)+point_c.z;
					//面BCH
					side.Mybegin = point_b;
					side.Myend = point_c;
					temp_face.side.append(side);
					side.Mybegin = point_c;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Origface.append(temp_face);
					temp_face.side.clear();
					//面BHD
					side.Mybegin = point_b;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_d;
					temp_face.side.append(side);
					side.Mybegin = point_d;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 4;
					Origface.append(temp_face);
					temp_face.side.clear();
					//////////////////////////////////////////////
				}else{
					w = l4/l2;
					P.x = w*(point_e.x-point_b.x)+point_b.x;
					P.y = w*(point_e.y-point_b.y)+point_b.y;
					P.z = w*(point_e.z-point_b.z)+point_b.z;
					v = l_bo/l3;
					H.x = v*(point_f.x-point_b.x)+point_b.x;
					H.y = v*(point_f.y-point_b.y)+point_b.y;
					H.z = v*(point_f.z-point_b.z)+point_b.z;
					//面BPH
					side.Mybegin = point_b;
					side.Myend = P;
					temp_face.side.append(side);
					side.Mybegin = P;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Targface.append(temp_face);
					temp_face.side.clear();
					//面PEFH
					side.Mybegin = P;
					side.Myend = point_e;
					temp_face.side.append(side);
					side.Mybegin = point_e;
					side.Myend = point_f;
					temp_face.side.append(side);
					side.Mybegin = point_f;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = P;
					temp_face.side.append(side);
					temp_face.type = 2;
					Targface.append(temp_face);
					temp_face.side.clear();
					////////////////////////////////////////////////
					if((int)(abt*1000000)==(int)(alp*1000000))
					{
						//面HCP
						side.Mybegin = point_b;
						side.Myend = point_c;
						temp_face.side.append(side);
						side.Mybegin = point_c;
						side.Myend = point_d;
						temp_face.side.append(side);
						side.Mybegin = point_d;
						side.Myend = point_b;
						temp_face.side.append(side);
						temp_face.type = 0;
						Origface.append(temp_face);
						temp_face.side.clear();
					}else{
						v = (l4*sin(alp))/(l1*sin(alp+ath));
						H.x = v*(point_d.x-point_c.x)+point_c.x;
						H.y = v*(point_d.y-point_c.y)+point_c.y;
						H.z = v*(point_d.z-point_c.z)+point_c.z;
						//面BCH
						side.Mybegin = point_b;
						side.Myend = point_c;
						temp_face.side.append(side);
						side.Mybegin = point_c;
						side.Myend = H;
						temp_face.side.append(side);
						side.Mybegin = H;
						side.Myend = point_b;
						temp_face.side.append(side);
						temp_face.type = 0;
						Origface.append(temp_face);
						temp_face.side.clear();
						//面BHD
						side.Mybegin = point_b;
						side.Myend = H;
						temp_face.side.append(side);
						side.Mybegin = H;
						side.Myend = point_d;
						temp_face.side.append(side);
						side.Mybegin = point_d;
						side.Myend = point_b;
						temp_face.side.append(side);
						temp_face.type = 4;
						Origface.append(temp_face);
						temp_face.side.clear();
					}
					////////////////////////////////////////////////
				}
			}
		}else{
			if(alp<abt)
			{
				if(afn<ath)
				{
					//面BEF
					side.Mybegin = point_b;
					side.Myend = point_e;
					temp_face.side.append(side);
					side.Mybegin = point_e;
					side.Myend = point_f;
					temp_face.side.append(side);
					side.Mybegin = point_f;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Targface.append(temp_face);
					temp_face.side.clear();
					///////////////////////////////////////
					w = (l4*sin(alp))/(l1*sin(ath+alp));
					P.x = w*(point_d.x-point_c.x)+point_c.x;
					P.y = w*(point_d.y-point_c.y)+point_c.y;
					P.z = w*(point_d.z-point_c.z)+point_c.z;
					l_bo = l4*sin(ath)/sin(alp+ath);
					g = (l2*sin(afn))/(l_bo*sin(alp+afn));
					G.x = g*(P.x-point_b.x)+point_b.x;
					G.y = g*(P.y-point_b.y)+point_b.y;
					G.z = g*(P.z-point_b.z)+point_b.z;
					//面BCG
					side.Mybegin = point_b;
					side.Myend = point_c;
					temp_face.side.append(side);
					side.Mybegin = point_c;
					side.Myend = G;
					temp_face.side.append(side);
					side.Mybegin = G;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Origface.append(temp_face);
					temp_face.side.clear();
					//面BGD
					side.Mybegin = point_b;
					side.Myend = G;
					temp_face.side.append(side);
					side.Mybegin = G;
					side.Myend = point_d;
					temp_face.side.append(side);
					side.Mybegin = point_d;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 4;
					Origface.append(temp_face);
					temp_face.side.clear();
					//面DGC
					side.Mybegin = point_d;
					side.Myend = G;
					temp_face.side.append(side);
					side.Mybegin = G;
					side.Myend = point_c;
					temp_face.side.append(side);
					side.Mybegin = point_c;
					side.Myend = point_d;
					temp_face.side.append(side);
					temp_face.type = 4;
					Origface.append(temp_face);
					temp_face.side.clear();
					///////////////////////////////////////
				}else{
					v = (l2*sin(ath))/(l3*sin(ath+alp)); 
					H.x = v*(point_f.x-point_b.x)+point_b.x;
					H.y = v*(point_f.y-point_b.y)+point_b.y;
					H.z = v*(point_f.z-point_b.z)+point_b.z;
					//面BEH
					side.Mybegin = point_b;
					side.Myend = point_e;
					temp_face.side.append(side);
					side.Mybegin = point_e;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Targface.append(temp_face);
					temp_face.side.clear();
					//面EFH
					side.Mybegin = point_e;
					side.Myend = point_f;
					temp_face.side.append(side);
					side.Mybegin = point_f;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_e;
					temp_face.side.append(side);
					temp_face.type = 2;
					Targface.append(temp_face);
					temp_face.side.clear();
					////////////////////////////////////////////////////
					v = (l4*sin(alp))/(l1*sin(alp+ath));
					H.x = v*(point_d.x-point_c.x)+point_c.x;
					H.y = v*(point_d.y-point_c.y)+point_c.y;
					H.z = v*(point_d.z-point_c.z)+point_c.z;
					//面BCH
					side.Mybegin = point_b;
					side.Myend = point_c;
					temp_face.side.append(side);
					side.Mybegin = point_c;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Origface.append(temp_face);
					temp_face.side.clear();
					//面BHD
					side.Mybegin = point_b;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_d;
					temp_face.side.append(side);
					side.Mybegin = point_d;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 4;
					Origface.append(temp_face);
					temp_face.side.clear();
					////////////////////////////////////////////////////
				}
			}else if (alp == abt)
			{
				if(l3>l5)
				{
					v = l5/l3;
					H.x = v*(point_f.x-point_b.x)+point_b.x;
					H.y = v*(point_f.y-point_b.y)+point_b.y;
					H.z = v*(point_f.z-point_b.z)+point_b.z;
					//面BEH
					side.Mybegin = point_b;
					side.Myend = point_e;
					temp_face.side.append(side);
					side.Mybegin = point_e;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Targface.append(temp_face);
					temp_face.side.clear();
					//面EFH
					side.Mybegin = point_e;
					side.Myend = point_f;
					temp_face.side.append(side);
					side.Mybegin = point_f;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_e;
					temp_face.side.append(side);
					temp_face.type = 2;
					Targface.append(temp_face);
					temp_face.side.clear();
					/////////////////////////////////////////////
					//面HCP
					side.Mybegin = point_b;
					side.Myend = point_c;
					temp_face.side.append(side);
					side.Mybegin = point_c;
					side.Myend = point_d;
					temp_face.side.append(side);
					side.Mybegin = point_d;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Origface.append(temp_face);
					temp_face.side.clear();
					/////////////////////////////////////////////
				}else{
					//面BEF
					side.Mybegin = point_b;
					side.Myend = point_e;
					temp_face.side.append(side);
					side.Mybegin = point_e;
					side.Myend = point_f;
					temp_face.side.append(side);
					side.Mybegin = point_f;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Targface.append(temp_face);
					temp_face.side.clear();
					///////////////////////////////////////////////
					v = l3/l5;
					H.x = v*(point_d.x-point_b.x)+point_b.x;
					H.y = v*(point_d.y-point_b.y)+point_b.y;
					H.z = v*(point_d.z-point_b.z)+point_b.z;
					//面HCP
					side.Mybegin = point_b;
					side.Myend = point_c;
					temp_face.side.append(side);
					side.Mybegin = point_c;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Origface.append(temp_face);
					temp_face.side.clear();
					//面HCP
					side.Mybegin = H;
					side.Myend = point_c;
					temp_face.side.append(side);
					side.Mybegin = point_c;
					side.Myend = point_d;
					temp_face.side.append(side);
					side.Mybegin = point_d;
					side.Myend = H;
					temp_face.side.append(side);
					temp_face.type = 0;
					Origface.append(temp_face);
					temp_face.side.clear();
					///////////////////////////////////////////////
				}
			}else{
				if(afn>ath)
				{
					v = sin(abt+ath)/sin(afn+abt);
					H.x = v*(point_f.x-point_e.x)+point_e.x;
					H.y = v*(point_f.y-point_e.y)+point_e.y;
					H.z = v*(point_f.z-point_e.z)+point_e.z;
					l_bo = H.dis(point_b);				
					g = (l4*sin(ath))/(l_bo*sin(abt+ath));
					G.x = g*(H.x-point_b.x)+point_b.x;
					G.y = g*(H.y-point_b.y)+point_b.y;
					G.z = g*(H.z-point_b.z)+point_b.z;
					//面BEG
					side.Mybegin = point_b;
					side.Myend = point_e;
					temp_face.side.append(side);
					side.Mybegin = point_e;
					side.Myend = G;
					temp_face.side.append(side);
					side.Mybegin = G;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Targface.append(temp_face);
					temp_face.side.clear();
					//面GEF
					side.Mybegin = G;
					side.Myend = point_e;
					temp_face.side.append(side);
					side.Mybegin = point_e;
					side.Myend = point_f;
					temp_face.side.append(side);
					side.Mybegin = point_f;
					side.Myend = G;
					temp_face.side.append(side);
					temp_face.type = 2;
					Targface.append(temp_face);
					temp_face.side.clear();
					//面BGF
					side.Mybegin = point_b;
					side.Myend = G;
					temp_face.side.append(side);
					side.Mybegin = G;
					side.Myend = point_f;
					temp_face.side.append(side);
					side.Mybegin = point_f;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 2;
					Targface.append(temp_face);
					temp_face.side.clear();
					////////////////////////////////////////////
					//面HCP
					side.Mybegin = point_b;
					side.Myend = point_c;
					temp_face.side.append(side);
					side.Mybegin = point_c;
					side.Myend = point_d;
					temp_face.side.append(side);
					side.Mybegin = point_d;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Origface.append(temp_face);
					temp_face.side.clear();
					////////////////////////////////////////////
				}else{
					v = sin(abt+ath)/sin(afn+abt);
					H.x = v*(point_f.x-point_e.x)+point_e.x;
					H.y = v*(point_f.y-point_e.y)+point_e.y;
					H.z = v*(point_f.z-point_e.z)+point_e.z;
					//面BEH
					side.Mybegin = point_b;
					side.Myend = point_e;
					temp_face.side.append(side);
					side.Mybegin = point_e;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Targface.append(temp_face);
					temp_face.side.clear();
					//面BHF
					side.Mybegin = point_b;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_f;
					temp_face.side.append(side);
					side.Mybegin = point_f;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 2;
					Targface.append(temp_face);
					temp_face.side.clear();
					/////////////////////////////////////////////////////
					v = (l2*sin(afn))/(l5*sin(abt+afn));
					H.x = v*(point_d.x-point_b.x)+point_b.x;
					H.y = v*(point_d.y-point_b.y)+point_b.y;
					H.z = v*(point_d.z-point_b.z)+point_b.z;
					//面HCP
					side.Mybegin = point_b;
					side.Myend = point_c;
					temp_face.side.append(side);
					side.Mybegin = point_c;
					side.Myend = H;
					temp_face.side.append(side);
					side.Mybegin = H;
					side.Myend = point_b;
					temp_face.side.append(side);
					temp_face.type = 0;
					Origface.append(temp_face);
					temp_face.side.clear();
					//面HCP
					side.Mybegin = H;
					side.Myend = point_c;
					temp_face.side.append(side);
					side.Mybegin = point_c;
					side.Myend = point_d;
					temp_face.side.append(side);
					side.Mybegin = point_d;
					side.Myend = H;
					temp_face.side.append(side);
					temp_face.type = 0;
					Origface.append(temp_face);
					temp_face.side.clear();
					/////////////////////////////////////////////////////
				}
			}
		}
	}
}


bool Morphing::samedir(MyPoint a, MyPoint b,MyPoint c, MyPoint d)
{
	
	MyVector ab,ac,ae;
	ab = a.vet(b);
	ac = a.vet(c);
	ae = a.vet(d);
	if(ab.plus(ac).dot(ac.plus(ae))>=0)
		return true;
	return false;
}

MyVector Morphing::normal(MyVector in)
{
	float norm;
	MyVector v;
	v = in;
	norm = sqrt((v.a)*(v.a)+(v.b)*(v.b)+(v.c)*(v.c));
	if(norm>0)
	{
		v.a = v.a/norm;
		v.b = v.b/norm;
		v.c = v.c/norm;
	}
	return v;
}

void Morphing::Bottom(int n)
{
	MyPoint temp;
	aup.clear();
	down.clear();
	for(int i=0;i<=720;i++)
	{
		float arc;
		arc = 2*PI/720;
		if(n!=7)
		{
			temp.x = r*cos(arc*i)+x;
			temp.y = r*sin(arc*i)+y;
			temp.z = h/2+ext;
			aup.append(temp);
		}else{
			temp.x = r*cos(arc*i)*cos(roll);
			temp.y = r*sin(arc*i);		
			temp.z = h/2-r*cos(arc*i)*sin(roll);
			aup.append(temp);
		}
		temp.x = r*cos(arc*i);
		temp.y = r*sin(arc*i);
		temp.z = h/2;
		bup.append(temp);
		temp.x = R*cos(arc*i);
		temp.y = R*sin(arc*i);
		temp.z = -h/2;
		down.append(temp);
		
	}
}

