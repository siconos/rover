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

#include "geomPrims.hpp"

#include "CircularR.hpp"
#include <cmath>

class Rover3DWheelFixedTriangleR : public LagrangianScleronomousR, public std11::enable_shared_from_this<Rover3DWheelFixedTriangleR>
{

public:

  //id - tells which wheel interacts

  int _id;

  SiconosVector _vert1;
  SiconosVector _vert2;
  SiconosVector _vert3; 

  //triangle's plane normal unit vector (used for projection)

  SiconosVector _planeNormal;

  //wheel radius

  const double _radius;

  //relation's normal

  SiconosVector _normal;

  //relation's distance

  double _distance;

  //contact point

  SiconosVector _pcn;

  //orthonormal basis

  SimpleMatrix _orthoBase;

public:

  //default constructor

  Rover3DWheelFixedTriangleR();

  double getID();  

  //compute wheel center

  SiconosVector computeWheelCenter(double* tags);

  SiconosVector computeWheelNorm(double* tags);

  //compute normal vector

  double computeDistance(double* q);

  void computeNormalAndDistance(SiconosVector wheelCenter);

  //geometric jacobian computation

  SimpleMatrix computeGeomJac(SiconosVector norm, double* tags, double* qs);

  //skew-symmetric matrix computation

  SimpleMatrix getSkewMat(SiconosVector v);

  //Constructor accepts coords of three points, wheel mark, wheel radius
  
  Rover3DWheelFixedTriangleR(double, double, double, double, double, double, double, double, double, double, int);

  SiconosVector projectOnMe(SiconosVector p);

  void computeh(const double time, Interaction& inter);

  void computeJachq(const double time, Interaction& inter);

};

TYPEDEF_SPTR(Rover3DWheelFixedTriangleR);

#endif /*Rover3DWheeelFixedTriangleR_hpp*/
