#include "LagrangianModel.h"
#include <math.h>
void ContactHessian(CH,q,qdot)
double CH[18];
double q[21];
double qdot[21];
{
  double t1;
  double t10;
  double t103;
  double t105;
  double t106;
  double t107;
  double t108;
  double t11;
  double t114;
  double t116;
  double t117;
  double t118;
  double t119;
  double t12;
  double t123;
  double t124;
  double t125;
  double t126;
  double t128;
  double t13;
  double t130;
  double t133;
  double t135;
  double t137;
  double t14;
  double t140;
  double t142;
  double t143;
  double t144;
  double t145;
  double t146;
  double t147;
  double t148;
  double t149;
  double t150;
  double t154;
  double t155;
  double t158;
  double t159;
  double t16;
  double t160;
  double t161;
  double t162;
  double t163;
  double t165;
  double t166;
  double t167;
  double t17;
  double t170;
  double t171;
  double t172;
  double t173;
  double t174;
  double t175;
  double t177;
  double t178;
  double t179;
  double t18;
  double t181;
  double t182;
  double t183;
  double t184;
  double t185;
  double t186;
  double t187;
  double t188;
  double t189;
  double t195;
  double t197;
  double t199;
  double t2;
  double t20;
  double t201;
  double t203;
  double t206;
  double t21;
  double t210;
  double t213;
  double t214;
  double t22;
  double t221;
  double t222;
  double t223;
  double t224;
  double t225;
  double t226;
  double t227;
  double t228;
  double t229;
  double t23;
  double t233;
  double t236;
  double t237;
  double t238;
  double t24;
  double t240;
  double t241;
  double t242;
  double t245;
  double t246;
  double t247;
  double t248;
  double t249;
  double t25;
  double t250;
  double t252;
  double t253;
  double t254;
  double t26;
  double t260;
  double t262;
  double t263;
  double t264;
  double t266;
  double t268;
  double t27;
  double t271;
  double t273;
  double t274;
  double t28;
  double t280;
  double t281;
  double t288;
  double t29;
  double t291;
  double t293;
  double t295;
  double t296;
  double t297;
  double t298;
  double t3;
  double t30;
  double t300;
  double t301;
  double t303;
  double t304;
  double t305;
  double t306;
  double t308;
  double t309;
  double t31;
  double t310;
  double t311;
  double t313;
  double t314;
  double t32;
  double t321;
  double t325;
  double t34;
  double t340;
  double t347;
  double t35;
  double t351;
  double t36;
  double t366;
  double t367;
  double t368;
  double t369;
  double t370;
  double t371;
  double t372;
  double t373;
  double t374;
  double t38;
  double t39;
  double t4;
  double t40;
  double t41;
  double t42;
  double t43;
  double t434;
  double t435;
  double t44;
  double t46;
  double t47;
  double t48;
  double t49;
  double t497;
  double t499;
  double t5;
  double t50;
  double t501;
  double t51;
  double t52;
  double t54;
  double t55;
  double t56;
  double t57;
  double t58;
  double t59;
  double t6;
  double t60;
  double t61;
  double t62;
  double t65;
  double t69;
  double t7;
  double t71;
  double t72;
  double t73;
  double t74;
  double t75;
  double t76;
  double t77;
  double t81;
  double t82;
  double t83;
  double t84;
  double t85;
  double t86;
  double t87;
  double t9;
  double t94;
  double t96;
  {
    t1 = q[4];
    t2 = cos(t1);
    t3 = qdot[4];
    t4 = t3*t3;
    t5 = t2*t4;
    t6 = q[5];
    t7 = cos(t6);
    t9 = 0.6374999*t5*t7;
    t10 = sin(t1);
    t11 = t10*t3;
    t12 = sin(t6);
    t13 = qdot[5];
    t14 = t12*t13;
    t16 = 0.12749998E1*t11*t14;
    t17 = t7*t2;
    t18 = t13*t13;
    t20 = 0.6374999*t17*t18;
    t21 = q[3];
    t22 = sin(t21);
    t23 = qdot[3];
    t24 = t23*t23;
    t25 = t22*t24;
    t26 = t10*t7;
    t27 = t25*t26;
    t28 = cos(t21);
    t29 = t28*t23;
    t30 = t2*t3;
    t31 = t30*t7;
    t32 = t29*t31;
    t34 = t10*t12;
    t35 = t34*t13;
    t36 = t29*t35;
    t38 = t22*t10;
    t39 = t7*t4;
    t40 = t38*t39;
    t41 = t22*t2;
    t42 = t3*t12;
    t43 = t42*t13;
    t44 = t41*t43;
    t46 = t7*t18;
    t47 = t38*t46;
    t48 = t28*t24;
    t49 = t48*t12;
    t50 = t22*t23;
    t51 = t7*t13;
    t52 = t50*t51;
    t54 = t28*t12;
    t55 = t54*t18;
    t56 = -t27+2.0*t32-2.0*t36-t40-2.0*t44-t47+t49+2.0*t52+t55;
    t57 = q[6];
    t58 = cos(t57);
    t59 = 0.601203*t58;
    t60 = sin(t57);
    t61 = 0.286*t60;
    t62 = t59+t61;
    t65 = t3*t7;
    t69 = t28*t7;
    t71 = t26*t29+t41*t65-t38*t14+t50*t12-t69*t13;
    t72 = qdot[6];
    t73 = t60*t72;
    t74 = 0.601203*t73;
    t75 = t58*t72;
    t76 = 0.286*t75;
    t77 = -t74+t76;
    t81 = t38*t7-t54;
    t82 = t72*t72;
    t83 = t58*t82;
    t84 = 0.601203*t83;
    t85 = t60*t82;
    t86 = 0.286*t85;
    t87 = -t84-t86;
    t94 = t28*t10;
    t96 = t28*t2;
    t103 = t22*t12;
    t105 = -t26*t48-2.0*t50*t31+2.0*t50*t35-t94*t39-2.0*t96*t43-t94*t46-t12*t25
+2.0*t29*t51-t103*t18;
    t106 = 0.601203*t60;
    t107 = 0.286*t58;
    t108 = -0.16375+t106-t107;
    t114 = t22*t7;
    t116 = -t50*t26+t96*t65-t94*t14+t29*t12+t114*t13;
    t117 = 0.601203*t75;
    t118 = 0.286*t73;
    t119 = t117+t118;
    t123 = t94*t7+t103;
    t124 = 0.601203*t85;
    t125 = 0.286*t83;
    t126 = -t124+t125;
    CH[0] = t9-t16+t20+t56*t62+2.0*t71*t77+t81*t87+t105*t108+2.0*t116*t119+t123
*t126;
    t128 = -t59+t61;
    t130 = t74+t76;
    t133 = t84-t86;
    t135 = -0.16375-t106-t107;
    t137 = -t117+t118;
    t140 = t124+t125;
    CH[1] = t9-t16+t20+t56*t128+2.0*t71*t130+t81*t133+t105*t135+2.0*t116*t137+
t123*t140;
    t142 = q[11];
    t143 = sin(t142);
    t144 = qdot[11];
    t145 = t143*t144;
    t146 = 0.32*t145;
    t147 = cos(t142);
    t148 = t147*t144;
    t149 = 0.216*t148;
    t150 = t146-t149;
    t154 = t2*t12;
    t155 = t13*t150;
    t158 = 0.601203*t49;
    t159 = 0.1202406E1*t52;
    t160 = 0.601203*t55;
    t161 = 0.32*t143;
    t162 = 0.216*t147;
    t163 = t161-0.23375-t162;
    t165 = 0.32*t148;
    t166 = 0.216*t145;
    t167 = t165+t166;
    t170 = t144*t144;
    t171 = t143*t170;
    t172 = 0.32*t171;
    t173 = t147*t170;
    t174 = 0.216*t173;
    t175 = -t172+t174;
    t177 = 0.32*t173;
    t178 = 0.216*t171;
    t179 = t177+t178;
    t181 = 0.601203*t40;
    t182 = 0.1202406E1*t32;
    t183 = 0.601203*t27;
    t184 = 0.601203*t47;
    t185 = 0.1202406E1*t44;
    t186 = 0.1202406E1*t36;
    t187 = 0.32*t147;
    t188 = 0.216*t143;
    t189 = -t187+0.4025001-t188;
    t195 = t18*t189;
    CH[2] = -2.0*t11*t7*t150-2.0*t154*t155+t158+t159+t160+t105*t163+2.0*t116*
t167+t123*t175+t17*t179-t181+t182-t183-t184-t185-t186-t5*t7*t189+2.0*t11*t14*
t189-t17*t195;
    t197 = -t177+t178;
    t199 = t172+t174;
    t201 = -t161-0.23375-t162;
    t203 = -t165+t166;
    t206 = -t146-t149;
    t210 = t13*t206;
    t213 = t187+0.4025001-t188;
    t214 = t18*t213;
    CH[3] = t158+t159+t160+t17*t197+t123*t199+t105*t201+2.0*t116*t203-2.0*t11*
t7*t206-2.0*t154*t210-t181+t182-t183-t184-t185-t186-t17*t214+2.0*t11*t14*t213-
t5*t7*t213;
    t221 = q[16];
    t222 = sin(t221);
    t223 = qdot[16];
    t224 = t222*t223;
    t225 = 0.32*t224;
    t226 = cos(t221);
    t227 = t226*t223;
    t228 = 0.216*t227;
    t229 = t225-t228;
    t233 = t13*t229;
    t236 = 0.32*t222;
    t237 = 0.216*t226;
    t238 = t236-0.23375-t237;
    t240 = 0.32*t227;
    t241 = 0.216*t224;
    t242 = t240+t241;
    t245 = t223*t223;
    t246 = t222*t245;
    t247 = 0.32*t246;
    t248 = t226*t245;
    t249 = 0.216*t248;
    t250 = -t247+t249;
    t252 = 0.32*t226;
    t253 = 0.216*t222;
    t254 = -t252+0.4025001-t253;
    t260 = t18*t254;
    t262 = 0.32*t248;
    t263 = 0.216*t246;
    t264 = t262+t263;
    CH[4] = -t158-t159-t160-2.0*t11*t7*t229-2.0*t154*t233+t105*t238+2.0*t116*
t242+t123*t250+t181-t182+t183-t5*t7*t254+2.0*t11*t14*t254-t17*t260+t184+t185+
t186+t17*t264;
    t266 = -t236-0.23375-t237;
    t268 = -t240+t241;
    t271 = t247+t249;
    t273 = -t225-t228;
    t274 = t13*t273;
    t280 = t252+0.4025001-t253;
    t281 = t18*t280;
    t288 = -t262+t263;
    CH[5] = -t158-t159-t160+t105*t266+2.0*t116*t268+t123*t271-2.0*t154*t274-2.0
*t11*t7*t273+t181-t182+t183+t184+t185+t186-t17*t281-t5*t7*t280+2.0*t11*t14*t280
+t17*t288;
    t291 = 0.6374999*t5*t12;
    t293 = 0.12749998E1*t11*t51;
    t295 = 0.6374999*t154*t18;
    t296 = t25*t34;
    t297 = t30*t12;
    t298 = t29*t297;
    t300 = t26*t13;
    t301 = t29*t300;
    t303 = t12*t4;
    t304 = t38*t303;
    t305 = t65*t13;
    t306 = t41*t305;
    t308 = t12*t18;
    t309 = t38*t308;
    t310 = t48*t7;
    t311 = t50*t14;
    t313 = t69*t18;
    t314 = -t296+2.0*t298+2.0*t301-t304+2.0*t306-t309-t310+2.0*t311-t313;
    t321 = t29*t34+t41*t42+t38*t51-t50*t7-t54*t13;
    t325 = t38*t12+t69;
    t340 = -t48*t34-2.0*t50*t297-2.0*t50*t300-t94*t303+2.0*t96*t305-t94*t308+t7
*t25+2.0*t29*t14+t114*t18;
    t347 = -t50*t34+t96*t42+t94*t51-t29*t7+t103*t13;
    t351 = t94*t12-t114;
    CH[6] = t291+t293+t295+t314*t62+2.0*t321*t77+t325*t87+t340*t108+2.0*t347*
t119+t351*t126;
    CH[7] = t291+t293+t295+t314*t128+2.0*t321*t130+t325*t133+t340*t135+2.0*t347
*t137+t351*t140;
    t366 = 0.601203*t309;
    t367 = 0.1202406E1*t298;
    t368 = 0.601203*t296;
    t369 = 0.1202406E1*t306;
    t370 = 0.1202406E1*t301;
    t371 = 0.601203*t304;
    t372 = 0.601203*t310;
    t373 = 0.1202406E1*t311;
    t374 = 0.601203*t313;
    CH[8] = t154*t179+t340*t163+2.0*t347*t167+t351*t175-t366+t367-t368+t369+
t370-t371-t372+t373-t374-2.0*t11*t12*t150+2.0*t17*t155-t5*t12*t189-2.0*t11*t51*
t189-t154*t195;
    CH[9] = t154*t197-2.0*t11*t12*t206+2.0*t17*t210-t366+t367-t368+t369+t370-
t371-t154*t214-2.0*t11*t51*t213-t5*t12*t213-t372+t373-t374+t340*t201+2.0*t347*
t203+t351*t199;
    CH[10] = t154*t264-t5*t12*t254-2.0*t11*t51*t254+t366-t367-t154*t260+t368-
t369-t370+t371+2.0*t17*t233+t372-t373+t374+t340*t238+2.0*t347*t242+t351*t250
-2.0*t11*t12*t229;
    CH[11] = t340*t266+2.0*t347*t268+t351*t271-2.0*t11*t12*t273+2.0*t17*t274+
t366-t367+t368-t369-t370+t371+t372-t373+t374+t154*t288-2.0*t11*t51*t280-t154*
t281-t5*t12*t280;
    t434 = t10*t4;
    t435 = 0.6374999*t434;
    CH[12] = -t435-t25*t2*t62-2.0*t29*t11*t62+2.0*t29*t2*t77-t41*t4*t62-2.0*t38
*t3*t77+t41*t87-t48*t2*t108+2.0*t50*t11*t108-2.0*t50*t2*t119-t96*t4*t108-2.0*
t94*t3*t119+t96*t126;
    CH[13] = -t435-t25*t2*t128-2.0*t29*t11*t128+2.0*t29*t2*t130-t41*t4*t128-2.0
*t38*t3*t130+t41*t133-t48*t2*t135+2.0*t50*t11*t135-2.0*t50*t2*t137-t96*t4*t135
-2.0*t94*t3*t137+t96*t140;
    t497 = 0.601203*t25*t2;
    t499 = 0.1202406E1*t29*t11;
    t501 = 0.601203*t41*t4;
    CH[14] = t434*t189-2.0*t30*t150-t10*t179-t497-t499-t501-t48*t2*t163+2.0*t50
*t11*t163-2.0*t50*t2*t167-t96*t4*t163-2.0*t94*t3*t167+t96*t175;
    CH[15] = t434*t213-2.0*t30*t206-t10*t197-t497-t499-t501-t48*t2*t201+2.0*t50
*t11*t201-2.0*t50*t2*t203-t96*t4*t201-2.0*t94*t3*t203+t96*t199;
    CH[16] = t434*t254-2.0*t30*t229-t10*t264+t497+t499+t501-t48*t2*t238+2.0*t50
*t11*t238-2.0*t50*t2*t242-t96*t4*t238-2.0*t94*t3*t242+t96*t250;
    CH[17] = t434*t280-2.0*t30*t273-t10*t288+t497+t499+t501-t48*t2*t266+2.0*t50
*t11*t266-2.0*t50*t2*t268-t96*t4*t266-2.0*t94*t3*t268+t96*t271;
    return;
  }
}

