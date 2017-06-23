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

// Rover3D with Fixed Sphere
// Two Shpere example




#include "Robot.h"
#include "SiconosKernel.hpp"
#include <stdlib.h>
#include "Rover3DWheelFixedSphereR.hpp"
using namespace std;

#include <boost/progress.hpp>


static int iteration_failed = 0;

/* do nothing if solver does not converge */
void localCheckSolverOuput(int info, Simulation* simu)
{
  if(info)
  {
    cout << "iteration failed " << iteration_failed << endl;
    cout << "iparam[0]" << simu ->oneStepNSProblem(SICONOS_OSNSP_TS_VELOCITY)->numericsSolverOptions()->iparam[0] << endl;
    FILE * foutput;

    char filename[100];

    sprintf(filename,"Rover%d.dat", iteration_failed);

    foutput = fopen(filename, "w");
    SP::FrictionContact fc3D = std11::static_pointer_cast<FrictionContact>(simu ->oneStepNSProblem(SICONOS_OSNSP_TS_VELOCITY));

    //fc3D.get()->display();
    //FrictionContactProblem * numfc3D = (fc3D.get()->numericsProblem()).get();

    //NumericsMatrix *  matmat =  numfc3D->M;

    //cout << "matmat->storageType" << matmat->storageType <<  endl;

    //display(numfc3D->M);





    frictionContact_printInFile((fc3D->frictionContactProblem()).get(), foutput);
    fclose(foutput);
  }


};



