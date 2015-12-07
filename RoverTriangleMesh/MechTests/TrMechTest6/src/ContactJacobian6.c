#include "LagrangianModel.h"
#include <math.h>
void ContactJacobian6(CJ,q)
double CJ[63];
double q[21];
{
  double t1;
  double t10;
  double t11;
  double t12;
  double t14;
  double t15;
  double t16;
  double t18;
  double t19;
  double t2;
  double t20;
  double t21;
  double t22;
  double t23;
  double t25;
  double t27;
  double t29;
  double t3;
  double t30;
  double t33;
  double t34;
  double t36;
  double t39;
  double t4;
  double t40;
  double t41;
  double t5;
  double t56;
  double t6;
  double t60;
  double t62;
  double t66;
  double t68;
  double t7;
  double t70;
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
    t16 = t2*t11;
    t18 = q[16];
    t19 = sin(t18);
    t20 = 0.32*t19;
    t21 = cos(t18);
    t22 = 0.216*t21;
    t23 = -t20-0.23375-t22;
    CJ[9] = -0.601203*t8-0.601203*t12+(-t15+t16)*t23;
    t25 = t5*t11;
    t27 = t10*t7;
    t29 = t11*t14;
    t30 = t7*t2;
    CJ[10] = -0.601203*t25+0.601203*t27+(-t29-t30)*t23;
    t33 = cos(t3);
    t34 = t2*t33;
    t36 = t10*t33;
    CJ[11] = -0.601203*t34-t36*t23;
    t39 = 0.32*t21;
    t40 = 0.216*t19;
    t41 = t39+0.4025001-t40;
    CJ[12] = -t4*t7*t41-0.601203*t36*t7+t34*t7*t23;
    CJ[13] = -t4*t11*t41-0.601203*t36*t11+t34*t11*t23;
    CJ[14] = -t33*t41+0.601203*t14-t5*t23;
    t56 = t33*t11;
    t60 = -t25+t27;
    CJ[15] = -t56*t41+0.601203*t29+0.601203*t30+t60*t23;
    t62 = t33*t7;
    t66 = t8+t12;
    CJ[16] = t62*t41-0.601203*t15+0.601203*t16+t66*t23;
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
    t68 = -t20-t22;
    t70 = -t39+t40;
    CJ[48] = t62*t68+t66*t70;
    CJ[49] = t56*t68-t60*t70;
    CJ[50] = -t4*t68+t34*t70;
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

