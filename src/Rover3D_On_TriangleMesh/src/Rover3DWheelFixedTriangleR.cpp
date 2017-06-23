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
  : LagrangianScleronomousR(), vert1(Ax, Ay, Az), vert2(Bx, By, Bz), vert3(Cx, Cy, Cz)
{
 
  //constructor called only with three points and wheel parameters
  //calculation of a local plane frame
  //calculation of a plane equation
  //conversion of the local plane from rotation matrix into euler angles
  
  TireRadius = WheelRadius;
  TireMark = WheelMark;

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

  if(axy.y < 0){

    axy.flip();
   
    axx = crossProd(axy, ab);
   
    axz = ab;
  
  }else{
    
    axx = crossProd(axy, ac);
   
    axz = ac;

  }

  //orthonormal basis

  axy.norm();  
  axz.norm();
  axx.norm();

  n.x = axy.x;
  n.y = axy.y;
  n.z = axy.z;
  n.norm();
  
  /* 

          |axx.x axy.x axz.x|
    rot = |axx.y axy.y axz.y|
          |axx.z axy.z axz.z|

  */

  if((axx.z < 0.998) && (axx.z > -0.998)){
    
    eul[1] = atan2(-axx.z, sqrt(pow(axx.x, 2) + pow(axx.y, 2)));
    eul[0] = atan2((axy.z/cos(eul[1])), (axz.z/cos(eul[1])));
    eul[2] = atan2((axx.y/cos(eul[1])), (axx.x/cos(eul[1])));
  
  }
  else{

    eul[2] = 0;
    
    if(axx.z == -1){

      eul[1] = PI/2;
      eul[0] = atan2(axy.x, axy.y);
      

    }
    else{

      eul[1] = -PI/2;
      eul[0] = -atan2(axy.x, axy.y);

    }

  }

  cout << "euler angles: " << endl;
  cout << eul[0] << " " << eul[1] << " " << eul[2] << endl;
  
  cout << "Normal " << endl;
  cout << n.x << " " << n.y << " " << n.z << endl;

  cout << "rot. matrices: " << endl;
  cout << "[ " << axx.x  << " " << axy.x << " " << axz.x << " ]" << endl;
  cout << "[ " << axx.y  << " " << axy.y << " " << axz.y << " ]" << endl;
  cout << "[ " << axx.z  << " " << axy.z << " " << axz.z << " ]" << endl;  

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

  //cout << " FL :" << norms[0] << " " << norms[1] << " " << norms[2] << endl;
  //cout << " FR :" << norms[3] << " " << norms[4] << " " << norms[5] << endl;
  //cout << " rad: " << TireRadius << endl;
  //cout << " normal*rad :" << GE.x << " " << GE.y << " " << GE.z << endl;

  //Q is a contact point on a wheel projected onto a plane

  vect Q, P, Ds;

  vect m, t, nn;

  vect GE;

  //contact point

  vect Contact;

  //Calculate the distance for each wheel
  
  for(int i = 0; i < 6; ++i)
  {
   
    //normal vectors of the wheel

    Ds.x = norms[(i*3)];
    Ds.y = norms[(i*3) + 1];
    Ds.z = norms[(i*3) + 2];
 
    //project point on the plane and check if the projection lies inside the triangle

    //contact point in cartesian space - passage from HUMANS convention included
    
    P.x = tags[(i*3)];
    P.y = tags[(i*3) + 1];
    P.z = tags[(i*3) + 2];
 
    //calculate the contact point coords//////////////////////////////////////

    //get vector m in the direction of motion of the wheel

    Ds.norm();

    m = crossProd(n, Ds);

    m.norm();

    t = m;

    nn = crossProd(Ds, t);
    
    nn.norm();

    //vector nn gets changed because of the way * is overloaded in the class

    nn.flip();
    GE = nn*TireRadius;

    Contact = P + GE;
    
    Q.x = Contact.x - dotProd((Contact - vert1), n)*n.x;
    Q.y = Contact.y - dotProd((Contact - vert1), n)*n.y;
    Q.z = Contact.z - dotProd((Contact - vert1), n)*n.z;
   
    /////////////////////////////////////////////////////////////////////////
   
    if(checkIfInsideTriangle(Q))
    {  

      double l = dotProd(Contact - vert1, n);

      dist[i] = l;
      
    }
    else if(checkIfInsideSegment(Q, vert1, vert2) || checkIfInsideSegment(Q, vert1, vert3) || checkIfInsideSegment(Q, vert2, vert3))
    {

      //where distances from segments will be stored

      vector<double> distanceV;
      vector<double>::const_iterator it; 

      
      if(checkIfInsideSegment(Q, vert1, vert2)){

        double di1 = distFromSegment(Contact, vert1, vert2);
        distanceV.push_back(di1);
      
      }

      if(checkIfInsideSegment(Q, vert1, vert3)){

        double di2 = distFromSegment(Contact, vert1, vert3);
        distanceV.push_back(di2);
      
      }

      if(checkIfInsideSegment(Q, vert2, vert3)){

        double di3 = distFromSegment(Contact, vert2, vert3);
        distanceV.push_back(di3);
      
      }
       
      it = min_element(distanceV.begin(), distanceV.end());

      dist[i] = *it;        

    }
    else 
    {

      //where distances from vertices will be stored

      vector<double> distanceVertex;
      vector<double>::const_iterator iter; 
        
      //point is outside the  segments and triangle - we get as distance the minimum of the distances from vertices

      double dis1 = sqrt(pow(Contact.x - vert1.x, 2) + pow(Contact.y - vert1.y, 2) +  pow(Contact.z - vert1.z, 2));
      distanceVertex.push_back(dis1);

      double dis2 = sqrt(pow(Contact.x - vert2.x, 2) + pow(Contact.y - vert2.y, 2) +  pow(Contact.z - vert2.z, 2));
      distanceVertex.push_back(dis2);

      double dis3 = sqrt(pow(Contact.x - vert3.x, 2) + pow(Contact.y - vert3.y, 2) +  pow(Contact.z - vert3.z, 2));
      distanceVertex.push_back(dis3);
    
      iter = min_element(distanceVertex.begin(), distanceVertex.end());
      
      dist[i] = *iter;

    }

  }
  
}

