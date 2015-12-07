#include "LagrangianModel.h"
#include <math.h>
void ContactJacobian4s(CJ,AngleT,q)
double CJ[63];
double AngleT[4];
double q[21];
{
  double t1;
  double t10;
  double t101;
  double t102;
  double t103;
  double t105;
  double t106;
  double t107;
  double t109;
  double t11;
  double t110;
  double t111;
  double t113;
  double t114;
  double t116;
  double t117;
  double t118;
  double t120;
  double t121;
  double t13;
  double t130;
  double t135;
  double t139;
  double t14;
  double t144;
  double t15;
  double t154;
  double t16;
  double t162;
  double t167;
  double t17;
  double t177;
  double t179;
  double t18;
  double t185;
  double t187;
  double t189;
  double t19;
  double t193;
  double t197;
  double t2;
  double t20;
  double t21;
  double t22;
  double t25;
  double t26;
  double t27;
  double t28;
  double t29;
  double t3;
  double t31;
  double t32;
  double t33;
  double t34;
  double t36;
  double t37;
  double t38;
  double t4;
  double t41;
  double t42;
  double t43;
  double t45;
  double t46;
  double t47;
  double t5;
  double t50;
  double t53;
  double t55;
  double t56;
  double t57;
  double t59;
  double t6;
  double t60;
  double t63;
  double t66;
  double t69;
  double t7;
  double t70;
  double t71;
  double t72;
  double t73;
  double t74;
  double t75;
  double t76;
  double t77;
  double t78;
  double t79;
  double t8;
  double t83;
  double t84;
  double t85;
  double t86;
  double t87;
  double t9;
  double t91;
  double t92;
  double t93;
  double t94;
  double t99;
  {
    t1 = AngleT[0];
    t2 = q[4];
    t3 = cos(t2);
    t4 = q[5];
    t5 = cos(t4);
    t6 = t3*t5;
    t7 = q[11];
    t8 = cos(t7);
    t9 = q[13];
    t10 = sin(t9);
    t11 = t8*t10;
    t13 = q[3];
    t14 = sin(t13);
    t15 = sin(t2);
    t16 = t14*t15;
    t17 = t16*t5;
    t18 = cos(t13);
    t19 = sin(t4);
    t20 = t18*t19;
    t21 = t17-t20;
    t22 = sin(t7);
    t25 = t18*t15;
    t26 = t25*t5;
    t27 = t14*t19;
    t28 = t26+t27;
    t29 = cos(t9);
    t31 = t6*t11+t21*t22*t10+t28*t29;
    t32 = fabs(t31);
    t33 = t32*t32;
    t34 = t3*t19;
    t36 = t16*t19;
    t37 = t18*t5;
    t38 = t36+t37;
    t41 = t25*t19;
    t42 = t14*t5;
    t43 = t41-t42;
    t45 = t34*t11+t38*t22*t10+t43*t29;
    t46 = fabs(t45);
    t47 = t46*t46;
    t50 = t14*t3;
    t53 = t18*t3;
    t55 = -t15*t8*t10+t50*t22*t10+t53*t29;
    t56 = fabs(t55);
    t57 = t56*t56;
    t59 = sqrt(t33+t47+t57);
    t60 = 1/t59;
    t63 = AngleT[1];
    t66 = AngleT[2];
    t69 = 30.0*t8;
    t70 = 15.0*t22;
    t71 = -t69+t70-40.0;
    t72 = t6*t71;
    t73 = 30.0*t22;
    t74 = 15.0*t8;
    t75 = -t73-t74-10.0;
    t76 = t21*t75;
    t77 = 53.0*t26;
    t78 = 53.0*t27;
    t79 = q[0];
    t83 = t34*t71;
    t84 = t38*t75;
    t85 = 53.0*t41;
    t86 = 53.0*t42;
    t87 = q[1];
    t91 = t15*t71;
    t92 = t50*t75;
    t93 = 53.0*t53;
    t94 = q[2];
    t99 = (t1*t60*t31+t63*t60*t45+t66*t60*t55-(t72+t76-t77-t78+t79)*t60*t31-(
t83+t84-t85+t86+t87)*t60*t45-(-t91+t92-t93+t94)*t60*t55)*t60;
    t101 = -t1+t99*t31+t72+t76-t77-t78+t79;
    t102 = fabs(t101);
    t103 = t102*t102;
    t105 = t63-t99*t45-t83-t84+t85-t86-t87;
    t106 = fabs(t105);
    t107 = t106*t106;
    t109 = t66-t99*t55+t91-t92+t93-t94;
    t110 = fabs(t109);
    t111 = t110*t110;
    t113 = sqrt(t103+t107+t111);
    t114 = 1/t113;
    t116 = -t114*t101;
    CJ[0] = -t116;
    t117 = t114*t105;
    t118 = t60*t55;
    t120 = t114*t109;
    t121 = t60*t45;
    CJ[1] = -t117*t118+t120*t121;
    CJ[2] = t60*t31;
    CJ[3] = -t117;
    CJ[4] = -t120*CJ[2]+t116*t118;
    CJ[5] = t121;
    CJ[6] = -t120;
    CJ[7] = -t116*CJ[5]+t117*CJ[2];
    CJ[8] = t118;
    t130 = t28*t75+53.0*t17-53.0*t20;
    t135 = t43*t75+53.0*t36+53.0*t37;
    t139 = t53*t75+53.0*t50;
    CJ[9] = -t116*t130-t117*t135-t120*t139;
    CJ[10] = CJ[1]*t130+CJ[4]*t135+CJ[7]*t139;
    t144 = t60*t31;
    CJ[11] = t144*t130+t121*t135+t118*t139;
    t154 = -t15*t5*t71+t50*t5*t75-53.0*t53*t5;
    t162 = -t15*t19*t71+t50*t19*t75-53.0*t53*t19;
    t167 = -t3*t71-t16*t75+53.0*t25;
    CJ[12] = -t116*t154-t117*t162-t120*t167;
    CJ[13] = CJ[1]*t154+CJ[4]*t162+CJ[7]*t167;
    CJ[14] = t144*t154+t121*t162+t118*t167;
    t177 = -t83-t38*t75+t85-t86;
    t179 = t72+t76-t77-t78;
    CJ[15] = -t116*t177-t117*t179;
    CJ[16] = CJ[1]*t177+CJ[4]*t179;
    CJ[17] = t144*t177+t121*t179;
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
    t185 = t73+t74;
    t187 = -t69+t70;
    t189 = t6*t185+t21*t187;
    t193 = t34*t185+t38*t187;
    t197 = -t15*t185+t50*t187;
    CJ[33] = -t116*t189-t117*t193-t120*t197;
    CJ[34] = CJ[1]*t189+CJ[4]*t193+CJ[7]*t197;
    CJ[35] = t144*t189+t121*t193+t118*t197;
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

