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
#include "op3x3.h"
#include "Rover3DWheelFixedSphereR.hpp"

using namespace std;

Rover3DWheelFixedSphereR::Rover3DWheelFixedSphereR(int wheelMark, double r, double A, double B, double C, double wheelRad)
: LagrangianScleronomousR(), sphereRad(r), tireRad(wheelRad), tireMark(wheelMark), sphCenter(3)

{
  
  sphCenter.setValue(0, A);
  sphCenter.setValue(1, B);
  sphCenter.setValue(2, C);

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

  //contact point coordinate

  SiconosVector cPoint(3);

  //normal to the wheel plane

  SiconosVector nWheel(3);

  //vector from sphere center to the contact point
  SiconosVector sphCp(3); 

  //vector from sphere center to wheel plane
  SiconosVector AB(3);

  //coords of point on the wheel plane along AB
  SiconosVector B(3);

  SiconosVector DB(3);

  SiconosVector C(3);

  //distance from the sphere's center to the plane of the wheel

  double d;

  //Calculate the distance for each wheel
  
  for(int i = 0; i < 6; ++i)
  {

    //contact point in cartesian space

    cPoint.setValue(0, tags[(i*3)]);
    cPoint.setValue(1, tags[(i*3) + 1]);
    cPoint.setValue(2, tags[(i*3) + 2]);

    nWheel.setValue(0, norms[(i*3)]);
    nWheel.setValue(1, norms[(i*3) + 1]);
    nWheel.setValue(2, norms[(i*3) + 2]);

    //we calculate the distance from sphere's center to the wheel plane

    sub(nWheel, cPoint, nWheel);

    sub(sphCenter, cPoint, sphCp);

    d = inner_prod(nWheel, sphCp);

    scal(-1, nWheel, nWheel);

    scal(d, nWheel, AB);

    add(sphCenter, AB, B); 

    //we calculate contact point coodinates

    sub(B, cPoint, DB);

    scal(1/DB.norm2(), DB, DB);

    scal(tireRad, DB, DB);

    add(cPoint, DB, C);

    //distance

    sub(C, sphCenter, C);

    distance[i] = C.norm2() - sphereRad;

    //distance[i] = sqrt(pow(C.x - x, 2) + pow(C.y - y, 2) + pow(C.z - z, 2)) - sphereRad;

    //cout <<"distance " << i << " :" << endl;
    //cout << distance[i] << endl;

  }

}

void Rover3DWheelFixedSphereR::computeh(double, Interaction& inter)
{
  double * tmpQ = &(*inter.data(q0))(0);  
  double yValue;

  double distance[6];

  for(int i = 0; i < 21; i++)
  {
    tmpQ[i] = (*inter.data(q0))(i);
  }

  yValue = 1000000;

  Distance(distance, tmpQ);

  if(distance[tireMark] < yValue)
  {

    yValue = distance[tireMark];

  }

  SP::SiconosVector y = inter.y(0);

  y->setValue(0,yValue);

}

