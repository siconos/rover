#include "LagrangianModel.h"
void Tags(T,q)
double T[6];
double q[6];
{
  {
    T[0] = q[0];
    T[1] = T[0];
    T[2] = q[1];
    T[3] = T[2];
    T[4] = q[2];
    T[5] = T[4];
    return;
  }
}

