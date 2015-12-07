#include "LagrangianModel.h"
#include <math.h>
void ContactJacobian6(CJ,AngleT,q)
double CJ[63];
double AngleT[3];
double q[21];
{
  double t1;
  double t10;
  double t102;
  double t103;
  double t104;
  double t106;
  double t107;
  double t108;
  double t109;
  double t112;
  double t114;
  double t115;
  double t116;
  double t119;
  double t12;
  double t121;
  double t122;
  double t123;
  double t126;
  double t127;
  double t128;
  double t13;
  double t130;
  double t131;
  double t132;
  double t133;
  double t134;
  double t135;
  double t136;
  double t137;
  double t139;
  double t14;
  double t141;
  double t143;
  double t144;
  double t145;
  double t146;
  double t147;
  double t148;
  double t15;
  double t152;
  double t157;
  double t16;
  double t161;
  double t163;
  double t165;
  double t167;
  double t17;
  double t176;
  double t177;
  double t178;
  double t18;
  double t184;
  double t19;
  double t192;
  double t197;
  double t2;
  double t20;
  double t21;
  double t213;
  double t219;
  double t227;
  double t229;
  double t231;
  double t235;
  double t239;
  double t24;
  double t25;
  double t26;
  double t27;
  double t28;
  double t3;
  double t30;
  double t31;
  double t32;
  double t33;
  double t35;
  double t36;
  double t37;
  double t4;
  double t40;
  double t41;
  double t42;
  double t44;
  double t45;
  double t46;
  double t49;
  double t5;
  double t52;
  double t54;
  double t55;
  double t56;
  double t58;
  double t59;
  double t6;
  double t60;
  double t61;
  double t62;
  double t63;
  double t64;
  double t65;
  double t67;
  double t68;
  double t69;
  double t7;
  double t71;
  double t73;
  double t78;
  double t8;
  double t80;
  double t82;
  double t84;
  double t85;
  double t87;
  double t89;
  double t9;
  double t90;
  double t91;
  double t94;
  double t97;
  double t98;
  double t99;
  {
    t1 = q[4];
    t2 = cos(t1);
    t3 = q[5];
    t4 = cos(t3);
    t5 = t2*t4;
    t6 = q[16];
    t7 = cos(t6);
    t8 = q[18];
    t9 = sin(t8);
    t10 = t7*t9;
    t12 = q[3];
    t13 = sin(t12);
    t14 = sin(t1);
    t15 = t13*t14;
    t16 = t15*t4;
    t17 = cos(t12);
    t18 = sin(t3);
    t19 = t17*t18;
    t20 = t16-t19;
    t21 = sin(t6);
    t24 = t17*t14;
    t25 = t24*t4;
    t26 = t13*t18;
    t27 = t25+t26;
    t28 = cos(t8);
    t30 = t5*t10+t20*t21*t9+t27*t28;
    t31 = fabs(t30);
    t32 = t31*t31;
    t33 = t2*t18;
    t35 = t15*t18;
    t36 = t17*t4;
    t37 = t35+t36;
    t40 = t24*t18;
    t41 = t13*t4;
    t42 = t40-t41;
    t44 = t33*t10+t37*t21*t9+t42*t28;
    t45 = fabs(t44);
    t46 = t45*t45;
    t49 = t13*t2;
    t52 = t17*t2;
    t54 = -t14*t7*t9+t49*t21*t9+t52*t28;
    t55 = fabs(t54);
    t56 = t55*t55;
    t58 = sqrt(t32+t46+t56);
    t59 = 1/t58;
    t60 = t59*t44;
    t61 = t59*t30;
    t62 = AngleT[2];
    t63 = cos(t62);
    t64 = AngleT[0];
    t65 = cos(t64);
    t67 = sin(t62);
    t68 = AngleT[1];
    t69 = sin(t68);
    t71 = sin(t64);
    t73 = t63*t65+t67*t69*t71;
    t78 = -t65*t67+t63*t69*t71;
    t80 = t61*t73-t60*t78;
    t82 = t59*t54;
    t84 = cos(t68);
    t85 = t84*t71;
    t87 = t82*t78-t61*t85;
    t89 = t60*t80-t82*t87;
    t90 = fabs(t89);
    t91 = t90*t90;
    t94 = t60*t85-t82*t73;
    t97 = -t82*t94+t61*t80;
    t98 = fabs(t97);
    t99 = t98*t98;
    t102 = t61*t87-t60*t94;
    t103 = fabs(t102);
    t104 = t103*t103;
    t106 = sqrt(t91+t99+t104);
    t107 = 1/t106;
    t108 = t107*t89;
    CJ[0] = -t108;
    t109 = t97*t59;
    t112 = -t102*t59;
    t114 = t109*t54-t112*t44;
    t115 = fabs(t114);
    t116 = t115*t115;
    t119 = -t89*t59;
    t121 = t112*t30-t119*t54;
    t122 = fabs(t121);
    t123 = t122*t122;
    t126 = -t119*t44+t109*t30;
    t127 = fabs(t126);
    t128 = t127*t127;
    t130 = sqrt(t116+t123+t128);
    t131 = 1/t130;
    CJ[1] = t131*t114;
    t132 = fabs(t61);
    t133 = t132*t132;
    t134 = fabs(t60);
    t135 = t134*t134;
    t136 = fabs(t82);
    t137 = t136*t136;
    t139 = sqrt(t133+t135+t137);
    t141 = t59/t139;
    CJ[2] = t141*t30;
    t143 = -t107*t97;
    CJ[3] = -t143;
    CJ[4] = t131*t121;
    CJ[5] = t141*t44;
    t144 = t107*t102;
    CJ[6] = -t144;
    t145 = -t126;
    CJ[7] = t131*t145;
    CJ[8] = t141*t54;
    t146 = 30.0*t21;
    t147 = 15.0*t7;
    t148 = -t146-t147-10.0;
    t152 = t27*t148-53.0*t16+53.0*t19;
    t157 = t42*t148-53.0*t35-53.0*t36;
    t161 = t52*t148-53.0*t49;
    CJ[9] = -t108*t152-t143*t157-t144*t161;
    t163 = t131*t114;
    t165 = t131*t121;
    t167 = t131*t145;
    CJ[10] = t163*t152+t165*t157+t167*t161;
    CJ[11] = t141*t30*t152+t141*t44*t157+t141*t54*t161;
    t176 = 30.0*t7;
    t177 = 15.0*t21;
    t178 = -t176+t177-40.0;
    t184 = -t14*t4*t178+t49*t4*t148+53.0*t52*t4;
    t192 = -t14*t18*t178+t49*t18*t148+53.0*t52*t18;
    t197 = -t2*t178-t15*t148-53.0*t24;
    CJ[12] = -t108*t184-t143*t192-t144*t197;
    CJ[13] = t163*t184+t165*t192+t167*t197;
    CJ[14] = t141*t30*t184+t141*t44*t192+t141*t54*t197;
    t213 = -t33*t178-t37*t148-53.0*t40+53.0*t41;
    t219 = t5*t178+t20*t148+53.0*t25+53.0*t26;
    CJ[15] = -t108*t213-t143*t219;
    CJ[16] = t163*t213+t165*t219;
    CJ[17] = t141*t30*t213+t141*t44*t219;
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
    t227 = t146+t147;
    t229 = -t176+t177;
    t231 = t5*t227+t20*t229;
    t235 = t33*t227+t37*t229;
    t239 = -t14*t227+t49*t229;
    CJ[48] = -t108*t231-t143*t235-t144*t239;
    CJ[49] = t163*t231+t165*t235+t167*t239;
    CJ[50] = t141*t30*t231+t141*t44*t235+t141*t54*t239;
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