void Rover3DWheelFixedSphereR::computeJachq(double, Interaction& inter)
{

  double tmp[63];
  double *tmpQ = &(*inter.data(q0))(0); 

  SimpleMatrix orthoBase(3,3);

  double TT[69];

  double tags[18];

  Tags(TT, tmpQ);

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

  //contact point coordinate

  SiconosVector cPoint(3);

  //normal to the wheel plane

  SiconosVector nWheel(3);

  //vector from sphere center to the contact point
  SiconosVector sphCp(3); 

  //vector from sphere center to wheel plane
  SiconosVector AB(3);

  //coords of point on the wheel plane along AB
  SiconosVector B(3);

  SiconosVector DB(3);

  SiconosVector C(3);

  SimpleMatrix baseTrans(3, 3);

  double d;

  double A1x, A1y, A1z;

  SimpleMatrix J(3, 21);

  SimpleMatrix *g = (SimpleMatrix *)_jachq.get();

  switch(tireMark)
  {

  case 0:

    ContactJacobian1(tmp, tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }

    //contact point in cartesian space

    cPoint.setValue(0, tags[0]);
    cPoint.setValue(1, tags[1]);
    cPoint.setValue(2, tags[2]);

    nWheel.setValue(0, norms[0]);
    nWheel.setValue(1, norms[1]);
    nWheel.setValue(2, norms[2]);

    //we calculate the distance from sphere's center to the wheel plane

    sub(nWheel, cPoint, nWheel);

    sub(sphCenter, cPoint, sphCp);

    d = inner_prod(nWheel, sphCp);

    scal(-1, nWheel, nWheel);

    scal(d, nWheel, AB);

    add(sphCenter, AB, B); 

    //we calculate contact point coodinates

    sub(B, cPoint, DB);

    scal(1/DB.norm2(), DB, DB);

    scal(tireRad, DB, DB);

    add(cPoint, DB, C);

    //normal

    sub(C, sphCenter, C);

    scal(1/C.norm2(), C, C);

    //orthobase

    orthoBase(0,0) = C.getValue(0);
    orthoBase(0,1) = C.getValue(1);
    orthoBase(0,2) = C.getValue(2);
    
    orthoBaseFromVector(&orthoBase(0,0), &orthoBase(0,1), &orthoBase(0,2), &orthoBase(1,0), &orthoBase(1,1),
                      &orthoBase(1,2), &orthoBase(2,0), &orthoBase(2,1), &orthoBase(2,2));

    baseTrans = orthoBase;

    //swapping x and y axes

    A1x = baseTrans.getValue(1, 0);
    A1y = baseTrans.getValue(1, 1);
    A1z = baseTrans.getValue(1, 2);

    baseTrans.setValue(1, 0, baseTrans.getValue(2, 0));
    baseTrans.setValue(1, 1, baseTrans.getValue(2, 1));
    baseTrans.setValue(1, 2, baseTrans.getValue(2, 2));

    baseTrans.setValue(2, 0, A1x);
    baseTrans.setValue(2, 1, A1y);
    baseTrans.setValue(2, 2, A1z);

    ////

    prod(baseTrans, (*g), (*g));    

    (*g)(28%3,28/3) = (*g)(28%3,28/3)+tireRad;

    break;

  case 1:

    ContactJacobian2(tmp, tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }

    //contact point in cartesian space

    cPoint.setValue(0, tags[3]);
    cPoint.setValue(1, tags[4]);
    cPoint.setValue(2, tags[5]);

    nWheel.setValue(0, norms[3]);
    nWheel.setValue(1, norms[4]);
    nWheel.setValue(2, norms[5]);

    //we calculate the distance from sphere's center to the wheel plane

    sub(nWheel, cPoint, nWheel);

    sub(sphCenter, cPoint, sphCp);

    d = inner_prod(nWheel, sphCp);

    scal(-1, nWheel, nWheel);

    scal(d, nWheel, AB);

    add(sphCenter, AB, B); 

    //we calculate contact point coodinates

    sub(B, cPoint, DB);

    scal(1/DB.norm2(), DB, DB);

    scal(tireRad, DB, DB);

    add(cPoint, DB, C);

    //normal

    sub(C, sphCenter, C);

    scal(1/C.norm2(), C, C);

    //orthobase

    orthoBase(0,0) = C.getValue(0);
    orthoBase(0,1) = C.getValue(1);
    orthoBase(0,2) = C.getValue(2);
    
    orthoBaseFromVector(&orthoBase(0,0), &orthoBase(0,1), &orthoBase(0,2), &orthoBase(1,0), &orthoBase(1,1),
                      &orthoBase(1,2), &orthoBase(2,0), &orthoBase(2,1), &orthoBase(2,2));

    baseTrans = orthoBase;

    //swapping x and y axes

    A1x = baseTrans.getValue(1, 0);
    A1y = baseTrans.getValue(1, 1);
    A1z = baseTrans.getValue(1, 2);

    baseTrans.setValue(1, 0, baseTrans.getValue(2, 0));
    baseTrans.setValue(1, 1, baseTrans.getValue(2, 1));
    baseTrans.setValue(1, 2, baseTrans.getValue(2, 2));

    baseTrans.setValue(2, 0, A1x);
    baseTrans.setValue(2, 1, A1y);
    baseTrans.setValue(2, 2, A1z);

    ////

    prod(baseTrans, (*g), (*g));    

    (*g)(31%3,31/3) = (*g)(31%3,31/3)+tireRad;
    break;

  case 2:

    ContactJacobian3(tmp, tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }

    //contact point in cartesian space

    cPoint.setValue(0, tags[6]);
    cPoint.setValue(1, tags[7]);
    cPoint.setValue(2, tags[8]);

    nWheel.setValue(0, norms[6]);
    nWheel.setValue(1, norms[7]);
    nWheel.setValue(2, norms[8]);

    //we calculate the distance from sphere's center to the wheel plane

    sub(nWheel, cPoint, nWheel);

    sub(sphCenter, cPoint, sphCp);

    d = inner_prod(nWheel, sphCp);

    scal(-1, nWheel, nWheel);

    scal(d, nWheel, AB);

    add(sphCenter, AB, B); 

    //we calculate contact point coodinates

    sub(B, cPoint, DB);

    scal(1/DB.norm2(), DB, DB);

    scal(tireRad, DB, DB);

    add(cPoint, DB, C);

    //normal

    sub(C, sphCenter, C);

    scal(1/C.norm2(), C, C);

    //orthobase

    orthoBase(0,0) = C.getValue(0);
    orthoBase(0,1) = C.getValue(1);
    orthoBase(0,2) = C.getValue(2);
    
    orthoBaseFromVector(&orthoBase(0,0), &orthoBase(0,1), &orthoBase(0,2), &orthoBase(1,0), &orthoBase(1,1),
                      &orthoBase(1,2), &orthoBase(2,0), &orthoBase(2,1), &orthoBase(2,2));

    baseTrans = orthoBase;

    //swapping x and y axes

    A1x = baseTrans.getValue(1, 0);
    A1y = baseTrans.getValue(1, 1);
    A1z = baseTrans.getValue(1, 2);

    baseTrans.setValue(1, 0, baseTrans.getValue(2, 0));
    baseTrans.setValue(1, 1, baseTrans.getValue(2, 1));
    baseTrans.setValue(1, 2, baseTrans.getValue(2, 2));

    baseTrans.setValue(2, 0, A1x);
    baseTrans.setValue(2, 1, A1y);
    baseTrans.setValue(2, 2, A1z);

    ////

    prod(baseTrans, (*g), (*g));    

    (*g)(43%3,43/3) = (*g)(43%3,43/3)+tireRad;
    break;

  case 3:

    ContactJacobian4(tmp, tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }

    //contact point in cartesian space

    cPoint.setValue(0, tags[9]);
    cPoint.setValue(1, tags[10]);
    cPoint.setValue(2, tags[11]);

    nWheel.setValue(0, norms[9]);
    nWheel.setValue(1, norms[10]);
    nWheel.setValue(2, norms[11]);

    //we calculate the distance from sphere's center to the wheel plane

    sub(nWheel, cPoint, nWheel);

    sub(sphCenter, cPoint, sphCp);

    d = inner_prod(nWheel, sphCp);

    scal(-1, nWheel, nWheel);

    scal(d, nWheel, AB);

    add(sphCenter, AB, B); 

    //we calculate contact point coodinates

    sub(B, cPoint, DB);

    scal(1/DB.norm2(), DB, DB);

    scal(tireRad, DB, DB);

    add(cPoint, DB, C);

    //normal

    sub(C, sphCenter, C);

    scal(1/C.norm2(), C, C);

    //orthobase

    orthoBase(0,0) = C.getValue(0);
    orthoBase(0,1) = C.getValue(1);
    orthoBase(0,2) = C.getValue(2);
    
    orthoBaseFromVector(&orthoBase(0,0), &orthoBase(0,1), &orthoBase(0,2), &orthoBase(1,0), &orthoBase(1,1),
                      &orthoBase(1,2), &orthoBase(2,0), &orthoBase(2,1), &orthoBase(2,2));

    baseTrans = orthoBase;

    //swapping x and y axes

    A1x = baseTrans.getValue(1, 0);
    A1y = baseTrans.getValue(1, 1);
    A1z = baseTrans.getValue(1, 2);

    baseTrans.setValue(1, 0, baseTrans.getValue(2, 0));
    baseTrans.setValue(1, 1, baseTrans.getValue(2, 1));
    baseTrans.setValue(1, 2, baseTrans.getValue(2, 2));

    baseTrans.setValue(2, 0, A1x);
    baseTrans.setValue(2, 1, A1y);
    baseTrans.setValue(2, 2, A1z);

    ////

    prod(baseTrans, (*g), (*g));    

    (*g)(46%3,46/3) = (*g)(46%3,46/3)+tireRad;
    break;

  case 4:

    ContactJacobian5(tmp, tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }

    //contact point in cartesian space

    cPoint.setValue(0, tags[12]);
    cPoint.setValue(1, tags[13]);
    cPoint.setValue(2, tags[14]);

    nWheel.setValue(0, norms[12]);
    nWheel.setValue(1, norms[13]);
    nWheel.setValue(2, norms[14]);

    //we calculate the distance from sphere's center to the wheel plane

    sub(nWheel, cPoint, nWheel);

    sub(sphCenter, cPoint, sphCp);

    d = inner_prod(nWheel, sphCp);

    scal(-1, nWheel, nWheel);

    scal(d, nWheel, AB);

    add(sphCenter, AB, B); 

    //we calculate contact point coodinates

    sub(B, cPoint, DB);

    scal(1/DB.norm2(), DB, DB);

    scal(tireRad, DB, DB);

    add(cPoint, DB, C);

    //normal

    sub(C, sphCenter, C);

    scal(1/C.norm2(), C, C);

    //orthobase

    orthoBase(0,0) = C.getValue(0);
    orthoBase(0,1) = C.getValue(1);
    orthoBase(0,2) = C.getValue(2);
    
    orthoBaseFromVector(&orthoBase(0,0), &orthoBase(0,1), &orthoBase(0,2), &orthoBase(1,0), &orthoBase(1,1),
                      &orthoBase(1,2), &orthoBase(2,0), &orthoBase(2,1), &orthoBase(2,2));

    baseTrans = orthoBase;

    //swapping x and y axes

    A1x = baseTrans.getValue(1, 0);
    A1y = baseTrans.getValue(1, 1);
    A1z = baseTrans.getValue(1, 2);

    baseTrans.setValue(1, 0, baseTrans.getValue(2, 0));
    baseTrans.setValue(1, 1, baseTrans.getValue(2, 1));
    baseTrans.setValue(1, 2, baseTrans.getValue(2, 2));

    baseTrans.setValue(2, 0, A1x);
    baseTrans.setValue(2, 1, A1y);
    baseTrans.setValue(2, 2, A1z);

    ////

    prod(baseTrans, (*g), (*g));    

    (*g)(58%3,58/3) = (*g)(58%3,58/3)+tireRad;
    break;

  case 5:

    ContactJacobian6(tmp, tmpQ);  //(double *)data[q0].get());
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }

    //contact point in cartesian space

    cPoint.setValue(0, tags[15]);
    cPoint.setValue(1, tags[16]);
    cPoint.setValue(2, tags[17]);

    nWheel.setValue(0, norms[15]);
    nWheel.setValue(1, norms[16]);
    nWheel.setValue(2, norms[17]);

    //we calculate the distance from sphere's center to the wheel plane

    sub(nWheel, cPoint, nWheel);

    sub(sphCenter, cPoint, sphCp);

    d = inner_prod(nWheel, sphCp);

    scal(-1, nWheel, nWheel);

    scal(d, nWheel, AB);

    add(sphCenter, AB, B); 

    //we calculate contact point coodinates

    sub(B, cPoint, DB);

    scal(1/DB.norm2(), DB, DB);

    scal(tireRad, DB, DB);

    add(cPoint, DB, C);

    //normal

    sub(C, sphCenter, C);

    scal(1/C.norm2(), C, C);

    //orthobase

    orthoBase(0,0) = C.getValue(0);
    orthoBase(0,1) = C.getValue(1);
    orthoBase(0,2) = C.getValue(2);
    
    orthoBaseFromVector(&orthoBase(0,0), &orthoBase(0,1), &orthoBase(0,2), &orthoBase(1,0), &orthoBase(1,1),
                      &orthoBase(1,2), &orthoBase(2,0), &orthoBase(2,1), &orthoBase(2,2));

    baseTrans = orthoBase;

    //swapping x and y axes

    A1x = baseTrans.getValue(1, 0);
    A1y = baseTrans.getValue(1, 1);
    A1z = baseTrans.getValue(1, 2);

    baseTrans.setValue(1, 0, baseTrans.getValue(2, 0));
    baseTrans.setValue(1, 1, baseTrans.getValue(2, 1));
    baseTrans.setValue(1, 2, baseTrans.getValue(2, 2));

    baseTrans.setValue(2, 0, A1x);
    baseTrans.setValue(2, 1, A1y);
    baseTrans.setValue(2, 2, A1z);

    ////

    prod(baseTrans, (*g), (*g));    

    (*g)(61%3,61/3) = (*g)(61%3,61/3)+tireRad;
    break;

  default:
    cout << "Please specify correct number of Wheel" << endl;

  }

}

