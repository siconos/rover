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
#include <assert.h>


double kk = 0;
double kz=kk;
double b = 0.5;
double xi = 1/(sqrt(kk*kk+1));
double r = 0.4;
double rce=0.2;
double ln=1;

extern "C" void h0(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, unsigned int sizeZ, double* z)
{
  y[0] = q[1]-ln*sin(q[2])-kk*(q[0]-ln*cos(q[2]))-b;
}

extern "C" void G0(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, unsigned int sizeZ, double* z)
{
  double k0=kk;
  double xi0=xi;
  G[0] = -xi0*k0;
  G[1] = xi0;
  G[2] = xi0;
  G[3] = xi0*k0;
  G[4] = xi0*(-k0*ln*sin(q[2])-ln*cos(q[2]));
  G[5] = xi0*(ln*sin(q[2])-k0*ln*cos(q[2]));
  G[7]=-r;
}

extern "C" void h1(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, unsigned int sizeZ, double* z)
{
  y[0] = q[1]+ln*sin(q[2])-kk*(q[0]+ln*cos(q[2]))-b;
}

extern "C" void G1(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, unsigned int sizeZ, double* z)
{
  double k1=kk;
  double xi1=xi;
  G[0] = -xi1*k1;
  G[1] = xi1;
  G[2] = xi1;
  G[3] = xi1*k1;
  G[4] = xi1*(k1*ln*sin(q[2])+ln*cos(q[2]));
  G[5] = xi1*(-ln*sin(q[2])+k1*ln*cos(q[2]));
  G[9]=-r;
  
}

extern "C" void h2(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, unsigned int sizeZ, double* z)
{
  y[0] = q[6]-kk*q[5]-b;
}

extern "C" void G2(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, unsigned int sizeZ, double* z)
{
  double xin=xi;
  G[10] = -xin*kk;
  G[11] = xin;
  G[12] = xin;
  G[13] = xin*kk;
  G[14] = 0;
  G[15] = -rce; 
}


//-----------------------------------------------
extern "C" void h3(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, unsigned int sizeZ, double* z)
{
  y[0] = sqrt((q[1]-ln*sin(q[2])-q[6])*(q[1]-ln*sin(q[2])-q[6])+(q[0]-ln*cos(q[2])-q[5])*(q[0]-ln*cos(q[2])-q[5]))-(r+rce);
}

extern "C" void G3(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, unsigned int sizeZ, double* z)
{
  double kc=(q[5]-(q[0]-ln*cos(q[2])))/(q[1]-ln*sin(q[2])-q[6]);
  double xi3;
  xi3=1/(sqrt(1+kc*kc));
  G[0] = -xi3*kc;
  G[1] = xi3;
  G[2] = xi3;
  G[3] = xi3*kc;
  G[4] = xi3*(-kc*ln*sin(q[2])-ln*cos(q[2]));
  G[5] = xi3*(ln*sin(q[2])-kc*ln*cos(q[2]));
  G[7]=-r;
  G[10] = xi3*kc;
  G[11] = -xi3;
  G[12] = -xi3;
  G[13] = -xi3*kc;
  G[14] = 0;
  G[15] = rce; 
}

extern "C" void h4(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, unsigned int sizeZ, double* z)
{
  y[0] = sqrt((q[1]+ln*sin(q[2])-q[6])*(q[1]+ln*sin(q[2])-q[6])+(q[0]+ln*cos(q[2])-q[5])*(q[0]+ln*cos(q[2])-q[5]))-(r+rce);
}

extern "C" void G4(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, unsigned int sizeZ, double* z)
{
  double k4=(q[5]-(q[0]+ln*cos(q[2])))/(q[1]+ln*sin(q[2])-q[6]);
  double xi4;
  xi4=1/(sqrt(1+k4*k4));
  G[0] = -xi4*k4;
  G[1] = xi4;
  G[2] = xi4;
  G[3] = xi4*k4;
  G[4] = xi4*(k4*ln*sin(q[2])+ln*cos(q[2]));
  G[5] = xi4*(-ln*sin(q[2])+k4*ln*cos(q[2]));
  G[9]=-r;
  G[10] = xi4*k4;
  G[11] = -xi4;
  G[12] = -xi4;
  G[13] = -xi4*k4;
  G[14] = 0;
  G[15] = rce; 
  
}


