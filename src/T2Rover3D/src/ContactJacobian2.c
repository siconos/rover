#include "LagrangianModel.h"
#include <math.h>
void ContactJacobian2(CJ,AngleT,q)
double CJ[63];
double AngleT[3];
double q[21];
{
  double t1;
  double t10;
  double t100;
  double t101;
  double t103;
  double t104;
  double t105;
  double t108;
  double t110;
  double t111;
  double t112;
  double t113;
  double t116;
  double t117;
  double t118;
  double t12;
  double t121;
  double t122;
  double t123;
  double t125;
  double t126;
  double t127;
  double t128;
  double t13;
  double t130;
  double t131;
  double t133;
  double t134;
  double t135;
  double t137;
  double t139;
  double t140;
  double t141;
  double t144;
  double t145;
  double t146;
  double t148;
  double t149;
  double t15;
  double t150;
  double t154;
  double t158;
  double t16;
  double t160;
  double t165;
  double t168;
  double t17;
  double t170;
  double t172;
  double t174;
  double t176;
  double t178;
  double t18;
  double t186;
  double t19;
  double t195;
  double t2;
  double t20;
  double t201;
  double t21;
  double t213;
  double t216;
  double t22;
  double t223;
  double t225;
  double t227;
  double t23;
  double t232;
  double t237;
  double t26;
  double t29;
  double t3;
  double t30;
  double t32;
  double t33;
  double t34;
  double t35;
  double t36;
  double t39;
  double t4;
  double t43;
  double t47;
  double t48;
  double t49;
  double t5;
  double t51;
  double t53;
  double t56;
  double t57;
  double t58;
  double t6;
  double t60;
  double t61;
  double t62;
  double t63;
  double t64;
  double t65;
  double t66;
  double t67;
  double t68;
  double t69;
  double t7;
  double t70;
  double t72;
  double t74;
  double t75;
  double t76;
  double t79;
  double t8;
  double t83;
  double t84;
  double t85;
  double t9;
  double t91;
  double t92;
  double t93;
  double t99;
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
    t21 = -10.0-t18-t20;
    t22 = t15*t21;
    t23 = t12*t9;
    t26 = t23*t4+t8*t13;
    t29 = -15.0*t19+53.0*t17;
    t30 = t26*t29;
    t32 = t6+t22+t30+q[0];
    t33 = fabs(t32);
    t34 = t33*t33;
    t35 = t2*t13;
    t36 = 62.0*t35;
    t39 = t10*t13+t12*t4;
    t43 = t23*t13-t8*t4;
    t47 = t36+t39*t21+t43*t29+q[1]+AngleT[0];
    t48 = fabs(t47);
    t49 = t48*t48;
    t51 = t8*t2;
    t53 = t2*t12;
    t56 = -62.0*t9+t51*t21+t53*t29+q[2];
    t57 = fabs(t56);
    t58 = t57*t57;
    t60 = sqrt(t34+t49+t58);
    t61 = 1/t60;
    t62 = t61*t32;
    t63 = fabs(t62);
    t64 = t63*t63;
    t65 = t61*t47;
    t66 = fabs(t65);
    t67 = t66*t66;
    t68 = t61*t56;
    t69 = fabs(t68);
    t70 = t69*t69;
    t72 = sqrt(t64+t67+t70);
    t74 = t61/t72;
    CJ[0] = t74*t32;
    t75 = q[8];
    t76 = sin(t75);
    t79 = cos(t75);
    t83 = t5*t76-t15*t19*t79+t26*t17*t79;
    t84 = fabs(t83);
    t85 = t84*t84;
    t91 = -t35*t76+t39*t19*t79-t43*t17*t79;
    t92 = fabs(t91);
    t93 = t92*t92;
    t99 = -t9*t76-t51*t19*t79+t53*t17*t79;
    t100 = fabs(t99);
    t101 = t100*t100;
    t103 = sqrt(t85+t93+t101);
    t104 = 1/t103;
    t105 = t104*t99;
    t108 = -t104*t91;
    t110 = t65*t105-t68*t108;
    t111 = fabs(t110);
    t112 = t111*t111;
    t113 = t104*t83;
    t116 = -t68*t113+t62*t105;
    t117 = fabs(t116);
    t118 = t117*t117;
    t121 = -t62*t108+t65*t113;
    t122 = fabs(t121);
    t123 = t122*t122;
    t125 = sqrt(t112+t118+t123);
    t126 = 1/t125;
    CJ[1] = t126*t110;
    t127 = -t116;
    t128 = t127*t61;
    t130 = -t121;
    t131 = t130*t61;
    t133 = t56*t128-t131*t47;
    t134 = fabs(t133);
    t135 = t134*t134;
    t137 = t110*t61;
    t139 = -t131*t32+t137*t56;
    t140 = fabs(t139);
    t141 = t140*t140;
    t144 = t137*t47-t128*t32;
    t145 = fabs(t144);
    t146 = t145*t145;
    t148 = sqrt(t135+t141+t146);
    t149 = 1/t148;
    CJ[2] = t149*t133;
    CJ[3] = t74*t47;
    CJ[4] = t126*t127;
    t150 = -t139;
    CJ[5] = t149*t150;
    CJ[6] = t74*t56;
    CJ[7] = t126*t130;
    CJ[8] = t149*t144;
    t154 = t26*t21-t15*t29;
    t158 = -t39;
    t160 = t43*t21+t158*t29;
    t165 = t53*t21-t29*t51;
    CJ[9] = t74*t32*t154+t74*t47*t160+t74*t56*t165;
    t168 = t126*t110;
    t170 = t126*t127;
    t172 = t126*t130;
    CJ[10] = t168*t154+t170*t160+t172*t165;
    t174 = t149*t133;
    t176 = t149*t150;
    t178 = t149*t144;
    CJ[11] = t174*t154+t176*t160+t178*t165;
    t186 = -62.0*t9*t4+t51*t4*t21+t53*t4*t29;
    t195 = -62.0*t9*t13+t51*t13*t21+t53*t13*t29;
    t201 = -62.0*t2-t10*t21-t23*t29;
    CJ[12] = t74*t32*t186+t74*t47*t195+t74*t56*t201;
    CJ[13] = t168*t186+t170*t195+t172*t201;
    CJ[14] = t174*t186+t176*t195+t178*t201;
    t213 = -t36+t158*t21-t43*t29;
    t216 = t6+t22+t30;
    CJ[15] = t74*t32*t213+t74*t47*t216;
    CJ[16] = t168*t213+t170*t216;
    CJ[17] = t174*t213+t176*t216;
    t223 = -t29;
    t225 = -t18-t20;
    t227 = t15*t223+t26*t225;
    t232 = t39*t223+t43*t225;
    t237 = t51*t223+t53*t225;
    CJ[18] = t74*t32*t227+t74*t47*t232+t74*t56*t237;
    CJ[19] = t168*t227+t170*t232+t172*t237;
    CJ[20] = t174*t227+t176*t232+t178*t237;
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
