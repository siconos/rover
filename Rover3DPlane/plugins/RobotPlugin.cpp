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
#include <stdio.h>
#include <math.h>

int NCONT = 6;
double r = 20;
double PI=3.1415927;
double angleA=0.1;
double angleB=0.1;//atan(1/(106/132+1/tan(angleA)));
double CapK=-15000;
static int sFirst =1 ;
static double *sQ0;
static double RotationAngle[3]= {0.1,0.0,0.1};


extern "C" void mass(unsigned int sizeOfq, const double *q, double *mass, unsigned int sizeZ, double* z)
{
  unsigned int n = sizeOfq;
  unsigned int n1 = n*n;

  unsigned int i,j;
  
  
  // mass set to zero
  for (i = 0; i < n1; i++)
    mass[i] = 0.0;	

  
  // compute mass matrix
  Inertia(mass,(double*)q);
 
}

extern "C" void NNL(unsigned int sizeOfq, const double *q, const double *velocity, double *NNL, unsigned int sizeZ, double* z)
{
  unsigned int n = sizeOfq;

  unsigned int i;
  
 
  // NNL set to zero
  for (i = 0; i < n; i++)
    NNL[i] = 0.0;	
  

  // compute mass matrix
  NLEffects(NNL,(double*)q,(double*)velocity);


}

extern "C" void jacobianNNLq(unsigned int sizeOfq, const double *q, const double *velocity, double *jacob, unsigned int sizeZ, double* z)
{
  unsigned int n = sizeOfq;
  unsigned int n1 = n*n;

  unsigned int i,j;
  
 
  // set to zero
  for (i = 0; i < n1; i++)
    jacob[i] = 0.0;	
  

  // compute jacobian matrix
  JacobianQNLEffects(jacob,(double *)q,(double *)velocity);
  
  
}	

extern "C" void jacobianVNNL(unsigned int sizeOfq, const double *q,const  double *velocity, double *jacob, unsigned int sizeZ, double* z)
{
  unsigned int n = sizeOfq;
  unsigned int n1 = n*n;

  unsigned int i,j;
  

  // set to zero
  for (i = 0; i < n1; i++)
    jacob[i] = 0.0;	
  
  // compute jacobian matrix
  JacobianVNLEffects(jacob,(double *)q,(double *)velocity);
  
  
}


extern "C" void h0(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, unsigned int sizeZ, double* z)
{ 
  double * tmp = (double *)malloc(NCONT*sizeof(double));
  double * tmpAngle = (double *)malloc(3*sizeof(double));
  tmpAngle[0] = RotationAngle[0];
  tmpAngle[1] = RotationAngle[1];
  tmpAngle[2] = RotationAngle[2];
  Distance(tmp, tmpAngle,(double *)q); 
  y[0] = tmp[0];  
  //cout << "y[0]= " << tmp[0]-12.5 << endl;
   free(tmp); 
   free(tmpAngle);
}


extern "C" void G0(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, unsigned int sizeZ, double* z)
{
  //FL
  double * tmpAngle = (double *)malloc(3*sizeof(double));
  tmpAngle[0] = RotationAngle[0];
  tmpAngle[1] = RotationAngle[1];
  tmpAngle[2] = RotationAngle[2];
  ContactJacobian1(G,tmpAngle,(double *)q);
  G[28]=G[28]+r;//*cos(angleB);//q[7]);
  G[29]=G[29];//+r*sin(angleB);//q[7]); //cout << "y[0]= " << angleB << endl;

  free(tmpAngle);
}

extern "C" void h1(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, unsigned int sizeZ, double* z)
{
  double * tmpAngle = (double *)malloc(3*sizeof(double));
  tmpAngle[0] = RotationAngle[0];
  tmpAngle[1] = RotationAngle[1];
  tmpAngle[2] = RotationAngle[2];
  double * tmp = (double *)malloc(NCONT*sizeof(double));
  Distance(tmp,tmpAngle,(double *)q);
  y[0] = tmp[1]; //cout << "y[0]= " << tmp[1] << endl;
  //printf("%e ",y[0]);
 free(tmp); free(tmpAngle);
}

extern "C" void G1(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, unsigned int sizeZ, double* z)
{
  //FR
  double * tmpAngle = (double *)malloc(3*sizeof(double));
  tmpAngle[0] = RotationAngle[0];
  tmpAngle[1] = RotationAngle[1];
  tmpAngle[2] = RotationAngle[2];
  ContactJacobian2(G,tmpAngle,(double *)q);
  G[31]=G[31]+r;//*cos(angleA);//q[8]);
  G[32]=G[32];//+r*sin(angleA);//q[8]);
  free(tmpAngle);
}

extern "C" void h2(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, unsigned int sizeZ, double* z)
{ 
  double * tmpAngle = (double *)malloc(3*sizeof(double));
  tmpAngle[0] = RotationAngle[0];
  tmpAngle[1] = RotationAngle[1];
  tmpAngle[2] = RotationAngle[2];
  double * tmp = (double *)malloc(NCONT*sizeof(double));
  Distance(tmp, tmpAngle,(double *)q); //cout << "y[0]= " << tmp[2] << endl;
  y[0] = tmp[2]; 
  free(tmp); free(tmpAngle); 
}