// z[0] = R, z[1]=ln, z[2]=r2 (disk radius)

extern "C" void h5(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, unsigned int sizeZ, double* z)
{

  assert(sizeZ == 3);
  
  y[0] = sqrt((q[1]-z[1]*sin(q[2])-q[6])*(q[1]-z[1]*sin(q[2])-q[6])+(q[0]-z[1]*cos(q[2])-q[5])*(q[0]-z[1]*cos(q[2])-q[5]))-(z[0]+z[2]);

}

extern "C" void G5(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, unsigned int sizeZ, double* z)
{

  assert(sizeZ == 3);
  
  double r = z[0];
  double rce = z[2];
  double ln = z[1];
  
  double kc=(q[5]-(q[0]-ln*cos(q[2])))/(q[1]-ln*sin(q[2])-q[6]);
  double xi3;
  xi3=1/(sqrt(1+kc*kc));
  /*G[0] = -xi3*kc;
  G[1] = xi3;
  G[2] = xi3;
  G[3] = xi3*kc;
  G[4] = xi3*(-kc*ln*sin(q[2])-ln*cos(q[2]));
  G[5] = xi3*(ln*sin(q[2])-kc*ln*cos(q[2]));
  G[7]=-r;
  G[10] = xi3*kc;
  G[11] = -xi3;
  G[12] = -xi3;
  G[13] = -xi3*kc;
  G[14] = 0;
  G[15] = -rce; */
  G[0] = -xi3*kc;
  G[1] = xi3;
  G[2] = xi3;
  G[3] = xi3*kc;
  G[4] = xi3*(-kc*ln*sin(q[2])-ln*cos(q[2]));
  G[5] = xi3*(ln*sin(q[2])-kc*ln*cos(q[2]));
  G[7]=r;
  G[10] = xi3*kc;
  G[11] = -xi3;
  G[12] = -xi3;
  G[13] = -xi3*kc;
  G[14] = 0;
  G[15] = rce;
  
}


extern "C" void h6(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, unsigned int sizeZ, double* z)
{
  assert(sizeZ == 3);
    
  y[0] = sqrt((q[1]+z[1]*sin(q[2])-q[6])*(q[1]+z[1]*sin(q[2])-q[6])+(q[0]+z[1]*cos(q[2])-q[5])*(q[0]+z[1]*cos(q[2])-q[5]))-(z[0]+z[2]);

}


extern "C" void G6(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, unsigned int sizeZ, double* z)
{
  assert(sizeZ == 3);
  
  double r = z[0];
  double rce = z[2];
  double ln = z[1];
  
  double k4=(q[5]-(q[0]+ln*cos(q[2])))/(q[1]+ln*sin(q[2])-q[6]);
  double xi4;
  xi4=1/(sqrt(1+k4*k4));
  /*G[0] = -xi4*k4;
  G[1] = xi4;
  G[2] = xi4;
  G[3] = xi4*k4;
  G[4] = xi4*(k4*ln*sin(q[2])+ln*cos(q[2]));
  G[5] = xi4*(-ln*sin(q[2])+k4*ln*cos(q[2]));
  G[9]=-r;
  G[10] = xi4*k4;
  G[11] = -xi4;
  G[12] = -xi4;
  G[13] = -xi4*k4;
  G[14] = 0;
  G[15] = - rce; */
  G[0] = -xi4*k4;
  G[1] = xi4;
  G[2] = xi4;
  G[3] = xi4*k4;
  G[4] = xi4*(k4*ln*sin(q[2])+ln*cos(q[2]));
  G[5] = xi4*(-ln*sin(q[2])+k4*ln*cos(q[2]));
  G[9]= r;
  G[10] = xi4*k4;
  G[11] = -xi4;
  G[12] = -xi4;
  G[13] = -xi4*k4;
  G[14] = 0;
  G[15] = rce;
  
}


