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
 * Relation Implementation of Rover3DWheelFixedTriangleR.hpp
 * Author: Jan Michalczyk
 * Team: Bipop
 */

#include "Robot.h"
#include <stdio.h>
#include <cmath>
#include "Rover3DWheelFixedTriangleR.hpp"
#include "SiconosMatrix.hpp"
#include "SiconosVector.hpp"
#include "SimpleMatrix.hpp"
#include "SiconosVectorFriends.hpp"
#include "SiconosAlgebra.hpp"
#include <fstream>
#include <vector>
#include <algorithm>

#include "op3x3.h"

#define PI 3.14159

using namespace std;

double Rover3DWheelFixedTriangleR::dotProd(vect A, vect B)
{

  double tmp;

  tmp = A.x*B.x + A.y*B.y + A.z*B.z;

  return tmp;

}

vect Rover3DWheelFixedTriangleR::crossProd(vect A, vect B)
{

  vect tmp;

  tmp.x = (A.y*B.z) - (B.y*A.z);
  tmp.y = (B.x*A.z) - (A.x*B.z);
  tmp.z = (A.x*B.y) - (A.y*B.x);

  return tmp;

}

double Rover3DWheelFixedTriangleR::distFromSegment(vect P, vect A, vect B)
{

  //from: http://geomalgorithms.com/a02-_lines.html - very neat

  vect AB = B - A;
  vect AP = P - A;

  AB.norm();

  vect tmp = crossProd(AB, AP);
    
  double lengthFin = sqrt(pow(tmp.x, 2) + pow(tmp.y, 2) + pow(tmp.z, 2));

  return lengthFin;

}

Rover3DWheelFixedTriangleR::Rover3DWheelFixedTriangleR(double Ax , double Ay, double Az, double Bx , double By, double Bz, double Cx , double Cy, double Cz, int WheelMark, double WheelRadius)
: LagrangianScleronomousR(), vert1(Ax, Ay, Az), vert2(Bx, By, Bz), vert3(Cx, Cy, Cz), orthoBase(3,3)
{
  
  TireRadius = WheelRadius;
  TireMark = WheelMark;

  ///////////////////////////////////////////////////////////////////////////////

  //getting plane equation coeffs A, B, C and D

  //Plane coeffs - normal vector (A, B, C)
    
  A = (vert2.y - vert1.y)*(vert3.z - vert1.z) - (vert3.y - vert1.y)*(vert2.z - vert1.z); 
  B = (vert2.z - vert1.z)*(vert3.x - vert1.x) - (vert3.z - vert1.z)*(vert2.x - vert1.x);
  C = (vert2.x - vert1.x)*(vert3.y - vert1.y) - (vert3.x - vert1.x)*(vert2.y - vert1.y);
  D = -(A*(vert1.x) + B*(vert1.y) + C*(vert1.z));

  //plane flipping - if plane's nomal is pointing downwards - can be because of the cross product

  if(B < 0){

    A = -A;
    B = -B;
    C = -C;
    D = -D;

  }

  ///////////////////////////////////////////////////////////////////////////////

  //normal unit vector to the plane 
 
  //getting the normalized right-handed frame located in vertex 1 

  vect ab, ac;

  //axes

  vect axz, axy, axx;

  ab = vert2 - vert1;
  ac = vert3 - vert1;
  
  //axy cannot have zero magintude as a result of triangulation (ab and ac can't be parallel)

  axy = crossProd(ac, ab);
  
  //axis flipping - if normal's pointing downwards

  axy.norm();

  if(axy.y < 0){

    axy.flip();

  }

  //3x3 orthobase

  orthoBase(0,0) = axy.x;
  orthoBase(1,0) = axy.y;
  orthoBase(2,0) = axy.z;

  n.x = orthoBase(0,0);
  n.y = orthoBase(1,0);
  n.z = orthoBase(2,0);

  orthoBaseFromVector(&orthoBase(0,0), &orthoBase(1,0), &orthoBase(2,0), &orthoBase(0,1), &orthoBase(1,1),
                      &orthoBase(2,1), &orthoBase(0,2), &orthoBase(1,2), &orthoBase(2,2));

}

