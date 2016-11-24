/* Siconos-sample version 3.0.0, Copyright INRIA 2005-2008.
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
 * Contact: Vincent ACARY vincent.acary@inrialpes.fr 
*/
#include "Robot.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
int NCONT = 6;
double r = 20;
double PI=3.1415927;
double angleA=0.0;
double angleB=0.0;//atan(1/(106/132+1/tan(angleA)));
double CapK=-15000;

extern "C" void mass(unsigned int sizeOfq, const double *q, double *mass, unsigned int sizeZ, double* z)
{
  unsigned int n = sizeOfq;
  unsigned int n1 = n*n;

  // mass set to zero
  for (unsigned int i = 0; i < n1; i++)
    mass[i] = 0.0;	

  
  // compute mass matrix
  Inertia(mass,(double*)q);
 
}

extern "C" void FGyr(unsigned int sizeOfq, const double *q, const double *velocity, double *FGyr, unsigned int sizeZ, double* z)
{
  unsigned int n = sizeOfq;

  unsigned int i;
  
 
  // FGyr set to zero
  for (i = 0; i < n; i++)
    FGyr[i] = 0.0;	
  

  // compute mass matrix
  NLEffects(FGyr,(double*)q,(double*)velocity);


}

extern "C" void jacobianFGyrq(unsigned int sizeOfq, const double *q, const double *velocity, double *jacob, unsigned int sizeZ, double* z)
{
  unsigned int n = sizeOfq;
  unsigned int n1 = n*n;

  // set to zero
  for (unsigned int i = 0; i < n1; i++)
    jacob[i] = 0.0;	
  

  // compute jacobian matrix
  JacobianQNLEffects(jacob,(double *)q,(double *)velocity);
  
  
}	

extern "C" void jacobianVFGyr(unsigned int sizeOfq, const double *q,const  double *velocity, double *jacob, unsigned int sizeZ, double* z)
{
  unsigned int n = sizeOfq;
  unsigned int n1 = n*n;

  // set to zero
  for (unsigned int i = 0; i < n1; i++)
    jacob[i] = 0.0;	
  
  // compute jacobian matrix
  JacobianVNLEffects(jacob,(double *)q,(double *)velocity);
  
  
}

extern "C" void jacobFintQ(double time, unsigned int sizeOfq, const double *q,const  double *velocity, double *jacobFintQ, unsigned int sizeZ, double* z)
{ 
    jacobFintQ[(7-1)*(sizeOfq+1)]=-CapK;
    jacobFintQ[(8-1)*(sizeOfq+1)]=-CapK;

    jacobFintQ[(12-1)*(sizeOfq+1)]=-CapK;
    jacobFintQ[(13-1)*(sizeOfq+1)]=-CapK;

    jacobFintQ[(17-1)*(sizeOfq+1)]=-CapK;
    jacobFintQ[(18-1)*(sizeOfq+1)]=-CapK;

}

extern "C" void jacobFintV(double time, unsigned int sizeOfq, const double *q,const  double *velocity, double *jacobFintV, unsigned int sizeZ, double* z)
{ 
    jacobFintV[(7-1)*(sizeOfq+1)]=-CapK;
    jacobFintV[(8-1)*(sizeOfq+1)]=-CapK;

    jacobFintV[(12-1)*(sizeOfq+1)]=-CapK;
    jacobFintV[(13-1)*(sizeOfq+1)]=-CapK;

    jacobFintV[(17-1)*(sizeOfq+1)]=-CapK;
    jacobFintV[(18-1)*(sizeOfq+1)]=-CapK;

}
  
