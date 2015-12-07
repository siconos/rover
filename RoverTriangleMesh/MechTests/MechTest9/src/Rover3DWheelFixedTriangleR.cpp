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

#include <stdio.h>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>

#include "op3x3.h"

#include "Robot.h"
#include "Rover3DWheelFixedTriangleR.hpp"

#define PI 3.14159

using namespace std;

Rover3DWheelFixedTriangleR::Rover3DWheelFixedTriangleR(double Ax , double Ay, double Az, double Bx , double By, double Bz, double Cx , double Cy, double Cz, int WheelMark, double WheelRadius, double id)
: LagrangianScleronomousR(), TireMark(WheelMark), TireRadius(WheelRadius), _id(id), vert1(3), vert2(3), vert3(3), planeNorm(3), jacNorm(3)
{

  vert1.setValue(0, Ax);
  vert1.setValue(1, Ay);
  vert1.setValue(2, Az);

  vert2.setValue(0, Bx);
  vert2.setValue(1, By);
  vert2.setValue(2, Bz);

  vert3.setValue(0, Cx);
  vert3.setValue(1, Cy);
  vert3.setValue(2, Cz);

  SiconosVector ab(3), ac(3);

  sub(vert2, vert1, ab);
  sub(vert3, vert1, ac);

  //defining the plane's normal (cross-product or two vertices)



  cross_product(ab, ac, planeNorm);

  double plNorm = planeNorm.norm2();

  //normalization

  scal(1.0/plNorm, planeNorm, planeNorm);

  //flipping normals

  if(planeNorm.getValue(1) < 0){

    planeNorm.setValue(0, -planeNorm.getValue(0));
    planeNorm.setValue(1, -planeNorm.getValue(1));
    planeNorm.setValue(2, -planeNorm.getValue(2));

  }

  if(planeNorm.getValue(0) > 0.995){

    planeNorm.setValue(0, -planeNorm.getValue(0));
    planeNorm.setValue(1, -planeNorm.getValue(1));
    planeNorm.setValue(2, -planeNorm.getValue(2));

  }
 
  jacNorm = planeNorm;

  cout << "Normals : " << endl;
  cout << planeNorm.getValue(0) << " " << planeNorm.getValue(1) << " " << planeNorm.getValue(2) << endl;

}

double Rover3DWheelFixedTriangleR::getID(){

  return _id;

}

double Rover3DWheelFixedTriangleR::fcnMin(double a, double b)
{

  return ((a < b) ? a : b);

}

double Rover3DWheelFixedTriangleR::fcnMax(double a, double b)
{

  return ((a > b) ? a : b);

}

double Rover3DWheelFixedTriangleR::distFromSegment(SiconosVector P, SiconosVector A, SiconosVector B)
{

  //from: http://geomalgorithms.com/a02-_lines.html - very neat

  SiconosVector AB(3);

  sub(B, A, AB);

  SiconosVector AP(3);

  sub(P, A, AP);

  double norm = AB.norm2();
 
  scal(1.0/norm, AB, AB);

  SiconosVector tmp(3);

  cross_product(AB, AP, tmp);
  
  double lengthFin = tmp.norm2();

  return lengthFin;

}

bool Rover3DWheelFixedTriangleR::checkIfSameSideOfEdge(SiconosVector P1, SiconosVector P2, SiconosVector A, SiconosVector B)
{

  SiconosVector cp1(3), cp2(3), tmp1(3), tmp2(3), tmp3(3);

  sub(B, A, tmp1);
  sub(P1, A, tmp2);
  sub(P2, A, tmp3);

  cross_product(tmp1, tmp2, cp1);
  cross_product(tmp1, tmp3, cp2);

  // >= replaced by > (in this way segments are outside triangles)

  if(inner_prod(cp1, cp2) > 0)
  {
  
    return true;

  }
  else
  {

    return false;
 
  }

}

bool Rover3DWheelFixedTriangleR::checkIfInsideTriangle(SiconosVector P)
{

  SiconosVector A(vert1), B(vert2), C(vert3);

  if(checkIfSameSideOfEdge(P, A, B, C) && checkIfSameSideOfEdge(P, B, A, C) && checkIfSameSideOfEdge(P, C, A, B))
  {

    return true;

  }
  else
  {

    return false;

  }

}

