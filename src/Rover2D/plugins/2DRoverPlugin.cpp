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

#include <stdio.h>
#include <math.h>
#include <cmath>

// extern double gravity;
// extern double m1;
// extern double m2;
// extern double l1;
//extern double l2;

double MY_kk = 0.2;
double b = 0.5;
double xi = 1.0/(sqrt(MY_kk*MY_kk+1.0));
double r = 1.5;
double lambda = 1; // the function of the ground is f(x)=sin(lambda*x)
 


extern "C" void h0(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, unsigned int sizeZ, double* z)
{ 
  //y[0] = q[1]-MY_kk*q[0]-b;
     y[0] = q[1]-sin(q[0]*lambda);
}


extern "C" void G0(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, unsigned int sizeZ, double* z)
{
  double k = lambda*cos(q[0]*lambda);
  double sintheta = k/(sqrt(k*k)+1.0);
  double costheta = 1/(sqrt(k*k)+1.0);
  
  G[0] = -sintheta;
  G[1] = costheta;
  G[2] = costheta;
  G[3] = sintheta;
  G[4] = 0.0;
  G[5] = -r;

 
  //G[0] = -xi*MY_kk;
  //G[1] = xi;
  //G[2] = xi;
  //G[3] = xi*MY_kk;
  //G[4] = 0.0;
  //G[5] = -r; 
  




  //G[0] = -xi*MY_kk;
  //G[1] = xi;
  //G[2] = xi*(-MY_kk*r*cos(q[2])-r*sin(q[2]));
  //G[3] = -xi;
  //G[4] = -xi*MY_kk;
  //G[5] = -(xi*(r*cos(q[2])-MY_kk*r*sin(q[2])));   
  //G[0]=-xi*MY_kk;
  //G[1]=xi;
  //G[2]=xi*(-MY_kk*r*cos(q[2])-r*sin(q[2]));
}


