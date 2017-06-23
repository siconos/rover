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
 * Relation Implementation of TrasysRelLg.hpp
 * Author: Jan Michalczyk
 * Team: Bipop
*/

#include "RoverIO.hpp"
#include "RoverBody.hpp"

#include <vector>
#include <cmath>
#include "op3x3.h"
#include <algorithm> 
#include <iostream>
#include <iomanip>
#include <fstream>

#include <NewtonImpactFrictionNSL.hpp>
#include <FrictionContact.hpp>

/*Quaternion convention for vtk - w x y z*/

using namespace std;

RoverIO::RoverIO(string posOutput, string forcesOutput, string solverOutput, string staticOutput) : posStream(posOutput), forcesStream(forcesOutput), solverStream(solverOutput), staticStream(staticOutput)
{

  posStream.precision(15);
  forcesStream.precision(15);
  solverStream.precision(15);
  staticStream.precision(15);

}

RoverIO::~RoverIO()
{

  //closing the output files

  posStream.close();

  forcesStream.close();

  solverStream.close();

  staticStream.close();

}

SimpleMatrix RoverIO::quatToRotMatrix(double w, double x, double y, double z){

  SimpleMatrix rotMatrix(3, 3);

  rotMatrix.setValue(0, 0, 1-2*pow(y,2)-2*pow(z,2));
  rotMatrix.setValue(0, 1, 2*x*y+2*w*z);
  rotMatrix.setValue(0, 2, 2*x*z-2*w*y);
  rotMatrix.setValue(1, 0, 2*x*y-2*w*z);
  rotMatrix.setValue(1, 1, 1-2*pow(x,2)-2*pow(z,2));
  rotMatrix.setValue(1, 2, 2*y*z+2*w*x);
  rotMatrix.setValue(2, 0, 2*x*z+2*w*y);
  rotMatrix.setValue(2, 1, 2*y*z-2*w*x);
  rotMatrix.setValue(2, 2, 1-2*pow(x,2)-2*pow(y,2));

  return rotMatrix;

}

SiconosVector RoverIO::axisAngleToQuat(double ang, double ax1, double ax2, double ax3){

  double q[4];

  SiconosVector qResult(4);

  double axNorm = sqrt(pow(ax1, 2) + pow(ax2, 2) + pow(ax3, 2));

  double axis1Norm = ax1/axNorm;
  double axis2Norm = ax2/axNorm;
  double axis3Norm = ax3/axNorm;

  q[0] = cos(ang/2);
  q[1] = axis1Norm*sin(ang/2);
  q[2] = axis2Norm*sin(ang/2);
  q[3] = axis3Norm*sin(ang/2);

  double qNorm = sqrt(pow(q[0], 2) + pow(q[1], 2) + pow(q[2], 2) + pow(q[3], 2));

  qResult.setValue(0, q[0]/qNorm);
  qResult.setValue(1, q[1]/qNorm);
  qResult.setValue(2, q[2]/qNorm);
  qResult.setValue(3, q[3]/qNorm);

  return qResult;

}

SiconosVector RoverIO::eulToQuat(double r, double p, double y){

  SiconosVector qx(4);
  SiconosVector qy(4);
  SiconosVector qz(4);

  SiconosVector qResult(4);

  qx = axisAngleToQuat(r, 1.0, 0.0, 0.0);
  qy = axisAngleToQuat(p, 0.0, 1.0, 0.0);
  qz = axisAngleToQuat(y, 0.0, 0.0, 1.0);

  qResult.setValue(0, qz.getValue(0)*qx.getValue(0)*qy.getValue(0) - qz.getValue(3)*qx.getValue(1)*qy.getValue(2));
  qResult.setValue(1, qz.getValue(0)*qx.getValue(1)*qy.getValue(0) + qz.getValue(3)*qx.getValue(0)*qy.getValue(2));
  qResult.setValue(2, -qz.getValue(3)*qx.getValue(1)*qy.getValue(0) + qz.getValue(0)*qx.getValue(0)*qy.getValue(2));  
  qResult.setValue(3, qz.getValue(3)*qx.getValue(0)*qy.getValue(0) + qz.getValue(0)*qx.getValue(1)*qy.getValue(2));

  return qResult;

}

