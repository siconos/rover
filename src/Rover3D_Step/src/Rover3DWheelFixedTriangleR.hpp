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
 * Author: Jan michalczyk
 * Team: Bipop
 */

/* 
   \file Rover3DWheeelFixedTriangleR.hpp
   \Relation of a wheel with a single plane - inherits from LagrangianScleronomousR
   \each plane (triangle) maintains one relation with each wheel of the rover
   \hence, there are six relations for a single triangle on the map
*/

#ifndef Rover3DWheeelFixedTriangleR_hpp
#define Rover3DWheeelFixedTriangleR_hpp

#include "SiconosMatrix.hpp"
#include "SiconosVector.hpp"
#include "SimpleMatrix.hpp"
#include "SiconosVectorFriends.hpp"
#include "SiconosAlgebra.hpp"

#include "CircularR.hpp"
#include <cmath>

class Rover3DWheelFixedTriangleR : public LagrangianScleronomousR, public std11::enable_shared_from_this<Rover3DWheelFixedTriangleR>
{

public:

  //id

  int _id;

  SiconosVector vert1;
  SiconosVector vert2;
  SiconosVector vert3; 

  //plane's normal unit vector

  SiconosVector planeNorm;

  SiconosVector jacNorm;

  double TireRadius;
  int TireMark;

  //default constructor

  Rover3DWheelFixedTriangleR();

  double getID();  

  //function calculating the distance of points from a plane
  //Arguments: pointer to the array with distances, pointer to the array with robot state (positions - q0)

  void calcDistance(double*, double*);

  //function which checks if two points are on the same side of a triangle edge
  //one point is a point to be checked, another is a point which belongs to the 
  //trinagle. it's an auxiliary function to be called three times for each edge
  //from within checkIfInsideTriangle(vect ) function.
  //if the result is true for all three edges, point belongs to the triangle.
  //arguments: triangle vertices, point to be checked

  bool checkIfSameSideOfEdge(SiconosVector, SiconosVector, SiconosVector, SiconosVector);

  //function which checks if the projection is inside the triangle
  //arguments: point to be checked 

  bool checkIfInsideTriangle(SiconosVector);

  //function which checks if the projection is inside the segment
  //arguments: point to be checked

  bool checkIfInsideSegment(SiconosVector, SiconosVector, SiconosVector);

  //function to compute minimun of two numbers
  
  double fcnMin(double, double);

  //function to compute maximum of two numbers
  
  double fcnMax(double, double);

  //distance of a point from a segment

  double distFromSegment(SiconosVector, SiconosVector, SiconosVector);

public:

  //Constructor accepts coords of three points, wheel mark, wheel radius
  
  Rover3DWheelFixedTriangleR(double, double, double, double, double, double, double, double, double, int, double, double);

  void computeh(SiconosVector& q, SiconosVector& z, SiconosVector& y);

  void computeJachq(SiconosVector& q, SiconosVector& z);

};

TYPEDEF_SPTR(Rover3DWheelFixedTriangleR);

#endif /*Rover3DWheeelFixedTriangleR_hpp */

