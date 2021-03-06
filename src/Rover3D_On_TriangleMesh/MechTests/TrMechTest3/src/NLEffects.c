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
  double tmp1 = -0.369e1 * S4;
  double tmp2 = 0.369e1 * S3 * C4;
  double tmp3 = 0.369e1 * C3 * C4;
  double tmp4 = (C4 * S3 * qdot[5] + C3 * qdot[4]) * (qdot[3] - S4 * qdot[5]);
  double tmp5 = (C3 * C4 * qdot[5] - S3 * qdot[4]) * (qdot[3] - S4 * qdot[5]);
  double tmp6 = (C3 * C4 * qdot[5] - S3 * qdot[4]) * (C4 * S3 * qdot[5] + C3 * qdot[4]);
  double tmp7 = -pow(C3 * C4 * qdot[5] - S3 * qdot[4], 2) - pow(qdot[3] - S4 * qdot[5], 2);
  double tmp8 = -pow(C4 * S3 * qdot[5] + C3 * qdot[4], 2) - pow(qdot[3] - S4 * qdot[5], 2);
  double tmp9 = -pow(C3 * C4 * qdot[5] - S3 * qdot[4], 2) - pow(C4 * S3 * qdot[5] + C3 * qdot[4], 2);
  double tmp10 = (C3 * C4 * qdot[5] - S3 * qdot[4]) * (qdot[3] - S4 * qdot[5]);
  double tmp11 = (C4 * S3 * qdot[5] + C3 * qdot[4]) * (qdot[3] - S4 * qdot[5]);
  double tmp12 = (C3 * C4 * qdot[5] - S3 * qdot[4]) * (C4 * S3 * qdot[5] + C3 * qdot[4]);
  double tmp13 = 50 * tmp1;
  double tmp14 = 50 * tmp2;
  double tmp15 = 50 * tmp3;
  double tmp16 = (C4 * S3 * qdot[5] + C3 * qdot[4]) * (0.5463270833e1 * C3 * C4 * qdot[5] - 0.5463270833e1 * S3 * qdot[4]) - (C3 * C4 * qdot[5] - S3 * qdot[4]) * (0.3450663542e1 * C4 * S3 * qdot[5] + 0.3450663542e1 * C3 * qdot[4]);
  double tmp17 = (C3 * C4 * qdot[5] - S3 * qdot[4]) * (0.4677526042e1 * qdot[3] - 0.4677526042e1 * S4 * qdot[5]) - (qdot[3] - S4 * qdot[5]) * (0.5463270833e1 * C3 * C4 * qdot[5] - 0.5463270833e1 * S3 * qdot[4]);
  double tmp18 = (qdot[3] - S4 * qdot[5]) * (0.3450663542e1 * C4 * S3 * qdot[5] + 0.3450663542e1 * C3 * qdot[4]) - (C4 * S3 * qdot[5] + C3 * qdot[4]) * (0.4677526042e1 * qdot[3] - 0.4677526042e1 * S4 * qdot[5]);
  double tmp19 = qdot[3] - S4 * qdot[5];
  double tmp20 = C6 * (C4 * S3 * qdot[5] + C3 * qdot[4]) + S6 * (C3 * C4 * qdot[5] - S3 * qdot[4]);
  double tmp21 = -S6 * (C4 * S3 * qdot[5] + C3 * qdot[4]) + C6 * (C3 * C4 * qdot[5] - S3 * qdot[4]);
  double tmp22 = tmp21 * qdot[6];
  double tmp23 = -tmp20 * qdot[6];
  double tmp24 = tmp1 - 0.4139999000e0 * tmp9 - 0.16375e0 * tmp5;
  double tmp25 = C6 * (tmp2 - 0.4139999000e0 * tmp4 - 0.16375e0 * tmp6) + S6 * (tmp3 - 0.4139999000e0 * tmp10 - 0.16375e0 * tmp8);
  double tmp26 = -S6 * (tmp2 - 0.4139999000e0 * tmp4 - 0.16375e0 * tmp6) + C6 * (tmp3 - 0.4139999000e0 * tmp10 - 0.16375e0 * tmp8);
  double tmp27 = tmp23 + tmp20 * (tmp19 + qdot[6]);
  double tmp28 = tmp22 + tmp21 * (tmp19 + qdot[6]);
  double tmp29 = tmp21 * tmp20;
  double tmp30 = -tmp21 * tmp21 - pow(tmp19 + qdot[6], 2);
  double tmp31 = -tmp20 * tmp20 - pow(tmp19 + qdot[6], 2);
  double tmp32 = -tmp21 * tmp21 - tmp20 * tmp20;
  double tmp33 = -tmp22 + tmp21 * (tmp19 + qdot[6]);
  double tmp34 = -tmp23 + tmp20 * (tmp19 + qdot[6]);
  double tmp35 = tmp21 * tmp20;
  double tmp36 = 4 * tmp24;
  double tmp37 = 4 * tmp25;
  double tmp38 = 4 * tmp26;
  double tmp39 = 0.3519918024e0 * tmp21 * tmp20;
  double tmp40 = 0.3402719757e-1 * tmp22 + tmp21 * (0.3746321977e0 * tmp19 + 0.3746321977e0 * qdot[6]) - 0.3860190000e0 * tmp21 * (tmp19 + qdot[6]);
  double tmp41 = 0.3860190000e0 * tmp23 + 0.3402719757e-1 * tmp20 * (tmp19 + qdot[6]) - tmp20 * (0.3746321977e0 * tmp19 + 0.3746321977e0 * qdot[6]);
  double tmp42 = C7 * (tmp19 + qdot[6]) + S7 * tmp20;
  double tmp43 = -S7 * (tmp19 + qdot[6]) + C7 * tmp20;
  double tmp44 = S7 * tmp22 + tmp43 * qdot[7];
  double tmp45 = C7 * tmp22 - tmp42 * qdot[7];
  double tmp46 = C7 * (tmp24 - 0.2235e0 * tmp32 + 0.601203e0 * tmp34 - 0.64092e-1 * tmp28) + S7 * (tmp25 - 0.2235e0 * tmp27 + 0.601203e0 * tmp30 - 0.64092e-1 * tmp29);
  double tmp47 = -S7 * (tmp24 - 0.2235e0 * tmp32 + 0.601203e0 * tmp34 - 0.64092e-1 * tmp28) + C7 * (tmp25 - 0.2235e0 * tmp27 + 0.601203e0 * tmp30 - 0.64092e-1 * tmp29);
  double tmp48 = tmp26 - 0.2235e0 * tmp33 + 0.601203e0 * tmp35 - 0.64092e-1 * tmp31;
  double tmp50 = tmp45 + (tmp21 + qdot[7]) * tmp42;
  double tmp51 = -tmp44 + (tmp21 + qdot[7]) * tmp43;
  double tmp53 = -tmp43 * tmp43 - tmp42 * tmp42;
  double tmp58 = 0.5937903093e-2 * tmp44 + tmp43 * (0.2928831175e-2 * tmp21 + 0.2928831175e-2 * qdot[7]) - 0.5653560135e-2 * (tmp21 + qdot[7]) * tmp43;
  double tmp59 = 0.5653560135e-2 * tmp45 + 0.5937903093e-2 * (tmp21 + qdot[7]) * tmp42 - tmp42 * (0.2928831175e-2 * tmp21 + 0.2928831175e-2 * qdot[7]);
  double tmp60 = 0.2928831175e-2 * tmp23 - 0.284342958e-3 * tmp43 * tmp42;
  double tmp61 = C9 * tmp42 - S9 * (tmp21 + qdot[7]);
  double tmp62 = S9 * tmp42 + C9 * (tmp21 + qdot[7]);
  double tmp63 = C9 * tmp44 - S9 * tmp23 - tmp62 * qdot[9];
  double tmp64 = S9 * tmp44 + C9 * tmp23 + tmp61 * qdot[9];
  double tmp65 = C9 * (tmp46 - 0.221908e0 * tmp50) - S9 * (tmp48 - 0.221908e0 * tmp53);
  double tmp66 = tmp47 - 0.221908e0 * tmp51;
  double tmp67 = S9 * (tmp46 - 0.221908e0 * tmp50) + C9 * (tmp48 - 0.221908e0 * tmp53);
  double tmp77 = 0.1e0 * tmp65;
  double tmp78 = 0.1e0 * tmp66;
  double tmp79 = 0.1e0 * tmp67;
  double tmp80 = 0.4235250000e-3 * tmp63 + 0.4235250000e-3 * tmp62 * (tmp43 + qdot[9]) - tmp62 * (0.8320500000e-3 * tmp43 + 0.8320500000e-3 * qdot[9]);
  double tmp81 = 0.8320500000e-3 * tmp45;
  double tmp82 = 0.4235250000e-3 * tmp64 + tmp61 * (0.8320500000e-3 * tmp43 + 0.8320500000e-3 * qdot[9]) - 0.4235250000e-3 * (tmp43 + qdot[9]) * tmp61;
  double tmp83 = C9 * tmp77 + S9 * tmp79;
  double tmp84 = -S9 * tmp77 + C9 * tmp79;
  double tmp85 = C9 * tmp80 + S9 * tmp82 + 0.221908e0 * tmp78;
  double tmp86 = tmp81 - 0.221908e0 * tmp83;
  double tmp87 = -S9 * tmp80 + C9 * tmp82;
  double tmp88 = tmp46 + tmp83;
  double tmp89 = tmp47 + tmp78;
  double tmp90 = tmp48 + tmp84;
  double tmp91 = tmp58 + tmp85;
  double tmp92 = tmp59 + tmp86;
  double tmp93 = tmp60 + tmp87;
  double tmp94 = C7 * tmp88 - S7 * tmp89;
  double tmp95 = S7 * tmp88 + C7 * tmp89;
  double tmp96 = C7 * tmp91 - S7 * tmp92 + 0.601203e0 * tmp90 + 0.64092e-1 * tmp95;
  double tmp97 = S7 * tmp91 + C7 * tmp92 - 0.64092e-1 * tmp94 + 0.2235e0 * tmp90;
  double tmp98 = tmp93 - 0.2235e0 * tmp95 - 0.601203e0 * tmp94;
  double tmp99 = tmp36 + tmp94;
  double tmp100 = tmp37 + tmp95;
  double tmp101 = tmp38 + tmp90;
  double tmp102 = tmp39 + tmp96;
  double tmp103 = tmp40 + tmp97;
  double tmp104 = tmp41 + tmp98;
  double tmp105 = C8 * (tmp19 + qdot[6]) + S8 * tmp20;
  double tmp106 = -S8 * (tmp19 + qdot[6]) + C8 * tmp20;
  double tmp107 = S8 * tmp22 + tmp106 * qdot[8];
  double tmp108 = C8 * tmp22 - tmp105 * qdot[8];
  double tmp109 = C8 * (tmp24 - 0.2235e0 * tmp32 - 0.601203e0 * tmp34 - 0.64092e-1 * tmp28) + S8 * (tmp25 - 0.2235e0 * tmp27 - 0.601203e0 * tmp30 - 0.64092e-1 * tmp29);
  double tmp110 = -S8 * (tmp24 - 0.2235e0 * tmp32 - 0.601203e0 * tmp34 - 0.64092e-1 * tmp28) + C8 * (tmp25 - 0.2235e0 * tmp27 - 0.601203e0 * tmp30 - 0.64092e-1 * tmp29);
  double tmp111 = tmp26 - 0.2235e0 * tmp33 - 0.601203e0 * tmp35 - 0.64092e-1 * tmp31;
  double tmp113 = tmp108 + (tmp21 + qdot[8]) * tmp105;
  double tmp114 = -tmp107 + (tmp21 + qdot[8]) * tmp106;
  double tmp116 = -tmp106 * tmp106 - tmp105 * tmp105;
  double tmp121 = 0.5937903093e-2 * tmp107 + tmp106 * (0.2928831175e-2 * tmp21 + 0.2928831175e-2 * qdot[8]) - 0.5653560135e-2 * (tmp21 + qdot[8]) * tmp106;
  double tmp122 = 0.5653560135e-2 * tmp108 + 0.5937903093e-2 * (tmp21 + qdot[8]) * tmp105 - tmp105 * (0.2928831175e-2 * tmp21 + 0.2928831175e-2 * qdot[8]);
  double tmp123 = 0.2928831175e-2 * tmp23 - 0.284342958e-3 * tmp106 * tmp105;
  double tmp124 = C10 * tmp105 - S10 * (tmp21 + qdot[8]);
  double tmp125 = S10 * tmp105 + C10 * (tmp21 + qdot[8]);
  double tmp126 = C10 * tmp107 - S10 * tmp23 - tmp125 * qdot[10];
  double tmp127 = S10 * tmp107 + C10 * tmp23 + tmp124 * qdot[10];
  double tmp128 = C10 * (tmp109 - 0.221908e0 * tmp113) - S10 * (tmp111 - 0.221908e0 * tmp116);
  double tmp129 = tmp110 - 0.221908e0 * tmp114;
  double tmp130 = S10 * (tmp109 - 0.221908e0 * tmp113) + C10 * (tmp111 - 0.221908e0 * tmp116);
  double tmp140 = 0.1e0 * tmp128;
  double tmp141 = 0.1e0 * tmp129;
  double tmp142 = 0.1e0 * tmp130;
  double tmp143 = 0.4235250000e-3 * tmp126 + 0.4235250000e-3 * tmp125 * (tmp106 + qdot[10]) - tmp125 * (0.8320500000e-3 * tmp106 + 0.8320500000e-3 * qdot[10]);
  double tmp144 = 0.8320500000e-3 * tmp108;
  double tmp145 = 0.4235250000e-3 * tmp127 + tmp124 * (0.8320500000e-3 * tmp106 + 0.8320500000e-3 * qdot[10]) - 0.4235250000e-3 * (tmp106 + qdot[10]) * tmp124;
  double tmp146 = C10 * tmp140 + S10 * tmp142;
  double tmp147 = -S10 * tmp140 + C10 * tmp142;
  double tmp148 = C10 * tmp143 + S10 * tmp145 + 0.221908e0 * tmp141;
  double tmp149 = tmp144 - 0.221908e0 * tmp146;
  double tmp150 = -S10 * tmp143 + C10 * tmp145;
  double tmp151 = tmp109 + tmp146;
  double tmp152 = tmp110 + tmp141;
  double tmp153 = tmp111 + tmp147;
  double tmp154 = tmp121 + tmp148;
  double tmp155 = tmp122 + tmp149;
  double tmp156 = tmp123 + tmp150;
  double tmp157 = C8 * tmp151 - S8 * tmp152;
  double tmp158 = S8 * tmp151 + C8 * tmp152;
  double tmp159 = C8 * tmp154 - S8 * tmp155 - 0.601203e0 * tmp153 + 0.64092e-1 * tmp158;
  double tmp160 = S8 * tmp154 + C8 * tmp155 - 0.64092e-1 * tmp157 + 0.2235e0 * tmp153;
  double tmp161 = tmp156 - 0.2235e0 * tmp158 + 0.601203e0 * tmp157;
  double tmp162 = tmp99 + tmp157;
  double tmp163 = tmp100 + tmp158;
  double tmp164 = tmp101 + tmp153;
  double tmp165 = tmp102 + tmp159;
  double tmp166 = tmp103 + tmp160;
  double tmp167 = tmp104 + tmp161;
  double tmp168 = C6 * tmp163 - S6 * tmp164;
  double tmp169 = S6 * tmp163 + C6 * tmp164;
  double tmp170 = tmp165 + 0.16375e0 * tmp168;
  double tmp171 = C6 * tmp166 - S6 * tmp167 - 0.16375e0 * tmp162 + 0.41399990000000003e0 * tmp169;
  double tmp172 = S6 * tmp166 + C6 * tmp167 - 0.41399990000000003e0 * tmp168;
  double tmp173 = tmp13 + tmp162;
  double tmp174 = tmp14 + tmp168;
  double tmp175 = tmp15 + tmp169;
  double tmp176 = tmp16 + tmp170;
  double tmp177 = tmp17 + tmp171;
  double tmp178 = tmp18 + tmp172;
  double tmp179 = C11 * (qdot[3] - S4 * qdot[5]) - S11 * (C3 * C4 * qdot[5] - S3 * qdot[4]);
  double tmp180 = C4 * S3 * qdot[5] + C3 * qdot[4];
  double tmp181 = S11 * (qdot[3] - S4 * qdot[5]) + C11 * (C3 * C4 * qdot[5] - S3 * qdot[4]);
  double tmp182 = -tmp181 * qdot[11];
  double tmp183 = tmp179 * qdot[11];
  double tmp184 = C11 * (tmp1 + 0.4025001000e0 * tmp9 + 0.4705e0 * tmp11 - 0.23375e0 * tmp5) - S11 * (tmp3 + 0.4025001000e0 * tmp10 + 0.4705e0 * tmp12 - 0.23375e0 * tmp8);
  double tmp185 = tmp2 + 0.4025001000e0 * tmp4 + 0.4705e0 * tmp7 - 0.23375e0 * tmp6;
  double tmp186 = S11 * (tmp1 + 0.4025001000e0 * tmp9 + 0.4705e0 * tmp11 - 0.23375e0 * tmp5) + C11 * (tmp3 + 0.4025001000e0 * tmp10 + 0.4705e0 * tmp12 - 0.23375e0 * tmp8);
  double tmp187 = tmp183 + (tmp180 + qdot[11]) * tmp179;
  double tmp188 = tmp181 * tmp179;
  double tmp189 = -tmp182 + tmp181 * (tmp180 + qdot[11]);
  double tmp190 = -tmp181 * tmp181 - tmp179 * tmp179;
  double tmp191 = -pow(tmp180 + qdot[11], 2) - tmp179 * tmp179;
  double tmp192 = -tmp181 * tmp181 - pow(tmp180 + qdot[11], 2);
  double tmp193 = tmp181 * tmp179;
  double tmp194 = -tmp183 + (tmp180 + qdot[11]) * tmp179;
  double tmp195 = tmp182 + tmp181 * (tmp180 + qdot[11]);
  double tmp196 = 2 * tmp184;
  double tmp197 = 2 * tmp185;
  double tmp198 = 2 * tmp186;
  double tmp199 = 0.6451466667e-1 * tmp182 + 0.6368550290e-1 * tmp181 * (tmp180 + qdot[11]) - tmp181 * (0.3352169567e-2 * tmp180 + 0.3352169567e-2 * qdot[11]);
  double tmp200 = 0.82916377e-3 * tmp181 * tmp179;
  double tmp201 = 0.6368550290e-1 * tmp183 + tmp179 * (0.3352169567e-2 * tmp180 + 0.3352169567e-2 * qdot[11]) - 0.6451466667e-1 * (tmp180 + qdot[11]) * tmp179;
  double tmp202 = C12 * tmp179 + S12 * (tmp180 + qdot[11]);
  double tmp203 = -S12 * tmp179 + C12 * (tmp180 + qdot[11]);
  double tmp204 = C12 * tmp182 + tmp203 * qdot[12];
  double tmp205 = -S12 * tmp182 - tmp202 * qdot[12];
  double tmp206 = C12 * (tmp184 - 0.32e0 * tmp192 + 0.130703e0 * tmp194 + 0.5908e-2 * tmp188) + S12 * (tmp185 - 0.32e0 * tmp187 + 0.130703e0 * tmp190 + 0.5908e-2 * tmp189);
  double tmp207 = -S12 * (tmp184 - 0.32e0 * tmp192 + 0.130703e0 * tmp194 + 0.5908e-2 * tmp188) + C12 * (tmp185 - 0.32e0 * tmp187 + 0.130703e0 * tmp190 + 0.5908e-2 * tmp189);
  double tmp208 = tmp186 - 0.32e0 * tmp193 + 0.130703e0 * tmp195 + 0.5908e-2 * tmp191;
  double tmp210 = tmp205 + (tmp181 + qdot[12]) * tmp202;
  double tmp211 = -tmp204 + (tmp181 + qdot[12]) * tmp203;
  double tmp213 = -tmp203 * tmp203 - tmp202 * tmp202;
  double tmp218 = 0.5937903093e-2 * tmp204 + tmp203 * (0.2928831175e-2 * tmp181 + 0.2928831175e-2 * qdot[12]) - 0.5653560135e-2 * (tmp181 + qdot[12]) * tmp203;
  double tmp219 = 0.5653560135e-2 * tmp205 + 0.5937903093e-2 * (tmp181 + qdot[12]) * tmp202 - tmp202 * (0.2928831175e-2 * tmp181 + 0.2928831175e-2 * qdot[12]);
  double tmp220 = 0.2928831175e-2 * tmp183 - 0.284342958e-3 * tmp203 * tmp202;
  double tmp221 = C14 * tmp202 - S14 * (tmp181 + qdot[12]);
  double tmp222 = S14 * tmp202 + C14 * (tmp181 + qdot[12]);
  double tmp223 = C14 * tmp204 - S14 * tmp183 - tmp222 * qdot[14];
  double tmp224 = S14 * tmp204 + C14 * tmp183 + tmp221 * qdot[14];
  double tmp225 = C14 * (tmp206 - 0.221908e0 * tmp210) - S14 * (tmp208 - 0.221908e0 * tmp213);
  double tmp226 = tmp207 - 0.221908e0 * tmp211;
  double tmp227 = S14 * (tmp206 - 0.221908e0 * tmp210) + C14 * (tmp208 - 0.221908e0 * tmp213);
  double tmp237 = 0.1e0 * tmp225;
  double tmp238 = 0.1e0 * tmp226;
  double tmp239 = 0.1e0 * tmp227;
  double tmp240 = 0.4235250000e-3 * tmp223 + 0.4235250000e-3 * tmp222 * (tmp203 + qdot[14]) - tmp222 * (0.8320500000e-3 * tmp203 + 0.8320500000e-3 * qdot[14]);
  double tmp241 = 0.8320500000e-3 * tmp205;
  double tmp242 = 0.4235250000e-3 * tmp224 + tmp221 * (0.8320500000e-3 * tmp203 + 0.8320500000e-3 * qdot[14]) - 0.4235250000e-3 * (tmp203 + qdot[14]) * tmp221;
  double tmp243 = C14 * tmp237 + S14 * tmp239;
  double tmp244 = -S14 * tmp237 + C14 * tmp239;
  double tmp245 = C14 * tmp240 + S14 * tmp242 + 0.221908e0 * tmp238;
  double tmp246 = tmp241 - 0.221908e0 * tmp243;
  double tmp247 = -S14 * tmp240 + C14 * tmp242;
  double tmp248 = tmp206 + tmp243;
  double tmp249 = tmp207 + tmp238;
  double tmp250 = tmp208 + tmp244;
  double tmp251 = tmp218 + tmp245;
  double tmp252 = tmp219 + tmp246;
  double tmp253 = tmp220 + tmp247;
  double tmp254 = C12 * tmp248 - S12 * tmp249;
  double tmp255 = S12 * tmp248 + C12 * tmp249;
  double tmp256 = C12 * tmp251 - S12 * tmp252 + 0.130703e0 * tmp250 - 0.5908e-2 * tmp255;
  double tmp257 = S12 * tmp251 + C12 * tmp252 + 0.5908e-2 * tmp254 + 0.32e0 * tmp250;
  double tmp258 = tmp253 - 0.32e0 * tmp255 - 0.130703e0 * tmp254;
  double tmp259 = tmp196 + tmp254;
  double tmp260 = tmp197 + tmp255;
  double tmp261 = tmp198 + tmp250;
  double tmp262 = tmp199 + tmp256;
  double tmp263 = tmp200 + tmp257;
  double tmp264 = tmp201 + tmp258;
  double tmp265 = C13 * tmp179 + S13 * (tmp180 + qdot[11]);
  double tmp266 = -S13 * tmp179 + C13 * (tmp180 + qdot[11]);
  double tmp267 = C13 * tmp182 + tmp266 * qdot[13];
  double tmp268 = -S13 * tmp182 - tmp265 * qdot[13];
  double tmp269 = C13 * (tmp184 + 0.32e0 * tmp192 + 0.130703e0 * tmp194 + 0.5908e-2 * tmp188) + S13 * (tmp185 + 0.32e0 * tmp187 + 0.130703e0 * tmp190 + 0.5908e-2 * tmp189);
  double tmp270 = -S13 * (tmp184 + 0.32e0 * tmp192 + 0.130703e0 * tmp194 + 0.5908e-2 * tmp188) + C13 * (tmp185 + 0.32e0 * tmp187 + 0.130703e0 * tmp190 + 0.5908e-2 * tmp189);
  double tmp271 = tmp186 + 0.32e0 * tmp193 + 0.130703e0 * tmp195 + 0.5908e-2 * tmp191;
  double tmp273 = tmp268 + (tmp181 + qdot[13]) * tmp265;
  double tmp274 = -tmp267 + (tmp181 + qdot[13]) * tmp266;
  double tmp276 = -tmp266 * tmp266 - tmp265 * tmp265;
  double tmp281 = 0.5937903093e-2 * tmp267 + tmp266 * (0.2928831175e-2 * tmp181 + 0.2928831175e-2 * qdot[13]) - 0.5653560135e-2 * (tmp181 + qdot[13]) * tmp266;
  double tmp282 = 0.5653560135e-2 * tmp268 + 0.5937903093e-2 * (tmp181 + qdot[13]) * tmp265 - tmp265 * (0.2928831175e-2 * tmp181 + 0.2928831175e-2 * qdot[13]);
  double tmp283 = 0.2928831175e-2 * tmp183 - 0.284342958e-3 * tmp266 * tmp265;
  double tmp284 = C15 * tmp265 - S15 * (tmp181 + qdot[13]);
  double tmp285 = S15 * tmp265 + C15 * (tmp181 + qdot[13]);
  double tmp286 = C15 * tmp267 - S15 * tmp183 - tmp285 * qdot[15];
  double tmp287 = S15 * tmp267 + C15 * tmp183 + tmp284 * qdot[15];
  double tmp288 = C15 * (tmp269 - 0.221908e0 * tmp273) - S15 * (tmp271 - 0.221908e0 * tmp276);
  double tmp289 = tmp270 - 0.221908e0 * tmp274;
  double tmp290 = S15 * (tmp269 - 0.221908e0 * tmp273) + C15 * (tmp271 - 0.221908e0 * tmp276);
  double tmp300 = 0.1e0 * tmp288;
  double tmp301 = 0.1e0 * tmp289;
  double tmp302 = 0.1e0 * tmp290;
  double tmp303 = 0.4235250000e-3 * tmp286 + 0.4235250000e-3 * tmp285 * (tmp266 + qdot[15]) - tmp285 * (0.8320500000e-3 * tmp266 + 0.8320500000e-3 * qdot[15]);
  double tmp304 = 0.8320500000e-3 * tmp268;
  double tmp305 = 0.4235250000e-3 * tmp287 + tmp284 * (0.8320500000e-3 * tmp266 + 0.8320500000e-3 * qdot[15]) - 0.4235250000e-3 * (tmp266 + qdot[15]) * tmp284;
  double tmp306 = C15 * tmp300 + S15 * tmp302;
  double tmp307 = -S15 * tmp300 + C15 * tmp302;
  double tmp308 = C15 * tmp303 + S15 * tmp305 + 0.221908e0 * tmp301;
  double tmp309 = tmp304 - 0.221908e0 * tmp306;
  double tmp310 = -S15 * tmp303 + C15 * tmp305;
  double tmp311 = tmp269 + tmp306;
  double tmp312 = tmp270 + tmp301;
  double tmp313 = tmp271 + tmp307;
  double tmp314 = tmp281 + tmp308;
  double tmp315 = tmp282 + tmp309;
  double tmp316 = tmp283 + tmp310;
  double tmp317 = C13 * tmp311 - S13 * tmp312;
  double tmp318 = S13 * tmp311 + C13 * tmp312;
  double tmp319 = C13 * tmp314 - S13 * tmp315 + 0.130703e0 * tmp313 - 0.5908e-2 * tmp318;
  double tmp320 = S13 * tmp314 + C13 * tmp315 + 0.5908e-2 * tmp317 - 0.32e0 * tmp313;
  double tmp321 = tmp316 + 0.32e0 * tmp318 - 0.130703e0 * tmp317;
  double tmp322 = tmp259 + tmp317;
  double tmp323 = tmp260 + tmp318;
  double tmp324 = tmp261 + tmp313;
  double tmp325 = tmp262 + tmp319;
  double tmp326 = tmp263 + tmp320;
  double tmp327 = tmp264 + tmp321;
  double tmp328 = C11 * tmp322 + S11 * tmp324;
  double tmp329 = -S11 * tmp322 + C11 * tmp324;
  double tmp330 = C11 * tmp325 + S11 * tmp327 + 0.4705e0 * tmp329 + 0.23375e0 * tmp323;
  double tmp331 = tmp326 - 0.23375e0 * tmp328 - 0.40250009999999997e0 * tmp329;
  double tmp332 = -S11 * tmp325 + C11 * tmp327 + 0.40250009999999997e0 * tmp323 - 0.4705e0 * tmp328;
  double tmp333 = tmp173 + tmp328;
  double tmp334 = tmp174 + tmp323;
  double tmp335 = tmp175 + tmp329;
  double tmp336 = tmp176 + tmp330;
  double tmp337 = tmp177 + tmp331;
  double tmp338 = tmp178 + tmp332;
  double tmp339 = C16 * (qdot[3] - S4 * qdot[5]) - S16 * (C3 * C4 * qdot[5] - S3 * qdot[4]);
  double tmp340 = C4 * S3 * qdot[5] + C3 * qdot[4];
  double tmp341 = S16 * (qdot[3] - S4 * qdot[5]) + C16 * (C3 * C4 * qdot[5] - S3 * qdot[4]);
  double tmp342 = -tmp341 * qdot[16];
  double tmp343 = tmp339 * qdot[16];
  double tmp344 = C16 * (tmp1 + 0.4025001000e0 * tmp9 - 0.4705e0 * tmp11 - 0.23375e0 * tmp5) - S16 * (tmp3 + 0.4025001000e0 * tmp10 - 0.4705e0 * tmp12 - 0.23375e0 * tmp8);
  double tmp345 = tmp2 + 0.4025001000e0 * tmp4 - 0.4705e0 * tmp7 - 0.23375e0 * tmp6;
  double tmp346 = S16 * (tmp1 + 0.4025001000e0 * tmp9 - 0.4705e0 * tmp11 - 0.23375e0 * tmp5) + C16 * (tmp3 + 0.4025001000e0 * tmp10 - 0.4705e0 * tmp12 - 0.23375e0 * tmp8);
  double tmp347 = tmp343 + (tmp340 + qdot[16]) * tmp339;
  double tmp348 = tmp341 * tmp339;
  double tmp349 = -tmp342 + tmp341 * (tmp340 + qdot[16]);
  double tmp350 = -tmp341 * tmp341 - tmp339 * tmp339;
  double tmp351 = -pow(tmp340 + qdot[16], 2) - tmp339 * tmp339;
  double tmp352 = -tmp341 * tmp341 - pow(tmp340 + qdot[16], 2);
  double tmp353 = tmp341 * tmp339;
  double tmp354 = -tmp343 + (tmp340 + qdot[16]) * tmp339;
  double tmp355 = tmp342 + tmp341 * (tmp340 + qdot[16]);
  double tmp356 = 2 * tmp344;
  double tmp357 = 2 * tmp345;
  double tmp358 = 2 * tmp346;
  double tmp359 = 0.6451466667e-1 * tmp342 + 0.6368550290e-1 * tmp341 * (tmp340 + qdot[16]) - tmp341 * (0.3352169567e-2 * tmp340 + 0.3352169567e-2 * qdot[16]);
  double tmp360 = 0.82916377e-3 * tmp341 * tmp339;
  double tmp361 = 0.6368550290e-1 * tmp343 + tmp339 * (0.3352169567e-2 * tmp340 + 0.3352169567e-2 * qdot[16]) - 0.6451466667e-1 * (tmp340 + qdot[16]) * tmp339;
  double tmp362 = C17 * tmp339 + S17 * (tmp340 + qdot[16]);
  double tmp363 = -S17 * tmp339 + C17 * (tmp340 + qdot[16]);
  double tmp364 = C17 * tmp342 + tmp363 * qdot[17];
  double tmp365 = -S17 * tmp342 - tmp362 * qdot[17];
  double tmp366 = C17 * (tmp344 - 0.32e0 * tmp352 - 0.130703e0 * tmp354 + 0.5908e-2 * tmp348) + S17 * (tmp345 - 0.32e0 * tmp347 - 0.130703e0 * tmp350 + 0.5908e-2 * tmp349);
  double tmp367 = -S17 * (tmp344 - 0.32e0 * tmp352 - 0.130703e0 * tmp354 + 0.5908e-2 * tmp348) + C17 * (tmp345 - 0.32e0 * tmp347 - 0.130703e0 * tmp350 + 0.5908e-2 * tmp349);
  double tmp368 = tmp346 - 0.32e0 * tmp353 - 0.130703e0 * tmp355 + 0.5908e-2 * tmp351;
  double tmp370 = tmp365 + (tmp341 + qdot[17]) * tmp362;
  double tmp371 = -tmp364 + (tmp341 + qdot[17]) * tmp363;
  double tmp373 = -tmp363 * tmp363 - tmp362 * tmp362;
  double tmp378 = 0.5937903093e-2 * tmp364 + tmp363 * (0.2928831175e-2 * tmp341 + 0.2928831175e-2 * qdot[17]) - 0.5653560135e-2 * (tmp341 + qdot[17]) * tmp363;
  double tmp379 = 0.5653560135e-2 * tmp365 + 0.5937903093e-2 * (tmp341 + qdot[17]) * tmp362 - tmp362 * (0.2928831175e-2 * tmp341 + 0.2928831175e-2 * qdot[17]);
  double tmp380 = 0.2928831175e-2 * tmp343 - 0.284342958e-3 * tmp363 * tmp362;
  double tmp381 = C19 * tmp362 - S19 * (tmp341 + qdot[17]);
  double tmp382 = S19 * tmp362 + C19 * (tmp341 + qdot[17]);
  double tmp383 = C19 * tmp364 - S19 * tmp343 - tmp382 * qdot[19];
  double tmp384 = S19 * tmp364 + C19 * tmp343 + tmp381 * qdot[19];
  double tmp385 = C19 * (tmp366 - 0.221908e0 * tmp370) - S19 * (tmp368 - 0.221908e0 * tmp373);
  double tmp386 = tmp367 - 0.221908e0 * tmp371;
  double tmp387 = S19 * (tmp366 - 0.221908e0 * tmp370) + C19 * (tmp368 - 0.221908e0 * tmp373);
  double tmp397 = 0.1e0 * tmp385;
  double tmp398 = 0.1e0 * tmp386;
  double tmp399 = 0.1e0 * tmp387;
  double tmp400 = 0.4235250000e-3 * tmp383 + 0.4235250000e-3 * tmp382 * (tmp363 + qdot[19]) - tmp382 * (0.8320500000e-3 * tmp363 + 0.8320500000e-3 * qdot[19]);
  double tmp401 = 0.8320500000e-3 * tmp365;
  double tmp402 = 0.4235250000e-3 * tmp384 + tmp381 * (0.8320500000e-3 * tmp363 + 0.8320500000e-3 * qdot[19]) - 0.4235250000e-3 * (tmp363 + qdot[19]) * tmp381;
  double tmp403 = C19 * tmp397 + S19 * tmp399;
  double tmp404 = -S19 * tmp397 + C19 * tmp399;
  double tmp405 = C19 * tmp400 + S19 * tmp402 + 0.221908e0 * tmp398;
  double tmp406 = tmp401 - 0.221908e0 * tmp403;
  double tmp407 = -S19 * tmp400 + C19 * tmp402;
  double tmp408 = tmp366 + tmp403;
  double tmp409 = tmp367 + tmp398;
  double tmp410 = tmp368 + tmp404;
  double tmp411 = tmp378 + tmp405;
  double tmp412 = tmp379 + tmp406;
  double tmp413 = tmp380 + tmp407;
  double tmp414 = C17 * tmp408 - S17 * tmp409;
  double tmp415 = S17 * tmp408 + C17 * tmp409;
  double tmp416 = C17 * tmp411 - S17 * tmp412 - 0.130703e0 * tmp410 - 0.5908e-2 * tmp415;
  double tmp417 = S17 * tmp411 + C17 * tmp412 + 0.5908e-2 * tmp414 + 0.32e0 * tmp410;
  double tmp418 = tmp413 - 0.32e0 * tmp415 + 0.130703e0 * tmp414;
  double tmp419 = tmp356 + tmp414;
  double tmp420 = tmp357 + tmp415;
  double tmp421 = tmp358 + tmp410;
  double tmp422 = tmp359 + tmp416;
  double tmp423 = tmp360 + tmp417;
  double tmp424 = tmp361 + tmp418;
  double tmp425 = C18 * tmp339 + S18 * (tmp340 + qdot[16]);
  double tmp426 = -S18 * tmp339 + C18 * (tmp340 + qdot[16]);
  double tmp427 = C18 * tmp342 + tmp426 * qdot[18];
  double tmp428 = -S18 * tmp342 - tmp425 * qdot[18];
  double tmp429 = C18 * (tmp344 + 0.32e0 * tmp352 - 0.130703e0 * tmp354 + 0.5908e-2 * tmp348) + S18 * (tmp345 + 0.32e0 * tmp347 - 0.130703e0 * tmp350 + 0.5908e-2 * tmp349);
  double tmp430 = -S18 * (tmp344 + 0.32e0 * tmp352 - 0.130703e0 * tmp354 + 0.5908e-2 * tmp348) + C18 * (tmp345 + 0.32e0 * tmp347 - 0.130703e0 * tmp350 + 0.5908e-2 * tmp349);
  double tmp431 = tmp346 + 0.32e0 * tmp353 - 0.130703e0 * tmp355 + 0.5908e-2 * tmp351;
  double tmp433 = tmp428 + (tmp341 + qdot[18]) * tmp425;
  double tmp434 = -tmp427 + (tmp341 + qdot[18]) * tmp426;
  double tmp436 = -tmp426 * tmp426 - tmp425 * tmp425;
  double tmp441 = 0.5937903093e-2 * tmp427 + tmp426 * (0.2928831175e-2 * tmp341 + 0.2928831175e-2 * qdot[18]) - 0.5653560135e-2 * (tmp341 + qdot[18]) * tmp426;
  double tmp442 = 0.5653560135e-2 * tmp428 + 0.5937903093e-2 * (tmp341 + qdot[18]) * tmp425 - tmp425 * (0.2928831175e-2 * tmp341 + 0.2928831175e-2 * qdot[18]);
  double tmp443 = 0.2928831175e-2 * tmp343 - 0.284342958e-3 * tmp426 * tmp425;
  double tmp444 = C20 * tmp425 - S20 * (tmp341 + qdot[18]);
  double tmp445 = S20 * tmp425 + C20 * (tmp341 + qdot[18]);
  double tmp446 = C20 * tmp427 - S20 * tmp343 - tmp445 * qdot[20];
  double tmp447 = S20 * tmp427 + C20 * tmp343 + tmp444 * qdot[20];
  double tmp448 = C20 * (tmp429 - 0.221908e0 * tmp433) - S20 * (tmp431 - 0.221908e0 * tmp436);
  double tmp449 = tmp430 - 0.221908e0 * tmp434;
  double tmp450 = S20 * (tmp429 - 0.221908e0 * tmp433) + C20 * (tmp431 - 0.221908e0 * tmp436);
  double tmp460 = 0.1e0 * tmp448;
  double tmp461 = 0.1e0 * tmp449;
  double tmp462 = 0.1e0 * tmp450;
  double tmp463 = 0.4235250000e-3 * tmp446 + 0.4235250000e-3 * tmp445 * (tmp426 + qdot[20]) - tmp445 * (0.8320500000e-3 * tmp426 + 0.8320500000e-3 * qdot[20]);
  double tmp464 = 0.8320500000e-3 * tmp428;
  double tmp465 = 0.4235250000e-3 * tmp447 + tmp444 * (0.8320500000e-3 * tmp426 + 0.8320500000e-3 * qdot[20]) - 0.4235250000e-3 * (tmp426 + qdot[20]) * tmp444;
  double tmp466 = C20 * tmp460 + S20 * tmp462;
  double tmp467 = -S20 * tmp460 + C20 * tmp462;
  double tmp468 = C20 * tmp463 + S20 * tmp465 + 0.221908e0 * tmp461;
  double tmp469 = tmp464 - 0.221908e0 * tmp466;
  double tmp470 = -S20 * tmp463 + C20 * tmp465;
  double tmp471 = tmp429 + tmp466;
  double tmp472 = tmp430 + tmp461;
  double tmp473 = tmp431 + tmp467;
  double tmp474 = tmp441 + tmp468;
  double tmp475 = tmp442 + tmp469;
  double tmp476 = tmp443 + tmp470;
  double tmp477 = C18 * tmp471 - S18 * tmp472;
  double tmp478 = S18 * tmp471 + C18 * tmp472;
  double tmp479 = C18 * tmp474 - S18 * tmp475 - 0.130703e0 * tmp473 - 0.5908e-2 * tmp478;
  double tmp480 = S18 * tmp474 + C18 * tmp475 + 0.5908e-2 * tmp477 - 0.32e0 * tmp473;
  double tmp481 = tmp476 + 0.32e0 * tmp478 + 0.130703e0 * tmp477;
  double tmp482 = tmp419 + tmp477;
  double tmp483 = tmp420 + tmp478;
  double tmp484 = tmp421 + tmp473;
  double tmp485 = tmp422 + tmp479;
  double tmp486 = tmp423 + tmp480;
  double tmp487 = tmp424 + tmp481;
  double tmp488 = C16 * tmp482 + S16 * tmp484;
  double tmp489 = -S16 * tmp482 + C16 * tmp484;
  double tmp490 = C16 * tmp485 + S16 * tmp487 - 0.4705e0 * tmp489 + 0.23375e0 * tmp483;
  double tmp491 = tmp486 - 0.23375e0 * tmp488 - 0.40250009999999997e0 * tmp489;
  double tmp492 = -S16 * tmp485 + C16 * tmp487 + 0.40250009999999997e0 * tmp483 + 0.4705e0 * tmp488;
  double tmp493 = tmp333 + tmp488;
  double tmp494 = tmp334 + tmp483;
  double tmp495 = tmp335 + tmp489;
  double tmp496 = tmp336 + tmp490;
  double tmp497 = tmp337 + tmp491;
  double tmp498 = tmp338 + tmp492;
  double tmp499 = C4 * C5 * tmp493 + (S3 * S4 * C5 - C3 * S5) * tmp494 + (C3 * S4 * C5 + S3 * S5) * tmp495;
  double tmp500 = C4 * S5 * tmp493 + (S3 * S4 * S5 + C3 * C5) * tmp494 + (C3 * S4 * S5 - S3 * C5) * tmp495;
  double tmp501 = -S4 * tmp493 + S3 * C4 * tmp494 + C3 * C4 * tmp495;
  double tmp502 = C3 * tmp497 - S3 * tmp498;
  double tmp503 = -S4 * tmp496 + S3 * C4 * tmp497 + C3 * C4 * tmp498;
  N[0] = tmp499;
  N[1] = tmp500;
  N[2] = tmp501;
  N[3] = tmp496;
  N[4] = tmp502;
  N[5] = tmp503;
  N[6] = tmp165;
  N[7] = tmp93;
  N[8] = tmp156;
  N[9] = tmp81;
  N[10] = tmp144;
  N[11] = tmp326;
  N[12] = tmp253;
  N[13] = tmp316;
  N[14] = tmp241;
  N[15] = tmp304;
  N[16] = tmp486;
  N[17] = tmp413;
  N[18] = tmp476;
  N[19] = tmp401;
  N[20] = tmp464;
}