SiconosVector RoverIO::quatCombine(SiconosVector q1, SiconosVector q2){

  SiconosVector qResult(4);

  qResult.setValue(0, q1.getValue(0)*q2.getValue(0) - q1.getValue(1)*q2.getValue(1) - q1.getValue(2)*q2.getValue(2) - q1.getValue(3)*q2.getValue(3));
  qResult.setValue(1, q1.getValue(0)*q2.getValue(1) + q1.getValue(1)*q2.getValue(0) + q1.getValue(2)*q2.getValue(3) - q1.getValue(3)*q2.getValue(2));
  qResult.setValue(2, q1.getValue(0)*q2.getValue(2) + q1.getValue(2)*q2.getValue(0) + q1.getValue(3)*q2.getValue(1) - q1.getValue(1)*q2.getValue(3));
  qResult.setValue(3, q1.getValue(0)*q2.getValue(3) + q1.getValue(3)*q2.getValue(0) + q1.getValue(1)*q2.getValue(2) - q1.getValue(2)*q2.getValue(1));

  return qResult;

}

SiconosVector RoverIO::rotMatrixToQuat(SimpleMatrix rotMatrix){

  SiconosVector qResult(4);

  double tr = rotMatrix.getValue(0, 0) + rotMatrix.getValue(1, 1) + rotMatrix.getValue(2, 2);

    if(tr > 0){ 

      double S = 0.5 / sqrt(tr + 1.0); // S=4*qw 

      qResult.setValue(0, 0.25 / S);
      qResult.setValue(1, (rotMatrix.getValue(2, 1) - rotMatrix.getValue(1, 2)) * S);
      qResult.setValue(2, (rotMatrix.getValue(0, 2) - rotMatrix.getValue(2, 0)) * S); 
      qResult.setValue(3, (rotMatrix.getValue(1, 0) - rotMatrix.getValue(0, 1)) * S); 

    }
    else{

      if((rotMatrix.getValue(0, 0) > rotMatrix.getValue(1, 1))&&(rotMatrix.getValue(0, 0) > rotMatrix.getValue(2, 2))){ 

        double S = 2.0*sqrt(1.0 + rotMatrix.getValue(0, 0) - rotMatrix.getValue(1, 1) - rotMatrix.getValue(2, 2)); // S=4*qx 
        
        qResult.setValue(0, (rotMatrix.getValue(2, 1) - rotMatrix.getValue(1, 2)) / S);
        qResult.setValue(1, 0.25 * S);
        qResult.setValue(2, (rotMatrix.getValue(0, 1) + rotMatrix.getValue(1, 0)) / S); 
        qResult.setValue(3, (rotMatrix.getValue(0, 2) + rotMatrix.getValue(2, 0)) / S); 
        
      }
      else if(rotMatrix.getValue(1, 1) > rotMatrix.getValue(2, 2)){ 
        
        double S = 2.0*sqrt(1.0 + rotMatrix.getValue(1, 1) - rotMatrix.getValue(0, 0) - rotMatrix.getValue(2, 2)); // S=4*qy
        
        qResult.setValue(0, (rotMatrix.getValue(0, 2) - rotMatrix.getValue(2, 0)) / S);
        qResult.setValue(1, (rotMatrix.getValue(0, 1) + rotMatrix.getValue(1, 0)) / S); 
        qResult.setValue(2, 0.25 * S);
        qResult.setValue(3, (rotMatrix.getValue(1, 2) + rotMatrix.getValue(2, 1)) / S); 
        
      }
      else{ 
        
        double S = 2.0*sqrt(1.0 + rotMatrix.getValue(2, 2) - rotMatrix.getValue(0, 0) - rotMatrix.getValue(1, 1)); // S=4*qz
        
        qResult.setValue(0, (rotMatrix.getValue(1, 0) - rotMatrix.getValue(0, 1)) / S);
        qResult.setValue(1, (rotMatrix.getValue(0, 2) + rotMatrix.getValue(2, 0)) / S);
        qResult.setValue(2, (rotMatrix.getValue(1, 2) + rotMatrix.getValue(2, 1)) / S);
        qResult.setValue(3, 0.25 * S);
        
      }

    }

    return qResult;

}

