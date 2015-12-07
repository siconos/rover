#include "LagrangianModel.h"
#include <math.h>
void ContactJacobian3(CJ,q)
double CJ[63];
double q[21];
{
  double t1;
  double t10;
  double t11;
  double t13;
  double t14;
  double t15;
  double t16;
  double t17;
  double t18;
  double t2;
  double t20;
  double t21;
  double t23;
  double t25;
  double t26;
  double t29;
  double t3;
  double t31;
  double t33;
  double t34;
  double t36;
  double t39;
  double t4;
  double t40;
  double t41;
  double t5;
  double t56;
  double t58;
  double t6;
  double t62;
  double t64;
  double t68;
  double t7;
  double t70;
  double t8;
  double t9;
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
    t9 = sin(t1);
    t10 = sin(t6);
    t11 = t9*t10;
    t13 = q[11];
    t14 = sin(t13);
    t15 = 30.0*t14;
    t16 = cos(t13);
    t17 = 15.0*t16;
    t18 = t15-t17-10.0;
    t20 = t9*t4;
    t21 = t20*t7;
    t23 = t2*t10;
    CJ[9] = (t8+t11)*t18+53.0*t21-53.0*t23;
    t25 = t5*t10;
    t26 = t9*t7;
    t29 = t20*t10;
    t31 = t7*t2;
    CJ[10] = (t25-t26)*t18+53.0*t29+53.0*t31;
    t33 = cos(t3);
    t34 = t2*t33;
    t36 = t9*t33;
    CJ[11] = t34*t18+53.0*t36;
    t39 = 30.0*t16;
    t40 = 15.0*t14;
    t41 = t39+t40-40.0;
    CJ[12] = -t4*t7*t41+t36*t7*t18-53.0*t34*t7;
    CJ[13] = -t4*t10*t41+t36*t10*t18-53.0*t34*t10;
    CJ[14] = -t33*t41-t20*t18+53.0*t5;
    t56 = t33*t10;
    t58 = -t29-t31;
    CJ[15] = -t56*t41+t58*t18+53.0*t25-53.0*t26;
    t62 = t33*t7;
    t64 = t21-t23;
    CJ[16] = t62*t41+t64*t18-53.0*t8-53.0*t11;
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
    t68 = -t15+t17;
    t70 = t39+t40;
    CJ[33] = t62*t68+t64*t70;
    CJ[34] = t56*t68-t58*t70;
    CJ[35] = -t4*t68+t36*t70;
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

