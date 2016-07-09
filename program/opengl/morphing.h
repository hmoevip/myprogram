#ifndef TRANSLATION_H
#define TRANSLATION_H

#include "MyClass.h"

#include <math.h>
class Morphing
{
	public:
		Morphing();
		~Morphing();
	        void Init(float *a,int fn);
		QVector <MyFace> Origface;
		QVector <MyFace> Targface;
		QVector <MyFace> Two;
		QVector <MyPoint> aup;
		QVector <MyPoint> down;
		QVector <MyPoint> bup;
		
	private:
		//float C[10];
		float r;
		float R;
		float h;
		int k;
		float x;
		float y;
		float diff;
		float ext;
		float roll;
		void ComK(int b);
		
		void SetLocation();
		void RollLocation();
		void TestDraw();

		
		

		void DrawOne();
		void DrawTwo();
		void DrawThr();
		void DrawFor();
		void Bottom(int n);

	        bool samedir(MyPoint a, MyPoint b,MyPoint c, MyPoint d);
		MyVector normal(MyVector in);	
};

#endif

