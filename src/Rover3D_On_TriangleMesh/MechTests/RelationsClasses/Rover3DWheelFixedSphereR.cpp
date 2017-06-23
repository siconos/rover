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

//auxiliary vector class

class vect
{
 
  public:
    
    double x, y, z;
    
    vect()
    {

      x = 0;
      y = 0;
      z = 0;

    }

    vect(double a, double b, double c)
    {
      
      x = a;
      y = b;
      z = c;
      
    }

    vect& operator=(const vect & templ)
    {

      if(&templ == this)
      {

        return *this;

      }
      
      x = templ.x;
      y = templ.y;
      z = templ.z;

      return *this;

    }

    vect operator-(vect temp)
    {
     
      vect res;
       
      res.x = x - temp.x;
      res.y = y - temp.y;
      res.z = z - temp.z;

      return res;

    }

    vect& operator*(double temp)
    {
               
      x = x*temp;
      y = y*temp;
      z = z*temp;

      return *this;

    }

    vect operator+(vect temp)
    {
     
      vect res;
       
      res.x = x + temp.x;
      res.y = y + temp.y;
      res.z = z + temp.z;

      return res;

    }


    vect(const vect & templ)
    {

      x = templ.x;
      y = templ.y;
      z = templ.z;
    
    }

    void norm()
    {
      
      double l = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
      
      if(l > 0)
      {

      x = x/l;
      y = y/l;
      z = z/l;

      }
    
    }

  void flip()
  {

    x = -x;
    y = -y;
    z = -z;

  }

};

double Rover3DWheelFixedSphereR::dotProd(vect A, vect B)
{

  double tmp;

  tmp = A.x*B.x + A.y*B.y + A.z*B.z;

  return tmp;

}

vect Rover3DWheelFixedSphereR::crossProd(vect A, vect B)
{

  vect tmp;

  tmp.x = (A.y*B.z) - (B.y*A.z);
  tmp.y = (B.x*A.z) - (A.x*B.z);
  tmp.z = (A.x*B.y) - (A.y*B.x);

  return tmp;

}

Rover3DWheelFixedSphereR::Rover3DWheelFixedSphereR(int WheelMark, double r, double A, double B, double C, double WheelR)
  : LagrangianScleronomousR(), sphereR(r), x(A), y(B), z(C)

{
  x = A;
  y = B;
  z = C;
  sphereR = r;
  TireR = WheelR;
  TireMark = WheelMark;
}

