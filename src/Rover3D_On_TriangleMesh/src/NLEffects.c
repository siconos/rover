#include <math.h>
#include "LagrangianModel.h"

void NLEffects(N, q, qdot)
double N[21];
double q[21];
double qdot[21];
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
  double tmp1 = 0.981e1 * C4 * S5;
  double tmp2 = 0.981e1 * S3 * S4 * S5 + 0.981e1 * C3 * C5;
  double tmp3 = 0.981e1 * C3 * S4 * S5 - 0.981e1 * S3 * C5;
  double tmp4 = (C3 * C4 * qdot[5] - S3 * qdot[4]) * (qdot[3] - S4 * qdot[5]);
  double tmp5 = (C3 * C4 * qdot[5] - S3 * qdot[4]) * (C4 * S3 * qdot[5] + C3 * qdot[4]);
  double tmp6 = -pow(C3 * C4 * qdot[5] - S3 * qdot[4], 2) - pow(qdot[3] - S4 * qdot[5], 2);
  double tmp7 = -pow(C4 * S3 * qdot[5] + C3 * qdot[4], 2) - pow(qdot[3] - S4 * qdot[5], 2);
  double tmp8 = (C4 * S3 * qdot[5] + C3 * qdot[4]) * (qdot[3] - S4 * qdot[5]);
  double tmp9 = -pow(C3 * C4 * qdot[5] - S3 * qdot[4], 2) - pow(C4 * S3 * qdot[5] + C3 * qdot[4], 2);
  double tmp10 = (C3 * C4 * qdot[5] - S3 * qdot[4]) * (qdot[3] - S4 * qdot[5]);
  double tmp11 = (C4 * S3 * qdot[5] + C3 * qdot[4]) * (qdot[3] - S4 * qdot[5]);
  double tmp12 = (C3 * C4 * qdot[5] - S3 * qdot[4]) * (C4 * S3 * qdot[5] + C3 * qdot[4]);
  double tmp13 = 700 * tmp1;
  double tmp14 = 700 * tmp2;
  double tmp15 = 700 * tmp3;
  double tmp16 = (C4 * S3 * qdot[5] + C3 * qdot[4]) * (0.2800000e7 / 0.3e1 * C3 * C4 * qdot[5] - 0.2800000e7 / 0.3e1 * S3 * qdot[4]) - (C3 * C4 * qdot[5] - S3 * qdot[4]) * (0.4270000e7 / 0.3e1 * C4 * S3 * qdot[5] + 0.4270000e7 / 0.3e1 * C3 * qdot[4]);
  double tmp17 = (C3 * C4 * qdot[5] - S3 * qdot[4]) * (0.2030000e7 / 0.3e1 * qdot[3] - 0.2030000e7 / 0.3e1 * S4 * qdot[5]) - (qdot[3] - S4 * qdot[5]) * (0.2800000e7 / 0.3e1 * C3 * C4 * qdot[5] - 0.2800000e7 / 0.3e1 * S3 * qdot[4]);
  double tmp18 = (qdot[3] - S4 * qdot[5]) * (0.4270000e7 / 0.3e1 * C4 * S3 * qdot[5] + 0.4270000e7 / 0.3e1 * C3 * qdot[4]) - (C4 * S3 * qdot[5] + C3 * qdot[4]) * (0.2030000e7 / 0.3e1 * qdot[3] - 0.2030000e7 / 0.3e1 * S4 * qdot[5]);
  double tmp19 = qdot[3] - S4 * qdot[5];
  double tmp20 = C6 * (C4 * S3 * qdot[5] + C3 * qdot[4]) + S6 * (C3 * C4 * qdot[5] - S3 * qdot[4]);
  double tmp21 = -S6 * (C4 * S3 * qdot[5] + C3 * qdot[4]) + C6 * (C3 * C4 * qdot[5] - S3 * qdot[4]);
  double tmp22 = tmp21 * qdot[6];
  double tmp23 = -tmp20 * qdot[6];
  double tmp24 = tmp1 + 62 * tmp9 - 10 * tmp11;
  double tmp25 = C6 * (tmp2 + 62 * tmp8 - 10 * tmp6) + S6 * (tmp3 + 62 * tmp10 - 10 * tmp5);
  double tmp26 = -S6 * (tmp2 + 62 * tmp8 - 10 * tmp6) + C6 * (tmp3 + 62 * tmp10 - 10 * tmp5);
  double tmp27 = tmp22 + tmp21 * (tmp19 + qdot[6]);
  double tmp30 = -tmp20 * tmp20 - pow(tmp19 + qdot[6], 2);
  double tmp35 = tmp21 * tmp20;
  double tmp36 = 20 * tmp24;
  double tmp37 = 20 * tmp25;
  double tmp38 = 20 * tmp26;
  double tmp39 = -0.65945e5 / 0.3e1 * tmp21 * tmp20;
  double tmp40 = 0.66305e5 / 0.3e1 * tmp22 + tmp21 * (0.66305e5 / 0.3e1 * tmp19 + 0.66305e5 / 0.3e1 * qdot[6]) - 120 * tmp21 * (tmp19 + qdot[6]);
  double tmp41 = 120 * tmp23 + 0.66305e5 / 0.3e1 * tmp20 * (tmp19 + qdot[6]) - tmp20 * (0.66305e5 / 0.3e1 * tmp19 + 0.66305e5 / 0.3e1 * qdot[6]);
  double tmp42 = C7 * (tmp19 + qdot[6]) - S7 * tmp21;
  double tmp43 = S7 * (tmp19 + qdot[6]) + C7 * tmp21;
  double tmp44 = -S7 * tmp23 - tmp43 * qdot[7];
  double tmp45 = C7 * tmp23 + tmp42 * qdot[7];
  double tmp46 = C7 * (tmp24 - 53 * tmp27) - S7 * (tmp26 - 53 * tmp30);
  double tmp47 = tmp25 - 53 * tmp35;
  double tmp48 = S7 * (tmp24 - 53 * tmp27) + C7 * (tmp26 - 53 * tmp30);
  double tmp50 = tmp44 + tmp43 * (tmp20 + qdot[7]);
  double tmp51 = -tmp43 * tmp43 - tmp42 * tmp42;
  double tmp56 = -tmp45 + (tmp20 + qdot[7]) * tmp42;
  double tmp58 = 6 * tmp46;
  double tmp59 = 6 * tmp47;
  double tmp60 = 6 * tmp48;
  double tmp61 = 126 * tmp44 + 126 * tmp43 * (tmp20 + qdot[7]) - tmp43 * (27 * tmp20 + 27 * qdot[7]);
  double tmp62 = 27 * tmp22;
  double tmp63 = 126 * tmp45 + tmp42 * (27 * tmp20 + 27 * qdot[7]) - 126 * (tmp20 + qdot[7]) * tmp42;
  double tmp64 = C9 * tmp42 + S9 * (tmp20 + qdot[7]);
  double tmp65 = -S9 * tmp42 + C9 * (tmp20 + qdot[7]);
  double tmp66 = C9 * tmp44 + S9 * tmp22 + tmp65 * qdot[9];
  double tmp67 = -S9 * tmp44 + C9 * tmp22 - tmp64 * qdot[9];
  double tmp68 = C9 * (tmp46 - 15 * tmp56) + S9 * (tmp47 - 15 * tmp51);
  double tmp69 = -S9 * (tmp46 - 15 * tmp56) + C9 * (tmp47 - 15 * tmp51);
  double tmp70 = tmp48 - 15 * tmp50;
  double tmp80 = 14 * tmp68;
  double tmp81 = 14 * tmp69;
  double tmp82 = 14 * tmp70;
  double tmp83 = 350 * tmp66 + tmp65 * (700 * tmp43 + 700 * qdot[9]) - 350 * (tmp43 + qdot[9]) * tmp65;
  double tmp84 = 350 * tmp67 + 350 * (tmp43 + qdot[9]) * tmp64 - tmp64 * (700 * tmp43 + 700 * qdot[9]);
  double tmp85 = 700 * tmp45;
  double tmp86 = C9 * tmp80 - S9 * tmp81;
  double tmp87 = S9 * tmp80 + C9 * tmp81;
  double tmp88 = C9 * tmp83 - S9 * tmp84 - 15 * tmp82;
  double tmp89 = S9 * tmp83 + C9 * tmp84;
  double tmp90 = tmp85 + 15 * tmp86;
  double tmp91 = tmp58 + tmp86;
  double tmp92 = tmp59 + tmp87;
  double tmp93 = tmp60 + tmp82;
  double tmp94 = tmp61 + tmp88;
  double tmp95 = tmp62 + tmp89;
  double tmp96 = tmp63 + tmp90;
  double tmp97 = C7 * tmp91 + S7 * tmp93;
  double tmp98 = -S7 * tmp91 + C7 * tmp93;
  double tmp99 = C7 * tmp94 + S7 * tmp96 + 53 * tmp92;
  double tmp100 = tmp95 - 53 * tmp97;
  double tmp101 = -S7 * tmp94 + C7 * tmp96;
  double tmp102 = tmp36 + tmp97;
  double tmp103 = tmp37 + tmp92;
  double tmp104 = tmp38 + tmp98;
  double tmp105 = tmp39 + tmp99;
  double tmp106 = tmp40 + tmp100;
  double tmp107 = tmp41 + tmp101;
  double tmp108 = C8 * (tmp19 + qdot[6]) - S8 * tmp21;
  double tmp109 = S8 * (tmp19 + qdot[6]) + C8 * tmp21;
  double tmp110 = -S8 * tmp23 - tmp109 * qdot[8];
  double tmp111 = C8 * tmp23 + tmp108 * qdot[8];
  double tmp112 = C8 * (tmp24 + 53 * tmp27) - S8 * (tmp26 + 53 * tmp30);
  double tmp113 = tmp25 + 53 * tmp35;
  double tmp114 = S8 * (tmp24 + 53 * tmp27) + C8 * (tmp26 + 53 * tmp30);
  double tmp116 = tmp110 + tmp109 * (tmp20 + qdot[8]);
  double tmp117 = -tmp109 * tmp109 - tmp108 * tmp108;
  double tmp122 = -tmp111 + (tmp20 + qdot[8]) * tmp108;
  double tmp124 = 6 * tmp112;
  double tmp125 = 6 * tmp113;
  double tmp126 = 6 * tmp114;
  double tmp127 = 126 * tmp110 + 126 * tmp109 * (tmp20 + qdot[8]) - tmp109 * (27 * tmp20 + 27 * qdot[8]);
  double tmp128 = 27 * tmp22;
  double tmp129 = 126 * tmp111 + tmp108 * (27 * tmp20 + 27 * qdot[8]) - 126 * (tmp20 + qdot[8]) * tmp108;
  double tmp130 = C10 * tmp108 + S10 * (tmp20 + qdot[8]);
  double tmp131 = -S10 * tmp108 + C10 * (tmp20 + qdot[8]);
  double tmp132 = C10 * tmp110 + S10 * tmp22 + tmp131 * qdot[10];
  double tmp133 = -S10 * tmp110 + C10 * tmp22 - tmp130 * qdot[10];
  double tmp134 = C10 * (tmp112 - 15 * tmp122) + S10 * (tmp113 - 15 * tmp117);
  double tmp135 = -S10 * (tmp112 - 15 * tmp122) + C10 * (tmp113 - 15 * tmp117);
  double tmp136 = tmp114 - 15 * tmp116;
  double tmp146 = 14 * tmp134;
  double tmp147 = 14 * tmp135;
  double tmp148 = 14 * tmp136;
  double tmp149 = 350 * tmp132 + tmp131 * (700 * tmp109 + 700 * qdot[10]) - 350 * (tmp109 + qdot[10]) * tmp131;
  double tmp150 = 350 * tmp133 + 350 * (tmp109 + qdot[10]) * tmp130 - tmp130 * (700 * tmp109 + 700 * qdot[10]);
  double tmp151 = 700 * tmp111;
  double tmp152 = C10 * tmp146 - S10 * tmp147;
  double tmp153 = S10 * tmp146 + C10 * tmp147;
  double tmp154 = C10 * tmp149 - S10 * tmp150 - 15 * tmp148;
  double tmp155 = S10 * tmp149 + C10 * tmp150;
  double tmp156 = tmp151 + 15 * tmp152;
  double tmp157 = tmp124 + tmp152;
  double tmp158 = tmp125 + tmp153;
  double tmp159 = tmp126 + tmp148;
  double tmp160 = tmp127 + tmp154;
  double tmp161 = tmp128 + tmp155;
  double tmp162 = tmp129 + tmp156;
  double tmp163 = C8 * tmp157 + S8 * tmp159;
  double tmp164 = -S8 * tmp157 + C8 * tmp159;
  double tmp165 = C8 * tmp160 + S8 * tmp162 - 53 * tmp158;
  double tmp166 = tmp161 + 53 * tmp163;
  double tmp167 = -S8 * tmp160 + C8 * tmp162;
  double tmp168 = tmp102 + tmp163;
  double tmp169 = tmp103 + tmp158;
  double tmp170 = tmp104 + tmp164;
  double tmp171 = tmp105 + tmp165;
  double tmp172 = tmp106 + tmp166;
  double tmp173 = tmp107 + tmp167;
  double tmp174 = C6 * tmp169 - S6 * tmp170;
  double tmp175 = S6 * tmp169 + C6 * tmp170;
  double tmp176 = tmp171 - 10 * tmp175;
  double tmp177 = C6 * tmp172 - S6 * tmp173 - 62 * tmp175;
  double tmp178 = S6 * tmp172 + C6 * tmp173 + 62 * tmp174 + 10 * tmp168;
  double tmp179 = tmp13 + tmp168;
  double tmp180 = tmp14 + tmp174;
  double tmp181 = tmp15 + tmp175;
  double tmp182 = tmp16 + tmp176;
  double tmp183 = tmp17 + tmp177;
  double tmp184 = tmp18 + tmp178;
  double tmp185 = C11 * (qdot[3] - S4 * qdot[5]) + S11 * (C4 * S3 * qdot[5] + C3 * qdot[4]);
  double tmp186 = -S11 * (qdot[3] - S4 * qdot[5]) + C11 * (C4 * S3 * qdot[5] + C3 * qdot[4]);
  double tmp187 = C3 * C4 * qdot[5] - S3 * qdot[4];
  double tmp188 = tmp186 * qdot[11];
  double tmp189 = -tmp185 * qdot[11];
  double tmp190 = C11 * (tmp1 - 40 * tmp9 - 10 * tmp11 - 53 * tmp4) + S11 * (tmp2 - 40 * tmp8 - 10 * tmp6 - 53 * tmp12);
  double tmp191 = -S11 * (tmp1 - 40 * tmp9 - 10 * tmp11 - 53 * tmp4) + C11 * (tmp2 - 40 * tmp8 - 10 * tmp6 - 53 * tmp12);
  double tmp192 = tmp3 - 40 * tmp10 - 10 * tmp5 - 53 * tmp7;
  double tmp197 = tmp186 * tmp185;
  double tmp198 = -pow(tmp187 + qdot[11], 2) - tmp186 * tmp186;
  double tmp199 = -tmp189 + (tmp187 + qdot[11]) * tmp185;
  double tmp202 = 20 * tmp190;
  double tmp203 = 20 * tmp191;
  double tmp204 = 20 * tmp192;
  double tmp205 = 120 * tmp188 + tmp186 * (0.24680e5 / 0.3e1 * tmp187 + 0.24680e5 / 0.3e1 * qdot[11]) - 0.24680e5 / 0.3e1 * (tmp187 + qdot[11]) * tmp186;
  double tmp206 = 0.24680e5 / 0.3e1 * tmp189 + 120 * (tmp187 + qdot[11]) * tmp185 - tmp185 * (0.24680e5 / 0.3e1 * tmp187 + 0.24680e5 / 0.3e1 * qdot[11]);
  double tmp207 = 0.24320e5 / 0.3e1 * tmp186 * tmp185;
  double tmp208 = C12 * tmp185 - S12 * (tmp187 + qdot[11]);
  double tmp209 = S12 * tmp185 + C12 * (tmp187 + qdot[11]);
  double tmp210 = C12 * tmp188 - tmp209 * qdot[12];
  double tmp211 = S12 * tmp188 + tmp208 * qdot[12];
  double tmp212 = C12 * (tmp190 + 30 * tmp198) - S12 * (tmp192 + 30 * tmp199);
  double tmp213 = tmp191 + 30 * tmp197;
  double tmp214 = S12 * (tmp190 + 30 * tmp198) + C12 * (tmp192 + 30 * tmp199);
  double tmp216 = tmp210 + tmp209 * (tmp186 + qdot[12]);
  double tmp217 = -tmp209 * tmp209 - tmp208 * tmp208;
  double tmp222 = -tmp211 + (tmp186 + qdot[12]) * tmp208;
  double tmp224 = 6 * tmp212;
  double tmp225 = 6 * tmp213;
  double tmp226 = 6 * tmp214;
  double tmp227 = 126 * tmp210 + 126 * tmp209 * (tmp186 + qdot[12]) - tmp209 * (27 * tmp186 + 27 * qdot[12]);
  double tmp228 = 27 * tmp189;
  double tmp229 = 126 * tmp211 + tmp208 * (27 * tmp186 + 27 * qdot[12]) - 126 * (tmp186 + qdot[12]) * tmp208;
  double tmp230 = C14 * tmp208 + S14 * (tmp186 + qdot[12]);
  double tmp231 = -S14 * tmp208 + C14 * (tmp186 + qdot[12]);
  double tmp232 = C14 * tmp210 + S14 * tmp189 + tmp231 * qdot[14];
  double tmp233 = -S14 * tmp210 + C14 * tmp189 - tmp230 * qdot[14];
  double tmp234 = C14 * (tmp212 - 15 * tmp222) + S14 * (tmp213 - 15 * tmp217);
  double tmp235 = -S14 * (tmp212 - 15 * tmp222) + C14 * (tmp213 - 15 * tmp217);
  double tmp236 = tmp214 - 15 * tmp216;
  double tmp246 = 14 * tmp234;
  double tmp247 = 14 * tmp235;
  double tmp248 = 14 * tmp236;
  double tmp249 = 350 * tmp232 + tmp231 * (700 * tmp209 + 700 * qdot[14]) - 350 * (tmp209 + qdot[14]) * tmp231;
  double tmp250 = 350 * tmp233 + 350 * (tmp209 + qdot[14]) * tmp230 - tmp230 * (700 * tmp209 + 700 * qdot[14]);
  double tmp251 = 700 * tmp211;
  double tmp252 = C14 * tmp246 - S14 * tmp247;
  double tmp253 = S14 * tmp246 + C14 * tmp247;
  double tmp254 = C14 * tmp249 - S14 * tmp250 - 15 * tmp248;
  double tmp255 = S14 * tmp249 + C14 * tmp250;
  double tmp256 = tmp251 + 15 * tmp252;
  double tmp257 = tmp224 + tmp252;
  double tmp258 = tmp225 + tmp253;
  double tmp259 = tmp226 + tmp248;
  double tmp260 = tmp227 + tmp254;
  double tmp261 = tmp228 + tmp255;
  double tmp262 = tmp229 + tmp256;
  double tmp263 = C12 * tmp257 + S12 * tmp259;
  double tmp264 = -S12 * tmp257 + C12 * tmp259;
  double tmp265 = C12 * tmp260 + S12 * tmp262;
  double tmp266 = tmp261 - 30 * tmp264;
  double tmp267 = -S12 * tmp260 + C12 * tmp262 + 30 * tmp258;
  double tmp268 = tmp202 + tmp263;
  double tmp269 = tmp203 + tmp258;
  double tmp270 = tmp204 + tmp264;
  double tmp271 = tmp205 + tmp265;
  double tmp272 = tmp206 + tmp266;
  double tmp273 = tmp207 + tmp267;
  double tmp274 = C13 * tmp185 - S13 * (tmp187 + qdot[11]);
  double tmp275 = S13 * tmp185 + C13 * (tmp187 + qdot[11]);
  double tmp276 = C13 * tmp188 - tmp275 * qdot[13];
  double tmp277 = S13 * tmp188 + tmp274 * qdot[13];
  double tmp278 = C13 * (tmp190 - 30 * tmp198) - S13 * (tmp192 - 30 * tmp199);
  double tmp279 = tmp191 - 30 * tmp197;
  double tmp280 = S13 * (tmp190 - 30 * tmp198) + C13 * (tmp192 - 30 * tmp199);
  double tmp282 = tmp276 + tmp275 * (tmp186 + qdot[13]);
  double tmp283 = -tmp275 * tmp275 - tmp274 * tmp274;
  double tmp288 = -tmp277 + (tmp186 + qdot[13]) * tmp274;
  double tmp290 = 6 * tmp278;
  double tmp291 = 6 * tmp279;
  double tmp292 = 6 * tmp280;
  double tmp293 = 126 * tmp276 + 126 * tmp275 * (tmp186 + qdot[13]) - tmp275 * (27 * tmp186 + 27 * qdot[13]);
  double tmp294 = 27 * tmp189;
  double tmp295 = 126 * tmp277 + tmp274 * (27 * tmp186 + 27 * qdot[13]) - 126 * (tmp186 + qdot[13]) * tmp274;
  double tmp296 = C15 * tmp274 + S15 * (tmp186 + qdot[13]);
  double tmp297 = -S15 * tmp274 + C15 * (tmp186 + qdot[13]);
  double tmp298 = C15 * tmp276 + S15 * tmp189 + tmp297 * qdot[15];
  double tmp299 = -S15 * tmp276 + C15 * tmp189 - tmp296 * qdot[15];
  double tmp300 = C15 * (tmp278 - 15 * tmp288) + S15 * (tmp279 - 15 * tmp283);
  double tmp301 = -S15 * (tmp278 - 15 * tmp288) + C15 * (tmp279 - 15 * tmp283);
  double tmp302 = tmp280 - 15 * tmp282;
  double tmp312 = 14 * tmp300;
  double tmp313 = 14 * tmp301;
  double tmp314 = 14 * tmp302;
  double tmp315 = 350 * tmp298 + tmp297 * (700 * tmp275 + 700 * qdot[15]) - 350 * (tmp275 + qdot[15]) * tmp297;
  double tmp316 = 350 * tmp299 + 350 * (tmp275 + qdot[15]) * tmp296 - tmp296 * (700 * tmp275 + 700 * qdot[15]);
  double tmp317 = 700 * tmp277;
  double tmp318 = C15 * tmp312 - S15 * tmp313;
  double tmp319 = S15 * tmp312 + C15 * tmp313;
  double tmp320 = C15 * tmp315 - S15 * tmp316 - 15 * tmp314;
  double tmp321 = S15 * tmp315 + C15 * tmp316;
  double tmp322 = tmp317 + 15 * tmp318;
  double tmp323 = tmp290 + tmp318;
  double tmp324 = tmp291 + tmp319;
  double tmp325 = tmp292 + tmp314;
  double tmp326 = tmp293 + tmp320;
  double tmp327 = tmp294 + tmp321;
  double tmp328 = tmp295 + tmp322;
  double tmp329 = C13 * tmp323 + S13 * tmp325;
  double tmp330 = -S13 * tmp323 + C13 * tmp325;
  double tmp331 = C13 * tmp326 + S13 * tmp328;
  double tmp332 = tmp327 + 30 * tmp330;
  double tmp333 = -S13 * tmp326 + C13 * tmp328 - 30 * tmp324;
  double tmp334 = tmp268 + tmp329;
  double tmp335 = tmp269 + tmp324;
  double tmp336 = tmp270 + tmp330;
  double tmp337 = tmp271 + tmp331;
  double tmp338 = tmp272 + tmp332;
  double tmp339 = tmp273 + tmp333;
  double tmp340 = C11 * tmp334 - S11 * tmp335;
  double tmp341 = S11 * tmp334 + C11 * tmp335;
  double tmp342 = C11 * tmp337 - S11 * tmp338 - 10 * tmp336 + 53 * tmp341;
  double tmp343 = S11 * tmp337 + C11 * tmp338 - 53 * tmp340 + 40 * tmp336;
  double tmp344 = tmp339 - 40 * tmp341 + 10 * tmp340;
  double tmp345 = tmp179 + tmp340;
  double tmp346 = tmp180 + tmp341;
  double tmp347 = tmp181 + tmp336;
  double tmp348 = tmp182 + tmp342;
  double tmp349 = tmp183 + tmp343;
  double tmp350 = tmp184 + tmp344;
  double tmp351 = C16 * (qdot[3] - S4 * qdot[5]) + S16 * (C4 * S3 * qdot[5] + C3 * qdot[4]);
  double tmp352 = -S16 * (qdot[3] - S4 * qdot[5]) + C16 * (C4 * S3 * qdot[5] + C3 * qdot[4]);
  double tmp353 = C3 * C4 * qdot[5] - S3 * qdot[4];
  double tmp354 = tmp352 * qdot[16];
  double tmp355 = -tmp351 * qdot[16];
  double tmp356 = C16 * (tmp1 - 40 * tmp9 - 10 * tmp11 + 53 * tmp4) + S16 * (tmp2 - 40 * tmp8 - 10 * tmp6 + 53 * tmp12);
  double tmp357 = -S16 * (tmp1 - 40 * tmp9 - 10 * tmp11 + 53 * tmp4) + C16 * (tmp2 - 40 * tmp8 - 10 * tmp6 + 53 * tmp12);
  double tmp358 = tmp3 - 40 * tmp10 - 10 * tmp5 + 53 * tmp7;
  double tmp363 = tmp352 * tmp351;
  double tmp364 = -pow(tmp353 + qdot[16], 2) - tmp352 * tmp352;
  double tmp365 = -tmp355 + (tmp353 + qdot[16]) * tmp351;
  double tmp368 = 20 * tmp356;
  double tmp369 = 20 * tmp357;
  double tmp370 = 20 * tmp358;
  double tmp371 = 120 * tmp354 + tmp352 * (0.24680e5 / 0.3e1 * tmp353 + 0.24680e5 / 0.3e1 * qdot[16]) - 0.24680e5 / 0.3e1 * (tmp353 + qdot[16]) * tmp352;
  double tmp372 = 0.24680e5 / 0.3e1 * tmp355 + 120 * (tmp353 + qdot[16]) * tmp351 - tmp351 * (0.24680e5 / 0.3e1 * tmp353 + 0.24680e5 / 0.3e1 * qdot[16]);
  double tmp373 = 0.24320e5 / 0.3e1 * tmp352 * tmp351;
  double tmp374 = C17 * tmp351 - S17 * (tmp353 + qdot[16]);
  double tmp375 = S17 * tmp351 + C17 * (tmp353 + qdot[16]);
  double tmp376 = C17 * tmp354 - tmp375 * qdot[17];
  double tmp377 = S17 * tmp354 + tmp374 * qdot[17];
  double tmp378 = C17 * (tmp356 + 30 * tmp364) - S17 * (tmp358 + 30 * tmp365);
  double tmp379 = tmp357 + 30 * tmp363;
  double tmp380 = S17 * (tmp356 + 30 * tmp364) + C17 * (tmp358 + 30 * tmp365);
  double tmp382 = tmp376 + tmp375 * (tmp352 + qdot[17]);
  double tmp383 = -tmp375 * tmp375 - tmp374 * tmp374;
  double tmp388 = -tmp377 + (tmp352 + qdot[17]) * tmp374;
  double tmp390 = 6 * tmp378;
  double tmp391 = 6 * tmp379;
  double tmp392 = 6 * tmp380;
  double tmp393 = 126 * tmp376 + 126 * tmp375 * (tmp352 + qdot[17]) - tmp375 * (27 * tmp352 + 27 * qdot[17]);
  double tmp394 = 27 * tmp355;
  double tmp395 = 126 * tmp377 + tmp374 * (27 * tmp352 + 27 * qdot[17]) - 126 * (tmp352 + qdot[17]) * tmp374;
  double tmp396 = C19 * tmp374 + S19 * (tmp352 + qdot[17]);
  double tmp397 = -S19 * tmp374 + C19 * (tmp352 + qdot[17]);
  double tmp398 = C19 * tmp376 + S19 * tmp355 + tmp397 * qdot[19];
  double tmp399 = -S19 * tmp376 + C19 * tmp355 - tmp396 * qdot[19];
  double tmp400 = C19 * (tmp378 - 15 * tmp388) + S19 * (tmp379 - 15 * tmp383);
  double tmp401 = -S19 * (tmp378 - 15 * tmp388) + C19 * (tmp379 - 15 * tmp383);
  double tmp402 = tmp380 - 15 * tmp382;
  double tmp412 = 14 * tmp400;
  double tmp413 = 14 * tmp401;
  double tmp414 = 14 * tmp402;
  double tmp415 = 350 * tmp398 + tmp397 * (700 * tmp375 + 700 * qdot[19]) - 350 * (tmp375 + qdot[19]) * tmp397;
  double tmp416 = 350 * tmp399 + 350 * (tmp375 + qdot[19]) * tmp396 - tmp396 * (700 * tmp375 + 700 * qdot[19]);
  double tmp417 = 700 * tmp377;
  double tmp418 = C19 * tmp412 - S19 * tmp413;
  double tmp419 = S19 * tmp412 + C19 * tmp413;
  double tmp420 = C19 * tmp415 - S19 * tmp416 - 15 * tmp414;
  double tmp421 = S19 * tmp415 + C19 * tmp416;
  double tmp422 = tmp417 + 15 * tmp418;
  double tmp423 = tmp390 + tmp418;
  double tmp424 = tmp391 + tmp419;
  double tmp425 = tmp392 + tmp414;
  double tmp426 = tmp393 + tmp420;
  double tmp427 = tmp394 + tmp421;
  double tmp428 = tmp395 + tmp422;
  double tmp429 = C17 * tmp423 + S17 * tmp425;
  double tmp430 = -S17 * tmp423 + C17 * tmp425;
  double tmp431 = C17 * tmp426 + S17 * tmp428;
  double tmp432 = tmp427 - 30 * tmp430;
  double tmp433 = -S17 * tmp426 + C17 * tmp428 + 30 * tmp424;
  double tmp434 = tmp368 + tmp429;
  double tmp435 = tmp369 + tmp424;
  double tmp436 = tmp370 + tmp430;
  double tmp437 = tmp371 + tmp431;
  double tmp438 = tmp372 + tmp432;
  double tmp439 = tmp373 + tmp433;
  double tmp440 = C18 * tmp351 - S18 * (tmp353 + qdot[16]);
  double tmp441 = S18 * tmp351 + C18 * (tmp353 + qdot[16]);
  double tmp442 = C18 * tmp354 - tmp441 * qdot[18];
  double tmp443 = S18 * tmp354 + tmp440 * qdot[18];
  double tmp444 = C18 * (tmp356 - 30 * tmp364) - S18 * (tmp358 - 30 * tmp365);
  double tmp445 = tmp357 - 30 * tmp363;
  double tmp446 = S18 * (tmp356 - 30 * tmp364) + C18 * (tmp358 - 30 * tmp365);
  double tmp448 = tmp442 + tmp441 * (tmp352 + qdot[18]);
  double tmp449 = -tmp441 * tmp441 - tmp440 * tmp440;
  double tmp454 = -tmp443 + (tmp352 + qdot[18]) * tmp440;
  double tmp456 = 6 * tmp444;
  double tmp457 = 6 * tmp445;
  double tmp458 = 6 * tmp446;
  double tmp459 = 126 * tmp442 + 126 * tmp441 * (tmp352 + qdot[18]) - tmp441 * (27 * tmp352 + 27 * qdot[18]);
  double tmp460 = 27 * tmp355;
  double tmp461 = 126 * tmp443 + tmp440 * (27 * tmp352 + 27 * qdot[18]) - 126 * (tmp352 + qdot[18]) * tmp440;
  double tmp462 = C20 * tmp440 + S20 * (tmp352 + qdot[18]);
  double tmp463 = -S20 * tmp440 + C20 * (tmp352 + qdot[18]);
  double tmp464 = C20 * tmp442 + S20 * tmp355 + tmp463 * qdot[20];
  double tmp465 = -S20 * tmp442 + C20 * tmp355 - tmp462 * qdot[20];
  double tmp466 = C20 * (tmp444 - 15 * tmp454) + S20 * (tmp445 - 15 * tmp449);
  double tmp467 = -S20 * (tmp444 - 15 * tmp454) + C20 * (tmp445 - 15 * tmp449);
  double tmp468 = tmp446 - 15 * tmp448;
  double tmp478 = 14 * tmp466;
  double tmp479 = 14 * tmp467;
  double tmp480 = 14 * tmp468;
  double tmp481 = 350 * tmp464 + tmp463 * (700 * tmp441 + 700 * qdot[20]) - 350 * (tmp441 + qdot[20]) * tmp463;
  double tmp482 = 350 * tmp465 + 350 * (tmp441 + qdot[20]) * tmp462 - tmp462 * (700 * tmp441 + 700 * qdot[20]);
  double tmp483 = 700 * tmp443;
  double tmp484 = C20 * tmp478 - S20 * tmp479;
  double tmp485 = S20 * tmp478 + C20 * tmp479;
  double tmp486 = C20 * tmp481 - S20 * tmp482 - 15 * tmp480;
  double tmp487 = S20 * tmp481 + C20 * tmp482;
  double tmp488 = tmp483 + 15 * tmp484;
  double tmp489 = tmp456 + tmp484;
  double tmp490 = tmp457 + tmp485;
  double tmp491 = tmp458 + tmp480;
  double tmp492 = tmp459 + tmp486;
  double tmp493 = tmp460 + tmp487;
  double tmp494 = tmp461 + tmp488;
  double tmp495 = C18 * tmp489 + S18 * tmp491;
  double tmp496 = -S18 * tmp489 + C18 * tmp491;
  double tmp497 = C18 * tmp492 + S18 * tmp494;
  double tmp498 = tmp493 + 30 * tmp496;
  double tmp499 = -S18 * tmp492 + C18 * tmp494 - 30 * tmp490;
  double tmp500 = tmp434 + tmp495;
  double tmp501 = tmp435 + tmp490;
  double tmp502 = tmp436 + tmp496;
  double tmp503 = tmp437 + tmp497;
  double tmp504 = tmp438 + tmp498;
  double tmp505 = tmp439 + tmp499;
  double tmp506 = C16 * tmp500 - S16 * tmp501;
  double tmp507 = S16 * tmp500 + C16 * tmp501;
  double tmp508 = C16 * tmp503 - S16 * tmp504 - 10 * tmp502 - 53 * tmp507;
  double tmp509 = S16 * tmp503 + C16 * tmp504 + 53 * tmp506 + 40 * tmp502;
  double tmp510 = tmp505 - 40 * tmp507 + 10 * tmp506;
  double tmp511 = tmp345 + tmp506;
  double tmp512 = tmp346 + tmp507;
  double tmp513 = tmp347 + tmp502;
  double tmp514 = tmp348 + tmp508;
  double tmp515 = tmp349 + tmp509;
  double tmp516 = tmp350 + tmp510;
  double tmp517 = C4 * C5 * tmp511 + (S3 * S4 * C5 - C3 * S5) * tmp512 + (C3 * S4 * C5 + S3 * S5) * tmp513;
  double tmp518 = C4 * S5 * tmp511 + (S3 * S4 * S5 + C3 * C5) * tmp512 + (C3 * S4 * S5 - S3 * C5) * tmp513;
  double tmp519 = -S4 * tmp511 + S3 * C4 * tmp512 + C3 * C4 * tmp513;
  double tmp520 = C3 * tmp515 - S3 * tmp516;
  double tmp521 = -S4 * tmp514 + S3 * C4 * tmp515 + C3 * C4 * tmp516;
  N[0] = tmp517;
  N[1] = tmp518;
  N[2] = tmp519;
  N[3] = tmp514;
  N[4] = tmp520;
  N[5] = tmp521;
  N[6] = tmp171;
  N[7] = tmp95;
  N[8] = tmp161;
  N[9] = tmp85;
  N[10] = tmp151;
  N[11] = tmp339;
  N[12] = tmp261;
  N[13] = tmp327;
  N[14] = tmp251;
  N[15] = tmp317;
  N[16] = tmp505;
  N[17] = tmp427;
  N[18] = tmp493;
  N[19] = tmp417;
  N[20] = tmp483;
}