int main(int argc, char* argv[])
{
  try
  {

    // ================= Creation of the model =======================

    // User-defined main parameters
    unsigned int nDof = 21;           // degrees of freedom for robot rover_ds
    double t0 = 0;                   // initial computation time
    double T = 120;                   // final computation time
    double h = 0.02;                // time step
    double eps_n=0.3;
    double eps_t=0.0;
    double mu=0.7;
    double R=12.5;                 //Wheel Radius
    double thickness=2.5;                 //Wheel Radius
    double l=20;
    double g=9.8;                  //gravity
    double ls1,ls2;
    double RAngle[4]= {0,-8000,0,8000};  //Shpere1 input format: coordinate x,y,z,radius
    double RAngle2[4]= {4300,-8000,0,8000}; //Shpere2 input format: coordinate x,y,z,radius



    // -> mind to set the initial conditions below.

    // -------------------------
    // --- Dynamical systems ---
    // -------------------------

    // --- DS: RoverDS ---

    // Initial position (angles in radian)
    SP::SiconosVector q0(new SiconosVector(nDof));
    SP::SiconosVector v0(new SiconosVector(nDof));
    q0->zero();
    v0->zero();

    (*q0)(0) = 600;
    (*q0)(2) = 1800;//1500;
    (*q0)(1) = -40.5;
    (*q0)(7) = 0.04;
    (*q0)(8) = 0.04;
    //(*q0)(6) = 0.0;

    SP::LagrangianDS rover_ds(new LagrangianDS(q0, v0));
    // external plug-in
    rover_ds->setComputeMassFunction("RobotPlugin.so","mass");

    // -- Set external forces (traction) --
    SP::SiconosVector weight(new SiconosVector(nDof));
    (*weight)(9) = -2000;       //FL traction
    (*weight)(10) = -2000;      //FR  traction
    (*weight)(14) = -2000;  //ML traction
    (*weight)(15) = -2000;  //BL traction
    (*weight)(19) = -2000;  //MR traction
    (*weight)(20) = -2000;  //BR traction

    rover_ds->setFExtPtr(weight);

    rover_ds->setComputeFGyrFunction("RobotPlugin.so","NLEffects");
    rover_ds->setComputeJacobianFGyrqFunction("RobotPlugin.so","jacobianNNLq");
    rover_ds->setComputeJacobianFGyrqDotFunction("RobotPlugin.so","jacobianVNNL");
    rover_ds->setComputeFIntFunction("RobotPlugin.so","U");
    rover_ds->setComputeJacobianFIntqFunction("RobotPlugin.so","jacobFintQ");
    rover_ds->setComputeJacobianFIntqDotFunction("RobotPlugin.so","jacobFintV");


    // -------------------
    // --- Interactions---
    // -------------------





    vector<SP::Relation> relation(6);
    vector<SP::Interaction> inter(6);
    SP::NonSmoothLaw nslaw(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));
    for(int i=0; i<6; i++)
    {
      relation[i].reset(new Rover3DWheelFixedSphereR(i,8000.0,0.0,-8000.0,0.0,R,thickness));
      inter[i].reset(new Interaction(nslaw, relation[i]));
    }


    /*
       // -- relations --
       string G ="RobotPlugin:G0";
       SP::NonSmoothLaw nslaw(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));
       //SP::Relation relation(new LagrangianScleronomousR("RobotPlugin:h0",G));
       SP::Relation relation(new Rover3DWheelFixedSphereR(0,8000.0,0.0,-8000.0,0.0,12.5));
       SP::Interaction inter(new Interaction("floor-mass1", allDS,0,3, nslaw, relation));


       string G1 ="RobotPlugin:G1";
       SP::NonSmoothLaw nslaw1(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));
       SP::Relation relation1(new LagrangianScleronomousR("RobotPlugin:h1",G1));
       SP::Interaction inter1(new Interaction("floor-mass2",allDS,1,3, nslaw1, relation1));


       string G2 ="RobotPlugin:G2";
       SP::NonSmoothLaw nslaw2(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));
       SP::Relation relation2(new LagrangianScleronomousR("RobotPlugin:h2",G2));
       SP::Interaction inter2(new Interaction("floor-mass3", allDS,2,3, nslaw2, relation2));


       string G3 ="RobotPlugin:G3";
       SP::NonSmoothLaw nslaw3(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));
       SP::Relation relation3(new LagrangianScleronomousR("RobotPlugin:h3",G3));
       SP::Interaction inter3(new Interaction("floor-mass4",allDS,3,3, nslaw3, relation3));

       string G4 ="RobotPlugin:G4";
       SP::NonSmoothLaw nslaw4(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));
       SP::Relation relation4(new LagrangianScleronomousR("RobotPlugin:h4",G4));
       SP::Interaction inter4(new Interaction("floor-mass5",allDS,4,3, nslaw4, relation4));

       string G5 ="RobotPlugin:G5";
       SP::NonSmoothLaw nslaw5(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));
       SP::Relation relation5(new LagrangianScleronomousR("RobotPlugin:h5",G5));
       SP::Interaction inter5(new Interaction("floor-mass6",allDS,5,3, nslaw5, relation5));   */

    //-------------------------------------------------------------------------

    string GTwo ="RobotPlugin:G20";
    SP::NonSmoothLaw nslawTwo(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));
    //SP::Relation relationTwo(new LagrangianScleronomousR("RobotPlugin:h20",GTwo));
    SP::Relation relationTwo(new Rover3DWheelFixedSphereR(0, 8000.0,4300.0,-8000.0,0.0,12.5, thickness));
    SP::Interaction interTwo(new Interaction( nslawTwo, relationTwo));


    string GTwo1 ="RobotPlugin:G21";
    SP::NonSmoothLaw nslawTwo1(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));
    SP::Relation relationTwo1(new LagrangianScleronomousR("RobotPlugin:h21",GTwo1));
    SP::Interaction interTwo1(new Interaction( nslawTwo1, relationTwo1));


    string GTwo2 ="RobotPlugin:G22";
    SP::NonSmoothLaw nslawTwo2(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));
    SP::Relation relationTwo2(new LagrangianScleronomousR("RobotPlugin:h22",GTwo2));
    SP::Interaction interTwo2(new Interaction( nslawTwo2, relationTwo2));


    string GTwo3 ="RobotPlugin:G23";
    SP::NonSmoothLaw nslawTwo3(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));
    SP::Relation relationTwo3(new LagrangianScleronomousR("RobotPlugin:h23",GTwo3));
    SP::Interaction interTwo3(new Interaction( nslawTwo3, relationTwo3));

    string GTwo4 ="RobotPlugin:G24";
    SP::NonSmoothLaw nslawTwo4(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));
    SP::Relation relationTwo4(new LagrangianScleronomousR("RobotPlugin:h24",GTwo4));
    SP::Interaction interTwo4(new Interaction(nslawTwo4, relationTwo4));

    string GTwo5 ="RobotPlugin:G25";
    SP::NonSmoothLaw nslawTwo5(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));
    SP::Relation relationTwo5(new LagrangianScleronomousR("RobotPlugin:h25",GTwo5));
    SP::Interaction interTwo5(new Interaction(nslawTwo5, relationTwo5));



    // -------------
    // --- Model ---
    // -------------

    SP::Model Rover3D(new Model(t0,T));
    Rover3D->nonSmoothDynamicalSystem()->insertDynamicalSystem(rover_ds);
    Rover3D->nonSmoothDynamicalSystem()->link(interTwo, rover_ds);
    Rover3D->nonSmoothDynamicalSystem()->link(interTwo1, rover_ds);
    Rover3D->nonSmoothDynamicalSystem()->link(interTwo2, rover_ds);
    Rover3D->nonSmoothDynamicalSystem()->link(interTwo3, rover_ds);
    Rover3D->nonSmoothDynamicalSystem()->link(interTwo4, rover_ds);
    Rover3D->nonSmoothDynamicalSystem()->link(interTwo5, rover_ds);

    for(int i=0; i<6; i++)
    {
      Rover3D->nonSmoothDynamicalSystem()->link(inter[i], rover_ds);
    }
    // ----------------
    // --- Simulation ---
    // ----------------

    // -- Time discretisation --
    SP::TimeDiscretisation t(new TimeDiscretisation(t0,h));

    SP::TimeStepping s(new TimeStepping(t));
    //        s->setUseRelativeConvergenceCriteron(true);
    Rover3D->setSimulation(s);

    // -- OneStepIntegrators --

    //double theta=0.500001;
    double theta=0.50000001;

    SP::MoreauJeanOSI OSI(new MoreauJeanOSI(theta));
    s->insertIntegrator(OSI);


    //*******************************************************
    // -- OneStepNsProblem --
    //osnspb.reset(new FrictionContact(3));
    SP::OneStepNSProblem osnspb(new FrictionContact(3));

    osnspb->numericsSolverOptions()->iparam[0]=100000; // Max number of
    // iterations
    // osnspb->numericsSolverOptions()->iparam[1]=10000;  // compute error
    //                                                  // iterations

    osnspb->numericsSolverOptions()->iparam[4]=0;   // projection
    // Solver/formulation  0: projection, 1: Newton/AlartCurnier, 2: Newton/Fischer-Burmeister
    osnspb->numericsSolverOptions()->dparam[0]=1e-5;// Tolerance
    osnspb->numericsSolverOptions()->dparam[2]=1e-5;// Local tolerance


    //*********************************************************************************

    s->insertNonSmoothProblem(osnspb);
    //s->setCheckSolverFunction(localCheckSolverOuput);
    cout << "=== End of model loading === " << endl;


    // ================================= Computation =================================

    // --- Simulation initialization ---
    cout << "=== Simulation initialization ===" << endl;
    Rover3D->initialize();




    cout <<"End of initialisation" << endl;
    int i=0;
    int k=0;
    int kk= 0;
    int N = (int)((T-t0)/h)+1;
    int NN=3*N+3;
    cout << "Number of time step   " << N << endl;
    // --- Get the values to be plotted ---
    // -> saved in a matrix dataPlot
    SimpleMatrix dataPlot(N+1,nDof+17+6);

    double qq[21];
    double Test[69];

    SimpleMatrix testdatabase(N+1,18);

    SP::SiconosVector q = rover_ds->q();
    SP::SiconosVector v = rover_ds->velocity();
    SP::SiconosVector yfunc = inter[0]->y(0);
    SP::SiconosVector yfunc1 = inter[1]->y(0);
    SP::SiconosVector yfunc2 = inter[2]->y(0);
    SP::SiconosVector yfunc3 = inter[3]->y(0);
    SP::SiconosVector yfunc4 = inter[4]->y(0);
    SP::SiconosVector yfunc5 = inter[5]->y(0);
    SP::SiconosVector lambda = inter[1]->lambda(1);
    SP::SiconosVector y2func = interTwo->y(0);
    SP::SiconosVector y2func1 = interTwo1->y(0);
    SP::SiconosVector y2func2 = interTwo2->y(0);
    SP::SiconosVector y2func3 = interTwo3->y(0);
    SP::SiconosVector y2func4 = interTwo4->y(0);
    SP::SiconosVector y2func5 = interTwo5->y(0);

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
    dataPlot(k,10)= (*q)(9);
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
    dataPlot(k,31)=(*lambda)(0);
    dataPlot(k,32)=(*v)(9);
    dataPlot(k,33)=(*v)(10);
    dataPlot(k,34)=(*v)(14);
    dataPlot(k,35)=(*v)(15);
    dataPlot(k,36)=(*v)(19);
    dataPlot(k,37)=(*v)(20);
    dataPlot(k,38)=(*y2func)(0);
    dataPlot(k,39)=(*y2func1)(0);
    dataPlot(k,40)=(*y2func2)(0);
    dataPlot(k,41)=(*y2func3)(0);
    dataPlot(k,42)=(*y2func4)(0);
    dataPlot(k,43)=(*y2func5)(0);

    //----------------------gnuplot data----------------************************
    i=0;
    while(i < nDof)
    {
      qq[i]=(*q)(i);
      i++;
    }
    Tags(Test ,qq);

