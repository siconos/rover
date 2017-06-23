#include <math.h>
#include "LagrangianModel.h"

void NLEffects(N, q, qdot)
double N[6];
double q[6];
double qdot[6];
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
  double tmp1 = 0.981e1 * C4 * S5;
  double tmp2 = 0.981e1 * S3 * S4 * S5 + 0.981e1 * C3 * C5;
  double tmp3 = 0.981e1 * C3 * S4 * S5 - 0.981e1 * S3 * C5;
  double tmp13 = 14 * tmp1;
  double tmp14 = 14 * tmp2;
  double tmp15 = 14 * tmp3;
  double tmp16 = (C4 * S3 * qdot[5] + C3 * qdot[4]) * (3150 * C3 * C4 * qdot[5] - 3150 * S3 * qdot[4]) - (C3 * C4 * qdot[5] - S3 * qdot[4]) * (6300 * C4 * S3 * qdot[5] + 6300 * C3 * qdot[4]);
  double tmp17 = (C3 * C4 * qdot[5] - S3 * qdot[4]) * (3150 * qdot[3] - 3150 * S4 * qdot[5]) - (qdot[3] - S4 * qdot[5]) * (3150 * C3 * C4 * qdot[5] - 3150 * S3 * qdot[4]);
  double tmp18 = (qdot[3] - S4 * qdot[5]) * (6300 * C4 * S3 * qdot[5] + 6300 * C3 * qdot[4]) - (C4 * S3 * qdot[5] + C3 * qdot[4]) * (3150 * qdot[3] - 3150 * S4 * qdot[5]);
  double tmp19 = C4 * C5 * tmp13 + (S3 * S4 * C5 - C3 * S5) * tmp14 + (C3 * S4 * C5 + S3 * S5) * tmp15;
  double tmp20 = C4 * S5 * tmp13 + (S3 * S4 * S5 + C3 * C5) * tmp14 + (C3 * S4 * S5 - S3 * C5) * tmp15;
  double tmp21 = -tmp13 * S4 + S3 * C4 * tmp14 + C3 * C4 * tmp15;
  double tmp22 = C3 * tmp17 - S3 * tmp18;
  double tmp23 = -S4 * tmp16 + S3 * C4 * tmp17 + C3 * C4 * tmp18;
  N[0] = tmp19;
  N[1] = tmp20;
  N[2] = tmp21;
  N[3] = tmp16;
  N[4] = tmp22;
  N[5] = tmp23;
}