bool Rover3DWheelFixedTriangleR::checkIfInsideSegment(SiconosVector P, SiconosVector A, SiconosVector B)
{

  SiconosVector AB(3);
  sub(B, A, AB);
 
  SiconosVector AP(3);
  sub(P, A, AP);  

  SiconosVector BA(3);
  sub(B, A, BA);

  double length = BA.norm2();

  double test = inner_prod(AB, AP)/length;

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
  tags[17] = TT[61];

  //Q is a contact point on a wheel projected onto a plane, P is a center of the wheel

  SiconosVector Q(3), P(3);

  for(int i = 0; i < 6; ++i){

    P.setValue(0, tags[(i*3) + 0]);
    P.setValue(1, tags[(i*3) + 1]);
    P.setValue(2, tags[(i*3) + 2]);

    //cout << "center " << P.getValue(0) << " " << P.getValue(1) << " " << P.getValue(2) << endl;

    //projection on the plane
  
    SiconosVector tmpQ(3);
    //cout << "center " << tmpQ.getValue(0) << " " << tmpQ.getValue(1) << " " << tmpQ.getValue(2) << endl;
    sub(P, vert1, tmpQ);

    double tmpInn = inner_prod(tmpQ, planeNorm);

    scal(tmpInn, planeNorm, tmpQ);

    sub(P, tmpQ, Q);
    //cout << "projection " << _id << " " << Q.getValue(0) << " " << Q.getValue(1) << " " << Q.getValue(2) << endl;
    if(checkIfInsideTriangle(Q))
    {  

      SiconosVector Pvert1(3);

      sub(P, vert1, Pvert1);

      //calculate the normal

      sub(P, Q, jacNorm);

      double nm = jacNorm.norm2();

      scal(1.0/nm, jacNorm, jacNorm);

      //cout << "normal " << _id << " " << jacNorm.getValue(0) << " " << jacNorm.getValue(1) << " " << jacNorm.getValue(2) << endl;

      //calculate the distance between the plane and the point

      double l = inner_prod(jacNorm, Pvert1);

      dist[i] = l - TireRadius;
      //cout << "distance " << dist << " " << _id << endl;
    }
    else if(checkIfInsideSegment(Q, vert1, vert2) || checkIfInsideSegment(Q, vert1, vert3) || checkIfInsideSegment(Q, vert2, vert3))
    {
      //cout << "relation " << _id << endl;
      //where distances from segments will be stored

      vector<double> distanceV;
      vector<double>::const_iterator it;
      vector<double>::const_iterator it2; 

      //map with normals

      std::map<double, SiconosVector> vectMap;

      SiconosVector nrmTmp(3);

      nrmTmp.setValue(0, -0.7071);
      nrmTmp.setValue(1, 0.7071);
      nrmTmp.setValue(2, 0);
      
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

      //normal update

      jacNorm = nrmTmp;

      dist[i] = (*it) - TireRadius;
      //cout << "distance " << dist << " " << _id << endl;
    }
    else 
    {

      //where distances from vertices will be stored

      vector<double> distanceVertex;
      vector<double>::const_iterator iter; 

      //point is outside the  segments and triangle - we get as distance the minimum of the distances from vertices

      SiconosVector d1(3), d2(3), d3(3);

      sub(P, vert1, d1);
      sub(P, vert2, d2);
      sub(P, vert3, d3);

      double dis1 = d1.norm2();
      distanceVertex.push_back(dis1);

      double dis2 = d2.norm2();
      distanceVertex.push_back(dis2);

      double dis3 = d3.norm2();
      distanceVertex.push_back(dis3);
    
      iter = min_element(distanceVertex.begin(), distanceVertex.end());
      
      dist[i] = (*iter) - TireRadius;

    }

     //cout << "-----------------------------------------------------" << endl;   
     //cout << "Normals : " << _id << endl;
     //cout << jacNorm.getValue(0) << " " << jacNorm.getValue(1) << " " << jacNorm.getValue(2) << endl;
     //cout << "-----------------------------------------------------" << endl;   

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
  //cout << "Y :" << yValue << endl;
  y->setValue(0,yValue);
  
}

void Rover3DWheelFixedTriangleR::computeJachq(const double time, Interaction& inter)
{
    
  double tmp[63];
  
  double *tmpQ = &(*inter.data(q0))(0); 
  
  SimpleMatrix *g = (SimpleMatrix *)_jachq.get();

  SimpleMatrix orthoBase(3,3);

  orthoBase(0,0) = jacNorm.getValue(0);
  orthoBase(1,0) = jacNorm.getValue(1);
  orthoBase(2,0) = jacNorm.getValue(2);

  orthoBaseFromVector(&orthoBase(0,0), &orthoBase(1,0), &orthoBase(2,0), &orthoBase(0,1), &orthoBase(1,1),
                      &orthoBase(2,1), &orthoBase(0,2), &orthoBase(1,2), &orthoBase(2,2));

  //correction of the mistake with the frame orienatation 

  orthoBase(2,2) = -orthoBase(2,2);

  //cout << _id << " ";
  //orthoBase.display();

  SimpleMatrix baseTrans(orthoBase);

  baseTrans.trans();

  SimpleMatrix J(3, 21);

  switch(TireMark)
  {

  case 0:

    ContactJacobian1(tmp, tmpQ);  
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }

    prod(baseTrans, (*g), (*g));    

    (*g)(28%3,28/3) = ((*g)(28%3,28/3) + TireRadius);

    break;

  case 1:

    ContactJacobian2(tmp, tmpQ);  
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }

    prod(baseTrans, (*g), (*g));    

    (*g)(31%3,31/3) = ((*g)(31%3,31/3) + TireRadius);
    
    break;


  case 2:

    ContactJacobian3(tmp, tmpQ);  
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }

    prod(baseTrans, (*g), (*g));    

    (*g)(43%3,43/3) = ((*g)(43%3,43/3) + TireRadius);
    
    break;


  case 3:

    ContactJacobian4(tmp, tmpQ);  
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }

    prod(baseTrans, (*g), (*g));    

    (*g)(46%3,46/3) = ((*g)(46%3,46/3) + TireRadius);
     
    break;

  case 4:

    ContactJacobian5(tmp, tmpQ);  
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }

    prod(baseTrans, (*g), (*g));    

    (*g)(58%3,58/3) = ((*g)(58%3,58/3) + TireRadius);
          
    break;


  case 5:

    ContactJacobian6(tmp, tmpQ);  
    for(int i=0 ; i<63; i++)
    {
      (*g)(i%3,i/3) = tmp[i];
    }

    prod(baseTrans, (*g), (*g));    

    (*g)(61%3,61/3) = ((*g)(61%3,61/3) + TireRadius);
      
    break;

  default:

    cout << "Please specify correct number of wheels" << endl;

  }

}