//--------------------------------------------------


//-------------------------------------------************************

    boost::timer time;
    time.restart();
    // --- Time loop ---
    cout << "Start computation ... " << endl;

    boost::progress_display show_progress(N);

    while(k < N)
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
      //cout << "k value ..ak2. " << k << endl;

      dataPlot(k, 0) =  s->nextTime();

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
      dataPlot(k,31)=(*lambda)(0);
      dataPlot(k,32)=(*v)(9);
      dataPlot(k,33)=(*v)(10);
      dataPlot(k,34)=(*v)(14);
      dataPlot(k,35)=(*v)(15);
      dataPlot(k,36)=(*v)(19);
      dataPlot(k,37)=(*v)(20);
      dataPlot(k,38)=(*y2func)(0);
      dataPlot(k,39)=(*y2func1)(0);
      dataPlot(k,40)=(*y2func2)(0);
      dataPlot(k,41)=(*y2func3)(0);
      dataPlot(k,42)=(*y2func4)(0);
      dataPlot(k,43)=(*y2func5)(0);
      //-------------------gnuplot ------------------*********************
      i=0;
      while(i < nDof)
      {
        qq[i]=(*q)(i);
        i++;
      }
      Tags(Test,qq);


//--------------------------------------------------

      //----------------------------------------------------**********************

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
      "1 0 0"
    };	//DEF Rover_bl_wheel_jointRotInterp

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
    pFile = fopen("data.wrl","w");

