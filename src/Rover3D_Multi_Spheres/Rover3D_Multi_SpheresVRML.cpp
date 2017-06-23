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
// Multi Shpere
// Author: Jianhui YANG
// Team: Bipop




#include "Robot.h"
#include "SiconosKernel.hpp"
#include <stdlib.h>
#include "Rover3DWheelFixedSphereR.hpp"
using namespace std;

#include <boost/progress.hpp>


static int iteration_failed = 0;

/* do nothing if solver does not converge */
// void localCheckSolverOuput(int info, Simulation* simu)
// {
//   if (info)
//     {
//       cout << "iteration failed " << iteration_failed << endl;
//       cout << "iparam[0]" << simu ->oneStepNSProblem(SICONOS_OSNSP_TS_VELOCITY)->numericsSolverOptions()->iparam[0] << endl;
//       FILE * foutput;

//       char filename[100];

//       sprintf(filename,"Rover%d.dat", iteration_failed  );

//       foutput = fopen(filename, "w");
//       SP::FrictionContact fc3D = boost::static_pointer_cast<FrictionContact>(simu ->oneStepNSProblem(SICONOS_OSNSP_TS_VELOCITY));

//       //fc3D.get()->display();
//       //FrictionContactProblem * numfc3D = (fc3D.get()->numericsProblem()).get();

//       //NumericsMatrix *  matmat =  numfc3D->M;

//       //cout << "matmat->storageType" << matmat->storageType <<  endl;

//       //display(numfc3D->M);





//       frictionContact_printInFile((fc3D->numericsProblem()).get(), foutput);
//       fclose(foutput);
//     }


// };


void write_vrml(SimpleMatrix * data, int nb_spheres, double Sphere[nb_spheres][4], int nb_time_steps, double T, double t0, unsigned int ndof)
{

  
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

    FILE * pFile;
    pFile = fopen("data.wrl","w");
    
    //---------------Sphere---------------------
    for(int i=0; i<nb_spheres; i++)
    {
      fprintf(pFile,"DEF SPHERE Transform {\n");
      fprintf(pFile,"translation ");
      fprintf(pFile,"%e %e %e\n",-Sphere[i][2]/100 ,Sphere[i][1]/100, -Sphere[i][0]/100);

      fprintf(pFile,"children [\n Shape {\n appearance Appearance {\n material Material { diffuseColor %e 1 %e }}\n",(double) i/nb_spheres,1- (double) i/nb_spheres);

      fprintf(pFile,"geometry Sphere{ radius %e }", Sphere[i][3]/100);
      fprintf(pFile,"}\n]\n}\n");
    }


//----------------Animation------------------
    fprintf(pFile,"DEF Animation Group {\n  children [\n");
    fprintf(pFile,"\n");

    fprintf(pFile,"DEF Rover_RootPosInterp PositionInterpolator{\n");
    fprintf(pFile,"    key [ 0 ");
    for(int cmp =1; cmp <= nb_time_steps; cmp++)
    {
      fprintf(pFile,",%e",((*data)(cmp,0)-t0)/(T-t0));
    }

    fprintf(pFile,"]\n");
    fprintf(pFile,"    keyValue [  ");
    fprintf(pFile,"%e %e %e,\n",(*data)(0,1),(*data)(0,2),(*data)(0,3));
    for(int cmp =1; cmp <= nb_time_steps; cmp++)
    {

      fprintf(pFile,"%e %e %e,\n",-(*data)(cmp,3),(*data)(cmp,2),-(*data)(cmp,1));
    }

    fprintf(pFile,"  ]\n}\n");

// ----------root oritation--------------
    fprintf(pFile,"DEF Rover_RootRotInterp OrientationInterpolator{\n");
    fprintf(pFile,"    key [ 0 ");
    for(int cmp =1; cmp <= nb_time_steps; cmp++)
    {
      fprintf(pFile,",%e",((*data)(cmp,0)-t0)/(T-t0));
    }

    fprintf(pFile,"]\n");
    fprintf(pFile,"    keyValue [  ");

    double qq[ndof];
    
    for(unsigned int i=0;i<ndof;++i)
      qq[i]=(*data)(0,i+1);

    RRV(RootRotationVector,qq);
    if(RootRotationVector[3]==0)
    {
      fprintf(pFile,"%e %e %e %e,\n",0.0,0.0,0.0,0.0);
    }
    else
    {
      fprintf(pFile,"%e %e %e %e,\n",RootRotationVector[2], RootRotationVector[1], RootRotationVector[0],RootRotationVector[3]);
    }

    for(int cmp =1; cmp <= nb_time_steps; cmp++)
    {
      for(unsigned int i=0;i<ndof;++i)
        qq[i]=(*data)(cmp,i+1);

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

      fprintf(pFile, "%s", Names[CountN]);
      fprintf(pFile,"    key [ 0 ");
      for(int cmp =1; cmp <= nb_time_steps; cmp++)
      {
        fprintf(pFile,",%e",((*data)(cmp,0)-t0)/(T-t0));
      }

      fprintf(pFile,"]\n");
      fprintf(pFile,"    keyValue [  ");
      fprintf(pFile, "%s", NamesRotationVector[CountN]);
      fprintf(pFile," %e,\n",(*data)(0,NamesDOF[CountN]));

      for(int cmp =1; cmp <= nb_time_steps; cmp++)
      {
        fprintf(pFile, "%s", NamesRotationVector[CountN]);
        fprintf(pFile," %e,\n",(*data)(cmp,NamesDOF[CountN]));
      }

      fprintf(pFile,"  ]\n}\n");
    }
    //fprintf(pFile,"  ]\n}\n");
    fclose(pFile);
    //    system("cat RoverModel.wrl data.wrl RoverAnimation.wrl > run.wrl");
  

}



