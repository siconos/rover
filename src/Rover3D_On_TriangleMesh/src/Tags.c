#include "LagrangianModel.h"
#include <math.h>
void Tags(T,q)
double T[69];
double q[21];
{
  double t1;
  double t10;
  double t100;
  double t102;
  double t105;
  double t106;
  double t107;
  double t109;
  double t11;
  double t111;
  double t113;
  double t114;
  double t115;
  double t118;
  double t12;
  double t120;
  double t121;
  double t122;
  double t124;
  double t126;
  double t128;
  double t129;
  double t13;
  double t130;
  double t133;
  double t137;
  double t14;
  double t143;
  double t148;
  double t149;
  double t15;
  double t150;
  double t151;
  double t152;
  double t153;
  double t154;
  double t155;
  double t156;
  double t157;
  double t158;
  double t159;
  double t16;
  double t160;
  double t161;
  double t166;
  double t167;
  double t168;
  double t169;
  double t17;
  double t170;
  double t171;
  double t172;
  double t177;
  double t178;
  double t179;
  double t18;
  double t180;
  double t186;
  double t19;
  double t193;
  double t2;
  double t20;
  double t200;
  double t21;
  double t212;
  double t213;
  double t214;
  double t215;
  double t216;
  double t218;
  double t219;
  double t22;
  double t224;
  double t225;
  double t226;
  double t227;
  double t228;
  double t229;
  double t23;
  double t234;
  double t235;
  double t236;
  double t237;
  double t24;
  double t25;
  double t252;
  double t26;
  double t261;
  double t27;
  double t28;
  double t29;
  double t3;
  double t30;
  double t31;
  double t32;
  double t33;
  double t35;
  double t36;
  double t37;
  double t39;
  double t4;
  double t41;
  double t43;
  double t44;
  double t45;
  double t46;
  double t47;
  double t48;
  double t49;
  double t5;
  double t50;
  double t51;
  double t52;
  double t53;
  double t54;
  double t55;
  double t56;
  double t57;
  double t58;
  double t59;
  double t6;
  double t60;
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
  double t74;
  double t75;
  double t76;
  double t77;
  double t78;
  double t79;
  double t8;
  double t80;
  double t81;
  double t82;
  double t83;
  double t85;
  double t86;
  double t88;
  double t9;
  double t90;
  double t92;
  double t93;
  double t95;
  double t96;
  double t99;
  {
    T[0] = q[0];
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
    t11 = t10*t4;
    t12 = 10.0*t11;
    t13 = cos(t7);
    t14 = sin(t3);
    t15 = t13*t14;
    t16 = 10.0*t15;
    T[1] = t6-t12+t16+T[0];
    t17 = t11-t15;
    t18 = q[6];
    t19 = sin(t18);
    t20 = 53.0*t19;
    t21 = -10.0+t20;
    t22 = t17*t21;
    t23 = t13*t9;
    t24 = t23*t4;
    t25 = t8*t14;
    t26 = t24+t25;
    t27 = cos(t18);
    t28 = t26*t27;
    t29 = 53.0*t28;
    T[2] = t6+t22-t29+T[0];
    t30 = -10.0-t20;
    t31 = t17*t30;
    T[3] = t6+t31+t29+T[0];
    t32 = 15.0*t27;
    t33 = -10.0-t32+t20;
    t35 = 15.0*t19;
    t36 = 53.0*t27;
    t37 = -t35-t36;
    T[4] = t6+t17*t33+t26*t37+T[0];
    t39 = -10.0-t32-t20;
    t41 = -t35+t36;
    T[5] = t6+t17*t39+t26*t41+T[0];
    t43 = 40.0*t5;
    t44 = 53.0*t24;
    t45 = 53.0*t25;
    T[6] = -t43-t12+t16-t44-t45+T[0];
    t46 = q[11];
    t47 = cos(t46);
    t48 = 30.0*t47;
    t49 = t48-40.0;
    t50 = t5*t49;
    t51 = sin(t46);
    t52 = 30.0*t51;
    t53 = t52-10.0;
    t54 = t17*t53;
    T[7] = t50+t54-t44-t45+T[0];
    t55 = -t48-40.0;
    t56 = t5*t55;
    t57 = -t52-10.0;
    t58 = t17*t57;
    T[8] = t56+t58-t44-t45+T[0];
    t59 = 15.0*t51;
    t60 = t48+t59-40.0;
    t62 = 15.0*t47;
    t63 = t52-t62-10.0;
    T[9] = t5*t60+t17*t63-t44-t45+T[0];
    t65 = -t48+t59-40.0;
    t67 = -t52-t62-10.0;
    T[10] = t5*t65+t17*t67-t44-t45+T[0];
    T[11] = -t43-t12+t16+t44+t45+T[0];
    t69 = q[16];
    t70 = cos(t69);
    t71 = 30.0*t70;
    t72 = t71-40.0;
    t73 = t5*t72;
    t74 = sin(t69);
    t75 = 30.0*t74;
    t76 = t75-10.0;
    t77 = t17*t76;
    T[12] = t73+t77+t44+t45+T[0];
    t78 = -t71-40.0;
    t79 = t5*t78;
    t80 = -t75-10.0;
    t81 = t17*t80;
    T[13] = t79+t81+t44+t45+T[0];
    t82 = 15.0*t74;
    t83 = t71+t82-40.0;
    t85 = 15.0*t70;
    t86 = t75-t85-10.0;
    T[14] = t5*t83+t17*t86+t44+t45+T[0];
    t88 = -t71+t82-40.0;
    t90 = -t75-t85-10.0;
    T[15] = t5*t88+t17*t90+t44+t45+T[0];
    t92 = q[7];
    t93 = sin(t92);
    t95 = t17*t19;
    t96 = cos(t92);
    T[16] = t6+t22-t29+T[0]+t5*t93-t95*t96+t28*t96;
    t99 = q[8];
    t100 = sin(t99);
    t102 = cos(t99);
    T[17] = t6+t31+t29+T[0]+t5*t100-t95*t102+t28*t102;
    t105 = q[12];
    t106 = sin(t105);
    t107 = t47*t106;
    t109 = t17*t51;
    t111 = cos(t105);
    T[18] = t50+t54-t44-t45+T[0]+t5*t107+t109*t106+t26*t111;
    t113 = q[13];
    t114 = sin(t113);
    t115 = t47*t114;
    t118 = cos(t113);
    T[19] = t56+t58-t44-t45+T[0]+t5*t115+t109*t114+t26*t118;
    t120 = q[17];
    t121 = sin(t120);
    t122 = t70*t121;
    t124 = t17*t74;
    t126 = cos(t120);
    T[20] = t73+t77+t44+t45+T[0]+t5*t122+t124*t121+t26*t126;
    t128 = q[18];
    t129 = sin(t128);
    t130 = t70*t129;
    t133 = cos(t128);
    T[21] = t79+t81+t44+t45+T[0]+t5*t130+t124*t129+t26*t133;
    t137 = -1080.0+420.0*t51+420.0*t74;
    t143 = -420.0*t27-1800.0-420.0*t47-420.0*t70;
    T[22] = t5*t137/880.0+t17*t143/880.0-21.0/44.0*t26*t19+T[0];
    T[23] = q[1];
    t148 = t2*t14;
    t149 = 62.0*t148;
    t150 = t10*t14;
    t151 = 10.0*t150;
    t152 = t13*t4;
    t153 = 10.0*t152;
    T[24] = t149-t151-t153+T[23];
    t154 = t150+t152;
    t155 = t154*t21;
    t156 = t23*t14;
    t157 = t8*t4;
    t158 = t156-t157;
    t159 = t158*t27;
    t160 = 53.0*t159;
    T[25] = t149+t155-t160+T[23];
    t161 = t154*t30;
    T[26] = t149+t161+t160+T[23];
    T[27] = t149+t154*t33+t158*t37+T[23];
    T[28] = t149+t154*t39+t158*t41+T[23];
    t166 = 40.0*t148;
    t167 = 53.0*t156;
    t168 = 53.0*t157;
    T[29] = -t166-t151-t153-t167+t168+T[23];
    t169 = t148*t49;
    t170 = t154*t53;
    T[30] = t169+t170-t167+t168+T[23];
    t171 = t148*t55;
    t172 = t154*t57;
    T[31] = t171+t172-t167+t168+T[23];
    T[32] = t148*t60+t154*t63-t167+t168+T[23];
    T[33] = t148*t65+t154*t67-t167+t168+T[23];
    T[34] = -t166-t151-t153+t167-t168+T[23];
    t177 = t148*t72;
    t178 = t154*t76;
    T[35] = t177+t178+t167-t168+T[23];
    t179 = t148*t78;
    t180 = t154*t80;
    T[36] = t179+t180+t167-t168+T[23];
    T[37] = t148*t83+t154*t86+t167-t168+T[23];
    T[38] = t148*t88+t154*t90+t167-t168+T[23];
    t186 = t154*t19;
    T[39] = t149+t155-t160+T[23]+t148*t93-t186*t96+t159*t96;
    T[40] = t149+t161+t160+T[23]+t148*t100-t186*t102+t159*t102;
    t193 = t154*t51;
    T[41] = t169+t170-t167+t168+T[23]+t148*t107+t193*t106+t158*t111;
    T[42] = t171+t172-t167+t168+T[23]+t148*t115+t193*t114+t158*t118;
    t200 = t154*t74;
    T[43] = t177+t178+t167-t168+T[23]+t148*t122+t200*t121+t158*t126;
    T[44] = t179+t180+t167-t168+T[23]+t148*t130+t200*t129+t158*t133;
    T[45] = t148*t137/880.0+t154*t143/880.0-21.0/44.0*t158*t19+T[23];
    T[46] = q[2];
    t212 = 62.0*t9;
    t213 = t8*t2;
    t214 = 10.0*t213;
    T[47] = -t212-t214+T[46];
    t215 = t213*t21;
    t216 = t13*t2;
    t218 = 53.0*t216*t27;
    T[48] = -t212+t215-t218+T[46];
    t219 = t213*t30;
    T[49] = -t212+t219+t218+T[46];
    T[50] = -t212+t213*t33+t216*t37+T[46];
    T[51] = -t212+t213*t39+t216*t41+T[46];
    t224 = 40.0*t9;
    t225 = 53.0*t216;
    T[52] = t224-t214-t225+T[46];
    t226 = t9*t49;
    t227 = t213*t53;
    T[53] = -t226+t227-t225+T[46];
    t228 = t9*t55;
    t229 = t213*t57;
    T[54] = -t228+t229-t225+T[46];
    T[55] = -t9*t60+t213*t63-t225+T[46];
    T[56] = -t9*t65+t213*t67-t225+T[46];
    T[57] = t224-t214+t225+T[46];
    t234 = t9*t72;
    t235 = t213*t76;
    T[58] = -t234+t235+t225+T[46];
    t236 = t9*t78;
    t237 = t213*t80;
    T[59] = -t236+t237+t225+T[46];
    T[60] = -t9*t83+t213*t86+t225+T[46];
    T[61] = -t9*t88+t213*t90+t225+T[46];
    T[62] = -t212+t215-t218+T[46]-t9*t93-t213*t19*t96+t216*t27*t96;
    T[63] = -t212+t219+t218+T[46]-t9*t100-t213*t19*t102+t216*t27*t102;
    t252 = t9*t47;
    T[64] = -t226+t227-t225+T[46]-t252*t106+t213*t51*t106+t216*t111;
    T[65] = -t228+t229-t225+T[46]-t252*t114+t213*t51*t114+t216*t118;
    t261 = t9*t70;
    T[66] = -t234+t235+t225+T[46]-t261*t121+t213*t74*t121+t216*t126;
    T[67] = -t236+t237+t225+T[46]-t261*t129+t213*t74*t129+t216*t133;
    T[68] = -t9*t137/880.0+t213*t143/880.0-21.0/44.0*t216*t19+T[46];
    return;
  }
}