//---------------Sphere---------------------

    fprintf(pFile,"DEF SPHERE Transform {\n");
    fprintf(pFile,"translation ");
    fprintf(pFile,"%e %e %e\n",-RAngle[2]/100 ,RAngle[1]/100, -RAngle[0]/100);

    fprintf(pFile,"children [\n Shape {\n appearance Appearance {\n material Material { diffuseColor 0 1 1 }}\n");
    fprintf(pFile,"geometry Sphere{ radius %e }", RAngle[3]/100);
    fprintf(pFile,"}\n]\n}\n");


    fprintf(pFile,"DEF SPHERE2 Transform {\n");
    fprintf(pFile,"translation ");
    fprintf(pFile,"%e %e %e\n",-RAngle2[2]/100 ,RAngle2[1]/100, -RAngle2[0]/100);

    fprintf(pFile,"children [\n Shape {\n appearance Appearance {\n material Material { diffuseColor 1 1 0 }}\n");
    fprintf(pFile,"geometry Sphere{ radius %e }", RAngle2[3]/100);
    fprintf(pFile,"}\n]\n}\n");


//----------------Animation------------------
    fprintf(pFile,"DEF Animation Group {\n  children [\n");
    fprintf(pFile,"\n");

    fprintf(pFile,"DEF Rover_rootPosInterp PositionInterpolator{\n");
    fprintf(pFile,"    key [ 0 ");
    for(int cmp =1; cmp <= N; cmp++)
    {
      fprintf(pFile,",%e",(dataPlot(cmp,0)-t0)/(T-t0));
    }

    fprintf(pFile,"]\n");
    fprintf(pFile,"    keyValue [  ");
    fprintf(pFile,"%e %e %e,\n",dataPlot(0,1),dataPlot(0,2),dataPlot(0,3));
    for(int cmp =1; cmp <= N; cmp++)
    {

      fprintf(pFile,"%e %e %e,\n",-dataPlot(cmp,3),dataPlot(cmp,2),-dataPlot(cmp,1));
    }

    fprintf(pFile,"  ]\n}\n");

