#include "LagrangianModel.h"
#include <math.h>
void Contact(CC,q)
double CC[18];
double q[21];
{
  double t1;
  double t10;
  double t101;
  double t12;
  double t13;
  double t15;
  double t16;
  double t17;
  double t18;
  double t19;
  double t2;
  double t20;
  double t21;
  double t23;
  double t24;
  double t25;
  double t26;
  double t27;
  double t28;
  double t29;
  double t3;
  double t31;
  double t32;
  double t34;
  double t36;
  double t37;
  double t38;
  double t39;
  double t4;
  double t40;
  double t41;
  double t43;
  double t44;
  double t45;
  double t47;
  double t48;
  double t49;
  double t5;
  double t51;
  double t53;
  double t54;
  double t55;
  double t56;
  double t57;
  double t58;
  double t6;
  double t60;
  double t61;
  double t62;
  double t64;
  double t66;
  double t68;
  double t69;
  double t7;
  double t72;
  double t74;
  double t75;
  double t76;
  double t78;
  double t8;
  double t83;
  double t84;
  double t9;
  double t91;
  double t92;
  double t94;
  double t96;
  {
    t1 = q[4];
    t2 = cos(t1);
    t3 = q[5];
    t4 = cos(t3);
    t5 = t2*t4;
    t6 = 62.0*t5;
    t7 = q[3];
    t8 = sin(t7);
    t9 = sin(t1);
    t10 = t8*t9;
    t12 = cos(t7);
    t13 = sin(t3);
    t15 = t10*t4-t12*t13;
    t16 = q[6];
    t17 = cos(t16);
    t18 = 15.0*t17;
    t19 = sin(t16);
    t20 = 53.0*t19;
    t21 = -10.0-t18+t20;
    t23 = t12*t9;
    t24 = t23*t4;
    t25 = t8*t13;
    t26 = t24+t25;
    t27 = 15.0*t19;
    t28 = 53.0*t17;
    t29 = -t27-t28;
    t31 = q[0];
    CC[0] = t15*t21+t26*t29+t31+t6;
    t32 = -10.0-t18-t20;
    t34 = -t27+t28;
    CC[1] = t15*t32+t26*t34+t31+t6;
    t36 = q[11];
    t37 = cos(t36);
    t38 = 30.0*t37;
    t39 = sin(t36);
    t40 = 15.0*t39;
    t41 = t38+t40-40.0;
    t43 = 30.0*t39;
    t44 = 15.0*t37;
    t45 = t43-t44-10.0;
    t47 = 53.0*t24;
    t48 = 53.0*t25;
    CC[2] = t15*t45+t5*t41+t31-t47-t48;
    t49 = -t38+t40-40.0;
    t51 = -t43-t44-10.0;
    CC[3] = t15*t51+t5*t49+t31-t47-t48;
    t53 = q[16];
    t54 = cos(t53);
    t55 = 30.0*t54;
    t56 = sin(t53);
    t57 = 15.0*t56;
    t58 = t55+t57-40.0;
    t60 = 30.0*t56;
    t61 = 15.0*t54;
    t62 = t60-t61-10.0;
    CC[4] = t15*t62+t5*t58+t31+t47+t48;
    t64 = -t55+t57-40.0;
    t66 = -t60-t61-10.0;
    CC[5] = t15*t66+t5*t64+t31+t47+t48;
    t68 = t2*t13;
    t69 = 62.0*t68;
    t72 = t10*t13+t12*t4;
    t74 = t23*t13;
    t75 = t8*t4;
    t76 = t74-t75;
    t78 = q[1];
    CC[6] = t72*t21+t76*t29+t69+t78;
    CC[7] = t72*t32+t76*t34+t69+t78;
    t83 = 53.0*t74;
    t84 = 53.0*t75;
    CC[8] = t68*t41+t72*t45+t78-t83+t84;
    CC[9] = t68*t49+t72*t51+t78-t83+t84;
    CC[10] = t68*t58+t72*t62+t78+t83-t84;
    CC[11] = t68*t64+t72*t66+t78+t83-t84;
    t91 = 62.0*t9;
    t92 = t8*t2;
    t94 = t2*t12;
    t96 = q[2];
    CC[12] = t92*t21+t94*t29-t91+t96;
    CC[13] = t92*t32+t94*t34-t91+t96;
    t101 = 53.0*t94;
    CC[14] = -t9*t41+t92*t45-t101+t96;
    CC[15] = -t9*t49+t92*t51-t101+t96;
    CC[16] = -t9*t58+t92*t62+t101+t96;
    CC[17] = -t9*t64+t92*t66+t101+t96;
    return;
  }
}