extern "C" void G2(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, unsigned int sizeZ, double* z)
{ //ML
  double * tmpAngle = (double *)malloc(3*sizeof(double));
  tmpAngle[0] = RotationAngle[0];
  tmpAngle[1] = RotationAngle[1];
  tmpAngle[2] = RotationAngle[2];
  ContactJacobian3(G,tmpAngle,(double *)q);
  G[43]=G[43]+r;//*cos(0.0);//q[12]);
  G[44]=G[44];//+r*sin(0.0);//q[12]);
  free(tmpAngle);
}

extern "C" void h3(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, unsigned int sizeZ, double* z, double *CDTmp)
{

  double * tmpAngle = (double *)malloc(3*sizeof(double));
  tmpAngle[0] = RotationAngle[0];
  tmpAngle[1] = RotationAngle[1];
  tmpAngle[2] = RotationAngle[2];
  double * tmp = (double *)malloc(NCONT*sizeof(double));
  Distance(tmp,tmpAngle,(double *)q); //cout << "y[0]= " << tmp[3] << endl;
  y[0] = tmp[3];  
  free(tmp); free(tmpAngle);
}

extern "C" void G3(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, unsigned int sizeZ, double* z)
{
  //BL

  double * tmpAngle = (double *)malloc(3*sizeof(double));
  tmpAngle[0] = RotationAngle[0];
  tmpAngle[1] = RotationAngle[1];
  tmpAngle[2] = RotationAngle[2];
  ContactJacobian4(G,tmpAngle,(double *)q);
  G[46]=G[46]+r;//*cos(0.0);//q[13]);
  G[47]=G[47];//+r*sin(0.0);//q[13]);
  free(tmpAngle);
}


extern "C" void h4(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, unsigned int sizeZ, double* z)
{ 
  double * tmpAngle = (double *)malloc(3*sizeof(double));
  tmpAngle[0] = RotationAngle[0];
  tmpAngle[1] = RotationAngle[1];
  tmpAngle[2] = RotationAngle[2];
  double * tmp = (double *)malloc(NCONT*sizeof(double));
  Distance(tmp, tmpAngle,(double *)q); //cout << "y[0]= " << tmp[4] << endl;
  y[0] = tmp[4]; 
  free(tmp); free(tmpAngle); 
}


extern "C" void G4(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, unsigned int sizeZ, double* z)
{  //MR

  double * tmpAngle = (double *)malloc(3*sizeof(double));
  tmpAngle[0] = RotationAngle[0];
  tmpAngle[1] = RotationAngle[1];
  tmpAngle[2] = RotationAngle[2];
  ContactJacobian5(G,tmpAngle,(double *)q);
  G[58]=G[58]+r;//*cos(0.0);//q[17]);
  G[59]=G[59];//+r*sin(0.0);//q[17]);

  free(tmpAngle);
}

extern "C" void h5(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* y, unsigned int sizeZ, double* z, double *CDTmp)
{

  double * tmpAngle = (double *)malloc(3*sizeof(double));
  tmpAngle[0] = RotationAngle[0];
  tmpAngle[1] = RotationAngle[1];
  tmpAngle[2] = RotationAngle[2];
  double * tmp = (double *)malloc(NCONT*sizeof(double));
  Distance(tmp,tmpAngle,(double *)q); 
  //cout << "y[0]= " << tmp[5] << endl;
  y[0] = tmp[5];  
  free(tmp); free(tmpAngle);
}

extern "C" void G5(unsigned int sizeOfq, const double* q, unsigned int sizeOfY, double* G, unsigned int sizeZ, double* z)
{

  double * tmpAngle = (double *)malloc(3*sizeof(double));
  tmpAngle[0] = RotationAngle[0];
  tmpAngle[1] = RotationAngle[1];
  tmpAngle[2] = RotationAngle[2];
  //BR
  ContactJacobian6(G,tmpAngle,(double *)q);
  G[61]=G[61]+r;//*cos(0.0);//q[18]);
  G[62]=G[62];//+r*sin(0.0);//q[18]);
  
  
}



//------------------PID Control-----------------------


extern "C" void U(double time, unsigned int sizeOfq, const double *q,const  double *velocity, double *U, unsigned int sizeZ, double *z)
{  
   if (sFirst){
                sQ0=(double *)malloc(sizeOfq * sizeof(double));
                 for (int i=0;i<sizeOfq; i++)
                 sQ0[i]=q[i];
		sFirst=0;
	       }
	
   
   U[7] = -CapK*(q[7]-sQ0[7])-CapK*velocity[7];
   U[8] = -CapK*(q[8]-sQ0[8])-CapK*velocity[8];

   U[12] = -CapK*(q[12]-sQ0[12])-CapK*velocity[12];
   U[13] = -CapK*(q[13]-sQ0[13])-CapK*velocity[13]; 

   U[17] = -CapK*(q[17]-sQ0[17])-CapK*velocity[17];
   U[18] = -CapK*(q[18]-sQ0[18])-CapK*velocity[18];
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
  