SiconosVector RoverIO::rotMatrixToQuat2(SimpleMatrix rotMatrix){

  SiconosVector qResult(4);

  qResult(0) = sqrt( std::max( 0.0, 1 + rotMatrix.getValue(0,0) + rotMatrix.getValue(1,1) + rotMatrix.getValue(2,2) ) ) / 2;
  qResult(1) = sqrt( std::max( 0.0, 1 + rotMatrix.getValue(0,0) - rotMatrix.getValue(1,1) - rotMatrix.getValue(2,2) ) ) / 2;
  qResult(2) = sqrt( std::max( 0.0, 1 - rotMatrix.getValue(0,0) + rotMatrix.getValue(1,1) - rotMatrix.getValue(2,2) ) ) / 2;
  qResult(3) = sqrt( std::max( 0.0, 1 - rotMatrix.getValue(0,0) - rotMatrix.getValue(1,1) + rotMatrix.getValue(2,2) ) ) / 2;
  qResult(1) = qResult(1) * copysign( 1.0, qResult(1) * ( rotMatrix.getValue(2,1) - rotMatrix.getValue(1,2) ) );
  qResult(2) = qResult(2) * copysign( 1.0, qResult(2) * ( rotMatrix.getValue(0,2) - rotMatrix.getValue(2,0) ) );
  qResult(3) = qResult(3) * copysign( 1.0, qResult(3) * ( rotMatrix.getValue(1,0) - rotMatrix.getValue(0,1) ) );

  return qResult;

}

/*function below to compute rotation matrix based on euler angles (Z-Y-X convention around current axis)*/

SimpleMatrix RoverIO::zyxEulersToRotMatrix(double alpha, double beta, double gamma){

  SimpleMatrix rotMatrix(3, 3);

  SimpleMatrix rotX(3, 3);

  rotX.setValue(0, 0, 1);
  rotX.setValue(0, 1, 0);
  rotX.setValue(0, 2, 0);
  rotX.setValue(1, 0, 0);
  rotX.setValue(1, 1, cos(alpha));
  rotX.setValue(1, 2, -sin(alpha));
  rotX.setValue(2, 0, 0);
  rotX.setValue(2, 1, sin(alpha));
  rotX.setValue(2, 2, cos(alpha));

  SimpleMatrix rotY(3, 3);
  
  rotY.setValue(0, 0, cos(beta));
  rotY.setValue(0, 1, 0);
  rotY.setValue(0, 2, sin(beta));
  rotY.setValue(1, 0, 0);
  rotY.setValue(1, 1, 1);
  rotY.setValue(1, 2, 0);
  rotY.setValue(2, 0, -sin(beta));
  rotY.setValue(2, 1, 0);
  rotY.setValue(2, 2, cos(beta));

  SimpleMatrix rotZ(3, 3);

  rotZ.setValue(0, 0, cos(gamma));
  rotZ.setValue(0, 1, -sin(gamma));
  rotZ.setValue(0, 2, 0);
  rotZ.setValue(1, 0, sin(gamma));
  rotZ.setValue(1, 1, cos(gamma));
  rotZ.setValue(1, 2, 0);
  rotZ.setValue(2, 0, 0);
  rotZ.setValue(2, 1, 0);
  rotZ.setValue(2, 2, 1);

  //multiplication in the right order

  prod(rotZ, rotY, rotMatrix);

  SimpleMatrix rotFinMatrix(3, 3);

  prod(rotMatrix, rotX, rotFinMatrix);

  return rotFinMatrix;

}