//--------------------------------------Static Disks------------------------------
// z[0] = R, z[1]=ln, z[2]=r2 (disk radius)

extern "C" void statich5(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, unsigned int sizeZ, double* z)
{

  assert(sizeZ == 3);
  
  y[0] = sqrt((q[1]-z[1]*sin(q[2])-q[6])*(q[1]-z[1]*sin(q[2])-q[6])+(q[0]-z[1]*cos(q[2])-q[5])*(q[0]-z[1]*cos(q[2])-q[5]))-(z[0]+z[2]);

}

extern "C" void staticG5(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, unsigned int sizeZ, double* z)
{

  assert(sizeZ == 3);
  
  double r = z[0];
  double rce = z[2];
  double ln = z[1];
  
  double kc=(q[5]-(q[0]-ln*cos(q[2])))/(q[1]-ln*sin(q[2])-q[6]);
  double xi3;
  xi3=1/(sqrt(1+kc*kc));
  /*G[0] = -xi3*kc;
  G[1] = xi3;
  G[2] = xi3;
  G[3] = xi3*kc;
  G[4] = xi3*(-kc*ln*sin(q[2])-ln*cos(q[2]));
  G[5] = xi3*(ln*sin(q[2])-kc*ln*cos(q[2]));
  G[7]=-r;
  G[10] = xi3*kc;
  G[11] = -xi3;
  G[12] = -xi3;
  G[13] = -xi3*kc;
  G[14] = 0;
  G[15] = -rce; */
  G[0] = -xi3*kc;
  G[1] = xi3;
  G[2] = xi3;
  G[3] = xi3*kc;
  G[4] = xi3*(-kc*ln*sin(q[2])-ln*cos(q[2]));
  G[5] = xi3*(ln*sin(q[2])-kc*ln*cos(q[2]));
  G[7]=r;
  /*G[10] = xi3*kc;
  G[11] = -xi3;
  G[12] = -xi3;
  G[13] = -xi3*kc;
  G[14] = 0;
  G[15] = rce;*/
  
}


extern "C" void statich6(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, unsigned int sizeZ, double* z)
{
  assert(sizeZ == 3);
    
  y[0] = sqrt((q[1]+z[1]*sin(q[2])-q[6])*(q[1]+z[1]*sin(q[2])-q[6])+(q[0]+z[1]*cos(q[2])-q[5])*(q[0]+z[1]*cos(q[2])-q[5]))-(z[0]+z[2]);

}


extern "C" void staticG6(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, unsigned int sizeZ, double* z)
{
  assert(sizeZ == 3);
  
  double r = z[0];
  double rce = z[2];
  double ln = z[1];
  
  double k4=(q[5]-(q[0]+ln*cos(q[2])))/(q[1]+ln*sin(q[2])-q[6]);
  double xi4;
  xi4=1/(sqrt(1+k4*k4));
  /*G[0] = -xi4*k4;
  G[1] = xi4;
  G[2] = xi4;
  G[3] = xi4*k4;
  G[4] = xi4*(k4*ln*sin(q[2])+ln*cos(q[2]));
  G[5] = xi4*(-ln*sin(q[2])+k4*ln*cos(q[2]));
  G[9]=-r;
  G[10] = xi4*k4;
  G[11] = -xi4;
  G[12] = -xi4;
  G[13] = -xi4*k4;
  G[14] = 0;
  G[15] = - rce; */
  G[0] = -xi4*k4;
  G[1] = xi4;
  G[2] = xi4;
  G[3] = xi4*k4;
  G[4] = xi4*(k4*ln*sin(q[2])+ln*cos(q[2]));
  G[5] = xi4*(-ln*sin(q[2])+k4*ln*cos(q[2]));
  G[9]= r;
  /*G[10] = xi4*k4;
  G[11] = -xi4;
  G[12] = -xi4;
  G[13] = -xi4*k4;
  G[14] = 0;
  G[15] = rce;*/
  
}


