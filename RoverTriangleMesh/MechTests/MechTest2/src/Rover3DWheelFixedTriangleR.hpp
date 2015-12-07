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

#include "CircularR.hpp"
#include <cmath>

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

class Rover3DWheelFixedTriangleR : public LagrangianScleronomousR, public std11::enable_shared_from_this<Rover3DWheelFixedTriangleR>
{

//private:
public:
  
  //Geometrical data (Tire thickness assumed 1, Number of contact points on the tire assumed 1)

  vect vert1, vert2, vert3; 

  //coeffs of the plane associated with the relation

  double A, B, C, D;

  //plane's normal unit vector

  vect n;

  double TireRadius;
  int TireMark;

  //array with RPY euler angles

  double eul[3];

  //default constructor

  Rover3DWheelFixedTriangleR();
  
  //function calculating the distance of points from a plane
  //Arguments: pointer to the array with distances, pointer to the array with robot state (positions - q0)
  //and pointer to the array with coordinates of contact point

  void calcDistance(double*, double*);

  //function which checks if two points are on the same side of a triangle edge
  //one point is a point to be checked, another is a point which belongs to the 
  //trinagle. it's an auxiliary function to be called three times for each edge
  //from within checkIfInsideTriangle(vect ) function.
  //if the result is true for all three edges, point belongs to the triangle.
  //arguments: triangle vertices, point to be checked

  bool checkIfSameSideOfEdge(vect, vect, vect, vect);

  //function which checks if the projection is inside the triangle
  //arguments: point to be checked 

  bool checkIfInsideTriangle(vect);

  //function which checks if the projection is inside the segment
  //arguments: point to be checked

  bool checkIfInsideSegment(vect, vect, vect);

  //function to compute minimun of two numbers
  
  double fcnMin(double, double);

  //function to compute maximum of two numbers
  
  double fcnMax(double, double);

  //dot product and cross product functions

  double dotProd(vect, vect);

  vect crossProd(vect, vect);

  //distance of a point from a segment

  double distFromSegment(vect A, vect B, vect C);

public:

  //Constructor accepts coords of three points, wheel mark, wheel radius
  
  Rover3DWheelFixedTriangleR(double, double, double, double, double, double, double, double, double, int, double);

  void computeh(const double, Interaction& inter);

  void computeJachq(const double, Interaction& inter);

};

TYPEDEF_SPTR(Rover3DWheelFixedTriangleR);

#endif /*Rover3DWheeelFixedTriangleR_hpp */