void RoverIO::outputPositions(double time, double* Tags, double* qs){

  //version for wheels only - tags contain normal vectors - apply offset on z according to 3DROV scene (+1.5)

  //rotation matrices
  
  SimpleMatrix wheelFL(3, 3);
  SimpleMatrix wheelFR(3, 3);
  SimpleMatrix wheelCR(3, 3);
  SimpleMatrix wheelCL(3, 3);
  SimpleMatrix wheelRL(3, 3);
  SimpleMatrix wheelRR(3, 3);

  SimpleMatrix trunk(3, 3);

  //quaternions

  SiconosVector wheelFLq(4);
  SiconosVector wheelFRq(4);
  SiconosVector wheelCRq(4);
  SiconosVector wheelCLq(4);
  SiconosVector wheelRLq(4);
  SiconosVector wheelRRq(4);

  SiconosVector trunkq(4);

  //positions

  SiconosVector wheelFLp(3);
  SiconosVector wheelFRp(3);
  SiconosVector wheelCRp(3);
  SiconosVector wheelCLp(3);
  SiconosVector wheelRLp(3);
  SiconosVector wheelRRp(3);

  SiconosVector trunkp(3);

  wheelRLp.setValue(0, Tags[7]);   //x
  wheelRLp.setValue(1, Tags[51]);  //y
  wheelRLp.setValue(2, Tags[95]);  //z

  wheelRRp.setValue(0, Tags[8]);
  wheelRRp.setValue(1, Tags[52]);
  wheelRRp.setValue(2, Tags[96]);

  wheelCLp.setValue(0, Tags[15]);
  wheelCLp.setValue(1, Tags[59]);
  wheelCLp.setValue(2, Tags[103]);

  wheelFLp.setValue(0, Tags[16]);
  wheelFLp.setValue(1, Tags[60]);
  wheelFLp.setValue(2, Tags[104]);

  wheelCRp.setValue(0, Tags[23]);
  wheelCRp.setValue(1, Tags[67]);
  wheelCRp.setValue(2, Tags[111]);

  wheelFRp.setValue(0, Tags[24]);
  wheelFRp.setValue(1, Tags[68]);
  wheelFRp.setValue(2, Tags[112]);

  /*trunk's center point and rotation matrix*/

  trunkp.setValue(0, qs[0]);
  trunkp.setValue(1, qs[1]);
  trunkp.setValue(2, qs[2]);

  trunk = zyxEulersToRotMatrix(qs[3], qs[4], qs[5]);

  //normal vectors of wheels

  SiconosVector tmpNormX(3);
  SiconosVector tmpNormY(3);
  SiconosVector tmpNormZ(3);

  //RL

  tmpNormX.setValue(0, Tags[25]);
  tmpNormX.setValue(1, Tags[69]);
  tmpNormX.setValue(2, Tags[113]);

  tmpNormY.setValue(0, Tags[26]);
  tmpNormY.setValue(1, Tags[70]);
  tmpNormY.setValue(2, Tags[114]);

  tmpNormZ.setValue(0, Tags[27]);
  tmpNormZ.setValue(1, Tags[71]);
  tmpNormZ.setValue(2, Tags[115]);

  sub(tmpNormX, wheelRLp, tmpNormX);
  sub(tmpNormY, wheelRLp, tmpNormY);
  sub(tmpNormZ, wheelRLp, tmpNormZ);

  wheelRL.setValue(0, 0, tmpNormX.getValue(0)); //x
  wheelRL.setValue(1, 0, tmpNormX.getValue(1)); //y
  wheelRL.setValue(2, 0, tmpNormX.getValue(2)); //z
  wheelRL.setValue(0, 1, tmpNormY.getValue(0)); //x
  wheelRL.setValue(1, 1, tmpNormY.getValue(1)); //y
  wheelRL.setValue(2, 1, tmpNormY.getValue(2)); //z
  wheelRL.setValue(0, 2, tmpNormZ.getValue(0)); //x
  wheelRL.setValue(1, 2, tmpNormZ.getValue(1)); //y
  wheelRL.setValue(2, 2, tmpNormZ.getValue(2)); //z

  //RR

  tmpNormX.setValue(0, Tags[28]);
  tmpNormX.setValue(1, Tags[72]);
  tmpNormX.setValue(2, Tags[116]);

  tmpNormY.setValue(0, Tags[29]);
  tmpNormY.setValue(1, Tags[73]);
  tmpNormY.setValue(2, Tags[117]);

  tmpNormZ.setValue(0, Tags[30]);
  tmpNormZ.setValue(1, Tags[74]);
  tmpNormZ.setValue(2, Tags[118]);

  sub(tmpNormX, wheelRRp, tmpNormX);
  sub(tmpNormY, wheelRRp, tmpNormY);
  sub(tmpNormZ, wheelRRp, tmpNormZ);

  wheelRR.setValue(0, 0, tmpNormX.getValue(0)); //x
  wheelRR.setValue(1, 0, tmpNormX.getValue(1)); //y
  wheelRR.setValue(2, 0, tmpNormX.getValue(2)); //z
  wheelRR.setValue(0, 1, tmpNormY.getValue(0)); //x
  wheelRR.setValue(1, 1, tmpNormY.getValue(1)); //y
  wheelRR.setValue(2, 1, tmpNormY.getValue(2)); //z
  wheelRR.setValue(0, 2, tmpNormZ.getValue(0)); //x
  wheelRR.setValue(1, 2, tmpNormZ.getValue(1)); //y
  wheelRR.setValue(2, 2, tmpNormZ.getValue(2)); //z

  //CL

  tmpNormX.setValue(0, Tags[31]);
  tmpNormX.setValue(1, Tags[75]);
  tmpNormX.setValue(2, Tags[119]);

  tmpNormY.setValue(0, Tags[32]);
  tmpNormY.setValue(1, Tags[76]);
  tmpNormY.setValue(2, Tags[120]);

  tmpNormZ.setValue(0, Tags[33]);
  tmpNormZ.setValue(1, Tags[77]);
  tmpNormZ.setValue(2, Tags[121]);

  sub(tmpNormX, wheelCLp, tmpNormX);
  sub(tmpNormY, wheelCLp, tmpNormY);
  sub(tmpNormZ, wheelCLp, tmpNormZ);

  wheelCL.setValue(0, 0, tmpNormX.getValue(0)); //x
  wheelCL.setValue(1, 0, tmpNormX.getValue(1)); //y
  wheelCL.setValue(2, 0, tmpNormX.getValue(2)); //z
  wheelCL.setValue(0, 1, tmpNormY.getValue(0)); //x
  wheelCL.setValue(1, 1, tmpNormY.getValue(1)); //y
  wheelCL.setValue(2, 1, tmpNormY.getValue(2)); //z
  wheelCL.setValue(0, 2, tmpNormZ.getValue(0)); //x
  wheelCL.setValue(1, 2, tmpNormZ.getValue(1)); //y
  wheelCL.setValue(2, 2, tmpNormZ.getValue(2)); //z

  //FL

  tmpNormX.setValue(0, Tags[34]);
  tmpNormX.setValue(1, Tags[78]);
  tmpNormX.setValue(2, Tags[122]);

  tmpNormY.setValue(0, Tags[35]);
  tmpNormY.setValue(1, Tags[79]);
  tmpNormY.setValue(2, Tags[123]);

  tmpNormZ.setValue(0, Tags[36]);
  tmpNormZ.setValue(1, Tags[80]);
  tmpNormZ.setValue(2, Tags[124]);

  sub(tmpNormX, wheelFLp, tmpNormX);
  sub(tmpNormY, wheelFLp, tmpNormY);
  sub(tmpNormZ, wheelFLp, tmpNormZ);

  wheelFL.setValue(0, 0, tmpNormX.getValue(0)); //x
  wheelFL.setValue(1, 0, tmpNormX.getValue(1)); //y
  wheelFL.setValue(2, 0, tmpNormX.getValue(2)); //z
  wheelFL.setValue(0, 1, tmpNormY.getValue(0)); //x
  wheelFL.setValue(1, 1, tmpNormY.getValue(1)); //y
  wheelFL.setValue(2, 1, tmpNormY.getValue(2)); //z
  wheelFL.setValue(0, 2, tmpNormZ.getValue(0)); //x
  wheelFL.setValue(1, 2, tmpNormZ.getValue(1)); //y
  wheelFL.setValue(2, 2, tmpNormZ.getValue(2)); //z

  //CR

  tmpNormX.setValue(0, Tags[37]);
  tmpNormX.setValue(1, Tags[81]);
  tmpNormX.setValue(2, Tags[125]);

  tmpNormY.setValue(0, Tags[38]);
  tmpNormY.setValue(1, Tags[82]);
  tmpNormY.setValue(2, Tags[126]);

  tmpNormZ.setValue(0, Tags[39]);
  tmpNormZ.setValue(1, Tags[83]);
  tmpNormZ.setValue(2, Tags[127]);

  sub(tmpNormX, wheelCRp, tmpNormX);
  sub(tmpNormY, wheelCRp, tmpNormY);
  sub(tmpNormZ, wheelCRp, tmpNormZ);

  wheelCR.setValue(0, 0, tmpNormX.getValue(0)); //x
  wheelCR.setValue(1, 0, tmpNormX.getValue(1)); //y
  wheelCR.setValue(2, 0, tmpNormX.getValue(2)); //z
  wheelCR.setValue(0, 1, tmpNormY.getValue(0)); //x
  wheelCR.setValue(1, 1, tmpNormY.getValue(1)); //y
  wheelCR.setValue(2, 1, tmpNormY.getValue(2)); //z
  wheelCR.setValue(0, 2, tmpNormZ.getValue(0)); //x
  wheelCR.setValue(1, 2, tmpNormZ.getValue(1)); //y
  wheelCR.setValue(2, 2, tmpNormZ.getValue(2)); //z

  //FR

  tmpNormX.setValue(0, Tags[40]);
  tmpNormX.setValue(1, Tags[84]);
  tmpNormX.setValue(2, Tags[128]);

  tmpNormY.setValue(0, Tags[41]);
  tmpNormY.setValue(1, Tags[85]);
  tmpNormY.setValue(2, Tags[129]);

  tmpNormZ.setValue(0, Tags[42]);
  tmpNormZ.setValue(1, Tags[86]);
  tmpNormZ.setValue(2, Tags[130]);

  sub(tmpNormX, wheelFRp, tmpNormX);
  sub(tmpNormY, wheelFRp, tmpNormY);
  sub(tmpNormZ, wheelFRp, tmpNormZ);

  wheelFR.setValue(0, 0, tmpNormX.getValue(0)); //x
  wheelFR.setValue(1, 0, tmpNormX.getValue(1)); //y
  wheelFR.setValue(2, 0, tmpNormX.getValue(2)); //z
  wheelFR.setValue(0, 1, tmpNormY.getValue(0)); //x
  wheelFR.setValue(1, 1, tmpNormY.getValue(1)); //y
  wheelFR.setValue(2, 1, tmpNormY.getValue(2)); //z
  wheelFR.setValue(0, 2, tmpNormZ.getValue(0)); //x
  wheelFR.setValue(1, 2, tmpNormZ.getValue(1)); //y
  wheelFR.setValue(2, 2, tmpNormZ.getValue(2)); //z

  //quaternions computation

  wheelFLq = rotMatrixToQuat(wheelFL);
  wheelFRq = rotMatrixToQuat(wheelFR);
  wheelCLq = rotMatrixToQuat(wheelCL);
  wheelCRq = rotMatrixToQuat(wheelCR);
  wheelRLq = rotMatrixToQuat(wheelRL);
  wheelRRq = rotMatrixToQuat(wheelRR);

  trunkq = rotMatrixToQuat(trunk);
 
  //centers computation
  
  RoverBody bodyRL(4, wheelRLp, wheelRLq);
  RoverBody bodyRR(3, wheelRRp, wheelRRq);
  RoverBody bodyCL(2, wheelCLp, wheelCLq);
  RoverBody bodyFL(1, wheelFLp, wheelFLq);
  RoverBody bodyCR(5, wheelCRp, wheelCRq);
  RoverBody bodyFR(6, wheelFRp, wheelFRq);

  RoverBody bodyTRUNK(7, trunkp, trunkq);

  vector<RoverBody> chain_wheels;

  chain_wheels.push_back(bodyFL);
  chain_wheels.push_back(bodyFR);
  chain_wheels.push_back(bodyCL);
  chain_wheels.push_back(bodyCR);
  chain_wheels.push_back(bodyRL);
  chain_wheels.push_back(bodyRR);

  chain_wheels.push_back(bodyTRUNK);

  if(!posStream.is_open()){

    cout << "file can't be opened" << endl; 

  }
  else{

    for(vector<RoverBody>::iterator chain_it = chain_wheels.begin(); chain_it != chain_wheels.end(); ++chain_it){
     
      posStream << std::scientific << time << " " << (*chain_it)._id << " " << (*chain_it)._pos.getValue(0) << " " <<  (*chain_it)._pos.getValue(1) << " " << (*chain_it)._pos.getValue(2) << " ";
      posStream << std::scientific << (*chain_it)._orient.getValue(0) << " " << (*chain_it)._orient.getValue(1) << " " << (*chain_it)._orient.getValue(2) << " " << (*chain_it)._orient.getValue(3) << endl;

    }
      
  }

}