double Rover3DWheelFixedTriangleR::fcnMin(double a, double b)
{

  return ((a < b) ? a : b);

}

double Rover3DWheelFixedTriangleR::fcnMax(double a, double b)
{

  return ((a > b) ? a : b);

}

bool Rover3DWheelFixedTriangleR::checkIfSameSideOfEdge(vect P1, vect P2, vect A, vect B)
{

  vect cp1, cp2, tmp1, tmp2, tmp3;

  tmp1 = B - A;
  tmp2 = P1 - A;
  tmp3 = P2 - A;

  cp1 = crossProd(tmp1, tmp2);
  cp2 = crossProd(tmp1, tmp3);

  // >= replaced by > (in this way segments are outside triangles)

  if(dotProd(cp1,cp2) >= 0)
  {
  
    return true;

  }
  else
  {

    return false;
 
  }

}

bool Rover3DWheelFixedTriangleR::checkIfInsideTriangle(vect P)
{

  vect A, B, C;

  A = vert1;
  B = vert2;
  C = vert3;

  if(checkIfSameSideOfEdge(P, A, B, C) && checkIfSameSideOfEdge(P, B, A, C) && checkIfSameSideOfEdge(P, C, A, B))
  {

    return true;

  }
  else
  {

    return false;

  }

}

bool Rover3DWheelFixedTriangleR::checkIfInsideSegment(vect P, vect A, vect B)
{

  vect AB = B - A;
 
  vect AP = P - A;
  
  double length = sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2) + pow(B.z - A.z, 2));

  double test = dotProd(AB, AP)/length;

  if((test > 0) && (test < length)){

    return true;

  }
  else{

    return false;

  }
   
}

