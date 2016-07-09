#include "carve.h"
#include "reverseCalcu.h"
Carve::Carve()
{
    //数据组数
    //XY缓存，系数矩阵缓存
    std::vector<double> m_x,m_y;
   // QVector<double> x(101), y(101); // initialize with entries 0..100
    m_x.resize(512);
        m_y.resize(512);
        //m_yploy.resize(512);
        for(size_t i =0;i<512;++i)
        {
            m_x[i] = i;
            m_y[i] = 2.32*i*i+1.35*i+12;
          //  m_yploy[i] = 0.005*pow(double(i),2)+0.0012*i+4+randf(-25,25);
        }
   // double BufferX[1024], BufferY[1024], ParaK[6];
   // if (GetXY((const char*)"test.txt", (double*)BufferX, (double*)BufferY, &Amount))
   // return 0;
        size_t n =2;
    czy::Fit fit;
        fit.polyfit(m_x,m_y,n,true);
    printf("方程：y=%gx+%g\r\n误差：ssr:%g,sse=%g,rmse:%g,确定系数:%g",fit.getSlope(),fit.getIntercept()
                ,fit.getSSR(),fit.getSSE(),fit.getRMSE(),fit.getR_square());
   // for (Amount = 0; Amount < sizeof(ParaK) / sizeof(double); Amount++)
     //       printf("ParaK[%d] = %lf!\r\n", Amount, ParaK[Amount]);
    printf("\r\n%g     %g       %g",fit.getFactor(2),fit.getFactor(1),fit.getFactor(0));
    //屏幕暂留
}

Carve::Carve(double s0, Mplace ori, Mplace tar,double v0,double v,double vmax,int pieces,\
             QVector< QVector<double> >& pos,QVector< QVector<double> >&vel ,QVector<double>& time ,int n)
{
    this->qube(s0, ori, tar,v0,v,vmax,pieces,pos,vel,time ,n);
}

void Carve::qube(double s0, Mplace ori, Mplace tar,double v0,double v,double vmax\
                 ,int pieces,QVector< QVector<double> >& pos ,QVector< QVector<double> >& vel ,QVector<double>& time,int n)
{
    double T,hh,t,S,A,V;
    std::vector<double> a(pieces);
    vector< vector<double> > gan(8,vector<double>(pieces,0));
   // double gan[8][1024];
    //double ParaK[8][6];
    double x,y,z;
    double gan_x,gan_y,gan_z;
    MyCalcu *mCalcu = NULL;
    x = tar.x-ori.x;
    y = tar.y-ori.y;
    z = tar.z-ori.z;
    hh = sqrt(x*x+y*y+z*z);
    if(v0==0 && v==0)
        T = 1.875*hh/vmax;
    else
        T = 2*hh/(v0+v);
    for(int i=0;i<pieces;++i)
    {
        a[i] = i*T/pieces;
        time[i] = a[i];
        t = a[i];
        S = s0 + v0*t + (10*hh-6*v0*T-4*v*T)*pow(t/T,3) + (-15*hh+8*v0*T+7*v*T)*pow(t/T,4) + (6*hh-3*v0*T-3*v*T)*pow(t/T,5);
        //暂时可以不算
        //V = v0 + 3*(10*hh/T-6*v0-4*v)*pow(t/T,2) + 4*(-15*hh/T+8*v0+7*v)*pow(t/T,3) + 5*(6*hh/T-3*v0-3*v)*pow(t/T,4);
        //A = (6/T)*(10*hh/T-6*v0-4*v)*(t/T) + (12/T)*(-15*hh/T+8*v0+7*v)*pow(t/T,2) + (20/T)*(6*hh/T-3*v0-3*v)*pow(t/T,3);
        gan_x = x*S/hh + ori.x;//sqrt(S*S/(1 + (y/x)*(y/x) + (z/x)*(z/x)));
        gan_y = y*S/hh + ori.y;
        gan_z = z*S/hh + ori.z;
        //反解
        vector<double> listTemp;
        listTemp.clear();
        //读取并反解
        listTemp = mCalcu->calculate(gan_x,gan_y,gan_z,0,0,0);
        for(int j=0;j<8;++j)
        {
            gan[j][i] = listTemp[j];
            //gangan = listTemp;
        }
    }

    //计算出每根杆的位移曲线
    czy::Fit fit;
    for(int j=0;j<8;++j)
    {
        fit.polyfit(a,gan[j],n-1,false);
        //Cal((const double*)a, (const double*)gan[j], pieces, n, ((double*)ParaK + n*j));
        for(int i=0;i<pieces;++i)
        {
            pos[j][i] = fit.getFactor(5)*pow(time[i],5)+fit.getFactor(4)*pow(time[i],4)+\
                fit.getFactor(3)*pow(time[i],3)+fit.getFactor(2)*pow(time[i],2)+fit.getFactor(1)*time[i]+\
                fit.getFactor(0);
        }
    }

    for(int j=0;j<8;++j)
    {
        for(int i=0;i<pieces;++i)
        {
            vel[j][i] = 5*fit.getFactor(5)*pow(time[i],4)+4*fit.getFactor(4)*pow(time[i],3)+\
                    3*fit.getFactor(3)*pow(time[i],2)+2*fit.getFactor(2)*time[i]+fit.getFactor(1);
        }
    }

}