void RoverIO::outputForces(double time, SP::Model _model, SP::NonSmoothLaw _nslaw){

  //mu

  double mu;

  //lambda

  SiconosVector lbd(3);

  if (_model->nonSmoothDynamicalSystem()->topology()->numberOfIndexSet() > 1){

    SP::InteractionsGraph indexSet1 = _model->nonSmoothDynamicalSystem()->topology()->indexSet(1);

    if(indexSet1->size() > 0){

      InteractionsGraph::VIterator ui0, ui0end, v0next;

      std11::tie(ui0, ui0end) = indexSet1->vertices();

      for(v0next = ui0; ui0 != ui0end; ui0 = v0next)
      {

        //trick to iterate on a dynamic bgl graph

        ++v0next;  

        Interaction& inter0 = *(indexSet1->bundle(*ui0));

        SP::Rover3DWheelFixedTriangleR RoverR = std11::static_pointer_cast<Rover3DWheelFixedTriangleR>(inter0.relation());

        SP::NewtonImpactFrictionNSL NSL = std11::static_pointer_cast<NewtonImpactFrictionNSL>(_nslaw);

        mu = NSL->mu();

        lbd = inter0.getLambda(1);

        //multiplication to put the forces back in the global frame - to get R's

        SimpleMatrix Offset1(3, 3);

        Offset1 = RoverR->_orthoBase;

        prod(Offset1, lbd, lbd);

        SiconosVector pct(RoverR->_pcn);
        SiconosVector normalt(RoverR->_normal);

        //output

        forcesStream << std::scientific << time << " " << mu << " " << pct.getValue(0) << " " << pct.getValue(1) << " " << pct.getValue(2) << " ";
        forcesStream << std::scientific << pct.getValue(0) << " " << pct.getValue(1) << " " << pct.getValue(2) << " ";
        forcesStream << std::scientific << normalt.getValue(0) << " " << normalt.getValue(1) << " " << normalt.getValue(2) << " ";
        forcesStream << std::scientific << lbd.getValue(0) << " " << lbd.getValue(1) << " " << lbd.getValue(2) << endl;

      }

    }

  }

}

