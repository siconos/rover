//function to convert from rotation matrix to cardan ZYX representation.

#include <iostream>
#include <cmath>

#define PI 3.1415

using namespace std;

void toEuler(vect a, vect b, vect c, double* p){

  double beta = asin(a.z);

  double alphasin = asin((-b.z)/cos(beta));
  double alphacos = acos((c.z)/cos(beta));

  if(alphacos > PI/2


  double alphasin = asin((-b.z)/cos(beta));
  double alphacos = acos((c.z)/cos(beta));



}

int main(){





}
