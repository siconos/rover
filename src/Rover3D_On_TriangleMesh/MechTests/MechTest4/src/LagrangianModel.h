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
*/
/**
** @file LagrangianModel/Kondo-KHR1/LagrangianModel.h
** @author: Florence Billet
** Affiliation(s): INRIA, team BIPOP
** Email(s): florence.billet@inria.fr
** 
** @brief Compute the complete Dynamics
** 
**
*/
#ifndef __LagrangianModel_h
#define __LagrangianModel_h

#ifdef WINDOWS
#define extern __declspec (dllexport)
#endif

#define NDOF 23
#define NTAGS (34+1)
#define NCONT 8


/**
 * Compute the matrix of contact for a given robot state
 *
 * @param[out] CC Matrix of contact <em> dim NCONTx3(xyz) </em>
 * @param[in] q Joint State Vector <em> dim NDOF </em>
 */
extern  void
Contact(double *CC,double *q);


extern  void
Distance(double *CD,double *AngleT, double *q);
/**			 	    
 * Compute the matrix of contact jacobian for a given robot state
 *
 * @param[out] CJ Matrix of Contact Jacobian <em> dim (3xNCONT)*NDOF </em>
 * @param[in] q Joint State Vector <em> dim NDOF </em>
 */
extern void
ContactJacobian1(double *CJ,double *AngleT,double *q);

extern void
ContactJacobian2(double *CJ,double *AngleT,double *q);

extern void
ContactJacobian3(double *CJ,double *AngleT,double *q);

extern void
ContactJacobian4(double *CJ,double *AngleT,double *q);


extern void
ContactJacobian5(double *CJ,double *AngleT,double *q);

extern void
ContactJacobian6(double *CJ,double *AngleT,double *q);



/**			 	    
 * Compute the vector of contact hessians for a given robot state
 *
 * @param[out] H Vector of Contact Hessians <em> dim NCONT*3 </em>
 * @param[in] q Joint State Vector <em> dim NDOF </em>
 * @param[in] qdot Articular Velocity State Vector <em> dim NDOF </em>
 */
extern void
ContactHessian(double *H,double *q, double *qdot);

/**
 * Compute the matrix of Non Linear Effect (Coriolis + Gravity) 
 * for a given robot state
 *
 * @param[out] N Matrix of Coriolis <em> dim NDOF </em>
 * @param[in] q joint State Vector <em> dim NDOF </em>
 * @param[in] qdot Articular Velocity State Vector <em> dim NDOF </em>
 */
extern void
NLEffects(double *N, double *q, double *qdot);

/**			 	    
 * Compute the matrix of inertia for a given robot state
 *
 * @param[out] M Matrix of Inertia <em> dim NDOFxNDOF </em>
 * @param[in] q Joint State Vector <em> dim NDOF </em>
 */
extern void 
Inertia(double *M,double *q);

/**			 	    
 * Compute the matrix of tags for a given robot state
 * This matrix is made up of caracteristic points of robot
 * in the absolute referential. The end of matrix T contains
 * the coordinate of the biped mass center  
 *
 * @param[out] T Matrix of contact <em> dim 60 = NTAGSx3(xyz) </em>
 * @param[in] q Joint State Vector <em> dim NDOF </em>
 */
extern void 
Tags(double M[], double q[]);

extern void 
JacobianQNLEffects(double *jaco,double* q, double *qdot);

extern void 
JacobianVNLEffects(double *jaco,double* q, double *qdot);

extern void 
RRV(double RootRotationVector[4], double AngleT[3], double q[21]);

extern void 
PRV(double PlaneRotationVector[4], double AngleT[3], double q[21]);

#endif /* __LagrangianModel_h */
