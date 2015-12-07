#include "LagrangianModel.h"
#include <math.h>
void RRV(RootRotation,AngleT,q)
double RootRotation[4];
double AngleT[3];
double q[21];
{
  double t1;
  double t10;
  double t12;
  double t16;
  double t2;
  double t21;
  double t22;
  double t24;
  double t25;
  double t3;
  double t4;
  double t5;
  double t6;
  double t7;
  double t9;
  {
    t1 = q[3];
    t2 = cos(t1);
    t3 = q[4];
    t4 = sin(t3);
    t5 = t2*t4;
    t6 = q[5];
    t7 = sin(t6);
    t9 = sin(t1);
    t10 = cos(t6);
    t12 = cos(t3);
    t16 = t9*t4;
    t21 = t12*t10/2.0+t16*t7/2.0+t2*t10/2.0+t2*t12/2.0-1.0/2.0;
    t22 = t21*t21;
    t24 = sqrt(1.0-t22);
    t25 = 1/t24;
    RootRotation[0] = (-t5*t7+t9*t10+t9*t12)*t25/2.0;
    RootRotation[1] = (-t4-t5*t10-t9*t7)*t25/2.0;
    RootRotation[2] = (-t16*t10+t2*t7+t12*t7)*t25/2.0;
    RootRotation[3] = acos(t21);
    return;
  }
}

