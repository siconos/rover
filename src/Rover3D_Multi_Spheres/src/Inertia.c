#include <math.h>
#include "Robot.h"
void Inertia(double M[441], double q[21])
{
  double C0 = cos(q[0]);
  double S0 = sin(q[0]);
  double C1 = cos(q[1]);
  double S1 = sin(q[1]);
  double C2 = cos(q[2]);
  double S2 = sin(q[2]);
  double C3 = cos(q[3]);
  double S3 = sin(q[3]);
  double C4 = cos(q[4]);
  double S4 = sin(q[4]);
  double C5 = cos(q[5]);
  double S5 = sin(q[5]);
  double C6 = cos(q[6]);
  double S6 = sin(q[6]);
  double C7 = cos(q[7]);
  double S7 = sin(q[7]);
  double C8 = cos(q[8]);
  double S8 = sin(q[8]);
  double C9 = cos(q[9]);
  double S9 = sin(q[9]);
  double C10 = cos(q[10]);
  double S10 = sin(q[10]);
  double C11 = cos(q[11]);
  double S11 = sin(q[11]);
  double C12 = cos(q[12]);
  double S12 = sin(q[12]);
  double C13 = cos(q[13]);
  double S13 = sin(q[13]);
  double C14 = cos(q[14]);
  double S14 = sin(q[14]);
  double C15 = cos(q[15]);
  double S15 = sin(q[15]);
  double C16 = cos(q[16]);
  double S16 = sin(q[16]);
  double C17 = cos(q[17]);
  double S17 = sin(q[17]);
  double C18 = cos(q[18]);
  double S18 = sin(q[18]);
  double C19 = cos(q[19]);
  double S19 = sin(q[19]);
  double C20 = cos(q[20]);
  double S20 = sin(q[20]);
  double tmp1 = 750 * S9;
  double tmp2 = -750 * S9;
  double tmp3 = 750 * C9;
  double tmp4 = 750 * C9;
  double tmp5 = C9 * tmp1 - S9 * tmp4;
  double tmp6 = C9 * tmp2 + S9 * tmp3;
  double tmp7 = C9 * tmp3 - S9 * tmp2 + 6855;
  double tmp8 = 0.45e2 / 0.2e1 + S9 * tmp1 + C9 * tmp4;
  double tmp9 = 8355 * S7;
  double tmp10 = -tmp7 * S7;
  double tmp11 = tmp6 * C7;
  double tmp12 = 8355 * C7;
  double tmp13 = tmp7 * C7;
  double tmp14 = -tmp6 * S7;
  double tmp15 = C7 * tmp9 - S7 * tmp13;
  double tmp16 = C7 * tmp10 + S7 * tmp12;
  double tmp17 = C7 * tmp5;
  double tmp18 = -S7 * tmp5 - 23850;
  double tmp19 = C7 * tmp12 - S7 * tmp10 + 300;
  double tmp20 = 0.921415e6 / 0.6e1 + C7 * tmp13 + S7 * tmp9;
  double tmp21 = 0.921415e6 / 0.6e1 + tmp8;
  double tmp22 = tmp14 - 23850;
  double tmp23 = -S7 * tmp5;
  double tmp24 = 1500 * S7;
  double tmp25 = 1500 * C7;
  double tmp26 = C7 * tmp5;
  double tmp27 = 750 * S10;
  double tmp28 = -750 * S10;
  double tmp29 = 750 * C10;
  double tmp30 = 750 * C10;
  double tmp31 = C10 * tmp27 - S10 * tmp30;
  double tmp32 = C10 * tmp28 + S10 * tmp29;
  double tmp33 = C10 * tmp29 - S10 * tmp28 + 6855;
  double tmp34 = 0.45e2 / 0.2e1 + S10 * tmp27 + C10 * tmp30;
  double tmp35 = 8355 * S8;
  double tmp36 = -tmp33 * S8;
  double tmp37 = tmp32 * C8;
  double tmp38 = 8355 * C8;
  double tmp39 = tmp33 * C8;
  double tmp40 = -tmp32 * S8;
  double tmp41 = C8 * tmp35 - S8 * tmp39 + tmp15;
  double tmp42 = C8 * tmp36 + S8 * tmp38 + tmp16;
  double tmp43 = C8 * tmp31 + tmp17;
  double tmp44 = -S8 * tmp31 + tmp18 + 23850;
  double tmp45 = tmp11 + tmp37;
  double tmp46 = C8 * tmp38 - S8 * tmp36 + tmp19;
  double tmp47 = C8 * tmp39 + S8 * tmp35 + tmp20 + 98315;
  double tmp48 = tmp21 + tmp34 + 98315;
  double tmp49 = tmp22 + tmp40 + 23850;
  double tmp50 = 1500 * C8;
  double tmp51 = C8 * tmp31;
  double tmp52 = 1500 * S8;
  double tmp53 = -S8 * tmp31;
  double tmp54 = -900 * C6;
  double tmp55 = -900 * S6;
  double tmp56 = -900 * C6;
  double tmp57 = 900 * S6;
  double tmp58 = 62 * tmp55;
  double tmp59 = -10 * tmp55;
  double tmp60 = 62 * tmp54;
  double tmp61 = 10 * tmp54;
  double tmp62 = 10 * tmp54;
  double tmp63 = tmp42 * C6 + tmp43 * S6;
  double tmp64 = tmp43 * C6 - tmp42 * S6;
  double tmp65 = tmp44 * C6 - tmp46 * S6;
  double tmp66 = tmp46 * C6 + tmp44 * S6;
  double tmp67 = tmp48 * C6 - tmp49 * S6;
  double tmp68 = tmp49 * C6 + tmp48 * S6;
  double tmp69 = tmp54 - 1200;
  double tmp70 = C6 * tmp41 + S6 * tmp45 - tmp58;
  double tmp71 = tmp63 - tmp58;
  double tmp72 = tmp64 + 74400 - tmp60;
  double tmp73 = C6 * tmp65 + S6 * tmp67 - tmp59;
  double tmp74 = C6 * tmp45 - S6 * tmp41 - tmp60 + 74400;
  double tmp75 = C6 * tmp66 + S6 * tmp68 - 2 * tmp61 + 1273280;
  double tmp76 = 592000 + tmp47 - 2 * tmp62;
  double tmp77 = C6 * tmp67 - S6 * tmp65 + 1681280;
  double tmp78 = C6 * tmp68 - S6 * tmp66 - tmp59;
  double tmp79 = -S6 * tmp50;
  double tmp80 = C6 * tmp23 + S6 * tmp8;
  double tmp81 = C6 * tmp34 - S6 * tmp53;
  double tmp82 = -S6 * tmp25;
  double tmp83 = C6 * tmp50;
  double tmp84 = C6 * tmp41 + S6 * tmp45 + 62 * tmp57;
  double tmp85 = C6 * tmp25;
  double tmp86 = C6 * tmp45 - S6 * tmp41 - 62 * tmp56;
  double tmp87 = C6 * tmp53 + S6 * tmp34;
  double tmp88 = tmp47 - 10 * tmp56;
  double tmp89 = C6 * tmp8 - S6 * tmp23;
  double tmp90 = 750 * S14;
  double tmp91 = -750 * S14;
  double tmp92 = 750 * C14;
  double tmp93 = 750 * C14;
  double tmp94 = C14 * tmp90 - S14 * tmp93;
  double tmp95 = C14 * tmp91 + S14 * tmp92;
  double tmp96 = C14 * tmp92 - S14 * tmp91 + 6855;
  double tmp97 = 0.45e2 / 0.2e1 + S14 * tmp90 + C14 * tmp93;
  double tmp98 = 8355 * S12;
  double tmp99 = -tmp96 * S12;
  double tmp100 = tmp95 * C12;
  double tmp101 = 8355 * C12;
  double tmp102 = tmp96 * C12;
  double tmp103 = -tmp95 * S12;
  double tmp104 = C12 * tmp98 - S12 * tmp102;
  double tmp105 = C12 * tmp99 + S12 * tmp101;
  double tmp106 = C12 * tmp94 + 13500;
  double tmp107 = -S12 * tmp94;
  double tmp108 = tmp100 + 13500;
  double tmp109 = 0.156200e6 / 0.3e1 - S12 * tmp99 + C12 * tmp101;
  double tmp110 = C12 * tmp102 + S12 * tmp98 + 300;
  double tmp111 = 0.156200e6 / 0.3e1 + tmp97;
  double tmp112 = C12 * tmp94;
  double tmp113 = 1500 * C12;
  double tmp114 = -S12 * tmp94;
  double tmp115 = 1500 * S12;
  double tmp116 = 750 * S15;
  double tmp117 = -750 * S15;
  double tmp118 = 750 * C15;
  double tmp119 = 750 * C15;
  double tmp120 = C15 * tmp116 - S15 * tmp119;
  double tmp121 = C15 * tmp117 + S15 * tmp118;
  double tmp122 = C15 * tmp118 - S15 * tmp117 + 6855;
  double tmp123 = 0.45e2 / 0.2e1 + S15 * tmp116 + C15 * tmp119;
  double tmp124 = 8355 * S13;
  double tmp125 = -tmp122 * S13;
  double tmp126 = tmp121 * C13;
  double tmp127 = 8355 * C13;
  double tmp128 = tmp122 * C13;
  double tmp129 = -tmp121 * S13;
  double tmp130 = C13 * tmp124 - S13 * tmp128 + tmp104;
  double tmp131 = C13 * tmp125 + S13 * tmp127 + tmp105;
  double tmp132 = C13 * tmp120 + tmp106 - 13500;
  double tmp133 = -S13 * tmp120 + tmp107;
  double tmp134 = tmp108 + tmp126 - 13500;
  double tmp135 = C13 * tmp127 - S13 * tmp125 + tmp109 + 31500;
  double tmp136 = C13 * tmp128 + S13 * tmp124 + tmp110;
  double tmp137 = tmp111 + tmp123 + 31500;
  double tmp138 = tmp103 + tmp129;
  double tmp139 = 1500 * S13;
  double tmp140 = -S13 * tmp120;
  double tmp141 = 1500 * C13;
  double tmp142 = C13 * tmp120;
  double tmp143 = 900 * S11;
  double tmp144 = -900 * C11;
  double tmp145 = 900 * C11;
  double tmp146 = 900 * S11;
  double tmp147 = -53 * tmp143;
  double tmp148 = -10 * tmp143;
  double tmp149 = -40 * tmp144;
  double tmp150 = 10 * tmp144 + 40 * tmp143;
  double tmp151 = 10 * tmp144;
  double tmp152 = 40 * tmp143;
  double tmp153 = -53 * tmp144;
  double tmp154 = tmp130 * C11 - tmp133 * S11;
  double tmp155 = tmp132 * C11 + tmp136 * S11;
  double tmp156 = tmp133 * C11 + tmp130 * S11;
  double tmp157 = tmp134 * C11 - tmp137 * S11;
  double tmp158 = tmp136 * C11 - tmp132 * S11;
  double tmp159 = tmp137 * C11 + tmp134 * S11;
  double tmp160 = 2640 + tmp143;
  double tmp161 = tmp69 + tmp144 - 1200;
  double tmp162 = tmp55 - 6360;
  double tmp163 = tmp70 + tmp154 - 254400 - tmp147;
  double tmp164 = C11 * tmp131 - S11 * tmp138 - tmp147 + tmp71 - 254400;
  double tmp165 = C11 * tmp155 - S11 * tmp159 - tmp148 - tmp149 + tmp72 - 48000;
  double tmp166 = tmp73 + tmp156 - 63600 - tmp153;
  double tmp167 = C11 * tmp157 + S11 * tmp158 - tmp148 - tmp149 + tmp74 - 48000;
  double tmp168 = tmp75 + tmp135 + 204000 - 2 * tmp150;
  double tmp169 = C11 * tmp158 - S11 * tmp157 - 2 * tmp151 + tmp76 + 349080;
  double tmp170 = C11 * tmp159 + S11 * tmp155 - 2 * tmp152 + tmp77 + 529080;
  double tmp171 = C11 * tmp138 + S11 * tmp131 - tmp153 + tmp78 - 63600;
  double tmp172 = C11 * tmp112 - S11 * tmp97;
  double tmp173 = S11 * tmp115;
  double tmp174 = C11 * tmp139;
  double tmp175 = C11 * tmp123 + S11 * tmp142;
  double tmp176 = C11 * tmp131 - S11 * tmp138 + 53 * tmp146;
  double tmp177 = tmp135 + 10 * tmp145 - 40 * tmp146;
  double tmp178 = C11 * tmp142 - S11 * tmp123;
  double tmp179 = C11 * tmp97 + S11 * tmp112;
  double tmp180 = S11 * tmp139;
  double tmp181 = C11 * tmp138 + S11 * tmp131 - 53 * tmp145;
  double tmp182 = C11 * tmp115;
  double tmp183 = 750 * S19;
  double tmp184 = -750 * S19;
  double tmp185 = 750 * C19;
  double tmp186 = 750 * C19;
  double tmp187 = C19 * tmp183 - S19 * tmp186;
  double tmp188 = C19 * tmp184 + S19 * tmp185;
  double tmp189 = C19 * tmp185 - S19 * tmp184 + 6855;
  double tmp190 = 0.45e2 / 0.2e1 + S19 * tmp183 + C19 * tmp186;
  double tmp191 = 8355 * S17;
  double tmp192 = -tmp189 * S17;
  double tmp193 = tmp188 * C17;
  double tmp194 = 8355 * C17;
  double tmp195 = tmp189 * C17;
  double tmp196 = -tmp188 * S17;
  double tmp197 = C17 * tmp191 - S17 * tmp195;
  double tmp198 = C17 * tmp192 + S17 * tmp194;
  double tmp199 = C17 * tmp187 + 13500;
  double tmp200 = -S17 * tmp187;
  double tmp201 = tmp193 + 13500;
  double tmp202 = 0.156200e6 / 0.3e1 - S17 * tmp192 + C17 * tmp194;
  double tmp203 = C17 * tmp195 + S17 * tmp191 + 300;
  double tmp204 = 0.156200e6 / 0.3e1 + tmp190;
  double tmp205 = 1500 * C17;
  double tmp206 = 1500 * S17;
  double tmp207 = C17 * tmp187;
  double tmp208 = -S17 * tmp187;
  double tmp209 = 750 * S20;
  double tmp210 = -750 * S20;
  double tmp211 = 750 * C20;
  double tmp212 = 750 * C20;
  double tmp213 = C20 * tmp209 - S20 * tmp212;
  double tmp214 = C20 * tmp210 + S20 * tmp211;
  double tmp215 = C20 * tmp211 - S20 * tmp210 + 6855;
  double tmp216 = 0.45e2 / 0.2e1 + S20 * tmp209 + C20 * tmp212;
  double tmp217 = 8355 * S18;
  double tmp218 = -tmp215 * S18;
  double tmp219 = tmp214 * C18;
  double tmp220 = 8355 * C18;
  double tmp221 = tmp215 * C18;
  double tmp222 = -tmp214 * S18;
  double tmp223 = C18 * tmp217 - S18 * tmp221 + tmp197;
  double tmp224 = C18 * tmp218 + S18 * tmp220 + tmp198;
  double tmp225 = C18 * tmp213 + tmp199 - 13500;
  double tmp226 = -S18 * tmp213 + tmp200;
  double tmp227 = tmp201 + tmp219 - 13500;
  double tmp228 = C18 * tmp220 - S18 * tmp218 + tmp202 + 31500;
  double tmp229 = C18 * tmp221 + S18 * tmp217 + tmp203;
  double tmp230 = tmp204 + tmp216 + 31500;
  double tmp231 = tmp196 + tmp222;
  double tmp232 = C18 * tmp213;
  double tmp233 = -S18 * tmp213;
  double tmp234 = 1500 * S18;
  double tmp235 = 1500 * C18;
  double tmp236 = 900 * S16;
  double tmp237 = -900 * C16;
  double tmp238 = 900 * C16;
  double tmp239 = 900 * S16;
  double tmp240 = 53 * tmp236;
  double tmp241 = -10 * tmp236;
  double tmp242 = -40 * tmp237;
  double tmp243 = 10 * tmp237 + 40 * tmp236;
  double tmp244 = 10 * tmp237;
  double tmp245 = 40 * tmp236;
  double tmp246 = 53 * tmp237;
  double tmp247 = tmp223 * C16 - tmp226 * S16;
  double tmp248 = tmp225 * C16 + tmp229 * S16;
  double tmp249 = tmp226 * C16 + tmp223 * S16;
  double tmp250 = tmp227 * C16 - tmp230 * S16;
  double tmp251 = tmp229 * C16 - tmp225 * S16;
  double tmp252 = tmp230 * C16 + tmp227 * S16;
  double tmp253 = tmp160 + tmp236 - 4800;
  double tmp254 = tmp161 + tmp237 - 1200;
  double tmp255 = tmp162 + 6360;
  double tmp256 = tmp163 + tmp247 + 254400 - tmp240;
  double tmp257 = C16 * tmp224 - S16 * tmp231 + tmp164 - tmp240 + 254400;
  double tmp258 = C16 * tmp248 - S16 * tmp252 + tmp165 - tmp241 - tmp242 - 48000;
  double tmp259 = tmp166 + tmp249 + 63600 - tmp246;
  double tmp260 = C16 * tmp250 + S16 * tmp251 + tmp167 - tmp241 - tmp242 - 48000;
  double tmp261 = tmp168 + tmp228 + 204000 - 2 * tmp243;
  double tmp262 = C16 * tmp251 - S16 * tmp250 + tmp169 - 2 * tmp244 + 349080;
  double tmp263 = C16 * tmp252 + S16 * tmp248 + tmp170 - 2 * tmp245 + 529080;
  double tmp264 = C16 * tmp231 + S16 * tmp224 + tmp171 - tmp246 + 63600;
  double tmp265 = S16 * tmp234;
  double tmp266 = C16 * tmp216 + S16 * tmp232;
  double tmp267 = C16 * tmp232 - S16 * tmp216;
  double tmp268 = C16 * tmp234;
  double tmp269 = C16 * tmp190 + S16 * tmp207;
  double tmp270 = C16 * tmp206;
  double tmp271 = C16 * tmp224 - S16 * tmp231 - 53 * tmp239;
  double tmp272 = C16 * tmp207 - S16 * tmp190;
  double tmp273 = C16 * tmp231 + S16 * tmp224 + 53 * tmp238;
  double tmp274 = tmp228 + 10 * tmp238 - 40 * tmp239;
  double tmp275 = S16 * tmp206;
  double tmp276 = tmp145 * C4 * S5 + tmp146 * (S3 * S4 * S5 + C3 * C5);
  double tmp277 = tmp146 * S3 * C4 - tmp145 * S4;
  double tmp278 = tmp238 * C4 * S5 + tmp239 * (S3 * S4 * S5 + C3 * C5);
  double tmp279 = tmp56 * C3 * C4 + tmp57 * S3 * C4;
  double tmp280 = tmp239 * S3 * C4 - tmp238 * S4;
  double tmp281 = tmp57 * (S3 * S4 * S5 + C3 * C5) + tmp56 * (C3 * S4 * S5 - S3 * C5);
  double tmp282 = tmp57 * (S3 * S4 * C5 - C3 * S5) + tmp56 * (C3 * S4 * C5 + S3 * S5);
  double tmp283 = tmp145 * C4 * C5 + tmp146 * (S3 * S4 * C5 - C3 * S5);
  double tmp284 = tmp238 * C4 * C5 + tmp239 * (S3 * S4 * C5 - C3 * S5);
  double tmp285 = tmp235 * C3 * C4 + tmp265 * S3 * C4 - tmp268 * S4;
  double tmp286 = tmp177 * C3 * C4 + tmp181 * S3 * C4 - tmp176 * S4;
  double tmp287 = tmp141 * C3 * C4 + tmp180 * S3 * C4 - tmp174 * S4;
  double tmp288 = tmp85 * C3 * C4 + tmp82 * S3 * C4 - tmp24 * S4;
  double tmp289 = tmp274 * C3 * C4 + tmp273 * S3 * C4 - tmp271 * S4;
  double tmp290 = tmp233 * C3 * C4 + tmp266 * S3 * C4 - tmp267 * S4;
  double tmp291 = tmp84 * C3 * C4 + tmp86 * S3 * C4 - tmp88 * S4;
  double tmp292 = tmp181 * C3 - tmp177 * S3;
  double tmp293 = tmp87 * C3 * C4 + tmp81 * S3 * C4 - tmp51 * S4;
  double tmp294 = tmp79 * C3 - tmp83 * S3;
  double tmp295 = tmp179 * C3 - tmp114 * S3;
  double tmp296 = tmp113 * C3 * C4 + tmp173 * S3 * C4 - tmp182 * S4;
  double tmp297 = tmp265 * C3 - tmp235 * S3;
  double tmp298 = tmp83 * C3 * C4 + tmp79 * S3 * C4 - tmp52 * S4;
  double tmp299 = tmp81 * C3 - tmp87 * S3;
  double tmp300 = tmp175 * C3 - tmp140 * S3;
  double tmp301 = tmp80 * C3 * C4 + tmp89 * S3 * C4 - tmp26 * S4;
  double tmp302 = tmp273 * C3 - tmp274 * S3;
  double tmp303 = tmp89 * C3 - tmp80 * S3;
  double tmp304 = tmp205 * C3 * C4 + tmp275 * S3 * C4 - tmp270 * S4;
  double tmp305 = tmp275 * C3 - tmp205 * S3;
  double tmp306 = tmp208 * C3 * C4 + tmp269 * S3 * C4 - tmp272 * S4;
  double tmp307 = tmp114 * C3 * C4 + tmp179 * S3 * C4 - tmp172 * S4;
  double tmp308 = tmp140 * C3 * C4 + C4 * S3 * tmp175 - S4 * tmp178;
  double tmp309 = tmp173 * C3 - tmp113 * S3;
  double tmp310 = tmp82 * C3 - tmp85 * S3;
  double tmp311 = tmp269 * C3 - tmp208 * S3;
  double tmp312 = tmp180 * C3 - tmp141 * S3;
  double tmp313 = tmp86 * C3 - tmp84 * S3;
  double tmp314 = tmp266 * C3 - tmp233 * S3;
  double tmp315 = -tmp254 * C3 * C4 + tmp255 * S3 * C4;
  double tmp316 = 960 * C3 * S4 * C5 + 960 * S3 * S5;
  double tmp317 = -960 * S4;
  double tmp318 = -tmp253 * S3;
  double tmp319 = 960 * C4 * S5;
  double tmp320 = 960 * C3 * S4 * S5 - 960 * S3 * C5;
  double tmp321 = tmp253 * C3 * C4 + tmp255 * S4;
  double tmp322 = 960 * S3 * S4 * C5 - 960 * C3 * S5;
  double tmp323 = 960 * C3 * C4;
  double tmp324 = -tmp253 * C3;
  double tmp325 = -tmp253 * S3 * C4 - tmp254 * S4;
  double tmp326 = 960 * C4 * C5;
  double tmp327 = 960 * S3 * S4 * S5 + 960 * C3 * C5;
  double tmp328 = 960 * S3 * C4;
  double tmp329 = tmp255 * C3 + tmp254 * S3;
  double tmp330 = tmp257 * C3 * C4 + tmp258 * S3 * C4 - tmp262 * S4;
  double tmp331 = -tmp254 * C4 * C5 + tmp253 * (S3 * S4 * C5 - C3 * S5);
  double tmp332 = tmp254 * C3 * C4 - tmp255 * S3 * C4;
  double tmp333 = tmp263 * C3 - tmp264 * S3;
  double tmp334 = -tmp255 * (S3 * S4 * S5 + C3 * C5) + tmp254 * (C3 * S4 * S5 - S3 * C5);
  double tmp335 = -tmp254 * C4 * S5 + tmp253 * (S3 * S4 * S5 + C3 * C5);
  double tmp336 = tmp264 * C3 * C4 + tmp263 * S3 * C4 - tmp260 * S4;
  double tmp337 = tmp255 * C4 * C5 - tmp253 * (C3 * S4 * C5 + S3 * S5);
  double tmp338 = tmp253 * S3 * C4 + tmp254 * S4;
  double tmp339 = tmp259 * C3 - tmp261 * S3;
  double tmp340 = tmp261 * C3 * C4 + tmp259 * S3 * C4 - tmp256 * S4;
  double tmp341 = -tmp255 * (S3 * S4 * C5 - C3 * S5) + tmp254 * (C3 * S4 * C5 + S3 * S5);
  double tmp342 = tmp255 * C4 * S5 - tmp253 * (C3 * S4 * S5 - S3 * C5);
  double tmp343 = -tmp253 * C3 * C4 - tmp255 * S4;
  double tmp344 = tmp258 * C3 - tmp257 * S3;
  double t1 = cos(q[4]);
  double t2 = t1 * tmp326;
  double t3 = cos(q[5]);
  double t5 = sin(q[3]);
  double t6 = sin(q[4]);
  double t7 = t6 * t5;
  double t9 = cos(q[3]);
  double t10 = sin(q[5]);
  double t12 = -t10 * t9 + t3 * t7;
  double t14 = t6 * t9;
  double t17 = t10 * t5 + t14 * t3;
  double t23 = t10 * t7 + t3 * t9;
  double t27 = t10 * t14 - t3 * t5;
  double t45 = t1 * tmp319;
  double t69 = t1 * tmp317;
  double t113 = t1 * tmp329;
  double t137 = t1 * tmp315;
  M[0] = t12 * tmp322 + t17 * tmp316 + t2 * t3;
  M[1] = t10 * t2 + t23 * tmp322 + t27 * tmp316;
  M[2] = t1 * t5 * tmp322 + t1 * t9 * tmp316 - t6 * tmp326;
  M[3] = tmp341;
  M[4] = -t5 * tmp331 + t9 * tmp337;
  M[5] = t1 * t5 * tmp337 + t1 * t9 * tmp331 - t6 * tmp341;
  M[6] = tmp282;
  M[7] = 0;
  M[8] = 0;
  M[9] = 0;
  M[10] = 0;
  M[11] = tmp283;
  M[12] = 0;
  M[13] = 0;
  M[14] = 0;
  M[15] = 0;
  M[16] = tmp284;
  M[17] = 0;
  M[18] = 0;
  M[19] = 0;
  M[20] = 0;
  M[21] = t12 * tmp327 + t17 * tmp320 + t3 * t45;
  M[22] = t10 * t45 + t23 * tmp327 + t27 * tmp320;
  M[23] = t1 * t5 * tmp327 + t1 * t9 * tmp320 - t6 * tmp319;
  M[24] = tmp334;
  M[25] = -t5 * tmp335 + t9 * tmp342;
  M[26] = t1 * t5 * tmp342 + t1 * t9 * tmp335 - t6 * tmp334;
  M[27] = tmp281;
  M[28] = 0;
  M[29] = 0;
  M[30] = 0;
  M[31] = 0;
  M[32] = tmp276;
  M[33] = 0;
  M[34] = 0;
  M[35] = 0;
  M[36] = 0;
  M[37] = tmp278;
  M[38] = 0;
  M[39] = 0;
  M[40] = 0;
  M[41] = 0;
  M[42] = t12 * tmp328 + t17 * tmp323 + t3 * t69;
  M[43] = t10 * t69 + t23 * tmp328 + t27 * tmp323;
  M[44] = t1 * t5 * tmp328 + t1 * t9 * tmp323 - t6 * tmp317;
  M[45] = tmp332;
  M[46] = -t5 * tmp338 + t9 * tmp343;
  M[47] = t1 * t5 * tmp343 + t1 * t9 * tmp338 - t6 * tmp332;
  M[48] = tmp279;
  M[49] = 0;
  M[50] = 0;
  M[51] = 0;
  M[52] = 0;
  M[53] = tmp277;
  M[54] = 0;
  M[55] = 0;
  M[56] = 0;
  M[57] = 0;
  M[58] = tmp280;
  M[59] = 0;
  M[60] = 0;
  M[61] = 0;
  M[62] = 0;
  M[63] = -t12 * tmp255 + t17 * tmp254;
  M[64] = -t23 * tmp255 + t27 * tmp254;
  M[65] = -t1 * t5 * tmp255 + t1 * t9 * tmp254;
  M[66] = tmp262;
  M[67] = -t5 * tmp256 + t9 * tmp260;
  M[68] = t1 * t5 * tmp260 + t1 * t9 * tmp256 - t6 * tmp262;
  M[69] = tmp88;
  M[70] = tmp26;
  M[71] = tmp51;
  M[72] = tmp24;
  M[73] = tmp52;
  M[74] = tmp176;
  M[75] = tmp172;
  M[76] = tmp178;
  M[77] = tmp182;
  M[78] = tmp174;
  M[79] = tmp271;
  M[80] = tmp272;
  M[81] = tmp267;
  M[82] = tmp270;
  M[83] = tmp268;
  M[84] = t113 * t3 + t12 * tmp318 + t17 * tmp324;
  M[85] = t10 * t113 + t23 * tmp318 + t27 * tmp324;
  M[86] = t1 * t5 * tmp318 + t1 * t9 * tmp324 - t6 * tmp329;
  M[87] = tmp344;
  M[88] = -t5 * tmp339 + t9 * tmp333;
  M[89] = t1 * t5 * tmp333 + t1 * t9 * tmp339 - t6 * tmp344;
  M[90] = tmp313;
  M[91] = tmp303;
  M[92] = tmp299;
  M[93] = tmp310;
  M[94] = tmp294;
  M[95] = tmp292;
  M[96] = tmp295;
  M[97] = tmp300;
  M[98] = tmp309;
  M[99] = tmp312;
  M[100] = tmp302;
  M[101] = tmp311;
  M[102] = tmp314;
  M[103] = tmp305;
  M[104] = tmp297;
  M[105] = t12 * tmp321 + t137 * t3 + t17 * tmp325;
  M[106] = t10 * t137 + t23 * tmp321 + t27 * tmp325;
  M[107] = t1 * t5 * tmp321 + t1 * t9 * tmp325 - t6 * tmp315;
  M[108] = tmp330;
  M[109] = -t5 * tmp340 + t9 * tmp336;
  M[110] = t1 * t5 * tmp336 + t1 * t9 * tmp340 - t6 * tmp330;
  M[111] = tmp291;
  M[112] = tmp301;
  M[113] = tmp293;
  M[114] = tmp288;
  M[115] = tmp298;
  M[116] = tmp286;
  M[117] = tmp307;
  M[118] = tmp308;
  M[119] = tmp296;
  M[120] = tmp287;
  M[121] = tmp289;
  M[122] = tmp306;
  M[123] = tmp290;
  M[124] = tmp304;
  M[125] = tmp285;
  M[126] = tmp282;
  M[127] = tmp281;
  M[128] = tmp279;
  M[129] = tmp88;
  M[130] = tmp313;
  M[131] = tmp291;
  M[132] = tmp47;
  M[133] = tmp26;
  M[134] = tmp51;
  M[135] = tmp24;
  M[136] = tmp52;
  M[137] = 0;
  M[138] = 0;
  M[139] = 0;
  M[140] = 0;
  M[141] = 0;
  M[142] = 0;
  M[143] = 0;
  M[144] = 0;
  M[145] = 0;
  M[146] = 0;
  M[147] = 0;
  M[148] = 0;
  M[149] = 0;
  M[150] = tmp26;
  M[151] = tmp303;
  M[152] = tmp301;
  M[153] = tmp26;
  M[154] = tmp8;
  M[155] = 0;
  M[156] = 0;
  M[157] = 0;
  M[158] = 0;
  M[159] = 0;
  M[160] = 0;
  M[161] = 0;
  M[162] = 0;
  M[163] = 0;
  M[164] = 0;
  M[165] = 0;
  M[166] = 0;
  M[167] = 0;
  M[168] = 0;
  M[169] = 0;
  M[170] = 0;
  M[171] = tmp51;
  M[172] = tmp299;
  M[173] = tmp293;
  M[174] = tmp51;
  M[175] = 0;
  M[176] = tmp34;
  M[177] = 0;
  M[178] = 0;
  M[179] = 0;
  M[180] = 0;
  M[181] = 0;
  M[182] = 0;
  M[183] = 0;
  M[184] = 0;
  M[185] = 0;
  M[186] = 0;
  M[187] = 0;
  M[188] = 0;
  M[189] = 0;
  M[190] = 0;
  M[191] = 0;
  M[192] = tmp24;
  M[193] = tmp310;
  M[194] = tmp288;
  M[195] = tmp24;
  M[196] = 0;
  M[197] = 0;
  M[198] = 1500;
  M[199] = 0;
  M[200] = 0;
  M[201] = 0;
  M[202] = 0;
  M[203] = 0;
  M[204] = 0;
  M[205] = 0;
  M[206] = 0;
  M[207] = 0;
  M[208] = 0;
  M[209] = 0;
  M[210] = 0;
  M[211] = 0;
  M[212] = 0;
  M[213] = tmp52;
  M[214] = tmp294;
  M[215] = tmp298;
  M[216] = tmp52;
  M[217] = 0;
  M[218] = 0;
  M[219] = 0;
  M[220] = 1500;
  M[221] = 0;
  M[222] = 0;
  M[223] = 0;
  M[224] = 0;
  M[225] = 0;
  M[226] = 0;
  M[227] = 0;
  M[228] = 0;
  M[229] = 0;
  M[230] = 0;
  M[231] = tmp283;
  M[232] = tmp276;
  M[233] = tmp277;
  M[234] = tmp176;
  M[235] = tmp292;
  M[236] = tmp286;
  M[237] = 0;
  M[238] = 0;
  M[239] = 0;
  M[240] = 0;
  M[241] = 0;
  M[242] = tmp135;
  M[243] = tmp114;
  M[244] = tmp140;
  M[245] = tmp113;
  M[246] = tmp141;
  M[247] = 0;
  M[248] = 0;
  M[249] = 0;
  M[250] = 0;
  M[251] = 0;
  M[252] = 0;
  M[253] = 0;
  M[254] = 0;
  M[255] = tmp172;
  M[256] = tmp295;
  M[257] = tmp307;
  M[258] = 0;
  M[259] = 0;
  M[260] = 0;
  M[261] = 0;
  M[262] = 0;
  M[263] = tmp114;
  M[264] = tmp97;
  M[265] = 0;
  M[266] = 0;
  M[267] = 0;
  M[268] = 0;
  M[269] = 0;
  M[270] = 0;
  M[271] = 0;
  M[272] = 0;
  M[273] = 0;
  M[274] = 0;
  M[275] = 0;
  M[276] = tmp178;
  M[277] = tmp300;
  M[278] = tmp308;
  M[279] = 0;
  M[280] = 0;
  M[281] = 0;
  M[282] = 0;
  M[283] = 0;
  M[284] = tmp140;
  M[285] = 0;
  M[286] = tmp123;
  M[287] = 0;
  M[288] = 0;
  M[289] = 0;
  M[290] = 0;
  M[291] = 0;
  M[292] = 0;
  M[293] = 0;
  M[294] = 0;
  M[295] = 0;
  M[296] = 0;
  M[297] = tmp182;
  M[298] = tmp309;
  M[299] = tmp296;
  M[300] = 0;
  M[301] = 0;
  M[302] = 0;
  M[303] = 0;
  M[304] = 0;
  M[305] = tmp113;
  M[306] = 0;
  M[307] = 0;
  M[308] = 1500;
  M[309] = 0;
  M[310] = 0;
  M[311] = 0;
  M[312] = 0;
  M[313] = 0;
  M[314] = 0;
  M[315] = 0;
  M[316] = 0;
  M[317] = 0;
  M[318] = tmp174;
  M[319] = tmp312;
  M[320] = tmp287;
  M[321] = 0;
  M[322] = 0;
  M[323] = 0;
  M[324] = 0;
  M[325] = 0;
  M[326] = tmp141;
  M[327] = 0;
  M[328] = 0;
  M[329] = 0;
  M[330] = 1500;
  M[331] = 0;
  M[332] = 0;
  M[333] = 0;
  M[334] = 0;
  M[335] = 0;
  M[336] = tmp284;
  M[337] = tmp278;
  M[338] = tmp280;
  M[339] = tmp271;
  M[340] = tmp302;
  M[341] = tmp289;
  M[342] = 0;
  M[343] = 0;
  M[344] = 0;
  M[345] = 0;
  M[346] = 0;
  M[347] = 0;
  M[348] = 0;
  M[349] = 0;
  M[350] = 0;
  M[351] = 0;
  M[352] = tmp228;
  M[353] = tmp208;
  M[354] = tmp233;
  M[355] = tmp205;
  M[356] = tmp235;
  M[357] = 0;
  M[358] = 0;
  M[359] = 0;
  M[360] = tmp272;
  M[361] = tmp311;
  M[362] = tmp306;
  M[363] = 0;
  M[364] = 0;
  M[365] = 0;
  M[366] = 0;
  M[367] = 0;
  M[368] = 0;
  M[369] = 0;
  M[370] = 0;
  M[371] = 0;
  M[372] = 0;
  M[373] = tmp208;
  M[374] = tmp190;
  M[375] = 0;
  M[376] = 0;
  M[377] = 0;
  M[378] = 0;
  M[379] = 0;
  M[380] = 0;
  M[381] = tmp267;
  M[382] = tmp314;
  M[383] = tmp290;
  M[384] = 0;
  M[385] = 0;
  M[386] = 0;
  M[387] = 0;
  M[388] = 0;
  M[389] = 0;
  M[390] = 0;
  M[391] = 0;
  M[392] = 0;
  M[393] = 0;
  M[394] = tmp233;
  M[395] = 0;
  M[396] = tmp216;
  M[397] = 0;
  M[398] = 0;
  M[399] = 0;
  M[400] = 0;
  M[401] = 0;
  M[402] = tmp270;
  M[403] = tmp305;
  M[404] = tmp304;
  M[405] = 0;
  M[406] = 0;
  M[407] = 0;
  M[408] = 0;
  M[409] = 0;
  M[410] = 0;
  M[411] = 0;
  M[412] = 0;
  M[413] = 0;
  M[414] = 0;
  M[415] = tmp205;
  M[416] = 0;
  M[417] = 0;
  M[418] = 1500;
  M[419] = 0;
  M[420] = 0;
  M[421] = 0;
  M[422] = 0;
  M[423] = tmp268;
  M[424] = tmp297;
  M[425] = tmp285;
  M[426] = 0;
  M[427] = 0;
  M[428] = 0;
  M[429] = 0;
  M[430] = 0;
  M[431] = 0;
  M[432] = 0;
  M[433] = 0;
  M[434] = 0;
  M[435] = 0;
  M[436] = tmp235;
  M[437] = 0;
  M[438] = 0;
  M[439] = 0;
  M[440] = 1500;
}