void Rover3DWheelFixedTriangleR::computeh(SiconosVector& q, SiconosVector& z, SiconosVector& y)
{


  // V.A. Memory management seems hazardous
  double * tmpQ = &(q(0));

  
  double yValue; 

  double tmp[6];
  
  for(int i = 0; i < 21; i++)
  {
    
    tmpQ[i] = q(i);
  }
 
  yValue = 100000;

  calcDistance(tmp, tmpQ);

  if(tmp[TireMark] < yValue)
  {

    yValue = tmp[TireMark];
  
  }

  y.setValue(0,yValue);
  
};

void Rover3DWheelFixedTriangleR::computeJachq(SiconosVector& q, SiconosVector& z)
{

  //Calculating the coordinate frame in the contact point - rotation matrix
  //is given by the normalized axis of the coord. frame. It's
  //stored as a class member as Euler angles in eul[3]
    
  double tmp[63];
  
  double *tmpQ = &(q(0)); 
  
  SimpleMatrix *g = (SimpleMatrix *)_jachq.get();
    
  switch(TireMark)
  {

  case 0:

    ContactJacobian1(tmp, eul, tmpQ);  
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }
    
    (*g)(28%3,28/3) = (*g)(28%3,28/3)+TireRadius;

    break;

  case 1:

    ContactJacobian2(tmp, eul, tmpQ);  
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }
   
    (*g)(31%3,31/3) = (*g)(31%3,31/3)+TireRadius;
    
    break;


  case 2:

    ContactJacobian3(tmp, eul, tmpQ);  
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }

    (*g)(43%3,43/3) = (*g)(43%3,43/3)+TireRadius;
    
    break;


  case 3:

    ContactJacobian4(tmp, eul, tmpQ);  
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }

    (*g)(46%3,46/3) = (*g)(46%3,46/3)+TireRadius;
     
    break;

  case 4:

    ContactJacobian5(tmp, eul, tmpQ);  
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }

    (*g)(58%3,58/3) = (*g)(58%3,58/3)+TireRadius;
          
    break;


  case 5:

    ContactJacobian6(tmp, eul, tmpQ);  
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }

    (*g)(61%3,61/3) = (*g)(61%3,61/3)+TireRadius;
      
    break;

  default:

    cout << "Please specify correct number of wheels" << endl;

  }
}

