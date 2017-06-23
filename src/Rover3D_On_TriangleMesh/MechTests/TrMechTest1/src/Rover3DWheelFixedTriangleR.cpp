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

#include "geomPrims.hpp"

#include "Robot.h"
#include "Rover3DWheelFixedTriangleR.hpp"

#define PI 3.14159
#define NUMOFWHEELS 6

using namespace std;

bool sortEdges(Edge a, Edge b) { return ( a._d < b._d ); }

bool sortVertices(Vertex a, Vertex b) { return ( a._d < b._d ); }

Rover3DWheelFixedTriangleR::Rover3DWheelFixedTriangleR(double Ax , double Ay, double Az, double Bx , double By, double Bz, double Cx , double Cy, double Cz, double radius, int id)
: LagrangianScleronomousR(), _vert1(3), _vert2(3), _vert3(3), _normal(3), _planeNormal(3), _pcn(3), _orthoBase(3, 3), _radius(radius), _id(id) 
{

  _vert1.setValue(0, Ax);
  _vert1.setValue(1, Ay);
  _vert1.setValue(2, Az);

  _vert2.setValue(0, Bx);
  _vert2.setValue(1, By);
  _vert2.setValue(2, Bz);

  _vert3.setValue(0, Cx);
  _vert3.setValue(1, Cy);
  _vert3.setValue(2, Cz);

  //finding the normal to the plane where the triangle lies

  SiconosVector ab(3), ac(3);

  sub(_vert2, _vert1, ab);
  sub(_vert3, _vert1, ac);

  cross_product(ab, ac, _planeNormal);

  double normCoeff = _planeNormal.norm2();

  //normalization

  scal(1.0/normCoeff, _planeNormal, _planeNormal);

  //flipping the normal if it's upside down

  if(_planeNormal.getValue(2) < 0){

    _planeNormal.setValue(0, -_planeNormal.getValue(0));
    _planeNormal.setValue(1, -_planeNormal.getValue(1));
    _planeNormal.setValue(2, -_planeNormal.getValue(2));

  }

}

double Rover3DWheelFixedTriangleR::getID(){

  return _id;

}

SiconosVector Rover3DWheelFixedTriangleR::computeWheelCenter(double* tags)
{

  int index = _id % NUMOFWHEELS;

  SiconosVector wheelCenter(3);

  switch(index)
  {
    
  case 0:

    /*wheel RL*/

    wheelCenter.setValue(0, tags[7]);
    wheelCenter.setValue(1, tags[51]);
    wheelCenter.setValue(2, tags[95]);
    
    break;

  case 1:

    /*wheel RR*/

    wheelCenter.setValue(0, tags[8]);
    wheelCenter.setValue(1, tags[52]);
    wheelCenter.setValue(2, tags[96]);
    
    break;

  case 2:

    /*wheel CL*/

    wheelCenter.setValue(0, tags[15]);
    wheelCenter.setValue(1, tags[59]);
    wheelCenter.setValue(2, tags[103]);
    
    break;

  case 3:

    /*wheel FL*/

    wheelCenter.setValue(0, tags[16]);
    wheelCenter.setValue(1, tags[60]);
    wheelCenter.setValue(2, tags[104]);
    
    break;

  case 4:

    /*wheel CR*/

    wheelCenter.setValue(0, tags[23]);
    wheelCenter.setValue(1, tags[67]);
    wheelCenter.setValue(2, tags[111]);
    
    break;

  case 5:

    /*wheel FR*/

    wheelCenter.setValue(0, tags[24]);
    wheelCenter.setValue(1, tags[68]);
    wheelCenter.setValue(2, tags[112]);
    
    break;

  default:

    cout << "No such wheel" << endl;

    break;

  }

  return wheelCenter;

}

SiconosVector Rover3DWheelFixedTriangleR::projectOnMe(SiconosVector p)
{

  /*projects a point on the triangle plane*/

  SiconosVector pProjected(3);

  SiconosVector tmpVec(3);

  sub(p, _vert1, tmpVec);

  double projOnNormal = inner_prod(tmpVec, _planeNormal);

  scal(projOnNormal, _planeNormal, tmpVec);

  sub(p, tmpVec, pProjected);

  return pProjected;

}