int main(int argc, char* argv[])
{
  try
  {

    // ================= Creation of the model =======================

    // User-defined main parameters
    unsigned int nDof = 21;        // degrees of freedom for robot arm
    double t0 = 0;                 // initial computation time
    double T = 15.;                 // final computation time
    double h = 0.005;               // time step
    double eps_n=0.1;
    double eps_t=0.0;
    double mu=0.8;
    double R=30;                 //Wheel Radius
    // Number of spheres
    int Ns = 50;
    double WheelT = 10;         //Wheel Thickness

    //======input data for SphereGeneration===============
    int NumSphere = Ns*Ns/2;
    const double AverageR = 50;
    const double AverageDistance = 60 ;
    double Sphere[NumSphere][4];

    // -----------------------SphereGeneration--------------------------

    //This part generate spheres automatically
    //If you prefer, you can input the sphere data manually
    //With the format Sphere[sphere No.][0]  x coordinate
    //                Sphere[sphere No.][1]  y coordinate
    //                Sphere[sphere No.][2]  z coordinate
    //                Sphere[sphere No.][3]  radius of sphere
    double eps;
    int NumS = 0;
    for(int i=0; i<Ns; i++)
      for(int j=0; j<Ns/2; j++)
      {
        eps=rand() / (double)(RAND_MAX);
        //eps=(1-(double) i/Ns)*1.5;
        Sphere[NumS][0] = AverageDistance*i+eps*AverageR*0.0;
        Sphere[NumS][2] = AverageDistance*j+eps*AverageR*0.0;
        Sphere[NumS][1] = -AverageR+eps*AverageR*0.0+AverageR*sin(Sphere[NumS][0]/500+3.1415927/2)+eps*AverageR*0.0;    //(Sphere[NumS][0]/1000+3.1415927/2)
        Sphere[NumS][3] = AverageR+eps*AverageR*0.0;
        NumS++;

      }
    //---------------------------------------------------------------------
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
    (*q0)(0) = Ns * 0.5 * AverageR;
    (*q0)(1) = 1.5 * AverageR;
    (*q0)(2) = Ns * 0.25 * AverageR;
    (*q0)(7) = -0.1;
    (*q0)(8) = -0.1;
    //(*q0)(6) = 0.0;

    SP::LagrangianDS rover_ds(new LagrangianDS(q0, v0));
    // external plug-in
    rover_ds->setComputeMassFunction("RobotPlugin.so","mass");

    // -- Set external forces (traction) --
    double driving_force = -4000; // -4000;
    SP::SiconosVector Force(new SiconosVector(nDof));
    (*Force)(9) = driving_force;       //FL traction
    (*Force)(10) = driving_force;      //FR  traction
    (*Force)(14) = driving_force;      //ML traction
    (*Force)(15) = driving_force;      //BL traction
    (*Force)(19) = driving_force;      //MR traction
    (*Force)(20) = driving_force;      //BR traction

    rover_ds->setFExtPtr(Force);

    rover_ds->setComputeFGyrFunction("RobotPlugin.so","FGyr");
    rover_ds->setComputeJacobianFGyrqFunction("RobotPlugin.so","jacobianFGyrq");
    rover_ds->setComputeJacobianFGyrqDotFunction("RobotPlugin.so","jacobianVFGyr");
    rover_ds->setComputeFIntFunction("RobotPlugin.so","U");
    rover_ds->setComputeJacobianFIntqFunction("RobotPlugin.so","jacobFintQ");
    rover_ds->setComputeJacobianFIntqDotFunction("RobotPlugin.so","jacobFintV");

    // ------------------------------
    // --- Interactions and Model ---
    // ------------------------------

    // add the dynamical system into the model
    SP::Model Rover3D(new Model(t0,T));
    Rover3D->nonSmoothDynamicalSystem()->insertDynamicalSystem(rover_ds);

    vector<SP::Relation> relation(6*NumSphere);
    vector<SP::Interaction> inter(6*NumSphere);

    SP::NonSmoothLaw nslaw(new NewtonImpactFrictionNSL(eps_n, eps_t, mu,3));
    
    int interaction_number;
    for(int i=0; i<NumSphere; i++)
    {
      for(int j=0; j<6; j++)
      {
	interaction_number = i * 6 + j;
        relation[interaction_number].reset(new Rover3DWheelFixedSphereR(j,Sphere[i][3],Sphere[i][0],Sphere[i][1],Sphere[i][2],R,WheelT));
        inter[interaction_number].reset(new Interaction(3, nslaw, relation[interaction_number], interaction_number));
	// link the interactions and the dynamical systems
	Rover3D->nonSmoothDynamicalSystem()->link(inter[interaction_number], rover_ds);
      }
    }

    // ----------------
    // --- Simulation ---
    // ----------------

    // -- Time discretisation --
    SP::TimeDiscretisation t(new TimeDiscretisation(t0,h));

    // -- OneStepIntegrator --
    //double theta=0.500001;
    double theta=0.50000001;

    SP::MoreauJeanOSI OSI(new MoreauJeanOSI(theta));

    // -- OneStepNsProblem --
    //osnspb.reset(new FrictionContact(3));
    SP::OneStepNSProblem osnspb(new FrictionContact(3));
    osnspb->numericsSolverOptions()->iparam[SICONOS_IPARAM_MAX_ITER]=10000; // Max number of
                                                      // iterations
    osnspb->numericsSolverOptions()->iparam[1]=10000;  // compute error
    // iterations
    //osnspb->numericsSolverOptions()->iparam[4]=1;   // projection
    // Solver/formulation  0: projection, 1: Newton/AlartCurnier, 2: Newton/Fischer-Burmeister
    osnspb->numericsSolverOptions()->dparam[SICONOS_DPARAM_TOL]=1e-5;// Tolerance
    //osnspb->numericsSolverOptions()->dparam[2]=1e-5;// Local tolerance
    osnspb->numericsSolverOptions()->internalSolvers->dparam[SICONOS_DPARAM_TOL]=1e-5;
    SP::TimeStepping s(new TimeStepping(t, OSI, osnspb));
    //        s->setUseRelativeConvergenceCriteron(true);
    Rover3D->setSimulation(s);

    //s->setCheckSolverFunction(localCheckSolverOuput);
    cout << "=== End of model loading === " << endl;


    // ================================= Computation =================================

    // --- Simulation initialization ---
    cout << "=== Initialization ===" << endl;
    Rover3D->initialize();


    cout <<"End of initialisation" << endl;
    int k=0;
    int N = (int)((T-t0)/h);//+1;
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
    SP::SiconosVector y2func = inter[6]->y(0);
    SP::SiconosVector y2func1 = inter[7]->y(0);
    SP::SiconosVector y2func2 = inter[8]->y(0);
    SP::SiconosVector y2func3 = inter[9]->y(0);
    SP::SiconosVector y2func4 = inter[10]->y(0);
    SP::SiconosVector y2func5 = inter[11]->y(0);

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
    for(unsigned int i=0;i<nDof; ++i)
      qq[i]=(*q)(i);

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
//--------------------------------------------------


// //-------------------------------------------************************

    boost::timer time;
    time.restart();
    // --- Time loop ---
    cout << "Start computation ... " << endl;

    boost::progress_display show_progress(N);

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
      for(unsigned int i=0;i<nDof;++i)
        qq[i]=(*q)(i);

      Tags(Test,qq);
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

      //--------------------------------------------------

      //----------------------------------------------------**********************

      s->nextStep();
    }

    cout<<"End of computation - Number of iterations done: "<<k<<endl;
    cout << "Computation Time " << time.elapsed()  << endl;

    write_vrml(&dataPlot, NumSphere, Sphere, N, T, t0, nDof);

    // --- Output files ---
    ioMatrix::write("Rover3D_Multi_Spheres.dat", "ascii",
                    dataPlot,"noDim");
    ioMatrix::write("TAGSDATA.dat", "ascii",
                    testdatabase,"noDim");

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