// ----------root oritation--------------
    fprintf(pFile,"DEF Rover_rootRotInterp OrientationInterpolator{\n");
    fprintf(pFile,"    key [ 0 ");
    for(int cmp =1; cmp <= N; cmp++)
    {
      fprintf(pFile,",%e",(dataPlot(cmp,0)-t0)/(T-t0));
    }

    fprintf(pFile,"]\n");
    fprintf(pFile,"    keyValue [  ");

    i = 0;
    while(i < nDof)
    {
      qq[i]=dataPlot(0,i+1);
      i++;
    }
    RRV(RootRotationVector,qq);
    if(RootRotationVector[3]==0)
    {
      fprintf(pFile,"%e %e %e %e,\n",0.0,0.0,0.0,0.0);
    }
    else
    {
      fprintf(pFile,"%e %e %e %e,\n",RootRotationVector[2], RootRotationVector[1], RootRotationVector[0],RootRotationVector[3]);
    }

    for(int cmp =1; cmp <= N; cmp++)
    {
      i = 0;
      while(i < nDof)
      {
        qq[i]=dataPlot(cmp,i+1);
        i++;
      }
      RRV(RootRotationVector,qq);
      if(RootRotationVector[3]==0)
      {
        fprintf(pFile,"%e %e %e %e,\n",0.0,0.0,0.0,0.0);
      }
      else
      {
        fprintf(pFile,"%e %e %e %e,\n",RootRotationVector[2], RootRotationVector[1], RootRotationVector[0],RootRotationVector[3]);
      }
    }


    fprintf(pFile,"  ]\n}\n");

//---------segment rotation----------------
    for(int CountN=2; CountN<=16; CountN++)
    {

      fprintf(pFile, " %s", Names[CountN]);
      fprintf(pFile,"    key [ 0 ");
      for(int cmp =1; cmp <= N; cmp++)
      {
        fprintf(pFile,",%e",(dataPlot(cmp,0)-t0)/(T-t0));
      }

      fprintf(pFile,"]\n");
      fprintf(pFile,"    keyValue [  ");
      fprintf(pFile," %s",NamesRotationVector[CountN]);
      fprintf(pFile," %e,\n",dataPlot(0,NamesDOF[CountN]));

      for(int cmp =1; cmp <= N; cmp++)
      {
        fprintf(pFile," %s",NamesRotationVector[CountN]);
        fprintf(pFile," %e,\n",dataPlot(cmp,NamesDOF[CountN]));
      }

      fprintf(pFile,"  ]\n}\n");
    }
    //fprintf(pFile,"  ]\n}\n");
    fclose(pFile);
    system("cat RoverModel.wrl data.wrl RoverAnimation.wrl > run.wrl");


    // --- Output files ---
    ioMatrix::write("DoublePendulumResult.dat", "ascii",dataPlot,"noDim");
    ioMatrix::write("TAGSDATA.dat", "ascii",testdatabase,"noDim");
  }

  catch(SiconosException e)
  {
    cout << e.report() << endl;
  }
  catch(...)
  {
    cout << "Exception caught in \'sample/MultiBeadsColumn\'" << endl;
  }
}
