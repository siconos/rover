#include "LagrangianModel.h"
#include <math.h>
void ContactJacobian1(CJ,AngleT,q)
double CJ[63];
double AngleT[3];
double q[21];
{
  double t1;
  double t10;
  double t100;
  double t101;
  double t104;
  double t105;
  double t106;
  double t108;
  double t109;
  double t11;
  double t111;
  double t112;
  double t114;
  double t116;
  double t117;
  double t118;
  double t12;
  double t120;
  double t122;
  double t123;
  double t124;
  double t127;
  double t128;
  double t129;
  double t131;
  double t132;
  double t133;
  double t134;
  double t135;
  double t136;
  double t137;
  double t138;
  double t14;
  double t140;
  double t142;
  double t144;
  double t146;
  double t147;
  double t148;
  double t149;
  double t15;
  double t150;
  double t155;
  double t157;
  double t160;
  double t162;
  double t166;
  double t168;
  double t17;
  double t170;
  double t172;
  double t18;
  double t186;
  double t19;
  double t194;
  double t199;
  double t2;
  double t21;
  double t214;
  double t219;
  double t227;
  double t229;
  double t23;
  double t231;
  double t235;
  double t239;
  double t26;
  double t27;
  double t3;
  double t30;
  double t31;
  double t32;
  double t33;
  double t37;
  double t4;
  double t42;
  double t45;
  double t46;
  double t47;
  double t49;
  double t5;
  double t52;
  double t55;
  double t56;
  double t57;
  double t59;
  double t6;
  double t60;
  double t61;
  double t62;
  double t63;
  double t64;
  double t65;
  double t66;
  double t67;
  double t69;
  double t7;
  double t70;
  double t71;
  double t73;
  double t75;
  double t80;
  double t82;
  double t84;
  double t86;
  double t87;
  double t89;
  double t9;
  double t91;
  double t92;
  double t93;
  double t96;
  double t99;
  {
    t1 = q[4];
    t2 = cos(t1);
    t3 = q[5];
    t4 = cos(t3);
    t5 = t2*t4;
    t6 = q[7];
    t7 = sin(t6);
    t9 = q[3];
    t10 = sin(t9);
    t11 = sin(t1);
    t12 = t10*t11;
    t14 = cos(t9);
    t15 = sin(t3);
    t17 = t12*t4-t14*t15;
    t18 = q[6];
    t19 = sin(t18);
    t21 = cos(t6);
    t23 = t11*t14;
    t26 = t23*t4+t10*t15;
    t27 = cos(t18);
    t30 = t5*t7-t17*t19*t21+t26*t27*t21;
    t31 = fabs(t30);
    t32 = t31*t31;
    t33 = t2*t15;
    t37 = t12*t15+t14*t4;
    t42 = t23*t15-t10*t4;
    t45 = -t33*t7+t37*t19*t21-t42*t27*t21;
    t46 = fabs(t45);
    t47 = t46*t46;
    t49 = t10*t2;
    t52 = t14*t2;
    t55 = -t11*t7-t49*t19*t21+t52*t27*t21;
    t56 = fabs(t55);
    t57 = t56*t56;
    t59 = sqrt(t32+t47+t57);
    t60 = 1/t59;
    t61 = -t45;
    t62 = t60*t61;
    t63 = t60*t30;
    t64 = AngleT[2];
    t65 = cos(t64);
    t66 = AngleT[0];
    t67 = cos(t66);
    t69 = sin(t64);
    t70 = AngleT[1];
    t71 = sin(t70);
    t73 = sin(t66);
    t75 = t65*t67+t69*t71*t73;
    t80 = -t69*t67+t65*t71*t73;
    t82 = t63*t75-t62*t80;
    t84 = t60*t55;
    t86 = cos(t70);
    t87 = t86*t73;
    t89 = t84*t80-t63*t87;
    t91 = -t62*t82+t84*t89;
    t92 = fabs(t91);
    t93 = t92*t92;
    t96 = t62*t87-t84*t75;
    t99 = -t84*t96+t63*t82;
    t100 = fabs(t99);
    t101 = t100*t100;
    t104 = -t63*t89+t62*t96;
    t105 = fabs(t104);
    t106 = t105*t105;
    t108 = sqrt(t93+t101+t106);
    t109 = 1/t108;
    t111 = -t109*t91;
    CJ[0] = -t111;
    t112 = t99*t60;
    t114 = t104*t60;
    t116 = t112*t55-t114*t61;
    t117 = fabs(t116);
    t118 = t117*t117;
    t120 = t91*t60;
    t122 = t114*t30-t120*t55;
    t123 = fabs(t122);
    t124 = t123*t123;
    t127 = -t120*t61+t112*t30;
    t128 = fabs(t127);
    t129 = t128*t128;
    t131 = sqrt(t118+t124+t129);
    t132 = 1/t131;
    CJ[1] = t132*t116;
    t133 = fabs(t63);
    t134 = t133*t133;
    t135 = fabs(t62);
    t136 = t135*t135;
    t137 = fabs(t84);
    t138 = t137*t137;
    t140 = sqrt(t134+t136+t138);
    t142 = t60/t140;
    CJ[2] = t142*t30;
    t144 = -t109*t99;
    CJ[3] = -t144;
    CJ[4] = t132*t122;
    CJ[5] = t142*t61;
    t146 = -t109*t104;
    CJ[6] = -t146;
    t147 = -t127;
    CJ[7] = t132*t147;
    CJ[8] = t142*t55;
    t148 = 15.0*t27;
    t149 = 53.0*t19;
    t150 = -10.0-t148+t149;
    t155 = -15.0*t19-53.0*t27;
    t157 = t26*t150-t17*t155;
    t160 = -t37;
    t162 = t42*t150+t160*t155;
    t166 = t52*t150-t49*t155;
    CJ[9] = -t111*t157-t144*t162-t146*t166;
    t168 = t132*t116;
    t170 = t132*t122;
    t172 = t132*t147;
    CJ[10] = t168*t157+t170*t162+t172*t166;
    CJ[11] = t142*t30*t157+t142*t61*t162+t142*t55*t166;
    t186 = -62.0*t11*t4+t49*t4*t150+t52*t4*t155;
    t194 = -62.0*t11*t15+t49*t15*t150+t52*t15*t155;
    t199 = -62.0*t2-t12*t150-t23*t155;
    CJ[12] = -t111*t186-t144*t194-t146*t199;
    CJ[13] = t168*t186+t170*t194+t172*t199;
    CJ[14] = t142*t30*t186+t142*t61*t194+t142*t55*t199;
    t214 = -62.0*t33+t160*t150-t42*t155;
    t219 = 62.0*t5+t17*t150+t26*t155;
    CJ[15] = -t111*t214-t144*t219;
    CJ[16] = t168*t214+t170*t219;
    CJ[17] = t142*t30*t214+t142*t61*t219;
    t227 = -t155;
    t229 = -t148+t149;
    t231 = t17*t227+t26*t229;
    t235 = t37*t227+t42*t229;
    t239 = t49*t227+t52*t229;
    CJ[18] = -t111*t231-t144*t235-t146*t239;
    CJ[19] = t168*t231+t170*t235+t172*t239;
    CJ[20] = t142*t30*t231+t142*t61*t235+t142*t55*t239;
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