void Rover3DWheelFixedTriangleR::computeNormalAndDistance(SiconosVector wheelCenter)
{

  /*finding a normal based on where the wheel center projects*/

  SiconosVector proj = projectOnMe(wheelCenter);

  /*vectors to hold vertices and edges*/

  std::vector<Edge> edges;

  std::vector<Vertex> vertices;

  /*geometrical primitives*/

  Triangle triangle(_vert1, _vert2, _vert3, _planeNormal, 1);

  Edge edge1(_vert1, _vert2, 2);
  Edge edge2(_vert1, _vert3, 3);
  Edge edge3(_vert2, _vert3, 4);

  Vertex vertex1(_vert1, 5);
  Vertex vertex2(_vert2, 6);
  Vertex vertex3(_vert3, 7);
  
  if(triangle.checkIfInsideMe(proj)){
    
    _normal = triangle._n;

    _distance = triangle.computeDistance(wheelCenter) - _radius;

    return;

  }
  else if(edge1.checkIfInsideMe(proj) || edge2.checkIfInsideMe(proj) || edge3.checkIfInsideMe(proj)){

    if(edge1.checkIfInsideMe(proj)){

      edge1.computeDistance(wheelCenter);
      edge1.computeNormal(wheelCenter);
      edges.push_back(edge1);
      
    }
    if(edge2.checkIfInsideMe(proj)){

      edge2.computeDistance(wheelCenter);
      edge2.computeNormal(wheelCenter);
      edges.push_back(edge2);

    }
    if(edge3.checkIfInsideMe(proj)){

      edge3.computeDistance(wheelCenter);
      edge3.computeNormal(wheelCenter);
      edges.push_back(edge3);

    }

    std::sort(edges.begin(), edges.end(), sortEdges);

    _normal = edges.at(0)._n;

    _distance = edges.at(0)._d - _radius;

    return;

  }  
  else{

    vertex1.computeDistance(wheelCenter);
    vertex1.computeNormal(wheelCenter);
    vertices.push_back(vertex1);

    vertex2.computeDistance(wheelCenter);
    vertex2.computeNormal(wheelCenter);
    vertices.push_back(vertex2);

    vertex3.computeDistance(wheelCenter);
    vertex3.computeNormal(wheelCenter);
    vertices.push_back(vertex3);

    std::sort(vertices.begin(), vertices.end(), sortVertices);

    _normal = vertices.at(0)._n;

    _distance = vertices.at(0)._d - _radius;

    return;

  }

}

double Rover3DWheelFixedTriangleR::computeDistance(double* q)
{
 
  //get the contact points in cartesian space

  double TT[132];

  Tags(TT, q);

  SiconosVector wheelCnt = computeWheelCenter(TT);

  computeNormalAndDistance(wheelCnt);

  return this->_distance;
  
}

void Rover3DWheelFixedTriangleR::computeh(const double time, Interaction& inter)
{

  double * stateQ = &(*inter.data(q0))(0);  

  double yValue; 

  for(int i = 0; i < 21; i++)
  {
    
    stateQ[i] = (*inter.data(q0))(i);

  }

  yValue = 100000;

  yValue = computeDistance(stateQ);

  SP::SiconosVector y = inter.y(0);

  y->setValue(0, yValue);
  
}

SimpleMatrix Rover3DWheelFixedTriangleR::getSkewMat(SiconosVector v)
{

  SimpleMatrix skewMatrix(3, 3);

  skewMatrix.setValue(0, 0, 0);
  skewMatrix.setValue(0, 1, -v.getValue(2));
  skewMatrix.setValue(0, 2, v.getValue(1));
  skewMatrix.setValue(1, 0, v.getValue(2));
  skewMatrix.setValue(1, 1, 0);
  skewMatrix.setValue(1, 2, -v.getValue(0));
  skewMatrix.setValue(2, 0, -v.getValue(1));
  skewMatrix.setValue(2, 1, v.getValue(0));
  skewMatrix.setValue(2, 2, 0);

  return skewMatrix;

}

