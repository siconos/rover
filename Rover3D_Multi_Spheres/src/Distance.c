#include "LagrangianModel.h"
#include <math.h>
void Distance(CD,gamma,AngleT,q)
double CD[6];
double gamma;
double AngleT[4];
double q[21];
{
  double t1;
  double t10;
  double t101;
  double t103;
  double t104;
  double t105;
  double t107;
  double t108;
  double t109;
  double t11;
  double t111;
  double t112;
  double t113;
  double t115;
  double t116;
  double t12;
  double t120;
  double t121;
  double t126;
  double t127;
  double t133;
  double t134;
  double t136;
  double t137;
  double t138;
  double t139;
  double t14;
  double t141;
  double t144;
  double t145;
  double t146;
  double t15;
  double t150;
  double t151;
  double t152;
  double t158;
  double t159;
  double t160;
  double t162;
  double t163;
  double t164;
  double t169;
  double t17;
  double t173;
  double t174;
  double t175;
  double t176;
  double t18;
  double t180;
  double t181;
  double t185;
  double t186;
  double t19;
  double t191;
  double t193;
  double t194;
  double t195;
  double t197;
  double t198;
  double t199;
  double t2;
  double t20;
  double t201;
  double t202;
  double t203;
  double t205;
  double t206;
  double t21;
  double t210;
  double t211;
  double t216;
  double t217;
  double t223;
  double t224;
  double t226;
  double t227;
  double t228;
  double t229;
  double t23;
  double t230;
  double t231;
  double t233;
  double t234;
  double t236;
  double t238;
  double t239;
  double t24;
  double t240;
  double t242;
  double t245;
  double t246;
  double t247;
  double t248;
  double t25;
  double t253;
  double t254;
  double t255;
  double t257;
  double t258;
  double t259;
  double t26;
  double t267;
  double t268;
  double t269;
  double t27;
  double t270;
  double t271;
  double t272;
  double t273;
  double t274;
  double t275;
  double t276;
  double t28;
  double t280;
  double t281;
  double t282;
  double t283;
  double t287;
  double t288;
  double t289;
  double t294;
  double t296;
  double t297;
  double t298;
  double t3;
  double t30;
  double t300;
  double t301;
  double t302;
  double t304;
  double t305;
  double t306;
  double t308;
  double t309;
  double t31;
  double t313;
  double t314;
  double t32;
  double t320;
  double t321;
  double t327;
  double t328;
  double t33;
  double t330;
  double t331;
  double t332;
  double t333;
  double t336;
  double t338;
  double t339;
  double t340;
  double t344;
  double t345;
  double t346;
  double t351;
  double t352;
  double t353;
  double t355;
  double t356;
  double t357;
  double t365;
  double t366;
  double t367;
  double t368;
  double t37;
  double t372;
  double t373;
  double t377;
  double t378;
  double t38;
  double t383;
  double t385;
  double t386;
  double t387;
  double t389;
  double t390;
  double t391;
  double t393;
  double t394;
  double t395;
  double t397;
  double t398;
  double t4;
  double t40;
  double t402;
  double t403;
  double t409;
  double t41;
  double t410;
  double t416;
  double t417;
  double t419;
  double t42;
  double t420;
  double t421;
  double t422;
  double t423;
  double t424;
  double t426;
  double t427;
  double t429;
  double t43;
  double t431;
  double t432;
  double t433;
  double t435;
  double t438;
  double t439;
  double t440;
  double t441;
  double t446;
  double t447;
  double t448;
  double t45;
  double t450;
  double t451;
  double t452;
  double t46;
  double t460;
  double t461;
  double t462;
  double t463;
  double t464;
  double t465;
  double t466;
  double t467;
  double t47;
  double t471;
  double t472;
  double t476;
  double t477;
  double t482;
  double t484;
  double t485;
  double t486;
  double t488;
  double t489;
  double t49;
  double t490;
  double t492;
  double t493;
  double t494;
  double t496;
  double t497;
  double t5;
  double t501;
  double t502;
  double t508;
  double t509;
  double t515;
  double t516;
  double t518;
  double t519;
  double t52;
  double t520;
  double t521;
  double t524;
  double t526;
  double t527;
  double t528;
  double t532;
  double t533;
  double t534;
  double t539;
  double t540;
  double t541;
  double t543;
  double t544;
  double t545;
  double t55;
  double t553;
  double t554;
  double t555;
  double t556;
  double t56;
  double t560;
  double t561;
  double t565;
  double t566;
  double t57;
  double t571;
  double t573;
  double t574;
  double t575;
  double t577;
  double t578;
  double t579;
  double t581;
  double t582;
  double t583;
  double t585;
  double t586;
  double t59;
  double t590;
  double t591;
  double t597;
  double t598;
  double t6;
  double t60;
  double t604;
  double t605;
  double t607;
  double t61;
  double t63;
  double t66;
  double t68;
  double t7;
  double t70;
  double t73;
  double t74;
  double t75;
  double t76;
  double t77;
  double t78;
  double t79;
  double t80;
  double t81;
  double t82;
  double t86;
  double t87;
  double t88;
  double t89;
  double t9;
  double t93;
  double t94;
  double t95;
  double t96;
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
    t20 = t17*t19;
    t21 = cos(t6);
    t23 = t14*t11;
    t24 = t23*t4;
    t25 = t10*t15;
    t26 = t24+t25;
    t27 = cos(t18);
    t28 = t26*t27;
    t30 = -t20*t21+t28*t21+t5*t7;
    t31 = fabs(t30);
    t32 = t31*t31;
    t33 = t2*t15;
    t37 = t12*t15+t14*t4;
    t38 = t37*t19;
    t40 = t23*t15;
    t41 = t10*t4;
    t42 = t40-t41;
    t43 = t42*t27;
    t45 = t38*t21-t43*t21-t33*t7;
    t46 = fabs(t45);
    t47 = t46*t46;
    t49 = t10*t2;
    t52 = t14*t2;
    t55 = -t49*t19*t21+t52*t27*t21-t11*t7;
    t56 = fabs(t55);
    t57 = t56*t56;
    t59 = sqrt(t32+t47+t57);
    t60 = 1/t59;
    t61 = gamma*t60;
    t63 = AngleT[0];
    t66 = AngleT[1];
    t68 = -t45;
    t70 = AngleT[2];
    t73 = 62.0*t5;
    t74 = 15.0*t27;
    t75 = 53.0*t19;
    t76 = -10.0-t74+t75;
    t77 = t17*t76;
    t78 = 15.0*t19;
    t79 = 53.0*t27;
    t80 = -t78-t79;
    t81 = t26*t80;
    t82 = q[0];
    t86 = 62.0*t33;
    t87 = t37*t76;
    t88 = t42*t80;
    t89 = q[1];
    t93 = 62.0*t11;
    t94 = t49*t76;
    t95 = t52*t80;
    t96 = q[2];
    t101 = (t63*t60*t30+t66*t60*t68+t70*t60*t55-(t73+t77+t81+t82)*t60*t30-(t86+
t87+t88+t89)*t60*t68-(-t93+t94+t95+t96)*t60*t55)*t60;
    t103 = -t101*t30+t63-t73-t77-t81-t82;
    t104 = fabs(t103);
    t105 = t104*t104;
    t107 = -t101*t68+t66-t86-t87-t88-t89;
    t108 = fabs(t107);
    t109 = t108*t108;
    t111 = t101*t55-t70-t93+t94+t95+t96;
    t112 = fabs(t111);
    t113 = t112*t112;
    t115 = sqrt(t105+t109+t113);
    t116 = 1/t115;
    t120 = fabs(30.0*t116*t103+t61*t30-t63+t73+t77+t81+t82);
    t121 = t120*t120;
    t126 = fabs(-30.0*t116*t107-t61*t68+t66-t86-t87-t88-t89);
    t127 = t126*t126;
    t133 = fabs(-30.0*t116*t111+t61*t55-t70-t93+t94+t95+t96);
    t134 = t133*t133;
    t136 = sqrt(t121+t127+t134);
    t137 = AngleT[3];
    CD[0] = t136-t137;
    t138 = q[8];
    t139 = sin(t138);
    t141 = cos(t138);
    t144 = t5*t139-t20*t141+t28*t141;
    t145 = fabs(t144);
    t146 = t145*t145;
    t150 = -t33*t139+t38*t141-t43*t141;
    t151 = fabs(t150);
    t152 = t151*t151;
    t158 = -t49*t19*t141+t52*t27*t141-t11*t139;
    t159 = fabs(t158);
    t160 = t159*t159;
    t162 = sqrt(t146+t152+t160);
    t163 = 1/t162;
    t164 = gamma*t163;
    t169 = -t150;
    t173 = -10.0-t74-t75;
    t174 = t17*t173;
    t175 = -t78+t79;
    t176 = t26*t175;
    t180 = t37*t173;
    t181 = t42*t175;
    t185 = t49*t173;
    t186 = t52*t175;
    t191 = (t63*t163*t144+t66*t163*t169+t70*t163*t158-(t73+t174+t176+t82)*t163*
t144-(t86+t180+t181+t89)*t163*t169-(-t93+t185+t186+t96)*t163*t158)*t163;
    t193 = -t191*t144-t174-t176+t63-t73-t82;
    t194 = fabs(t193);
    t195 = t194*t194;
    t197 = -t191*t169-t180-t181+t66-t86-t89;
    t198 = fabs(t197);
    t199 = t198*t198;
    t201 = t191*t158+t185+t186-t70-t93+t96;
    t202 = fabs(t201);
    t203 = t202*t202;
    t205 = sqrt(t195+t199+t203);
    t206 = 1/t205;
    t210 = fabs(t164*t144+30.0*t206*t193+t174+t176-t63+t73+t82);
    t211 = t210*t210;
    t216 = fabs(-t164*t169-30.0*t206*t197-t180-t181+t66-t86-t89);
    t217 = t216*t216;
    t223 = fabs(t164*t158-30.0*t206*t201+t185+t186-t70-t93+t96);
    t224 = t223*t223;
    t226 = sqrt(t211+t217+t224);
    CD[1] = t226-t137;
    t227 = q[11];
    t228 = cos(t227);
    t229 = q[12];
    t230 = sin(t229);
    t231 = t228*t230;
    t233 = sin(t227);
    t234 = t17*t233;
    t236 = cos(t229);
    t238 = t234*t230+t5*t231+t26*t236;
    t239 = fabs(t238);
    t240 = t239*t239;
    t242 = t37*t233;
    t245 = t242*t230+t33*t231+t42*t236;
    t246 = fabs(t245);
    t247 = t246*t246;
    t248 = t11*t228;
    t253 = t49*t233*t230-t248*t230+t52*t236;
    t254 = fabs(t253);
    t255 = t254*t254;
    t257 = sqrt(t240+t247+t255);
    t258 = 1/t257;
    t259 = gamma*t258;
    t267 = 30.0*t228;
    t268 = 15.0*t233;
    t269 = t267+t268-40.0;
    t270 = t5*t269;
    t271 = 30.0*t233;
    t272 = 15.0*t228;
    t273 = t271-t272-10.0;
    t274 = t17*t273;
    t275 = 53.0*t24;
    t276 = 53.0*t25;
    t280 = t33*t269;
    t281 = t37*t273;
    t282 = 53.0*t40;
    t283 = 53.0*t41;
    t287 = t11*t269;
    t288 = t49*t273;
    t289 = 53.0*t52;
    t294 = (t63*t258*t238+t66*t258*t245+t70*t258*t253-(t270+t274-t275-t276+t82)
*t258*t238-(t280+t281-t282+t283+t89)*t258*t245-(-t287+t288-t289+t96)*t258*t253)
*t258;
    t296 = -t294*t238-t270-t274+t275+t276+t63-t82;
    t297 = fabs(t296);
    t298 = t297*t297;
    t300 = t294*t245+t280+t281-t282+t283-t66+t89;
    t301 = fabs(t300);
    t302 = t301*t301;
    t304 = t294*t253-t287+t288-t289-t70+t96;
    t305 = fabs(t304);
    t306 = t305*t305;
    t308 = sqrt(t298+t302+t306);
    t309 = 1/t308;
    t313 = fabs(t259*t238+30.0*t309*t296+t270+t274-t275-t276-t63+t82);
    t314 = t313*t313;
    t320 = fabs(t259*t245-30.0*t309*t300+t280+t281-t282+t283-t66+t89);
    t321 = t320*t320;
    t327 = fabs(t259*t253-30.0*t309*t304-t287+t288-t289-t70+t96);
    t328 = t327*t327;
    t330 = sqrt(t314+t321+t328);
    CD[2] = t330-t137;
    t331 = q[13];
    t332 = sin(t331);
    t333 = t228*t332;
    t336 = cos(t331);
    t338 = t234*t332+t26*t336+t5*t333;
    t339 = fabs(t338);
    t340 = t339*t339;
    t344 = t242*t332+t33*t333+t42*t336;
    t345 = fabs(t344);
    t346 = t345*t345;
    t351 = t49*t233*t332-t248*t332+t52*t336;
    t352 = fabs(t351);
    t353 = t352*t352;
    t355 = sqrt(t340+t346+t353);
    t356 = 1/t355;
    t357 = gamma*t356;
    t365 = -t267+t268-40.0;
    t366 = t5*t365;
    t367 = -t271-t272-10.0;
    t368 = t17*t367;
    t372 = t33*t365;
    t373 = t37*t367;
    t377 = t11*t365;
    t378 = t49*t367;
    t383 = (t63*t356*t338+t66*t356*t344+t70*t356*t351-(t366+t368-t275-t276+t82)
*t356*t338-(t372+t373-t282+t283+t89)*t356*t344-(-t377+t378-t289+t96)*t356*t351)
*t356;
    t385 = -t383*t338+t275+t276-t366-t368+t63-t82;
    t386 = fabs(t385);
    t387 = t386*t386;
    t389 = t383*t344-t282+t283+t372+t373-t66+t89;
    t390 = fabs(t389);
    t391 = t390*t390;
    t393 = t383*t351-t289-t377+t378-t70+t96;
    t394 = fabs(t393);
    t395 = t394*t394;
    t397 = sqrt(t387+t391+t395);
    t398 = 1/t397;
    t402 = fabs(t357*t338+30.0*t398*t385-t275-t276+t366+t368-t63+t82);
    t403 = t402*t402;
    t409 = fabs(t357*t344-30.0*t398*t389-t282+t283+t372+t373-t66+t89);
    t410 = t409*t409;
    t416 = fabs(t357*t351-30.0*t398*t393-t289-t377+t378-t70+t96);
    t417 = t416*t416;
    t419 = sqrt(t403+t410+t417);
    CD[3] = t419-t137;
    t420 = q[16];
    t421 = cos(t420);
    t422 = q[17];
    t423 = sin(t422);
    t424 = t421*t423;
    t426 = sin(t420);
    t427 = t17*t426;
    t429 = cos(t422);
    t431 = t26*t429+t427*t423+t5*t424;
    t432 = fabs(t431);
    t433 = t432*t432;
    t435 = t37*t426;
    t438 = t33*t424+t42*t429+t435*t423;
    t439 = fabs(t438);
    t440 = t439*t439;
    t441 = t11*t421;
    t446 = t49*t426*t423-t441*t423+t52*t429;
    t447 = fabs(t446);
    t448 = t447*t447;
    t450 = sqrt(t433+t440+t448);
    t451 = 1/t450;
    t452 = gamma*t451;
    t460 = 30.0*t421;
    t461 = 15.0*t426;
    t462 = t460+t461-40.0;
    t463 = t5*t462;
    t464 = 30.0*t426;
    t465 = 15.0*t421;
    t466 = t464-t465-10.0;
    t467 = t17*t466;
    t471 = t33*t462;
    t472 = t37*t466;
    t476 = t11*t462;
    t477 = t49*t466;
    t482 = (t63*t451*t431+t66*t451*t438+t70*t451*t446-(t463+t467+t275+t276+t82)
*t451*t431-(t471+t472+t282-t283+t89)*t451*t438-(-t476+t477+t289+t96)*t451*t446)
*t451;
    t484 = -t482*t431-t275-t276-t463-t467+t63-t82;
    t485 = fabs(t484);
    t486 = t485*t485;
    t488 = t482*t438+t282-t283+t471+t472-t66+t89;
    t489 = fabs(t488);
    t490 = t489*t489;
    t492 = t482*t446+t289-t476+t477-t70+t96;
    t493 = fabs(t492);
    t494 = t493*t493;
    t496 = sqrt(t486+t490+t494);
    t497 = 1/t496;
    t501 = fabs(t452*t431+30.0*t497*t484+t275+t276+t463+t467-t63+t82);
    t502 = t501*t501;
    t508 = fabs(t452*t438-30.0*t497*t488+t282-t283+t471+t472-t66+t89);
    t509 = t508*t508;
    t515 = fabs(t452*t446-30.0*t497*t492+t289-t476+t477-t70+t96);
    t516 = t515*t515;
    t518 = sqrt(t502+t509+t516);
    CD[4] = t518-t137;
    t519 = q[18];
    t520 = sin(t519);
    t521 = t421*t520;
    t524 = cos(t519);
    t526 = t26*t524+t427*t520+t5*t521;
    t527 = fabs(t526);
    t528 = t527*t527;
    t532 = t33*t521+t42*t524+t435*t520;
    t533 = fabs(t532);
    t534 = t533*t533;
    t539 = t49*t426*t520-t441*t520+t52*t524;
    t540 = fabs(t539);
    t541 = t540*t540;
    t543 = sqrt(t528+t534+t541);
    t544 = 1/t543;
    t545 = gamma*t544;
    t553 = -t460+t461-40.0;
    t554 = t5*t553;
    t555 = -t464-t465-10.0;
    t556 = t17*t555;
    t560 = t33*t553;
    t561 = t37*t555;
    t565 = t11*t553;
    t566 = t49*t555;
    t571 = (t63*t544*t526+t66*t544*t532+t70*t544*t539-(t554+t556+t275+t276+t82)
*t544*t526-(t560+t561+t282-t283+t89)*t544*t532-(-t565+t566+t289+t96)*t544*t539)
*t544;
    t573 = -t571*t526-t275-t276-t554-t556+t63-t82;
    t574 = fabs(t573);
    t575 = t574*t574;
    t577 = t571*t532+t282-t283+t560+t561-t66+t89;
    t578 = fabs(t577);
    t579 = t578*t578;
    t581 = t571*t539+t289-t565+t566-t70+t96;
    t582 = fabs(t581);
    t583 = t582*t582;
    t585 = sqrt(t575+t579+t583);
    t586 = 1/t585;
    t590 = fabs(t545*t526+30.0*t586*t573+t275+t276+t554+t556-t63+t82);
    t591 = t590*t590;
    t597 = fabs(t545*t532-30.0*t586*t577+t282-t283+t560+t561-t66+t89);
    t598 = t597*t597;
    t604 = fabs(t545*t539-30.0*t586*t581+t289-t565+t566-t70+t96);
    t605 = t604*t604;
    t607 = sqrt(t591+t598+t605);
    CD[5] = t607-t137;
    return;
  }
}