void Rover3DWheelFixedTriangleR::calcDistance(double* dist, double* q)
{
 
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
  tags[14] = TT[60];  //MR
  tags[15] = TT[15];
  tags[16] = TT[38];
  tags[17] = TT[61];  //BR

  //Q is a contact point on a wheel projected onto a plane

  vect P, Q;

  //Calculate the distance for each wheel

  //DEBUG/////////////////////////////////////////////////

  switch(TireMark)
  {

  case 0:

    Pj.x = tags[TireMark];
    Pj.y = tags[TireMark + 1];
    Pj.z = tags[TireMark + 2];

    Pj.x = Pj.x - dotProd((Pj - vert1), n)*n.x;
    Pj.y = Pj.y - dotProd((Pj - vert1), n)*n.y;
    Pj.z = Pj.z - dotProd((Pj - vert1), n)*n.z;

    break;

  case 1:

    Pj.x = tags[TireMark + 2];
    Pj.y = tags[TireMark + 3];
    Pj.z = tags[TireMark + 4];

    Pj.x = Pj.x - dotProd((Pj - vert1), n)*n.x;
    Pj.y = Pj.y - dotProd((Pj - vert1), n)*n.y;
    Pj.z = Pj.z - dotProd((Pj - vert1), n)*n.z;
    
    break;

  case 2:

    Pj.x = tags[TireMark + 4];
    Pj.y = tags[TireMark + 5];
    Pj.z = tags[TireMark + 6];

    Pj.x = Pj.x - dotProd((Pj - vert1), n)*n.x;
    Pj.y = Pj.y - dotProd((Pj - vert1), n)*n.y;
    Pj.z = Pj.z - dotProd((Pj - vert1), n)*n.z;
  
    break;

  case 3:

    Pj.x = tags[TireMark + 6];
    Pj.y = tags[TireMark + 7];
    Pj.z = tags[TireMark + 8];

    Pj.x = Pj.x - dotProd((Pj - vert1), n)*n.x;
    Pj.y = Pj.y - dotProd((Pj - vert1), n)*n.y;
    Pj.z = Pj.z - dotProd((Pj - vert1), n)*n.z;
     
    break;

  case 4:

    Pj.x = tags[TireMark + 8];
    Pj.y = tags[TireMark + 9];
    Pj.z = tags[TireMark + 10];

    Pj.x = Pj.x - dotProd((Pj - vert1), n)*n.x;
    Pj.y = Pj.y - dotProd((Pj - vert1), n)*n.y;
    Pj.z = Pj.z - dotProd((Pj - vert1), n)*n.z;
          
    break;

  case 5:

    Pj.x = tags[TireMark + 10];
    Pj.y = tags[TireMark + 11];
    Pj.z = tags[TireMark + 12];

    Pj.x = Pj.x - dotProd((Pj - vert1), n)*n.x;
    Pj.y = Pj.y - dotProd((Pj - vert1), n)*n.y;
    Pj.z = Pj.z - dotProd((Pj - vert1), n)*n.z;
      
    break;

  default:

    cout << "Please specify correct number of wheels" << endl;

  }

  //DEBUG/////////////////////////////////////////////////
  
  for(int i = 0; i < 6; ++i)
  {
   
    //project point on the plane and check if the projection lies inside the triangle

    //contact point in cartesian space - passage from HUMANS convention included
    
    P.x = tags[(i*3)];
    P.y = tags[(i*3) + 1];
    P.z = tags[(i*3) + 2];

    //projection on the plane

    //Q.x = P.x - A*((A*P.x + B*P.y + C*P.z + D)/(pow(A,2) + pow(B,2) + pow(C,2)));
    //Q.y = P.y - B*((A*P.x + B*P.y + C*P.z + D)/(pow(A,2) + pow(B,2) + pow(C,2)));
    //Q.z = P.z - C*((A*P.x + B*P.y + C*P.z + D)/(pow(A,2) + pow(B,2) + pow(C,2)));
    
    Q.x = P.x - dotProd((P - vert1), n)*n.x;
    Q.y = P.y - dotProd((P - vert1), n)*n.y;
    Q.z = P.z - dotProd((P - vert1), n)*n.z;

  //DEBUG/////////////////////////////////////////////////

    /*switch(TireMark)
    {

    case 0:

      Pj = Q;
      
      break;

    case 1:

      Pj = Q;
    
      break;

    case 2:

      Pj = Q;
  
      break;

    case 3:

      Pj = Q;
     
      break;

    case 4:

      Pj = Q;
          
      break;

    case 5:

      Pj = Q;
      
      break;

    default:

      cout << "Please specify correct number of wheels" << endl;

    }*/

  //DEBUG/////////////////////////////////////////////////


    if(checkIfInsideTriangle(Q))
    {  

      //calculate the distance between the plane and the point
    
      double l = dotProd(n, P - vert1);

      dist[i] = l - TireRadius;
      //cout << "distance triangle:" << " " << TireMark  << " " << (l - TireRadius) << endl;
    }
    else if(checkIfInsideSegment(Q, vert1, vert2) || checkIfInsideSegment(Q, vert1, vert3) || checkIfInsideSegment(Q, vert2, vert3))
    {

      //where distances from segments will be stored

      vector<double> distanceV;
      vector<double>::const_iterator it; 
      
      if(checkIfInsideSegment(Q, vert1, vert2)){

        double di1 = distFromSegment(P, vert1, vert2);
        distanceV.push_back(di1);
      
      }

      if(checkIfInsideSegment(Q, vert1, vert3)){

        double di2 = distFromSegment(P, vert1, vert3);
        distanceV.push_back(di2);
      
      }

      if(checkIfInsideSegment(Q, vert2, vert3)){

        double di3 = distFromSegment(P, vert2, vert3);
        distanceV.push_back(di3);
      
      }
       
      it = min_element(distanceV.begin(), distanceV.end());

      dist[i] = *it - TireRadius;        
      //cout << "distance segment:" << " " << TireMark  << " " << (*it - TireRadius) << endl;
    }
    else 
    {

      //where distances from vertices will be stored

      vector<double> distanceVertex;
      vector<double>::const_iterator iter; 
        
      //point is outside the  segments and triangle - we get as distance the minimum of the distances from vertices

      double dis1 = sqrt(pow(P.x - vert1.x, 2) + pow(P.y - vert1.y, 2) +  pow(P.z - vert1.z, 2));
      distanceVertex.push_back(dis1);

      double dis2 = sqrt(pow(P.x - vert2.x, 2) + pow(P.y - vert2.y, 2) +  pow(P.z - vert2.z, 2));
      distanceVertex.push_back(dis2);

      double dis3 = sqrt(pow(P.x - vert3.x, 2) + pow(P.y - vert3.y, 2) +  pow(P.z - vert3.z, 2));
      distanceVertex.push_back(dis3);
    
      iter = min_element(distanceVertex.begin(), distanceVertex.end());
      
      dist[i] = *iter - TireRadius;

    }

  }
  
}

