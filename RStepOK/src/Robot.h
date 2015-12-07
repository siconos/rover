/* Copyright (C) INRIA 1999-2005
** 
** This program is free software; you can redistribute it and/or modify it
** under the terms of the GNU General Public License version 2 as published
** by the Free Software Foundation.
** 
** This program is distributed in the hope that it will be useful, but
** WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
** Public License for more details.
** 
** You should have received a copy of the GNU General Public License along
** with this program; if not, write to the Free Software Foundation, Inc.,
** 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
** 
** Author(s): Pierre-Brice Wieber
** Affiliation(s): INRIA, team BIPOP
** Email(s): Pierre-Brice.Wieber@inria.fr
** 
** Description:
** 
** Modifications:
** $Log: LagrangianModel.h,v $
** Revision 3.0.0.1  2005/02/08 13:05:22  rpissard
** version start HuMAnS
**
*/
#include <math.h>

extern "C" void NLEffects(double *N,double* q, double *qdot);

extern "C" void Inertia(double *M, double *q);

extern "C" void JacobianQNLEffects(double *jaco,double* q, double *qdot);

extern "C" void JacobianVNLEffects(double *jaco,double* q, double *qdot);

extern "C" void Contact(double *CC, double* q);

extern "C" void Distance(double *CD,double *AngleT,  double* q);

extern "C" void ContactJacobian1(double *CJ, double *q);

extern "C" void ContactJacobian2(double *CJ, double *q);

extern "C" void ContactJacobian3(double *CJ, double *q);

extern "C" void ContactJacobian4(double *CJ, double *q);

extern "C" void ContactJacobian5(double *CJ, double *q);

extern "C" void ContactJacobian6(double *CJ, double *q);

extern "C" void Tags(double *M, double *q);

extern "C" void RRV(double RootRotationVector[4], double AngleT[3],double q[21]);

extern "C" void PRV(double PlaneRotationVector[4],double AngleT[3], double q[21]);
