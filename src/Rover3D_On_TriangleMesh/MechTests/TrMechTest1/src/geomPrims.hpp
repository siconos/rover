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

#ifndef geomPrims_hpp
#define geomPrims_hpp

#include "SiconosMatrix.hpp"
#include "SiconosVector.hpp"
#include "SimpleMatrix.hpp"
#include "SiconosVectorFriends.hpp"
#include "SiconosAlgebra.hpp"

#include "CircularR.hpp"
#include <cmath>

class Triangle : public std11::enable_shared_from_this<Triangle> {

public:

  int _id;

  //vertices

  SiconosVector _p1;
  SiconosVector _p2;
  SiconosVector _p3;

  //normal

  SiconosVector _n;

public:

  //default constructor

  Triangle();

  //constructor taking three points

  Triangle(SiconosVector p1, SiconosVector p2, SiconosVector p3, SiconosVector n, int id);

  //compute distance point-triangle plane

  double computeDistance(SiconosVector p);

  //function which checks if two points are on the same side of a triangle edge

  bool checkIfSameSideOfEdge(SiconosVector p1, SiconosVector p2, SiconosVector a, SiconosVector b);

  //check if inside the triangle

  bool checkIfInsideMe(SiconosVector p);

};

class Edge : public std11::enable_shared_from_this<Edge> {

public:

  int _id;

  SiconosVector _p1;
  SiconosVector _p2;

  //distance to sort the array of edges

  double _d;

  //normal

  SiconosVector _n;

public:

  //default constructor

  Edge();

  //constructor taking two points

  Edge(SiconosVector p1, SiconosVector p2, int id);

  //compute distance point-edge

  void computeDistance(SiconosVector p);

  //compute normal point-edge

  void computeNormal(SiconosVector p);

  //check if inside the edge

  bool checkIfInsideMe(SiconosVector p);

};

class Vertex : public std11::enable_shared_from_this<Vertex> {

public:

  int _id;

  SiconosVector _p1;

  //distance

  double _d;

  //normal

  SiconosVector _n;

public:

  //default constructor

  Vertex();

  //constructor taking one point

  Vertex(SiconosVector p1, int id);

  //compute distance point-vertex

  void computeDistance(SiconosVector p);

  //compute normal point-vertex

  void computeNormal(SiconosVector p);

};

TYPEDEF_SPTR(Triangle);
TYPEDEF_SPTR(Edge);
TYPEDEF_SPTR(Vertex);

#endif /*geomPrims_hpp*/



