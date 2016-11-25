#include "LagrangianModel.h"
#include <math.h>
void ContactJacobian1(CJ,AngleT,q)
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
  double t115;
  double t116;
  double t117;
  double t12;
  double t120;
  double t121;
  double t13;
  double t130;
  double t133;
  double t135;
  double t139;
  double t144;
  double t15;
  double t154;
  double t16;
  double t162;
  double t167;
  double t178;
  double t18;
  double t180;
  double t186;
  double t188;
  double t19;
  double t190;
  double t194;
  double t198;
  double t2;
  double t20;
  double t22;
  double t24;
  double t27;
  double t28;
  double t3;
  double t31;
  double t32;
  double t33;
  double t34;
  double t38;
  double t4;
  double t43;
  double t46;
  double t47;
  double t48;
  double t5;
  double t50;
  double t53;
  double t56;
  double t57;
  double t58;
  double t6;
  double t60;
  double t61;
  double t64;
  double t66;
  double t68;
  double t7;
  double t71;
  double t72;
  double t73;
  double t74;
  double t75;
  double t78;
  double t79;
  double t8;
  double t80;
  double t84;
  double t85;
  double t86;
  double t87;
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
    t7 = q[7];
    t8 = sin(t7);
    t10 = q[3];
    t11 = sin(t10);
    t12 = sin(t2);
    t13 = t11*t12;
    t15 = cos(t10);
    t16 = sin(t4);
    t18 = t13*t5-t15*t16;
    t19 = q[6];
    t20 = sin(t19);
    t22 = cos(t7);
    t24 = t15*t12;
    t27 = t11*t16+t24*t5;
    t28 = cos(t19);
    t31 = -t18*t20*t22+t27*t28*t22+t6*t8;
    t32 = fabs(t31);
    t33 = t32*t32;
    t34 = t3*t16;
    t38 = t13*t16+t15*t5;
    t43 = -t11*t5+t24*t16;
    t46 = t38*t20*t22-t43*t28*t22-t34*t8;
    t47 = fabs(t46);
    t48 = t47*t47;
    t50 = t11*t3;
    t53 = t15*t3;
    t56 = -t50*t20*t22+t53*t28*t22-t12*t8;
    t57 = fabs(t56);
    t58 = t57*t57;
    t60 = sqrt(t33+t48+t58);
    t61 = 1/t60;
    t64 = AngleT[1];
    t66 = -t46;
    t68 = AngleT[2];
    t71 = 62.0*t6;
    t72 = 15.0*t28;
    t73 = 53.0*t20;
    t74 = -10.0-t72+t73;
    t75 = t18*t74;
    t78 = -15.0*t20-53.0*t28;
    t79 = t27*t78;
    t80 = q[0];
    t84 = 62.0*t34;
    t85 = t38*t74;
    t86 = t43*t78;
    t87 = q[1];
    t91 = 62.0*t12;
    t92 = t50*t74;
    t93 = t53*t78;
    t94 = q[2];
    t99 = (t1*t61*t31+t64*t61*t66+t68*t61*t56-(t71+t75+t79+t80)*t61*t31-(t84+
t85+t86+t87)*t61*t66-(-t91+t92+t93+t94)*t61*t56)*t61;
    t101 = -t99*t31+t1-t71-t75-t79-t80;
    t102 = fabs(t101);
    t103 = t102*t102;
    t105 = -t99*t66+t64-t84-t85-t86-t87;
    t106 = fabs(t105);
    t107 = t106*t106;
    t109 = t99*t56-t68-t91+t92+t93+t94;
    t110 = fabs(t109);
    t111 = t110*t110;
    t113 = sqrt(t103+t107+t111);
    t114 = 1/t113;
    t115 = t114*t101;
    CJ[0] = -t115;
    t116 = t114*t105;
    t117 = t61*t56;
    t120 = -t114*t109;
    t121 = t61*t66;
    CJ[1] = -t116*t117+t120*t121;
    CJ[2] = t61*t31;
    CJ[3] = -t116;
    CJ[4] = t115*t117-t120*CJ[2];
    CJ[5] = t121;
    CJ[6] = -t120;
    CJ[7] = -t115*CJ[5]+t116*CJ[2];
    CJ[8] = t117;
    t130 = -t18*t78+t27*t74;
    t133 = -t38;
    t135 = t133*t78+t43*t74;
    t139 = -t50*t78+t53*t74;
    CJ[9] = -t115*t130-t116*t135-t120*t139;
    CJ[10] = CJ[1]*t130+CJ[4]*t135+CJ[7]*t139;
    t144 = t61*t31;
    CJ[11] = t117*t139+t121*t135+t144*t130;
    t154 = t50*t5*t74+t53*t5*t78-62.0*t5*t12;
    t162 = t50*t16*t74+t53*t16*t78-62.0*t12*t16;
    t167 = -t13*t74-t24*t78-62.0*t3;
    CJ[12] = -t115*t154-t116*t162-t120*t167;
    CJ[13] = CJ[1]*t154+CJ[4]*t162+CJ[7]*t167;
    CJ[14] = t117*t167+t121*t162+t144*t154;
    t178 = t133*t74-t43*t78-t84;
    t180 = t71+t75+t79;
    CJ[15] = -t115*t178-t116*t180;
    CJ[16] = CJ[1]*t178+CJ[4]*t180;
    CJ[17] = t121*t180+t144*t178;
    t186 = -t78;
    t188 = -t72+t73;
    t190 = t18*t186+t27*t188;
    t194 = t38*t186+t43*t188;
    t198 = t50*t186+t53*t188;
    CJ[18] = -t115*t190-t116*t194-t120*t198;
    CJ[19] = CJ[1]*t190+CJ[4]*t194+CJ[7]*t198;
    CJ[20] = t117*t198+t121*t194+t144*t190;
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
