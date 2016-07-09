#ifndef CARVE_H
#define CARVE_H
#include "fit.h"
#include <QVector>

class Mplace
{
public:
    double x;
    double y;
    double z;
    Mplace();
    Mplace(double a, double b,double c)
    {
        this->x = a;
        this->y = b;
        this->z = c;
    };
};


class Carve
{
public:
    Carve();
    Carve(double s0, Mplace ori, Mplace tar,double v0,double v,\
          double vmax,int pieces,QVector< QVector<double> >& pos ,\
          QVector< QVector<double> >& vel ,QVector<double>& time ,int n);
    void qube(double s0, Mplace ori, Mplace tar,double v0,\
                double v,double vmax,int pieces,QVector< QVector<double> >& pos ,\
              QVector< QVector<double> >& vel ,QVector<double>& time ,int n);
};

#endif // CARVE_H