SimpleMatrix Rover3DWheelFixedTriangleR::computeGeomJac(SiconosVector norm, double* tags, double* qs)
{

  //index - to know which wheel we're dealing with

  int index = _id % NUMOFWHEELS;

  /*checking for the wheel and computing the right jacobian of the contact point*/
  /*for clarity's sake jacobian is divided into three parts following the document*/
  /*first part - the identity, second the angular velocity part, third for joints*/

  /*result of the function - full geometric jacobian in the contact point*/

  SimpleMatrix geomJac(3, 21);

  /*to store the joints axes and centers and r vectors for joints during computations*/

  SiconosVector jointAxis1(3);
  SiconosVector jointAxis2(3);
  SiconosVector wheelJointAxis(3);

  SiconosVector jointCenter1(3);
  SiconosVector jointCenter2(3);
  SiconosVector wheelJointCenter(3);

  SiconosVector rJointVector1(3);
  SiconosVector rJointVector2(3);
  SiconosVector rWheelJointVector(3);

  /*to store columns for the joints for the third part of the jacobian*/

  SiconosVector jointColumn1(3);
  SiconosVector jointColumn2(3);
  SiconosVector wheelColumn(3);

  /*to store the base coordinates (obtained from qs)*/

  SiconosVector baseCoords(3);

  /*r vector computation for base*/

  baseCoords.setValue(0, qs[0]);
  baseCoords.setValue(1, qs[1]);
  baseCoords.setValue(2, qs[2]);

  /*to store the r vector for the base during computations (from base to wheel contact point)*/

  SiconosVector rBaseVector(3);

  /*to store the r vector-based skew matrix during computations*/

  SimpleMatrix rBaseSkew(3, 3);

  /*to store the E matrix (look in the jacobian document)*/

  SimpleMatrix E(3, 3);

  /*get E matrix*/

  E.setValue(0, 0, cos(qs[4])*cos(qs[5]));
  E.setValue(0, 1, -sin(qs[5]));
  E.setValue(0, 2, 0);
  E.setValue(1, 0, cos(qs[4])*sin(qs[5]));
  E.setValue(1, 1, cos(qs[5]));
  E.setValue(1, 2, 0);
  E.setValue(2, 0, -sin(qs[4]));
  E.setValue(2, 1, 0);
  E.setValue(2, 2, 1);

  /*to store the contact point*/

  SiconosVector pcn(3);

  /*second part of the jacobian*/

  SimpleMatrix angVelPart(3, 3);

  if(index == 0)
  {

    /*wheel RL*/

    /*supporting joints - RBogieJoint, RLSteeringJoint, RLWheel*/

    /*contact point computation*/

    wheelJointCenter.setValue(0, tags[7]);
    wheelJointCenter.setValue(1, tags[51]);
    wheelJointCenter.setValue(2, tags[95]);

    pcn = wheelJointCenter - _radius*norm;

    /*r vector computation for base*/

    rBaseVector = pcn - baseCoords;

    rBaseSkew = getSkewMat(rBaseVector);

    scal(-1,rBaseSkew,rBaseSkew);

    /*poduct of E and skewsym. matrix*/

    prod(rBaseSkew, E, angVelPart);

    /*getting joints columns for the third part*/
    
    /*RBogieJoint*/

    jointCenter1.setValue(0, tags[1]);
    jointCenter1.setValue(1, tags[45]);
    jointCenter1.setValue(2, tags[89]);

    jointAxis1.setValue(0, tags[2]);  
    jointAxis1.setValue(1, tags[46]);
    jointAxis1.setValue(2, tags[90]);

    jointAxis1 = jointAxis1 - jointCenter1;

    rJointVector1 = pcn - jointCenter1;

    cross_product(jointAxis1, rJointVector1, jointColumn1);

    /*RLSteeringJoint*/

    jointCenter2.setValue(0, tags[3]);
    jointCenter2.setValue(1, tags[47]);
    jointCenter2.setValue(2, tags[91]);

    jointAxis2.setValue(0, tags[4]);  
    jointAxis2.setValue(1, tags[48]);
    jointAxis2.setValue(2, tags[92]);

    jointAxis2 = jointAxis2 - jointCenter2;

    rJointVector2 = pcn - jointCenter2;

    cross_product(jointAxis2, rJointVector2, jointColumn2);

    /*RLWheelJoint*/

    wheelJointAxis.setValue(0, tags[26]);  
    wheelJointAxis.setValue(1, tags[70]);
    wheelJointAxis.setValue(2, tags[114]);

    wheelJointAxis = wheelJointAxis - wheelJointCenter;

    rWheelJointVector = pcn - wheelJointCenter;

    cross_product(wheelJointAxis, rWheelJointVector, wheelColumn);

    /*final composition of the jacobian matrix*/

    geomJac.zero();

    /*first part - identity*/
    
    geomJac.setValue(0, 0, 1);
    geomJac.setValue(0, 1, 0);
    geomJac.setValue(0, 2, 0);
    geomJac.setValue(1, 0, 0);
    geomJac.setValue(1, 1, 1);
    geomJac.setValue(1, 2, 0);
    geomJac.setValue(2, 0, 0);
    geomJac.setValue(2, 1, 0);
    geomJac.setValue(2, 2, 1);

    /*second part - angular velocity part*/

    geomJac.setValue(0, 3, angVelPart.getValue(0, 0));
    geomJac.setValue(0, 4, angVelPart.getValue(0, 1));
    geomJac.setValue(0, 5, angVelPart.getValue(0, 2));
    geomJac.setValue(1, 3, angVelPart.getValue(1, 0));
    geomJac.setValue(1, 4, angVelPart.getValue(1, 1));
    geomJac.setValue(1, 5, angVelPart.getValue(1, 2));
    geomJac.setValue(2, 3, angVelPart.getValue(2, 0));
    geomJac.setValue(2, 4, angVelPart.getValue(2, 1));
    geomJac.setValue(2, 5, angVelPart.getValue(2, 2));

    /*third part - joints - q6, q7, q9*/

    geomJac.setValue(0, 6, jointColumn1.getValue(0));
    geomJac.setValue(1, 6, jointColumn1.getValue(1));
    geomJac.setValue(2, 6, jointColumn1.getValue(2));

    geomJac.setValue(0, 7, jointColumn2.getValue(0));
    geomJac.setValue(1, 7, jointColumn2.getValue(1));
    geomJac.setValue(2, 7, jointColumn2.getValue(2));

    geomJac.setValue(0, 9, wheelColumn.getValue(0));
    geomJac.setValue(1, 9, wheelColumn.getValue(1));
    geomJac.setValue(2, 9, wheelColumn.getValue(2));

  }
  else if(index == 1)
  {

    /*wheel RR*/

    /*supporting joints - RBogieJoint, RRSteeringJoint, RRWheel*/

    /*contact point computation*/

    wheelJointCenter.setValue(0, tags[8]);
    wheelJointCenter.setValue(1, tags[52]);
    wheelJointCenter.setValue(2, tags[96]);

    pcn = wheelJointCenter - _radius*norm;

    /*r vector computation for base*/

    rBaseVector = pcn - baseCoords;

    rBaseSkew = getSkewMat(rBaseVector);

    scal(-1,rBaseSkew,rBaseSkew);

    /*poduct of E and skewsym. matrix*/

    prod(rBaseSkew, E, angVelPart);

    /*getting joints columns for the third part*/
    
    /*RBogieJoint*/

    jointCenter1.setValue(0, tags[1]);
    jointCenter1.setValue(1, tags[45]);
    jointCenter1.setValue(2, tags[89]);

    jointAxis1.setValue(0, tags[2]);  
    jointAxis1.setValue(1, tags[46]);
    jointAxis1.setValue(2, tags[90]);

    jointAxis1 = jointAxis1 - jointCenter1;

    rJointVector1 = pcn - jointCenter1;

    cross_product(jointAxis1, rJointVector1, jointColumn1);

    /*RRSteeringJoint*/

    jointCenter2.setValue(0, tags[5]);
    jointCenter2.setValue(1, tags[49]);
    jointCenter2.setValue(2, tags[93]);

    jointAxis2.setValue(0, tags[6]);  
    jointAxis2.setValue(1, tags[50]);
    jointAxis2.setValue(2, tags[94]);

    jointAxis2 = jointAxis2 - jointCenter2;

    rJointVector2 = pcn - jointCenter2;

    cross_product(jointAxis2, rJointVector2, jointColumn2);

    /*RRWheelJoint*/

    wheelJointAxis.setValue(0, tags[29]);  
    wheelJointAxis.setValue(1, tags[73]);
    wheelJointAxis.setValue(2, tags[117]);

    wheelJointAxis = wheelJointAxis - wheelJointCenter;

    rWheelJointVector = pcn - wheelJointCenter;

    cross_product(wheelJointAxis, rWheelJointVector, wheelColumn);

    /*final composition of the jacobian matrix*/

    geomJac.zero();

    /*first part - identity*/
    
    geomJac.setValue(0, 0, 1);
    geomJac.setValue(0, 1, 0);
    geomJac.setValue(0, 2, 0);
    geomJac.setValue(1, 0, 0);
    geomJac.setValue(1, 1, 1);
    geomJac.setValue(1, 2, 0);
    geomJac.setValue(2, 0, 0);
    geomJac.setValue(2, 1, 0);
    geomJac.setValue(2, 2, 1);

    /*second part - angular velocity part*/

    geomJac.setValue(0, 3, angVelPart.getValue(0, 0));
    geomJac.setValue(0, 4, angVelPart.getValue(0, 1));
    geomJac.setValue(0, 5, angVelPart.getValue(0, 2));
    geomJac.setValue(1, 3, angVelPart.getValue(1, 0));
    geomJac.setValue(1, 4, angVelPart.getValue(1, 1));
    geomJac.setValue(1, 5, angVelPart.getValue(1, 2));
    geomJac.setValue(2, 3, angVelPart.getValue(2, 0));
    geomJac.setValue(2, 4, angVelPart.getValue(2, 1));
    geomJac.setValue(2, 5, angVelPart.getValue(2, 2));

    /*third part - joints - q6, q8, q10*/

    geomJac.setValue(0, 6, jointColumn1.getValue(0));
    geomJac.setValue(1, 6, jointColumn1.getValue(1));
    geomJac.setValue(2, 6, jointColumn1.getValue(2));

    geomJac.setValue(0, 8, jointColumn2.getValue(0));
    geomJac.setValue(1, 8, jointColumn2.getValue(1));
    geomJac.setValue(2, 8, jointColumn2.getValue(2));

    geomJac.setValue(0, 10, wheelColumn.getValue(0));
    geomJac.setValue(1, 10, wheelColumn.getValue(1));
    geomJac.setValue(2, 10, wheelColumn.getValue(2));

  }  
  else if(index == 2)
  {

    /*wheel CL*/

    /*supporting joints - FLBogieJoint, CLSteeringJoint, CLWheel*/

    /*contact point computation*/

    wheelJointCenter.setValue(0, tags[15]);
    wheelJointCenter.setValue(1, tags[59]);
    wheelJointCenter.setValue(2, tags[103]);

    pcn = wheelJointCenter - _radius*norm;

    /*r vector computation for base*/

    rBaseVector = pcn - baseCoords;

    rBaseSkew = getSkewMat(rBaseVector);

    scal(-1,rBaseSkew,rBaseSkew);

    /*poduct of E and skewsym. matrix*/

    prod(rBaseSkew, E, angVelPart);

    /*getting joints columns for the third part*/
    
    /*FLBogieJoint*/

    jointCenter1.setValue(0, tags[9]);
    jointCenter1.setValue(1, tags[53]);
    jointCenter1.setValue(2, tags[97]);

    jointAxis1.setValue(0, tags[10]);  
    jointAxis1.setValue(1, tags[54]);
    jointAxis1.setValue(2, tags[98]);

    jointAxis1 = jointAxis1 - jointCenter1;

    rJointVector1 = pcn - jointCenter1;

    cross_product(jointAxis1, rJointVector1, jointColumn1);

    /*CLSteeringJoint*/

    jointCenter2.setValue(0, tags[11]);
    jointCenter2.setValue(1, tags[55]);
    jointCenter2.setValue(2, tags[99]);

    jointAxis2.setValue(0, tags[12]);  
    jointAxis2.setValue(1, tags[56]);
    jointAxis2.setValue(2, tags[100]);

    jointAxis2 = jointAxis2 - jointCenter2;

    rJointVector2 = pcn - jointCenter2;

    cross_product(jointAxis2, rJointVector2, jointColumn2);

    /*CLWheelJoint*/

    wheelJointAxis.setValue(0, tags[32]);  
    wheelJointAxis.setValue(1, tags[76]);
    wheelJointAxis.setValue(2, tags[120]);

    wheelJointAxis = wheelJointAxis - wheelJointCenter;

    rWheelJointVector = pcn - wheelJointCenter;

    cross_product(wheelJointAxis, rWheelJointVector, wheelColumn);

    /*final composition of the jacobian matrix*/

    geomJac.zero();

    /*first part - identity*/
    
    geomJac.setValue(0, 0, 1);
    geomJac.setValue(0, 1, 0);
    geomJac.setValue(0, 2, 0);
    geomJac.setValue(1, 0, 0);
    geomJac.setValue(1, 1, 1);
    geomJac.setValue(1, 2, 0);
    geomJac.setValue(2, 0, 0);
    geomJac.setValue(2, 1, 0);
    geomJac.setValue(2, 2, 1);

    /*second part - angular velocity part*/

    geomJac.setValue(0, 3, angVelPart.getValue(0, 0));
    geomJac.setValue(0, 4, angVelPart.getValue(0, 1));
    geomJac.setValue(0, 5, angVelPart.getValue(0, 2));
    geomJac.setValue(1, 3, angVelPart.getValue(1, 0));
    geomJac.setValue(1, 4, angVelPart.getValue(1, 1));
    geomJac.setValue(1, 5, angVelPart.getValue(1, 2));
    geomJac.setValue(2, 3, angVelPart.getValue(2, 0));
    geomJac.setValue(2, 4, angVelPart.getValue(2, 1));
    geomJac.setValue(2, 5, angVelPart.getValue(2, 2));

    /*third part - joints - q6, q7, q9*/

    geomJac.setValue(0, 11, jointColumn1.getValue(0));
    geomJac.setValue(1, 11, jointColumn1.getValue(1));
    geomJac.setValue(2, 11, jointColumn1.getValue(2));

    geomJac.setValue(0, 12, jointColumn2.getValue(0));
    geomJac.setValue(1, 12, jointColumn2.getValue(1));
    geomJac.setValue(2, 12, jointColumn2.getValue(2));

    geomJac.setValue(0, 14, wheelColumn.getValue(0));
    geomJac.setValue(1, 14, wheelColumn.getValue(1));
    geomJac.setValue(2, 14, wheelColumn.getValue(2));

  }  
  else if(index == 3)
  {

    /*wheel FL*/

    /*supporting joints - FLBogieJoint, FLSteeringJoint, FLWheel*/

    /*contact point computation*/

    wheelJointCenter.setValue(0, tags[16]);
    wheelJointCenter.setValue(1, tags[60]);
    wheelJointCenter.setValue(2, tags[104]);

    pcn = wheelJointCenter - _radius*norm;

    /*r vector computation for base*/

    rBaseVector = pcn - baseCoords;

    rBaseSkew = getSkewMat(rBaseVector);

    scal(-1,rBaseSkew,rBaseSkew);

    /*poduct of E and skewsym. matrix*/

    prod(rBaseSkew, E, angVelPart);

    /*getting joints columns for the third part*/
    
    /*FLBogieJoint*/

    jointCenter1.setValue(0, tags[9]);
    jointCenter1.setValue(1, tags[53]);
    jointCenter1.setValue(2, tags[97]);

    jointAxis1.setValue(0, tags[10]);  
    jointAxis1.setValue(1, tags[54]);
    jointAxis1.setValue(2, tags[98]);

    jointAxis1 = jointAxis1 - jointCenter1;

    rJointVector1 = pcn - jointCenter1;

    cross_product(jointAxis1, rJointVector1, jointColumn1);

    /*FLSteeringJoint*/

    jointCenter2.setValue(0, tags[13]);
    jointCenter2.setValue(1, tags[57]);
    jointCenter2.setValue(2, tags[101]);

    jointAxis2.setValue(0, tags[14]);  
    jointAxis2.setValue(1, tags[58]);
    jointAxis2.setValue(2, tags[102]);

    jointAxis2 = jointAxis2 - jointCenter2;

    rJointVector2 = pcn - jointCenter2;

    cross_product(jointAxis2, rJointVector2, jointColumn2);

    /*FLWheelJoint*/

    wheelJointAxis.setValue(0, tags[35]);  
    wheelJointAxis.setValue(1, tags[79]);
    wheelJointAxis.setValue(2, tags[123]);

    wheelJointAxis = wheelJointAxis - wheelJointCenter;

    rWheelJointVector = pcn - wheelJointCenter;

    cross_product(wheelJointAxis, rWheelJointVector, wheelColumn);

    /*final composition of the jacobian matrix*/

    geomJac.zero();

    /*first part - identity*/
    
    geomJac.setValue(0, 0, 1);
    geomJac.setValue(0, 1, 0);
    geomJac.setValue(0, 2, 0);
    geomJac.setValue(1, 0, 0);
    geomJac.setValue(1, 1, 1);
    geomJac.setValue(1, 2, 0);
    geomJac.setValue(2, 0, 0);
    geomJac.setValue(2, 1, 0);
    geomJac.setValue(2, 2, 1);

    /*second part - angular velocity part*/

    geomJac.setValue(0, 3, angVelPart.getValue(0, 0));
    geomJac.setValue(0, 4, angVelPart.getValue(0, 1));
    geomJac.setValue(0, 5, angVelPart.getValue(0, 2));
    geomJac.setValue(1, 3, angVelPart.getValue(1, 0));
    geomJac.setValue(1, 4, angVelPart.getValue(1, 1));
    geomJac.setValue(1, 5, angVelPart.getValue(1, 2));
    geomJac.setValue(2, 3, angVelPart.getValue(2, 0));
    geomJac.setValue(2, 4, angVelPart.getValue(2, 1));
    geomJac.setValue(2, 5, angVelPart.getValue(2, 2));

    /*third part - joints - q6, q7, q9*/

    geomJac.setValue(0, 11, jointColumn1.getValue(0));
    geomJac.setValue(1, 11, jointColumn1.getValue(1));
    geomJac.setValue(2, 11, jointColumn1.getValue(2));

    geomJac.setValue(0, 13, jointColumn2.getValue(0));
    geomJac.setValue(1, 13, jointColumn2.getValue(1));
    geomJac.setValue(2, 13, jointColumn2.getValue(2));

    geomJac.setValue(0, 15, wheelColumn.getValue(0));
    geomJac.setValue(1, 15, wheelColumn.getValue(1));
    geomJac.setValue(2, 15, wheelColumn.getValue(2));

  }  
  else if(index == 4)
  {

    /*wheel CR*/

    /*supporting joints - FRBogieJoint, CRSteeringJoint, CRWheel*/

    /*contact point computation*/

    wheelJointCenter.setValue(0, tags[23]);
    wheelJointCenter.setValue(1, tags[67]);
    wheelJointCenter.setValue(2, tags[111]);

    pcn = wheelJointCenter - _radius*norm;

    /*r vector computation for base*/

    rBaseVector = pcn - baseCoords;

    rBaseSkew = getSkewMat(rBaseVector);

    scal(-1,rBaseSkew,rBaseSkew);

    /*poduct of E and skewsym. matrix*/

    prod(rBaseSkew, E, angVelPart);

    /*getting joints columns for the third part*/
    
    /*FRBogieJoint*/

    jointCenter1.setValue(0, tags[17]);
    jointCenter1.setValue(1, tags[61]);
    jointCenter1.setValue(2, tags[105]);

    jointAxis1.setValue(0, tags[18]);  
    jointAxis1.setValue(1, tags[62]);
    jointAxis1.setValue(2, tags[106]);

    jointAxis1 = jointAxis1 - jointCenter1;

    rJointVector1 = pcn - jointCenter1;

    cross_product(jointAxis1, rJointVector1, jointColumn1);

    /*CRSteeringJoint*/

    jointCenter2.setValue(0, tags[19]);
    jointCenter2.setValue(1, tags[63]);
    jointCenter2.setValue(2, tags[107]);

    jointAxis2.setValue(0, tags[20]);  
    jointAxis2.setValue(1, tags[64]);
    jointAxis2.setValue(2, tags[108]);

    jointAxis2 = jointAxis2 - jointCenter2;

    rJointVector2 = pcn - jointCenter2;

    cross_product(jointAxis2, rJointVector2, jointColumn2);

    /*CRWheelJoint*/

    wheelJointAxis.setValue(0, tags[38]);  
    wheelJointAxis.setValue(1, tags[82]);
    wheelJointAxis.setValue(2, tags[126]);

    wheelJointAxis = wheelJointAxis - wheelJointCenter;

    rWheelJointVector = pcn - wheelJointCenter;

    cross_product(wheelJointAxis, rWheelJointVector, wheelColumn);

    /*final composition of the jacobian matrix*/

    geomJac.zero();

    /*first part - identity*/
    
    geomJac.setValue(0, 0, 1);
    geomJac.setValue(0, 1, 0);
    geomJac.setValue(0, 2, 0);
    geomJac.setValue(1, 0, 0);
    geomJac.setValue(1, 1, 1);
    geomJac.setValue(1, 2, 0);
    geomJac.setValue(2, 0, 0);
    geomJac.setValue(2, 1, 0);
    geomJac.setValue(2, 2, 1);

    /*second part - angular velocity part*/

    geomJac.setValue(0, 3, angVelPart.getValue(0, 0));
    geomJac.setValue(0, 4, angVelPart.getValue(0, 1));
    geomJac.setValue(0, 5, angVelPart.getValue(0, 2));
    geomJac.setValue(1, 3, angVelPart.getValue(1, 0));
    geomJac.setValue(1, 4, angVelPart.getValue(1, 1));
    geomJac.setValue(1, 5, angVelPart.getValue(1, 2));
    geomJac.setValue(2, 3, angVelPart.getValue(2, 0));
    geomJac.setValue(2, 4, angVelPart.getValue(2, 1));
    geomJac.setValue(2, 5, angVelPart.getValue(2, 2));

    /*third part - joints - q6, q7, q9*/

    geomJac.setValue(0, 16, jointColumn1.getValue(0));
    geomJac.setValue(1, 16, jointColumn1.getValue(1));
    geomJac.setValue(2, 16, jointColumn1.getValue(2));

    geomJac.setValue(0, 17, jointColumn2.getValue(0));
    geomJac.setValue(1, 17, jointColumn2.getValue(1));
    geomJac.setValue(2, 17, jointColumn2.getValue(2));

    geomJac.setValue(0, 19, wheelColumn.getValue(0));
    geomJac.setValue(1, 19, wheelColumn.getValue(1));
    geomJac.setValue(2, 19, wheelColumn.getValue(2));

  }  
  else if(index == 5)
  {

    /*wheel FR*/

    /*supporting joints - FRBogieJoint, FRSteeringJoint, FRWheel*/

    /*contact point computation*/

    wheelJointCenter.setValue(0, tags[24]);
    wheelJointCenter.setValue(1, tags[68]);
    wheelJointCenter.setValue(2, tags[112]);

    pcn = wheelJointCenter - _radius*norm;

    /*r vector computation for base*/

    rBaseVector = pcn - baseCoords;

    rBaseSkew = getSkewMat(rBaseVector);

    scal(-1,rBaseSkew,rBaseSkew);

    /*poduct of E and skewsym. matrix*/

    prod(rBaseSkew, E, angVelPart);

    /*getting joints columns for the third part*/
    
    /*FRBogieJoint*/

    jointCenter1.setValue(0, tags[17]);
    jointCenter1.setValue(1, tags[61]);
    jointCenter1.setValue(2, tags[105]);

    jointAxis1.setValue(0, tags[18]);  
    jointAxis1.setValue(1, tags[62]);
    jointAxis1.setValue(2, tags[106]);

    jointAxis1 = jointAxis1 - jointCenter1;

    rJointVector1 = pcn - jointCenter1;

    cross_product(jointAxis1, rJointVector1, jointColumn1);

    /*FRSteeringJoint*/

    jointCenter2.setValue(0, tags[21]);
    jointCenter2.setValue(1, tags[65]);
    jointCenter2.setValue(2, tags[109]);

    jointAxis2.setValue(0, tags[22]);  
    jointAxis2.setValue(1, tags[66]);
    jointAxis2.setValue(2, tags[110]);

    jointAxis2 = jointAxis2 - jointCenter2;

    rJointVector2 = pcn - jointCenter2;

    cross_product(jointAxis2, rJointVector2, jointColumn2);

    /*FRWheelJoint*/

    wheelJointAxis.setValue(0, tags[41]);  
    wheelJointAxis.setValue(1, tags[85]);
    wheelJointAxis.setValue(2, tags[129]);

    wheelJointAxis = wheelJointAxis - wheelJointCenter;

    rWheelJointVector = pcn - wheelJointCenter;

    cross_product(wheelJointAxis, rWheelJointVector, wheelColumn);

    /*final composition of the jacobian matrix*/

    geomJac.zero();

    /*first part - identity*/
    
    geomJac.setValue(0, 0, 1);
    geomJac.setValue(0, 1, 0);
    geomJac.setValue(0, 2, 0);
    geomJac.setValue(1, 0, 0);
    geomJac.setValue(1, 1, 1);
    geomJac.setValue(1, 2, 0);
    geomJac.setValue(2, 0, 0);
    geomJac.setValue(2, 1, 0);
    geomJac.setValue(2, 2, 1);

    /*second part - angular velocity part*/

    geomJac.setValue(0, 3, angVelPart.getValue(0, 0));
    geomJac.setValue(0, 4, angVelPart.getValue(0, 1));
    geomJac.setValue(0, 5, angVelPart.getValue(0, 2));
    geomJac.setValue(1, 3, angVelPart.getValue(1, 0));
    geomJac.setValue(1, 4, angVelPart.getValue(1, 1));
    geomJac.setValue(1, 5, angVelPart.getValue(1, 2));
    geomJac.setValue(2, 3, angVelPart.getValue(2, 0));
    geomJac.setValue(2, 4, angVelPart.getValue(2, 1));
    geomJac.setValue(2, 5, angVelPart.getValue(2, 2));

    /*third part - joints - q6, q7, q9*/

    geomJac.setValue(0, 16, jointColumn1.getValue(0));
    geomJac.setValue(1, 16, jointColumn1.getValue(1));
    geomJac.setValue(2, 16, jointColumn1.getValue(2));

    geomJac.setValue(0, 18, jointColumn2.getValue(0));
    geomJac.setValue(1, 18, jointColumn2.getValue(1));
    geomJac.setValue(2, 18, jointColumn2.getValue(2));

    geomJac.setValue(0, 20, wheelColumn.getValue(0));
    geomJac.setValue(1, 20, wheelColumn.getValue(1));
    geomJac.setValue(2, 20, wheelColumn.getValue(2));

  }  

  _pcn = pcn;

  return geomJac;

}

void Rover3DWheelFixedTriangleR::computeJachq(const double time, Interaction& inter)
{

  double tgs[132];
 
  double *tmpQ = &(*inter.data(q0))(0); 

  Tags(tgs, tmpQ);

  SimpleMatrix *g = (SimpleMatrix *)_jachq.get();

  _orthoBase(0,0) = _normal.getValue(0);
  _orthoBase(0,1) = _normal.getValue(1);
  _orthoBase(0,2) = _normal.getValue(2);

  orthoBaseFromVector(&_orthoBase(0,0), &_orthoBase(0,1), &_orthoBase(0,2), &_orthoBase(1,0), &_orthoBase(1,1),
                      &_orthoBase(1,2), &_orthoBase(2,0), &_orthoBase(2,1), &_orthoBase(2,2));

  SimpleMatrix baseTrans(_orthoBase);

  SimpleMatrix Jac(3, 21);

  Jac = computeGeomJac(_normal, tgs, tmpQ);

  (*g) = Jac;

  prod(baseTrans, (*g), (*g));    
  
}

//EOF