void RoverIO::outputSolver(double time, SP::OneStepNSProblem osnsp){

  SP::FrictionContact frContact = std11::static_pointer_cast<FrictionContact>(osnsp);

  solverStream << std::scientific << time << " " << osnsp->numericsSolverOptions()->iparam[7] << " " << osnsp->numericsSolverOptions()->dparam[1] << " ";
  solverStream << std::scientific << osnsp->numericsSolverOptions()->dparam[2] << endl; 

}

void RoverIO::outputStatObjects(double time){
  
  //main scene (baseBody) -0.5 on z wrt to its local frame 

  //rotating the plane
  
  SimpleMatrix of(3, 3);

  of = zyxEulersToRotMatrix(0, 0, 0);

  SiconosVector of1(3);

  of1.setValue(0, 10);
  of1.setValue(1, 5);
  of1.setValue(2, -0.5);
  prod(of, of1, of1);

  SiconosVector offs(4);
  offs = eulToQuat(0, 0, 0);

  staticStream << std::scientific << time << " " << "-1" << " " << of1.getValue(0) << " " << of1.getValue(1) << " " << of1.getValue(2) << " ";
  staticStream << offs.getValue(0) << " " << offs.getValue(1) << " " << offs.getValue(2) << " " << offs.getValue(3) << endl;

  staticStream << std::scientific << time << " " << "-2" << " " << 0 << " " << 5 << " " << 0.05 << " ";
  staticStream << 1 << " " << 0 << " " << 0 << " " << 0 << endl;


}

