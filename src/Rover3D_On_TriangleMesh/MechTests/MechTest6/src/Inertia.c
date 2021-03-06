#include <math.h>
#include "LagrangianModel.h"

void Inertia(M, q)
double M[441];
double q[21];
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
  double tmp1 = 3150 * C9;
  double tmp2 = -3150 * S9;
  double tmp3 = 3150 * S9;
  double tmp4 = 3150 * C9;
  double tmp5 = 3276 + C9 * tmp1 - S9 * tmp2;
  double tmp6 = S9 * tmp1 + C9 * tmp2;
  double tmp7 = C9 * tmp3 - S9 * tmp4;
  double tmp8 = 27 + S9 * tmp3 + C9 * tmp4;
  double tmp9 = 9576 * C7;
  double tmp10 = -tmp6 * S7;
  double tmp11 = tmp5 * C7;
  double tmp12 = 9576 * S7;
  double tmp13 = -tmp5 * S7;
  double tmp14 = tmp6 * C7;
  double tmp15 = 120 - S7 * tmp13 + C7 * tmp9;
  double tmp16 = -S7 * tmp7 - 11130;
  double tmp17 = tmp10 - 11130;
  double tmp18 = 0.234845e6 / 0.3e1 + C7 * tmp11 + S7 * tmp12;
  double tmp19 = -S7 * tmp11 + C7 * tmp12;
  double tmp20 = C7 * tmp13 + S7 * tmp9;
  double tmp21 = C7 * tmp7;
  double tmp22 = 0.234845e6 / 0.3e1 + tmp8;
  double tmp23 = 6300 * S7;
  double tmp24 = C7 * tmp7;
  double tmp25 = -S7 * tmp7;
  double tmp26 = 6300 * C7;
  double tmp27 = 3150 * C10;
  double tmp28 = -3150 * S10;
  double tmp29 = 3150 * S10;
  double tmp30 = 3150 * C10;
  double tmp31 = 3276 + C10 * tmp27 - S10 * tmp28;
  double tmp32 = S10 * tmp27 + C10 * tmp28;
  double tmp33 = C10 * tmp29 - S10 * tmp30;
  double tmp34 = 27 + S10 * tmp29 + C10 * tmp30;
  double tmp35 = 9576 * C8;
  double tmp36 = -tmp32 * S8;
  double tmp37 = tmp31 * C8;
  double tmp38 = 9576 * S8;
  double tmp39 = -tmp31 * S8;
  double tmp40 = tmp32 * C8;
  double tmp41 = tmp15 - S8 * tmp39 + C8 * tmp35;
  double tmp42 = tmp16 - S8 * tmp33 + 11130;
  double tmp43 = tmp17 + tmp36 + 11130;
  double tmp44 = tmp18 + C8 * tmp37 + S8 * tmp38 + 56180;
  double tmp45 = tmp19 - S8 * tmp37 + C8 * tmp38;
  double tmp46 = tmp20 + C8 * tmp39 + S8 * tmp35;
  double tmp47 = tmp14 + tmp40;
  double tmp48 = tmp21 + C8 * tmp33;
  double tmp49 = tmp22 + tmp34 + 56180;
  double tmp50 = 6300 * S8;
  double tmp51 = C8 * tmp33;
  double tmp52 = 6300 * C8;
  double tmp53 = -S8 * tmp33;
  double tmp54 = -420 * C6;
  double tmp55 = -420 * S6;
  double tmp56 = 420 * S6;
  double tmp57 = -420 * C6;
  double tmp58 = 10 * tmp54;
  double tmp59 = -10 * tmp55;
  double tmp60 = 10 * tmp54;
  double tmp61 = 62 * tmp55;
  double tmp62 = 62 * tmp54;
  double tmp63 = tmp42 * S6 + tmp41 * C6;
  double tmp64 = tmp42 * C6 - tmp41 * S6;
  double tmp65 = tmp49 * S6 + tmp43 * C6;
  double tmp66 = tmp48 * S6 + tmp46 * C6;
  double tmp67 = tmp48 * C6 - tmp46 * S6;
  double tmp68 = tmp49 * C6 - tmp43 * S6;
  double tmp69 = tmp54 - 600;
  double tmp70 = 0.3509920e7 / 0.3e1 + S6 * tmp65 + C6 * tmp63 - 2 * tmp58;
  double tmp71 = S6 * tmp68 + C6 * tmp64 - tmp59;
  double tmp72 = C6 * tmp65 - S6 * tmp63 - tmp59;
  double tmp73 = 0.2048000e7 / 0.3e1 + tmp44 - 2 * tmp60;
  double tmp74 = S6 * tmp47 + C6 * tmp45 - tmp61;
  double tmp75 = tmp66 - tmp61;
  double tmp76 = C6 * tmp47 - S6 * tmp45 + 37200 - tmp62;
  double tmp77 = tmp67 + 37200 - tmp62;
  double tmp78 = 0.4961920e7 / 0.3e1 + C6 * tmp68 - S6 * tmp64;
  double tmp79 = C6 * tmp47 - S6 * tmp45 - 62 * tmp57;
  double tmp80 = C6 * tmp8 - S6 * tmp25;
  double tmp81 = C6 * tmp34 - S6 * tmp53;
  double tmp82 = S6 * tmp8 + C6 * tmp25;
  double tmp83 = C6 * tmp52;
  double tmp84 = -S6 * tmp26;
  double tmp85 = -S6 * tmp52;
  double tmp86 = S6 * tmp47 + C6 * tmp45 + 62 * tmp56;
  double tmp87 = tmp44 - 10 * tmp57;
  double tmp88 = S6 * tmp34 + C6 * tmp53;
  double tmp89 = C6 * tmp26;
  double tmp90 = 3150 * C14;
  double tmp91 = -3150 * S14;
  double tmp92 = 3150 * S14;
  double tmp93 = 3150 * C14;
  double tmp94 = 3276 + C14 * tmp90 - S14 * tmp91;
  double tmp95 = S14 * tmp90 + C14 * tmp91;
  double tmp96 = C14 * tmp92 - S14 * tmp93;
  double tmp97 = 27 + S14 * tmp92 + C14 * tmp93;
  double tmp98 = 9576 * C12;
  double tmp99 = -tmp95 * S12;
  double tmp100 = tmp94 * C12;
  double tmp101 = 9576 * S12;
  double tmp102 = -tmp94 * S12;
  double tmp103 = tmp95 * C12;
  double tmp104 = 0.78680e5 / 0.3e1 - S12 * tmp102 + C12 * tmp98;
  double tmp105 = -S12 * tmp96;
  double tmp106 = 120 + C12 * tmp100 + S12 * tmp101;
  double tmp107 = -S12 * tmp100 + C12 * tmp101;
  double tmp108 = C12 * tmp102 + S12 * tmp98;
  double tmp109 = tmp103 + 6300;
  double tmp110 = C12 * tmp96 + 6300;
  double tmp111 = 0.78680e5 / 0.3e1 + tmp97;
  double tmp112 = -S12 * tmp96;
  double tmp113 = 6300 * C12;
  double tmp114 = C12 * tmp96;
  double tmp115 = 6300 * S12;
  double tmp116 = 3150 * C15;
  double tmp117 = -3150 * S15;
  double tmp118 = 3150 * S15;
  double tmp119 = 3150 * C15;
  double tmp120 = 3276 + C15 * tmp116 - S15 * tmp117;
  double tmp121 = S15 * tmp116 + C15 * tmp117;
  double tmp122 = C15 * tmp118 - S15 * tmp119;
  double tmp123 = 27 + S15 * tmp118 + C15 * tmp119;
  double tmp124 = 9576 * C13;
  double tmp125 = -tmp121 * S13;
  double tmp126 = tmp120 * C13;
  double tmp127 = 9576 * S13;
  double tmp128 = -tmp120 * S13;
  double tmp129 = tmp121 * C13;
  double tmp130 = tmp104 - S13 * tmp128 + C13 * tmp124 + 18000;
  double tmp131 = tmp105 - S13 * tmp122;
  double tmp132 = tmp99 + tmp125;
  double tmp133 = tmp106 + C13 * tmp126 + S13 * tmp127;
  double tmp134 = tmp107 - S13 * tmp126 + C13 * tmp127;
  double tmp135 = tmp108 + C13 * tmp128 + S13 * tmp124;
  double tmp136 = tmp109 + tmp129 - 6300;
  double tmp137 = tmp110 + C13 * tmp122 - 6300;
  double tmp138 = tmp111 + tmp123 + 18000;
  double tmp139 = -S13 * tmp122;
  double tmp140 = 6300 * C13;
  double tmp141 = 6300 * S13;
  double tmp142 = C13 * tmp122;
  double tmp143 = 420 * S11;
  double tmp144 = -420 * C11;
  double tmp145 = 420 * C11;
  double tmp146 = 420 * S11;
  double tmp147 = 10 * tmp144 + 40 * tmp143;
  double tmp148 = -53 * tmp144;
  double tmp149 = 10 * tmp144;
  double tmp150 = -53 * tmp143;
  double tmp151 = -40 * tmp144;
  double tmp152 = -10 * tmp143;
  double tmp153 = 40 * tmp143;
  double tmp154 = tmp134 * S11 + tmp131 * C11;
  double tmp155 = tmp133 * C11 - tmp137 * S11;
  double tmp156 = tmp134 * C11 - tmp131 * S11;
  double tmp157 = tmp136 * C11 - tmp138 * S11;
  double tmp158 = tmp133 * S11 + tmp137 * C11;
  double tmp159 = tmp136 * S11 + tmp138 * C11;
  double tmp160 = 1320 + tmp143;
  double tmp161 = tmp69 + tmp144 - 600;
  double tmp162 = tmp55 - 3180;
  double tmp163 = tmp70 + tmp130 + 102000 - 2 * tmp147;
  double tmp164 = tmp71 + tmp154 - 31800 - tmp148;
  double tmp165 = tmp72 + S11 * tmp135 + C11 * tmp132 - 31800 - tmp148;
  double tmp166 = tmp73 + C11 * tmp155 - S11 * tmp157 + 174540 - 2 * tmp149;
  double tmp167 = tmp74 + tmp156 - 127200 - tmp150;
  double tmp168 = tmp75 + C11 * tmp135 - S11 * tmp132 - 127200 - tmp150;
  double tmp169 = tmp76 + S11 * tmp155 + C11 * tmp157 - 24000 - tmp151 - tmp152;
  double tmp170 = tmp77 + C11 * tmp158 - S11 * tmp159 - 24000 - tmp152 - tmp151;
  double tmp171 = tmp78 + S11 * tmp158 + C11 * tmp159 + 264540 - 2 * tmp153;
  double tmp172 = S11 * tmp114 + C11 * tmp97;
  double tmp173 = S11 * tmp141;
  double tmp174 = S11 * tmp142 + C11 * tmp123;
  double tmp175 = S11 * tmp115;
  double tmp176 = tmp130 + 10 * tmp145 - 40 * tmp146;
  double tmp177 = C11 * tmp135 - S11 * tmp132 + 53 * tmp146;
  double tmp178 = C11 * tmp141;
  double tmp179 = C11 * tmp114 - S11 * tmp97;
  double tmp180 = S11 * tmp135 + C11 * tmp132 - 53 * tmp145;
  double tmp181 = C11 * tmp115;
  double tmp182 = C11 * tmp142 - S11 * tmp123;
  double tmp183 = 3150 * C19;
  double tmp184 = -3150 * S19;
  double tmp185 = 3150 * S19;
  double tmp186 = 3150 * C19;
  double tmp187 = 3276 + C19 * tmp183 - S19 * tmp184;
  double tmp188 = S19 * tmp183 + C19 * tmp184;
  double tmp189 = C19 * tmp185 - S19 * tmp186;
  double tmp190 = 27 + S19 * tmp185 + C19 * tmp186;
  double tmp191 = 9576 * C17;
  double tmp192 = -tmp188 * S17;
  double tmp193 = tmp187 * C17;
  double tmp194 = 9576 * S17;
  double tmp195 = -tmp187 * S17;
  double tmp196 = tmp188 * C17;
  double tmp197 = 0.78680e5 / 0.3e1 - S17 * tmp195 + C17 * tmp191;
  double tmp198 = -S17 * tmp189;
  double tmp199 = 120 + C17 * tmp193 + S17 * tmp194;
  double tmp200 = -S17 * tmp193 + C17 * tmp194;
  double tmp201 = C17 * tmp195 + S17 * tmp191;
  double tmp202 = tmp196 + 6300;
  double tmp203 = C17 * tmp189 + 6300;
  double tmp204 = 0.78680e5 / 0.3e1 + tmp190;
  double tmp205 = -S17 * tmp189;
  double tmp206 = 6300 * C17;
  double tmp207 = C17 * tmp189;
  double tmp208 = 6300 * S17;
  double tmp209 = 3150 * C20;
  double tmp210 = -3150 * S20;
  double tmp211 = 3150 * S20;
  double tmp212 = 3150 * C20;
  double tmp213 = 3276 + C20 * tmp209 - S20 * tmp210;
  double tmp214 = S20 * tmp209 + C20 * tmp210;
  double tmp215 = C20 * tmp211 - S20 * tmp212;
  double tmp216 = 27 + S20 * tmp211 + C20 * tmp212;
  double tmp217 = 9576 * C18;
  double tmp218 = -tmp214 * S18;
  double tmp219 = tmp213 * C18;
  double tmp220 = 9576 * S18;
  double tmp221 = -tmp213 * S18;
  double tmp222 = tmp214 * C18;
  double tmp223 = tmp197 - S18 * tmp221 + C18 * tmp217 + 18000;
  double tmp224 = tmp198 - S18 * tmp215;
  double tmp225 = tmp192 + tmp218;
  double tmp226 = tmp199 + C18 * tmp219 + S18 * tmp220;
  double tmp227 = tmp200 - S18 * tmp219 + C18 * tmp220;
  double tmp228 = tmp201 + C18 * tmp221 + S18 * tmp217;
  double tmp229 = tmp202 + tmp222 - 6300;
  double tmp230 = tmp203 + C18 * tmp215 - 6300;
  double tmp231 = tmp204 + tmp216 + 18000;
  double tmp232 = C18 * tmp215;
  double tmp233 = 6300 * C18;
  double tmp234 = -S18 * tmp215;
  double tmp235 = 6300 * S18;
  double tmp236 = 420 * S16;
  double tmp237 = -420 * C16;
  double tmp238 = 420 * C16;
  double tmp239 = 420 * S16;
  double tmp240 = 10 * tmp237 + 40 * tmp236;
  double tmp241 = 53 * tmp237;
  double tmp242 = 10 * tmp237;
  double tmp243 = 53 * tmp236;
  double tmp244 = -40 * tmp237;
  double tmp245 = -10 * tmp236;
  double tmp246 = 40 * tmp236;
  double tmp247 = tmp227 * S16 + tmp224 * C16;
  double tmp248 = tmp226 * C16 - tmp230 * S16;
  double tmp249 = tmp227 * C16 - tmp224 * S16;
  double tmp250 = tmp229 * C16 - tmp231 * S16;
  double tmp251 = tmp226 * S16 + tmp230 * C16;
  double tmp252 = tmp229 * S16 + tmp231 * C16;
  double tmp253 = tmp160 + tmp236 - 2400;
  double tmp254 = tmp161 + tmp237 - 600;
  double tmp255 = tmp162 + 3180;
  double tmp256 = tmp163 + tmp223 + 102000 - 2 * tmp240;
  double tmp257 = tmp164 + tmp247 + 31800 - tmp241;
  double tmp258 = tmp165 + S16 * tmp228 + C16 * tmp225 + 31800 - tmp241;
  double tmp259 = tmp166 + C16 * tmp248 - S16 * tmp250 + 174540 - 2 * tmp242;
  double tmp260 = tmp167 + tmp249 + 127200 - tmp243;
  double tmp261 = tmp168 + C16 * tmp228 - S16 * tmp225 + 127200 - tmp243;
  double tmp262 = tmp169 + S16 * tmp248 + C16 * tmp250 - 24000 - tmp244 - tmp245;
  double tmp263 = tmp170 + C16 * tmp251 - S16 * tmp252 - 24000 - tmp245 - tmp244;
  double tmp264 = tmp171 + S16 * tmp251 + C16 * tmp252 + 264540 - 2 * tmp246;
  double tmp265 = C16 * tmp232 - S16 * tmp216;
  double tmp266 = S16 * tmp208;
  double tmp267 = S16 * tmp235;
  double tmp268 = C16 * tmp207 - S16 * tmp190;
  double tmp269 = C16 * tmp208;
  double tmp270 = C16 * tmp228 - S16 * tmp225 - 53 * tmp239;
  double tmp271 = C16 * tmp235;
  double tmp272 = S16 * tmp228 + C16 * tmp225 + 53 * tmp238;
  double tmp273 = S16 * tmp232 + C16 * tmp216;
  double tmp274 = tmp223 + 10 * tmp238 - 40 * tmp239;
  double tmp275 = S16 * tmp207 + C16 * tmp190;
  double tmp276 = tmp56 * S3 * C4 + tmp57 * C3 * C4;
  double tmp277 = tmp145 * C4 * C5 + tmp146 * (S3 * S4 * C5 - C3 * S5);
  double tmp278 = tmp56 * (S3 * S4 * C5 - C3 * S5) + tmp57 * (C3 * S4 * C5 + S3 * S5);
  double tmp279 = tmp238 * C4 * C5 + tmp239 * (S3 * S4 * C5 - C3 * S5);
  double tmp280 = tmp56 * (S3 * S4 * S5 + C3 * C5) + tmp57 * (C3 * S4 * S5 - S3 * C5);
  double tmp281 = -tmp145 * S4 + tmp146 * S3 * C4;
  double tmp282 = tmp238 * C4 * S5 + tmp239 * (S3 * S4 * S5 + C3 * C5);
  double tmp283 = -tmp238 * S4 + tmp239 * S3 * C4;
  double tmp284 = tmp145 * C4 * S5 + tmp146 * (S3 * S4 * S5 + C3 * C5);
  double tmp285 = -tmp181 * S4 + tmp175 * S3 * C4 + tmp113 * C3 * C4;
  double tmp286 = tmp272 * C3 - tmp274 * S3;
  double tmp287 = tmp81 * C3 - tmp88 * S3;
  double tmp288 = -tmp87 * S4 + tmp79 * S3 * C4 + tmp86 * C3 * C4;
  double tmp289 = -tmp51 * S4 + tmp81 * S3 * C4 + tmp88 * C3 * C4;
  double tmp290 = -tmp179 * S4 + tmp172 * S3 * C4 + tmp112 * C3 * C4;
  double tmp291 = -tmp271 * S4 + tmp267 * S3 * C4 + tmp233 * C3 * C4;
  double tmp292 = -tmp182 * S4 + tmp174 * S3 * C4 + tmp139 * C3 * C4;
  double tmp293 = tmp266 * C3 - tmp206 * S3;
  double tmp294 = tmp174 * C3 - tmp139 * S3;
  double tmp295 = tmp173 * C3 - tmp140 * S3;
  double tmp296 = tmp267 * C3 - tmp233 * S3;
  double tmp297 = tmp85 * C3 - tmp83 * S3;
  double tmp298 = -tmp270 * S4 + tmp272 * S3 * C4 + tmp274 * C3 * C4;
  double tmp299 = -tmp268 * S4 + tmp275 * S3 * C4 + tmp205 * C3 * C4;
  double tmp300 = -tmp24 * S4 + tmp80 * S3 * C4 + tmp82 * C3 * C4;
  double tmp301 = tmp79 * C3 - tmp86 * S3;
  double tmp302 = -tmp265 * S4 + tmp273 * S3 * C4 + tmp234 * C3 * C4;
  double tmp303 = -tmp177 * S4 + tmp180 * S3 * C4 + tmp176 * C3 * C4;
  double tmp304 = tmp273 * C3 - tmp234 * S3;
  double tmp305 = tmp84 * C3 - tmp89 * S3;
  double tmp306 = -tmp50 * S4 + tmp85 * S3 * C4 + tmp83 * C3 * C4;
  double tmp307 = tmp275 * C3 - tmp205 * S3;
  double tmp308 = -tmp269 * S4 + tmp266 * S3 * C4 + tmp206 * C3 * C4;
  double tmp309 = tmp80 * C3 - tmp82 * S3;
  double tmp310 = -tmp23 * S4 + tmp84 * S3 * C4 + tmp89 * C3 * C4;
  double tmp311 = tmp172 * C3 - tmp112 * S3;
  double tmp312 = -tmp178 * S4 + tmp173 * S3 * C4 + tmp140 * C3 * C4;
  double tmp313 = tmp180 * C3 - tmp176 * S3;
  double tmp314 = tmp175 * C3 - tmp113 * S3;
  double tmp315 = 880 * C3 * C4;
  double tmp316 = tmp255 * C3 + tmp254 * S3;
  double tmp317 = -tmp254 * S4 - tmp253 * S3 * C4;
  double tmp318 = tmp255 * S3 * C4 - tmp254 * C3 * C4;
  double tmp319 = 880 * C3 * S4 * S5 - 880 * S3 * C5;
  double tmp320 = 880 * S3 * C4;
  double tmp321 = 880 * C4 * C5;
  double tmp322 = 880 * C3 * S4 * C5 + 880 * S3 * S5;
  double tmp323 = -tmp253 * C3;
  double tmp324 = -880 * S4;
  double tmp325 = -tmp253 * S3;
  double tmp326 = tmp255 * S4 + tmp253 * C3 * C4;
  double tmp327 = 880 * S3 * S4 * C5 - 880 * C3 * S5;
  double tmp328 = 880 * C4 * S5;
  double tmp329 = 880 * S3 * S4 * S5 + 880 * C3 * C5;
  double tmp330 = tmp254 * S4 + tmp253 * S3 * C4;
  double tmp331 = tmp263 * C3 - tmp261 * S3;
  double tmp332 = -tmp260 * S4 + tmp257 * S3 * C4 + tmp256 * C3 * C4;
  double tmp333 = -tmp259 * S4 + tmp263 * S3 * C4 + tmp261 * C3 * C4;
  double tmp334 = -tmp254 * C4 * S5 + tmp253 * (S3 * S4 * S5 + C3 * C5);
  double tmp335 = -tmp255 * S4 - tmp253 * C3 * C4;
  double tmp336 = -tmp255 * (S3 * S4 * C5 - C3 * S5) + tmp254 * (C3 * S4 * C5 + S3 * S5);
  double tmp337 = -tmp254 * C4 * C5 + tmp253 * (S3 * S4 * C5 - C3 * S5);
  double tmp338 = tmp257 * C3 - tmp256 * S3;
  double tmp339 = -tmp255 * S3 * C4 + tmp254 * C3 * C4;
  double tmp340 = tmp264 * C3 - tmp258 * S3;
  double tmp341 = -tmp262 * S4 + tmp264 * S3 * C4 + tmp258 * C3 * C4;
  double tmp342 = tmp255 * C4 * C5 - tmp253 * (C3 * S4 * C5 + S3 * S5);
  double tmp343 = -tmp255 * (S3 * S4 * S5 + C3 * C5) + tmp254 * (C3 * S4 * S5 - S3 * C5);
  double tmp344 = tmp255 * C4 * S5 - tmp253 * (C3 * S4 * S5 - S3 * C5);
  double t1 = cos(q[4]);
  double t2 = tmp321 * t1;
  double t3 = cos(q[5]);
  double t5 = sin(q[3]);
  double t6 = sin(q[4]);
  double t7 = t5 * t6;
  double t9 = cos(q[3]);
  double t10 = sin(q[5]);
  double t12 = t7 * t3 - t9 * t10;
  double t14 = t9 * t6;
  double t17 = t14 * t3 + t5 * t10;
  double t23 = t7 * t10 + t9 * t3;
  double t27 = t10 * t14 - t5 * t3;
  double t45 = tmp328 * t1;
  double t69 = tmp324 * t1;
  double t113 = tmp316 * t1;
  double t137 = tmp318 * t1;
  M[0] = t2 * t3 + tmp327 * t12 + tmp322 * t17;
  M[1] = t2 * t10 + tmp327 * t23 + tmp322 * t27;
  M[2] = -tmp321 * t6 + tmp327 * t5 * t1 + tmp322 * t9 * t1;
  M[3] = tmp336;
  M[4] = tmp342 * t9 - tmp337 * t5;
  M[5] = -tmp336 * t6 + tmp342 * t5 * t1 + tmp337 * t9 * t1;
  M[6] = tmp278;
  M[7] = 0;
  M[8] = 0;
  M[9] = 0;
  M[10] = 0;
  M[11] = tmp277;
  M[12] = 0;
  M[13] = 0;
  M[14] = 0;
  M[15] = 0;
  M[16] = tmp279;
  M[17] = 0;
  M[18] = 0;
  M[19] = 0;
  M[20] = 0;
  M[21] = t45 * t3 + tmp329 * t12 + tmp319 * t17;
  M[22] = t45 * t10 + tmp329 * t23 + tmp319 * t27;
  M[23] = -tmp328 * t6 + tmp329 * t5 * t1 + tmp319 * t9 * t1;
  M[24] = tmp343;
  M[25] = tmp344 * t9 - tmp334 * t5;
  M[26] = -tmp343 * t6 + tmp344 * t5 * t1 + tmp334 * t9 * t1;
  M[27] = tmp280;
  M[28] = 0;
  M[29] = 0;
  M[30] = 0;
  M[31] = 0;
  M[32] = tmp284;
  M[33] = 0;
  M[34] = 0;
  M[35] = 0;
  M[36] = 0;
  M[37] = tmp282;
  M[38] = 0;
  M[39] = 0;
  M[40] = 0;
  M[41] = 0;
  M[42] = t69 * t3 + tmp320 * t12 + tmp315 * t17;
  M[43] = t69 * t10 + tmp320 * t23 + tmp315 * t27;
  M[44] = -tmp324 * t6 + tmp320 * t5 * t1 + tmp315 * t9 * t1;
  M[45] = tmp339;
  M[46] = tmp335 * t9 - tmp330 * t5;
  M[47] = -tmp339 * t6 + tmp335 * t5 * t1 + tmp330 * t9 * t1;
  M[48] = tmp276;
  M[49] = 0;
  M[50] = 0;
  M[51] = 0;
  M[52] = 0;
  M[53] = tmp281;
  M[54] = 0;
  M[55] = 0;
  M[56] = 0;
  M[57] = 0;
  M[58] = tmp283;
  M[59] = 0;
  M[60] = 0;
  M[61] = 0;
  M[62] = 0;
  M[63] = -tmp255 * t12 + tmp254 * t17;
  M[64] = -tmp255 * t23 + tmp254 * t27;
  M[65] = -tmp255 * t5 * t1 + tmp254 * t9 * t1;
  M[66] = tmp259;
  M[67] = tmp262 * t9 - tmp260 * t5;
  M[68] = -tmp259 * t6 + tmp262 * t5 * t1 + tmp260 * t9 * t1;
  M[69] = tmp87;
  M[70] = tmp24;
  M[71] = tmp51;
  M[72] = tmp23;
  M[73] = tmp50;
  M[74] = tmp177;
  M[75] = tmp179;
  M[76] = tmp182;
  M[77] = tmp181;
  M[78] = tmp178;
  M[79] = tmp270;
  M[80] = tmp268;
  M[81] = tmp265;
  M[82] = tmp269;
  M[83] = tmp271;
  M[84] = t113 * t3 + tmp325 * t12 + tmp323 * t17;
  M[85] = t113 * t10 + tmp325 * t23 + tmp323 * t27;
  M[86] = -tmp316 * t6 + tmp325 * t5 * t1 + tmp323 * t9 * t1;
  M[87] = tmp331;
  M[88] = tmp340 * t9 - tmp338 * t5;
  M[89] = -tmp331 * t6 + tmp340 * t5 * t1 + tmp338 * t9 * t1;
  M[90] = tmp301;
  M[91] = tmp309;
  M[92] = tmp287;
  M[93] = tmp305;
  M[94] = tmp297;
  M[95] = tmp313;
  M[96] = tmp311;
  M[97] = tmp294;
  M[98] = tmp314;
  M[99] = tmp295;
  M[100] = tmp286;
  M[101] = tmp307;
  M[102] = tmp304;
  M[103] = tmp293;
  M[104] = tmp296;
  M[105] = t137 * t3 + tmp326 * t12 + tmp317 * t17;
  M[106] = t137 * t10 + tmp326 * t23 + tmp317 * t27;
  M[107] = -tmp318 * t6 + tmp326 * t5 * t1 + tmp317 * t9 * t1;
  M[108] = tmp333;
  M[109] = tmp341 * t9 - tmp332 * t5;
  M[110] = -tmp333 * t6 + tmp341 * t5 * t1 + tmp332 * t9 * t1;
  M[111] = tmp288;
  M[112] = tmp300;
  M[113] = tmp289;
  M[114] = tmp310;
  M[115] = tmp306;
  M[116] = tmp303;
  M[117] = tmp290;
  M[118] = tmp292;
  M[119] = tmp285;
  M[120] = tmp312;
  M[121] = tmp298;
  M[122] = tmp299;
  M[123] = tmp302;
  M[124] = tmp308;
  M[125] = tmp291;
  M[126] = tmp278;
  M[127] = tmp280;
  M[128] = tmp276;
  M[129] = tmp87;
  M[130] = tmp301;
  M[131] = tmp288;
  M[132] = tmp44;
  M[133] = tmp24;
  M[134] = tmp51;
  M[135] = tmp23;
  M[136] = tmp50;
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
  M[150] = tmp24;
  M[151] = tmp309;
  M[152] = tmp300;
  M[153] = tmp24;
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
  M[172] = tmp287;
  M[173] = tmp289;
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
  M[192] = tmp23;
  M[193] = tmp305;
  M[194] = tmp310;
  M[195] = tmp23;
  M[196] = 0;
  M[197] = 0;
  M[198] = 6300;
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
  M[213] = tmp50;
  M[214] = tmp297;
  M[215] = tmp306;
  M[216] = tmp50;
  M[217] = 0;
  M[218] = 0;
  M[219] = 0;
  M[220] = 6300;
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
  M[231] = tmp277;
  M[232] = tmp284;
  M[233] = tmp281;
  M[234] = tmp177;
  M[235] = tmp313;
  M[236] = tmp303;
  M[237] = 0;
  M[238] = 0;
  M[239] = 0;
  M[240] = 0;
  M[241] = 0;
  M[242] = tmp130;
  M[243] = tmp112;
  M[244] = tmp139;
  M[245] = tmp113;
  M[246] = tmp140;
  M[247] = 0;
  M[248] = 0;
  M[249] = 0;
  M[250] = 0;
  M[251] = 0;
  M[252] = 0;
  M[253] = 0;
  M[254] = 0;
  M[255] = tmp179;
  M[256] = tmp311;
  M[257] = tmp290;
  M[258] = 0;
  M[259] = 0;
  M[260] = 0;
  M[261] = 0;
  M[262] = 0;
  M[263] = tmp112;
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
  M[276] = tmp182;
  M[277] = tmp294;
  M[278] = tmp292;
  M[279] = 0;
  M[280] = 0;
  M[281] = 0;
  M[282] = 0;
  M[283] = 0;
  M[284] = tmp139;
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
  M[297] = tmp181;
  M[298] = tmp314;
  M[299] = tmp285;
  M[300] = 0;
  M[301] = 0;
  M[302] = 0;
  M[303] = 0;
  M[304] = 0;
  M[305] = tmp113;
  M[306] = 0;
  M[307] = 0;
  M[308] = 6300;
  M[309] = 0;
  M[310] = 0;
  M[311] = 0;
  M[312] = 0;
  M[313] = 0;
  M[314] = 0;
  M[315] = 0;
  M[316] = 0;
  M[317] = 0;
  M[318] = tmp178;
  M[319] = tmp295;
  M[320] = tmp312;
  M[321] = 0;
  M[322] = 0;
  M[323] = 0;
  M[324] = 0;
  M[325] = 0;
  M[326] = tmp140;
  M[327] = 0;
  M[328] = 0;
  M[329] = 0;
  M[330] = 6300;
  M[331] = 0;
  M[332] = 0;
  M[333] = 0;
  M[334] = 0;
  M[335] = 0;
  M[336] = tmp279;
  M[337] = tmp282;
  M[338] = tmp283;
  M[339] = tmp270;
  M[340] = tmp286;
  M[341] = tmp298;
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
  M[352] = tmp223;
  M[353] = tmp205;
  M[354] = tmp234;
  M[355] = tmp206;
  M[356] = tmp233;
  M[357] = 0;
  M[358] = 0;
  M[359] = 0;
  M[360] = tmp268;
  M[361] = tmp307;
  M[362] = tmp299;
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
  M[373] = tmp205;
  M[374] = tmp190;
  M[375] = 0;
  M[376] = 0;
  M[377] = 0;
  M[378] = 0;
  M[379] = 0;
  M[380] = 0;
  M[381] = tmp265;
  M[382] = tmp304;
  M[383] = tmp302;
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
  M[394] = tmp234;
  M[395] = 0;
  M[396] = tmp216;
  M[397] = 0;
  M[398] = 0;
  M[399] = 0;
  M[400] = 0;
  M[401] = 0;
  M[402] = tmp269;
  M[403] = tmp293;
  M[404] = tmp308;
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
  M[415] = tmp206;
  M[416] = 0;
  M[417] = 0;
  M[418] = 6300;
  M[419] = 0;
  M[420] = 0;
  M[421] = 0;
  M[422] = 0;
  M[423] = tmp271;
  M[424] = tmp296;
  M[425] = tmp291;
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
  M[436] = tmp233;
  M[437] = 0;
  M[438] = 0;
  M[439] = 0;
  M[440] = 6300;
}