void Rover3DWheelFixedTriangleR::computeh(const double time, Interaction& inter)
{
  
  double * tmpQ = &(*inter.data(q0))(0);  
  double yValue; 

  double tmp[6];
  
  for(int i = 0; i < 21; i++)
  {
    
    tmpQ[i] = (*inter.data(q0))(i);
  }
 
  yValue = 100000;

  calcDistance(tmp, tmpQ);

  if(tmp[TireMark] < yValue)
  {

    yValue = tmp[TireMark];
  
  }

  SP::SiconosVector y = inter.y(0);

  //cout << "distance " << TireMark << " : " << yValue << endl;

  y->setValue(0,yValue);
  
};

void Rover3DWheelFixedTriangleR::computeJachq(const double time, Interaction& inter)
{

  //Calculating the coordinate frame in the contact point - rotation matrix
  //is given by the normalized axis of the coord. frame. It's
  //stored as a class member as Euler angles in eul[3]

  Qj.x = Pj.x - dotProd((Pj - vert1), n)*n.x;
  Qj.y = Pj.y - dotProd((Pj - vert1), n)*n.y;
  Qj.z = Pj.z - dotProd((Pj - vert1), n)*n.z;
    
  double tmp[63];
  
  double *tmpQ = &(*inter.data(q0))(0); 
  
  SimpleMatrix *g = (SimpleMatrix *)_jachq.get();

  SimpleMatrix baseTrans(orthoBase);

  SimpleMatrix altRotation(3,3);

  altRotation.setValue(0,0,0.707);
  altRotation.setValue(0,1,-0.707);
  altRotation.setValue(0,2,0);
  altRotation.setValue(1,0,0.707);
  altRotation.setValue(1,1,0.707);
  altRotation.setValue(1,2,0);
  altRotation.setValue(2,0,0);
  altRotation.setValue(2,1,0);
  altRotation.setValue(2,2,1);

  altRotation.trans();

  baseTrans.trans();

  SimpleMatrix J(3, 21);

  if(!checkIfInsideTriangle(Qj)){

    switch(TireMark)
    {

    case 0:

      ContactJacobian1(tmp, tmpQ);  
      for(int i=0 ; i<63; i++)
      {
        (*g)(i%3,i/3) = tmp[i];
      }

      prod(altRotation, baseTrans, baseTrans);

      prod(baseTrans, (*g), (*g));

      (*g)(28%3,28/3) = (*g)(28%3,28/3)+TireRadius;

      break;

    case 1:

      ContactJacobian2(tmp, tmpQ);  
      for(int i=0 ; i<63; i++)
      {
        (*g)(i%3,i/3) = tmp[i];
      }

      prod(altRotation, baseTrans, baseTrans);

      prod(baseTrans, (*g), (*g));

      (*g)(31%3,31/3) = (*g)(31%3,31/3)+TireRadius;
    
      break;


    case 2:

      ContactJacobian3(tmp, tmpQ);  
      for(int i=0 ; i<63; i++)
      {
        (*g)(i%3,i/3) = tmp[i];
      }

      prod(altRotation, baseTrans, baseTrans);

      prod(baseTrans, (*g), (*g));

      (*g)(43%3,43/3) = (*g)(43%3,43/3)+TireRadius;
    
      break;


    case 3:

      ContactJacobian4(tmp, tmpQ);  
      for(int i=0 ; i<63; i++)
      {
        (*g)(i%3,i/3) = tmp[i];
      }

      prod(altRotation, baseTrans, baseTrans);

      prod(baseTrans, (*g), (*g));

      (*g)(46%3,46/3) = (*g)(46%3,46/3)+TireRadius;
     
      break;

    case 4:

      ContactJacobian5(tmp, tmpQ);  
      for(int i=0 ; i<63; i++)
      {
        (*g)(i%3,i/3) = tmp[i];
      }

      prod(altRotation, baseTrans, baseTrans);

      prod(baseTrans, (*g), (*g));

      (*g)(58%3,58/3) = (*g)(58%3,58/3)+TireRadius;
          
      break;


    case 5:

      ContactJacobian6(tmp, tmpQ);  
      for(int i=0 ; i<63; i++)
      {
        (*g)(i%3,i/3) = tmp[i];
      }

      prod(altRotation, baseTrans, baseTrans);

      prod(baseTrans, (*g), (*g));

      (*g)(61%3,61/3) = (*g)(61%3,61/3)+TireRadius;
      
      break;

    default:

      cout << "Please specify correct number of wheels" << endl;

    }

  }
  else {
    
    switch(TireMark)
    {

    case 0:

      ContactJacobian1(tmp, tmpQ);  
      for(int i=0 ; i<63; i++)
      {
        (*g)(i%3,i/3) = tmp[i];
      }

      prod(baseTrans, (*g), (*g));    

      (*g)(28%3,28/3) = (*g)(28%3,28/3)+TireRadius;

      break;

    case 1:

      ContactJacobian2(tmp, tmpQ);  
      for(int i=0 ; i<63; i++)
      {
        (*g)(i%3,i/3) = tmp[i];
      }

      prod(baseTrans, (*g), (*g));    

      (*g)(31%3,31/3) = (*g)(31%3,31/3)+TireRadius;
    
      break;


    case 2:

      ContactJacobian3(tmp, tmpQ);  
      for(int i=0 ; i<63; i++)
      {
        (*g)(i%3,i/3) = tmp[i];
      }

      prod(baseTrans, (*g), (*g));    

      (*g)(43%3,43/3) = (*g)(43%3,43/3)+TireRadius;
    
      break;


    case 3:

      ContactJacobian4(tmp, tmpQ);  
      for(int i=0 ; i<63; i++)
      {
        (*g)(i%3,i/3) = tmp[i];
      }

      prod(baseTrans, (*g), (*g));    

      (*g)(46%3,46/3) = (*g)(46%3,46/3)+TireRadius;
     
      break;

    case 4:

      ContactJacobian5(tmp, tmpQ);  
      for(int i=0 ; i<63; i++)
      {
        (*g)(i%3,i/3) = tmp[i];
      }

      prod(baseTrans, (*g), (*g));    

      (*g)(58%3,58/3) = (*g)(58%3,58/3)+TireRadius;
          
      break;


    case 5:

      ContactJacobian6(tmp, tmpQ);  
      for(int i=0 ; i<63; i++)
      {
        (*g)(i%3,i/3) = tmp[i];
      }

      prod(baseTrans, (*g), (*g));    

      (*g)(61%3,61/3) = (*g)(61%3,61/3)+TireRadius;
      
      break;

    default:

      cout << "Please specify correct number of wheels" << endl;

    }
  }
}

