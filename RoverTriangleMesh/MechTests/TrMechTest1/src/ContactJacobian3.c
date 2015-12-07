#include "LagrangianModel.h"
#include <math.h>
void ContactJacobian3(CJ,q)
double CJ[63];
double q[21];
{
  double t1;
  double t10;
  double t11;
  double t12;
  double t14;
  double t15;
  double t17;
  double t19;
  double t2;
  double t21;
  double t23;
  double t25;
  double t27;
  double t28;
  double t3;
  double t30;
  double t4;
  double t5;
  double t6;
  double t7;
  double t8;
  {
    CJ[0] = 1.0;
    CJ[1] = 0.0;
    CJ[2] = 0.0;
    CJ[3] = 0.0;
    CJ[4] = 1.0;
    CJ[5] = 0.0;
    CJ[6] = 0.0;
    CJ[7] = 0.0;
    CJ[8] = 1.0;
    t1 = q[3];
    t2 = cos(t1);
    t3 = q[4];
    t4 = sin(t3);
    t5 = t2*t4;
    t6 = q[5];
    t7 = cos(t6);
    t8 = t5*t7;
    t10 = sin(t1);
    t11 = sin(t6);
    t12 = t10*t11;
    t14 = t10*t4;
    t15 = t14*t7;
    t17 = t2*t11;
    CJ[9] = 0.4705*t8+0.4705*t12+0.23375*t15-0.23375*t17;
    t19 = t5*t11;
    t21 = t10*t7;
    t23 = t14*t11;
    t25 = t7*t2;
    CJ[10] = 0.4705*t19-0.4705*t21+0.23375*t23+0.23375*t25;
    t27 = cos(t3);
    t28 = t2*t27;
    t30 = t10*t27;
    CJ[11] = 0.4705*t28+0.23375*t30;
    CJ[12] = -0.4025001*t7*t4+0.4705*t30*t7-0.23375*t28*t7;
    CJ[13] = -0.4025001*t4*t11+0.4705*t30*t11-0.23375*t28*t11;
    CJ[14] = -0.4025001*t27-0.4705*t14+0.23375*t5;
    CJ[15] = -0.4025001*t27*t11-0.4705*t23-0.4705*t25+0.23375*t19-0.23375*t21;
    CJ[16] = 0.4025001*t27*t7+0.4705*t15-0.4705*t17-0.23375*t8-0.23375*t12;
    CJ[17] = 0.0;
    CJ[18] = 0.0;
    CJ[19] = 0.0;
    CJ[20] = 0.0;
    CJ[21] = 0.0;
    CJ[22] = 0.0;
    CJ[23] = 0.0;
    CJ[24] = 0.0;
    CJ[25] = 0.0;
    CJ[26] = 0.0;
    CJ[27] = 0.0;
    CJ[28] = 0.0;
    CJ[29] = 0.0;
    CJ[30] = 0.0;
    CJ[31] = 0.0;
    CJ[32] = 0.0;
    CJ[33] = 0.0;
    CJ[34] = 0.0;
    CJ[35] = 0.0;
    CJ[36] = 0.0;
    CJ[37] = 0.0;
    CJ[38] = 0.0;
    CJ[39] = 0.0;
    CJ[40] = 0.0;
    CJ[41] = 0.0;
    CJ[42] = 0.0;
    CJ[43] = 0.0;
    CJ[44] = 0.0;
    CJ[45] = 0.0;
    CJ[46] = 0.0;
    CJ[47] = 0.0;
    CJ[48] = 0.0;
    CJ[49] = 0.0;
    CJ[50] = 0.0;
    CJ[51] = 0.0;
    CJ[52] = 0.0;
    CJ[53] = 0.0;
    CJ[54] = 0.0;
    CJ[55] = 0.0;
    CJ[56] = 0.0;
    CJ[57] = 0.0;
    CJ[58] = 0.0;
    CJ[59] = 0.0;
    CJ[60] = 0.0;
    CJ[61] = 0.0;
    CJ[62] = 0.0;
    return;
  }
}

