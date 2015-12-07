#include "LagrangianModel.h"
#include <math.h>
void PRV(PlaneRotation,AngleT,q)
double PlaneRotation[4];
double AngleT[3];
double q[21];
{
  double t1;
  double t10;
  double t11;
  double t12;
  double t17;
  double t2;
  double t21;
  double t22;
  double t24;
  double t25;
  double t3;
  double t4;
  double t6;
  double t7;
  double t9;
  {
    t1 = AngleT[2];
    t2 = sin(t1);
    t3 = AngleT[1];
    t4 = cos(t3);
    t6 = AngleT[0];
    t7 = cos(t6);
    t9 = cos(t1);
    t10 = sin(t3);
    t11 = t9*t10;
    t12 = sin(t6);
    t17 = t2*t10;
    t21 = t4*t7/2.0+t9*t7/2.0+t17*t12/2.0+t4*t9/2.0-1.0/2.0;
    t22 = t21*t21;
    t24 = sqrt(1.0-t22);
    t25 = 1/t24;
    PlaneRotation[0] = (t2*t4+t2*t7-t11*t12)*t25/2.0;
    PlaneRotation[1] = (t2*t12+t11*t7+t10)*t25/2.0;
    PlaneRotation[2] = (t4*t12+t9*t12-t17*t7)*t25/2.0;
    PlaneRotation[3] = acos(t21);
    return;
  }
}

