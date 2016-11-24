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

/*! \file Rover3DWheeelFixedSphereR.h
  \brief SphereWheeel relation with a plan - Inherits from LagrangianScleronomousR
*/

#ifndef Rover3DWheeelFixedSphereR_h
#define Rover3DWheeelFixedSphereR_h

#include "CircularR.hpp"

class Rover3DWheelFixedSphereR : public LagrangianScleronomousR, public std11::enable_shared_from_this<Rover3DWheelFixedSphereR>
{
private:

  // Coordicate data (A,B,C)
  double r, A, B, C, WheelR;
  double _x,_y,_z,sphereR,TireR,TireT;
  int TireMark,NCont;

  Rover3DWheelFixedSphereR();

public:

  /** Constructor

  \Number of Wheel (int, Wheel Mark)
  \param A
  \param B
  \param C
  \param disk radius
  \Wheel Radius
  \Wheel Thickness
  */
  Rover3DWheelFixedSphereR(int,double, double, double,  double, double, double);

//  double distance(double, double, double, double);

  void computeh(SiconosVector& q, SiconosVector& z, SiconosVector& y);

  void computeJachq(SiconosVector& q, SiconosVector& z);

//  bool equal(double _A, double _B, double _C, double _D, double _r) const
//  { return (A==_A && B==_B && C==_C && D==_D && r==_r) ;}

};

TYPEDEF_SPTR(Rover3DWheelFixedSphereR);

#endif /* Rover3DWheeelFixedSphereR_h */
