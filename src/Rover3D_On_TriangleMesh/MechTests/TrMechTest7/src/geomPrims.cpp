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
#include <fstream>
#include <vector>
#include <algorithm>

#include "geomPrims.hpp"

Triangle::Triangle(SiconosVector p1, SiconosVector p2, SiconosVector p3, SiconosVector n, int id) : _p1(p1), _p2(p2), _p3(p3), _n(n), _id(id)
{

}

double Triangle::computeDistance(SiconosVector p)
{

  SiconosVector _p1p(3);

  sub(p, _p1, _p1p);

  //distance between the plane and the point

  double dist = inner_prod(_n, _p1p);

  return dist;

}

bool Triangle::checkIfSameSideOfEdge(SiconosVector p1, SiconosVector p2, SiconosVector a, SiconosVector b)
{

  SiconosVector cp1(3), cp2(3), tmp1(3), tmp2(3), tmp3(3);

  sub(b, a, tmp1);
  sub(p1, a, tmp2);
  sub(p2, a, tmp3);

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

bool Triangle::checkIfInsideMe(SiconosVector p)
{

  if(checkIfSameSideOfEdge(p, _p1, _p2, _p3) && checkIfSameSideOfEdge(p, _p2, _p1, _p3) && checkIfSameSideOfEdge(p, _p3, _p1, _p2))
  {

    return true;

  }
  else
  {

    return false;

  }

}

Edge::Edge(SiconosVector p1, SiconosVector p2, int id) : _p1(p1), _p2(p2), _id(id), _n(3)
{
  _d = 10000;
}

bool Edge::checkIfInsideMe(SiconosVector p)
{

  SiconosVector AB(3);
  sub(_p2, _p1, AB);
 
  SiconosVector AP(3);
  sub(p, _p1, AP);  

  SiconosVector BA(3);
  sub(_p1, _p2, BA);

  double length = BA.norm2();

  double test = inner_prod(AB, AP)/length;

  if((test > 0) && (test < length)){

    return true;

  }
  else{

    return false;

  }

}

void Edge::computeDistance(SiconosVector p)
{

  //from: http://geomalgorithms.com/a02-_lines.html - very neat

  SiconosVector AB(3);

  sub(_p2, _p1, AB);

  SiconosVector AP(3);

  sub(p, _p1, AP);

  double norm = AB.norm2();
 
  scal(1.0/norm, AB, AB);

  SiconosVector tmp(3);

  cross_product(AB, AP, tmp);
  
  _d = tmp.norm2();

}

void Edge::computeNormal(SiconosVector p)
{

  SiconosVector AB(3);
  sub(_p2, _p1, AB);
 
  SiconosVector AP(3);
  sub(p, _p1, AP);  

  SiconosVector BA(3);
  sub(_p1, _p2, BA);

  double length = BA.norm2();

  //projection onto an edge

  double offset = inner_prod(AB, AP);  

  offset = offset / length;

  SiconosVector ABunit(3);

  scal(1/length, AB, ABunit);

  SiconosVector pproj(3);

  scal(offset, ABunit, pproj);

  SiconosVector tmpN(3);

  sub(p, pproj, tmpN);

  scal(1/tmpN.norm2(), tmpN, _n);

}

Vertex::Vertex(SiconosVector p1, int id) : _p1(p1), _id(id), _n(3)
{
    _d = 10000;
}

void Vertex::computeDistance(SiconosVector p)
{

  SiconosVector d(3);

  sub(p, _p1, d);

  _d = d.norm2();

}

void Vertex::computeNormal(SiconosVector p)
{

  SiconosVector d(3);

  sub(p, _p1, d);

  double dist = d.norm2();

  scal(1/dist, d, _n);

}

