#include "LagrangianModel.h"
#include <math.h>
void Contact(CC,q)
double CC[18];
double q[21];
{
  double t1;
  double t10;
  double t103;
  double t11;
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
  double t26;
  double t27;
  double t28;
  double t29;
  double t3;
  double t32;
  double t33;
  double t35;
  double t37;
  double t38;
  double t39;
  double t4;
  double t40;
  double t41;
  double t42;
  double t44;
  double t45;
  double t46;
  double t47;
  double t48;
  double t5;
  double t50;
  double t52;
  double t54;
  double t55;
  double t56;
  double t57;
  double t58;
  double t59;
  double t6;
  double t61;
  double t62;
  double t63;
  double t65;
  double t67;
  double t69;
  double t7;
  double t70;
  double t71;
  double t72;
  double t73;
  double t77;
  double t8;
  double t80;
  double t84;
  double t85;
  double t9;
  double t93;
  double t94;
  double t96;
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
    t20 = 0.286*t19;
    t21 = t18+t20;
    t23 = t12*t9;
    t26 = t23*t4+t8*t13;
    t27 = 0.601203*t19;
    t28 = 0.286*t17;
    t29 = -0.16375+t27-t28;
    t32 = 1.0*q[0];
    CC[0] = -t6+t15*t21+t26*t29+t32;
    t33 = -t18+t20;
    t35 = -0.16375-t27-t28;
    CC[1] = -t6+t15*t33+t26*t35+t32;
    t37 = q[11];
    t38 = cos(t37);
    t39 = 0.32*t38;
    t40 = sin(t37);
    t41 = 0.216*t40;
    t42 = -t39+0.4025001-t41;
    t44 = 0.601203*t11;
    t45 = 0.601203*t14;
    t46 = 0.32*t40;
    t47 = 0.216*t38;
    t48 = t46-0.23375-t47;
    CC[2] = t5*t42+t44-t45+t26*t48+t32;
    t50 = t39+0.4025001-t41;
    t52 = -t46-0.23375-t47;
    CC[3] = t5*t50+t44-t45+t26*t52+t32;
    t54 = q[16];
    t55 = cos(t54);
    t56 = 0.32*t55;
    t57 = sin(t54);
    t58 = 0.216*t57;
    t59 = -t56+0.4025001-t58;
    t61 = 0.32*t57;
    t62 = 0.216*t55;
    t63 = t61-0.23375-t62;
    CC[4] = t5*t59-t44+t45+t26*t63+t32;
    t65 = t56+0.4025001-t58;
    t67 = -t61-0.23375-t62;
    CC[5] = t5*t65-t44+t45+t26*t67+t32;
    t69 = t2*t13;
    t70 = 0.6374999*t69;
    t71 = t10*t13;
    t72 = t12*t4;
    t73 = t71+t72;
    t77 = t23*t13-t8*t4;
    t80 = 1.0*q[1];
    CC[6] = -t70+t73*t21+t77*t29+t80;
    CC[7] = -t70+t73*t33+t77*t35+t80;
    t84 = 0.601203*t71;
    t85 = 0.601203*t72;
    CC[8] = t69*t42+t84+t85+t77*t48+t80;
    CC[9] = t69*t50+t84+t85+t77*t52+t80;
    CC[10] = t69*t59-t84-t85+t77*t63+t80;
    CC[11] = t69*t65-t84-t85+t77*t67+t80;
    t93 = 0.6374999*t9;
    t94 = t8*t2;
    t96 = t2*t12;
    t99 = 1.0*q[2];
    CC[12] = t93+t94*t21+t96*t29+t99;
    CC[13] = t93+t94*t33+t96*t35+t99;
    t103 = 0.601203*t94;
    CC[14] = -t9*t42+t103+t96*t48+t99;
    CC[15] = -t9*t50+t103+t96*t52+t99;
    CC[16] = -t9*t59-t103+t96*t63+t99;
    CC[17] = -t9*t65-t103+t96*t67+t99;
    return;
  }
}