void RoverIO::test(){

  //rotMatToQuat test

  SimpleMatrix rMat(3, 3);

  rMat.setValue(0, 0, 0);
  rMat.setValue(0, 1, 0);
  rMat.setValue(0, 2, 1);
  rMat.setValue(1, 0, 0);
  rMat.setValue(1, 1, 1);
  rMat.setValue(1, 2, 0);
  rMat.setValue(2, 0, 1);
  rMat.setValue(2, 1, 0);
  rMat.setValue(2, 2, 0);

  std::cout << "QuatToRotMatrix output before : " << std::endl;
  std::cout << rMat.getValue(0, 0) << " " << rMat.getValue(0, 1) << " " << rMat.getValue(0, 2) << endl;
  std::cout << rMat.getValue(1, 0) << " " << rMat.getValue(1, 1) << " " << rMat.getValue(1, 2) << endl;
  std::cout << rMat.getValue(2, 0) << " " << rMat.getValue(2, 1) << " " << rMat.getValue(2, 2) << endl;
  
  SiconosVector testV(4);

  testV = rotMatrixToQuat(rMat);
  
  std::cout << "rotMatrixToQuat output : " << std::endl;
  std::cout << testV.getValue(0) << " " << testV.getValue(1) << " " << testV.getValue(2) << " " << testV.getValue(3) << " " << std::endl;

  rMat = quatToRotMatrix(testV.getValue(0), testV.getValue(1), testV.getValue(2), testV.getValue(3));

  std::cout << "QuatToRotMatrix output after : " << std::endl;
  std::cout << rMat.getValue(0, 0) << " " << rMat.getValue(0, 1) << " " << rMat.getValue(0, 2) << endl;
  std::cout << rMat.getValue(1, 0) << " " << rMat.getValue(1, 1) << " " << rMat.getValue(1, 2) << endl;
  std::cout << rMat.getValue(2, 0) << " " << rMat.getValue(2, 1) << " " << rMat.getValue(2, 2) << endl;

  //quatCombine test

  SiconosVector q1(4);
  SiconosVector q2(4);

  q1.setValue(0, 0);
  q1.setValue(0, 0);
  q1.setValue(0, 0);
  q1.setValue(0, 1);

  q2.setValue(0, 0);
  q2.setValue(0, 0);
  q2.setValue(0, 0);
  q2.setValue(0, 1);

  SiconosVector q3(4);

  q3 = quatCombine(q1, q2);
  
  std::cout << "quatCombine output : " << std::endl;
  std::cout << testV.getValue(0) << " " << testV.getValue(1) << " " << testV.getValue(2) << " " << testV.getValue(3) << " " << std::endl;

}