void Rover3DWheelFixedSphereR::Distance(double* distance, double* q){

  //get the contact points in cartesian space

  double TT[69];

  double tags[18];

  Tags(TT, q);

  tags[0] = TT[4];
  tags[1] = TT[27];
  tags[2] = TT[50];   //FL
  tags[3] = TT[5];
  tags[4] = TT[28];
  tags[5] = TT[51];   //FR
  tags[6] = TT[9];
  tags[7] = TT[32];
  tags[8] = TT[55];   //ML
  tags[9] = TT[10];
  tags[10] = TT[33];
  tags[11] = TT[56];  //BL
  tags[12] = TT[14];
  tags[13] = TT[37];
  tags[14] = TT[60];  //BR
  tags[15] = TT[15];
  tags[16] = TT[38];
  tags[17] = TT[61];  //MR

  //normal vectors of wheels as tags

  double norms[18];

  norms[0] = TT[16];
  norms[1] = TT[39];
  norms[2] = TT[62];   //FL
  norms[3] = TT[17];
  norms[4] = TT[40];
  norms[5] = TT[63];   //FR
  norms[6] = TT[18];
  norms[7] = TT[41];
  norms[8] = TT[64];   //ML
  norms[9] = TT[19];
  norms[10] = TT[42];
  norms[11] = TT[65];  //BL
  norms[12] = TT[20];
  norms[13] = TT[43];
  norms[14] = TT[66];  //BR
  norms[15] = TT[21];
  norms[16] = TT[44];
  norms[17] = TT[67];  //MR

  //contact point coodinate

  vect D, Dnorm;

  //normal to the wheel plane

  vect P;

  //distance from the sphere's center to the plane of the wheel

  double d;

  vect AB, B;

  vect DB, DC;

  //contact point

  vect C;

  vect sphCentr(x, y, z);

  //Calculate the distance for each wheel
  
  for(int i = 0; i < 6; ++i)
  {

    //contact point in cartesian space
    
    D.x = tags[(i*3)];
    D.y = tags[(i*3) + 1];
    D.z = tags[(i*3) + 2];

    P.x = norms[(i*3)];
    P.y = norms[(i*3) + 1];
    P.z = norms[(i*3) + 2];

    //we calculate the distance from sphere's center to the wheel plane

    Dnorm = P;
    Dnorm.norm();

    //d = dotProd(Dnorm, sphCentr - D);

    d = dotProd(Dnorm, D - sphCentr);

    P.norm();

    P.flip();
    AB = P*d;

    B.x = x + AB.x; 
    B.y = y + AB.y;
    B.z = z + AB.z;

    //we calculate contact point coodinates

    DB.x = B.x - D.x;
    DB.y = B.y - D.y;
    DB.z = B.z - D.z;    

    DB.norm();

    DC.x = DB.x*TireR;
    DC.y = DB.y*TireR;
    DC.z = DB.z*TireR;

    C.x = D.x + DC.x;
    C.y = D.y + DC.y;
    C.z = D.z + DC.z;

    //distance

    distance[i] = sqrt(pow(C.x - x, 2) + pow(C.y - y, 2) + pow(C.z - z, 2)) - sphereR;

    //cout <<"distance " << i << " :" << endl;
    //cout << distance[i] << endl;

  }

}

void Rover3DWheelFixedSphereR::computeh(double, Interaction& inter)
{
  double * tmpQ = &(*inter.data(q0))(0);  
  double yValue;

  double distance[6];
  double tmpAngle[4];

  for(int i=0; i<21; i++)
  {
    tmpQ[i] = (*inter.data(q0))(i);
  }

  //sphere coords and radius

  tmpAngle[0] = x; 
  tmpAngle[1] = y;
  tmpAngle[2] = z;
  tmpAngle[3] = sphereR; 

  yValue = 1000000;

  Distance(distance, tmpQ);

  if(distance[TireMark] < yValue)
  {

    yValue = distance[TireMark];

  }

  SP::SiconosVector y = inter.y(0);

  y->setValue(0,yValue);

}

void normalize(SP::SiconosVector, unsigned int);

void Rover3DWheelFixedSphereR::computeJachq(double, Interaction& inter)
{

  double tmpAngle[4];
  double tmp[63];
  double *tmpQ = &(*inter.data(q0))(0); 

  tmpAngle[0] = x;
  tmpAngle[1] = y;
  tmpAngle[2] = z;
  tmpAngle[3] = sphereR;

  SimpleMatrix *g = (SimpleMatrix *)_jachq.get();

  switch(TireMark)
  {
  case 0:

    ContactJacobian1s(tmp,tmpAngle,tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }
    (*g)(28%3,28/3) = (*g)(28%3,28/3)+TireR;
    break;

  case 1:

    ContactJacobian2s(tmp,tmpAngle,tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }
    (*g)(31%3,31/3) = (*g)(31%3,31/3)+TireR;
    break;


  case 2:

    ContactJacobian3s(tmp,tmpAngle,tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }
    (*g)(43%3,43/3) = (*g)(43%3,43/3)+TireR;
    break;


  case 3:

    ContactJacobian4s(tmp,tmpAngle,tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }
    (*g)(46%3,46/3) = (*g)(46%3,46/3)+TireR;
    break;

  case 4:

    ContactJacobian5s(tmp,tmpAngle,tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }
    (*g)(58%3,58/3) = (*g)(58%3,58/3)+TireR;
    break;


  case 5:

    ContactJacobian6s(tmp,tmpAngle,tmpQ);  //(double *)data[q0].get());
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

