#include "LagrangianModel.h"
#include <math.h>
void Contact(CC,q)
double CC[18];
double q[21];
{
  double t1;
  double t10;
  double t101;
  double t103;
  double t104;
  double t109;
  double t11;
  double t111;
  double t114;
  double t12;
  double t13;
  double t14;
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
  double t35;
  double t37;
  double t39;
  double t4;
  double t42;
  double t43;
  double t46;
  double t47;
  double t48;
  double t49;
  double t5;
  double t51;
  double t53;
  double t54;
  double t55;
  double t57;
  double t6;
  double t62;
  double t65;
  double t67;
  double t68;
  double t69;
  double t7;
  double t70;
  double t71;
  double t73;
  double t74;
  double t75;
  double t77;
  double t78;
  double t8;
  double t83;
  double t86;
  double t87;
  double t9;
  double t91;
  double t92;
  double t98;
  double t99;
  {
    t1 = q[4];
    t2 = cos(t1);
    t3 = q[5];
    t4 = cos(t3);
    t5 = t2*t4;
    t6 = 0.6374999*t5;
    t7 = q[3];
    t8 = sin(t7);
    t9 = sin(t1);
    t10 = t8*t9;
    t11 = t10*t4;
    t12 = cos(t7);
    t13 = sin(t3);
    t14 = t12*t13;
    t15 = t11-t14;
    t16 = q[6];
    t17 = cos(t16);
    t18 = 0.601203*t17;
    t19 = sin(t16);
    t20 = 0.64092E-1*t19;
    t21 = t18-t20;
    t23 = t12*t9;
    t24 = t23*t4;
    t25 = t8*t13;
    t26 = t24+t25;
    t27 = 0.601203*t19;
    t28 = 0.64092E-1*t17;
    t29 = -0.16375-t27-t28;
    t31 = q[0];
    t32 = 1.0*t31;
    CC[0] = -t6+t15*t21+t26*t29+t32+t15*t19+t26*t17;
    t35 = -t18-t20;
    t37 = -0.16375+t27-t28;
    CC[1] = -t6+t15*t35+t26*t37+t32;
    t39 = 0.4025001*t5;
    t42 = 0.23375*t24;
    t43 = 0.23375*t25;
    CC[2] = t39+0.4705*t11-0.4705*t14-t42-t43+t31;
    CC[3] = t39+0.14705E1*t11-0.14705E1*t14-t42-t43+t31;
    t46 = q[11];
    t47 = cos(t46);
    t48 = 0.32*t47;
    t49 = sin(t46);
    t51 = t48+0.4025001+0.5908E-2*t49;
    t53 = 0.601203*t11;
    t54 = 0.601203*t14;
    t55 = 0.32*t49;
    t57 = -t55-0.23375+0.5908E-2*t47;
    CC[4] = t5*t51+t53-t54+t26*t57+t32+t5*t49+t26*t47;
    t62 = -t48+0.4025001-0.216*t49;
    t65 = t55-0.23375-0.216*t47;
    CC[5] = t5*t62+t53-t54+t26*t65+t32;
    t67 = t2*t13;
    t68 = 0.6374999*t67;
    t69 = t10*t13;
    t70 = t12*t4;
    t71 = t69+t70;
    t73 = t23*t13;
    t74 = t8*t4;
    t75 = t73-t74;
    t77 = q[1];
    t78 = 1.0*t77;
    CC[6] = -t68+t71*t21+t75*t29+t78+t71*t19+t75*t17;
    CC[7] = -t68+t71*t35+t75*t37+t78;
    t83 = 0.4025001*t67;
    t86 = 0.23375*t73;
    t87 = 0.23375*t74;
    CC[8] = t83+0.4705*t69+0.4705*t70-t86+t87+t77;
    CC[9] = t83+0.14705E1*t69+0.14705E1*t70-t86+t87+t77;
    t91 = 0.601203*t69;
    t92 = 0.601203*t70;
    CC[10] = t67*t51+t91+t92+t75*t57+t78+t67*t49+t75*t47;
    CC[11] = t67*t62+t91+t92+t75*t65+t78;
    t98 = 0.6374999*t9;
    t99 = t8*t2;
    t101 = t2*t12;
    t103 = q[2];
    t104 = 1.0*t103;
    CC[12] = t98+t99*t21+t101*t29+t104+t99*t19+t101*t17;
    CC[13] = t98+t99*t35+t101*t37+t104;
    t109 = 0.4025001*t9;
    t111 = 0.23375*t101;
    CC[14] = -t109+0.4705*t99-t111+t103;
    CC[15] = -t109+0.14705E1*t99-t111+t103;
    t114 = 0.601203*t99;
    CC[16] = -t9*t51+t114+t101*t57+t104-t9*t49+t101*t47;
    CC[17] = -t9*t62+t114+t101*t65+t104;
    return;
  }
}
