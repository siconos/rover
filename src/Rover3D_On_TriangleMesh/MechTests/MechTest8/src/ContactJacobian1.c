#include "LagrangianModel.h"
void ContactJacobian1(CJ,q)
double CJ[18];
double q[6];
{
  {
    CJ[0] = 1.0;
    CJ[1] = 0.0;
    CJ[2] = 0.0;
    CJ[3] = 0.0;
    CJ[4] = 1.0;
    CJ[5] = 0.0;
    CJ[6] = 0.0;
    CJ[7] = 0.0;
    CJ[8] = 1.0;
    CJ[9] = 0.0;
    CJ[10] = 0.0;
    CJ[11] = 0.0;
    CJ[12] = 0.0;
    CJ[13] = 0.0;
    CJ[14] = 0.0;
    CJ[15] = 0.0;
    CJ[16] = 0.0;
    CJ[17] = 0.0;
    return;
  }
}

