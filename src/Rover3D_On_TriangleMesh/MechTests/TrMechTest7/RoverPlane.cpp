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

//.cpp for simulation of a robot with triangle mesh terrain
// Author: Jan Michalczyk
// Team: Bipop

#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Robot.h"
#include "SiconosKernel.hpp"
#include <stdlib.h>
#include "Rover3DWheelFixedTriangleR.hpp"
#include <boost/progress.hpp>

#include "RoverIO.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  try
  {

    // ================= Creation of the model =======================

    // User-defined main parameters
    unsigned int nDof = 21;           // degrees of freedom for robot arm
    double t0 = 0;                    // initial computation time
    double T = 22;                   // final computation time
    double h = 0.0005;                 // time step
    double eps_n = 0.1;
    double eps_t = 0.0;
    double mu = 0.6;
    double R = 0.129;                 //Wheel Radius
    double RAngle[3] = {0.0,0.0,0.0}; //Format of RAngle: Euler angles (alpha,beta,gamma)
 
    // -------------------------
    // --- Dynamical systems ---
    // -------------------------
 
    DynamicalSystemsSet allDS;

    // --- DS: RoverDS ---

    // Initial position (angles in radian)

    SP::SiconosVector q0(new SiconosVector(nDof));
    SP::SiconosVector v0(new SiconosVector(nDof));

    q0->zero();
    v0->zero();

    //q0 -> positions ((*q0)(0) - x, (*q0)(1) - y, (*q0)(2) - z)

    (*q0)(0) = 7;   //x 
    (*q0)(2) = 1;   //z
    (*q0)(1) = 5;     //y

    (*q0)(5) = 3.1415;

    SP::LagrangianDS arm(new LagrangianDS(q0, v0));
   
    //external plug-in

    arm->setComputeMassFunction("RobotPlugin.so","mass");
    
    // -- Set external forces (traction) --

    SP::SiconosVector Force(new SiconosVector(nDof));

    (*Force)(9) = 0;       //FL traction
    (*Force)(10) = 0;      //FR  traction
    (*Force)(14) = 0;      //ML traction
    (*Force)(15) = 0;      //BL traction
    (*Force)(19) = 0;      //MR traction
    (*Force)(20) = 0;      //BR traction

    arm->setFExtPtr(Force);

    arm->setComputeNNLFunction("RobotPlugin.so","NNL");
    arm->setComputeJacobianNNLqFunction("RobotPlugin.so","jacobianNNLq");
    arm->setComputeJacobianNNLqDotFunction("RobotPlugin.so","jacobianVNNL");
    arm->setComputeFIntFunction("RobotPlugin.so","U");
    arm->setComputeJacobianFIntqFunction("RobotPlugin.so","jacobFintQ");
    arm->setComputeJacobianFIntqDotFunction("RobotPlugin.so","jacobFintV");

    allDS.insert(arm);

    // -------------------
    // ---Interactions----
    // -------------------

    InteractionsSet allInteractions;

    SP::NonSmoothLaw nslaw(new NewtonImpactFrictionNSL(eps_n, eps_t, mu, 3));

    //---------------------------------------------------
    //---------------Interaction-------------------------
    //---------------------------------------------------

    //number of triangles 

    int NumTr = 4;

    //file for normals
    
    //end of file for normals

    vector<SP::Rover3DWheelFixedTriangleR> relation(6*NumTr);
    vector<SP::Interaction> inter(6*NumTr);

    for(int j = 0; j < 6; ++j){

      relation[j*NumTr + 0].reset(new Rover3DWheelFixedTriangleR(10, 5, 0, 5, 0, 0, 5, 10, 0, R, (j*NumTr + 0)));
      relation[j*NumTr + 1].reset(new Rover3DWheelFixedTriangleR(5, 0, 0, 5, 0, 0.1, 5, 10, 0, R, (j*NumTr + 1)));
      relation[j*NumTr + 2].reset(new Rover3DWheelFixedTriangleR(5, 10, 0, 5, 10, 0.1, 5, 0, 0.1, R, (j*NumTr + 2)));
      relation[j*NumTr + 3].reset(new Rover3DWheelFixedTriangleR(5, 0, 0.1, 5, 10, 0.1, 0, 5, 0.1, R, (j*NumTr + 3)));

      inter[j*NumTr + 0].reset(new Interaction(allDS, j*NumTr + 0, 3, nslaw, relation[j*NumTr + 0]));
      inter[j*NumTr + 1].reset(new Interaction(allDS, j*NumTr + 1, 3, nslaw, relation[j*NumTr + 1]));
      inter[j*NumTr + 2].reset(new Interaction(allDS, j*NumTr + 2, 3, nslaw, relation[j*NumTr + 2]));
      inter[j*NumTr + 3].reset(new Interaction(allDS, j*NumTr + 3, 3, nslaw, relation[j*NumTr + 3]));        

      allInteractions.insert(inter[j*NumTr + 0]);
      allInteractions.insert(inter[j*NumTr + 1]);
      allInteractions.insert(inter[j*NumTr + 2]);
      allInteractions.insert(inter[j*NumTr + 3]);

    }

    // -------------
    // --- Model ---
    // -------------

    SP::Model Rover3D(new Model(t0, T, allDS, allInteractions));

    // ------------------
    // --- Simulation ---
    // ------------------

    // -- Time discretisation --

    SP::TimeDiscretisation t(new TimeDiscretisation(t0,h));
    SP::TimeStepping s(new TimeStepping(t));

    // -- OneStepIntegrators --

    double theta = 0.50000001;

    SP::Moreau OSI(new Moreau(allDS,theta));
    s->insertIntegrator(OSI);

    //*******************************************************

    // -- OneStepNsProblem --
    SP::OneStepNSProblem osnspb(new FrictionContact(3));

    osnspb->numericsSolverOptions()->iparam[0]=100000; // Max number of

    osnspb->numericsSolverOptions()->iparam[4]=1;      // projection

    // Solver/formulation  0: projection, 1: Newton/AlartCurnier, 2: Newton/Fischer-Burmeister

    //tolerance needs to be reduced when torques applied to wheels (for moving foward 1e-7 is ok)
    //for the simulation with one turning steering axis use 1e-8

    osnspb->numericsSolverOptions()->dparam[0]=1e-7;   // Tolerance
    osnspb->numericsSolverOptions()->dparam[2]=1e-7;   // Local tolerance
    osnspb->setNumericsVerboseMode(true);

    //********************************************************

    s->insertNonSmoothProblem(osnspb);

    cout << "=== End of model loading === " << endl;

    // ================================= Computation =================================

    // --- Simulation initAialization ---
    cout << "=== Simulation initialization ===" << endl;

    Rover3D->initialize(s);

    cout <<"End of initialisation" << endl;

    //time
    double tm = 0;

    int i = 0;
    int k = 0;
    int N = (int)((T-t0)/h);

    cout << "Number of time step   " << N << endl;

    double qq[21];
    double TT[132];

    SP::SiconosVector q = arm->q();
    SP::SiconosVector v = arm->velocity();

    SP::SiconosVector yfunc = inter[0]->y(0);
    SP::SiconosVector yfunc1 = inter[1]->y(0);
    SP::SiconosVector yfunc2 = inter[2]->y(0);
    SP::SiconosVector yfunc3 = inter[3]->y(0);
    SP::SiconosVector yfunc4 = inter[4]->y(0);
    SP::SiconosVector yfunc5 = inter[5]->y(0);
    
    SP::SiconosVector pvalue = arm->p(1);

    SimpleMatrix Pvalue(N+1, 22);

    Pvalue(k, 0) = t0;

    Pvalue(k, 1) = (*pvalue)(0);
    Pvalue(k, 2) = (*pvalue)(1);
    Pvalue(k, 3) = (*pvalue)(2);
    Pvalue(k, 4) = (*pvalue)(3);
    Pvalue(k, 5) = (*pvalue)(4);
    Pvalue(k, 6) = (*pvalue)(5);
    Pvalue(k, 7) = (*pvalue)(6);
    Pvalue(k, 8) = (*pvalue)(7);
    Pvalue(k, 9) = (*pvalue)(8);
    Pvalue(k, 10) = (*pvalue)(9);
    Pvalue(k, 11) = (*pvalue)(10);
    Pvalue(k, 12) = (*pvalue)(11);
    Pvalue(k, 13) = (*pvalue)(12);
    Pvalue(k, 14) = (*pvalue)(13);
    Pvalue(k, 15) = (*pvalue)(14);
    Pvalue(k, 16) = (*pvalue)(15);
    Pvalue(k, 17) = (*pvalue)(16);
    Pvalue(k, 18) = (*pvalue)(17);
    Pvalue(k, 19) = (*pvalue)(18);
    Pvalue(k, 20) = (*pvalue)(19);
    Pvalue(k, 21) = (*pvalue)(20);

    SimpleMatrix yfunction(N+1, 19);

    yfunction(k, 0) = t0;

    yfunction(k, 1) = inter[0]->y(0)->getValue(0);
    yfunction(k, 2) = inter[0]->y(0)->getValue(1);
    yfunction(k, 3) = inter[0]->y(0)->getValue(2);

    yfunction(k, 4) = inter[1]->y(0)->getValue(0);
    yfunction(k, 5) = inter[1]->y(0)->getValue(1);
    yfunction(k, 6) = inter[1]->y(0)->getValue(2);

    yfunction(k, 7) = inter[2]->y(0)->getValue(0);
    yfunction(k, 8) = inter[2]->y(0)->getValue(1);
    yfunction(k, 9) = inter[2]->y(0)->getValue(2);

    yfunction(k, 10) = inter[3]->y(0)->getValue(0);
    yfunction(k, 11) = inter[3]->y(0)->getValue(1);
    yfunction(k, 12) = inter[3]->y(0)->getValue(2);

    yfunction(k, 13) = inter[4]->y(0)->getValue(0);
    yfunction(k, 14) = inter[4]->y(0)->getValue(1);
    yfunction(k, 15) = inter[4]->y(0)->getValue(2);

    yfunction(k, 16) = inter[5]->y(0)->getValue(0);
    yfunction(k, 17) = inter[5]->y(0)->getValue(1);
    yfunction(k, 18) = inter[5]->y(0)->getValue(2);

    SimpleMatrix ydotfunction(N+1, 19);

    ydotfunction(k, 0) = t0;

    ydotfunction(k, 1) = inter[0]->y(1)->getValue(0);
    ydotfunction(k, 2) = inter[0]->y(1)->getValue(1);
    ydotfunction(k, 3) = inter[0]->y(1)->getValue(2);

    ydotfunction(k, 4) = inter[1]->y(1)->getValue(0);
    ydotfunction(k, 5) = inter[1]->y(1)->getValue(1);
    ydotfunction(k, 6) = inter[1]->y(1)->getValue(2);

    ydotfunction(k, 7) = inter[2]->y(1)->getValue(0);
    ydotfunction(k, 8) = inter[2]->y(1)->getValue(1);
    ydotfunction(k, 9) = inter[2]->y(1)->getValue(2);

    ydotfunction(k, 10) = inter[3]->y(1)->getValue(0);
    ydotfunction(k, 11) = inter[3]->y(1)->getValue(1);
    ydotfunction(k, 12) = inter[3]->y(1)->getValue(2);

    ydotfunction(k, 13) = inter[4]->y(1)->getValue(0);
    ydotfunction(k, 14) = inter[4]->y(1)->getValue(1);
    ydotfunction(k, 15) = inter[4]->y(1)->getValue(2);

    ydotfunction(k, 16) = inter[5]->y(1)->getValue(0);
    ydotfunction(k, 17) = inter[5]->y(1)->getValue(1);
    ydotfunction(k, 18) = inter[5]->y(1)->getValue(2);

    SimpleMatrix lambdas(N+1, 19);

    lambdas(k, 0) = t0;

    lambdas(k, 1) = inter[0]->lambda(1)->getValue(0);
    lambdas(k, 2) = inter[0]->lambda(1)->getValue(1);
    lambdas(k, 3) = inter[0]->lambda(1)->getValue(2);

    lambdas(k, 4) = inter[1]->lambda(1)->getValue(0);
    lambdas(k, 5) = inter[1]->lambda(1)->getValue(1);
    lambdas(k, 6) = inter[1]->lambda(1)->getValue(2);

    lambdas(k, 7) = inter[2]->lambda(1)->getValue(0);
    lambdas(k, 8) = inter[2]->lambda(1)->getValue(1);
    lambdas(k, 9) = inter[2]->lambda(1)->getValue(2);

    lambdas(k, 10) = inter[3]->lambda(1)->getValue(0);
    lambdas(k, 11) = inter[3]->lambda(1)->getValue(1);
    lambdas(k, 12) = inter[3]->lambda(1)->getValue(2);

    lambdas(k, 13) = inter[4]->lambda(1)->getValue(0);
    lambdas(k, 14) = inter[4]->lambda(1)->getValue(1);
    lambdas(k, 15) = inter[4]->lambda(1)->getValue(2);

    lambdas(k, 16) = inter[5]->lambda(1)->getValue(0);
    lambdas(k, 17) = inter[5]->lambda(1)->getValue(1);
    lambdas(k, 18) = inter[5]->lambda(1)->getValue(2);

    SimpleMatrix velocity(N+1,22);

    velocity(k, 0) = t0;

    velocity(k, 1) = (*v)(0);
    velocity(k, 2) = (*v)(1);
    velocity(k, 3) = (*v)(2);
    velocity(k, 4) = (*v)(3);
    velocity(k, 5) = (*v)(4);
    velocity(k, 6) = (*v)(5);
    velocity(k, 7) = (*v)(6);
    velocity(k, 8) = (*v)(7);
    velocity(k, 9) = (*v)(8);
    velocity(k, 10) = (*v)(9);
    velocity(k, 11) = (*v)(10);
    velocity(k, 12) = (*v)(11);
    velocity(k, 13) = (*v)(12);
    velocity(k, 14) = (*v)(13);
    velocity(k, 15) = (*v)(14);
    velocity(k, 16) = (*v)(15);
    velocity(k, 17) = (*v)(16);
    velocity(k, 18) = (*v)(17);
    velocity(k, 19) = (*v)(18);
    velocity(k, 20) = (*v)(19);
    velocity(k, 21) = (*v)(20);

    SimpleMatrix position(N+1,22);

    position(k, 0) = t0;

    position(k, 1) = (*q)(0);
    position(k, 2) = (*q)(1);
    position(k, 3) = (*q)(2);
    position(k, 4) = (*q)(3);
    position(k, 5) = (*q)(4);
    position(k, 6) = (*q)(5);
    position(k, 7) = (*q)(6);
    position(k, 8) = (*q)(7);
    position(k, 9) = (*q)(8);
    position(k, 10) = (*q)(9);
    position(k, 11) = (*q)(10);
    position(k, 12) = (*q)(11);
    position(k, 13) = (*q)(12);
    position(k, 14) = (*q)(13);
    position(k, 15) = (*q)(14);
    position(k, 16) = (*q)(15);
    position(k, 17) = (*q)(16);
    position(k, 18) = (*q)(17);
    position(k, 19) = (*q)(18);
    position(k, 20) = (*q)(19);
    position(k, 21) = (*q)(20);

    //output object

    SP::RoverIO RoIO(new RoverIO());

    //-------------gnuplot data----------------

    i = 0;

    while(i < nDof)
    {
      qq[i]=(*q)(i);
      i++;
    }

    Tags(TT, qq);

    //output initial positions
    
    RoIO->outputPositions(tm, TT, qq);

    RoIO->outputStatObjects(tm);

    //------------------------------------------

    boost::timer time;

    time.restart();

    // --- Time loop ---

    cout << "Start computation ... " << endl;

    double static_torque = 0.000885;
    double sliding_torque = -0.01;

    boost::progress_display show_progress(N);

    while(s->hasNextEvent())
    {
      osnspb->setNumericsVerboseMode(0);

      k++;
      ++show_progress;

      // Solve problem
      s->computeOneStep();
     
      //cout << osnspb->numericsSolverOptions()->dparam[1] << endl;

      tm = s->nextTime();

      static_torque = 0.0000000000000087072;

      //static_torque = -0.87072;

      if(tm > 10){

        // (*Force)(9) = static_torque - 0.15*(4.0 - (*q)(0));  //FL traction
        // (*Force)(10) = static_torque - 0.15*(4.0 - (*q)(0)); //FR  traction
        // (*Force)(14) = static_torque - 0.15*(4.0 - (*q)(0)); //ML traction
        // (*Force)(15) = static_torque - 0.15*(4.0 - (*q)(0)); //BL traction
        // (*Force)(19) = static_torque - 0.15*(4.0 - (*q)(0)); //MR traction
        // (*Force)(20) = static_torque - 0.15*(4.0 - (*q)(0)); //BR traction

        (*Force)(9) = static_torque - 0.18*(4.0 - (*q)(0));  //FL traction
        (*Force)(10) = static_torque - 0.18*(4.0 - (*q)(0)); //FR  traction
        (*Force)(14) = static_torque - 0.18*(4.0 - (*q)(0)); //ML traction
        (*Force)(15) = static_torque - 0.18*(4.0 - (*q)(0)); //BL traction
        (*Force)(19) = static_torque - 0.18*(4.0 - (*q)(0)); //MR traction
        (*Force)(20) = static_torque - 0.18*(4.0 - (*q)(0)); //BR traction

      }

      Pvalue(k, 0) = tm;

      Pvalue(k, 1) = (*pvalue)(0);
      Pvalue(k, 2) = (*pvalue)(1);
      Pvalue(k, 3) = (*pvalue)(2);
      Pvalue(k, 4) = (*pvalue)(3);
      Pvalue(k, 5) = (*pvalue)(4);
      Pvalue(k, 6) = (*pvalue)(5);
      Pvalue(k, 7) = (*pvalue)(6);
      Pvalue(k, 8) = (*pvalue)(7);
      Pvalue(k, 9) = (*pvalue)(8);
      Pvalue(k, 10) = (*pvalue)(9);
      Pvalue(k, 11) = (*pvalue)(10);
      Pvalue(k, 12) = (*pvalue)(11);
      Pvalue(k, 13) = (*pvalue)(12);
      Pvalue(k, 14) = (*pvalue)(13);
      Pvalue(k, 15) = (*pvalue)(14);
      Pvalue(k, 16) = (*pvalue)(15);
      Pvalue(k, 17) = (*pvalue)(16);
      Pvalue(k, 18) = (*pvalue)(17);
      Pvalue(k, 19) = (*pvalue)(18);
      Pvalue(k, 20) = (*pvalue)(19);
      Pvalue(k, 21) = (*pvalue)(20);

      lambdas(k, 0) = tm;

      lambdas(k, 1) = inter[0]->lambda(1)->getValue(0);
      lambdas(k, 2) = inter[0]->lambda(1)->getValue(1);
      lambdas(k, 3) = inter[0]->lambda(1)->getValue(2);

      lambdas(k, 4) = inter[1]->lambda(1)->getValue(0);
      lambdas(k, 5) = inter[1]->lambda(1)->getValue(1);
      lambdas(k, 6) = inter[1]->lambda(1)->getValue(2);

      lambdas(k, 7) = inter[2]->lambda(1)->getValue(0);
      lambdas(k, 8) = inter[2]->lambda(1)->getValue(1);
      lambdas(k, 9) = inter[2]->lambda(1)->getValue(2);

      lambdas(k, 10) = inter[3]->lambda(1)->getValue(0);
      lambdas(k, 11) = inter[3]->lambda(1)->getValue(1);
      lambdas(k, 12) = inter[3]->lambda(1)->getValue(2);

      lambdas(k, 13) = inter[4]->lambda(1)->getValue(0);
      lambdas(k, 14) = inter[4]->lambda(1)->getValue(1);
      lambdas(k, 15) = inter[4]->lambda(1)->getValue(2);

      lambdas(k, 16) = inter[5]->lambda(1)->getValue(0);
      lambdas(k, 17) = inter[5]->lambda(1)->getValue(1);
      lambdas(k, 18) = inter[5]->lambda(1)->getValue(2);

      yfunction(k, 0) = tm;

      yfunction(k, 1) = inter[0]->y(0)->getValue(0);
      yfunction(k, 2) = inter[0]->y(0)->getValue(1);
      yfunction(k, 3) = inter[0]->y(0)->getValue(2);

      yfunction(k, 4) = inter[1]->y(0)->getValue(0);
      yfunction(k, 5) = inter[1]->y(0)->getValue(1);
      yfunction(k, 6) = inter[1]->y(0)->getValue(2);

      yfunction(k, 7) = inter[2]->y(0)->getValue(0);
      yfunction(k, 8) = inter[2]->y(0)->getValue(1);
      yfunction(k, 9) = inter[2]->y(0)->getValue(2);

      yfunction(k, 10) = inter[3]->y(0)->getValue(0);
      yfunction(k, 11) = inter[3]->y(0)->getValue(1);
      yfunction(k, 12) = inter[3]->y(0)->getValue(2);

      yfunction(k, 13) = inter[4]->y(0)->getValue(0);
      yfunction(k, 14) = inter[4]->y(0)->getValue(1);
      yfunction(k, 15) = inter[4]->y(0)->getValue(2);

      yfunction(k, 16) = inter[5]->y(0)->getValue(0);
      yfunction(k, 17) = inter[5]->y(0)->getValue(1);
      yfunction(k, 18) = inter[5]->y(0)->getValue(2);

      ydotfunction(k, 0) = tm;

      ydotfunction(k, 1) = inter[0]->y(1)->getValue(0);
      ydotfunction(k, 2) = inter[0]->y(1)->getValue(1);
      ydotfunction(k, 3) = inter[0]->y(1)->getValue(2);

      ydotfunction(k, 4) = inter[1]->y(1)->getValue(0);
      ydotfunction(k, 5) = inter[1]->y(1)->getValue(1);
      ydotfunction(k, 6) = inter[1]->y(1)->getValue(2);

      ydotfunction(k, 7) = inter[2]->y(1)->getValue(0);
      ydotfunction(k, 8) = inter[2]->y(1)->getValue(1);
      ydotfunction(k, 9) = inter[2]->y(1)->getValue(2);

      ydotfunction(k, 10) = inter[3]->y(1)->getValue(0);
      ydotfunction(k, 11) = inter[3]->y(1)->getValue(1);
      ydotfunction(k, 12) = inter[3]->y(1)->getValue(2);

      ydotfunction(k, 13) = inter[4]->y(1)->getValue(0);
      ydotfunction(k, 14) = inter[4]->y(1)->getValue(1);
      ydotfunction(k, 15) = inter[4]->y(1)->getValue(2);

      ydotfunction(k, 16) = inter[5]->y(1)->getValue(0);
      ydotfunction(k, 17) = inter[5]->y(1)->getValue(1);
      ydotfunction(k, 18) = inter[5]->y(1)->getValue(2);

      velocity(k, 0) = tm;

      velocity(k, 1) = (*v)(0); //velocity of the x coord of mass centre
      velocity(k, 2) = (*v)(1); //velocity of the y coord of mass centre
      velocity(k, 3) = (*v)(2); //velocity of the z coord of mass centre
      velocity(k, 4) = (*v)(3); //rotational velocity of the mass centre around x axle
      velocity(k, 5) = (*v)(4); //rotational velocity of the mass centre around y axle
      velocity(k, 6) = (*v)(5); //rotational velocity of the mass centre around z axle
      velocity(k, 7) = (*v)(6); //rotational velocity of the F bogie axle (around x)
      velocity(k, 8) = (*v)(7); //rotational velocity of the steering axle FL (around y)
      velocity(k, 9) = (*v)(8); //rotational velocity of the steering axle FR (around y)
      velocity(k, 10) = (*v)(9); //velocity of the FL wheel
      velocity(k, 11) = (*v)(10); //velocity of the FR wheel
      velocity(k, 12) = (*v)(11); //rotational velocity of the bogie axle BL (around z)
      velocity(k, 13) = (*v)(12); //rotational velocity of the steering axle ML (around y)
      velocity(k, 14) = (*v)(13); //rotational velocity of the steering axle BL (around y)
      velocity(k, 15) = (*v)(14); //velocity of the ML wheel
      velocity(k, 16) = (*v)(15); //velocity of the BL wheel
      velocity(k, 17) = (*v)(16); //rotational velocity of the bogie axle BR (around z)
      velocity(k, 18) = (*v)(17); //rotational velocity of the steering axle MR (around y)
      velocity(k, 19) = (*v)(18); //rotational velocity of the steering axle BR (around y)
      velocity(k, 20) = (*v)(19); //velocity of the MR wheel
      velocity(k, 21) = (*v)(20); //velocity of the BR wheel

      position(k, 0) = tm;

      position(k, 1) = (*q)(0);
      position(k, 2) = (*q)(1);
      position(k, 3) = (*q)(2);
      position(k, 4) = (*q)(3);
      position(k, 5) = (*q)(4);
      position(k, 6) = (*q)(5);
      position(k, 7) = (*q)(6);
      position(k, 8) = (*q)(7);
      position(k, 9) = (*q)(8);
      position(k, 10) = (*q)(9);
      position(k, 11) = (*q)(10);
      position(k, 12) = (*q)(11);
      position(k, 13) = (*q)(12);
      position(k, 14) = (*q)(13);
      position(k, 15) = (*q)(14);
      position(k, 16) = (*q)(15);
      position(k, 17) = (*q)(16);
      position(k, 18) = (*q)(17);
      position(k, 19) = (*q)(18);
      position(k, 20) = (*q)(19);
      position(k, 21) = (*q)(20);

      //-------------------gnuplot ------------------

      i=0;

      while(i < nDof)
      {
        qq[i]=(*q)(i);
        i++;
      }
      //cout << qq[0] << " " << qq[1] << " " << qq[2] << endl;
      Tags(TT, qq);

      //OUTPUT FORCES AND DPOS.DAT//////////////////////////////

      RoIO->outputPositions(tm, TT, qq);

      RoIO->outputForces(tm, Rover3D, nslaw);

      RoIO->outputSolver(tm, osnspb);

      //OUTPUT FORCES AND DPOS.DAT//////////////////////////////


    //--------------------------------------------

      s->nextStep();

    }

    cout<<"End of computation - Number of iterations done: "<<k<<endl;
    cout << "Computation Time " << time.elapsed()  << endl;

    // --- Output files ---
    ioMatrix::write("VELOCITY.dat", "ascii",
                    velocity,"noDim");
    ioMatrix::write("POSITION.dat", "ascii",
                    position,"noDim");
    ioMatrix::write("LAMBDAS.dat", "ascii",
                    lambdas,"noDim");
    ioMatrix::write("Y.dat", "ascii",
                    yfunction,"noDim");
    ioMatrix::write("YDOTS.dat", "ascii",
                    ydotfunction,"noDim");
    ioMatrix::write("PVALUE.dat", "ascii",
                    Pvalue,"noDim");
  }

  catch(SiconosException e)
  {
    cout << e.report() << endl;
  }
  catch(...)
  {
    cout << "Exception caught" << endl;
  }
}

