/* Siconos-Kernel, Copyright INRIA 2005-2012.
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Contact: Vincent ACARY, siconos-team@lists.gforge.inria.fr
*/

#ifndef RoverIO_H
#define RoverIO_H

#include "SiconosMatrix.hpp"
#include "SiconosVector.hpp"
#include "SimpleMatrix.hpp"
#include "SiconosVectorFriends.hpp"
#include "SiconosAlgebra.hpp"

#include "Rover3DWheelFixedTriangleR.hpp"
#include "RoverBody.hpp"

#include <Model.hpp>
#include <Simulation.hpp>
#include <NonSmoothDynamicalSystem.hpp>
#include <SimulationTypeDef.hpp>
#include <NonSmoothLaw.hpp>

#include <map>
#include <string>
#include <vector>

class RoverIO : public std11::enable_shared_from_this<RoverIO> 
{

private:

  SP::Model _model;

  SP::NonSmoothLaw _nslaw;

  std::ofstream posStream;

  std::ofstream forcesStream;

  std::ofstream solverStream;

  std::ofstream staticStream;

public:

  /** Constructors
   */

  RoverIO(std::string posOutput = "dpos.dat", std::string forcesOutput = "cf.dat", std::string solverOutput = "solv.dat", std::string staticOutput="spos.dat");

  /** Destructor closing files
   */

  ~RoverIO();

  /** Output functions
   */

  void outputPositions(double, double*, double*);

  void outputForces(double, SP::Model, SP::NonSmoothLaw);

  void outputSolver(double, SP::OneStepNSProblem); 

  void outputStatObjects(double);

  //for testing
  void test();

private:

  /** auxillary functions
   */

  SimpleMatrix zyxEulersToRotMatrix(double alpha, double beta, double gamma);
  SiconosVector axisAngleToQuat(double, double, double, double);
  SiconosVector eulToQuat(double, double, double);
  SiconosVector quatCombine(SiconosVector, SiconosVector);
  SiconosVector rotMatrixToQuat(SimpleMatrix);
  SiconosVector rotMatrixToQuat2(SimpleMatrix);
  SimpleMatrix quatToRotMatrix(double w, double x, double y, double z);
 
};

TYPEDEF_SPTR(RoverIO);

#endif /*RoverIO_H*/
