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
using namespace std;

static int iteration_failed = 0;

int main(int argc, char* argv[])
{
  try
  {

    // ================= Creation of the model =======================

    // User-defined main parameters
    unsigned int nDof = 21;        // degrees of freedom for robot arm
    double t0 = 0;                 // initial computation time
    double T = 100;                 // final computation time
    double h = 0.005;               // time step
    double eps_n = 0.0;
    double eps_t = 0.0;
    double mu = 0.7;
    //double mu = 0.5;
    double R = 30;                 //Wheel Radius
    double l = 20;
    double g = 9.8;
    int Ns = 20;                      
    double WheelT = 10;               //Wheel Thickness
    double RAngle[3] = {0.0,0.0,0.0};  //Format of RAngle: Euler angles (alpha,beta,gamma)
 
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

    //q0 -> positions
    // 9000 and 93
    (*q0)(0) = 700;  //x 
    (*q0)(2) = 500;  //z
    (*q0)(1) = 270;    //y

    //(*q0)(0) = 1061.46;  //x 
    //(*q0)(2) = 500.666;  //z
    //(*q0)(1) = 59.9797;    //y

    (*q0)(3) = 0.0;
    (*q0)(4) = 3.1415;
    (*q0)(5) = 0.0;

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
    (*Force)(20) = 0;     //BR traction

    arm->setFExtPtr(Force);

    arm->setComputeNNLFunction("RobotPlugin.so","NNL");
    arm->setComputeJacobianNNLqFunction("RobotPlugin.so","jacobianNNLq");
    arm->setComputeJacobianNNLqDotFunction("RobotPlugin.so","jacobianVNNL");
    arm->setComputeFIntFunction("RobotPlugin.so","U");
    arm->setComputeJacobianFIntqFunction("RobotPlugin.so","jacobFintQ");
    arm->setComputeJacobianFIntqDotFunction("RobotPlugin.so","jacobFintV");
    allDS.insert(arm);

    // -------------------
    // --- Interactions---
    // -------------------

    InteractionsSet allInteractions;

    SP::NonSmoothLaw nslaw(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));

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
          
      //relation[j*NumTr + 0].reset(new Rover3DWheelFixedTriangleR(0, 0, 500, 1000, 0, 0, 1000, 0, 1000, j, R));
      //relation[j*NumTr + 1].reset(new Rover3DWheelFixedTriangleR(1010, 15, 0, 1010, 15, 1000, 1000, 0, 0, j, R));
      //relation[j*NumTr + 2].reset(new Rover3DWheelFixedTriangleR(1010, 15, 1000, 1000, 0, 1000, 1000, 0, 0, j, R));
      //relation[j*NumTr + 3].reset(new Rover3DWheelFixedTriangleR(1010, 15, 0, 1010, 15, 1000, 2010, 15, 500, j, R));

      relation[j*NumTr + 0].reset(new Rover3DWheelFixedTriangleR(0, 0, 500, 1000, 0, 0, 1000, 0, 1000, j, R, (j*NumTr + 0)));
      relation[j*NumTr + 1].reset(new Rover3DWheelFixedTriangleR(1000, 10, 0, 1000, 10, 1000, 1000, 0, 0, j, R, (j*NumTr + 1)));
      relation[j*NumTr + 2].reset(new Rover3DWheelFixedTriangleR(1000, 10, 1000, 1000, 0, 1000, 1000, 0, 0, j, R, (j*NumTr + 2)));
      relation[j*NumTr + 3].reset(new Rover3DWheelFixedTriangleR(1000, 10, 0, 1000, 10, 1000, 2000, 10, 500, j, R, (j*NumTr + 3)));

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

    SP::Model Rover3D(new Model(t0,T,allDS, allInteractions));

    // ------------------
    // --- Simulation ---
    // ------------------

    // -- Time discretisation --
    SP::TimeDiscretisation t(new TimeDiscretisation(t0,h));

    SP::TimeStepping s(new TimeStepping(t));
    // s->setUseRelativeConvergenceCriteron(true);

    // -- OneStepIntegrators --

    //double theta=0.500001;
    double theta=0.50000001;

    SP::Moreau OSI(new Moreau(allDS,theta));
    s->insertIntegrator(OSI);

    //*******************************************************

    // -- OneStepNsProblem --
    //osnspb.reset(new FrictionContact(3));
    SP::OneStepNSProblem osnspb(new FrictionContact(3));

    osnspb->numericsSolverOptions()->iparam[0]=100000; // Max number of
    // iterations
    // osnspb->numericsSolverOptions()->iparam[1]=100000;  // compute error
    //                                                  // iterations

    osnspb->numericsSolverOptions()->iparam[4]=1;   // projection
    // Solver/formulation  0: projection, 1: Newton/AlartCurnier, 2: Newton/Fischer-Burmeister
    osnspb->numericsSolverOptions()->dparam[0]=1e-5;// Tolerance
    osnspb->numericsSolverOptions()->dparam[2]=1e-5;// Local tolerance
    osnspb->setNumericsVerboseMode(true);

    //********************************************************

    s->insertNonSmoothProblem(osnspb);
    //s->setCheckSolverFunction(localCheckSolverOuput);
    cout << "=== End of model loading === " << endl;

    // ================================= Computation =================================

    // --- Simulation initAialization ---
    cout << "=== Simulation initialization ===" << endl;
    Rover3D->initialize(s);

    cout <<"End of initialisation" << endl;
    int i=0;
    int k=0;
    int kk= 0;
    int N = (int)((T-t0)/h);
    int NN=3*N+3;
    cout << "Number of time step   " << N << endl;

    // --- Get the values to be plotted ---
    // -> saved in a matrix dataPlot

    SimpleMatrix dataPlot(N + 1,nDof+17+6);

    double qq[21];
    double Test[69];

    SimpleMatrix testdatabase(N+1,18);

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


    SimpleMatrix yfunction(N+1, 21);

    yfunction(k, 0) = t0;

    yfunction(k, 1) = inter[6]->y(0)->getValue(0);
    yfunction(k, 2) = inter[6]->y(0)->getValue(1);
    yfunction(k, 3) = inter[6]->y(0)->getValue(2);

    yfunction(k, 4) = inter[7]->y(0)->getValue(0);
    yfunction(k, 5) = inter[7]->y(0)->getValue(1);
    yfunction(k, 6) = inter[7]->y(0)->getValue(2);

    yfunction(k, 7) = inter[8]->y(0)->getValue(0);
    yfunction(k, 8) = inter[8]->y(0)->getValue(1);
    yfunction(k, 9) = inter[8]->y(0)->getValue(2);

    yfunction(k, 10) = inter[9]->y(0)->getValue(0);
    yfunction(k, 11) = inter[9]->y(0)->getValue(1);
    yfunction(k, 12) = inter[9]->y(0)->getValue(2);

    yfunction(k, 13) = inter[10]->y(0)->getValue(0);
    yfunction(k, 14) = inter[10]->y(0)->getValue(1);
    yfunction(k, 15) = inter[10]->y(0)->getValue(2);

    yfunction(k, 16) = inter[11]->y(0)->getValue(0);
    yfunction(k, 17) = inter[11]->y(0)->getValue(1);
    yfunction(k, 18) = inter[11]->y(0)->getValue(2);

    SimpleMatrix ydotfunction(N+1, 21);

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

    position(k, 1) = (*q)(0)/100;
    position(k, 2) = (*q)(1)/100;
    position(k, 3) = (*q)(2)/100;
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

    dataPlot(k,0)= t0;
    dataPlot(k,1)=(*q)(0)/100;
    dataPlot(k,2)=(*q)(1)/100;
    dataPlot(k,3)=(*q)(2)/100;

    dataPlot(k,4)=(*q)(3);
    dataPlot(k,5)=(*q)(4);
    dataPlot(k,6)=(*q)(5);
    dataPlot(k,7)=(*q)(6);
    dataPlot(k,8)=(*q)(7);
    dataPlot(k,9)=(*q)(8);
    dataPlot(k,10)=(*q)(9);
    dataPlot(k,11)=(*q)(10);
    dataPlot(k,12)=(*q)(11);
    dataPlot(k,13)=(*q)(12);
    dataPlot(k,14)=(*q)(13);
    dataPlot(k,15)=(*q)(14);
    dataPlot(k,16)=(*q)(15);
    dataPlot(k,17)=(*q)(16);
    dataPlot(k,18)=(*q)(17);
    dataPlot(k,19)=(*q)(18);
    dataPlot(k,20)=(*q)(19);
    dataPlot(k,21)=(*q)(20);

    dataPlot(k,22)=(*v)(0);
    dataPlot(k,23)=(*v)(1);
    dataPlot(k,24)=(*v)(2);

    dataPlot(k,25)=(*yfunc)(0);
    dataPlot(k,26)=(*yfunc1)(0);
    dataPlot(k,27)=(*yfunc2)(0);
    dataPlot(k,28)=(*yfunc3)(0);
    dataPlot(k,29)=(*yfunc4)(0);
    dataPlot(k,30)=(*yfunc5)(0);

    dataPlot(k,32)=(*v)(9);
    dataPlot(k,33)=(*v)(10);
    dataPlot(k,34)=(*v)(14);
    dataPlot(k,35)=(*v)(15);
    dataPlot(k,36)=(*v)(19);
    dataPlot(k,37)=(*v)(20);

    dataPlot(k,38)=(*Force)(9);

    //-------------gnuplot data----------------

    i=0;
    while(i < nDof)
    {
      qq[i]=(*q)(i);
      i++;
    }

    Tags(Test ,qq);

    testdatabase(k,0)= Test[4];
    testdatabase(k,1)= Test[27];
    testdatabase(k,2)= Test[50];  //FL
    testdatabase(k,3)= Test[5];
    testdatabase(k,4)= Test[28];
    testdatabase(k,5)= Test[51];  //FR
    testdatabase(k,6)= Test[9];
    testdatabase(k,7)= Test[32];
    testdatabase(k,8)= Test[55];  //ML
    testdatabase(k,9)= Test[10];
    testdatabase(k,10)= Test[33];
    testdatabase(k,11)= Test[56];  //BL
    testdatabase(k,12)= Test[14];
    testdatabase(k,13)= Test[37];
    testdatabase(k,14)= Test[60];  //BR
    testdatabase(k,15)= Test[15];
    testdatabase(k,16)= Test[38];
    testdatabase(k,17)= Test[61];

    //------------------------------------------

    boost::timer time;
    time.restart();

    // --- Time loop ---

    cout << "Start computation ... " << endl;

    boost::progress_display show_progress(N);

    double static_torque = 885;
    double sliding_torque = 10000;

    while(s->hasNextEvent())
    {
      osnspb->setNumericsVerboseMode(0);
      //cout << "k value ..ak1. " << k << endl;
      k++;
      iteration_failed=k;
      ++show_progress;
      //	if (!(div(k,1000).rem))  cout <<"Step number "<< k << "\n";

      // Solve problem
      s->computeOneStep();
     
      //s->newtonSolve(criterion,maxIter);
      // Data Output

      dataPlot(k, 0) =  s->nextTime();

      if(dataPlot(k, 0) >= 50){

        (*Force)(9) = 21500;       //FL traction
        (*Force)(10) = 21500;      //FR  traction
        (*Force)(14) = 21500;      //ML traction
        (*Force)(15) = 21500;      //BL traction
        (*Force)(19) = 21500;      //MR traction
        (*Force)(20) = 21500;      //BR traction
        
      }

      /*if(dataPlot(k, 0) >= 50 && dataPlot(k, 0) < 55){

        (*Force)(9) = 47000;       //FL traction
        (*Force)(10) = 47000;      //FR  traction
        (*Force)(14) = 47000;      //ML traction
        (*Force)(15) = 47000;      //BL traction
        (*Force)(19) = 47000;      //MR traction
        (*Force)(20) = 47000;      //BR traction
        
      }

      if(dataPlot(k, 0) >= 55){

        (*Force)(9) = 8000;       //FL traction
        (*Force)(10) = 8000;      //FR  traction
        (*Force)(14) = 8000;      //ML traction
        (*Force)(15) = 8000;      //BL traction
        (*Force)(19) = 8000;      //MR traction
        (*Force)(20) = 8000;      //BR traction
        
      }*/

      Pvalue(k, 0) = dataPlot(k, 0);

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


      lambdas(k, 0) = dataPlot(k, 0);

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

      yfunction(k, 0) = dataPlot(k, 0);

      yfunction(k, 1) = inter[6]->y(0)->getValue(0);
      yfunction(k, 2) = inter[6]->y(0)->getValue(1);
      yfunction(k, 3) = inter[6]->y(0)->getValue(2);

      yfunction(k, 4) = inter[7]->y(0)->getValue(0);
      yfunction(k, 5) = inter[7]->y(0)->getValue(1);
      yfunction(k, 6) = inter[7]->y(0)->getValue(2);

      yfunction(k, 7) = inter[8]->y(0)->getValue(0);
      yfunction(k, 8) = inter[8]->y(0)->getValue(1);
      yfunction(k, 9) = inter[8]->y(0)->getValue(2);

      yfunction(k, 10) = inter[9]->y(0)->getValue(0);
      yfunction(k, 11) = inter[9]->y(0)->getValue(1);
      yfunction(k, 12) = inter[9]->y(0)->getValue(2);

      yfunction(k, 13) = inter[10]->y(0)->getValue(0);
      yfunction(k, 14) = inter[10]->y(0)->getValue(1);
      yfunction(k, 15) = inter[10]->y(0)->getValue(2);

      yfunction(k, 16) = inter[11]->y(0)->getValue(0);
      yfunction(k, 17) = inter[11]->y(0)->getValue(1);
      yfunction(k, 18) = inter[11]->y(0)->getValue(2);

      ydotfunction(k, 0) = dataPlot(k, 0);

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

      velocity(k, 0) = dataPlot(k, 0);

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

      position(k, 0) = dataPlot(k, 0);

      position(k, 1) = (*q)(0)/100;
      position(k, 2) = (*q)(1)/100;
      position(k, 3) = (*q)(2)/100;
 
      //cout << position(k, 1) << " " << position(k, 2) << " " << position(k, 3) << endl;

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

      dataPlot(k,1)=(*q)(0)/100;
      dataPlot(k,2)=(*q)(1)/100;
      dataPlot(k,3)=(*q)(2)/100;
          
      dataPlot(k,4)=(*q)(3);
      dataPlot(k,5)=(*q)(4);
      dataPlot(k,6)=(*q)(5);
      dataPlot(k,7)=(*q)(6);
      dataPlot(k,8)=(*q)(7);
      dataPlot(k,9)=(*q)(8);
      dataPlot(k,10)=(*q)(9);
      dataPlot(k,11)=(*q)(10);
      dataPlot(k,12)=(*q)(11);
      dataPlot(k,13)=(*q)(12);
      dataPlot(k,14)=(*q)(13);
      dataPlot(k,15)=(*q)(14);
      dataPlot(k,16)=(*q)(15);
      dataPlot(k,17)=(*q)(16);
      dataPlot(k,18)=(*q)(17);
      dataPlot(k,19)=(*q)(18);
      dataPlot(k,20)=(*q)(19);
      dataPlot(k,21)=(*q)(20);
      dataPlot(k,22)=(*v)(0);
      dataPlot(k,23)=(*v)(1);
      dataPlot(k,24)=(*v)(2);

      dataPlot(k,25)=(*yfunc)(0);
      dataPlot(k,26)=(*yfunc1)(0);
      dataPlot(k,27)=(*yfunc2)(0);
      dataPlot(k,28)=(*yfunc3)(0);
      dataPlot(k,29)=(*yfunc4)(0);
      dataPlot(k,30)=(*yfunc5)(0);

      dataPlot(k,32)=(*v)(9);
      dataPlot(k,33)=(*v)(10);
      dataPlot(k,34)=(*v)(14);
      dataPlot(k,35)=(*v)(15);
      dataPlot(k,36)=(*v)(19);
      dataPlot(k,37)=(*v)(20);

      dataPlot(k,38)=(*Force)(9);

      //-------------------gnuplot ------------------

      i=0;
      while(i < nDof)
      {
        qq[i]=(*q)(i);
        i++;
      }
      Tags(Test,qq);

      testdatabase(k,0)= Test[4];
      testdatabase(k,1)= Test[27];
      testdatabase(k,2)= Test[50];   //FL
      testdatabase(k,3)= Test[5];
      testdatabase(k,4)= Test[28];
      testdatabase(k,5)= Test[51];   //FR
      testdatabase(k,6)= Test[9];
      testdatabase(k,7)= Test[32];
      testdatabase(k,8)= Test[55];   //ML
      testdatabase(k,9)= Test[10];
      testdatabase(k,10)= Test[33];
      testdatabase(k,11)= Test[56];  //BL
      testdatabase(k,12)= Test[14];
      testdatabase(k,13)= Test[37];
      testdatabase(k,14)= Test[60];  //BR
      testdatabase(k,15)= Test[15];
      testdatabase(k,16)= Test[38];
      testdatabase(k,17)= Test[61];

    //--------------------------------------------

      s->nextStep();
    }

    cout<<"End of computation - Number of iterations done: "<<k<<endl;
    cout << "Computation Time " << time.elapsed()  << endl;

    // --- Output files ---
    cout<<"====> Output file writing ..."<<endl;
    const char *Names[17]=
    {
      "DEF Rover_RootRotInterp OrientationInterpolator{\n",
      "DEF Rover_body_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_l_pendulum_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_lf_wheelAxis_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_lf_wheel_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_lm_wheelAxis_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_lm_wheel_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_r_pendulum_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_rf_wheelAxis_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_rf_wheel_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_rm_wheelAxis_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_rm_wheel_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_b_pendulum_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_br_wheelAxis_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_br_wheel_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_bl_wheelAxis_jointRotInterp OrientationInterpolator{\n",
      "DEF Rover_bl_wheel_jointRotInterp OrientationInterpolator{\n"
    };


    const char *NamesRotationVector[17]=
    {
      "Rover_RootRotInterp OrientationInterpolator{\n",
      "Rover_body_jointRotInterp OrientationInterpolator{\n",
      "1 0 0",       //DEF Rover_l_pendulum_jointRotInterp
      "0 -1 0",       //DEF Rover_lf_wheelAxis_jointRotInterp
      "1 0 0",	//DEF Rover_lf_wheel_jointRotInterp
      "0 -1 0",	//DEF Rover_lm_wheelAxis_jointRotInterp
      "1 0 0",	//DEF Rover_lm_wheel_jointRotInterp
      "1 0 0",	//DEF Rover_r_pendulum_jointRotInterp
      "0 -1 0",	//DEF Rover_rf_wheelAxis_jointRotInterp
      "1 0 0",	//DEF Rover_rf_wheel_jointRotInterp
      "0 -1 0",	//DEF Rover_rm_wheelAxis_jointRotInterp
      "1 0 0",	//DEF Rover_rm_wheel_jointRotInterp
      "0 0 1",	//DEF Rover_b_pendulum_jointRotInterp
      "0 -1 0",	//DEF Rover_br_wheelAxis_jointRotInterp
      "1 0 0",	//DEF Rover_br_wheel_jointRotInterp
      "0 -1 0",	//DEF Rover_bl_wheelAxis_jointRotInterp
      "1 0 0"   //DEF Rover_bl_wheel_jointRotInterp

    };	

    //all variables except trunk coords

    int NamesDOF[17];
    NamesDOF[0]=0;
    NamesDOF[1]=0;
    NamesDOF[2]=12;
    NamesDOF[3]=14;
    NamesDOF[4]=16;
    NamesDOF[5]=13;
    NamesDOF[6]=15;
    NamesDOF[7]=17;
    NamesDOF[8]=19;
    NamesDOF[9]=21;
    NamesDOF[10]=18;
    NamesDOF[11]=20;
    NamesDOF[12]=7;
    NamesDOF[13]=9;
    NamesDOF[14]=11;
    NamesDOF[15]=8;
    NamesDOF[16]=10;

  double RootRotationVector[4];
  double PlaneRotationVector[4];

  
    FILE * pFile;
    pFile = fopen ("data.wrl","w");

    FILE * sphFile;
    sphFile = fopen ("AnimSphere.wrl","w");

    //----------------Animation------------------

    fprintf(pFile,"DEF Animation Group {\n  children [\n");
    fprintf(pFile,"\n");




    fprintf(sphFile,"DEF Animation Group {\n  children [\n");
    fprintf(sphFile,"\n");

    fprintf(sphFile,"DEF FLWheelInterp PositionInterpolator{\n");
    fprintf(sphFile,"    key [ 0 ");
    for (int cmp =1;cmp <= N;cmp++){

    fprintf(sphFile,",%e",(dataPlot(cmp,0)-t0)/(T-t0));

    }
	
    fprintf(sphFile,"]\n"); 
    fprintf(sphFile,"    keyValue [  ");
    fprintf(sphFile,"%e %e %e,\n",dataPlot(0,1),dataPlot(0,2),dataPlot(0,3));
    for (int cmp =1;cmp <= N;cmp++){

    fprintf(sphFile,"%e %e %e,\n",-dataPlot(cmp,3),dataPlot(cmp,2),-dataPlot(cmp,1));}

    fprintf(sphFile,"  ]\n}\n");

    fprintf(sphFile,"  ]\n}\n");

    fclose(sphFile);

    system("cat sphere.wrl AnimSphere.wrl RoutesSphere.wrl > runSP.wrl");



    fprintf(pFile,"DEF Rover_rootPosInterp PositionInterpolator{\n");
    fprintf(pFile,"    key [ 0 ");
    for (int cmp =1;cmp <= N;cmp++){
        fprintf(pFile,",%e",(dataPlot(cmp,0)-t0)/(T-t0));}
	
    fprintf(pFile,"]\n"); 
    fprintf(pFile,"    keyValue [  ");
    fprintf(pFile,"%e %e %e,\n",dataPlot(0,1),dataPlot(0,2),dataPlot(0,3));
    for (int cmp =1;cmp <= N;cmp++){

    fprintf(pFile,"%e %e %e,\n",-dataPlot(cmp,3),dataPlot(cmp,2),-dataPlot(cmp,1));}

    fprintf(pFile,"  ]\n}\n");

    //----------root oritation-------------------

    fprintf(pFile,"DEF Rover_rootRotInterp OrientationInterpolator{\n");
    fprintf(pFile,"    key [ 0 ");
    for (int cmp =1;cmp <= N;cmp++){
        fprintf(pFile,",%e",(dataPlot(cmp,0)-t0)/(T-t0));}
	
    fprintf(pFile,"]\n"); 
    fprintf(pFile,"    keyValue [  ");

    i = 0;
    while(i < nDof)
  	{
          qq[i]=dataPlot(0,i+1);
          i++;
	  } 
    RRV(RootRotationVector,RAngle,qq);
    if (RootRotationVector[3]==0 )
      {fprintf(pFile,"%e %e %e %e,\n",0.0,0.0,0.0,0.0);}
    else
      {fprintf(pFile,"%e %e %e %e,\n", RootRotationVector[2], RootRotationVector[1], RootRotationVector[0], RootRotationVector[3]);}
   
    for (int cmp =1;cmp <= N;cmp++){
         i = 0;
    while(i < nDof)
	{  
           qq[i]=dataPlot(cmp,i+1);
          i++;
	} 
    RRV(RootRotationVector,RAngle,qq);
    if (RootRotationVector[3]==0 )
      {fprintf(pFile,"%e %e %e %e,\n",0.0,0.0,0.0,0.0);}
    else
      {fprintf(pFile,"%e %e %e %e,\n", RootRotationVector[2], RootRotationVector[1], RootRotationVector[0], RootRotationVector[3]);}
    }
 
    fprintf(pFile,"  ]\n}\n");

    //---------segment rotation----------------

    for (int CountN=2; CountN<=16; CountN++){
    
    fprintf(pFile,Names[CountN]);
    fprintf(pFile,"    key [ 0 ");
    for (int cmp =1;cmp <= N;cmp++){
        fprintf(pFile,",%e",(dataPlot(cmp,0)-t0)/(T-t0));}
	
    fprintf(pFile,"]\n"); 
    fprintf(pFile,"    keyValue [  ");
    fprintf(pFile,NamesRotationVector[CountN]);
    fprintf(pFile," %e,\n",dataPlot(0,NamesDOF[CountN]));

    for (int cmp =1;cmp <= N;cmp++){
    fprintf(pFile,NamesRotationVector[CountN]);
    fprintf(pFile," %e,\n",dataPlot(cmp,NamesDOF[CountN]));}

    fprintf(pFile,"  ]\n}\n");
                                 }
    //fprintf(pFile,"  ]\n}\n");
    fclose(pFile);
    //system("cat RoverModel.wrl data.wrl RoverAnimation.wrl > run.wrl");
    system("cat output.wrl RoverModel.wrl data.wrl RoverAnimation.wrl > run.wrl");

    // --- Output files ---
    //ioMatrix::write("DoublePendulumResult.dat", "ascii",
    //                dataPlot,"noDim");
    ioMatrix::write("TAGSDATA.dat", "ascii",
                    testdatabase,"noDim");
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

