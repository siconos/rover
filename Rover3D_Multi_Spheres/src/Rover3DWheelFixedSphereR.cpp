/* Siconos-Example version 3.0.0, Copyright INRIA 2005-2010.
 * Siconos is a program dedicated to modeling, simulation and control
 * of non smooth dynamical systems.
 * Siconos is a free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * Siconos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Siconos; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth FLOOR, Boston, MA  02110-1301  USA
 *
 * Contact: Vincent ACARY, siconos-team@lists.gforge.inria.fr
 *
 * Relation Class for Rover3D
 * Author: Jianhui YANG
 * Team: Bipop
 */




#include "Robot.h"
#include <stdio.h>
#include <math.h>
#include "Rover3DWheelFixedSphereR.hpp"
using namespace std;


//  Test code for Wheel FL (the first wheel)

Rover3DWheelFixedSphereR::Rover3DWheelFixedSphereR(int WheelMark, double r, double A, double B, double C, double WheelR, double thickness)
  : LagrangianScleronomousR(), r(r), A(A), B(B), C(C)

{
  x = A;
  y = B;
  z = C;
  sphereR = r;
  TireR = WheelR;
  TireMark = WheelMark;
  TireT = thickness;
  NCont = 20; // Number of "Contact point" for the approximation of minimized distance.
}


/*
double Rover3DWheeelFixedSphereR::distance(double x, double y, double z, double rad)
{
  double yValue;
  double * tmp = (double *)malloc(NCONT*sizeof(double));
  double * tmpAngle = (double *)malloc(4*sizeof(double));
  tmpAngle[0] = x;
  tmpAngle[1] = y;
  tmpAngle[2] = z;
  tmpAngle[3] = r;
  Distance(tmp, tmpAngle,(double *)q);
  yValue = tmp[0]-12.5;
  //cout << "y[0]= " << tmp[0]-12.5 << endl;
   free(tmp);
   free(tmpAngle);

  return (yValue);
}                                 */


void Rover3DWheelFixedSphereR::computeh(double, Interaction& inter)
{
  double * tmpQ = &(*inter.data(q0))(0);  //(double *)malloc(21*sizeof(double));
  double yValue;

  double tmp[6];
  double tmpAngle[4];
  for(int i=0; i<21; i++)
  {
    tmpQ[i] = (*inter.data(q0))(i);
  }
  tmpAngle[0] = x; // coordinated data of Fixed Sphere
  tmpAngle[1] = y;
  tmpAngle[2] = z;
  tmpAngle[3] = sphereR; //radius of Fixed Sphere
  yValue = 1000000;
  for(int i=0; i<NCont+1; i++)
  {
    Distance(tmp,-TireT/2+i*(TireT/2/NCont),tmpAngle,tmpQ);
    if(tmp[TireMark] < yValue)
    {
      yValue = tmp[TireMark];
    }

  }// Find the shortest distance between the wheel and the spheres.
  // Details could be found in the Chapter5 of the report



  SP::SiconosVector y = inter.y(0);

  y->setValue(0,yValue);

};

void normalize(SP::SiconosVector, unsigned int);

void Rover3DWheelFixedSphereR::computeJachq(double, Interaction& inter)
{

  //FL
  double tmpAngle[4];
  double tmp[63];
  double *tmpQ = &(*inter.data(q0))(0); // (double *)malloc(21*sizeof(double));
  //for (int i=0; i<21; i++)
  //  {tmpQ[i] = (*data[q0])(i);}


  //double * tmp = (double *)malloc(63*sizeof(double));
  //double * tmpAngle = (double *)malloc(4*sizeof(double));
  tmpAngle[0] = x;
  tmpAngle[1] = y;
  tmpAngle[2] = z;
  tmpAngle[3] = sphereR;
  //cout << y << endl;

  SimpleMatrix *g = (SimpleMatrix *)_jachq.get();

  switch(TireMark)
  {
  case 0:

    ContactJacobian1(tmp,tmpAngle,tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }
    (*g)(28%3,28/3) = (*g)(28%3,28/3)+TireR;
    break;

  case 1:

    ContactJacobian2(tmp,tmpAngle,tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }
    (*g)(31%3,31/3) = (*g)(31%3,31/3)+TireR;
    break;


  case 2:

    ContactJacobian3(tmp,tmpAngle,tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }
    (*g)(43%3,43/3) = (*g)(43%3,43/3)+TireR;
    break;


  case 3:

    ContactJacobian4(tmp,tmpAngle,tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }
    (*g)(46%3,46/3) = (*g)(46%3,46/3)+TireR;
    break;

  case 4:

    ContactJacobian5(tmp,tmpAngle,tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }
    (*g)(58%3,58/3) = (*g)(58%3,58/3)+TireR;
    break;


  case 5:

    ContactJacobian6(tmp,tmpAngle,tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }
    (*g)(61%3,61/3) = (*g)(61%3,61/3)+TireR;
    break;

  default:
    cout << "Please specify correct number of Wheel" << endl;

  }

  //free (tmpQ);
  //free(tmpAngle);
  //free(tmp);
}

